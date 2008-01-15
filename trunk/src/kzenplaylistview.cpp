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
#include "kzenplaylistview.h"
#include "kzenplaylistviewmodel.h"
#include "kzenplaylist.h"
#include "devices.h"

KZenPlaylistView::KZenPlaylistView( QWidget *parent)
    : QTreeView( parent ), playlistsDirty( false )
{
    qRegisterMetaType< QList<KZenPlaylist*> >( "QList<KZenPlaylist*>" );

    if( Devices::devices().size() > 0 )
        setModel( new KZenPlaylistViewModel( this, Devices::devices().first()->playlists() ) );
    else
        setModel( new KZenPlaylistViewModel( this ) );
}

KZenPlaylistView::~KZenPlaylistView()
{
}

void KZenPlaylistView::listPlaylists( const QList<KZenPlaylist*> &playlists )
{
    KZenPlaylistViewModel *oldmodel = static_cast<KZenPlaylistViewModel*>( model() );
    setModel( new KZenPlaylistViewModel( this, playlists ) );
    delete oldmodel;
}

#include "kzenplaylistview.moc"
