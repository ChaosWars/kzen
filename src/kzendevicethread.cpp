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
#include <QHash>
#include <KDE/KDebug>
#include "kzenalbum.h"
#include "kzendevice.h"
#include "kzendevicethread.h"
#include "kzenfile.h"
#include "kzenplaylist.h"
#include "kzentrack.h"

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
        case KZenDeviceThread::GET_TRACK_LIST:
            getTrackList();
            break;
        default:
            break;
    }

    m_status = KZenDeviceThread::IDLE;
}

void KZenDeviceThread::getAlbumList( const QList<KZenTrack*> &tracks )
{
    if( m_device ){
        QList<KZenAlbum*> albums;

        if( tracks.size() == 0 ){
            /* Here we assume that no tracks were passed as an argument,
             * so we query the device for a track list.
             * Of course, it could be that there are no tracks on the device,
             * but in that case this will be a relatively inexpensive operation anyway
             */

            //Process tracks
            emit message( QString( "Getting track list from %1" ).arg( m_parent->name() ) );
            LIBMTP_track_t *tracklisting = LIBMTP_Get_Tracklisting_With_Callback( m_device, NULL, NULL );
            QHash<uint32_t, LIBMTP_track_t*> trackHashList;

            for( LIBMTP_track_t *track = tracklisting; track != NULL; track = track->next ){
                trackHashList.insert( track->item_id, track );
            }

            //Process albums
            emit message( QString( "Getting album list from %1" ).arg( m_parent->name() ) );
            LIBMTP_album_t *album_list = LIBMTP_Get_Album_List( m_device );
            emit message( "Constructing album data" );

            for( LIBMTP_album_t *album = album_list; album != NULL; album = album->next ){
                QList<KZenTrack*> _tracks;
                uint32_t * trackid = album->tracks;

                for( uint32_t i = 0; i < album->no_tracks; i++ ){
                    LIBMTP_track_t *track = trackHashList.value( *(trackid + i) );
                    _tracks.append( new KZenTrack( track ) );
                }

                KZenAlbum *newAlbum = new KZenAlbum( album, _tracks );
                albums.append( newAlbum );
            }
        }else{
        }

        emit albumList( albums );
    }
}

void KZenDeviceThread::getFileList()
{
    if( m_device ){
        QList<KZenFile*> files;
        emit message( QString( "Getting files from %1" ).arg( m_parent->name() ) );
    }
}

void KZenDeviceThread::getPlaylistList()
{
    if( m_device ){
        QList<KZenPlaylist*> playlists;
        emit message( QString( "Getting playlists from %1" ).arg( m_parent->name() ) );
    }
}

void KZenDeviceThread::getTrackList()
{
    if( m_device ){
        QList<KZenTrack*> tracks;
        emit message( QString( "Getting tracks from %1" ).arg( m_parent->name() ) );
        LIBMTP_track_t *tracklisting = LIBMTP_Get_Tracklisting_With_Callback( m_device, NULL, NULL );

        for( LIBMTP_track_t *track = tracklisting; track != NULL; track = track->next ){
            tracks.append( new KZenTrack( track ) );
        }

        emit trackList( tracks );

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
