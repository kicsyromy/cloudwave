#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVariant>

#include "common.h"
#include "nowplaying.h"

namespace backend
{
    namespace playback
    {
        class Playlist: public QObject
        {
            Q_OBJECT
            Q_PROPERTY(bool playing READ isPlaying NOTIFY playingChanged)
            Q_PROPERTY(backend::playback::NowPlaying* nowPlaying READ getNowPlaying NOTIFY nowPlayingChanged)

        public:
            explicit Playlist(QObject *parent = 0);

        public:
            Q_INVOKABLE void play();
            Q_INVOKABLE void play(int index);
            Q_INVOKABLE void play(QVariant trackList, bool shuffle = false);
            Q_INVOKABLE void appendAndPlay(QVariant track);
            Q_INVOKABLE void append(QVariant track);
            Q_INVOKABLE void pause();
            Q_INVOKABLE void next();
            Q_INVOKABLE void previous();
            Q_INVOKABLE void clear();
            Q_INVOKABLE int size() const;

            NowPlaying *getNowPlaying();

        public:
            TrackList tracks() const;
            bool isPlaying() const;

        signals:
            void tracksChanged();
            void nowPlayingChanged();
            void playingChanged();

        private slots:
            void onCurrentIntexChanged(int position);

        private:
            QMediaPlayer mPlayer;
            QMediaPlaylist mPlaylist;
            TrackList mTracks;
            NowPlaying mPlaying;
        };
    }
}

#endif // PLAYLIST_H
