#ifndef HEADER_URI_PROVIDER_PLAYLIST
#define HEADER_URI_PROVIDER_PLAYLIST

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Filler.h>

#include <array>
#include <vector>

namespace OpenHome {
namespace Av {

class IPlaylistDatabaseReader;

class UriProviderPlaylist : public Media::UriProvider
{
public:
    UriProviderPlaylist(IPlaylistDatabaseReader& aDatabase);
private: // from UriProvider
    void Begin(TUint aTrackId);
    Media::EStreamPlay GetNext(Media::Track*& aTrack);
    TBool MoveCursorAfter(TUint aTrackId);
    TBool MoveCursorBefore(TUint aTrackId);
private:
    IPlaylistDatabaseReader& iDatabase;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_URI_PROVIDER_PLAYLIST
