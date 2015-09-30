#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
namespace Media {

class SuiteEncodedReservoir;

class EncodedAudioReservoir : public AudioReservoir, private IStreamHandler, private INonCopyable
{
    friend class SuiteEncodedReservoir;
public:
    EncodedAudioReservoir(MsgFactory& aMsgFactory, IFlushIdProvider& aFlushIdProvider, TUint aMsgCount, TUint aMaxStreamCount);
    TUint SizeInBytes() const;
private:
    inline IStreamHandler* StreamHandler();
    Msg* EndSeek(Msg* aMsg);
private: // from AudioReservoir
    TBool IsFull() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgTrack* aMsg) override;
    void ProcessMsgIn(MsgEncodedStream* aMsg) override;
    void ProcessMsgIn(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsgOut(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgAudioEncoded* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory& iMsgFactory;
    IFlushIdProvider& iFlushIdProvider;
    const TUint iMsgCount;
    const TUint iMaxStreamCount;
    Mutex iLock2;
    IStreamHandler* iStreamHandler; // FIXME - thread safety
    TUint iStreamId;
    TUint64 iStreamPos;
    TUint iNextFlushId;
    TUint64 iSeekPos;
};

} // namespace Media
} // namespace OpenHome

