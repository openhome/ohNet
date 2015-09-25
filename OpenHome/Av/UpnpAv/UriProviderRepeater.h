#pragma once

#include <OpenHome/Types.h>
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
    void Begin(TUint aTrackId) override;
    void BeginLater(TUint aTrackId) override;
    Media::EStreamPlay GetNext(Media::Track*& aTrack) override;
    TUint CurrentTrackId() const override;
    TBool MoveNext() override;
    TBool MovePrevious() override;
private: // from Media::ITrackObserver
    void NotifyTrackPlay(Media::Track& aTrack) override;
    void NotifyTrackFail(Media::Track& aTrack) override;
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

