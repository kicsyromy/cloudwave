#ifndef ALBUM_H
#define ALBUM_H

#include <QString>
#include <QUrl>
#include <QMetaType>

namespace backend
{
    namespace structure
    {
        struct Album
        {
            Album(const QString &title, const QString &artist, const QString &genre, const quint8 songCount, const QString &artworkUrl, const QString &key) :
                mTitle(title),
                mArtist(artist),
                mGenre(genre),
                mSongCount(songCount),
                mArtwork(artworkUrl),
                mKey(key)
            {}

            QString title() const
            {
                return mTitle;
            }

            QString artist() const
            {
                return mArtist;
            }

            QString genre() const
            {
                return mGenre;
            }

            quint8 songCount() const
            {
                return mSongCount;
            }

            QUrl artwork() const
            {
                return mArtwork;
            }

            QString key() const
            {
                return mKey;
            }

        private:
            const QString mTitle;
            const QString mArtist;
            const QString mGenre;
            const quint8 mSongCount;
            const QUrl mArtwork;
            const QString mKey;
        };
    }
}

Q_DECLARE_METATYPE(backend::structure::Album *)

#endif // ALBUM_H
