#ifndef HEADER_PIPELINE_URIPROVIDER_REPEATER
#define HEADER_PIPELINE_URIPROVIDER_REPEATER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/Pipeline/TrackInspector.h>

namespace OpenHome {
namespace Av {

class UriProviderRepeater : public Media::UriProvider, public Media::ITrackObserver
{
public:
    UriProviderRepeater(const TChar* aMode, Media::TrackFactory& aTrackFactory);
    ~UriProviderRepeater();
    Media::Track* SetTrack(const Brx& aUri, const Brx& aMetaData);
    void SetTrack(Media::Track* aTrack);
private: // from UriProvider
    void Begin(TUint aTrackId);
    void BeginLater(TUint aTrackId);
    Media::EStreamPlay GetNext(Media::Track*& aTrack);
    TUint CurrentTrackId() const;
    TBool MoveNext();
    TBool MovePrevious();
private: // from Media::ITrackObserver
    void NotifyTrackPlay(Media::Track& aTrack);
    void NotifyTrackFail(Media::Track& aTrack);
private:
    void DoBegin(TUint aTrackId, TBool aLater);
    TBool MoveCursor();
private:
    mutable Mutex iLock;
    Media::TrackFactory& iTrackFactory;
    Media::Track* iTrack;
    TBool iRetrieved;
    TBool iPlayLater;
    TBool iFailed;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_URIPROVIDER_REPEATER
