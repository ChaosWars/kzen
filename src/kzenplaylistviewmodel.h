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
#ifndef KZENPLAYLISTVIEWMODEL_H
#define KZENPLAYLISTVIEWMODEL_H

#include <QAbstractItemModel>
#include <QStringList>

class KZenPlaylist;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenPlaylistViewModel : public QAbstractItemModel
{
    Q_OBJECT

    public:

        /**
         *
         * @param parent
         * @param
         */
        KZenPlaylistViewModel( QObject *parent = 0, const QList<KZenPlaylist*> &playlists = QList<KZenPlaylist*>() );

        /**
         *
         */
        ~KZenPlaylistViewModel();

/**
         *
         * @param index
         * @param role
         * @return
 */
        int columnCount( const QModelIndex &parent = QModelIndex() ) const;

        /**
         *
         * @param index
         * @return
         */
        QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const;

        /**
         *
         * @param section
         * @param orientation
         * @param role
         * @return
         */
        Qt::ItemFlags flags( const QModelIndex &index ) const;

        /**
         *
         * @param section
         * @param orientation
         * @param role
         * @return
         */
        QVariant headerData( int section, Qt::Orientation orientation,
                             int role = Qt::DisplayRole ) const;

        /**
         *
         * @param row
         * @param column
         * @param parent
         * @return
         */
        QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;

        /**
         *
         * @param index
         * @return
         */
        QModelIndex parent( const QModelIndex &index ) const;

        /**
         *
         * @param parent
         * @return
         */
        int rowCount( const QModelIndex &parent = QModelIndex() ) const;

    private:
        QStringList rootItem;
        QList<KZenPlaylist*> m_playlists;
};

#endif
