#ifndef ALBUMTHUMBPROVIDER_H
#define ALBUMTHUMBPROVIDER_H

#include <QQuickImageProvider>

#include "localimagecache.h"

namespace backend
{
    namespace data
    {
        class AlbumThumbProvider: public QObject, public QQuickImageProvider
        {
            Q_OBJECT

        public:
            AlbumThumbProvider();
            ~AlbumThumbProvider();

        public:
            virtual QImage requestImage(const QString &albumName, QSize *size, const QSize &requestedSize);

        public:
            Q_INVOKABLE bool prepareThumb(QVariant album);

        signals:
            void thumbReady(const QString albumTitle);

        private:
            LocalImageCache mImgCache;
        };
    }
}

#endif // ALBUMTHUMBPROVIDER_H

