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
#include <QProgressBar>
#include "kzenwidget.h"
#include "kzenmusicwidget.h"
#include "kzenvideowidget.h"
#include "kzenphotowidget.h"
#include "kzendevicewidget.h"
#include "kzenfiletransferwidget.h"
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
    navPanel = new KMultiTabBar( KMultiTabBar::Left, this );
    navPanel->setStyle( KMultiTabBar::KDEV3ICON );

    //Music tab
    QPixmap musicPixmap( KIconLoader::global()->loadIcon( "preferences-desktop-sound", KIconLoader::NoGroup ) );
    navPanel->appendTab( musicPixmap, KZenWidget::MusicTab, "Music" );
    musicTab = navPanel->tab( KZenWidget::MusicTab );
    musicTab->setChecked( true );
    connect( musicTab, SIGNAL( toggled( bool ) ), this, SLOT( musicTabToggled( bool ) ) );

    //Video tab
    QPixmap videoPixmap( KIconLoader::global()->loadIcon( "preferences-desktop-display", KIconLoader::NoGroup ) );
    navPanel->appendTab( videoPixmap, KZenWidget::VideoTab, "Videos" );
    videoTab = navPanel->tab( KZenWidget::VideoTab );
    connect( videoTab, SIGNAL( toggled( bool ) ), this, SLOT( videoTabToggled( bool ) ) );

    //Photo tab
    QPixmap photoPixmap( KIconLoader::global()->loadIcon( "preferences-desktop-wallpaper", KIconLoader::NoGroup ) );
    navPanel->appendTab( photoPixmap, KZenWidget::PhotoTab, "Photos" );
    photoTab = navPanel->tab( KZenWidget::PhotoTab );
    connect( photoTab, SIGNAL( toggled( bool ) ), this, SLOT( photoTabToggled( bool ) ) );

    //File tab
    QPixmap deviceFilePixmap( KIconLoader::global()->loadIcon( "folder-remote", KIconLoader::NoGroup ) );
    navPanel->appendTab( deviceFilePixmap, KZenWidget::DeviceFileTab, "Files on Device" );
    deviceTab = navPanel->tab( KZenWidget::DeviceFileTab );
    connect( deviceTab, SIGNAL( toggled( bool ) ), this, SLOT( deviceTabToggled( bool ) ) );

    //Main splitter
    QSplitter *splitter = new QSplitter( this );

    //Media container widget
    mediaContainerWidget = new QSplitter( Qt::Vertical, splitter );

    //Media widget
    mediaWidget = new QWidget( mediaContainerWidget );
    QHBoxLayout *mediaWidgetLayout = new QHBoxLayout( mediaWidget );
    mediaWidget->setLayout( mediaWidgetLayout );

    //Music widget
    musicWidget = new KZenMusicWidget( mediaWidget );
    mediaWidgetLayout->addWidget( musicWidget );

    //Video Widget
    videoWidget = new KZenVideoWidget( mediaWidget );
    videoWidget->hide();
    mediaWidgetLayout->addWidget( videoWidget );

    //Photo Widget
    photoWidget = new KZenPhotoWidget( mediaWidget );
    photoWidget->hide();
    mediaWidgetLayout->addWidget( photoWidget );

    //Device widget
    deviceWidget = new KZenDeviceWidget( mediaWidget );
    deviceWidget->hide();
    mediaWidgetLayout->addWidget( deviceWidget );

    //File transfer widget
    fileTransferWidget = new KZenFileTransferWidget( mediaWidget );

    //Add the widget to the media container splitter
    mediaContainerWidget->addWidget( mediaWidget );
    mediaContainerWidget->addWidget( fileTransferWidget );


    //Storage space progress bar
