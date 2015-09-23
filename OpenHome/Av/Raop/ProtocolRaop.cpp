#include <OpenHome/Av/Raop/ProtocolRaop.h>
#include <OpenHome/Av/Raop/UdpServer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Media/SupplyAggregator.h>

EXCEPTION(RaopAudioServerClosed);

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;


// RtpHeaderRaop

RtpHeaderRaop::RtpHeaderRaop(TBool aPadding, TBool aExtension, TUint aCsrcCount, TBool aMarker, TUint aPayloadType, TUint aSeqNumber)
    : iPadding(aPadding)
    , iExtension(aExtension)
    , iCsrcCount(aCsrcCount)
    , iMarker(aMarker)
    , iPayloadType(aPayloadType)
    , iSequenceNumber(aSeqNumber)
{
    if (iCsrcCount > 0xf) {
        THROW(InvalidRaopPacket);
    }
    if (iPayloadType > 0x7f) {
        THROW(InvalidRaopPacket);
    }
    if (iSequenceNumber > 0xffff)
    {
        THROW(InvalidRaopPacket);
    }
}

RtpHeaderRaop::RtpHeaderRaop(const Brx& aRtpHeader)
{
    if (aRtpHeader.Bytes() != kBytes) {
        THROW(InvalidRaopPacket);
    }

    const TUint version = (aRtpHeader[0] & 0xc0) >> 6;
    if (version != kVersion) {
        THROW(InvalidRaopPacket);
    }
    iPadding = (aRtpHeader[0] & 0x20) == 0x20;
    iExtension = (aRtpHeader[0] & 0x10) == 0x10;
    iCsrcCount = aRtpHeader[0] & 0x0f;
    iMarker = (aRtpHeader[1] & 0x80) == 0x80;
    iPayloadType = aRtpHeader[1] & 0x7f;

    static const TUint offset = 2;  // Processed first 2 bytes above.
    Brn packetRemaining(aRtpHeader.Ptr()+offset, aRtpHeader.Bytes()-offset);
    ReaderBuffer readerBuffer(packetRemaining);
    ReaderBinary readerBinary(readerBuffer);

    try {
        iSequenceNumber = readerBinary.ReadUintBe(2);
    }
    catch (ReaderError&) {
        THROW(InvalidRaopPacket);
    }
}

void RtpHeaderRaop::Write(IWriter& aWriter) const
{
    WriterBinary writerBinary(aWriter);
    TUint8 byte1 = (TUint8)((kVersion << 6) | (iPadding << 5) | (iExtension << 4) | (iCsrcCount));
    TUint8 byte2 = (TUint8)((iMarker << 7) | (iPayloadType));
    writerBinary.WriteUint8(byte1);
    writerBinary.WriteUint8(byte2);
    writerBinary.WriteUint16Be(iSequenceNumber);
}

TBool RtpHeaderRaop::Padding() const
{
    return iPadding;
}

TBool RtpHeaderRaop::Extension() const
{
    return iExtension;
}

TUint RtpHeaderRaop::CsrcCount() const
{
    return iCsrcCount;
}

TBool RtpHeaderRaop::Marker() const
{
    return iMarker;
}

TUint RtpHeaderRaop::Type() const
{
    return iPayloadType;
}

TUint RtpHeaderRaop::Seq() const
{
    return iSequenceNumber;
}


// RtpPacketRaop

RtpPacketRaop::RtpPacketRaop(const Brx& aRtpPacket)
    : iHeader(Brn(aRtpPacket.Ptr(), RtpHeaderRaop::kBytes))
    , iPayload(aRtpPacket.Ptr()+RtpHeaderRaop::kBytes, aRtpPacket.Bytes()-RtpHeaderRaop::kBytes)
{
}

const RtpHeaderRaop& RtpPacketRaop::Header() const
{
    return iHeader;
}

const Brx& RtpPacketRaop::Payload() const
{
    return iPayload;
}


// RaopPacketSync

