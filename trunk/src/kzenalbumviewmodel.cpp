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
#include <KDE/KDebug>
#include "kzenalbumviewmodel.h"
#include "kzenalbummodelitem.h"
#include "kzenalbum.h"

KZenAlbumViewModel::KZenAlbumViewModel( QObject *parent, const QList<KZenAlbum*> &albums )
 : QAbstractItemModel( parent )
{
    rootItem << "Album" << "Artist" << "Genre" << "Nr. of Tracks";
    setupModelData( albums );
}

KZenAlbumViewModel::~KZenAlbumViewModel()
{
    qDeleteAll( albumsItems );
}

int KZenAlbumViewModel::columnCount( const QModelIndex &parent ) const
{
    kDebug() << parent;
    return 4;
}

QVariant KZenAlbumViewModel::data( const QModelIndex &index, int role ) const
{
    kDebug() << index;
    if( !index.isValid() )
        return QVariant();

    if( role != Qt::DisplayRole )
        return QVariant();

    KZenAlbumModelItem *item = static_cast<KZenAlbumModelItem*>( index.internalPointer() );
    return item->data( index.column() );
}

Qt::ItemFlags KZenAlbumViewModel::flags( const QModelIndex &index ) const
{
    kDebug() << index;
    if( !index.isValid() )
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant KZenAlbumViewModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    kDebug() << section;
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return rootItem.value( section );
    }

    return QVariant();
}

QModelIndex KZenAlbumViewModel::index( int row, int column, const QModelIndex &parent ) const
{
    kDebug() << QString( "%1, %2" ).arg( row ).arg( column ) << parent;

    if( !hasIndex( row, column, parent ) ){
        return QModelIndex();
    }

    if( !parent.isValid() ){ // This is an album, and therefor a top-level item
        kDebug() << "Album";
        KZenAlbumModelItem *album = const_cast<KZenAlbumModelItem*>( albumsItems.at( row ) );
        return createIndex( row, column, album );
    }else{ //This is a track, and has an album as a parent
        kDebug() << "Track";
        //KZenAlbum *parentItem = static_cast<KZenAlbum*>( index.internalPointer() );
    }

    //We should never return from here
    return QModelIndex();
}

QModelIndex KZenAlbumViewModel::parent( const QModelIndex &index ) const
{
    kDebug() << index;

    if( !index.isValid() )
        return QModelIndex();

//     if( parent )
//         return createIndex( index.row(), 0, parent );
//     else
        return QModelIndex();
}

int KZenAlbumViewModel::rowCount( const QModelIndex &parent ) const
{
    kDebug() << parent;
    if( parent.column() > 0 ){
        return 0;
    }else{
        return albumsItems.size();
    }
}

void KZenAlbumViewModel::setupModelData( const QList<KZenAlbum*> &albums )
{
    for( int i = 0; i < albums.size(); i++ ){
        albumsItems.append( new KZenAlbumModelItem( albums.at( i ), &rootItem ) );
    }
}

#include "kzenalbumviewmodel.moc"