//     storageSpace = new QProgressBar( deviceWidget );
//     storageSpace->setMinimum( 0 );
//     quint64 deviceCapacity = Devices::devices().at( 0 )->deviceStorage()->MaxCapacity;;
//     storageSpace->setMaximum( deviceCapacity );
//     quint64 deviceFreeSpace = Devices::devices().at( m_devices->currentIndex() )->deviceStorage()->FreeSpaceInBytes;
//     storageSpace->setValue( (int)( deviceCapacity - deviceFreeSpace ) );

    //Add storage space progress bar to the device widget

    //Navigation widget - contains a navigation toolbar, a view and a spacer
    dirNavWidget = new QWidget( splitter );
    QVBoxLayout *dirNavLayout = new QVBoxLayout( dirNavWidget );
    dirNavBar = new KZenDirNavBar( dirNavWidget );
    QSpacerItem *dirNavSpacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );

    //Main view
    mainView = new KDirOperator( QDir::homePath(), dirNavWidget );
    mainView->setView( KFile::Default );
    QSizePolicy sizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    sizePolicy.setHorizontalStretch( 0 );
    sizePolicy.setVerticalStretch( 0 );
    sizePolicy.setHeightForWidth( mainView->sizePolicy().hasHeightForWidth() );
    mainView->setSizePolicy(sizePolicy);

    //Construct the main views layout
    dirNavLayout->addWidget( dirNavBar );
    dirNavLayout->addWidget( mainView );
    dirNavLayout->addItem( dirNavSpacer );
    dirNavWidget->setLayout( dirNavLayout );

    //Add the widgets to the splitter
    splitter->addWidget( mediaContainerWidget );
    splitter->addWidget( dirNavWidget );

    //Set the layout
    mainHLayout->addWidget( navPanel );
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
        if( mediaContainerWidget->isHidden() )
            mediaContainerWidget->show();

        navPanel->tab( KZenWidget::DeviceFileTab )->setState( false );
        navPanel->tab( KZenWidget::PhotoTab )->setState( false );
        navPanel->tab( KZenWidget::VideoTab )->setState( false );
        musicWidget->show();
    }else{
        if( !navPanel->tab( KZenWidget::DeviceFileTab )->isChecked() &&
            !navPanel->tab( KZenWidget::PhotoTab )->isChecked() &&
            !navPanel->tab( KZenWidget::VideoTab )->isChecked() ){

                mediaContainerWidget->hide();
            }

        musicWidget->hide();
    }
}

void KZenWidget::videoTabToggled( bool on )
{
    if( on ){
        if( mediaContainerWidget->isHidden() )
            mediaContainerWidget->show();

        navPanel->tab( KZenWidget::DeviceFileTab )->setState( false );
        navPanel->tab( KZenWidget::MusicTab )->setState( false );
        navPanel->tab( KZenWidget::PhotoTab )->setState( false );
        videoWidget->show();
    }else{
        if( !navPanel->tab( KZenWidget::DeviceFileTab )->isChecked() &&
            !navPanel->tab( KZenWidget::MusicTab )->isChecked() &&
            !navPanel->tab( KZenWidget::PhotoTab )->isChecked() ){

                mediaContainerWidget->hide();

        }
    }

    videoWidget->hide();
}

void KZenWidget::photoTabToggled( bool on )
{
    if( on ){
        if( mediaContainerWidget->isHidden() )
            mediaContainerWidget->show();

        navPanel->tab( KZenWidget::DeviceFileTab )->setState( false );
        navPanel->tab( KZenWidget::MusicTab )->setState( false );
        navPanel->tab( KZenWidget::VideoTab )->setState( false );
        photoWidget->show();
    }else{
        if( !navPanel->tab( KZenWidget::DeviceFileTab )->isChecked() &&
            !navPanel->tab( KZenWidget::MusicTab )->isChecked() &&
            !navPanel->tab( KZenWidget::VideoTab )->isChecked() ){

                mediaContainerWidget->hide();
        }
    }

    photoWidget->hide();
}

void KZenWidget::deviceTabToggled( bool on )
{
    if( on ){
        if( mediaContainerWidget->isHidden() )
            mediaContainerWidget->show();

        navPanel->tab( KZenWidget::MusicTab )->setState( false );
        navPanel->tab( KZenWidget::PhotoTab )->setState( false );
        navPanel->tab( KZenWidget::VideoTab )->setState( false );
        deviceWidget->show();
    }else{
        if( !navPanel->tab( KZenWidget::MusicTab )->isChecked() &&
            !navPanel->tab( KZenWidget::PhotoTab )->isChecked() &&
            !navPanel->tab( KZenWidget::VideoTab )->isChecked() ){

            mediaContainerWidget->hide();
        }

        deviceWidget->hide();
    }
}

void KZenWidget::setMainView( KFile::FileView view )
{
    mainView->setView( view );
}

#include "kzenwidget.moc"
