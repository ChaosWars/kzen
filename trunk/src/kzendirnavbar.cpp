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
#include <KDE/KPushButton>
#include <KDE/KLocale>
#include <KDE/KMenu>
#include <KDE/KAction>
#include <QLayout>
#include <QSpacerItem>
#include "kzendirnavbar.h"

KZenDirNavBar::KZenDirNavBar( QWidget *parent )
 : QWidget(parent)
{
    //Options menu
    optionsMenu = new KMenu( this );
    defaultView = new KAction( "Default", this );
    optionsMenu->addAction( defaultView );
    simpleView = new KAction( "Simple", this );
    optionsMenu->addAction( simpleView );
    detailView = new KAction( "Detailed", this );
    optionsMenu->addAction( detailView );
    separateDirs = new KAction( "Seperate directories", this );
    optionsMenu->addAction( separateDirs );
    previewContents = new KAction( "Preview contents", this );
    optionsMenu->addAction( previewContents );
    previewInfo = new KAction( "Preview info", this );
    optionsMenu->addAction( previewInfo );
    fileViewMax = new KAction( "File view max", this );
    optionsMenu->addAction( fileViewMax );

    mainLayout = new QHBoxLayout( this );
    buttonLayout = new QHBoxLayout();
    m_home = new KPushButton( KIcon( "go-home" ), QString(), this );
    m_home->setToolTip( "Home" );
    buttonLayout->addWidget( m_home );
    m_up = new KPushButton( KIcon( "go-up" ), QString(), this );
    m_up->setToolTip( "Up" );
    buttonLayout->addWidget( m_up );
    m_back = new KPushButton( KIcon( "go-previous" ), QString(), this );
    m_back->setToolTip( "Back" );
    buttonLayout->addWidget( m_back );
    m_forward = new KPushButton( KIcon( "go-next" ), QString(), this );
    m_forward->setToolTip( "Forward" );
    buttonLayout->addWidget( m_forward );
    m_options = new KPushButton( KIcon( "view-choose" ), QString(), this );
    m_options->setMenu( optionsMenu );
    m_forward->setToolTip( "View options" );
    buttonLayout->addWidget( m_options );
    spacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    buttonLayout->addItem( spacer );
    mainLayout->addLayout( buttonLayout );

    //Set up the signals
    connect( m_home, SIGNAL( clicked() ), this, SIGNAL( home() ) );
    connect( m_up, SIGNAL( clicked() ), this, SIGNAL( cdUp() ) );
    connect( m_back, SIGNAL( clicked() ), this, SIGNAL( back() ) );
    connect( m_forward, SIGNAL( clicked() ), this, SIGNAL( forward() ) );
    connect( defaultView, SIGNAL( triggered() ), this, SLOT( defaultViewSlot() ) );
    connect( simpleView, SIGNAL( triggered() ), this, SLOT( simpleViewSlot() ) );
    connect( detailView, SIGNAL( triggered() ), this, SLOT( detailViewSlot() ) );
    connect( separateDirs, SIGNAL( triggered() ), this, SLOT( separateDirsSlot() ) );
    connect( previewContents, SIGNAL( triggered() ), this, SLOT( previewContentsSlot()) );
    connect( previewInfo, SIGNAL( triggered() ), this, SLOT( previewInfoSlot() ) );
    connect( fileViewMax, SIGNAL( triggered() ), this, SLOT( fileViewMaxSlot() ) );
}

KZenDirNavBar::~KZenDirNavBar()
{
}

#include "kzendirnavbar.moc"
