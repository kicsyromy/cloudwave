#ifndef ALBUMRETRIEVER_H
#define ALBUMRETRIEVER_H

#include <QObject>
#include <QSet>

#include "common.h"
#include "plexconnection.h"

namespace backend
{
    namespace adapter
    {
        class AlbumRetriever: public QObject
        {
            Q_OBJECT

        public:
            static AlbumRetriever &instance();

        public:
            AlbumList albums();
            structure::Album *album(const QString &name);
            void refresh();

        private slots:
            void onDataReady(RequestId id, const QByteArray &data,
                             network::PlexConnection::RequestStatus status,
                             const QString &errorString);

        signals:
            void albumsReady(const QString errorString);

        private:
            network::PlexConnection mPc;
            AlbumList mAlbums;

        private:
            AlbumRetriever();
            ~AlbumRetriever();
            Q_DISABLE_COPY(AlbumRetriever)
        };
    }
}

#endif // ALBUMRETRIEVER_H
