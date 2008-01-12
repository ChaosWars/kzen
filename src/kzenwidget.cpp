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
#include <KDE/KMultiTabBar>
#include <KDE/KTabWidget>
#include <KDE/KIconLoader>
#include <KDE/KComboBox>
#include <KDE/KDebug>
#include <QLayout>
#include <QSplitter>
#include <QPixmap>
#include <QTreeWidget>
#include "kzenwidget.h"
#include "kzenmusicwidget.h"
#include "kzenalbumview.h"
#include "kzenalbumviewmodel.h"
#include "kzendevice.h"
#include "kzendevicethread.h"
#include "kzenalbum.h"

KZenWidget::KZenWidget( const QList<KZenDevice*> &devices, QWidget *parent )
    : QWidget( parent ), mtp_devices( devices ), albumsDirty( false )
{
    qRegisterMetaType< QList<KZenAlbum*> >( "QList<KZenAlbum*>" );

    for( int i = 0; i < mtp_devices.size(); i++ ){
        connect( mtp_devices.at( i ), SIGNAL( albumList( const QList<KZenAlbum*>& ) ), this, SLOT( listAlbums( const QList<KZenAlbum*>& ) ) );
    }

    //Main layout
    QVBoxLayout *mainVLayout = new QVBoxLayout( this );
    QHBoxLayout *mainHLayout = new QHBoxLayout();

    //Device combo box
    m_devices = new KComboBox( mainVLayout );

    for( int i = 0; i < mtp_devices.size(); i++ ){
        m_devices->insertItem( i, mtp_devices.at( i )->name() );
    }

    //Navigation panel
    navpanel = new KMultiTabBar( KMultiTabBar::Left, this );
    navpanel->setStyle( KMultiTabBar::VSNET );

    //Music tab
    QPixmap musicPixmap( KIconLoader::global()->loadIcon( "preferences-desktop-sound", KIconLoader::NoGroup ) );
    navpanel->appendTab( musicPixmap, KZenWidget::MusicTab, "Music" );
    musicTab = navpanel->tab( KZenWidget::MusicTab );
    connect( musicTab, SIGNAL( toggled( bool ) ), this, SLOT( musicTabToggled( bool ) ) );

    //Video tab
    QPixmap videoPixmap( KIconLoader::global()->loadIcon( "preferences-desktop-display", KIconLoader::NoGroup ) );
    navpanel->appendTab( videoPixmap, KZenWidget::VideoTab, "Videos" );
    videoTab = navpanel->tab( KZenWidget::VideoTab );
    connect( videoTab, SIGNAL( toggled( bool ) ), this, SLOT( videoTabToggled( bool ) ) );

    //Photo tab
    QPixmap photoPixmap( KIconLoader::global()->loadIcon( "preferences-desktop-wallpaper", KIconLoader::NoGroup ) );
    navpanel->appendTab( photoPixmap, KZenWidget::PhotoTab, "Photos" );
    photoTab = navpanel->tab( KZenWidget::PhotoTab );
    connect( photoTab, SIGNAL( toggled( bool ) ), this, SLOT( photoTabToggled( bool ) ) );

    //Main splitter
    QSplitter *splitter = new QSplitter( this );
    musicWidget = new KZenMusicWidget( splitter );
    musicWidget->hide();
    mainView = new QTreeView( splitter );

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
        navpanel->tab( KZenWidget::PhotoTab )->setState( false );
        navpanel->tab( KZenWidget::VideoTab )->setState( false );
        musicWidget->show();

        if( mtp_devices.size() > 0 ){
            int device = m_devices->currentIndex();

            if( device >= 0 )
                mtp_devices.value( device )->albums();

        }

    }else{
        musicWidget->hide();
    }
}

void KZenWidget::videoTabToggled( bool on )
{
    if( on ){
        navpanel->tab( KZenWidget::MusicTab )->setState( false );
        navpanel->tab( KZenWidget::PhotoTab )->setState( false );
    }else{
    }
}

void KZenWidget::photoTabToggled( bool on )
{
    if( on ){
        navpanel->tab( KZenWidget::MusicTab )->setState( false );
        navpanel->tab( KZenWidget::VideoTab )->setState( false );
    }else{
    }
}

void KZenWidget::listAlbums( const QList<KZenAlbum*> &a )
{
    KZenAlbumView *albumView = musicWidget->albumView();
    if( !albumView->model() || albumsDirty ){
        KZenAlbumViewModel *model = static_cast<KZenAlbumViewModel*>( albumView->model() );
        albumView->setModel( new KZenAlbumViewModel( albumView, a ) );
        delete model;
    }
}

#include "kzenwidget.moc"
