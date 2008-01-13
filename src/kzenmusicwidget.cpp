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
#include <QLayout>
#include "kzenmusicwidget.h"
#include "kzenalbumview.h"
#include "kzentrackview.h"
#include "kzenalbum.h"
#include "kzentrack.h"
#include "kzendevice.h"
#include "devices.h"

KZenMusicWidget::KZenMusicWidget( QWidget *parent )
 : QToolBox( parent )
{
    m_albumView = new KZenAlbumView( this );
    m_trackView = new KZenTrackView( this );
    addItem( m_albumView, "Albums" );
    addItem( new QWidget( this ), "Artists" );
    addItem( new QWidget( this ), "Genres" );
    addItem( m_trackView, "All Tracks" );

    //Setup the connections
    for( int i = 0; i < Devices::devices().size(); i++ ){
        KZenDevice *device = Devices::devices().at( i );
        connect( device, SIGNAL( albumList( const QList<KZenAlbum*>& ) ), m_albumView, SLOT( listAlbums( const QList<KZenAlbum*>& ) ) );

        connect( device, SIGNAL( trackList( const QList<KZenTrack*>& ) ), m_trackView, SLOT( listTracks( const QList<KZenTrack*>& ) ) );
    }
}

KZenMusicWidget::~KZenMusicWidget()
{
}

#include "kzenmusicwidget.moc"
