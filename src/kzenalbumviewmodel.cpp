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
 : QAbstractItemModel( parent ), m_albums( albums )
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

    if( index.parent() == QModelIndex() ){ // This is an album
        KZenAlbum* album = static_cast<KZenAlbum*>( index.internalPointer() );

        switch( index.column() ){
            case 0:
                return m_albums.value( index.row() )->name();
                break;
            case 1:
                return m_albums.value( index.row() )->artist();
                break;
            case 2:
                return m_albums.value( index.row() )->genre();
                break;
            case 3:
                return m_albums.value( index.row() )->numTracks();
                break;
            default:
                return QVariant();
                break;
        }

    }else{ //This is a track on an album

    }

    //We should never return from here
    return QVariant();
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
    if( !parent.isValid() ){ //This is an album
        KZenAlbum *album = m_albums.value( row );

        if( album )
            return createIndex( row, column, album );
        else
            return QModelIndex();

    }

    //Parent is valid, so we are dealing with a track

    //We should never return from here
    return QModelIndex();

}

QModelIndex KZenAlbumViewModel::parent( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return QModelIndex();

    if( index == QModelIndex() ) //This is an album
        return QModelIndex();

    //Otherwise this is a track
//     KZenTrack *track = static_cast<KZenTrack*>( index.internalPointer() );
//     KZenAlbumModelItem *parentItem = childItem->parent();
//
//     return createIndex( parentItem->row(), 0, parentItem );
}

int KZenAlbumViewModel::rowCount( const QModelIndex &parent ) const
{
    KZenAlbum * album;

    if ( parent.isValid() )
        album = static_cast<KZenAlbum*>( parent.internalPointer() );
    else
        return m_albums.count();

    return album->albumTracks().size();
}

void KZenAlbumViewModel::setupModelData( const QList<KZenAlbum*> &albums )
{
}

#include "kzenalbumviewmodel.moc"
