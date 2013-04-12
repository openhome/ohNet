#ifndef HEADER_PIPELINE_ID_PROVIDER
#define HEADER_PIPELINE_ID_PROVIDER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

typedef Bws<32> BwsStyle;
typedef Bws<32> BwsProviderId;

class IStopper // FIXME - move to Msg.h ?
{
public:
    virtual void RemoveStream(TUint aTrackId, TUint aStreamId) = 0;
};

class PipelineIdProvider : public IPipelineIdProvider
{
    static const TUint kMaxActiveStreams = 100;
public:
    PipelineIdProvider(IStopper& aStopper);
    void AddStream(const Brx& aStyle, const Brx& aProviderId, TUint aTrackId, TUint aStreamId);
    TUint MaxStreams() const;
private:
    static inline void UpdateIndex(TUint& aIndex);
    TUint UpdateId(TUint& aId);
private: // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    void InvalidateAt(const Brx& aStyle, const Brx& aProviderId);
    void InvalidateAfter(const Brx& aStyle, const Brx& aProviderId);
private:
    class ActiveStream : public INonCopyable
    {
    public:
        ActiveStream();
        void Set(const Brx& aStyle, const Brx& aProviderId, TUint aTrackId, TUint aStreamId);
        void Set(const ActiveStream& aActiveStream);
        TBool Matches(const Brx& aStyle, const Brx& aProviderId) const;
        const Brx& Style() const { return iStyle; }
        const Brx& ProviderId() const { return iProviderId; }
        TUint TrackId() const { return iTrackId; }
        TUint StreamId() const { return iStreamId; }
    private:
        BwsStyle iStyle;
        BwsProviderId iProviderId;
        TUint iTrackId;
        TUint iStreamId;
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
