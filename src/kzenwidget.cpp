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
#include <KDE/KDirOperator>
#include <KDE/KDebug>
#include <QDir>
#include <QLayout>
#include <QSplitter>
#include <QPixmap>
#include <QTreeView>
#include <QListView>
#include "kzenwidget.h"
#include "kzenmusicwidget.h"
#include "kzenalbumview.h"
#include "kzentrackview.h"
#include "kzenalbumviewmodel.h"
#include "kzentrackviewmodel.h"
#include "kzendevice.h"
#include "kzendevicethread.h"
#include "kzenalbum.h"
#include "kzentrack.h"
#include "devices.h"

KZenWidget::KZenWidget( QWidget *parent )
    : QWidget( parent )
{
    //Main layout
    QVBoxLayout *mainVLayout = new QVBoxLayout( this );
    QHBoxLayout *mainHLayout = new QHBoxLayout();

    //Device combo box
    m_devices = new KComboBox( mainVLayout );

    for( int i = 0; i < Devices::devices().size(); i++ ){
        m_devices->insertItem( i, Devices::devices().at( i )->name() );
    }

    //Navigation panel
    navpanel = new KMultiTabBar( KMultiTabBar::Left, this );
    navpanel->setStyle( KMultiTabBar::KDEV3ICON );

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
    mainView = new KDirOperator( KUrl(), splitter );
    mainView->setView( KFile::Default );

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

#include "kzenwidget.moc"
