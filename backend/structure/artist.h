#ifndef ARTIST_H
#define ARTIST_H

#include <QString>
#include <QUrl>
#include <QMetaType>

namespace backend
{
    namespace structure
    {
        struct Artist
        {
            Artist(const QString &name, const QString &thumbnailUrl, const QString &summary, const QString &key) :
                mName(name),
                mThumbnail(thumbnailUrl),
                mSummary(summary),
                mKey(key)
            {}

            QString name() const
            {
                return mName;
            }

            QUrl thumbnail() const
            {
                return mThumbnail;
            }

            QString summary() const
            {
                return mSummary;
            }

            QString key() const
            {
                return mKey;
            }

        private:
            const QString mName;
            const QUrl mThumbnail;
            const QString mSummary;
            const QString mKey;
        };
    }
}

Q_DECLARE_METATYPE(backend::structure::Artist *)

#endif // ARTIST_H

