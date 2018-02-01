#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include <QObject>
#include <QUrl>
#include <QMediaPlayer>

namespace backend
{
    namespace structure
    {
        class Track;
    }

    namespace playback
    {
        class NowPlaying : public QObject
        {
            Q_OBJECT

            Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
            Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)

        public:
            NowPlaying(QMediaPlayer &mediaPlayer, QObject *parent = 0);

            Q_INVOKABLE QString artist() const;
            Q_INVOKABLE QString album() const;
            Q_INVOKABLE QString song() const;
            Q_INVOKABLE void seek(qint64 position);

        public:
            void setTrack(structure::Track *track);

        public:
            qint64 duration() const;
            qint64 position() const;

        signals:
            void durationChanged();
            void positionChanged();

        private:
            structure::Track *mTrack;
            QMediaPlayer &mPlayer;
        };
    }
}

#endif // NOWPLAYING_H
