#include <OpenHome/NtpClient.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;

// See RFC5905 section 7 (Data Structures) for details on the protocol

static const TChar* kNtpServers[] = { "0.pool.ntp.org",
                                      "1.pool.ntp.org",
                                      "2.pool.ntp.org",
                                      "3.pool.ntp.org" };
static const TUint kNumServers = sizeof(kNtpServers) / sizeof(kNtpServers[0]);

NtpClient::NtpClient(Environment& aEnv)
    : iEnv(aEnv)
    , iSocket(aEnv)
    , iUdpReader(iSocket)
    , iReadBuffer(iUdpReader)
    , iNextServerIndex(0)
    , iLogEnable(true) // temporarily enabled to help diagnose http://forums.linn.co.uk/bb/showthread.php?tid=36476&pid=440782#pid440782
{
    iWriteBuffer = new Sws<kFrameBytes>(*this);
    iReadTimeout = new Timer(aEnv, MakeFunctor(*this, &NtpClient::ReadTimeout), "NtpClient");
}

NtpClient::~NtpClient()
{
    delete iReadTimeout;
    delete iWriteBuffer;
}

TBool NtpClient::TryGetNetworkTime(NtpTimestamp& aNetworkTime, TUint& aNetworkDelayMs)
{
    TBool success = false;
    const TUint loopedIndex = iNextServerIndex;
    do {
        try {
            const TUint index = iNextServerIndex;
            iNextServerIndex = (iNextServerIndex+1) % kNumServers;
            iServerEndpoint = Endpoint(kNtpPort, Brn(kNtpServers[index]));
            success = DoTryGetNetworkTime(aNetworkTime, aNetworkDelayMs);
        }
        catch (NetworkError&) {}
    } while (!success && iNextServerIndex != loopedIndex);
    iNextServerIndex = (iNextServerIndex+1) % kNumServers;
    return success;
}

void NtpClient::TestAllServers()
{
    iLogEnable = true;
    for (;;) {
        for (TUint i=0; i<kNumServers; i++) {
            try {
                NtpTimestamp ts;
                TUint networkDelayMs;
                iServerEndpoint = Endpoint(kNtpPort, Brn(kNtpServers[i]));
                Endpoint::AddressBuf buf;
                iServerEndpoint.AppendAddress(buf);
                Log::Print("\n%s:\n", buf.PtrZ());
                if (DoTryGetNetworkTime(ts, networkDelayMs)) {
                    Log::Print("seconds = %u, networkDelayMs = %u\n", ts.Seconds(), networkDelayMs);
                    ASSERT(ts.Seconds() != 0);
                }
                else {
                    Log::Print("FAILED\n");
                }
            }
            catch (NetworkError&) {
                Log::Print("NetworkError for %s\n", kNtpServers[i]);
            }
        }
        Thread::Sleep(1000);
    }
}

TBool NtpClient::DoTryGetNetworkTime(NtpTimestamp& aNetworkTime, TUint& aNetworkDelayMs)
{
    TBool success = false;
    iSocket.Interrupt(false);
    try {
        NtpHeader::Write(*iWriteBuffer);
        WriterBinary writer(*iWriteBuffer);
        writer.WriteUint32Be(0); // root delay
        writer.WriteUint32Be(0); // root dispertion
        writer.WriteUint32Be(0); // reference id
        writer.WriteUint64Be(0); // reference timestamp
        writer.WriteUint64Be(0); // origin timestamp
        writer.WriteUint64Be(0); // receive timestamp
        writer.WriteUint64Be(0); // transmit timestamp
        const TUint txTime = Time::Now(iEnv);
        iWriteBuffer->WriteFlush();

        iReadTimeout->FireIn(kReadTimeoutMs);
        ReaderBinary reader(iReadBuffer);
        NtpHeader header;
        header.Read(iReadBuffer);
        Log("header", header.Value());
        Log("root delay", reader.ReadUintBe(4));
        Log("root dispersion", reader.ReadUintBe(4));
        Log("reference id", reader.ReadUintBe(4));
        Log("reference timestamp", reader.ReadUint64Be(8));
        Log("origin timestamp", reader.ReadUint64Be(8));
        aNetworkTime.Read(iReadBuffer); // receive timestamp
        Log("Seconds", aNetworkTime.Seconds());
        Log("Fraction", aNetworkTime.Fraction());
        Log("transmit timestamp", reader.ReadUint64Be(8));
        iUdpReader.ReadFlush();
        iReadTimeout->Cancel();

        success = (aNetworkTime.Seconds() > 0); // rfc958 s4 states that zero rx or tx timestamp is invalid
        aNetworkDelayMs = (Time::Now(iEnv) - txTime) / 2; // assume delay is spliy evenly over tx/rx 
    }
    catch (WriterError&) {
        LogError("WriterError");
    }
    catch (ReaderError&) {
        LogError("ReaderError");
    }

    return success;
}

