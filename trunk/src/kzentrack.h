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
#ifndef KZENTRACK_H
#define KZENTRACK_H

#include <libmtp.h>
#include "kzenobject.h"

class KZenAlbum;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenTrack : public KZenObject
{
    public:

        /**
         *
         * @param parent
         * @param track
         */
        KZenTrack( LIBMTP_track_t *track, KZenAlbum *parent = 0 );

        /**
         *
         */
        ~KZenTrack();

        /**
         *
         * @return
         */
        const uint32_t trackId(){ return m_track->item_id; }

        /**
         *
         * @return
         */
        const uint32_t parentId(){ return m_track->parent_id; }

        /**
         *
         * @return
         */
        const char* title(){ return m_track->title; }

        /**
         *
         * @return
         */
        const char* artist(){ return m_track->artist; }

        /**
         *
         * @return
         */
        const char* genre(){ return m_track->genre; }

        /**
         *
         * @return
         */
        const char* album(){ return m_track->album; }

        /**
         *
         * @return
         */
        const char* date(){ return m_track->date; }

        /**
         *
         * @return
         */
        const char* filename(){ return m_track->filename; }

        /**
         *
         * @return
         */
        uint16_t tracknumber(){ return m_track->tracknumber; }

        /**
         *
         * @return
         */
        uint32_t duration(){ return m_track->duration; }

        /**
         *
         * @return
         */
        uint32_t samplerate(){ return m_track->samplerate; }

        /**
         *
         * @return
         */
        uint16_t numchannels(){ return m_track->nochannels; }

        /**
         *
         * @return
         */
        uint32_t wavecodec(){ return m_track->wavecodec; }

        /**
         *
         * @return
         */
        uint32_t bitrate(){ return m_track->bitrate; }

        /**
         *
         * @return
         */
        uint16_t bitratetype(){ return m_track->bitratetype; }

        /**
         *
         * @return
         */
        uint16_t rating(){ return m_track->rating; }

        /**
         *
         * @return
         */
        uint32_t usecount(){ return m_track->usecount; }

        /**
         *
         * @return
         */
        uint64_t filesize(){ return m_track->filesize; }

        /**
         *
         * @return
         */
        LIBMTP_filetype_t filetype(){ return m_track->filetype; }

        /**
         *
         * @return
         */
        KZenAlbum* parent(){ return m_parent; }

        /**
         *
         * @param parent
         */
        void setParent( KZenAlbum *parent ){ m_parent = parent; }

    private:
        KZenAlbum *m_parent;
        LIBMTP_track_t *m_track;

};

#endif
