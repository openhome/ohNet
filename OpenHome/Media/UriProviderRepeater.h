#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/Pipeline/TrackInspector.h>

namespace OpenHome {
namespace Media {

class UriProviderRepeater : public UriProvider, public ITrackObserver
{
public:
    UriProviderRepeater(const TChar* aMode, TBool aSupportsLatency, TrackFactory& aTrackFactory);
    ~UriProviderRepeater();
    Track* SetTrack(const Brx& aUri, const Brx& aMetaData);
    void SetTrack(Track* aTrack);
private: // from UriProvider
    void Begin(TUint aTrackId) override;
    void BeginLater(TUint aTrackId) override;
    EStreamPlay GetNext(Track*& aTrack) override;
    TUint CurrentTrackId() const override;
    void MoveNext() override;
    void MovePrevious() override;
    void MoveTo(const Brx& aCommand) override;
private: // from ITrackObserver
    void NotifyTrackPlay(Track& aTrack) override;
    void NotifyTrackFail(Track& aTrack) override;
private:
    void DoBegin(TUint aTrackId, TBool aLater);
    void MoveCursor();
private:
    mutable Mutex iLock;
    TrackFactory& iTrackFactory;
    Track* iTrack;
    TBool iRetrieved;
    TBool iPlayLater;
    TBool iFailed;
};

} // namespace Media
} // namespace OpenHome

