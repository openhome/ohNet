#ifndef HEADER_CLOCK_PULLER_LOGGING
#define HEADER_CLOCK_PULLER_LOGGING

#include <OpenHome/Types.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
    class Environment;
namespace Media {

class IUtilisationObserver
{
public:
    virtual void AddAverage(TUint aAverage) = 0;
};

class Utilisation : private INonCopyable
{
public:
    Utilisation(TUint aEntries, IUtilisationObserver& aObserver);
    void Add(TUint aJiffies);
    void Clear();
private:
    IUtilisationObserver& iObserver;
    std::vector<TUint> iHistory;
};

class UtilisationHistoryLogging : private IUtilisationObserver, private INonCopyable
{
public:
    UtilisationHistoryLogging(Environment& aEnv);
    ~UtilisationHistoryLogging();
    void Add(TUint aJiffies);
    void Clear();
private: // from IUtilisationObserver
    void AddAverage(TUint aAverage);
private:
    Environment& iEnv;
    Utilisation* iLevel1;
    std::vector<TUint> iRecent;
    std::vector<TUint> iHistory;
    TUint iNextHistoryIndex;
    TUint iStartValue;
    TUint iLastValue;
    TUint iMinValue;
    TUint iMaxValue;
    TUint iStartTime;
};

class ClockPullerLogging : public IClockPuller
{
public:
    ClockPullerLogging(Environment& aEnv);
private: // from IClockPuller
    void StartTimestamp() override;
    void NotifyTimestamp(TInt aDrift, TUint aNetwork) override;
    void StopTimestamp() override;
    void StartDecodedReservoir(TUint aCapacityJiffies, TUint aNotificationFrequency);
    void NewStreamDecodedReservoir(TUint aTrackId, TUint aStreamId);
    void NotifySizeDecodedReservoir(TUint aJiffies);
    void StopDecodedReservoir();
    void StartStarvationMonitor(TUint aCapacityJiffies, TUint aNotificationFrequency);
    void NewStreamStarvationMonitor(TUint aTrackId, TUint aStreamId);
    void NotifySizeStarvationMonitor(TUint aJiffies);
    void StopStarvationMonitor();
private:
    Mutex iLock;
    StreamId iStreamLeft;
    StreamId iStreamRight;
    UtilisationHistoryLogging iUtilisationLeft;
    UtilisationHistoryLogging iUtilisationRight;
    TUint iActiveCount;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_CLOCK_PULLER_LOGGING
