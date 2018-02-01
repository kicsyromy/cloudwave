#ifndef ALBUMDETAILSMODEL_H
#define ALBUMDETAILSMODEL_H

#include <QAbstractListModel>

#include "common.h"

namespace backend
{
    namespace model
    {
        class AlbumDetailsModel: public QAbstractListModel
        {
             Q_OBJECT

            enum Roles
            {
                SongTitle = Qt::UserRole + 1,
                SongArtist,
                Track
            };

        public:
            explicit AlbumDetailsModel(QObject *parent = 0);

        public: // reimplemented
            virtual int rowCount(const QModelIndex &parent) const;
            virtual QVariant data(const QModelIndex &index, int role) const;
            virtual QHash<int, QByteArray> roleNames() const;

            Q_INVOKABLE void loadDetails(QVariant album);

            Q_INVOKABLE QString albumTitle() const;
            Q_INVOKABLE QString artistName() const;
            Q_INVOKABLE QString genre() const;
            Q_INVOKABLE int songCount() const;
            Q_INVOKABLE QVariant tracks() const;

        private slots:
            void loadTracks();

        private:
            TrackList mTracks;
            structure::Album *mAlbum;
            bool mTracksReady;
        };
    }
}

#endif // ALBUMDETAILSMODEL_H
