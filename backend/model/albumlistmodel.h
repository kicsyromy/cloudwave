#ifndef ALBUMLISTMODEL_H
#define ALBUMLISTMODEL_H

#include <QAbstractListModel>
#include <QThread>

#include "common.h"

namespace backend
{
    namespace model
    {
        class AlbumListModel : public QAbstractListModel
        {
            Q_OBJECT
            Q_PROPERTY(bool searching READ searching NOTIFY searchingChanged)

            friend class TrackListModel;

            enum Roles
            {
                Title = Qt::UserRole + 1,
                Artist,
                Genre,
                SongCount,
                Album
            };

        public:
            explicit AlbumListModel(QObject *parent = 0);

        public: // reimplemented
            virtual int rowCount(const QModelIndex &parent) const;
            virtual QVariant data(const QModelIndex &index, int role) const;
            virtual QHash<int, QByteArray> roleNames() const;

        public:
            Q_INVOKABLE void search(const QString &term);
            Q_INVOKABLE void refresh();

        public:
            bool searching() const;

        signals:
            void searchingChanged();

        private slots:
            void onAlbumsReady();

        private:
            QVariant searchData(int index, int role) const;

        private:
            int mItemCount;
            bool mSearching;
            AlbumList mFoundAlbums;
        };
    }
}

#endif // ALBUMLISTMODEL_H