void NtpClient::ReadTimeout()
{
    LogError("Timeout");
    iSocket.Interrupt(true);
}

void NtpClient::Write(TByte /*aValue*/)
{
    ASSERTS();
}

void NtpClient::Write(const Brx& aBuffer)
{
    try {
        iSocket.Send(aBuffer, iServerEndpoint);
    }
    catch (NetworkError&) {
        THROW(WriterError);
    }
}

void NtpClient::WriteFlush()
{
    // nothing to do, data is flushed inside Write(const Brx&)
}

void NtpClient::Log(const TChar* aId, TUint64 aVal, TUint aBytes) const
{
    if (!iLogEnable) {
        return;
    }
    Bws<64> buf;
    buf.AppendPrintf("%24s:", aId);
    for (TInt i=aBytes-1; i>=0; i--) {
        TByte b = (aVal >> i) & 0xff;
        buf.AppendPrintf(" %02x", b);
    }
    buf.Append('\n');
    Log::Print(buf);
}

void NtpClient::LogError(const TChar* aEx) const
{
    Endpoint::AddressBuf buf;
    iServerEndpoint.AppendAddress(buf);
    LOG2(kPipeline, kError, "%s from NtpClient::DoTryGetNetworkTime. Server is %.*s\n", aEx, PBUF(buf));
}


// NtpHeader

NtpHeader::NtpHeader()
    : iInitialised(false)
{
}

void NtpHeader::Write(IWriter& aWriter)
{ // static
    TUint header = kLeapIndicator << 30;
    header |= (kVersion << 27);
    header |= (kMode << 24);
    header |= (kStratum << 16);
    header |= (kPollFreq << 8);
    header |= kPrecision;
    WriterBinary writer(aWriter);
    writer.WriteUint32Be(header);
}

void NtpHeader::Read(IReader& aReader)
{
    ReaderBinary reader(aReader);
    iHeader = reader.ReadUintBe(4);
    iInitialised = true;
}

TUint NtpHeader::LeapIndicator() const
{
    ASSERT(iInitialised);
    return iHeader >> 30;
}

TUint NtpHeader::Version() const
{
    ASSERT(iInitialised);
    return (iHeader >> 27) & 7;
}

TUint NtpHeader::Mode() const
{
    ASSERT(iInitialised);
    return (iHeader >> 24) & 7;
}

TUint NtpHeader::Stratum() const
{
    ASSERT(iInitialised);
    return (iHeader >> 16) & 0xFF;
}

TUint NtpHeader::Poll() const
{
    ASSERT(iInitialised);
    return (iHeader >> 8) & 0xFF;
}

TUint NtpHeader::Precision() const
{
    ASSERT(iInitialised);
    return iHeader & 0xFF;
}

TUint NtpHeader::Value() const
{
    ASSERT(iInitialised);
    return iHeader;
}


// NtpTimestamp

NtpTimestamp::NtpTimestamp()
    : iInitialised(false)
{
}

void NtpTimestamp::Read(IReader& aReader)
{
    ReaderBinary reader(aReader);
    iSeconds = reader.ReadUintBe(4);
    iFraction = reader.ReadUintBe(4);
    iInitialised = true;
}

void NtpTimestamp::Reset()
{
    iInitialised = false;
}

TUint NtpTimestamp::Seconds() const
{
    ASSERT(iInitialised);
    return iSeconds;
}

TUint NtpTimestamp::Fraction() const
{
    ASSERT(iInitialised);
    return iFraction;
}
