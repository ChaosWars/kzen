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
#ifndef KZENDEVICETHREAD_H
#define KZENDEVICETHREAD_H

#include <QThread>
#include <QList>
#include <libmtp.h>

class KZenAlbum;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenDeviceThread : public QThread
{
    Q_OBJECT
    Q_ENUMS( Status )

    public:
        KZenDeviceThread( QObject *parent = 0, LIBMTP_mtpdevice_t *device = 0 );
        ~KZenDeviceThread();
        enum Status{ IDLE, GET_ALBUMS };
        void setStatus( Status status ){ m_status = status; };
        Status status() const{ return m_status; };
        void getAlbums();
        void action( Status status );

    protected:
        void run();

    private:
        Status m_status;
        LIBMTP_mtpdevice_t *m_device;

    Q_SIGNALS:
        void albums( const QList<KZenAlbum*> &a );
};

#endif
