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
#ifndef KZENDEVICETHREAD_H
#define KZENDEVICETHREAD_H

#include <QThread>
#include <QList>
#include <libmtp.h>

class KZenAlbum;
class KZenDevice;
class KZenFile;
class KZenPlaylist;
class KZenTrack;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenDeviceThread : public QThread
{
    Q_OBJECT
    Q_ENUMS( Status )

    public:

        /**
         *
         * @param parent
         * @param device
         */
        KZenDeviceThread( QObject *parent, LIBMTP_mtpdevice_t *device );

        /**
         *
         */
        ~KZenDeviceThread();

        enum Status{ IDLE, GET_ALBUM_LIST, GET_FILE_LIST, GET_PLAYLIST_LIST, GET_TRACK_LIST };

        /**
         *
         * @param status
         */
        void setStatus( Status status ){ m_status = status; };

        /**
         *
         * @param status
         */
        Status status() const{ return m_status; };

        /**
         *
         * @param status
         */
        void action( Status status );

        /**
         *
         */
        void getAlbumList( const QList<KZenTrack*> &files = QList<KZenTrack*>() );

        /**
         *
         */
        void getPlaylistList( const QList<KZenTrack*> &tracks = QList<KZenTrack*>() );

        /**
         *
         */
        void getFileList();

        /**
         *
         */
        void getTrackList();

    protected:

        /**
         *
         */
        void run();

    private:
        KZenDevice *m_parent;
        Status m_status;
        LIBMTP_mtpdevice_t *m_device;

    Q_SIGNALS:

        /**
         *
         * @param message
         */
        void message( const QString &message );

        /**
         *
         * @param albums
         */
        void albumList( const QList<KZenAlbum*> &albums );

        /**
         *
         * @param files
         */
        void fileList( const QList<KZenFile*> &files );

        /**
         *
         * @param playlists
         */
        void playlistList( const QList<KZenPlaylist*> &playlists );

        /**
         *
         * @param tracks
         */
        void trackList( const QList<KZenTrack*> &tracks );
};

#endif
