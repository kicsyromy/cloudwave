#include "albumlistmodel.h"

#include "albumretriever.h"

#include "logger.h"

using namespace backend;
using namespace backend::network;
using namespace backend::adapter;
using namespace backend::structure;
using namespace backend::model;

AlbumListModel::AlbumListModel(QObject *parent) :
    QAbstractListModel(parent),
    mItemCount(0),
    mSearching(false),
    mFoundAlbums()
{
    AlbumRetriever *retriever = &(AlbumRetriever::instance());
    connect(retriever, &AlbumRetriever::albumsReady, this, &AlbumListModel::onAlbumsReady);
    retriever->refresh();
}

int AlbumListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (mSearching)
        return mFoundAlbums.size();

    return mItemCount;
}

QVariant AlbumListModel::data(const QModelIndex &index, int role) const
{
    if (mSearching)
        return searchData(index.row(), role);

    AlbumList albums = AlbumRetriever::instance().albums();

    switch (role)
    {
    case Title: return albums.at(index.row())->title();
    case Artist: return albums.at(index.row())->artist();
    case Genre: return albums.at(index.row())->genre();
    case SongCount:  return albums.at(index.row())->songCount();
    case Album: return QVariant::fromValue(albums.at(index.row()));
    }

    return QVariant();
}

QHash<int, QByteArray> AlbumListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Title] = "title";
    roles[Artist] = "artist";
    roles[Genre] = "genre";
    roles[SongCount] = "songCount";
    roles[Album] = "album";

    return roles;
}

void AlbumListModel::search(const QString &term)
{
    beginResetModel();

    mFoundAlbums.clear();
    mSearching = true;

    if (!term.isEmpty())
    {
        QStringList terms = term.split(' ', QString::SkipEmptyParts);
        AlbumList albums;
        mFoundAlbums = AlbumRetriever::instance().albums();

        for (QStringList::iterator it = terms.begin(); it != terms.end(); ++it)
        {
            albums = mFoundAlbums;
            mFoundAlbums.clear();

            foreach (structure::Album *album, albums)
            {
                if (album->title().contains(*it, Qt::CaseInsensitive) ||
                    it->contains(album->title(), Qt::CaseInsensitive) ||
                    album->artist().contains(*it, Qt::CaseInsensitive) ||
                    it->contains(album->artist(), Qt::CaseInsensitive)
                   )
                    mFoundAlbums.append(album);
            }
        }
    }
    else
        mSearching = false;

    endResetModel();

    emit searchingChanged();
}

void AlbumListModel::refresh()
{
    beginResetModel();
    mItemCount = 0;
    endResetModel();

    AlbumRetriever::instance().refresh();
}

bool AlbumListModel::searching() const
{
    return mSearching;
}

void AlbumListModel::onAlbumsReady()
{
    beginResetModel();
    mItemCount = AlbumRetriever::instance().albums().size();
    endResetModel();
}

QVariant AlbumListModel::searchData(int index, int role) const
{
    switch (role)
    {
    case Title: return mFoundAlbums.at(index)->title();
    case Artist: return mFoundAlbums.at(index)->artist();
    case SongCount:  return mFoundAlbums.at(index)->songCount();
    case Album: return QVariant::fromValue(mFoundAlbums.at(index));
    }

    return QVariant();
}
