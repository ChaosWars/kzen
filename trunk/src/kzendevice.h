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
#ifndef KZENDEVICE_H
#define KZENDEVICE_H

#include <QObject>
#include <libmtp.h>

class KZenDeviceThread;
class KZenAlbum;
class KZenFile;
class KZenFolder;
class KZenPlaylist;
class KZenTrack;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenDevice : public QObject{

    Q_OBJECT

    public:
        /**
         *
         * @param device
         * @param parent
         */
        KZenDevice( LIBMTP_mtpdevice_t *device, QObject *parent = 0 );

        /**
         *
         */
        ~KZenDevice();

        /**
         *
         * @return
         */
        const QList<KZenAlbum*>& albums(){ return m_albums; };

        /**
         *
         * @return
         */
        int batteryLevel(){ return static_cast<int>( current_battery_level/maximum_battery_level )*100; };

        /**
         *
         * @return
         */
        LIBMTP_devicestorage_t* deviceStorage(){ return m_device->storage; }

        /**
         *
         * @return
         */
        const QList<KZenFile*>& files(){ return m_files; };

        /**
         *
         * @return
         */
        const char* name(){ return friendlyName; }

        /**
         *
         * @return
         */
        const QList<KZenPlaylist*>& playlists(){ return m_playlists; }

        /**
         *
         * @return
         */
        const QList<KZenTrack*>& tracks(){ return m_tracks; }

        /**
         *
         */
        void getAlbums();

        /**
         *
         */
        void getBatteryLevel();

        /**
         *
         */
        void getFiles();

        /**
         *
         */
        void getFolders();

        /**
         *
         */
        void getPlaylists();

        /**
         *
         */
        void getStorage();

        /**
         *
         */
        void getTracks();

    private:
        KZenDeviceThread *device_thread;
        LIBMTP_mtpdevice_t *m_device;
        QList<KZenAlbum*> m_albums;
        QList<KZenFile*> m_files;
        QList<KZenFolder*> m_folders;
        QList<KZenPlaylist*> m_playlists;
        QList<KZenTrack*> m_tracks;
        char* friendlyName;
        uint8_t maximum_battery_level, current_battery_level;

    private Q_SLOTS:
        void albumListSlot( const QList<KZenAlbum*> &albums );
        void fileListSlot( const QList<KZenFile*> &files );
        void folderListSlot( const QList<KZenFolder*> &folders );
        void playlistListSlot( const QList<KZenPlaylist*> &playlists );
        void trackListSlot( const QList<KZenTrack*> &tracks );

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
         * @param folders
         */
        void folderList( const QList<KZenFolder*> &folders );

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
