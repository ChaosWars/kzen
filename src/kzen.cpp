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

#include <KDE/KActionCollection>
#include <KDE/KApplication>
#include <KDE/KDebug>
#include <KDE/KLocale>
#include <KDE/KStatusBar>
#include <KDE/KSystemTrayIcon>
#include <KDE/KUniqueApplication>
#include <libmtp.h>
#include "kzen.h"
#include "kzenwidget.h"
#include "kzensplash.h"
#include "devices.h"

KZen::KZen( KZenSplash *splash, QWidget *parent )
    : KXmlGuiWindow( parent ), ok_to_close( false )
{
    m_splash = splash;

    if( m_splash ){
        m_splash->show();
        m_splash->showMessage( i18n( "Searching for MTP devices" ) );
    }

    LIBMTP_Init();
    kDebug() << i18n( "libmtp version: " LIBMTP_VERSION_STRING );
    LIBMTP_error_number_t error = checkDevices() ;

    if( error  != LIBMTP_ERROR_NONE ){

        while( error == LIBMTP_ERROR_CONNECTING ){
            message( i18n( "Error connecting to device, retrying" ) );
            sleep( 1 );
            error = checkDevices();
        }

    }

    m_widget = new KZenWidget( this );

    if( error != LIBMTP_ERROR_NONE ){
//         m_widget->setEnabled( false );
    }

    setCentralWidget( m_widget );
    setupActions();
    setupGUI();
    setAutoSaveSettings();
    trayIcon = new KSystemTrayIcon( "kzen", this );
    connect( trayIcon, SIGNAL( quitSelected() ), SLOT( exit() ) );
    trayIcon->show();
}

KZen::~KZen()
{
}

void KZen::setupActions()
{
//     setStandardToolBarMenuEnabled( true );
    createStandardStatusBarAction();
    KStandardAction::quit( this, SLOT( exit() ), actionCollection() );
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
    return true;
}

LIBMTP_error_number_t KZen::checkDevices()
{
    uint32_t numdevices;

    switch( LIBMTP_Get_Connected_Devices( &devices ) ){
        case LIBMTP_ERROR_NO_DEVICE_ATTACHED:
            kDebug() << i18n( "No devices were found." );
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
            message( i18n( "Successfully connected to %1 %2", numdevices, numdevices > 1 ? i18n( "devices" ) : i18n( "device" ) ) );
            kDebug() << i18n( "Successfully connected to %1 %2", numdevices, numdevices > 1 ? i18n( "devices" ) : i18n( "device" ) );
    }

    LIBMTP_mtpdevice_t *device;
    for( device = devices; device != NULL; device = device->next ){
        Devices::addDevice( new KZenDevice( device, this ) );
    }

    return LIBMTP_ERROR_NONE;
}

/**
 *
 * @param message
 */
void KZen::message( const QString& m )
{
    if( m_splash ){
        m_splash->showMessage( m );
        kapp->processEvents();
    }else{
        statusBar()->showMessage( m );
    }
}


void KZen::exit()
{
    ok_to_close = true;
    kapp->setQuitOnLastWindowClosed( true );
    close();
}

#include "kzen.moc"
