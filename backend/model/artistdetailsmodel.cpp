#include "artistdetailsmodel.h"

#include "albumretriever.h"

using namespace backend;
using namespace backend::network;
using namespace backend::structure;
using namespace backend::adapter;
using namespace backend::model;

ArtistDetailsModel::ArtistDetailsModel(QObject *parent) :
    QAbstractListModel(parent),
    mAlbums(),
    mArtist(0),
    mAlbumsReady(false)
{
    AlbumRetriever *retriever = &(AlbumRetriever::instance());
    connect(retriever, &AlbumRetriever::albumsReady, this, &ArtistDetailsModel::loadAlbums);
}

int ArtistDetailsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mAlbums.size();
}

QVariant ArtistDetailsModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Title: return mAlbums.at(index.row())->title();
    case Artist: return mAlbums.at(index.row())->artist();
    case Album: return QVariant::fromValue(mAlbums.at(index.row()));
    }

    return QVariant();
}

QHash<int, QByteArray> ArtistDetailsModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[Title] = "title";
    roleNames[Artist] = "artist";
    roleNames[Album] = "album";

    return roleNames;
}

void ArtistDetailsModel::loadDetails(QVariant artist)
{
    mArtist = qvariant_cast<structure::Artist *>(artist);

    if (mAlbumsReady)
    {
        loadAlbums();
    }
}

QString ArtistDetailsModel::artistName() const
{
    QString name;

    if (mArtist)
    {
        name = mArtist->name();
    }

    return name;
}

QString ArtistDetailsModel::summary() const
{
    QString summary;

    if (mArtist)
    {
        summary = mArtist->summary();
    }

    return summary;
}

void ArtistDetailsModel::loadAlbums()
{
    mAlbumsReady = true;

    if (!mArtist) return;

    beginResetModel();

    mAlbums.clear();

    AlbumList albums = AlbumRetriever::instance().albums();

    foreach (structure::Album *album, albums)
    {
        if (album->artist() == mArtist->name())
        {
            mAlbums.append(album);
        }
    }

    endResetModel();
}
