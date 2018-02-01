#include "plexconnection.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "logger.h"
#include "common.h"

using namespace backend;
using namespace backend::network;

QString PlexConnection::hostname = "";

PlexConnection::PlexConnection() :
    QObject(0),
    mNAManager(new QNetworkAccessManager(this))
{
    connect(mNAManager, &QNetworkAccessManager::finished, this, &PlexConnection::onRequestFinished);
}

PlexConnection::~PlexConnection()
{
}

RequestId PlexConnection::get(const QString &path)
{
    QNetworkRequest request;
    QString requestString(hostname + path);

    request.setUrl(QUrl(requestString));

    LOG_DEBUG << "Request for" << path << "on host" << hostname;
    QNetworkReply *reply = mNAManager->get(request);
    mRequests << reply;

    return (RequestId)reply;
}

void PlexConnection::onRequestFinished(QNetworkReply *reply)
{
    QByteArray replyData;
    QString errorString;
    RequestId id = (RequestId)reply;
    RequestStatus status = static_cast<RequestStatus>(reply->error());

    if (status == NoError)
    {
        replyData = reply->readAll();
    }
    else
    {
        replyData.clear();
        errorString.append(reply->errorString());
    }

    mRequests.remove(reply);

    emit dataReady(id, replyData, status, errorString);

    reply->deleteLater();
}

