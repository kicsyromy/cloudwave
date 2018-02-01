#include "trackretriever.h"

#include <QDomDocument>
#include <QDomElement>
#include <QThread>

#include "albumretriever.h"
#include "logger.h"

using namespace backend;
using namespace backend::adapter;
using namespace backend::network;
using namespace backend::structure;

TrackRetriever &TrackRetriever::instance()
{
    static TrackRetriever tr;
    return tr;
}

TrackRetriever::TrackRetriever() :
    QObject(0),
    mPc(),
    mTracks(),
    mRequests()
{
    connect(&mPc, &PlexConnection::dataReady, this, &TrackRetriever::onDataReady);
}

TrackRetriever::~TrackRetriever()
{
}

TrackList TrackRetriever::tracks()
{
    return mTracks;
}

void TrackRetriever::refresh()
{
    qDeleteAll(mTracks);
    mTracks.clear();

    AlbumList albums =  AlbumRetriever::instance().albums();

    foreach (Album *album, albums)
    {
        mRequests << mPc.get(album->key());
    }
}

void TrackRetriever::onDataReady(RequestId id, const QByteArray &data,
                                      PlexConnection::RequestStatus status,
                                      const QString &errorString)
{
    mRequests.remove(id);

    if (status == PlexConnection::NoError)
    {
        QDomDocument doc;
        doc.setContent(data);
        QDomNodeList nodes = doc.elementsByTagName("Track");

        int nodeCount = nodes.count();

        QDomElement domElement;

        for (int i = 0; i < nodeCount; ++i)
        {
            domElement = nodes.at(i).toElement();

            QString title = domElement.attribute("title");

            bool found = false;
            foreach (Track *track, mTracks)
            {
                if (track->title() == title)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
                mTracks.append(new Track(
                           title,
                           domElement.attribute("grandparentTitle"),
                           domElement.attribute("parentTitle"),
                           PlexConnection::hostname + domElement.attribute("parentThumb"),
                           PlexConnection::hostname + domElement.attribute("grandparentThumb"),
                           PlexConnection::hostname + domElement.childNodes().at(0).toElement().childNodes().at(0).toElement().attribute("key")
                           ));
        }
    }
    else
    {
        LOG_ERROR << "Failed to retrieve data for" << id << "status:" << status << "error:" << errorString;
    }

    if (mRequests.empty())
    {
        qSort(mTracks.begin(), mTracks.end(), LessThanPtr<Track>());
        emit tracksReady(errorString);
    }
}
