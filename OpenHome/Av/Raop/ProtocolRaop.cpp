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
        THROW(InvalidRaopHeader);
    }
    if (iPayloadType > 0x7f) {
        THROW(InvalidRaopHeader);
    }
    if (iSequenceNumber > 0xffff)
    {
        THROW(InvalidRaopHeader);
    }
}

RtpHeaderRaop::RtpHeaderRaop(const Brx& aRtpHeader)
{
    if (aRtpHeader.Bytes() != kBytes) {
        THROW(InvalidRaopHeader);
    }

    const TUint version = (aRtpHeader[0] & 0xc0) >> 6;
    if (version != kVersion) {
        THROW(InvalidRaopHeader);
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
        THROW(InvalidRaopHeader);
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
        THROW(InvalidRaopHeader);
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
        THROW(InvalidRaopHeader);
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
        THROW(InvalidRaopHeader);
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
        THROW(InvalidRaopHeader);
    }

    const Brx& payload = iPacket.Payload();
    ReaderBuffer readerBuffer(payload);
    ReaderBinary readerBinary(readerBuffer);

    try {
        iTimestamp = readerBinary.ReadUintBe(4);
        iSsrc = readerBinary.ReadUintBe(4);
    }
    catch (ReaderError&) {
        THROW(InvalidRaopHeader);
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
    , iSupply(NULL)
    , iLockRaop("PRAL")
    , iSem("PRAS", 0)
    , iSemInputChanged("PRIC", 0)
    , iTimerResend(aEnv, MakeFunctor(*this, &ProtocolRaop::TimerFired), "ProtocolRaopResendTimer")
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
    LOG(kMedia, "ProtocolRaop::Stream ");
    LOG(kMedia, aUri);
    LOG(kMedia, "\n");

    iLockRaop.Wait();

    try {
        iUri.Replace(aUri);
    }
    catch (UriError&) {
        LOG(kMedia, "ProtocolRaop::Stream unable to parse URI\n");
        return EProtocolErrorNotSupported;
    }

    // RAOP doesn't actually stream from a URI, so just expect a dummy URI.
    if (iUri.Scheme() != Brn("raop")) {
        LOG(kMedia, "ProtocolRaop::Stream Scheme not recognised\n");
        AutoMutex a(iLockRaop);
        iActive = false;
        iStopped = true;
        return EProtocolErrorNotSupported;
    }

    iSessionId = 0;
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iFlushSeq = iFlushTime = 0;
    iNextFlushId = MsgFlush::kIdInvalid;
    iWaiting = iResumePending = iStreamStart = iStopped = false;
    iActive = true;
    iLockRaop.Signal();

    // Parse URI to get client control/timing ports.
    // (Timing channel isn't monitored, so don't bother parsing port.)
    Parser p(aUri);
    p.Forward(7);   // skip raop://
    Brn ctrlPortBuf = p.Next('.');
    TUint ctrlPort = Ascii::Uint(ctrlPortBuf);

    TBool start = true;
    TUint aesSid = 0;
    iAudioServer.Reset();
    iControlServer.Reset(ctrlPort);
    Brn audio;
    TUint seqExpected = 0;
    iSem.Clear();

    WaitForChangeInput();

    // Output the delay before MsgEncodedStream - otherwise, the MsgDelay may
    // be pulled while the CodecController is attempting to Read(), causing a
    // CodecStreamEnded.
    //
    // FIXME - what about when a stream is paused and resumed, or skipped (as a
    // new MsgTrack is not currently sent out, so the new MsgDelay appears in
    // the middle of a stream, causing the condition above.)
    iSupply->OutputDelay(kDelayJiffies);

    StartStream();

    // Output audio stream
    for (;;) {
        {
            AutoMutex a(iLock);
            if (iWaiting) {
                iSupply->OutputFlush(iNextFlushId);
                iNextFlushId = MsgFlush::kIdInvalid;
                iWaiting = false;
                iResumePending = true;
                // Resume normal operation.
            }
            else if (iStopped) {
                iStreamId = IPipelineIdProvider::kStreamIdInvalid;
                iSupply->OutputFlush(iNextFlushId);
                iNextFlushId = MsgFlush::kIdInvalid;
                iActive = false;
                WaitForChangeInput();
                LOG(kMedia, "<ProtocolRaop::Stream iStopped\n");
                return EProtocolStreamStopped;
            }
        }

        try {
            iPacketBuf.SetBytes(0);
            iAudioServer.ReadPacket(iPacketBuf);

            RtpPacketRaop rtpPacket(iPacketBuf);
            RaopPacketAudio audioPacket(rtpPacket);
            UpdateSessionId(audioPacket);
            // FIXME - have a CheckSessionId that throws InvalidSessionId instead of having lots of if clauses?

            const TUint seqLast = audioPacket.Header().Seq();

            if (!iDiscovery.Active()) {
                LOG(kMedia, "ProtocolRaop::Stream() no active session\n");
                iLockRaop.Wait();
                iActive = false;
                iStopped = true;
                iLockRaop.Signal();
                WaitForChangeInput();
                LOG(kMedia, "<ProtocolRaop::Stream !iDiscovery.Active()\n");
                return EProtocolStreamStopped;
            }

            // FIXME - this key setup is only done once per connection.
            // Probably need to keep it between ProtocolRaop::Stream() runs in case NetAux source is switched away from and moved back to.
            iDiscovery.KeepAlive(); // FIXME - why is this called here and not by discovery thread?

            if(aesSid != iDiscovery.AesSid()) {
                aesSid = iDiscovery.AesSid();       // aes key has been updated

                LOG(kMedia, "ProtocolRaop::Stream() new sid\n");

                iAudioDecryptor.Init(iDiscovery.Aeskey(), iDiscovery.Aesiv());
            }
            if(start) {
                LOG(kMedia, "ProtocolRaop::Stream() new container\n");
                start = false;        // create dummy container for codec recognition and initialisation
                OutputContainer(Brn(iDiscovery.Fmtp()));
                seqExpected = seqLast;   // Init seqExpected.
            }

            TBool sessionValid = false;
            {
                AutoMutex a(iLock);
                if (iSessionId == audioPacket.Ssrc()) {
                    sessionValid = true;
                }
            }

            if (sessionValid) {
                TBool shouldFlush = false;
                {
                    AutoMutex a(iLock);
                    if (iResumePending) {
                        const TBool seqInFlushRange = (audioPacket.Header().Seq() <= iFlushSeq);
                        const TBool timeInFlushRange = (audioPacket.Timestamp() <= iFlushTime);
                        shouldFlush = (seqInFlushRange && timeInFlushRange);
                    }
                }

                if (!shouldFlush) {
                    if (seqLast == seqExpected) {
                        // The packet that was expected.
                        iAudioDecryptor.Decrypt(audioPacket.Payload(), iAudioDecrypted);
                        OutputAudio(iAudioDecrypted);
                        seqExpected++;
                    }
                    else if (seqLast > seqExpected) {
                        // Missed some packets.
                        const TUint missed = seqLast-seqExpected;
                        Log::Print("missed: %u\n", missed);
                        {
                            AutoMutex a(iLockRaop);
                            iResendSeqNext = seqExpected;
                            iResendCount = missed;
                            iTimerResend.FireIn(kResendTimeoutMs);
                            iControlServer.RequestResend(seqExpected, missed);
                            // Callbacks will come via ::ReceiveResend().
                        }
                        iSemResend.Wait();
                    }
                    else {
                        // Packet is one that's already been seen. Ignore.
                    }
                }
            }
        }
        catch (InvalidRaopHeader&) {
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

void ProtocolRaop::StartStream()
{
    LOG(kMedia, "ProtocolRaop::StartStream\n");
    AutoMutex a(iLockRaop);
    iStreamId = iIdProvider->NextStreamId();
    iSupply->OutputStream(iUri.AbsoluteUri(), 0, false, false, *this, iStreamId);
}

void ProtocolRaop::UpdateSessionId(const RaopPacketAudio& aPacket)
{
    const TUint sessionId = aPacket.Ssrc();
    AutoMutex a(iLock);
    if (iSessionId == 0) {
        // Initialise session ID.
        iSessionId = sessionId;
        LOG(kMedia, "ProtocolRaop::UpdateSessionId new iSessionId: %u\n", iSessionId);
    }
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

void ProtocolRaop::OutputAudio(const Brx& aPacket)
{
    // FIXME - remove iResumePending

    // FIXME - could not wait for streamStart notification and just assume any new audio is start of new stream (because might miss control packet with FIRST flag set).
    // However, FLUSH request contains a last seqnum and last RTP time. Pass these in and refuse to output audio until passed last seqnum.

    iLockRaop.Wait();
    const TUint streamStart = iStreamStart;
    iStreamStart = false;
    iLockRaop.Signal();

    if (streamStart) {
        const TBool startOfStream = false;  // FIXME - will this be output before first audio packet? If so, must be able to set startOfStream = true.

        iLockRaop.Wait();
        Track* track = iTrackFactory.CreateTrack(iUri.AbsoluteUri(), Brx::Empty());
        iStreamId = iIdProvider->NextStreamId();
        const TUint streamId = iStreamId;
        Uri uri(iUri);
        iLockRaop.Signal();

        iSupply->OutputSession();
        iSupply->OutputTrack(*track, startOfStream);
        iSupply->OutputStream(uri.AbsoluteUri(), 0, false, false, *this, streamId);
        OutputContainer(iDiscovery.Fmtp());

        track->RemoveRef();
    }
    iSupply->OutputData(aPacket);
}

void ProtocolRaop::WaitForChangeInput()
{
    //iSemInputChanged.Clear();
    //iSupply->OutputChangeInput(MakeFunctor(*this, &ProtocolRaop::InputChanged));
    //iSemInputChanged.Wait();
}

void ProtocolRaop::InputChanged()
{
    AutoMutex a(iLock);
    iVolumeEnabled = !iVolumeEnabled;   // Toggle volume.
    iVolume.SetVolumeEnabled(iVolumeEnabled);
    iSemInputChanged.Signal();
}

void ProtocolRaop::TimerFired()
{
    // FIXME - should probably notify pipeline of discontinuity if timer fires.
    AutoMutex a(iLock);
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

TUint ProtocolRaop::TryStop(TUint aStreamId)
{
    LOG(kMedia, "ProtocolRaop::TryStop\n");
    TBool stop = false;
    AutoMutex a(iLock);
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
    AutoMutex a(iLockRaop);
    if (iResendCount > 0) {
        if (aPacket.Header().Seq() == iResendSeqNext) {
            // Expected resend packet.

            iTimerResend.Cancel();

            iAudioDecryptor.Decrypt(aPacket.Payload(), iAudioDecrypted);
            OutputAudio(iAudioDecrypted);   // FIXME - probably don't lock around this.

            iResendSeqNext++;
            iResendCount--;
            if (iResendCount == 0) {
                iResendSeqNext = 0;
                iSemResend.Signal();
            }
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
}

TUint ProtocolRaop::SendFlush(TUint aSeq, TUint aTime)
{
    LOG(kMedia, "ProtocolRaop::NotifySessionWait\n");
    AutoMutex a(iLockRaop);
    ASSERT(iActive);
    iFlushSeq = aSeq;
    iFlushTime = aTime;
    iNextFlushId = iFlushIdProvider->NextFlushId();
    iWaiting = true;
    DoInterrupt();
    return iNextFlushId;
}


//// RaopResendHandler
//
//RaopResendHandler::RaopResendHandler(IRaopResendRequester& aResendRequester, IRaopResendReceiver& aResendReceiver)
//{
//
//}
//
//void RaopResendHandler::RequestResend(TUint aSeqStart, TUint aCount)
//{
//
//}
//
//void RaopResendHandler::ReceiveResend(const RtpPacketRaop& aPacket)
//{
//
//}
//
//void RaopResendHandler::TimerFired()
//{
//    // Didn't receive an expected resend.
//}
//
//private:
//    IRaopResendRequester& iRequester;
//    IRaopResendReceiver& iReceiver;
//    TUint iSeqNext;
//    TUint iCount;
//    Timer* iTimer;
//    Mutex iLock;
//};


// RaopControlServer

RaopControlServer::RaopControlServer(SocketUdpServer& aServer, IRaopResendReceiver& aResendReceiver)
    : iClientPort(kInvalidServerPort)
    , iServer(aServer)
    , iResendReceiver(aResendReceiver)
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
}

void RaopControlServer::Run()
{
    LOG(kMedia, "RaopControlServer::Run\n");

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
                    // However, by it's nature, UDP is unreliable, so can't rely on acting on this for detecting (re-)start.
                    LOG(kMedia, "RaopControlServer::Run packet.Extension(): %u\n", packet.Header().Extension());

                    // FIXME - require this?
                    //TUint mclk = iI2sDriver.MclkCount();  // record current mclk count at dac - use this to calculate the drift
                    //mclk /= 256;  // convert to samples
                    iLock.Wait();
                    iLatency = syncPacket.RtpTimestamp()-syncPacket.RtpTimestampMinusLatency();
                    //iSenderSkew = rtpTimestamp - mclk;   // calculate count when this should play relative to current mclk count
                    iLock.Signal();
                    LOG(kMedia, "RaopControlServer::Run rtpTimestamp: %u, ntpTimeSecs: %u, ntpTimeSecsFract: %u, rtpTimestampNextPacket: %u, iLatency: %u, iSenderSkew: %u\n", syncPacket.RtpTimestampMinusLatency(), syncPacket.NtpTimestampSecs(), syncPacket.NtpTimestampFract(), syncPacket.RtpTimestamp(), iLatency, iSenderSkew);
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
            catch (InvalidRaopHeader& aInvalidHeader) {
                aInvalidHeader;
                LOG(kMedia, "RaopControlServer::Run caught InvalidRtpHeader\n");
                iServer.ReadFlush();   // Unexpected, so ignore.
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

void RaopControlServer::Time(TUint& aSenderSkew, TUint& aLatency)
{
    AutoMutex a(iLock);
    aSenderSkew = iSenderSkew;
    aLatency = iLatency;
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
    LOG(kMedia, ">RaopAudioServer::ReadPacket\n");

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
    LOG(kMedia, ">RaopAudioDecryptor::Decrypt aEncryptedIn.Bytes(): %u\n", aEncryptedIn.Bytes());
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
