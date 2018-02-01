#ifndef ARTISTTHUMBPROVIDER_H
#define ARTISTTHUMBPROVIDER_H

#include <QQuickImageProvider>

#include "localimagecache.h"

namespace backend
{
    namespace data
    {
        class ArtistThumbProvider: public QObject, public QQuickImageProvider
        {
            Q_OBJECT

        public:
            ArtistThumbProvider();
            ~ArtistThumbProvider();

        public:
            virtual QImage requestImage(const QString &artistName, QSize *size, const QSize &requestedSize);

        public:
            Q_INVOKABLE bool prepareThumb(QVariant artist);

        signals:
            void thumbReady(const QString artistName);

        private:
            LocalImageCache mImgCache;
        };
    }
}

#endif // ARTISTTHUMBPROVIDER_H

