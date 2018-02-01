#ifndef ARTISTLISTMODEL_H
#define ARTISTLISTMODEL_H

#include <QAbstractListModel>

#include "common.h"

namespace backend
{
    namespace model
    {
        class ArtistListModel : public QAbstractListModel
        {
            Q_OBJECT
            Q_PROPERTY(bool searching READ searching NOTIFY searchingChanged)

            friend class TrackListModel;

            enum Roles
            {
                Name = Qt::UserRole + 1,
                Summary,
                Artist
            };

        public:
            explicit ArtistListModel(QObject *parent = 0);

        public:
            Q_INVOKABLE void search(const QString &term);
            Q_INVOKABLE void refresh();

        public: // reimplemented
            virtual int rowCount(const QModelIndex &parent) const;
            virtual QVariant data(const QModelIndex &index, int role) const;
            virtual QHash<int, QByteArray> roleNames() const;

        public:
            bool searching() const;

        signals:
            void searchingChanged();

        private slots:
            void onArtistsReady();

        private:
            QVariant searchData(int index, int role) const;

        private:
            int mItemCount;
            bool mSearching;
            ArtistList mFoundArtists;
        };
    }
}

#endif // ARTISTLISTMODEL_H
