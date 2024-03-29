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
#include "kzenalbumview.h"
#include "kzenalbumviewmodel.h"
#include "kzenalbum.h"
#include "devices.h"

KZenAlbumView::KZenAlbumView( QWidget *parent )
    : QTreeView( parent ), albumsDirty( false )
{
    qRegisterMetaType< QList<KZenAlbum*> >( "QList<KZenAlbum*>" );

    if( Devices::devices().size() > 0 )
        setModel( new KZenAlbumViewModel( this, Devices::devices().first()->albums() ) );
    else
        setModel( new KZenAlbumViewModel( this ) );
}

KZenAlbumView::~KZenAlbumView()
{
}

void KZenAlbumView::listAlbums( const QList<KZenAlbum*> &albums )
{
    KZenAlbumViewModel *oldmodel = static_cast<KZenAlbumViewModel*>( model() );
    setModel( new KZenAlbumViewModel( this, albums ) );
    delete oldmodel;
}

#include "kzenalbumview.moc"
