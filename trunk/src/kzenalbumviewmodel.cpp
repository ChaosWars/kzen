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
 : QAbstractItemModel( parent ), m_albums( albums )
{
    rootItem << "Album" << "Artist" << "Genre" << "Nr. of Tracks";
}

KZenAlbumViewModel::~KZenAlbumViewModel()
{
    qDeleteAll( m_albums );
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

    const QModelIndex parentIndex = index.parent();

    if( !parentIndex.isValid() ){
        switch( index.column() ){
            case 0:
                return m_albums.at( index.row() )->name();
            case 1:
                return m_albums.at( index.row() )->artist();
            case 2:
                return m_albums.at( index.row() )->genre();
            case 3:
                return m_albums.at( index.row() )->numTracks();
            default:
                return QVariant();
        }
    }
    else{
        switch( index.column() ){
            case 0:
                return m_albums.at( parentIndex.row() )->albumTracks().at( index.row() )->title();
            case 1:
                return m_albums.at( parentIndex.row() )->albumTracks().at( index.row() )->artist();
            case 2:
                return m_albums.at( parentIndex.row() )->albumTracks().at( index.row() )->genre();
            case 3:
                return m_albums.at( parentIndex.row() )->albumTracks().at( index.row() )->tracknumber();
            default:
                return QVariant();
        }
    }
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
    if( !hasIndex( row, column, parent ) )
        return QModelIndex();

    if( !parent.isValid() )
        return createIndex( row, column, m_albums.at( row ) );

    KZenObject *object = static_cast<KZenObject*>( parent.internalPointer() );
    KZenAlbum *album = dynamic_cast<KZenAlbum*>( object );

    if( !album )
        return QModelIndex();

    KZenTrack *track = album->albumTracks().at( row );

    if( !track )
        return QModelIndex();

    return createIndex( row, column, track );

}

QModelIndex KZenAlbumViewModel::parent( const QModelIndex &index ) const
{
    if( !index.isValid() )
        return QModelIndex();

    KZenObject *object = static_cast<KZenObject*>( index.internalPointer() );
    KZenTrack *track = dynamic_cast<KZenTrack*>( object );

    if( !track )
        return QModelIndex();

    KZenAlbum *album = dynamic_cast<KZenAlbum*>( track->parent() );

    if( !album )
        return QModelIndex();

    return createIndex( m_albums.indexOf( album ), 0, album );
}

int KZenAlbumViewModel::rowCount( const QModelIndex &parent ) const
{
    if( parent.column() > 3 )
        //Out of KZenAlbumViewModel bounds
        return 0;

    if( !parent.isValid() )
        return m_albums.size();

    if( !parent.parent().isValid() )
        return m_albums.at( parent.row() )->numTracks();

    return 0;
}

#include "kzenalbumviewmodel.moc"
