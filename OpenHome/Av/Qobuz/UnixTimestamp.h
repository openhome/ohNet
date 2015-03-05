#ifndef HEADER_UNIX_TIMERSTAMP
#define HEADER_UNIX_TIMERSTAMP

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/Qobuz/NtpClient.h>

EXCEPTION(UnixTimestampUnavailable);

namespace OpenHome {

class Environment;
class Timer;

class UnixTimestamp
{
    static const TUint kSecsBetweenNtpAndUnixEpoch = 2208988800; // secs between 1900 and 1970
public:
    UnixTimestamp(Environment& aEnv);
    ~UnixTimestamp();
    void Reset();
    TUint Now();
private:
    void TimestampExpired();
private:
    Environment& iEnv;
    Mutex iLock;
    NtpClient iNtpClient;
    Timer* iTimer;
    TBool iTimestampValid;
    TUint iStartSeconds;
    TUint iStartMs;
};

} // namespace OpenHome

#endif // HEADER_UNIX_TIMERSTAMP
