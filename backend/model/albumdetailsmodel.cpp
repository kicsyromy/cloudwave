#include "albumdetailsmodel.h"

#include "trackretriever.h"

using namespace backend;
using namespace backend::network;
using namespace backend::structure;
using namespace backend::adapter;
using namespace backend::model;

#include "logger.h"

AlbumDetailsModel::AlbumDetailsModel(QObject *parent) :
    QAbstractListModel(parent),
    mTracks(),
    mAlbum(0),
    mTracksReady(false)
{
    TrackRetriever *retriever = &(TrackRetriever::instance());
    connect(retriever, &TrackRetriever::tracksReady, this, &AlbumDetailsModel::loadTracks);
}

int AlbumDetailsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return mTracks.size();
}

QVariant AlbumDetailsModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case SongTitle: return mTracks.at(index.row())->title();
    case SongArtist: return mTracks.at(index.row())->artist();
    case Track: return QVariant::fromValue(mTracks.at(index.row()));
    }

    return QVariant();
}

QHash<int, QByteArray> AlbumDetailsModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[SongTitle] = "songTitle";
    roleNames[SongArtist] = "songArtist";
    roleNames[Track] = "track";

    return roleNames;
}

void AlbumDetailsModel::loadDetails(QVariant album)
{
    mAlbum = qvariant_cast<Album *>(album);

    if (mTracksReady)
    {
        loadTracks();
    }
}

QString AlbumDetailsModel::albumTitle() const
{
    QString title;

    if (mAlbum)
    {
        title = mAlbum->title();
    }

    return title;
}

QString AlbumDetailsModel::artistName() const
{
    QString name;

    if (mAlbum)
    {
        name = mAlbum->artist();
    }

    return name;
}

QString AlbumDetailsModel::genre() const
{
    QString genre;

    if (mAlbum)
    {
        genre = mAlbum->genre();
    }

    return genre;
}

int AlbumDetailsModel::songCount() const
{
    int songCount;

    if (mAlbum)
    {
        songCount = mAlbum->songCount();
    }

    return songCount;
}

QVariant AlbumDetailsModel::tracks() const
{
    return QVariant::fromValue(mTracks);
}

void AlbumDetailsModel::loadTracks()
{
    mTracksReady = true;

    if (!mAlbum) return;

    beginResetModel();

    mTracks.clear();

    TrackList tracks = TrackRetriever::instance().tracks();

    foreach (structure::Track *track, tracks)
    {
        if (track->album() == mAlbum->title() && track->artist() == mAlbum->artist())
        {
            mTracks.append(track);
        }
    }

    endResetModel();
}
