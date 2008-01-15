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
#include "kzenplaylistviewmodel.h"
#include "kzenplaylist.h"
#include "kzentrack.h"

KZenPlaylistViewModel::KZenPlaylistViewModel( QObject *parent, const QList<KZenPlaylist*> &playlists )
 : QAbstractItemModel( parent ), m_playlists( playlists )
{
    rootItem << "Playlist" << "Nr. of Tracks";
}

KZenPlaylistViewModel::~KZenPlaylistViewModel()
{
    qDeleteAll( m_playlists );
}

int KZenPlaylistViewModel::columnCount( const QModelIndex& /*parent*/ ) const
{
    return 2;
}

QVariant KZenPlaylistViewModel::data( const QModelIndex &index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    if( role != Qt::DisplayRole )
        return QVariant();

    const QModelIndex parentIndex = index.parent();

    if( !parentIndex.isValid() ){
        switch( index.column() ){
            case 0:
                return m_playlists.at( index.row() )->name();
            case 1:
                return m_playlists.at( index.row() )->numTracks();
            default:
                return QVariant();
        }
    }
    else{
        switch( index.column() ){
            case 0:
                return m_playlists.at( parentIndex.row() )->playlistTracks().at( index.row() )->title();
            case 1:
                return m_playlists.at( parentIndex.row() )->playlistTracks().at( index.row() )->tracknumber();
            default:
                return QVariant();
        }
    }
}

Qt::ItemFlags KZenPlaylistViewModel::flags( const QModelIndex &index ) const
{
    if( !index.isValid() )
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant KZenPlaylistViewModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return rootItem.value( section );
    }

    return QVariant();
}

QModelIndex KZenPlaylistViewModel::index( int row, int column, const QModelIndex &parent ) const
{
    if( !hasIndex( row, column, parent ) )
        return QModelIndex();

    if( !parent.isValid() )
        return createIndex( row, column, m_playlists.at( row ) );

    KZenObject *object = static_cast<KZenObject*>( parent.internalPointer() );
    KZenPlaylist *playlist = dynamic_cast<KZenPlaylist*>( object );

    if( !playlist )
        return QModelIndex();

    KZenTrack *track = playlist->playlistTracks().at( row );

    if( !track )
        return QModelIndex();

    return createIndex( row, column, track );

}

QModelIndex KZenPlaylistViewModel::parent( const QModelIndex &index ) const
{
    if( !index.isValid() )
        return QModelIndex();

    KZenObject *object = static_cast<KZenObject*>( index.internalPointer() );
    KZenTrack *track = dynamic_cast<KZenTrack*>( object );

    if( !track )
        return QModelIndex();

    KZenPlaylist *playlist = dynamic_cast<KZenPlaylist*>( track->parent() );

    if( !playlist )
        return QModelIndex();

    return createIndex( m_playlists.indexOf( playlist ), 0, playlist );
}

int KZenPlaylistViewModel::rowCount( const QModelIndex &parent ) const
{
    if( parent.column() > 1 )
        //Out of KZenPlaylistViewModel bounds
        return 0;

    if( !parent.isValid() )
        return m_playlists.size();

    if( !parent.parent().isValid() )
        return m_playlists.at( parent.row() )->numTracks();

    return 0;
}

#include "kzenplaylistviewmodel.moc"
