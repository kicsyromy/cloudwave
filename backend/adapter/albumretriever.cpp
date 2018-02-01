#include "albumretriever.h"

#include <QDomDocument>
#include <QDomElement>
#include <QThread>

#include "logger.h"

using namespace backend;
using namespace backend::adapter;
using namespace backend::network;
using namespace backend::structure;

AlbumRetriever &AlbumRetriever::instance()
{
    static AlbumRetriever ar;
    return ar;
}

AlbumRetriever::AlbumRetriever() :
    QObject(0),
    mPc(),
    mAlbums()
{
    connect(&mPc, &PlexConnection::dataReady, this, &AlbumRetriever::onDataReady);
}

AlbumRetriever::~AlbumRetriever()
{
    qDeleteAll(mAlbums);
    mAlbums.clear();
}

AlbumList AlbumRetriever::albums()
{
    return mAlbums;
}

Album *AlbumRetriever::album(const QString &name)
{
    Album *album = 0;

    foreach (Album *a, mAlbums)
    {
        if (a->title() == name)
        {
            album = a;
            break;
        }
    }

    return album;
}

void AlbumRetriever::refresh()
{
    qDeleteAll(mAlbums);
    mAlbums.clear();

    mPc.get("/library/sections/3/albums");
}

void AlbumRetriever::onDataReady(RequestId id, const QByteArray &data,
                                      PlexConnection::RequestStatus status,
                                      const QString &errorString)
{
    if (status == PlexConnection::NoError)
    {
        QDomDocument doc;
        doc.setContent(data);
        QDomNodeList nodes = doc.elementsByTagName("Directory");

        int nodeCount = nodes.count();

        QDomElement domElement;

        for (int i = 0; i < nodeCount; ++i)
        {
            domElement = nodes.at(i).toElement();

            mAlbums.append(new Album(
                               domElement.attribute("title"),
                               domElement.attribute("parentTitle"),
                               domElement.childNodes().at(0).toElement().attribute("tag"),
                               domElement.attribute("leafCount").toInt(),
                               PlexConnection::hostname + domElement.attribute("thumb"),
                               domElement.attribute("key")
                               ));
        }
    }
    else
    {
        LOG_ERROR << "Failed to retrieve data for" << id << "status:" << status << "error:" << errorString;
    }

    emit albumsReady(errorString);
}

