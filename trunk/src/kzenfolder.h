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
#ifndef KZENFOLDER_H
#define KZENFOLDER_H

#include <QList>
#include <libmtp.h>
#include "kzenobject.h"

class KZenFile;
class KZenFolder;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class KZenFolder : public KZenObject{
    public:
        KZenFolder( LIBMTP_folder_t *folder );
        ~KZenFolder();
        KZenFolder *parent(){ return m_parent; }
        QList<KZenFolder*> children(){ return m_children; }
        QList<KZenFile*> files(){ return m_files; }
        uint32_t folderId(){ return m_folder->folder_id; }
        uint32_t parentId(){ return m_folder->parent_id; }
        char* name(){ return m_folder->name; }

    private:
        KZenFolder *m_parent;
        LIBMTP_folder_t *m_folder;
        QList<KZenFolder*> m_children;
        QList<KZenFile*> m_files;
};

#endif
