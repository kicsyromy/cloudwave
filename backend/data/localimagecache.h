#ifndef LOCALIMAGECACHE_H
#define LOCALIMAGECACHE_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QPair>
#include <QMap>

class QNetworkAccessManager;
class QNetworkReply;

namespace backend
{
    namespace data
    {
        class LocalImageCache: public QObject
        {
            Q_OBJECT

        public:
            LocalImageCache(const QString &cacheLocation);

        public:
            QImage get(const QString &name);
            void keep(const QUrl &image, const QString &name);
            bool find(const QString &name);

        signals:
            void imageCached(const QString name);

        private slots:
            void dataReady(QNetworkReply *reply);

        private:
            QString cleanSpecialChars(const QString &string);

        private:
            const QString mCacheLocation;
            QNetworkAccessManager *mNAManager;
            QMap<QNetworkReply *, QString> mCacheIds;
        };
    }
}

#endif // LOCALIMAGECACHE_H