RaopPacketSync::RaopPacketSync(const RtpPacketRaop& aRtpPacket)
    : iPacket(aRtpPacket)
    , iPayload(iPacket.Payload().Ptr()+kSyncSpecificHeaderBytes, iPacket.Payload().Bytes()-kSyncSpecificHeaderBytes)
{
    if (iPacket.Header().Type() != kType) {
        THROW(InvalidRaopPacket);
    }

    const Brx& payload = iPacket.Payload();
    ReaderBuffer readerBuffer(payload);
    ReaderBinary readerBinary(readerBuffer);

    try {
        iRtpTimestampMinusLatency = readerBinary.ReadUintBe(4);
        iNtpTimestampSecs = readerBinary.ReadUintBe(4);
        iNtpTimestampFract = readerBinary.ReadUintBe(4);
        iRtpTimestamp = readerBinary.ReadUintBe(4);
    }
    catch (ReaderError&) {
        THROW(InvalidRaopPacket);
    }
}

const RtpHeaderRaop& RaopPacketSync::Header() const
{
    return iPacket.Header();
}

const Brx& RaopPacketSync::Payload() const
{
    return iPayload;
}

TUint RaopPacketSync::RtpTimestampMinusLatency() const
{
    return iRtpTimestampMinusLatency;
}

TUint RaopPacketSync::NtpTimestampSecs() const
{
    return iNtpTimestampSecs;
}

TUint RaopPacketSync::NtpTimestampFract() const
{
    return iNtpTimestampFract;
}

TUint RaopPacketSync::RtpTimestamp() const
{
    return iRtpTimestamp;
}


// RaopPacketResendResponse

RaopPacketResendResponse::RaopPacketResendResponse(const RtpPacketRaop& aRtpPacket)
    : iPacketOuter(aRtpPacket)
    , iPacketInner(iPacketOuter.Payload())
    , iAudioPacket(iPacketInner)
{
    if (iPacketOuter.Header().Type() != kType) {
        THROW(InvalidRaopPacket);
    }
}

const RtpHeaderRaop& RaopPacketResendResponse::Header() const
{
    return iPacketOuter.Header();
}

const RaopPacketAudio& RaopPacketResendResponse::AudioPacket() const
{
    return iAudioPacket;
}


// RaopPacketResendRequest

RaopPacketResendRequest::RaopPacketResendRequest(TUint aSeqStart, TUint aCount)
    : iHeader(false, false, 0, true, kType, 1)
    , iSeqStart(aSeqStart)
    , iCount(aCount)
{
}

void RaopPacketResendRequest::Write(IWriter& aWriter) const
{
    WriterBinary writerBinary(aWriter);
    iHeader.Write(aWriter);
    writerBinary.WriteUint16Be(iSeqStart);
    writerBinary.WriteUint16Be(iCount);
}


// RaopPacketAudio

RaopPacketAudio::RaopPacketAudio(const RtpPacketRaop& aRtpPacket)
    : iPacket(aRtpPacket)
    , iPayload(iPacket.Payload().Ptr()+kAudioSpecificHeaderBytes, iPacket.Payload().Bytes()-kAudioSpecificHeaderBytes)
{
    if (iPacket.Header().Type() != kType) {
        THROW(InvalidRaopPacket);
    }

    const Brx& payload = iPacket.Payload();
    ReaderBuffer readerBuffer(payload);
    ReaderBinary readerBinary(readerBuffer);

    try {
        iTimestamp = readerBinary.ReadUintBe(4);
        iSsrc = readerBinary.ReadUintBe(4);
    }
    catch (ReaderError&) {
        THROW(InvalidRaopPacket);
    }
}

const RtpHeaderRaop& RaopPacketAudio::Header() const
{
    return iPacket.Header();
}

const Brx& RaopPacketAudio::Payload() const
{
    return iPayload;
}

TUint RaopPacketAudio::Timestamp() const
{
    return iTimestamp;
}

