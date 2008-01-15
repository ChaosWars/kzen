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
#include "kzenwidget.h"
#include "kzenmusicwidget.h"
#include "kzendirnavbar.h"
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
    splitter->addWidget( musicWidget );
    musicWidget->hide();

    //Navigation widget - contains a navigation toolbar, a view and a spacer
    dirNavWidget = new QWidget( splitter );
    QVBoxLayout *dirNavLayout = new QVBoxLayout( dirNavWidget );

    //Directory navigation bar
    dirNavBar = new KZenDirNavBar( dirNavWidget );

    //Main view
    mainView = new KDirOperator( KUrl(), dirNavWidget );
    mainView->setView( KFile::Default );
    QSizePolicy sizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    sizePolicy.setHorizontalStretch( 0 );
    sizePolicy.setVerticalStretch( 0 );
    sizePolicy.setHeightForWidth( mainView->sizePolicy().hasHeightForWidth() );
    mainView->setSizePolicy(sizePolicy);

    //Spacer
    QSpacerItem *spacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );

    //Add the widgets to the splitter
    dirNavLayout->addWidget( dirNavBar );
    dirNavLayout->addWidget( mainView );
    dirNavLayout->addItem( spacer );
    dirNavWidget->setLayout( dirNavLayout );
    splitter->addWidget( dirNavWidget );

    //Set the layout
    mainHLayout->addWidget( navpanel );
    mainHLayout->addWidget( splitter );
    mainVLayout->addWidget( m_devices );
    mainVLayout->addLayout( mainHLayout );
    setLayout( mainVLayout );

    //Connect the signals of the navbar to the view
    connect( dirNavBar, SIGNAL( home() ), mainView, SLOT( home() ) );
    connect( dirNavBar, SIGNAL( cdUp() ), mainView, SLOT( cdUp() ) );
    connect( dirNavBar, SIGNAL( back() ), mainView, SLOT( back() ) );
    connect( dirNavBar, SIGNAL( forward() ), mainView, SLOT( forward() ) );

    connect( dirNavBar, SIGNAL( setView( KFile::FileView ) ), this, SLOT( setMainView( KFile::FileView ) )  );
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

void KZenWidget::setMainView( KFile::FileView view )
{
    kDebug() << view;
    mainView->setView( view );
}

#include "kzenwidget.moc"
