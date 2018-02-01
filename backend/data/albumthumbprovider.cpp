#include "albumthumbprovider.h"

#include <QDir>

#include "albumretriever.h"
#include "logger.h"

using namespace backend;
using namespace backend::data;
using namespace backend::adapter;
using namespace backend::structure;

AlbumThumbProvider::AlbumThumbProvider() :
    QObject(0),
    QQuickImageProvider(QQuickImageProvider::Image,
                        QQuickImageProvider::ForceAsynchronousImageLoading),
    mImgCache(QDir::homePath() + "/.local/share/CloudWave/covers")
{
    connect(&mImgCache, &LocalImageCache::imageCached, this, &AlbumThumbProvider::thumbReady);
}

AlbumThumbProvider::~AlbumThumbProvider()
{
}

QImage AlbumThumbProvider::requestImage(const QString &albumName, QSize *size, const QSize &requestedSize)
{
    QImage thumb = mImgCache.get(albumName);

    if (!thumb.isNull())
    {
        if (requestedSize.width() > 0 && requestedSize.height() > 0)
        {
            thumb = thumb.scaled(requestedSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        }

        if (size)
        {
            size->setWidth(requestedSize.width() > 0 ? requestedSize.width() : thumb.width());
            size->setHeight(requestedSize.height() > 0 ? requestedSize.height() : thumb.height());
        }
    }

    return thumb;
}

bool AlbumThumbProvider::prepareThumb(QVariant album)
{
    Album *a = qvariant_cast<Album *>(album);

    if (!a)
        return true;

    bool cached = mImgCache.find(a->title());

    if (!cached)
    {
        mImgCache.keep(a->artwork(), a->title());
    }

    return cached;
}
