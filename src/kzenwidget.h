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
#ifndef KZENWIDGET_H
#define KZENWIDGET_H

#include <QWidget>
#include <KDE/KFile>

class KComboBox;
class KMultiTabBar;
class KMultiTabBarTab;
class QProgressBar;
class QSplitter;
class KZenMusicWidget;
class KZenVideoWidget;
class KZenPhotoWidget;
class KZenDeviceWidget;
class KZenFileTransferWidget;
class KZenDirNavBar;
class KDirOperator;
class KZenAlbum;
class KZenDevice;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenWidget : public QWidget
{
    Q_OBJECT

    public:

        /**
         *
         * @param devices
         * @param parent
         */
        KZenWidget( QWidget *parent = 0 );

        /**
         *
         */
        ~KZenWidget();

        enum{
            MusicTab = 0,
            VideoTab,
            PhotoTab,
            DeviceFileTab
        };

    private:
        KMultiTabBar *navPanel;
        KMultiTabBarTab *musicTab, *videoTab, *photoTab, *deviceTab;
        KZenMusicWidget *musicWidget;
        KZenVideoWidget *videoWidget;
        KZenPhotoWidget *photoWidget;
        KZenDeviceWidget *deviceWidget;
        KZenFileTransferWidget *fileTransferWidget;
        QSplitter *mediaContainerWidget;
        QWidget *dirNavWidget, /* *mediaContainerWidget,*/ *mediaWidget;
        KZenDirNavBar *dirNavBar;
        KDirOperator *mainView;
        KComboBox *m_devices;
        QProgressBar *storageSpace;

    private Q_SLOTS:
        void deviceTabToggled( bool on );
        void musicTabToggled( bool on );
        void videoTabToggled( bool on );
        void photoTabToggled( bool on );
        void setMainView( KFile::FileView );
};

#endif
