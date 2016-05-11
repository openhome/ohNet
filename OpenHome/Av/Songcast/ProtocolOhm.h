#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Songcast/ProtocolOhBase.h>

namespace OpenHome {
    class Environment;
namespace Media {
    class TrackFactory;
    class IClockPullerTimestamp;
}
namespace Av {

class IOhmMsgFactory;
class IOhmTimestamper;

class ProtocolOhm : public ProtocolOhBase
{
public:
    ProtocolOhm(Environment& aEnv, IOhmMsgFactory& aMsgFactory, Media::TrackFactory& aTrackFactory, IOhmTimestamper* aTimestamper,
                Media::IClockPullerTimestamp& aClockPuller, const Brx& aMode);
private: // from ProtocolOhBase
    Media::ProtocolStreamResult Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint) override;
    void ProcessTimestamps(const OhmMsgAudio& aMsg, TBool& aDiscard, TUint& aClockPullMultiplier) override;
private: // from Media::Protocol
    void Interrupt(TBool aInterrupt) override;
private: // from IStreamHandler
    TUint TryStop(TUint aStreamId) override;
private:
    void ResetClockPuller();
private:
    TUint iNextFlushId;
    TBool iStopped;
    Mutex iStoppedLock;
    // clock pulling
    static const TInt kLockingMaxDeviation;
    static const TUint kLockingMsgCount;
    TBool iCheckForTimestamp;
    TBool iStreamIsTimestamped;
    TBool iLockedToStream;
    TBool iCalculateTimestampDelta;
    TUint iTimestamperFreq;
    TUint iLockingMaxDeviation;
    TUint iJiffiesBeforeTimestampsReliable;
    TInt iTimestampDelta;
    TUint iMsgsTillLock;
    Media::IClockPullerTimestamp& iClockPuller; // FIXME - change to reference
};

} // namespace Av
} // namespace OpenHome

