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
#ifndef KZENFILE_H
#define KZENFILE_H

#include <QObject>
#include "libmtp.h"

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenFile : public QObject
{
    Q_OBJECT

    public:
        KZenFile( LIBMTP_file_t *file, QObject *parent = 0 );
        ~KZenFile();
        uint32_t itemId(){ return m_file->item_id; };
        uint32_t parentId(){ return m_file->parent_id; };
        char* filename(){ return m_file->filename; };
        uint64_t filesize(){ return m_file->filesize; };
        LIBMTP_filetype_t filetype(){ return m_file->filetype; };

    private:
        LIBMTP_file_t *m_file;
};

#endif
