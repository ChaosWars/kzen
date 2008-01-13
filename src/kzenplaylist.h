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
#ifndef KZENPLAYLIST_H
#define KZENPLAYLIST_H

#include <QObject>
#include "libmtp.h"

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenPlaylist : public QObject
{
    Q_OBJECT

    public:

        /**
         *
         * @param playlist
         * @param parent
         */
        KZenPlaylist( LIBMTP_playlist_t *playlist, QObject *parent = 0 );

        /**
         *
         */
        ~KZenPlaylist();

        /**
         *
         * @return
         */
        uint32_t playlistId(){ return m_playlist->playlist_id; }

        /**
         *
         * @return
         */
        char* name(){ return m_playlist->name; };

        /**
         *
         * @return
         */
        uint32_t* tracks(){ return m_playlist->tracks; };

        /**
         *
         * @return
         */
        uint32_t nrTracks(){ return m_playlist->no_tracks; };

    private:
        LIBMTP_playlist_t *m_playlist;
};

#endif