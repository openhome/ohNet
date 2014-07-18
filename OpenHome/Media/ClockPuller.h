#ifndef HEADER_CLOCK_PULLER
#define HEADER_CLOCK_PULLER

#include <OpenHome/Types.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

namespace OpenHome {
namespace Media {

class IClockPuller
{
public:
    virtual ~IClockPuller() {}
    virtual void StartDecodedReservoir(TUint aCapacityJiffies) = 0;
    virtual void NewStreamDecodedReservoir(TUint aTrackId, TUint aStreamId) = 0;
    virtual void NotifySizeDecodedReservoir(TUint aJiffies) = 0;
    virtual void StopDecodedReservoir() = 0;
    virtual void StartStarvationMonitor(TUint aCapacityJiffies) = 0;
    virtual void NewStreamStarvationMonitor(TUint aTrackId, TUint aStreamId) = 0;
    virtual void NotifySizeStarvationMonitor(TUint aJiffies) = 0;
    virtual void StopStarvationMonitor() = 0;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_CLOCK_PULLER
