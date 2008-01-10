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
#ifndef KZENALBUMMODELITEM_H
#define KZENALBUMMODELITEM_H

#include <QList>
#include <QStringList>
#include <QVariant>
#include "kzenalbum.h"

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenAlbumModelItem{
    public:
        KZenAlbumModelItem( KZenAlbum *data, KZenAlbumModelItem *parent = 0 );
        ~KZenAlbumModelItem();
        void appendChild( const QString &item );
        QString child( int row );
        int childCount() const;
        int columnCount() const;
        QVariant data( int column ) const;
        int row() const;
        KZenAlbumModelItem* parent();

    private:
        QStringList childItems;
        KZenAlbum *itemData;
        KZenAlbumModelItem *parentItem;

};

#endif
