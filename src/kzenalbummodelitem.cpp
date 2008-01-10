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
#include "kzenalbummodelitem.h"

KZenAlbumModelItem::KZenAlbumModelItem( KZenAlbum *data, KZenAlbumModelItem *parent )
    : itemData( data )
{
    parentItem = parent;
}


KZenAlbumModelItem::~KZenAlbumModelItem()
{
    delete itemData;
}

void KZenAlbumModelItem::appendChild( const QString &item )
{
    childItems.append( item );
}

QString KZenAlbumModelItem::child( int row )
{
    return childItems.value( row );
}

int KZenAlbumModelItem::childCount() const
{
    return childItems.count();
}

int KZenAlbumModelItem::row() const
{
    return 0;
}

int KZenAlbumModelItem::columnCount() const
{
    return 4;
}

QVariant KZenAlbumModelItem::data( int column ) const
{
    switch( column ){
        case 0:
            return itemData->name();
            break;
        case 1:
            return itemData->artist();
            break;
        case 2:
            return itemData->genre();
            break;
        case 3:
            return itemData->numTracks();
            break;
        default:
            return QVariant();
            break;
    }
}

KZenAlbumModelItem* KZenAlbumModelItem::parent()
{
    return parentItem;
}


