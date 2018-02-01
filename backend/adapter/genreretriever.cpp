#include "genreretriever.h"

#include <QDomDocument>
#include <QDomElement>

#include "logger.h"

using namespace backend;
using namespace backend::adapter;
using namespace backend::network;
using namespace backend::structure;

GenreRetriever &GenreRetriever::instance()
{
    static GenreRetriever r;
    return r;
}

GenreRetriever::GenreRetriever() :
    QObject(0),
    mPc(),
    mGenres()
{
    connect(&mPc, &PlexConnection::dataReady, this, &GenreRetriever::onDataReady);
}

GenreRetriever::~GenreRetriever()
{
    mGenres.clear();
}

GenreList GenreRetriever::genres()
{
    return mGenres;
}

void GenreRetriever::refresh()
{
    mGenres.clear();

    mPc.get("/library/sections/3/genre");
}

void GenreRetriever::onDataReady(RequestId id, const QByteArray &data,
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
            mGenres.append(domElement.attribute("title"));
        }
    }
    else
    {
        LOG_ERROR << "Failed to retrieve data for" << id << "status:" << status << "error:" << errorString;
    }

    emit genresReady(errorString);
}
