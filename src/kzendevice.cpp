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
#include "kzen.h"
#include "kzendevice.h"
#include "kzendevicethread.h"

KZenDevice::KZenDevice( LIBMTP_mtpdevice_t *device, QObject *parent )
    : QObject( parent ), m_device( device )
{
    device_thread = new KZenDeviceThread( this, device );
    connect( device_thread, SIGNAL( message( const QString& ) ), this, SIGNAL( message( const QString& ) ) );
    connect( device_thread, SIGNAL( albumList( const QList<KZenAlbum*>& ) ), this, SLOT( albumListSlot( const QList<KZenAlbum*>& ) ) );
    connect( device_thread, SIGNAL( fileList( const QList<KZenFile*>& ) ), this, SLOT( fileListSlot( const QList<KZenFile*>& ) ) );
    connect( device_thread, SIGNAL( playlistList( const QList<KZenPlaylist*>& ) ), this, SLOT( playlistListSlot( const QList<KZenPlaylist*>& ) ) );
    KZen *m_parent = qobject_cast<KZen*>( parent );

    if( m_parent ){
        connect( this, SIGNAL( message( const QString& ) ), m_parent, SLOT( message( const QString& ) ) );
    }

    if( device ){
        friendlyName = LIBMTP_Get_Friendlyname( device );
        device_thread->getAlbumList();
        device_thread->getFileList();
        device_thread->getPlaylistList();
    }
}

KZenDevice::~KZenDevice()
{
    delete device_thread;

//     if( m_device )
//         LIBMTP_Release_Device( m_device );
}

void KZenDevice::getAlbums()
{
    if( m_device && device_thread->status() == KZenDeviceThread::IDLE )
        device_thread->action( KZenDeviceThread::GET_ALBUM_LIST );
}

void KZenDevice::getFiles()
{
    if( m_device && device_thread->status() == KZenDeviceThread::IDLE )
        device_thread->action( KZenDeviceThread::GET_FILE_LIST );
}

void KZenDevice::getPlaylists()
{
    if( m_device && device_thread->status() == KZenDeviceThread::IDLE )
        device_thread->action( KZenDeviceThread::GET_PLAYLIST_LIST );
}

void KZenDevice::albumListSlot( const QList<KZenAlbum*> &albums )
{
    qDeleteAll( m_albums );
    m_albums = albums;
}

void KZenDevice::fileListSlot( const QList<KZenFile*> &files )
{
    qDeleteAll( m_files );
    m_files = files;
}

void KZenDevice::playlistListSlot( const QList<KZenPlaylist*> &playlists )
{
    qDeleteAll( m_playlists );
    m_playlists = playlists;
}

#include "kzendevice.moc"
