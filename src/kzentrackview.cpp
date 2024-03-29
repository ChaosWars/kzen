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
#include "kzentrackview.h"
#include "kzentrackviewmodel.h"
#include "kzentrack.h"
#include "devices.h"

KZenTrackView::KZenTrackView( QWidget *parent )
    : QTreeView( parent ), tracksDirty( false )
{
    qRegisterMetaType< QList<KZenTrack*> >( "QList<KZenTrack*>" );
    setRootIsDecorated( false );

    if( Devices::devices().size() > 0 )
        setModel( new KZenTrackViewModel( this , Devices::devices().first()->tracks() ) );
    else
        setModel( new KZenTrackViewModel( this ) );
}

KZenTrackView::~KZenTrackView()
{
}

void KZenTrackView::listTracks( const QList<KZenTrack*> &tracks )
{
    KZenTrackViewModel *oldmodel = static_cast<KZenTrackViewModel*>( model() );
    setModel( new KZenTrackViewModel( this, tracks ) );
    delete oldmodel;
}

#include "kzentrackview.moc"
