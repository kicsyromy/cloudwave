#ifndef ASYNCTRACKRETRIEVER_H
#define ASYNCTRACKRETRIEVER_H

#include <QObject>
#include <QSet>

#include "plexconnection.h"
#include "common.h"

namespace backend
{
    namespace adapter
    {
        class TrackRetriever: public QObject
        {
            Q_OBJECT

        public:
            static TrackRetriever &instance();

        public:
            TrackList tracks();
            void refresh();

        signals:
            void tracksReady(const QString errorString);

        private slots:
            void onDataReady(RequestId id, const QByteArray &data,
                             network::PlexConnection::RequestStatus status,
                             const QString &errorString);

        private:
            network::PlexConnection mPc;
            TrackList mTracks;
            QSet<RequestId> mRequests;

        private:
            TrackRetriever();
            ~TrackRetriever();
            Q_DISABLE_COPY(TrackRetriever)
        };
    }
}

#endif // TRACKRETRIEVER_H
