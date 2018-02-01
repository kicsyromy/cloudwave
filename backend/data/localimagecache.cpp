#include "localimagecache.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QRegularExpression>

#include "logger.h"

using namespace backend;
using namespace backend::data;

LocalImageCache::LocalImageCache(const QString &cacheLocation) :
    QObject(0),
    mCacheLocation(cacheLocation),
    mNAManager(new QNetworkAccessManager(this)),
    mCacheIds()
{
    connect(mNAManager, &QNetworkAccessManager::finished, this, &LocalImageCache::dataReady);
}

QImage LocalImageCache::get(const QString &name)
{
    return QImage(mCacheLocation + "/" + cleanSpecialChars(name));
}

void LocalImageCache::keep(const QUrl &image, const QString &name)
{
    QDir dir(mCacheLocation);
    if (!dir.exists())
        dir.mkpath(mCacheLocation);

    QNetworkRequest request;
    request.setUrl(image);

    mCacheIds[mNAManager->get(request)] = name;
}

bool LocalImageCache::find(const QString &name)
{
    return QFile::exists(mCacheLocation + "/" + cleanSpecialChars(name) + ".jpg");
}

void LocalImageCache::dataReady(QNetworkReply *reply)
{
    QString name = mCacheIds.value(reply);
    mCacheIds.remove(reply);

    QImage image = QImage::fromData(reply->readAll());
    image.save(mCacheLocation + "/" + cleanSpecialChars(name) + ".jpg");

    emit imageCached(name);

    reply->deleteLater();
}

QString LocalImageCache::cleanSpecialChars(const QString &string)
{
    QString cleanedUp = string;

    cleanedUp.replace('.', '_');
    cleanedUp.replace('\\', '_');
    cleanedUp.replace('/', '_');
    cleanedUp.replace('&', '_');
    cleanedUp.replace('%', '_');
    cleanedUp.replace('#', '_');
    cleanedUp.replace('@', '_');
    cleanedUp.replace('!', '_');
    cleanedUp.replace('^', '_');
    cleanedUp.replace('*', '_');
    cleanedUp.replace(':', '_');
    cleanedUp.replace('?', '_');

    return cleanedUp;
}
