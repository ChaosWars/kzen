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
#include "kzenplaylist.h"
#include "kzentrack.h"

KZenPlaylist::KZenPlaylist( LIBMTP_playlist_t *playlist, const QList<KZenTrack*> &tracks )
 : m_playlist( playlist ), m_tracks( tracks )
{
    for( int i = 0; i < m_tracks.size(); i++ ){
        m_tracks.at( i )->setParent( this );
    }
}

KZenPlaylist::~KZenPlaylist()
{
    LIBMTP_destroy_playlist_t( m_playlist );
}


