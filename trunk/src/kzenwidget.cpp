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
#include <qlayout.h>
#include <qsplitter.h>
#include <klistview.h>
#include <qpixmap.h>
#include <kiconloader.h>
#include "kzenwidget.h"

KZenWidget::KZenWidget(QWidget *parent, const char *name)
 : QWidget(parent, name)
{
    //Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout( this );
    QHBox *n = new QHBox( this );

    //Navigation panel
    navpanel = new KMultiTabBar( KMultiTabBar::Vertical, n, "NavPanel" );
    navpanel->setStyle( KMultiTabBar::VSNET );
    navpanel->setPosition( KMultiTabBar::Left );
    mainLayout->addWidget( navpanel );

    //Album tab
    QPixmap albumPixmap( KGlobal::iconLoader()->loadIcon( "multimedia.png" , KIcon::Toolbar ) );
    navpanel->appendTab( albumPixmap, 0, "Albums" );
    albumTab = navpanel->tab( 0 );
    connect( albumTab, SIGNAL( clicked( int ) ), this, SLOT( albumTabClicked() ) );

    //Main splitter
    QSplitter *splitter = new QSplitter( n );
    albums = new KListView( splitter );
    view = new KListView( splitter );

    //Add layouts
    mainLayout->addWidget( n );
}


KZenWidget::~KZenWidget()
{
}

void KZenWidget::albumTabClicked()
{
    if( albums->isVisible() ){
        albums->hide();
    }else{
        albums->show();
    }
}

#include "kzenwidget.moc"
