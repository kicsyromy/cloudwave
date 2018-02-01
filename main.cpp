#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "logger.h"
#include "plexconnection.h"
#include "plexconnection.h"
#include "albumlistmodel.h"
#include "artistlistmodel.h"
#include "genrelistmodel.h"
#include "tracklistmodel.h"
#include "albumdetailsmodel.h"
#include "artistdetailsmodel.h"
#include "playlist.h"
#include "playlistmodel.h"
#include "pageid.h"
#include "artistthumbprovider.h"
#include "albumthumbprovider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    backend::network::PlexConnection::hostname = "http://192.168.0.110:32400";
    backend::network::PlexConnection::hostname = "http://192.168.0.110:32400";

    backend::model::ArtistListModel atm;
    backend::model::AlbumListModel alm;
    backend::model::TrackListModel tm;
    backend::model::GenreListModel gm;
    backend::model::AlbumDetailsModel adm;
    backend::model::ArtistDetailsModel atdm;
    backend::playback::Playlist pl;
    backend::model::PlayListModel pm(pl);
    backend::data::ArtistThumbProvider atp;
    backend::data::AlbumThumbProvider altp;

    QQmlApplicationEngine engine;
    engine.addImageProvider("artistThumbnails", &atp);
    engine.addImageProvider("albumThumbnails", &altp);

    qmlRegisterUncreatableType<backend::playback::NowPlaying>("Playback", 1, 0, "NowPlaying", "");
    qmlRegisterUncreatableType<backend::model::PageId>("Constants", 1, 0, "Page", "");

    engine.rootContext()->setContextProperty("albumListModel", &alm);
    engine.rootContext()->setContextProperty("albumDetailsModel", &adm);
    engine.rootContext()->setContextProperty("artistListModel", &atm);
    engine.rootContext()->setContextProperty("artistDetailsModel", &atdm);
    engine.rootContext()->setContextProperty("genreListModel", &gm);
    engine.rootContext()->setContextProperty("trackListModel", &tm);
    engine.rootContext()->setContextProperty("playListModel", &pm);
    engine.rootContext()->setContextProperty("playlist", &pl);
    engine.rootContext()->setContextProperty("artistThumbProvider", &atp);
    engine.rootContext()->setContextProperty("albumThumbProvider", &altp);
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));

    return app.exec();
}
