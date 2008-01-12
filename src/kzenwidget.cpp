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
#include <QLayout>
#include <QSplitter>
#include <QPixmap>
#include <KDE/KMultiTabBar>
#include <KDE/KIconLoader>
#include <KDE/KComboBox>
#include <KDE/KDebug>
#include "kzenwidget.h"
#include "kzennavview.h"
#include "kzenalbumviewmodel.h"
#include "kzendevice.h"
#include "kzendevicethread.h"
#include "kzenalbum.h"

KZenWidget::KZenWidget( QWidget *parent, QList<KZenDevice*> *devices )
    : QWidget( parent ), mtp_devices( devices ), albumsDirty( false )
{
    qRegisterMetaType< QList<KZenAlbum*> >( "QList<KZenAlbum*>" );

    for( int i = 0; i < mtp_devices->size(); i++ ){
        connect( mtp_devices->at( i )->deviceThread(), SIGNAL( albums( const QList<KZenAlbum*>& ) ), this, SLOT( listAlbums( const QList<KZenAlbum*>& ) ) );
    }

    //Main layout
    QVBoxLayout *mainVLayout = new QVBoxLayout( this );
    QHBoxLayout *mainHLayout = new QHBoxLayout();

    //Device combo box
    m_devices = new KComboBox( mainVLayout );

    for( int i = 0; i < mtp_devices->size(); i++ ){
        m_devices->insertItem( i, mtp_devices->at( i )->name() );
    }

    //Navigation panel
    navpanel = new KMultiTabBar( KMultiTabBar::Left, this );
    navpanel->setStyle( KMultiTabBar::VSNET );

    //Music tab
    QPixmap musicPixmap( KIconLoader::global()->loadIcon( "multimedia", KIconLoader::NoGroup ) );
    navpanel->appendTab( albumPixmap, KZenWidget::AlbumTab, "Albums" );
    albumTab = navpanel->tab( KZenWidget::AlbumTab );
    connect( albumTab, SIGNAL( toggled( bool ) ), this, SLOT( albumTabToggled( bool ) ) );

    //Video tab
    QPixmap playlistPixmap( KIconLoader::global()->loadIcon( "multimedia", KIconLoader::NoGroup ) );
    navpanel->appendTab( playlistPixmap, KZenWidget::PlaylistTab, "Playlists" );
    playlistTab = navpanel->tab( KZenWidget::PlaylistTab );
    connect( playlistTab, SIGNAL( toggled( bool ) ), this, SLOT( playlistTabToggled( bool ) ) );

    //Photo tab
    QPixmap videoPixmap( KIconLoader::global()->loadIcon( "multimedia", KIconLoader::NoGroup ) );
    navpanel->appendTab( videoPixmap, KZenWidget::VideoTab, "Videos" );
    videoTab = navpanel->tab( KZenWidget::VideoTab );
    connect( videoTab, SIGNAL( toggled( bool ) ), this, SLOT( videoTabToggled( bool ) ) );

    //Main splitter
    QSplitter *splitter = new QSplitter( this );
    navView = new KZenNavView( splitter );
    navView->hide();
    mainView = new KZenNavView( splitter );

    //Set the layout
    mainHLayout->addWidget( navpanel );
    mainHLayout->addWidget( splitter );
    mainVLayout->addWidget( m_devices );
    mainVLayout->addLayout( mainHLayout );
    setLayout( mainVLayout );
}


KZenWidget::~KZenWidget()
{
}

void KZenWidget::musicTabToggled( bool on )
{
    if( on ){
        navView->show();

        if( mtp_devices->size() > 0 ){
            int device = m_devices->currentIndex();

            if( device >= 0 )
                mtp_devices->value( device )->getAlbums();

        }

    }else{
        navView->hide();
    }
}

void KZenWidget::videoTabToggled( bool on )
{
}

void KZenWidget::photoTabToggled( bool on )
{
}

void KZenWidget::listAlbums( const QList<KZenAlbum*> &a )
{
    if( !navView->model() || albumsDirty ){
        KZenAlbumViewModel *model = static_cast<KZenAlbumViewModel*>( navView->model() );
        navView->setModel( new KZenAlbumViewModel( navView, a ) );
        delete model;
    }
}

#include "kzenwidget.moc"
