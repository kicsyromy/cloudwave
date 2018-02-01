#ifndef ARTISTRETRIEVER_H
#define ARTISTRETRIEVER_H

#include <QObject>

#include "common.h"
#include "plexconnection.h"

namespace backend
{
    namespace adapter
    {
        class ArtistRetriever: public QObject
        {
            Q_OBJECT

        public:
            static ArtistRetriever &instance();

        public:
            ArtistList artists();
            void refresh();

        signals:
            void artistsReady(const QString errorString);

        private slots:
            void onDataReady(RequestId id, const QByteArray &data,
                             network::PlexConnection::RequestStatus status,
                             const QString &errorString);

        private:
            network::PlexConnection mPc;
            ArtistList mArtists;

        private:
            ArtistRetriever();
            ~ArtistRetriever();
            Q_DISABLE_COPY(ArtistRetriever)
        };
    }
}

#endif // ARTISTRETRIEVER_H
