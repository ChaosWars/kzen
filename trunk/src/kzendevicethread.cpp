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
#include <KDE/KDebug>
#include "kzendevicethread.h"
#include "kzenalbum.h"

KZenDeviceThread::KZenDeviceThread( QObject *parent, LIBMTP_mtpdevice_t *device )
 : QThread( parent ), m_device( device )
{
    m_status = KZenDeviceThread::IDLE;
}


KZenDeviceThread::~KZenDeviceThread()
{
}

void KZenDeviceThread::run()
{
    switch( m_status ){
        case KZenDeviceThread::IDLE:
            break;
        case KZenDeviceThread::GET_ALBUMS:
            getAlbums();
            break;
        default:
            break;
    }

    m_status = KZenDeviceThread::IDLE;
}

void KZenDeviceThread::getAlbums()
{
    LIBMTP_album_t *albumList = LIBMTP_Get_Album_List( m_device );
    LIBMTP_album_t *iter;
    QList<KZenAlbum*> a;

    for( iter = albumList; iter != NULL; iter = iter->next ){
        a.append( new KZenAlbum( iter ) );
    }

    emit albums( a );
}

void KZenDeviceThread::action( Status status )
{
    m_status = status;

    if( !isRunning() )
        start();
}

#include "kzendevicethread.moc"
