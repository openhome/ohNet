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
    , iControlServer(iServerManager.Find(aControlId))
    , iSupply(nullptr)
    , iLockRaop("PRAL")
    , iSem("PRAS", 0)
    , iSemDrain("PRSD", 0)
    , iSeqExpected(0)
    , iResendTimer(aEnv, "PRRT")
    , iResendHandler(iControlServer, iResendTimer)
    , iSemResend("PRRS", 0)
{
    iControlServer.RegisterResendObserver(iResendHandler);
    iResendHandler.RegisterObserver(*this);
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
    iResendHandler.Interrupt();
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
                iSeqExpected = seqLast;   // Init seqExpected.
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
                if (seqLast == iSeqExpected) {
                    // The packet that was expected.
                    OutputAudio(audioPacket.Payload());
                    iSeqExpected++;
                }
                else if (seqLast > iSeqExpected) {
                    // Missed some packets.
                    const TUint missed = seqLast-iSeqExpected;
                    LOG(kMedia, "ProtocolRaop::Stream missed %u audio packets\n", missed);
                    Log::Print("ProtocolRaop::Stream expected audio packet: %u, got audio packet: %u\n", iSeqExpected, seqLast);

                    iResendHandler.RequestResend(iSeqExpected, missed);
                    // Callbacks will come via ::ReceiveResend().

                    // No need to notify of discontinuity here; might manage to recover if packets are resent.
                    iSemResend.Wait();  // Only signalled once resent packets have been received and/or timed out.

                    if (seqLast != iSeqExpected) {
                        // Still a packet discontinuity.
                        OutputDiscontinuity();
                    }

                    if (seqLast >= iSeqExpected) {
                        // Now, send out packet that followed discontinuity.
                        Log::Print("ProtocolRaop::Stream resend complete. Outputting seq: %u\n", audioPacket.Header().Seq());
                        iSeqExpected = audioPacket.Header().Seq()+1; // Jump over missed packets that have now been resent/dropped.
                        OutputAudio(audioPacket.Payload());
                    }
                    else {
                        ASSERTS();
                        // Shouldn't happen, but log anyway.
                        LOG(kMedia, "ProtocolRaop::Stream resend complete. Had packet %u, but iSeqExpected is now %u\n", seqLast, iSeqExpected);
                    }

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

void ProtocolRaop::OutputDiscontinuity()
{
    iSupply->OutputStreamInterrupted();
    TUint streamId = 0;
    Uri uri;
    {
        AutoMutex a(iLock);
        streamId = iStreamId = iIdProvider->NextStreamId();
        uri.Replace(iUri.AbsoluteUri());
    }
    // NOTE - if there is a very high rate of drop-outs, could potentially exhaust MsgEncodedStream allocator.
    iSupply->OutputStream(uri.AbsoluteUri(), 0, false, false, *this, streamId);
    // Allow stream to be re-recognised.
    OutputContainer(iDiscovery.Fmtp());
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

void ProtocolRaop::ResendReceive(const RaopPacketAudio& aPacket)
{
    Log::Print(">ProtocolRaop::ReceiveResend timestamp: %u, seq: %u\n", aPacket.Timestamp(), aPacket.Header().Seq());

    const TUint seq = aPacket.Header().Seq();
    if (seq == iSeqExpected) {
        OutputAudio(aPacket.Payload());
        iSeqExpected++;
    }
    else if (seq > iSeqExpected) {
        // Missed a packet.
        // Output this and update iSeqExpected accordingly.
        OutputDiscontinuity();
        OutputAudio(aPacket.Payload());
        iSeqExpected = seq+1;
    }
    else {
        // Packet that preceded current packet in sequence. Ignore.
    }
}

void ProtocolRaop::ResendComplete()
{
    iSemResend.Signal();
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


// RaopTimer

RaopTimer::RaopTimer(Environment& aEnv, const TChar* aId)
    : iTimer(aEnv, MakeFunctor(*this, &RaopTimer::TimerFired), aId)
{
}

void RaopTimer::Start(Functor aFunctor, TUint aFireInMs)
{
    iFunctor = aFunctor;
    iTimer.FireIn(aFireInMs);
}

void RaopTimer::Cancel()
{
    iTimer.Cancel();
}

void RaopTimer::TimerFired()
{
    iFunctor();
    iFunctor = Functor();
}


// RaopResendHandler

RaopResendHandler::RaopResendHandler(IRaopResendRequester& aRequester, IRaopTimer& aTimer)
    : iRequester(aRequester)
    , iObserver(nullptr)
    , iTimer(aTimer)
    , iSeqNext(0)
    , iCount(0)
    , iLock("RRHL")
{
}

void RaopResendHandler::RegisterObserver(IRaopResendBlockObserver& aObserver)
{
    ASSERT(iObserver == nullptr);
    iObserver = &aObserver;
}

void RaopResendHandler::Interrupt()
{
    ASSERT(iObserver == nullptr);
    AutoMutex a(iLock);
    iTimer.Cancel();
    iCount = 0;
    iSeqNext = 0;
    iObserver->ResendComplete();
}

void RaopResendHandler::RequestResend(TUint aSeqStart, TUint aCount)
{
    iSeqNext = aSeqStart;
    iCount = aCount;
    iTimer.Start(MakeFunctor(*this, &RaopResendHandler::TimerFired), kTimeoutMs);
    iRequester.RequestResend(aSeqStart, aCount);
}

void RaopResendHandler::ResendReceive(const RaopPacketAudio& aPacket)
{
    TBool outputAudio = false;
    TBool shouldSignal = false;
    ASSERT(iObserver != nullptr);

    {
        AutoMutex a(iLock);
        Log::Print(">RaopResendHandler::ReceiveResend timestamp: %u, seq: %u, iResendSeqNext %u, iResendCount: %u\n", aPacket.Timestamp(), aPacket.Header().Seq(), iSeqNext, iCount);

        if (iCount > 0) {
            if (aPacket.Header().Seq() == iSeqNext) {
                // Expected resend packet.
                iTimer.Cancel();
                iCount--;
                if (iCount == 0) {
                    iSeqNext = 0;
                }
                else {
                    iSeqNext++;
                }
                outputAudio = true;
            }
            else if (aPacket.Header().Seq() >= iSeqNext) {
                // Missed a resend packet.
                iTimer.Cancel();
                const TUint missCount = aPacket.Header().Seq()-iSeqNext;

                if (missCount > iCount) {
                    // Something went very wrong or missed end of resend sequence.
                    // Abort resend and don't output this packet.
                    iSeqNext = 0;
                    iCount = 0;
                }
                else {
                    // Advance over missed packet.
                    iSeqNext += missCount;
                    iCount -= missCount;
                    outputAudio = true;
                }
            }
            else { // aPacket.Header().Seq() >= iResendSeqNext
                // Bad sequence number. Ignore.
            }

            if (iCount == 0) {
                iSeqNext = 0;
                shouldSignal = true;
            }
            else {
                // Start timer for next resend packet.
                iTimer.Start(MakeFunctor(*this, &RaopResendHandler::TimerFired), kTimeoutMs);
            }
        }
    }

    if (outputAudio) {
        Log::Print("RaopResendHandler::ReceiveResend outputting audio; seq: %u\n", aPacket.Header().Seq());
        iObserver->ResendReceive(aPacket);
    }
    if (shouldSignal) {
        Log::Print("RaopResendHandler::ReceiveResend end of resend sequence; seq: %u\n", aPacket.Header().Seq());
        iObserver->ResendComplete();
    }
}

void RaopResendHandler::TimerFired()
{
    Log::Print(">RaopResendHandler::TimerFired\n");
    // Timer may fire for each resend packet.

    ASSERT(iObserver != nullptr);
    AutoMutex a(iLock);
    if (iCount > 0) {
        iCount--;
    }
    else {
        // Weren't expecting any packets.
        return;
    }

    if (iCount > 0) {
        iSeqNext++;
        iTimer.Start(MakeFunctor(*this, &RaopResendHandler::TimerFired), kTimeoutMs);
    }
    else {
        // Resend sequence complete.
        iSeqNext = 0;
        iObserver->ResendComplete();
    }
}


// RaopControlServer

RaopControlServer::RaopControlServer(SocketUdpServer& aServer)
    : iClientPort(kInvalidServerPort)
    , iServer(aServer)
    , iResendReceiver(nullptr)
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

void RaopControlServer::RegisterResendObserver(IRaopResendReceiver& aReceiver)
{
    ASSERT(iResendReceiver == nullptr);
    iResendReceiver = &aReceiver;
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
                    ASSERT(iResendReceiver != nullptr);
                    // Resend response packet contains a full audio packet as payload.
                    RaopPacketResendResponse resendResponsePacket(packet);
                    const RaopPacketAudio& audioPacket = resendResponsePacket.AudioPacket();
                    iResendReceiver->ResendReceive(audioPacket);
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
