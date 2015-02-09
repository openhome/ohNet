#ifndef HEADER_CLOCK_PULLER_SONGCAST
#define HEADER_CLOCK_PULLER_SONGCAST

#include <OpenHome/Types.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/ClockPullerUtilisation.h>
#include <OpenHome/Media/Pipeline/Msg.h>

#include <vector>

namespace OpenHome {
namespace Av {

class ClockPullerSongcast : public Media::IClockPuller, private Media::IUtilisationHistoryObserver, private INonCopyable
{
    static const TUint kMaxHistoryElements = 1000;
    static const TUint kMaxExpectedDeviation = Media::Jiffies::kPerMs * 5;
    static const TUint kMclkTicksPerSec44k = 44100 * 256;
    static const TUint kMclkTicksPerSec48k = 48000 * 256;
public:
    ClockPullerSongcast(Environment& aEnv, Media::IPullableClock& aPullableClock);
    ~ClockPullerSongcast();
private:
    void ResetTimestampHistory();
    void SmoothTimestamps(TInt& aDrift, TInt aIndexToSkip);
private: // from Media::IClockPuller
    void StartTimestamp() override;
    void NotifyTimestampSampleRate(TUint aSampleRate) override;
    void NotifyTimestamp(TInt aDrift, TUint aNetwork) override;
    void StopTimestamp() override;
    void StartDecodedReservoir(TUint aCapacityJiffies, TUint aNotificationFrequency) override;
    void NewStreamDecodedReservoir(TUint aStreamId) override;
    void NotifySizeDecodedReservoir(TUint aJiffies) override;
    void StopDecodedReservoir() override;
    void StartStarvationMonitor(TUint aCapacityJiffies, TUint aNotificationFrequency) override;
    void NewStreamStarvationMonitor(TUint aStreamId) override;
    void NotifySizeStarvationMonitor(TUint aJiffies) override;
    void StopStarvationMonitor() override;
private: // from Media::IUtilisationHistoryObserver
    void NotifyClockDrift(Media::UtilisationHistory* aHistory, TInt aDriftJiffies, TUint aNumSamples) override;
private:
    Media::IPullableClock& iPullableClock;
    Media::UtilisationHistory* iHistoryLeft;
    Media::UtilisationHistory* iHistoryRight;
    TUint iDecodedReservoirUpdateFrequency;
    TUint iStarvationMonitorUpdateFrequency;
    TBool iUseTimestamps;
    TBool iRunning;
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

#endif // HEADER_CLOCK_PULLER_SONGCAST
