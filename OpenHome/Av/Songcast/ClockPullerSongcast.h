#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/ClockPullerUtilisation.h>
#include <OpenHome/Media/Pipeline/Msg.h>

#include <vector>

namespace OpenHome {
namespace Av {

class ClockPullerNonTimestamped : public Media::IClockPullerReservoir, private INonCopyable
{
public:
    ClockPullerNonTimestamped(Environment& aEnv, Media::IPullableClock& aPullableClock);
    void SetEnabled(TBool aEnabled);
private:
    inline Media::IClockPullerReservoir& Puller();
private: // from IClockPullerReservoir
    void Reset() override;
    void Stop() override;
    void Start(TUint aNotificationFrequency) override;
    void NotifySize(TUint aJiffies) override;
private:
    Media::ClockPullerUtilisation iPuller;
    Mutex iLock;
    TBool iEnabled;
};

class ClockPullerSongcast : public Media::IClockPullerTimestamp, private INonCopyable
{
    static const TUint kMaxHistoryElements = 1000;
    static const TUint kMaxExpectedDeviation = Media::Jiffies::kPerMs * 5;
    static const TUint kMclkTicksPerSec44k = 44100 * 256;
    static const TUint kMclkTicksPerSec48k = 48000 * 256;
public:
    ClockPullerSongcast(Environment& aEnv, Media::IPullableClock& aPullableClock);
    Media::ModeClockPullers ClockPullers();
private:
    void ResetTimestampHistory();
    void SmoothTimestamps(TInt& aDrift, TInt aIndexToSkip);
private: // from Media::IClockPullerTimestamp
    void NewStream(TUint aSampleRate) override;
    void Reset() override;
    void Stop() override;
    void Start(TUint aExpectedPipelineJiffies) override;
    void NotifyTimestamp(TInt aDrift, TUint aNetwork) override;
private:
    ClockPullerNonTimestamped iPullerReservoirLeft;
    Media::IPullableClock& iPullableClock;
    TUint iMultiplier;
    TBool iUseTimestamps;
    TBool iStoreNetworkTimestamp;
    std::vector<TInt> iTimestampHistory;
    TUint iNextHistoryIndex;
    TUint iNetworkTimestampStart;
    TUint iNetworkTimestampLast;
    TUint iNetworkTimeOverflowCount;
    TUint iSampleRate;
    TInt iTimestampTotalDrift; // total over all history elements
    TUint iTimestampMaxAllowedDrift;
};

} // namespace Av
} // namespace OpenHome

