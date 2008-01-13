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
#include "kzentrackviewmodel.h"
#include "kzentrack.h"

KZenTrackViewModel::KZenTrackViewModel( QObject *parent, const QList<KZenTrack*> &tracks )
    : QAbstractListModel( parent ), m_tracks( tracks )
{
    rootItem << "Track" << "Album" << "Artist" << "Genre" << "Size";
}

KZenTrackViewModel::~KZenTrackViewModel()
{
    qDeleteAll( m_tracks );
}

int KZenTrackViewModel::columnCount( const QModelIndex& /*parent*/ ) const
{
    return 5;
}

QVariant KZenTrackViewModel::data( const QModelIndex &index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    if( role != Qt::DisplayRole )
        return QVariant();

    switch( index.column() ){
        case 0:
            return m_tracks.at( index.row() )->title();
        case 1:
            return m_tracks.at( index.row() )->artist();
        case 2:
            return m_tracks.at( index.row() )->genre();
        case 3:
            return m_tracks.at( index.row() )->album();
        case 4:
            return m_tracks.at( index.row() )->filesize();
        default:
            return QVariant();
    }

}

QVariant KZenTrackViewModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return rootItem.value( section );
    }

    return QVariant();
}

int KZenTrackViewModel::rowCount( const QModelIndex &parent ) const
{
    if( parent.column() > 4 )
        //Out of KZenTrackViewModel bounds
        return 0;

    if( !parent.isValid() )
        return m_tracks.size();

    return 0;
}

#include "kzentrackviewmodel.moc"
