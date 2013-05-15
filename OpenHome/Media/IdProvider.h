#ifndef HEADER_PIPELINE_ID_PROVIDER
#define HEADER_PIPELINE_ID_PROVIDER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

class PipelineIdProvider : public IPipelineIdProvider, public IPipelineIdTracker
{
    static const TUint kMaxActiveStreams = 100;
public:
    PipelineIdProvider(IStopper& aStopper);
    TUint MaxStreams() const;
public: // from IPipelineIdTracker
    void AddStream(const Brx& aStyle, const Brx& aProviderId, TUint aTrackId, TUint aStreamId, TBool aPlayNow);
private:
    static inline void UpdateIndex(TUint& aIndex);
    TUint UpdateId(TUint& aId);
private: // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    void InvalidateAt(const Brx& aStyle, const Brx& aProviderId);
    void InvalidateAfter(const Brx& aStyle, const Brx& aProviderId);
    void InvalidateAll();
private:
    class ActiveStream : public INonCopyable
    {
    public:
        ActiveStream();
        void Set(const Brx& aStyle, const Brx& aProviderId, TUint aTrackId, TUint aStreamId, TBool aPlayNow);
        void Set(const ActiveStream& aActiveStream);
        void Clear();
        TBool IsClear() const;
        TBool Matches(const Brx& aStyle, const Brx& aProviderId) const;
        const Brx& Style() const { return iStyle; }
        const Brx& ProviderId() const { return iProviderId; }
        TUint TrackId() const { return iTrackId; }
        TUint StreamId() const { return iStreamId; }
        TBool PlayNow() const { return iPlayNow; }
    private:
        BwsStyle iStyle;
        BwsProviderId iProviderId;
        TUint iTrackId;
        TUint iStreamId;
        TBool iPlayNow;
    };
private:
    Mutex iLock;
    IStopper& iStopper;
    TUint iNextTrackId;
    TUint iNextStreamId;
    ActiveStream iActiveStreams[kMaxActiveStreams];
    TUint iIndexHead;
    TUint iIndexTail;
    ActiveStream iPlaying;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_ID_PROVIDER
