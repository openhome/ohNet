#ifndef HEADER_PIPELINE_URIPROVIDER_SINGLE_TRACK
#define HEADER_PIPELINE_URIPROVIDER_SINGLE_TRACK

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class UriProviderSingleTrack : public UriProvider
{
public:
    UriProviderSingleTrack(TrackFactory& aTrackFactory);
private: // from UriProvider
    void Begin(const Brx& aProviderId);
    EStreamPlay GetNext(Track*& aTrack);
    TBool MoveCursorAfter(const Brx& aProviderId);
    TBool MoveCursorBefore(const Brx& aProviderId);
private:
    TBool MoveCursor(const Brx& aProviderId);
private:
    Mutex iLock;
    TrackFactory& iTrackFactory;
    BwsTrackUri iUri;
    TBool iIgnoreNext;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_URIPROVIDER_SINGLE_TRACK
