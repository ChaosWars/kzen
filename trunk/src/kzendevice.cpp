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
#include "kzendevice.h"
#include "kzendevicethread.h"

KZenDevice::KZenDevice( LIBMTP_mtpdevice_t *device )
    : m_device( device )
{
    device_thread = new KZenDeviceThread( this, device );
}

KZenDevice::~KZenDevice()
{
    delete device_thread;
    LIBMTP_Release_Device( m_device );
}

void KZenDevice::getAlbums()
{
    device_thread->action( KZenDeviceThread::GET_ALBUMS );
}

#include "kzendevice.moc"
