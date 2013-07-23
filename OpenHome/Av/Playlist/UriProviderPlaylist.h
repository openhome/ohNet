#ifndef HEADER_URI_PROVIDER_PLAYLIST
#define HEADER_URI_PROVIDER_PLAYLIST

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Private/Thread.h>

#include <array>
#include <vector>

namespace OpenHome {
namespace Av {

class IPlaylistDatabaseReader;

class UriProviderPlaylist : public Media::UriProvider
{
public:
    UriProviderPlaylist(IPlaylistDatabaseReader& aDatabase);
    void SetRepeat(TBool aRepeat);
private: // from UriProvider
    void Begin(TUint aTrackId);
    Media::EStreamPlay GetNext(Media::Track*& aTrack);
    TBool MoveCursorAfter(TUint aTrackId);
    TBool MoveCursorBefore(TUint aTrackId);
private:
    Mutex iLock;
    IPlaylistDatabaseReader& iDatabase;
    TBool iRepeat;
    TBool iDbCursorWrapped;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_URI_PROVIDER_PLAYLIST
