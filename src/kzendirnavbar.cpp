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
#include <KDE/KDebug>
#include <QLayout>
#include <QSpacerItem>
#include "kzendirnavbar.h"

KZenDirNavBar::KZenDirNavBar( QWidget *parent )
 : QWidget(parent)
{
    mainLayout = new QHBoxLayout( this );
    buttonLayout = new QHBoxLayout();
    m_home = new KPushButton( KIcon( "user-home" ), QString(), this );
    m_home->setToolTip( i18n( "Home" ) );
    buttonLayout->addWidget( m_home );
    m_up = new KPushButton( KIcon( "go-up" ), QString(), this );
    m_up->setToolTip( i18n( "Up" ) );
    buttonLayout->addWidget( m_up );
    m_back = new KPushButton( KIcon( "go-previous" ), QString(), this );
    m_back->setToolTip( i18n( "Back" ) );
    buttonLayout->addWidget( m_back );
    m_forward = new KPushButton( KIcon( "go-next" ), QString(), this );
    m_forward->setToolTip( i18n( "Forward" ) );
    buttonLayout->addWidget( m_forward );
    m_preview = new KPushButton( KIcon( "view-choose" ), QString(), this );
    m_preview->setCheckable( true );
    m_preview->setToolTip( i18n( "Toggle preview pane" ) );
    buttonLayout->addWidget( m_preview );
    spacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    buttonLayout->addItem( spacer );
    mainLayout->addLayout( buttonLayout );

    //Set up the signals
    connect( m_home, SIGNAL( clicked() ), this, SIGNAL( home() ) );
    connect( m_up, SIGNAL( clicked() ), this, SIGNAL( cdUp() ) );
    connect( m_back, SIGNAL( clicked() ), this, SIGNAL( back() ) );
    connect( m_forward, SIGNAL( clicked() ), this, SIGNAL( forward() ) );
    connect( m_preview, SIGNAL( toggled( bool ) ), this, SLOT( previewToggleSlot( bool ) ) );
}

KZenDirNavBar::~KZenDirNavBar()
{
}

void KZenDirNavBar::previewToggleSlot( bool checked )
{
    kDebug() << checked;
    if( checked )
        emit setView( KFile::PreviewContents );
    else
        emit setView( KFile::FileViewMax );
}

#include "kzendirnavbar.moc"
