#ifndef HEADER_CLOCK_PULLER
#define HEADER_CLOCK_PULLER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

namespace OpenHome {
namespace Media {

class IClockPuller
{
public:
    virtual ~IClockPuller() {}
    virtual void NotifySize(TUint aJiffies) = 0;
    virtual void Stop() = 0;
};

class UtilisationHistory : public IClockPuller
{
public:
    UtilisationHistory(TUint aMaxSamples, Functor aChanged);
    const std::vector<TUint64>& History() const; // can only be called from Changed callback
    TUint StartIndex() const; // can only be called from Changed callback
private: // from IClockPuller
    void NotifySize(TUint aJiffies);
    void Stop();
private:
    Functor iChanged;
    std::vector<TUint64> iHistory;
    TUint iNextIndex;
};

class ClockPuller
{
    static const TUint kMaxSamplePoints = 100;
public:
    ClockPuller();
    ~ClockPuller();
    IClockPuller& DecodedReservoirHistory();
    IClockPuller& StarvationMonitorHistory();
private: // from IClockPuller
    void DecodedReservoirChanged();
    void StarvationMonitorChanged();
private:
    UtilisationHistory* iDecodedReservoirHistory;
    UtilisationHistory* iStarvationMonitorHistory;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_CLOCK_PULLER
