#include "tracklistmodel.h"

#include "trackretriever.h"
#include "albumretriever.h"

#include "logger.h"

using namespace backend;
using namespace backend::network;
using namespace backend::adapter;
using namespace backend::structure;
using namespace backend::model;

TrackListModel::TrackListModel(QObject *parent) :
    QAbstractListModel(parent),
    mItemCount(0),
    mSearching(false),
    mFoundTracks()
{
    AlbumRetriever *albumRetriever = &(AlbumRetriever::instance());
    TrackRetriever *trackRetriever = &(TrackRetriever::instance());
    connect(albumRetriever, &AlbumRetriever::albumsReady, this, &TrackListModel::onAlbumsReady);
    connect(trackRetriever, &TrackRetriever::tracksReady, this, &TrackListModel::onTracksReady);
}

void TrackListModel::search(const QString &term)
{
    beginResetModel();

    mFoundTracks.clear();
    mSearching = true;

    if (!term.isEmpty())
    {
        QStringList terms = term.split(' ', QString::SkipEmptyParts);
        TrackList tracks;
        mFoundTracks = TrackRetriever::instance().tracks();

        for (QStringList::iterator it = terms.begin(); it != terms.end(); ++it)
        {
            tracks = mFoundTracks;
            mFoundTracks.clear();

            foreach (structure::Track *track, tracks)
            {
                if (track->title().contains(*it, Qt::CaseInsensitive) ||
                    it->contains(track->title(), Qt::CaseInsensitive) ||
                    track->artist().contains(*it, Qt::CaseInsensitive) ||
                    it->contains(track->artist(), Qt::CaseInsensitive) ||
                    track->album().contains(*it, Qt::CaseInsensitive) ||
                    it->contains(track->album(), Qt::CaseInsensitive)
                   )
                    mFoundTracks.append(track);
            }
        }
    }
    else
        mSearching = false;

    endResetModel();

    emit searchingChanged();
}

void TrackListModel::refresh()
{
    beginResetModel();
    mItemCount = 0;
    endResetModel();

    // refresh albums first, to make sure they are all avilable
    // before refreshing just the tracks
    AlbumRetriever::instance().refresh();
}

int TrackListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (mSearching)
        return mFoundTracks.size();

    return mItemCount;
}

QVariant TrackListModel::data(const QModelIndex &index, int role) const
{
    if (mSearching)
        return searchData(index.row(), role);

    TrackList tracks = TrackRetriever::instance().tracks();

    switch (role)
    {
    case Title: return tracks.at(index.row())->title();
    case Artist: return tracks.at(index.row())->artist();
    case Album: return tracks.at(index.row())->album();
    case FileUrl: return tracks.at(index.row())->file();
    case Track: return QVariant::fromValue(tracks.at(index.row()));
    }

    return QVariant();
}

QHash<int, QByteArray> TrackListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Title] = "title";
    roles[Artist] = "artist";
    roles[Album] = "album";
    roles[FileUrl] = "fileUrl";
    roles[Track] = "track";

    return roles;
}

bool TrackListModel::searching() const
{
    return mSearching;
}

void TrackListModel::onAlbumsReady()
{
    TrackRetriever::instance().refresh();
}

void TrackListModel::onTracksReady()
{
    beginResetModel();
    mItemCount = TrackRetriever::instance().tracks().size();
    endResetModel();
}

QVariant TrackListModel::searchData(int index, int role) const
{
    switch (role)
    {
    case Title: return mFoundTracks.at(index)->title();
    case Artist: return mFoundTracks.at(index)->artist();
    case Album: return mFoundTracks.at(index)->album();
    case FileUrl: return mFoundTracks.at(index)->file();
    case Track: return QVariant::fromValue(mFoundTracks.at(index));
    }

    return QVariant();

}
