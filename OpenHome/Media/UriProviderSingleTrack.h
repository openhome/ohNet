#ifndef HEADER_PIPELINE_URIPROVIDER_SINGLE_TRACK
#define HEADER_PIPELINE_URIPROVIDER_SINGLE_TRACK

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Filler.h>

namespace OpenHome {
namespace Media {

class UriProviderSingleTrack : public UriProvider
{
public:
    UriProviderSingleTrack(TrackFactory& aTrackFactory);
private: // from UriProvider
    virtual void Begin(const Brx& aProviderId) = 0;
    virtual EStreamPlay GetNext(Track*& aTrack) = 0;
    virtual EStreamPlay GetPrev(Track*& aTrack) = 0;
private:
    TrackFactory& iTrackFactory;
    BwsTrackUri iUri;

};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_URIPROVIDER_SINGLE_TRACK
