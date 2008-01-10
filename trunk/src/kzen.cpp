/***************************************************************************
 *   Copyright (C) 2007 by Lawrence Lee   *
 *   valheru@facticius.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <KDE/KMenuBar>
#include <KDE/KMenu>
#include <KDE/KAction>
#include <KDE/KLocale>
#include <KDE/KDebug>
#include <libmtp.h>
#include "kzen.h"
#include "kzenwidget.h"
#include "kzensplash.h"

KZen::KZen( KZenSplash *splash )
{
    LIBMTP_Init();
    QList<KZenDevice*> *device_list = new QList<KZenDevice*>();
    LIBMTP_error_number_t error = checkDevices( splash, device_list ) ;

    if( error  != LIBMTP_ERROR_NONE ){

        if( error != LIBMTP_ERROR_CONNECTING ){
            m_widget->setEnabled( false );
        }else{

            while( error == LIBMTP_ERROR_CONNECTING ){
                sleep( 1 );
                error = checkDevices( splash, device_list );
            }

        }

    }

    setupActions();
    m_widget = new KZenWidget( this, device_list );
    setCentralWidget( m_widget );
}

KZen::~KZen()
{
    LIBMTP_Release_Device_List( devices );
}

void KZen::setupActions()
{
    actionMenu = new KMenu( i18n( "&Action" ) );
    quit = new KAction( KIcon( "application-exit" ), i18n( "&Quit" ), actionMenu );
    connect(  quit, SIGNAL( triggered() ), this, SLOT( close() ) );
    actionMenu->addAction( quit );
    menuBar()->addMenu( actionMenu );
}

LIBMTP_error_number_t KZen::checkDevices( KZenSplash *splash, QList<KZenDevice*> *device_list )
{
    kDebug() << i18n( "libmtp version: " LIBMTP_VERSION_STRING );
    uint32_t numdevices;

    switch( LIBMTP_Get_Connected_Devices( &devices ) ){
        case LIBMTP_ERROR_NO_DEVICE_ATTACHED:
            kDebug() << i18n( "No Devices have been found." ) << endl;
            return LIBMTP_ERROR_NO_DEVICE_ATTACHED;
        case LIBMTP_ERROR_CONNECTING:
            kDebug() << i18n( "There has been an error connecting. Exiting" ) << endl;
            return LIBMTP_ERROR_CONNECTING;
        case LIBMTP_ERROR_MEMORY_ALLOCATION:
            kDebug() << i18n( "Encountered a Memory Allocation Error. Exiting" ) << endl;
            return LIBMTP_ERROR_MEMORY_ALLOCATION;

            /* Unknown general errors - This should never execute */
        case LIBMTP_ERROR_GENERAL:
        default:
            kDebug() << i18n( "There has been an unknown error, please report this to the libmtp developers." ) << endl;
            return LIBMTP_ERROR_GENERAL;

            /* Successfully connected at least one device, so continue */
        case LIBMTP_ERROR_NONE:
            numdevices = LIBMTP_Number_Devices_In_List( devices );
            kDebug() << i18n( "Successfully connected %1 %2", numdevices, numdevices > 1 ? i18n( "devices" ) : i18n( "device" ) ) << endl;
            splash->showMessage( i18n( "Successfully connected %1 %2", numdevices, numdevices > 1 ? i18n( "devices" ) : i18n( "device" ) ) );
    }

    LIBMTP_mtpdevice_t *iter;
    for( iter = devices; iter != NULL; iter = iter->next ){
        device_list->append( new KZenDevice( iter ) );
    }

    return LIBMTP_ERROR_NONE;
}

#include "kzen.moc"
