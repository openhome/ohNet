#include <OpenHome/UnixTimestamp.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/NtpClient.h>

#include <algorithm>
#include <limits.h>

using namespace OpenHome;

const TUint UnixTimestamp::kSecsBetweenNtpAndUnixEpoch = 2208988800; // secs between 1900 and 1970
const TUint UnixTimestamp::kTimeResyncFreqMs = 24 * 60 * 60 * 1000; // 1 day

UnixTimestamp::UnixTimestamp(Environment& aEnv)
    : iEnv(aEnv)
    , iLock("UNTS")
    , iNtpClient(aEnv)
    , iTimestampValid(false)
    , iTimestampRenew(true)
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
    AutoMutex _(iLock);
    iTimestampRenew = true;
}

TUint UnixTimestamp::Now()
{
    AutoMutex _(iLock);
    if (Time::Now(iEnv) < iStartMs) {
        iTimestampValid = false;
    }
    if (!iTimestampValid || iTimestampRenew) {
        NtpTimestamp networkTime;
        TUint networkDelayMs;
        if (!iNtpClient.TryGetNetworkTime(networkTime, networkDelayMs)) {
            if (!iTimestampValid) {
                THROW(UnixTimestampUnavailable);
            }
        }
        // round up network delay to make up for rounding down fractional component of networkTime
        iStartSeconds = networkTime.Seconds() - kSecsBetweenNtpAndUnixEpoch + ((networkDelayMs + 500) / 1000);
        iStartMs = Time::Now(iEnv);
        // recalculate when local millisecond timer wraps
        const TUint timeTillWrap = std::max(static_cast<TUint>(UINT_MAX)-iStartMs, static_cast<TUint>(1u));
        const TUint timerDuration = std::min(kTimeResyncFreqMs, timeTillWrap);
        iTimer->FireIn(timerDuration);
        iTimestampValid = true;
        iTimestampRenew = false;
    }

    const TUint unixTs = iStartSeconds + ((Time::Now(iEnv) - iStartMs) / 1000);
    return unixTs;
}

void UnixTimestamp::TimestampExpired()
{
    Reset();
}
