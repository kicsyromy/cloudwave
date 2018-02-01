#include "playlistmodel.h"

using namespace backend;
using namespace backend::playback;
using namespace backend::model;

PlayListModel::PlayListModel(Playlist &pl, QObject *parent) :
    QAbstractListModel(parent),
    mPl(pl)
{
    connect(&mPl, &Playlist::tracksChanged, this, &PlayListModel::onTracksChanged);
}

int PlayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return mPl.tracks().size();
}

QVariant PlayListModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Title: return mPl.tracks().at(index.row())->title();
    case Artist: return mPl.tracks().at(index.row())->artist();
    case Album: return mPl.tracks().at(index.row())->album();
    }

    return QVariant();
}

QHash<int, QByteArray> PlayListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Title] = "title";
    roles[Artist] = "artist";
    roles[Album] = "album";

    return roles;
}

void PlayListModel::onTracksChanged()
{
    beginResetModel();
    endResetModel();
}
