#include <OpenHome/Av/Qobuz/NtpClient.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Timer.h>

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
    iServerEndpoint = Endpoint(kNtpPort, Brn(kNtpServers[iNextServerIndex]));
    iNextServerIndex = (iNextServerIndex+1) % kNumServers;
    const TUint loopedIndex = iNextServerIndex;
    do {
        success = DoTryGetNetworkTime(aNetworkTime, aNetworkDelayMs);
        iServerEndpoint = Endpoint(kNtpPort, Brn(kNtpServers[iNextServerIndex]));
        iNextServerIndex = (iNextServerIndex+1) % kNumServers;
    } while (!success && iNextServerIndex != loopedIndex);
    return success;
}

void NtpClient::TestAllServers()
{
    for (TUint i=0; i<kNumServers; i++) {
        NtpTimestamp ts;
        TUint networkDelayMs;
        iServerEndpoint = Endpoint(kNtpPort, Brn(kNtpServers[i]));
        Endpoint::AddressBuf buf;
        iServerEndpoint.AppendAddress(buf);
        Log::Print("%s: ", buf.PtrZ());
        if (DoTryGetNetworkTime(ts, networkDelayMs)) {
            Log::Print("seconds = %u, networkDelayMs = %u\n", ts.Seconds(), networkDelayMs);
        }
        else {
            Log::Print("FAILED\n");
        }
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
        (void)reader.ReadUintBe(4);     // root delay
        (void)reader.ReadUintBe(4);     // root dispersion
        (void)reader.ReadUintBe(4);     // reference id
        (void)reader.ReadUint64Be(8);   // reference timestamp
        (void)reader.ReadUint64Be(8);   // origin timestamp
        aNetworkTime.Read(iReadBuffer); // receive timestamp
        (void)reader.ReadUint64Be(8);   // transmit timestamp
        iUdpReader.ReadFlush();
        iReadTimeout->Cancel();

        success = true;
        aNetworkDelayMs = (Time::Now(iEnv) - txTime) / 2; // assume delay is spliy evenly over tx/rx 
    }
    catch (WriterError&) {
    }
    catch (ReaderError&) {
    }

    return success;
}

void NtpClient::ReadTimeout()
{
    iSocket.Interrupt(true);
}

void NtpClient::Write(TByte /*aValue*/)
{
    ASSERTS();
}

void NtpClient::Write(const Brx& aBuffer)
{
    iSocket.Send(aBuffer, iServerEndpoint);
}

void NtpClient::WriteFlush()
{
    // nothing to do, data is flushed inside Write(const Brx&)
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
