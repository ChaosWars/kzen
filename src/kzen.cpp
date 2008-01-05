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
#include <libmtp.h>
#include "kzen.h"
#include "kzenwidget.h"

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
    qDebug( "libmtp version: " LIBMTP_VERSION_STRING );
    LIBMTP_mtpdevice_t *devices, *iter;
    char *friendlyname;
    uint32_t numdevices;

    switch(LIBMTP_Get_Connected_Devices( &devices ) )
    {
        case LIBMTP_ERROR_NO_DEVICE_ATTACHED:
            qDebug( "Detect: No Devices have been found." );
            return false;
        case LIBMTP_ERROR_CONNECTING:
            qDebug( "Detect: There has been an error connecting. Exiting" );
            return false;
        case LIBMTP_ERROR_MEMORY_ALLOCATION:
            qDebug( "Detect: Encountered a Memory Allocation Error. Exiting" );
            return false;

            /* Unknown general errors - This should never execute */
        case LIBMTP_ERROR_GENERAL:
        default:
            qDebug( "Detect: There has been an unknown error, please report this to the libmtp developers.");
            return false;

            /* Successfully connected at least one device, so continue */
        case LIBMTP_ERROR_NONE:
            numdevices = LIBMTP_Number_Devices_In_List( devices );
            qDebug( "Detect: Successfully connected %u devices\n", numdevices );
    }

    for( iter = devices; iter != NULL; iter = iter->next ){

        qDebug( "MTP-specific device properties:" );
        friendlyname = LIBMTP_Get_Friendlyname( iter );

        if (friendlyname == NULL) {
            qDebug( "   Friendly name: (NULL)" );
        } else {
            qDebug( "   Friendly name: %s", friendlyname );
            free( friendlyname );
        }

    }

    LIBMTP_Release_Device_List( devices );
    return true;
}

#include "kzen.moc"
