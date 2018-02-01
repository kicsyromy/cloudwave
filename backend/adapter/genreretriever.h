#ifndef GENRERETRIEVER_H
#define GENRERETRIEVER_H

#include <QObject>

#include "common.h"
#include "plexconnection.h"

namespace backend
{
    namespace adapter
    {
        class GenreRetriever: public QObject
        {
            Q_OBJECT

        public:
            static GenreRetriever &instance();

        public:
            GenreList genres();
            void refresh();

        signals:
            void genresReady(const QString errorString);

        private slots:
            void onDataReady(RequestId id, const QByteArray &data,
                             network::PlexConnection::RequestStatus status,
                             const QString &errorString);

        private:
            network::PlexConnection mPc;
            GenreList mGenres;

        private:
            GenreRetriever();
            ~GenreRetriever();
            Q_DISABLE_COPY(GenreRetriever)
        };
    }
}

#endif // GENRERETRIEVER_H
