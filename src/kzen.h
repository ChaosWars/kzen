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
#ifndef KZEN_H
#define KZEN_H

#include <KDE/KMainWindow>
#include <libmtp.h>
#include "kzendevice.h"

class KMenu;
class KAction;
class KSystemTrayIcon;
class KZenDevice;
class KZenWidget;
class KZenSplash;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZen : public KMainWindow
{
    Q_OBJECT

    public:
        KZen( KZenSplash *splash );
        ~KZen();

    protected:
        bool queryClose();
        bool queryExit();

    private:
        bool ok_to_close;
        KZenSplash *m_splash;
        KZenWidget *m_widget;
        KMenu *actionMenu;
        KAction *quit;
        LIBMTP_mtpdevice_t *devices;
        KSystemTrayIcon *trayIcon;
        QList<KZenDevice*> deviceList;
        void setupActions();
        void setupMenus();
        LIBMTP_error_number_t checkDevices( KZenSplash *splash );

    private Q_SLOTS:
        void message( const QString& );
        void exit();
};

#endif
