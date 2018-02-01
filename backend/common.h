#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include <QEventLoop>
#include <QList>

#include "album.h"
#include "artist.h"
#include "track.h"

#define WAIT_FOR(object_type, object, signal, instruction) \
    QEventLoop el; \
    QObject::connect(object, &object_type::signal, &el, &QEventLoop::quit); \
    instruction; \
    el.exec()

typedef QList<backend::structure::Album *>  AlbumList;
typedef QList<backend::structure::Artist *> ArtistList;
typedef QList<backend::structure::Track *>  TrackList;
typedef QList<QString>  GenreList;

template <typename T>
struct LessThanPtr
{
    inline bool operator()(const T* a, const T* b) const
    {
        return a && b ? *a < *b : false;
    }
};

#endif // COMMON_H

