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

#include <QObject>
#include <libmtp.h>

class KZenAlbum;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenTrack : public QObject
{
    Q_OBJECT

    public:
        KZenTrack( KZenAlbum *parent, LIBMTP_track_t *track = 0 );
        ~KZenTrack();
        const uint32_t trackId(){ return m_track->item_id; }
        const uint32_t parentId(){ return m_track->parent_id; }
        const char* title(){ return m_track->title; }
        const char* artist(){ return m_track->artist; }
        const char* genre(){ return m_track->genre; }
        const char* album(){ return m_track->album; }
        const char* date(){ return m_track->date; }
        const char* filename(){ return m_track->filename; }
        uint16_t tracknumber(){ return m_track->tracknumber; }
        uint32_t duration(){ return m_track->duration; }
        uint32_t samplerate(){ return m_track->samplerate; }
        uint16_t numchannels(){ return m_track->nochannels; }
        uint32_t wavecodec(){ return m_track->wavecodec; }
        uint32_t bitrate(){ return m_track->bitrate; }
        uint16_t bitratetype(){ return m_track->bitratetype; }
        uint16_t rating(){ return m_track->rating; }
        uint32_t usecount(){ return m_track->usecount; }
        uint64_t filesize(){ return m_track->filesize; }
        LIBMTP_filetype_t filetype(){ return m_track->filetype; }
        KZenAlbum *parent(){ return m_parent; }

    private:
        KZenAlbum *m_parent;
        LIBMTP_track_t *m_track;

};

#endif
