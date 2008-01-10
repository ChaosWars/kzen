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
#ifndef KZENDEVICE_H
#define KZENDEVICE_H

#include <QObject>
#include <libmtp.h>

class KZenDeviceThread;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenDevice : public QObject{

    Q_OBJECT

    public:
        KZenDevice( LIBMTP_mtpdevice_t *device );
        ~KZenDevice();
        KZenDeviceThread* deviceThread(){ return device_thread; }
        const char* name(){ return LIBMTP_Get_Friendlyname( m_device ); }

        const int batteryLevel( uint8_t *maximum_level, uint8_t *current_level ){
            return LIBMTP_Get_Batterylevel( m_device, maximum_level, current_level );
        }

        void getAlbums();

    private:
        KZenDeviceThread *device_thread;
        LIBMTP_mtpdevice_t *m_device;

};

#endif
