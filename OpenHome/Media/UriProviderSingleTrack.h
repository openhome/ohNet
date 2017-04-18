#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class UriProviderSingleTrack : public UriProvider
{
public:
    UriProviderSingleTrack(const TChar* aMode, TBool aSupportsLatency, TrackFactory& aTrackFactory);
    ~UriProviderSingleTrack();
    Track* SetTrack(const Brx& aUri, const Brx& aMetaData);
    void SetTrack(Track* aTrack);
protected: // from UriProvider
    void Begin(TUint aTrackId) override;
    void BeginLater(TUint aTrackId) override;
    EStreamPlay GetNext(Track*& aTrack) override;
    TUint CurrentTrackId() const override;
    void MoveNext() override;
    void MovePrevious() override;
    void MoveTo(const Brx& aCommand) override;
private:
    void DoBegin(TUint aTrackId, TBool aLater);
    void MoveCursor();
private:
    mutable Mutex iLock;
    TrackFactory& iTrackFactory;
    Track* iTrack;
    TBool iIgnoreNext;
    TBool iPlayLater;
};

} // namespace Media
} // namespace OpenHome

