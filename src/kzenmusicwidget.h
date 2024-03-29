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
#ifndef KZENMUSICWIDGET_H
#define KZENMUSICWIDGET_H

#include <QToolBox>

class KZenAlbumView;
class KZenTrackView;
class KZenPlaylistView;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenMusicWidget : public QToolBox
{
    Q_OBJECT

    public:

        /**
         *
         * @param parent
         */
        KZenMusicWidget( QWidget *parent = 0 );

        /**
         *
         */
        ~KZenMusicWidget();

        /**
         *
         * @return
         */
        KZenAlbumView* albumView(){ return m_albumView; }

        /**
         *
         * @return
         */
        KZenPlaylistView* playlistView(){ return m_playlistView; }

        /**
         *
         * @return
         */
        KZenTrackView* trackView(){ return m_trackView; }

    private:
        KZenAlbumView *m_albumView;
        KZenPlaylistView *m_playlistView;
        KZenTrackView *m_trackView;

};

#endif
