#include "artistthumbprovider.h"

#include <QDir>

#include "artistretriever.h"
#include "logger.h"

using namespace backend;
using namespace backend::data;
using namespace backend::adapter;
using namespace backend::structure;

ArtistThumbProvider::ArtistThumbProvider() :
    QObject(0),
    QQuickImageProvider(QQuickImageProvider::Image,
                        QQuickImageProvider::ForceAsynchronousImageLoading),
    mImgCache(QDir::homePath() + "/.local/share/CloudWave/artists")
{
    connect(&mImgCache, &LocalImageCache::imageCached, this, &ArtistThumbProvider::thumbReady);
}

ArtistThumbProvider::~ArtistThumbProvider()
{
}

QImage ArtistThumbProvider::requestImage(const QString &artistName, QSize *size, const QSize &requestedSize)
{
    QImage thumb = mImgCache.get(artistName);

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

bool ArtistThumbProvider::prepareThumb(QVariant artist)
{
    Artist *a = qvariant_cast<Artist *>(artist);

    if (!a)
        return true;

    bool cached = mImgCache.find(a->name());

    if (!cached)
    {
        mImgCache.keep(a->thumbnail(), a->name());
    }

    return cached;
}
