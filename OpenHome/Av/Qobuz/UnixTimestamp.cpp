#include <OpenHome/Av/Qobuz/UnixTimestamp.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Av/Qobuz/NtpClient.h>

#include <limits.h>

using namespace OpenHome;


UnixTimestamp::UnixTimestamp(Environment& aEnv)
    : iEnv(aEnv)
    , iLock("UNTS")
    , iNtpClient(aEnv)
    , iTimestampValid(false)
    , iStartMs(UINT_MAX)
{
    iTimer = new Timer(aEnv, MakeFunctor(*this, &UnixTimestamp::TimestampExpired), "UnixTimestamp");
}

UnixTimestamp::~UnixTimestamp()
{
    delete iTimer;
}

void UnixTimestamp::Reset()
{
    iLock.Wait();
    iTimestampValid = false;
    iLock.Signal();
}

TUint UnixTimestamp::Now()
{
    AutoMutex _(iLock);
    if (Time::Now(iEnv) < iStartMs) {
        iTimestampValid = false;
    }
    if (!iTimestampValid) {
        NtpTimestamp networkTime;
        TUint networkDelayMs;
        if (!iNtpClient.TryGetNetworkTime(networkTime, networkDelayMs)) {
            THROW(UnixTimestampUnavailable);
        }
        // round up network delay to make up for rounding down fractional component of networkTime
        iStartSeconds = networkTime.Seconds() - kSecsBetweenNtpAndUnixEpoch + ((networkDelayMs + 500) / 1000);
        iStartMs = Time::Now(iEnv);
        // recalculate when local millisecond timer wraps
        iTimer->FireIn(UINT_MAX - iStartMs + 1);
        iTimestampValid = true;
    }

    const TUint unixTs = iStartSeconds + ((Time::Now(iEnv) - iStartMs) / 1000);
    return unixTs;
}

void UnixTimestamp::TimestampExpired()
{
    Reset();
}
