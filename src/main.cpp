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
#include <kuniqueapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kdebug.h>
#include "kzen.h"
#include "kzensplash.h"

static const char description[] =
    I18N_NOOP( "A program for managing portable media players that use the MTP protocol" );

static const char version[] = "0.1";

static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
                           KCmdLineLastOption
};

KZenSplash *splash;

int main(int argc, char **argv)
{
    KAboutData about( "kzen", I18N_NOOP("KZen"), version, description,
                      KAboutData::License_GPL, "(C) 2007 Lawrence Lee", 0, "http://kzen.googlecode.com" );
    about.addAuthor( "Lawrence Lee", 0, "valheru@facticius.net" );
    KCmdLineArgs::init( argc, argv, &about );
    KCmdLineArgs::addCmdLineOptions( options );
    KUniqueApplication::addCmdLineOptions();

    if ( !KUniqueApplication::start() ){
        kdDebug() << "KZen is already running!" << endl;
        exit( 0 );
    }

    KUniqueApplication app;
    splash = new KZenSplash( UserIcon( "kzen_splash" ) );
    splash->show();
    splash->message( "Searching for MTP devices" );
    KZen *widget = new KZen();
    widget->show();
    splash->finish( widget );
    delete splash;
    return app.exec();
}
