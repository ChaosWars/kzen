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
#include "kzendevice.h"
#include "kzendevicethread.h"
#include "kzenalbum.h"

KZenDeviceThread::KZenDeviceThread( QObject *parent, LIBMTP_mtpdevice_t *device )
 : QThread( parent ), m_device( device )
{
    m_parent = qobject_cast<KZenDevice*>( parent );
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
        case KZenDeviceThread::GET_ALBUM_LIST:
            getAlbumList();
            break;
        case KZenDeviceThread::GET_FILE_LIST:
            getAlbumList();
            break;
        case KZenDeviceThread::GET_PLAYLIST_LIST:
            getPlaylistList();
            break;
        default:
            break;
    }

    m_status = KZenDeviceThread::IDLE;
}

void KZenDeviceThread::getAlbumList()
{
    if( m_device ){
        emit message( QString( "Getting album list from %1" ).arg( m_parent->name() ) );
        LIBMTP_album_t *album_list = LIBMTP_Get_Album_List( m_device );
        LIBMTP_album_t *album;
        QList<KZenAlbum*> albums;

        for( album = album_list; album != NULL; album = album->next ){
            albums.append( new KZenAlbum( album ) );
        }

        emit albumList( albums );
    }
}

void KZenDeviceThread::getFileList()
{
    if( m_device ){
        emit message( QString( "Getting file list from %1" ).arg( m_parent->name() ) );
    }
}

void KZenDeviceThread::getPlaylistList()
{
    if( m_device ){
        emit message( QString( "Getting playlist list from %1" ).arg( m_parent->name() ) );
    }
}

void KZenDeviceThread::action( Status status )
{
    if( !isRunning() ){
        m_status = status;
        start();
    }
}

#include "kzendevicethread.moc"
