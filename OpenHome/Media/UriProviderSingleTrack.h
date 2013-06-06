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
    UriProviderSingleTrack(const TChar* aMode, TrackFactory& aTrackFactory);
    TUint SetTrack(const Brx& aUri, const Brx& aMetaData);
    void SetTrack(Track* aTrack);
private: // from UriProvider
    void Begin(TUint aTrackId);
    EStreamPlay GetNext(Track*& aTrack);
    TBool MoveCursorAfter(TUint aTrackId);
    TBool MoveCursorBefore(TUint aTrackId);
private:
    TBool MoveCursor(TUint aTrackId);
private:
    Mutex iLock;
    TrackFactory& iTrackFactory;
    Track* iTrack;
    TBool iIgnoreNext;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_URIPROVIDER_SINGLE_TRACK
