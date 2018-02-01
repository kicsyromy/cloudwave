#include "genrelistmodel.h"

#include "genreretriever.h"

#include "logger.h"

using namespace backend;
using namespace backend::network;
using namespace backend::structure;
using namespace backend::adapter;
using namespace backend::model;

GenreListModel::GenreListModel(QObject *parent) :
    QAbstractListModel(parent),
    mItemCount(0),
    mSearching(false),
    mFoundGenres()
{
    GenreRetriever *retriever = &(GenreRetriever::instance());
    connect(retriever, &GenreRetriever::genresReady, this, &GenreListModel::onGenresReady);
    retriever->refresh();
}

void GenreListModel::search(const QString &term)
{
    beginResetModel();

    mFoundGenres.clear();
    mSearching = true;

    if (!term.isEmpty())
    {
        GenreList genres = GenreRetriever::instance().genres();

        foreach (QString genre, genres) {
            if (genre.contains(term, Qt::CaseInsensitive) ||
                term.contains(genre, Qt::CaseInsensitive))
                mFoundGenres.append(genre);
        }
    }
    else
        mSearching = false;

    endResetModel();

    emit searchingChanged();
}

void GenreListModel::refresh()
{
    beginResetModel();
    mItemCount = 0;
    endResetModel();

    GenreRetriever::instance().refresh();
}

int GenreListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (mSearching)
        return mFoundGenres.size();

    return mItemCount;
}

QVariant GenreListModel::data(const QModelIndex &index, int role) const
{
    if (mSearching)
        return searchData(index.row(), role);

    GenreList genres = GenreRetriever::instance().genres();

    switch (role)
    {
    default: return QVariant();
    case Name: return genres.at(index.row());
    }
}

QHash<int, QByteArray> GenreListModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[Name] = "name";

    return roleNames;
}

bool GenreListModel::searching() const
{
    return mSearching;
}

void GenreListModel::onGenresReady()
{
    beginResetModel();
    mItemCount = GenreRetriever::instance().genres().size();
    endResetModel();
}

QVariant GenreListModel::searchData(int index, int role) const
{
    if (role == Name)
        return mFoundGenres.at(index);

    return QVariant();
}
