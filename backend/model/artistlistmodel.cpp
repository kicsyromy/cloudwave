#include "artistlistmodel.h"

#include "artistretriever.h"

#include "logger.h"

using namespace backend;
using namespace backend::network;
using namespace backend::structure;
using namespace backend::adapter;
using namespace backend::model;

ArtistListModel::ArtistListModel(QObject *parent) :
    QAbstractListModel(parent),
    mItemCount(0),
    mSearching(false),
    mFoundArtists()
{
    ArtistRetriever *retriever = &(ArtistRetriever::instance());
    connect(retriever, &ArtistRetriever::artistsReady, this, &ArtistListModel::onArtistsReady);
    retriever->refresh();
}

void ArtistListModel::search(const QString &term)
{
    LOG_INFO << "Searching artists for" << term;
    beginResetModel();

    mFoundArtists.clear();
    mSearching = true;

    if (!term.isEmpty())
    {
        QStringList terms = term.split(' ', QString::SkipEmptyParts);
        ArtistList artists;
        mFoundArtists = ArtistRetriever::instance().artists();

        for (QStringList::iterator it = terms.begin(); it != terms.end(); ++it)
        {
            artists = mFoundArtists;
            mFoundArtists.clear();

            foreach (structure::Artist *artist, artists)
            {
                if (artist->name().contains(*it, Qt::CaseInsensitive) ||
                    it->contains(artist->name(), Qt::CaseInsensitive)
                   )
                    mFoundArtists.append(artist);
            }
        }
    }
    else
        mSearching = false;

    endResetModel();

    emit searchingChanged();
}

void ArtistListModel::refresh()
{
    beginResetModel();
    mItemCount = 0;
    endResetModel();

    ArtistRetriever::instance().refresh();
}

int ArtistListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (mSearching)
        return mFoundArtists.size();

    return mItemCount;
}

QVariant ArtistListModel::data(const QModelIndex &index, int role) const
{
    if (mSearching)
        return searchData(index.row(), role);

    ArtistList artists = ArtistRetriever::instance().artists();

    switch (role)
    {
    case Name: return artists.at(index.row())->name();
    case Summary: return artists.at(index.row())->summary();
    case Artist: return QVariant::fromValue(artists.at(index.row()));
    }

    return QVariant();
}

QHash<int, QByteArray> ArtistListModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[Name] = "name";
    roleNames[Summary] = "summary";
    roleNames[Artist] = "artist";

    return roleNames;
}

bool ArtistListModel::searching() const
{
    return mSearching;
}

void ArtistListModel::onArtistsReady()
{
    beginResetModel();
    mItemCount = ArtistRetriever::instance().artists().size();
    endResetModel();
}

QVariant ArtistListModel::searchData(int index, int role) const
{
    switch (role)
    {
    case Name: return mFoundArtists.at(index)->name();
    case Summary: return mFoundArtists.at(index)->summary();
    case Artist: return QVariant::fromValue(mFoundArtists.at(index));
    }

    return QVariant();
}
