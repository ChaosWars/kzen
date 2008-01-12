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
#include <KDE/KUniqueApplication>
#include <KDE/KMenuBar>
#include <KDE/KStatusBar>
#include <KDE/KMenu>
#include <KDE/KAction>
#include <KDE/KLocale>
#include <KDE/KDebug>
#include <KDE/KSystemTrayIcon>
#include <libmtp.h>
#include "kzen.h"
#include "kzenwidget.h"
#include "kzensplash.h"

KZen::KZen( KZenSplash *splash )
    : ok_to_close( false )
{
    m_splash = splash;
    LIBMTP_Init();
    LIBMTP_error_number_t error = checkDevices( splash ) ;

    if( error  != LIBMTP_ERROR_NONE ){

        while( error == LIBMTP_ERROR_CONNECTING ){
            splash->showMessage( "Error connecting to device, retrying" );
            sleep( 1 );
            error = checkDevices( splash );
        }

    }

    setupActions();
    m_widget = new KZenWidget( deviceList, this );

    if( error != LIBMTP_ERROR_NONE ){
        m_widget->setEnabled( false );
    }

    setCentralWidget( m_widget );
    setAutoSaveSettings();
    trayIcon = new KSystemTrayIcon( "KZen", this );
    trayIcon->show();
}

KZen::~KZen()
{
}

void KZen::setupActions()
{
    actionMenu = new KMenu( i18n( "&Action" ) );
    quit = new KAction( KIcon( "application-exit" ), i18n( "&Quit" ), actionMenu );
    connect(  quit, SIGNAL( triggered() ), this, SLOT( exit() ) );
    actionMenu->addAction( quit );
    menuBar()->addMenu( actionMenu );
    menuBar()->addMenu( helpMenu() );
    statusBar();
}

bool KZen::queryClose()
{
    if( !ok_to_close ){
        hide();
    }

    return ok_to_close;
}

bool KZen::queryExit()
{
    LIBMTP_Release_Device_List( devices );
    return true;
}

LIBMTP_error_number_t KZen::checkDevices( KZenSplash *splash )
{
    kDebug() << i18n( "libmtp version: " LIBMTP_VERSION_STRING );
    uint32_t numdevices;

    switch( LIBMTP_Get_Connected_Devices( &devices ) ){
        case LIBMTP_ERROR_NO_DEVICE_ATTACHED:
            kDebug() << i18n( "No Devices have been found." );
            return LIBMTP_ERROR_NO_DEVICE_ATTACHED;
        case LIBMTP_ERROR_CONNECTING:
            kDebug() << i18n( "There has been an error connecting to the device(s)." );
            return LIBMTP_ERROR_CONNECTING;
        case LIBMTP_ERROR_MEMORY_ALLOCATION:
            kDebug() << i18n( "Encountered a Memory Allocation Error." );
            return LIBMTP_ERROR_MEMORY_ALLOCATION;

        /* Unknown general errors - This should never execute */
        case LIBMTP_ERROR_GENERAL:
        default:
            kDebug() << i18n( "There has been an unknown error, please report this to the libmtp developers." ) << endl;
            return LIBMTP_ERROR_GENERAL;

        /* Successfully connected at least one device, so continue */
        case LIBMTP_ERROR_NONE:
            numdevices = LIBMTP_Number_Devices_In_List( devices );
            splash->showMessage( i18n( "Successfully connected %1 %2", numdevices, numdevices > 1 ? i18n( "devices" ) : i18n( "device" ) ) );
            kDebug() << i18n( "Successfully connected %1 %2", numdevices, numdevices > 1 ? i18n( "devices" ) : i18n( "device" ) );
    }

    LIBMTP_mtpdevice_t *device;
    for( device = devices; device != NULL; device = device->next ){
        deviceList.append( new KZenDevice( device, this ) );
    }

    return LIBMTP_ERROR_NONE;
}

/**
 *
 * @param message
 */
void KZen::message( const QString& m )
{
    if( m_splash )
        m_splash->showMessage( m );
    else
        statusBar()->showMessage( m );
}


void KZen::exit()
{
    ok_to_close = true;
    close();
}

#include "kzen.moc"
