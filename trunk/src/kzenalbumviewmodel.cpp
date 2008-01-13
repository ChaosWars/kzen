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
#include "kzenalbum.h"
#include "kzentrack.h"

KZenAlbumViewModel::KZenAlbumViewModel( QObject *parent, const QList<KZenAlbum*> &albums )
 : QAbstractItemModel( parent ), albumItems( albums )
{
    rootItem << "Album" << "Artist" << "Genre" << "Nr. of Tracks";
}

KZenAlbumViewModel::~KZenAlbumViewModel()
{
    qDeleteAll( albumItems );
}

int KZenAlbumViewModel::columnCount( const QModelIndex& /*parent*/ ) const
{
    return 4;
}

QVariant KZenAlbumViewModel::data( const QModelIndex &index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    if( role != Qt::DisplayRole )
        return QVariant();

    if( !index.parent().isValid() ){ //Album
        KZenAlbum *album = static_cast<KZenAlbum*>( index.internalPointer() );

        switch( index.column() ){
            case 0:
                return album->name();
            case 1:
                return album->artist();
            case 2:
                return album->genre();
            case 3:
                return album->numTracks();
            default:
                return QVariant();
        }
    }else{ //Track
        KZenTrack *track = static_cast<KZenTrack*>( index.internalPointer() );
        switch( index.column() ){
            case 0:
                return track->title();
            case 1:
                return track->artist();
            case 2:
                return track->genre();
            case 3:
                return track->tracknumber();
            default:
                return QVariant();
        }
    }

    //We should never return from here
    return QVariant();
}

Qt::ItemFlags KZenAlbumViewModel::flags( const QModelIndex &index ) const
{
    if( !index.isValid() )
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant KZenAlbumViewModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return rootItem.value( section );
    }

    return QVariant();
}

QModelIndex KZenAlbumViewModel::index( int row, int column, const QModelIndex &parent ) const
{
    if( !hasIndex( row, column, parent ) ){
        return QModelIndex();
    }

    if( !parent.isValid() ){ // This is an album, and therefor a top-level item
        KZenAlbum *album = const_cast<KZenAlbum*>( albumItems.at( row ) );
        return createIndex( row, column, album );
    }else{ //This is a track, and has an album as a parent
        KZenAlbum *album = static_cast<KZenAlbum*>( parent.internalPointer() );
        KZenTrack *track = album->albumTracks().value( row );
        return createIndex( row, column, track );
    }

    //We should never return from here
    return QModelIndex();
}

QModelIndex KZenAlbumViewModel::parent( const QModelIndex &index ) const
{
    if( !index.isValid() ){
        return QModelIndex();
    }

    QObject *item = static_cast<QObject*>( index.internalPointer() );
    KZenAlbum *album = qobject_cast<KZenAlbum*>( item );

    if( album ){
        return QModelIndex();
    }else{ //Track
        KZenTrack *track = qobject_cast<KZenTrack*>( item );
        KZenAlbum *album = track->parent();
        return createIndex( albumItems.indexOf( album ), 0, album );
    }

    //We should never return from here
    return QModelIndex();
}

int KZenAlbumViewModel::rowCount( const QModelIndex &parent ) const
{
    if( parent.column() > 0 )
        //Out of model bounds
        return 0;

    if( !parent.isValid() )
        //We are in the root of the model
        return albumItems.size();

    //Check to see if this is a track
    QObject *item = static_cast<QObject*>( parent.internalPointer() );
    KZenTrack *track = qobject_cast<KZenTrack*>( item );

    if( track ){ //It's a track
        return 0;
    }else{ //It's an album
        KZenAlbum *album = qobject_cast<KZenAlbum*>( item );

        if( album )
            return album->numTracks();
        else
            return 0;
    }

    //We should never reach this
    return 0;

}

#include "kzenalbumviewmodel.moc"
