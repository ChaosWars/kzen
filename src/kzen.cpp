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
#include <kstatusbar.h>
#include <kstdaction.h>
#include <kdebug.h>
#include <libmtp.h>
#include "kzen.h"
#include "kzenwidget.h"
#include "kzensplash.h"

extern KZenSplash *splash;

KZen::KZen( QWidget *parent, const char *name )
 : KMainWindow(parent, name), m_widget( new KZenWidget( this ) )
{
    setCentralWidget( m_widget );
    setupActions();
    statusBar()->show();
    setupGUI();

    if( !checkDevices() ){
        m_widget->setEnabled( false );
    }
}

KZen::~KZen()
{
}

void KZen::setupActions()
{
    KStdAction::quit( this, SLOT( close() ), actionCollection() );
}

bool KZen::checkDevices()
{
    LIBMTP_Init();
    kdDebug( "libmtp version: " LIBMTP_VERSION_STRING );
    LIBMTP_mtpdevice_t *devices, *iter;
    char *friendlyname;
    uint32_t numdevices;

    switch(LIBMTP_Get_Connected_Devices( &devices ) )
    {
        case LIBMTP_ERROR_NO_DEVICE_ATTACHED:
            kdDebug() << "Detect: No Devices have been found." << endl;
            return false;
        case LIBMTP_ERROR_CONNECTING:
            kdDebug() << "Detect: There has been an error connecting. Exiting" << endl;
            return false;
        case LIBMTP_ERROR_MEMORY_ALLOCATION:
            kdDebug() << "Detect: Encountered a Memory Allocation Error. Exiting" << endl;
            return false;

            /* Unknown general errors - This should never execute */
        case LIBMTP_ERROR_GENERAL:
        default:
            kdDebug() << "Detect: There has been an unknown error, please report this to the libmtp developers." << endl;
            return false;

            /* Successfully connected at least one device, so continue */
        case LIBMTP_ERROR_NONE:
            numdevices = LIBMTP_Number_Devices_In_List( devices );
            kdDebug() << "Detect: Successfully connected " << numdevices << " devices." << endl;
            splash->message( QString( "Successfully connected %1 %2" ).arg( numdevices ).arg( numdevices > 1 ? "devices" : "device" ) );
    }

    for( iter = devices; iter != NULL; iter = iter->next ){

        kdDebug() << "MTP-specific device properties:" << endl;
        friendlyname = LIBMTP_Get_Friendlyname( iter );

        if (friendlyname == NULL) {
            kdDebug() << "   Friendly name: (NULL)" << endl;
        } else {
            kdDebug() << "   Friendly name: " << friendlyname << endl;
            free( friendlyname );
        }

    }

    LIBMTP_Release_Device_List( devices );
    return true;
}

#include "kzen.moc"
