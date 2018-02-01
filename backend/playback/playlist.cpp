#include "playlist.h"

#include "track.h"
#include "logger.h"

using namespace backend;
using namespace backend::playback;
using namespace backend::structure;

Playlist::Playlist(QObject *parent) :
    QObject(parent),
    mPlayer(),
    mPlaylist(),
    mTracks(),
    mPlaying(mPlayer)
{
    connect(&mPlaylist, &QMediaPlaylist::currentIndexChanged, this, &Playlist::onCurrentIntexChanged);
    connect(&mPlayer, &QMediaPlayer::stateChanged, this, &Playlist::playingChanged);
    mPlayer.setPlaylist(&mPlaylist);
}

void Playlist::play()
{
    mPlayer.play();
}

void Playlist::play(int index)
{
    mPlayer.stop();
    mPlaylist.setCurrentIndex(index);
    mPlayer.play();

    mPlaying.setTrack(mTracks.at(index));

    emit nowPlayingChanged();
}

void Playlist::play(QVariant trackList, bool shuffle)
{
    Playlist::clear();

    QList<Track *> tracks = qvariant_cast<QList<Track *> >(trackList);

    foreach (Track *track, tracks)
    {
        Track *tcpy = new Track(
                           track->title(),
                           track->artist(),
                           track->album(),
                           track->albumArt().toString(),
                           track->artistThumbnail().toString(),
                           track->file().toString());

        mTracks.append(tcpy);
        mPlaylist.addMedia(tcpy->file());
    }

    if (mTracks.size() > 0)
    {
        mPlaying.setTrack(mTracks.at(0));

        int playbackIndex = 0;

        if (shuffle)
        {
            mPlaylist.setPlaybackMode(QMediaPlaylist::Random);
            playbackIndex = mPlaylist.nextIndex();
        }
        else
            mPlaylist.setPlaybackMode(QMediaPlaylist::Sequential);

        emit tracksChanged();
        Playlist::play(playbackIndex);
    }
    else
        mPlaying.setTrack(NULL);
}

void Playlist::appendAndPlay(QVariant track)
{
    Track *t = qvariant_cast<Track *>(track);

    // This needs to be deleted later on
    // Deep copy in case of track refresh
    Track *tcpy = new Track(
                       t->title(),
                       t->artist(),
                       t->album(),
                       t->albumArt().toString(),
                       t->artistThumbnail().toString(),
                       t->file().toString());

    int newIndex = mTracks.size();

    mTracks.append(tcpy);

    mPlaylist.addMedia(tcpy->file());
    mPlaylist.setCurrentIndex(newIndex);
    mPlayer.play();

    mPlaying.setTrack(tcpy);
    emit tracksChanged();
    emit nowPlayingChanged();
}

void Playlist::append(QVariant track)
{
    Track *t = qvariant_cast<Track *>(track);

    // This needs to be deleted later on
    // Deep copy in case of track refresh
    Track *tcpy = new Track(
                       t->title(),
                       t->artist(),
                       t->album(),
                       t->albumArt().toString(),
                       t->artistThumbnail().toString(),
                       t->file().toString());

    mTracks.append(tcpy);

    mTracks.append(tcpy);
    mPlaylist.addMedia(tcpy->file());

    emit tracksChanged();
}

void Playlist::pause()
{
    if (mPlayer.state() == QMediaPlayer::PlayingState)
        mPlayer.pause();
}

void Playlist::next()
{
    if (mTracks.size() > 0)
    {
        int nextIndex = mPlaylist.nextIndex();
        mPlaylist.setCurrentIndex(nextIndex);

        if (mPlayer.state() != QMediaPlayer::PlayingState)
            mPlayer.play();
    }
}

void Playlist::previous()
{
    if (mTracks.size() > 0)
    {
        int previousIndex = mPlaylist.previousIndex();
        mPlaylist.setCurrentIndex(previousIndex);

        if (mPlayer.state() != QMediaPlayer::PlayingState)
            mPlayer.play();
    }
}

void Playlist::clear()
{
    mPlayer.stop();
    mPlaylist.clear();
    qDeleteAll(mTracks);
    mTracks.clear();

    emit tracksChanged();
}

TrackList Playlist::tracks() const
{
    return mTracks;
}

bool Playlist::isPlaying() const
{
    return mPlayer.state() == QMediaPlayer::PlayingState;
}

void Playlist::onCurrentIntexChanged(int position)
{
    int index = position < mTracks.size() && position >= 0 ? position : 0;
    mPlaying.setTrack(mTracks.at(index));
    emit nowPlayingChanged();
}

int Playlist::size() const
{
    return mTracks.size();
}

NowPlaying *Playlist::getNowPlaying()
{
    return &mPlaying;
}
