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
#ifndef KZENDIRNAVBAR_H
#define KZENDIRNAVBAR_H

#include <QWidget>
#include <KFile>

class KPushButton;
class KMenu;
class KAction;
class QHBoxLayout;
class QSpacerItem;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenDirNavBar : public QWidget
{
    Q_OBJECT

    public:
        KZenDirNavBar( QWidget *parent = 0 );
        ~KZenDirNavBar();

    private:
        KPushButton *m_home, *m_up, *m_back, *m_forward, *m_options;
        KAction *defaultView, *simpleView, *detailView, *separateDirs, *previewContents, *previewInfo, *fileViewMax;
        KMenu *optionsMenu;
        QHBoxLayout *mainLayout, *buttonLayout;
        QSpacerItem *spacer;

    private Q_SLOTS:
        void defaultViewSlot(){ emit setView( KFile::Default ); }
        void simpleViewSlot(){ emit setView( KFile::Simple ); }
        void detailViewSlot(){ emit setView( KFile::Detail ); }
        void separateDirsSlot(){ emit setView( KFile::SeparateDirs ); }
        void previewContentsSlot(){ emit setView( KFile::PreviewContents ); }
        void previewInfoSlot(){ emit setView( KFile::PreviewInfo ); }
        void fileViewMaxSlot(){ emit setView( KFile::FileViewMax ); }

    Q_SIGNALS:
        void setView( KFile::FileView );
        void home();
        void cdUp();
        void back();
        void forward();
};

#endif
