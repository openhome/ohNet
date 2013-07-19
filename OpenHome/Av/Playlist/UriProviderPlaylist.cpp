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
    , iDatabase(aDatabase)
{
}

void UriProviderPlaylist::Begin(TUint aTrackId)
{
    iDatabase.MoveCursorTo(aTrackId);
}

EStreamPlay UriProviderPlaylist::GetNext(Media::Track*& aTrack)
{
    aTrack = iDatabase.NextTrack();    
    return ePlayYes; // FIXME
}

TBool UriProviderPlaylist::MoveCursorAfter(TUint aTrackId)
{
    return iDatabase.TryMoveCursorAfter(aTrackId);
}

TBool UriProviderPlaylist::MoveCursorBefore(TUint aTrackId)
{
    return iDatabase.TryMoveCursorBefore(aTrackId);
}
