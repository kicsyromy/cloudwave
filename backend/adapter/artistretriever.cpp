#include "artistretriever.h"

#include <QDomDocument>
#include <QDomElement>

#include "logger.h"

using namespace backend;
using namespace backend::adapter;
using namespace backend::network;
using namespace backend::structure;

ArtistRetriever &ArtistRetriever::instance()
{
    static ArtistRetriever ar;
    return ar;
}

ArtistRetriever::ArtistRetriever() :
    QObject(0),
    mPc(),
    mArtists()
{
    connect(&mPc, &PlexConnection::dataReady, this, &ArtistRetriever::onDataReady);
}

ArtistRetriever::~ArtistRetriever()
{
    qDeleteAll(mArtists);
    mArtists.clear();
}

ArtistList ArtistRetriever::artists()
{
    return mArtists;
}

void ArtistRetriever::refresh()
{
    qDeleteAll(mArtists);
    mArtists.clear();

    mPc.get("/library/sections/3/all");
}

void ArtistRetriever::onDataReady(RequestId id, const QByteArray &data,
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

            mArtists.append(new Artist(
                               domElement.attribute("title"),
                               PlexConnection::hostname + domElement.attribute("thumb"),
                               domElement.attribute("summary"),
                               domElement.attribute("key")
                               ));
        }
    }
    else
    {
        LOG_ERROR << "Failed to retrieve data for" << id << "status:" << status << "error:" << errorString;
    }

    emit artistsReady(errorString);
}

