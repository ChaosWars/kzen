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
#ifndef KZENALBUM_H
#define KZENALBUM_H

#include <libmtp.h>
#include "kzenobject.h"

class KZenTrack;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenAlbum : public KZenObject
{
    public:

        /**
         *
         */
        KZenAlbum( LIBMTP_album_t *album, const QList<KZenTrack*> &tracks );

        /**
         *
         * @return
         */
        ~KZenAlbum();

        /**
         *
         * @return
         */
        const uint32_t albumId(){ return m_album->album_id; }

        /**
         *
         * @return
         */
        const char *name(){ return m_album->name; }

        /**
         *
         * @return
         */
        const char *artist(){ return m_album->artist; }

        /**
         *
         * @return
         */
        const char *genre(){ return m_album->genre; }

        /**
         *
         * @return
         */
        const uint32_t* tracks(){ return m_album->tracks; }

        /**
         *
         * @return
         */
        const uint32_t numTracks(){ return m_album->no_tracks; }

        /**
         *
         * @return
         */
        QList<KZenTrack*> albumTracks(){ return m_tracks; }

    private:
        LIBMTP_album_t *m_album;
        QList<KZenTrack*> m_tracks;
};

#endif
