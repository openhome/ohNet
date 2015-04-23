#ifndef HEADER_NTP_CLIENT
#define HEADER_NTP_CLIENT

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {

class Environment;
class NtpTimestamp;
class Timer;

class NtpClient : public IWriter
{
    static const TUint kFrameBytes    = 48; // size of mandatory fields in NTP packet
    static const TUint kNtpPort       = 123;
    static const TUint kReadTimeoutMs = 5000;
public:
    NtpClient(Environment& aEnv);
    ~NtpClient();
    TBool TryGetNetworkTime(NtpTimestamp& aNetworkTime, TUint& aNetworkDelayMs);
    void TestAllServers();
private:
    TBool DoTryGetNetworkTime(NtpTimestamp& aNetworkTime, TUint& aNetworkDelayMs);
    void ReadTimeout();
    inline void Log(const TChar* aId, TUint aVal) const { Log(aId, aVal, sizeof(aVal)); }
    inline void Log(const TChar* aId, TUint64 aVal) const { Log(aId, aVal, sizeof(aVal)); }
    void Log(const TChar* aId, TUint64 aVal, TUint aBytes) const;
private: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
private:
    Environment& iEnv;
    SocketUdp iSocket;
    UdpReader iUdpReader;
    Srs<kFrameBytes> iReadBuffer;
    Sws<kFrameBytes>* iWriteBuffer;
    Timer* iReadTimeout;
    TUint iNextServerIndex;
    Endpoint iServerEndpoint;
    TBool iLogEnable;
};

class NtpHeader
{
    static const TUint kLeapIndicator = 0;
    static const TUint kVersion       = 4;
    static const TUint kMode          = 3;  // client
    static const TUint kStratum       = 16; //unsynchronised (i.e. a client only?)
    static const TUint kPollFreq      = 0;
    static const TUint kPrecision     = 0;
public:
    NtpHeader();
    static void Write(IWriter& aWriter);
    void Read(IReader& aReader);
    TUint LeapIndicator() const;
    TUint Version() const;
    TUint Mode() const;
    TUint Stratum() const;
    TUint Poll() const;
    TUint Precision() const;
    TUint Value() const;
private:
    TBool iInitialised;
    TUint iHeader;
};

class NtpTimestamp
{
public:
    NtpTimestamp();
    void Read(IReader& aReader);
    void Reset();
    TUint Seconds() const;
    TUint Fraction() const;
private:
    TBool iInitialised;
    TUint iSeconds;
    TUint iFraction;
};

} // namespace OpenHome

#endif // HEADER_NTP_CLIENT