TUint RaopPacketAudio::Ssrc() const
{
    return iSsrc;
}


// ProtocolRaop

ProtocolRaop::ProtocolRaop(Environment& aEnv, Media::TrackFactory& aTrackFactory, IRaopVolumeEnabler& aVolume, IRaopDiscovery& aDiscovery, UdpServerManager& aServerManager, TUint aAudioId, TUint aControlId)
    : ProtocolNetwork(aEnv)
    , iTrackFactory(aTrackFactory)
    , iVolumeEnabled(false)
    , iVolume(aVolume)
    , iDiscovery(aDiscovery)
    , iServerManager(aServerManager)
    , iAudioServer(iServerManager.Find(aAudioId))
    , iControlServer(iServerManager.Find(aControlId), *this)
    , iSupply(nullptr)
    , iLockRaop("PRAL")
    , iSem("PRAS", 0)
    , iSemDrain("PRSD", 0)
    , iTimerResend(aEnv, MakeFunctor(*this, &ProtocolRaop::ResendTimerFired), "ProtocolRaopResendTimer")
    , iResendSeqNext(0)
    , iResendCount(0)
    , iSemResend("PRRS", 0)
{
}

ProtocolRaop::~ProtocolRaop()
{
    delete iSupply;
}

void ProtocolRaop::DoInterrupt()
{
    LOG(kMedia, "ProtocolRaop::DoInterrupt\n");

    iAudioServer.DoInterrupt();
    iControlServer.DoInterrupt();
}

void ProtocolRaop::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new SupplyAggregatorBytes(aMsgFactory, aDownstream);
}

