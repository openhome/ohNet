#ifndef HEADER_CLOCK_PULLER_SONGCAST
#define HEADER_CLOCK_PULLER_SONGCAST

#include <OpenHome/Types.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class StreamId
{
public:
    StreamId();
    void SetTrack(TUint aId);
    void SetStream(TUint aId);
    TBool operator ==(const StreamId& aId) const;
    TUint IdPipeline() const { return iTrackId; }
    TUint IdStream() const { return iStreamId; }
private:
    TUint iTrackId;
    TUint iStreamId;
};

class UtilisationHistory
{
public:
    UtilisationHistory(TUint aMaxElements);
    void Clear();
    void Add(TUint aJiffies);
private:
    Functor iCallback;
    std::vector<TUint> iHistory;
    TUint iNextIndex;

    // speculative stuff follows
    TUint iStartValue;
    TUint iLastValue;
    TUint iMinValue;
    TUint iMaxValue;
    TUint iStartTime;
    TUint iSamplePointsSinceLastChange; // defeat pulling via constant tiny changes?
    TUint iAverage;
    TUint iTotal; // helper for iAverage calculation
};

class ClockPullerSongcast : public IClockPuller
{
public:
    ClockPullerSongcast();
private: // from IClockPuller
    void StartDecodedReservoir(TUint aCapacityJiffies);
    void NewStreamDecodedReservoir(TUint aTrackId, TUint aStreamId);
    void NotifySizeDecodedReservoir(TUint aJiffies);
    void StopDecodedReservoir();
    void StartStarvationMonitor(TUint aCapacityJiffies);
    void NewStreamStarvationMonitor(TUint aTrackId, TUint aStreamId);
    void NotifySizeStarvationMonitor(TUint aJiffies);
    void StopStarvationMonitor();
private:
    Mutex iLock;
    StreamId iStreamLeft;
    StreamId iStreamRight;
    UtilisationHistory iUtilisationLeft;
    UtilisationHistory iUtilisationRight;
    TUint iActiveCount;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_CLOCK_PULLER_SONGCAST
