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
#include "kzenalbumviewmodel.h"
#include "kzenalbummodelitem.h"
#include "kzenalbum.h"

KZenAlbumViewModel::KZenAlbumViewModel( QObject *parent, const QList<KZenAlbum*> &albums )
 : QAbstractItemModel( parent )
{
    rootItem << "Album" << "Artist" << "Genre" << "Nr. of Tracks";
}

KZenAlbumViewModel::~KZenAlbumViewModel()
{
}

int KZenAlbumViewModel::columnCount( const QModelIndex &parent ) const
{
    return 4;
}

QVariant KZenAlbumViewModel::data( const QModelIndex &index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    if ( role != Qt::DisplayRole )
        return QVariant();

    KZenAlbumModelItem *item = static_cast<KZenAlbumModelItem*>( index.internalPointer() );
    return item->data( index.column() );
}

Qt::ItemFlags KZenAlbumViewModel::flags( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant KZenAlbumViewModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return rootItem.value( section );

    return QVariant();
}

QModelIndex KZenAlbumViewModel::index( int row, int column, const QModelIndex &parent ) const
{
    KZenAlbumModelItem *parentItem;

    if ( parent.isValid() )
        parentItem = static_cast<KZenAlbumModelItem*>( parent.internalPointer() );

    KZenAlbumModelItem *childItem = children.value( row );

    if ( childItem )
        return createIndex( row, column, childItem );
    else
        return QModelIndex();
}

QModelIndex KZenAlbumViewModel::parent( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return QModelIndex();

    KZenAlbumModelItem *childItem = static_cast<KZenAlbumModelItem*>( index.internalPointer() );
    KZenAlbumModelItem *parentItem = childItem->parent();

    if ( !parentItem )
        return QModelIndex();

    return createIndex( parentItem->row(), 0, parentItem );
}

int KZenAlbumViewModel::rowCount( const QModelIndex &parent ) const
{
    KZenAlbumModelItem * parentItem;

    if ( parent.isValid() )
        parentItem = static_cast<KZenAlbumModelItem*>( parent.internalPointer() );
    else
        return children.count();

    return parentItem->childCount();
}

void KZenAlbumViewModel::setupModelData( const QList<KZenAlbum*> &albums )
{
}

#include "kzenalbumviewmodel.moc"
