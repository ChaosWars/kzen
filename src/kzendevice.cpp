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
    connect( device_thread, SIGNAL( trackList(const QList< KZenTrack * >&) ), this, SLOT( trackListSlot( const QList<KZenTrack*>& ) ) );
    KZen *m_parent = qobject_cast<KZen*>( parent );

    if( m_parent ){
        connect( this, SIGNAL( message( const QString& ) ), m_parent, SLOT( message( const QString& ) ) );
    }

    if( device ){
        friendlyName = LIBMTP_Get_Friendlyname( device );
        LIBMTP_Get_Storage( device, LIBMTP_STORAGE_SORTBY_NOTSORTED );
        LIBMTP_Get_Batterylevel( device, &maximum_battery_level, &current_battery_level );
        device_thread->getTrackList();
        device_thread->getAlbumList( m_tracks );
        device_thread->getFileList();
        device_thread->getPlaylistList( m_tracks );
    }
}

KZenDevice::~KZenDevice()
{
    delete device_thread;
    m_albums.clear();
    m_files.clear();
    m_playlists.clear();
    m_tracks.clear();

    if( m_device )
        LIBMTP_Release_Device( m_device );
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

void KZenDevice::getTracks()
{
    if( m_device && device_thread->status() == KZenDeviceThread::IDLE )
        device_thread->action( KZenDeviceThread::GET_TRACK_LIST );
}

void KZenDevice::albumListSlot( const QList<KZenAlbum*> &albums )
{
    m_albums.clear();
    m_albums = albums;
    emit albumList( m_albums );
}

void KZenDevice::fileListSlot( const QList<KZenFile*> &files )
{
    m_files.clear();
    m_files = files;
    emit fileList( m_files );
}

void KZenDevice::playlistListSlot( const QList<KZenPlaylist*> &playlists )
{
    m_playlists.clear();
    m_playlists = playlists;
    emit playlistList( m_playlists );
}

void KZenDevice::trackListSlot( const QList<KZenTrack*> &tracks )
{
    m_tracks.clear();
    m_tracks = tracks;
    emit trackList( m_tracks );
}

#include "kzendevice.moc"
