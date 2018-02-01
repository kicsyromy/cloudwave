#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QUrl>
#include <QMetaType>
#include <QtQml>

namespace backend
{
    namespace structure
    {
        struct Track
        {
            Track(const QString &title, const QString &artistName, const QString &albumName, const QString &albumArtUrl, const QString &artistThumbUrl, const QString &fileUrl) :
                mTitle(title),
                mArtist(artistName),
                mAlbum(albumName),
                mAlbumArt(albumArtUrl),
                mArtistThumbnail(artistThumbUrl),
                mFile(fileUrl)
            {}

            QString title() const
            {
                return mTitle;
            }

            QString artist() const
            {
                return mArtist;
            }

            QString album() const
            {
                return mAlbum;
            }

            QUrl albumArt() const
            {
                return mAlbumArt;
            }

            QUrl artistThumbnail() const
            {
                return mArtistThumbnail;
            }

            QUrl file() const
            {
                return mFile;
            }

            bool operator <(const Track &other) const
            {
                return mTitle < other.mTitle;
            }

        private:
            const QString mTitle;
            const QString mArtist;
            const QString mAlbum;
            const QUrl mAlbumArt;
            const QUrl mArtistThumbnail;
            const QUrl mFile;
        };
    }
}

Q_DECLARE_METATYPE(backend::structure::Track *)

#endif // TRACK_H

