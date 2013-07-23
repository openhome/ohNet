#include <OpenHome/Av/Playlist/UriProviderPlaylist.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/Playlist/PlaylistDatabase.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// UriProviderPlaylist

UriProviderPlaylist::UriProviderPlaylist(IPlaylistDatabaseReader& aDatabase)
    : UriProvider("Playlist")
    , iLock("UPPL")
    , iDatabase(aDatabase)
    , iRepeat(false)
    , iDbCursorWrapped(false)
{
}

void UriProviderPlaylist::SetRepeat(TBool aRepeat)
{
    iLock.Wait();
    iRepeat = aRepeat;
    iLock.Signal();
}

void UriProviderPlaylist::Begin(TUint aTrackId)
{
    iDatabase.MoveCursorTo(aTrackId);
}

EStreamPlay UriProviderPlaylist::GetNext(Media::Track*& aTrack)
{
    AutoMutex a(iLock);
    TBool wrapped;
    iDatabase.NextTrack(aTrack, wrapped);
    wrapped |= iDbCursorWrapped;
    iDbCursorWrapped = false;
    if (aTrack == NULL) {
        return ePlayNo;
    }
    if (!wrapped || iRepeat) {
        return ePlayYes;
    }
    return ePlayLater;
}

TBool UriProviderPlaylist::MoveCursorAfter(TUint aTrackId)
{
    AutoMutex a(iLock);
    TBool wrapped;
    const TBool moved = iDatabase.TryMoveCursorAfter(aTrackId, wrapped);
    iDbCursorWrapped |= wrapped;
    return moved;
}

TBool UriProviderPlaylist::MoveCursorBefore(TUint aTrackId)
{
    AutoMutex a(iLock);
    TBool wouldWrapped;
    const TBool moved = iDatabase.TryMoveCursorBefore(aTrackId, iRepeat, wouldWrapped);
    iDbCursorWrapped |= wouldWrapped;
    return moved;
}
