#include "nowplaying.h"

#include "track.h"

using namespace backend;
using namespace backend::playback;

NowPlaying::NowPlaying(QMediaPlayer &mediaPlayer, QObject *parent) :
    QObject(parent),
    mTrack(0),
    mPlayer(mediaPlayer)
{
    connect(&mPlayer, &QMediaPlayer::durationChanged, this, &NowPlaying::durationChanged);
    connect(&mPlayer, &QMediaPlayer::positionChanged, this, &NowPlaying::positionChanged);
}

QString NowPlaying::artist() const
{
    QString s;

    if (mTrack)
    {
        s = mTrack->artist();
    }

    return s;
}

QString NowPlaying::album() const
{
    QString s;

    if (mTrack)
    {
        s = mTrack->album();
    }

    return s;
}

QString NowPlaying::song() const
{
    QString s;

    if (mTrack)
    {
        s = mTrack->title();
    }

    return s;
}

void NowPlaying::seek(qint64 position)
{
    mPlayer.setPosition(position);
}

void NowPlaying::setTrack(structure::Track *track)
{
    mTrack = track;
}

qint64 NowPlaying::duration() const
{
    return mPlayer.duration();
}

qint64 NowPlaying::position() const
{
    return mPlayer.position();
}
