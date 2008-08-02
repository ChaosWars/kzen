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
#include <KDE/KUniqueApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>
#include <KDE/KIconLoader>
#include <KDE/KDebug>
#include "kzen.h"
#include "kzensplash.h"

static const char description[] = "Manage your Creative Zen";

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE( kzen );
    KCmdLineOptions options;
//     options.add( "+someoption", ki18n( "Some option" ) );
    KAboutData about( "kzen", QByteArray(), ki18n( "KZen" ), version, ki18n( description ),
                      KAboutData::License_GPL, ki18n( "Copyright (c) 2007-2008 Lawrence Lee" ),
                      ki18n("A program for managing portable media players that use the MTP protocol"),
                      "http://kzen.googlecode.com", "http://code.google.com/p/knewz/issues/list" );
    about.addAuthor( ki18n( "Lawrence Lee" ), ki18n( "Lead programmer" ), "valheru.ashen.shugar@gmail.com", "http://kzen.googlecode.com" );
    KCmdLineArgs::init( argc, argv, &about );
    KCmdLineArgs::addCmdLineOptions( options );
    KUniqueApplication::addCmdLineOptions();

    if ( !KUniqueApplication::start() ){
        kDebug() << i18n( "KZen is already running!" ) << endl;
        exit( 0 );
    }

    KUniqueApplication app;
    app.setQuitOnLastWindowClosed( false );
    KZenSplash *splash = new KZenSplash( QPixmap( ":/pics/kzen_splash.png" ) );
    KZen *kzenmw = new KZen( splash );
    if( app.isSessionRestored() )
    {
        RESTORE(KZen(splash));
    }else{
        kzenmw->show();
        splash->finish( kzenmw );
        delete splash;
    }
    return app.exec();
}