ProtocolStreamResult ProtocolRaop::Stream(const Brx& aUri)
{
    LOG(kMedia, "ProtocolRaop::Stream(%.*s)\n", PBUF(aUri));

    {
        AutoMutex a(iLockRaop);
        try {
            iUri.Replace(aUri);
        }
        catch (UriError&) {
            LOG(kMedia, "ProtocolRaop::Stream unable to parse URI\n");
            return EProtocolErrorNotSupported;
        }
    }

    // RAOP doesn't actually stream from a URI, so just expect a dummy URI.
    if (iUri.Scheme() != Brn("raop")) {
        LOG(kMedia, "ProtocolRaop::Stream Scheme not recognised\n");
        return EProtocolErrorNotSupported;
    }

    Reset();
    WaitForDrain();

    TBool start = true;
    TUint seqExpected = 0;

    // Output audio stream
    for (;;) {
        {
            AutoMutex a(iLockRaop);
            if (iWaiting) {
                iSupply->OutputFlush(iNextFlushId);
                iNextFlushId = MsgFlush::kIdInvalid;
                iWaiting = false;
                iResumePending = true;
                iSem.Clear();

                Semaphore sem("PRWS", 0);
                iSupply->OutputDrain(MakeFunctor(sem, &Semaphore::Signal));
                sem.Wait();
                // Resume normal operation.
            }
            else if (iStopped) {
                iStreamId = IPipelineIdProvider::kStreamIdInvalid;
                iSupply->OutputFlush(iNextFlushId);
                iNextFlushId = MsgFlush::kIdInvalid;
                iActive = false;
                WaitForDrain();
                LOG(kMedia, "<ProtocolRaop::Stream iStopped\n");
                return EProtocolStreamStopped;
            }
        }

        try {
            iPacketBuf.SetBytes(0);
            iAudioServer.ReadPacket(iPacketBuf);
            RtpPacketRaop rtpPacket(iPacketBuf);
            RaopPacketAudio audioPacket(rtpPacket);
            const TUint seqLast = audioPacket.Header().Seq();

            if (!iDiscovery.Active()) {
                LOG(kMedia, "ProtocolRaop::Stream() no active session\n");
                {
                    AutoMutex a(iLock);
                    iActive = false;
                    iStopped = true;
                }
                WaitForDrain();
                LOG(kMedia, "<ProtocolRaop::Stream !iDiscovery.Active()\n");
                return EProtocolStreamStopped;
            }

            if (ShouldFlush(audioPacket.Header().Seq(), audioPacket.Timestamp())) {
                continue;   // Flush this packet.
            }

            iLockRaop.Wait();
            const TBool resumePending = iResumePending;
            iLockRaop.Signal();
            if (start || resumePending) {
                LOG(kMedia, "ProtocolRaop::Stream starting new stream\n");
                UpdateSessionId(audioPacket.Ssrc());
                iAudioDecryptor.Init(iDiscovery.Aeskey(), iDiscovery.Aesiv());
                seqExpected = seqLast;   // Init seqExpected.
                start = false;


                Track* track = nullptr;
                TUint latency = 0;
                TUint streamId = 0;
                Uri uri;
                {
                    AutoMutex a(iLock);
                    iResumePending = false;
                    iFlushSeq = 0;
                    iFlushTime = 0;

                    // FIXME - is this correct uri for track/stream?
                    track = iTrackFactory.CreateTrack(iUri.AbsoluteUri(), Brx::Empty());
                    streamId = iStreamId = iIdProvider->NextStreamId();
                    latency = iLatency = iControlServer.Latency();
                    uri.Replace(iUri.AbsoluteUri());
                }

                // FIXME - outputting MsgTrack then MsgEncodedStream causes accumulated time reported by pipeline to be reset to 0.
                // Not necessarily desirable when pausing or seeking.

                iSupply->OutputDelay(Delay(latency));
                iSupply->OutputTrack(*track, !resumePending);
                iSupply->OutputStream(uri.AbsoluteUri(), 0, false, false, *this, streamId);
                OutputContainer(iDiscovery.Fmtp());
                track->RemoveRef();
            }
            iDiscovery.KeepAlive();


            const TBool validSession = IsValidSession(audioPacket.Ssrc());
            const TBool shouldFlush = ShouldFlush(audioPacket.Header().Seq(), audioPacket.Timestamp());

            if (validSession && !shouldFlush) {
                if (seqLast == seqExpected) {
                    // The packet that was expected.
                    OutputAudio(audioPacket.Payload());
                    seqExpected++;
                }
                else if (seqLast > seqExpected) {
                    // Missed some packets.
                    const TUint missed = seqLast-seqExpected;
                    LOG(kMedia, "ProtocolRaop::Stream missed %u audio packets\n", missed);
                    {
                        AutoMutex a(iLockRaop);
                        iResendSeqNext = seqExpected;
                        iResendCount = missed;
                        iTimerResend.FireIn(kResendTimeoutMs);
                        iControlServer.RequestResend(seqExpected, missed);
                        // Callbacks will come via ::ReceiveResend().
                    }
                    iSemResend.Wait();  // FIXME - ensure this is only cleared once ALL packets have been resent.
                    // FIXME - what if waiting on a resend during a flush?
                    // Still need to check if the resent audio should be flushed.
                    // FIXME - need to then output current audioPacket?
                }
                else {
                    // Packet is one that's already been seen. Ignore.
                }
            }
        }
        catch (InvalidRaopPacket&) {
            LOG(kMedia, "<ProtocolRaop::Stream Invalid Header\n");
            //break;
        }
        catch (NetworkError&) {
            LOG(kMedia, "<ProtocolRaop::Stream Network error\n");
            //break;
        }
        catch (ReaderError&) {
            LOG(kMedia, "<ProtocolRaop::Stream Reader error\n");
            // This can indicate an interrupt (caused by, e.g., a TryStop)
            // Continue around loop and see if iStopped has been set.
        }
        catch (HttpError&) {
            LOG(kMedia, "<ProtocolRaop::Stream sdp not received\n");
            // ignore and continue - sender should stop on a closed connection! wait for sender to re-select device
        }
        catch (RaopAudioServerClosed&) {
            LOG(kMedia, "ProtocolRaop::Stream RaopAudioServerClosed\n");
            // If this happens, it means an RAOP session should have ended.
            // Wait for TryStop() to be called so that iNextFlushId is
            // incremented, then return to start of loop for flush handling.
            iSem.Wait();
        }
    }
}

