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
#include <QLayout>
#include <QSpacerItem>
#include "kzendirnavbar.h"

KZenDirNavBar::KZenDirNavBar(QWidget *parent)
 : QWidget(parent)
{
    mainLayout = new QHBoxLayout( this );
    buttonLayout = new QHBoxLayout();
    home = new KPushButton( KIcon( "go-home" ), i18n( "Home" ), this );
    buttonLayout->addWidget( home );
    up = new KPushButton( KIcon( "go-up" ), i18n( "Up" ), this );
    buttonLayout->addWidget( up );
    back = new KPushButton( KIcon( "go-previous" ), i18n( "Back" ), this );
    buttonLayout->addWidget( back );
    forward = new KPushButton( KIcon( "go-next" ), i18n( "Forward" ), this );
    buttonLayout->addWidget( forward );
    spacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    buttonLayout->addItem( spacer );
    mainLayout->addLayout( buttonLayout );
}

KZenDirNavBar::~KZenDirNavBar()
{
}

#include "kzendirnavbar.moc"
