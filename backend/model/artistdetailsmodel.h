#ifndef ARTISTDETAILSMODEL_H
#define ARTISTDETAILSMODEL_H

#include <QAbstractListModel>

#include "common.h"

namespace backend
{
    namespace model
    {
        class ArtistDetailsModel: public QAbstractListModel
        {
             Q_OBJECT

            enum Roles
            {
                Title = Qt::UserRole + 1,
                Artist,
                Album
            };

        public:
            explicit ArtistDetailsModel(QObject *parent = 0);

        public: // reimplemented
            virtual int rowCount(const QModelIndex &parent) const;
            virtual QVariant data(const QModelIndex &index, int role) const;
            virtual QHash<int, QByteArray> roleNames() const;

            Q_INVOKABLE void loadDetails(QVariant artist);

            Q_INVOKABLE QString artistName() const;
            Q_INVOKABLE QString summary() const;

        private slots:
            void loadAlbums();

        private:
            AlbumList mAlbums;
            structure::Artist *mArtist;
            bool mAlbumsReady;
        };
    }
}

#endif // ARTISTDETAILSMODEL_H
