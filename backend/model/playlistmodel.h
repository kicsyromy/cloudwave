#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QThread>

#include "playlist.h"

namespace backend
{
    namespace model
    {
        class PlayListModel: public QAbstractListModel
        {
            Q_OBJECT

            enum Roles
            {
                Title = Qt::UserRole + 1,
                Artist,
                Album
            };

        public:
            explicit PlayListModel(playback::Playlist &pl, QObject *parent = 0);

        public: // reimplemented
            virtual int rowCount(const QModelIndex &parent) const;
            virtual QVariant data(const QModelIndex &index, int role) const;
            virtual QHash<int, QByteArray> roleNames() const;

        private slots:
            void onTracksChanged();

        private:
            playback::Playlist &mPl;
        };
    }
}

#endif // PLAYLISTMODEL_H