ProtocolGetResult ProtocolRaop::Get(IWriter& /*aWriter*/, const Brx& /*aUri*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return EProtocolGetErrorNotSupported;
}

void ProtocolRaop::Reset()
{
    AutoMutex a(iLockRaop);

    // Parse URI to get client control/timing ports.
    // (Timing channel isn't monitored, so don't bother parsing port.)
    Parser p(iUri.AbsoluteUri());
    p.Forward(7);   // skip raop://
    const Brn ctrlPortBuf = p.Next('.');
    const TUint ctrlPort = Ascii::Uint(ctrlPortBuf);
    iAudioServer.Reset();
    iControlServer.Reset(ctrlPort);

    iSessionId = 0;
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iLatency = 0;
    iFlushSeq = 0;
    iFlushTime = 0;
    iNextFlushId = MsgFlush::kIdInvalid;
    iActive = true;
    iWaiting = false;
    iResumePending = false;
    iStopped = false;
    iResendSeqNext = 0;
    iResendCount = 0;

    iSem.Clear();
}

void ProtocolRaop::StartStream()
{
    LOG(kMedia, "ProtocolRaop::StartStream\n");
    AutoMutex a(iLockRaop);
    iStreamId = iIdProvider->NextStreamId();
    iSupply->OutputStream(iUri.AbsoluteUri(), 0, false, false, *this, iStreamId);
}

void ProtocolRaop::UpdateSessionId(TUint aSessionId)
{
    AutoMutex a(iLockRaop);
    if (iSessionId == 0) {
        // Initialise session ID.
        iSessionId = aSessionId;
        LOG(kMedia, "ProtocolRaop::UpdateSessionId new iSessionId: %u\n", iSessionId);
    }
}

TBool ProtocolRaop::IsValidSession(TUint aSessionId) const
{
    AutoMutex a(iLockRaop);
    if (iSessionId == aSessionId) {
        return true;
    }
    return false;
}

TBool ProtocolRaop::ShouldFlush(TUint aSeq, TUint aTimestamp) const
{
    AutoMutex a(iLockRaop);
    if (iResumePending) {
        const TBool seqInFlushRange = (aSeq <= iFlushSeq);
        const TBool timeInFlushRange = (aTimestamp <= iFlushTime);
        const TBool shouldFlush = (seqInFlushRange && timeInFlushRange);
        return shouldFlush;
    }
    return false;
}

void ProtocolRaop::OutputContainer(const Brx& aFmtp)
{
    Bws<60> container(Brn("Raop"));
    container.Append(Brn(" "));
    Ascii::AppendDec(container, aFmtp.Bytes()+1);   // account for newline char added
    container.Append(" ");
    container.Append(aFmtp);
    container.Append(Brn("\n"));
    LOG(kMedia, "ProtocolRaop::OutputContainer container %d bytes [", container.Bytes()); LOG(kMedia, container); LOG(kMedia, "]\n");
    iSupply->OutputData(container);
}

void ProtocolRaop::OutputAudio(const Brx& aAudio)
{
    TBool outputDelay = false;
    TUint latency = iControlServer.Latency();
    {
        AutoMutex a(iLockRaop);
        if (latency != iLatency) {
            iLatency = latency;
            outputDelay = true;
        }
    }
    if (outputDelay) {
        iSupply->OutputDelay(Delay(latency));
    }

    iAudioDecryptor.Decrypt(aAudio, iAudioDecrypted);
    iSupply->OutputData(iAudioDecrypted);
}

void ProtocolRaop::WaitForDrain()
{
    iSemDrain.Clear();
    iSupply->OutputDrain(MakeFunctor(*this, &ProtocolRaop::InputChanged));
    iSemDrain.Wait();
}

void ProtocolRaop::InputChanged()
{
    // Only called while WaitForDrain() is blocking main thread, so no need to lock this.
    iVolumeEnabled = !iVolumeEnabled;   // Toggle volume.
    iVolume.SetVolumeEnabled(iVolumeEnabled);
    iSemDrain.Signal();
}

void ProtocolRaop::ResendTimerFired()
{
    // FIXME - should notify pipeline of discontinuity if timer fires.
    AutoMutex a(iLockRaop);
    if (iResendCount > 0) {
        iResendCount--;
    }

    if (iResendCount > 0) {
        iResendSeqNext++;
        iTimerResend.FireIn(kResendTimeoutMs);
    }
    else {
        iResendSeqNext = 0;
        iSemResend.Signal();
    }
}

TUint ProtocolRaop::Delay(TUint aSamples)
{
    static const TUint kJiffiesPerSample = Jiffies::JiffiesPerSample(kSampleRate);
    return kJiffiesPerSample*aSamples;
}

TUint ProtocolRaop::TryStop(TUint aStreamId)
{
    LOG(kMedia, "ProtocolRaop::TryStop\n");
    TBool stop = false;
    AutoMutex a(iLockRaop);
    if (!iStopped && iActive) {
        stop = (iStreamId == aStreamId && aStreamId != IPipelineIdProvider::kStreamIdInvalid);
        if (stop) {
            iNextFlushId = iFlushIdProvider->NextFlushId();
            iStopped = true;
            DoInterrupt();
            iSem.Signal();
        }
    }
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

void ProtocolRaop::ReceiveResend(const RaopPacketAudio& aPacket)
{
    iLockRaop.Wait();
    if (iResendCount > 0) {
        if (aPacket.Header().Seq() == iResendSeqNext) {
            // Expected resend packet.

            iTimerResend.Cancel();

            iResendSeqNext++;
            iResendCount--;

            TBool shouldSignal = false;
            if (iResendCount == 0) {
                iResendSeqNext = 0;
                shouldSignal = true;
            }

            iLockRaop.Signal();

            OutputAudio(aPacket.Payload());

            if (shouldSignal) {
                iSemResend.Signal();
            }

            return;
        }
        else if (aPacket.Header().Seq() >= iResendSeqNext) {
            // Missed a resend packet.
            const TUint missCount = aPacket.Header().Seq()-iResendSeqNext;

            if (missCount > iResendCount) {
                // Something went very wrong or missed end of resend sequence. Abort resend.
                iTimerResend.Cancel();
                iResendSeqNext = 0;
                iResendCount = 0;
                // FIXME - notify pipeline of discontinuity.

                iSemResend.Signal();
            }
            else {
                // FIXME - notify pipeline of discontinuity.

                // Advance over missed packet.
                iResendSeqNext += missCount;
                iResendCount -= missCount;
            }
        }
        else { // aPacket.Header().Seq() >= iResendSeqNext
            // Bad sequence number. Ignore.

            // FIXME - notify pipeline of discontinuity.
        }
    }
    iLockRaop.Signal();
}

TUint ProtocolRaop::SendFlush(TUint aSeq, TUint aTime)
{
    LOG(kMedia, "ProtocolRaop::NotifySessionWait\n");
    AutoMutex a(iLockRaop);
    ASSERT(iActive);
    iFlushSeq = aSeq;
    iFlushTime = aTime;

    // Don't increment flush ID if current MsgFlush hasn't been output.
    if (iNextFlushId == MsgFlush::kIdInvalid) {
        iNextFlushId = iFlushIdProvider->NextFlushId();
        iWaiting = true;
    }

    // FIXME - clear any resend-related members here?

    DoInterrupt();
    return iNextFlushId;
}


// RaopControlServer

RaopControlServer::RaopControlServer(SocketUdpServer& aServer, IRaopResendReceiver& aResendReceiver)
    : iClientPort(kInvalidServerPort)
    , iServer(aServer)
    , iResendReceiver(aResendReceiver)
    , iLatency(0)
    , iLock("RACL")
    , iExit(false)
{
    iThread = new ThreadFunctor("RaopControlServer", MakeFunctor(*this, &RaopControlServer::Run), kPriority-1, kSessionStackBytes);
    iThread->Start();
}

RaopControlServer::~RaopControlServer()
{
    {
        AutoMutex a(iLock);
        iExit = true;
    }
    iServer.ReadInterrupt();
    iServer.ClearWaitForOpen();
    delete iThread;
}

void RaopControlServer::DoInterrupt()
{
    LOG(kMedia, "RaopControlServer::DoInterrupt\n");
    AutoMutex a(iLock);
    iClientPort = kInvalidServerPort;
}

void RaopControlServer::Reset(TUint aClientPort)
{
    AutoMutex a(iLock);
    iClientPort = aClientPort;
    iLatency = 0;
}

void RaopControlServer::Run()
{
    //LOG(kMedia, "RaopControlServer::Run\n");

    for (;;) {

        {
            AutoMutex a(iLock);
            if (iExit) {
                return;
            }
        }

        try {
            iServer.Read(iPacket);
            iEndpoint.Replace(iServer.Sender());
            try {
                RtpPacketRaop packet(iPacket);
                if (packet.Header().Type() == ESync) {
                    RaopPacketSync syncPacket(packet);

                    // Extension bit set on sync packet signifies stream (re-)starting.
                    // However, by it's nature, UDP is unreliable, so can't rely on this for detecting (re-)start.
                    //LOG(kMedia, "RaopControlServer::Run packet.Extension(): %u\n", packet.Header().Extension());

                    AutoMutex a(iLock);
                    TUint latency = iLatency;
                    iLatency = syncPacket.RtpTimestamp()-syncPacket.RtpTimestampMinusLatency();

                    if (iLatency != latency) {
                        LOG(kMedia, "RaopControlServer::Run Old latency: %u; New latency: %u\n", latency, iLatency);
                    }

                    //LOG(kMedia, "RaopControlServer::Run RtpTimestampMinusLatency: %u, NtpTimestampSecs: %u, NtpTimestampFract: %u, RtpTimestamp: %u, iLatency: %u\n", syncPacket.RtpTimestampMinusLatency(), syncPacket.NtpTimestampSecs(), syncPacket.NtpTimestampFract(), syncPacket.RtpTimestamp(), iLatency);
                }
                else if (packet.Header().Type() == EResendResponse) {
                    // Resend response packet contains a full audio packet as payload.
                    RaopPacketResendResponse resendResponsePacket(packet);
                    const RaopPacketAudio& audioPacket = resendResponsePacket.AudioPacket();
                    iResendReceiver.ReceiveResend(audioPacket);
                }
                else {
                    LOG(kMedia, "RaopControlServer::Run unexpected packet type: %u\n", packet.Header().Type());
                }

                iServer.ReadFlush();
            }
            catch (InvalidRaopPacket&) {
                LOG(kMedia, "RaopControlServer::Run caught InvalidRtpHeader\n");
                iServer.ReadFlush();    // Unexpected, so ignore.
            }
        }
        catch (ReaderError&) {
            LOG(kMedia, "RaopControlServer::Run caught ReaderError\n");
            iServer.ReadFlush();
            if (!iServer.IsOpen()) {
                iServer.WaitForOpen();
            }
        }
    }
}

TUint RaopControlServer::Latency() const
{
    AutoMutex a(iLock);
    return iLatency;
}

void RaopControlServer::RequestResend(TUint aSeqStart, TUint aCount)
{
    LOG(kMedia, "RaopControlServer::RequestResend aSeqStart: %u, aCount: %u\n", aSeqStart, aCount);

    RaopPacketResendRequest resendPacket(aSeqStart, aCount);
    Bws<RaopPacketResendRequest::kBytes> resendBuf;
    WriterBuffer writerBuffer(resendBuf);
    resendPacket.Write(writerBuffer);

    try {
        iLock.Wait();
        //iEndpoint.SetPort(iClientPort); // Send to client listening port.
        iLock.Signal();
        iServer.Send(resendBuf, iEndpoint);
    }
    catch (NetworkError) {
        // Will handle this by timing out on receive.
    }
}


// RaopAudioServer

RaopAudioServer::RaopAudioServer(SocketUdpServer& aServer)
    : iServer(aServer)
{
}

RaopAudioServer::~RaopAudioServer()
{
}

void RaopAudioServer::Reset()
{
    iInterrupted = false;
    iServer.ReadFlush();    // Set to read next udp packet.
}

void RaopAudioServer::DoInterrupt()
{
    LOG(kMedia, "RaopAudioServer::DoInterrupt()\n");
    iInterrupted = true;
    iServer.ReadInterrupt();
}

void RaopAudioServer::ReadPacket(Bwx& aBuf)
{
    //LOG(kMedia, ">RaopAudioServer::ReadPacket\n");

    for (;;) {
        try {
            iServer.Read(aBuf);
            iServer.ReadFlush();
            return;
        }
        catch (ReaderError&) {
            // Either no data, user abort or invalid header
            if (!iServer.IsOpen()) {
                LOG(kMedia, "RaopAudioServer::ReadPacket ReaderError RaopAudioServerServerClosed\n");
                iServer.ReadFlush();
                THROW(RaopAudioServerClosed);
            }
            if (iInterrupted) {
                LOG(kMedia, "RaopAudioServer::ReadPacket ReaderError iInterrupted %d\n", iInterrupted);
                iServer.ReadFlush();
                THROW(ReaderError);
            }
        }
        iServer.ReadFlush();  // Set to read next UDP packet.
    }
}


// RaopAudioDecryptor

void RaopAudioDecryptor::Init(const Brx& aAesKey, const Brx& aAesInitVector)
{
    iKey.Replace(aAesKey);
    iInitVector.Replace(aAesInitVector);
}

void RaopAudioDecryptor::Decrypt(const Brx& aEncryptedIn, Bwx& aAudioOut) const
{
    //LOG(kMedia, ">RaopAudioDecryptor::Decrypt aEncryptedIn.Bytes(): %u\n", aEncryptedIn.Bytes());
    ASSERT(iKey.Bytes() > 0);
    ASSERT(iInitVector.Bytes() > 0);
    ASSERT(aAudioOut.MaxBytes() >= kPacketSizeBytes+aEncryptedIn.Bytes());

    aAudioOut.SetBytes(0);
    WriterBuffer writerBuffer(aAudioOut);
    WriterBinary writerBinary(writerBuffer);
    writerBinary.WriteUint32Be(aEncryptedIn.Bytes());    // Write out payload size.

    unsigned char* inBuf = const_cast<unsigned char*>(aEncryptedIn.Ptr());
    unsigned char* outBuf = const_cast<unsigned char*>(aAudioOut.Ptr()+aAudioOut.Bytes());
    unsigned char initVector[16];
    memcpy(initVector, iInitVector.Ptr(), sizeof(initVector));  // Use same initVector at start of each decryption block.

    AES_cbc_encrypt(inBuf, outBuf, aEncryptedIn.Bytes(), (AES_KEY*)iKey.Ptr(), initVector, AES_DECRYPT);
    const TUint audioRemaining = aEncryptedIn.Bytes() % 16;
    const TUint audioWritten = aEncryptedIn.Bytes()-audioRemaining;
    if (audioRemaining > 0) {
        // Copy remaining audio to outBuf if <16 bytes.
        memcpy(outBuf+audioWritten, inBuf+audioWritten, audioRemaining);
    }
    aAudioOut.SetBytes(kPacketSizeBytes+aEncryptedIn.Bytes());
}
