#include <OpenHome/Av/Raop/ProtocolRaop.h>
#include <OpenHome/Av/Raop/UdpServer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Media/SupplyAggregator.h>

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

ProtocolRaop::ProtocolRaop(Environment& aEnv, Media::TrackFactory& aTrackFactory, IVolumeScalerEnabler& aVolume, IRaopDiscovery& aDiscovery, UdpServerManager& aServerManager, TUint aAudioId, TUint aControlId)
    : Protocol(aEnv)
    , iTrackFactory(aTrackFactory)
    , iVolumeEnabled(false)
    , iVolume(aVolume)
    , iDiscovery(aDiscovery)
    , iServerManager(aServerManager)
    , iAudioServer(iServerManager.Find(aAudioId))
    , iControlServer(iServerManager.Find(aControlId), *this)
    , iSupply(nullptr)
    , iLockRaop("PRAL")
    , iSemDrain("PRSD", 0)
    , iResendRangeRequester(iControlServer)
    , iRepairerTimer(aEnv, "PRRT")
    , iRepairer(aEnv, iResendRangeRequester, *this, iRepairerTimer)
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
    iRepairer.DropAudio();
}

void ProtocolRaop::Interrupt(TBool /*aInterrupt*/)
{
    {
        AutoMutex a(iLockRaop);
        iInterrupted = true;
    }
    DoInterrupt();
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
    iControlServer.Open();
    iAudioServer.Open();

    TBool start = true;


    // Output audio stream
    for (;;) {
        {
            // Can't hold lock while outputting to supply as may block pipeline
            // if callbacks come in, so do admin here before outputting msgs.
            TUint flushId = MsgFlush::kIdInvalid;
            TBool waiting = false;
            TBool stopped = false;
            TBool interrupted = false;
            TBool discontinuity = false;
            {
                AutoMutex a(iLockRaop);

                flushId = iNextFlushId;
                iNextFlushId = MsgFlush::kIdInvalid;

                if (iStopped) {
                    stopped = true;
                    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
                    iActive = false;
                }
                if (iWaiting) {
                    waiting = true;
                    iWaiting = false;
                }
                if (iInterrupted) {
                    interrupted = true;
                    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
                    iActive = false;
                    iStopped = true;
                }
                if (iDiscontinuity) {
                    discontinuity = true;
                    iDiscontinuity = false;
                }
            }


            if (flushId != MsgFlush::kIdInvalid) {
                iSupply->OutputFlush(flushId);

                if (stopped) {
                    WaitForDrain();
                    iDiscovery.Close();
                    LOG(kMedia, "<ProtocolRaop::Stream iStopped\n");
                    return EProtocolStreamStopped;
                }
                else if (waiting) {
                    OutputDiscontinuity();
                    // Resume normal operation.
                    LOG(kMedia, "ProtocolRaop::Stream signalled end of wait.\n");
                }
                else {
                    ASSERTS();  // Shouldn't be flushing in any other state.
                }
            }

            if (discontinuity) {
                OutputDiscontinuity();
                LOG(kMedia, "ProtocolRaop::Stream signalled end of starvation.\n");
            }

            if (interrupted) {
                return EProtocolStreamStopped;
            }
        }

        try {
            iPacketBuf.SetBytes(0);
            iAudioServer.ReadPacket(iPacketBuf);
            RtpPacketRaop rtpPacket(iPacketBuf);
            RaopPacketAudio audioPacket(rtpPacket);

            if (!iDiscovery.Active()) {
                LOG(kMedia, "ProtocolRaop::Stream() no active session\n");
                {
                    AutoMutex a(iLockRaop);
                    iActive = false;
                    iStopped = true;
                }

                iControlServer.Close();
                iAudioServer.Close();

                WaitForDrain();
                LOG(kMedia, "<ProtocolRaop::Stream !iDiscovery.Active()\n");
                iDiscovery.Close();
                return EProtocolStreamStopped;
            }

            if (ShouldFlush(audioPacket.Header().Seq(), audioPacket.Timestamp())) {
                continue;   // Flush this packet.
            }

            iLockRaop.Wait();
            const TBool resumePending = iResumePending;
            iLockRaop.Signal();
            if (start || resumePending) {
                LOG(kMedia, "ProtocolRaop::Stream starting new stream start: %u, resumePending: %u\n", start, resumePending);
                UpdateSessionId(audioPacket.Ssrc());
                iAudioDecryptor.Init(iDiscovery.Aeskey(), iDiscovery.Aesiv());

                Track* track = nullptr;
                TUint latency = 0;
                TUint streamId = 0;
                Uri uri;
                {
                    AutoMutex a(iLockRaop);
                    iResumePending = false;
                    iFlushSeq = 0;
                    iFlushTime = 0;

                    if (start) {
                        // Report blank URI.
                        track = iTrackFactory.CreateTrack(Brx::Empty(), Brx::Empty());
                        latency = iLatency = iControlServer.Latency();
                    }
                    // Always output a new stream ID on start or resume pending (to avoid CodecStreamCorrupt exceptions).
                    streamId = iStreamId = iIdProvider->NextStreamId();
                    uri.Replace(iUri.AbsoluteUri());
                }

                /*
                 * NOTE - outputting MsgTrack then MsgEncodedStream causes accumulated time reported by pipeline to be reset to 0.
                 * Not necessarily desirable when pausing or seeking.
                 */
                if (start) {
                    iSupply->OutputDelay(Delay(latency));
                    iSupply->OutputTrack(*track, !resumePending);
                    track->RemoveRef();
                }
                // Always output a new stream ID on start or resume pending (to avoid CodecStreamCorrupt exceptions).
                iSupply->OutputStream(uri.AbsoluteUri(), 0, 0, false, false, *this, streamId);
                OutputContainer(iDiscovery.Fmtp());

                start = false;
            }
            iDiscovery.KeepAlive();


            const TBool validSession = IsValidSession(audioPacket.Ssrc());
            const TBool shouldFlush = ShouldFlush(audioPacket.Header().Seq(), audioPacket.Timestamp());

            if (validSession && !shouldFlush) {
                IRepairable* repairable = iRepairableAllocator.Allocate(audioPacket);
                try {
                    iRepairer.OutputAudio(*repairable);
                }
                catch (RepairerBufferFull&) {
                    LOG(kMedia, "ProtocolRaop::Stream RepairerBufferFull\n");
                    // Set state so that no more audio is output until a MsgDrain followed by a MsgEncodedStream.
                    OutputDiscontinuity();
                }
                catch (RepairerStreamRestarted&) {
                    LOG(kMedia, "ProtocolRaop::Stream RepairerStreamRestarted\n");
                    OutputDiscontinuity();
                }
            }
        }
        catch (InvalidRaopPacket&) {
            LOG(kMedia, "ProtocolRaop::Stream Invalid Header\n");
            //break;
        }
        catch (NetworkError&) {
            LOG(kMedia, "ProtocolRaop::Stream Network error\n");
            //break;
        }
        catch (ReaderError&) {
            LOG(kMedia, "ProtocolRaop::Stream Reader error\n");
            // This can indicate an interrupt (caused by, e.g., a TryStop)
            // Continue around loop and see if iStopped has been set.
        }
        catch (HttpError&) {
            LOG(kMedia, "ProtocolRaop::Stream sdp not received\n");
            // ignore and continue - sender should stop on a closed connection! wait for sender to re-select device
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
    iLatency = iControlServer.Latency();    // Get last known (or default) latency.
    iFlushSeq = 0;
    iFlushTime = 0;
    iNextFlushId = MsgFlush::kIdInvalid;
    iActive = true;
    iWaiting = false;
    iResumePending = false;
    iStopped = false;
    iInterrupted = false;
    iDiscontinuity = false;
}

void ProtocolRaop::StartStream()
{
    LOG(kMedia, "ProtocolRaop::StartStream\n");
    TUint streamId = IPipelineIdProvider::kStreamIdInvalid;;
    {
        AutoMutex a(iLockRaop);
        iStreamId = iIdProvider->NextStreamId();
        streamId = iStreamId;
    }
    iSupply->OutputStream(iUri.AbsoluteUri(), 0, 0, false, false, *this, streamId);
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
    /*
     * Outputting delay mid-stream is causing VariableDelay to ramp audio up/down
     * mid-stream and immediately after unpausing/seeking.
     * That makes for an unpleasant listening experience. Better to just
     * potentially allow stream to go a few ms out of sync.
     */
    TBool outputDelay = false;
    TUint latency = iControlServer.Latency();
    {
        AutoMutex a(iLockRaop);
        if (latency != iLatency) {

            TUint diffSamples = 0;
            if (latency > iLatency) {
                diffSamples = latency - iLatency;
            }
            else {
                diffSamples = iLatency - latency;
            }
            //LOG(kMedia, "ProtocolRaop::OutputAudio diffSamples: %u\n", diffSamples);

            // Some senders may toggle latency by a small amount when unpausing.
            // To avoid unnecessary ramp down/up as delay changes, only change
            // if a threshold is exceeded.
            if (diffSamples >= kMinDelayChangeSamples) {
                iLatency = latency;
                outputDelay = true;
            }
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
    LOG(kMedia, ">ProtocolRaop::OutputDiscontinuity\n");
    iAudioServer.Close();
    iControlServer.Close();
    iRepairer.DropAudio();  // Drop any audio buffered in repairer.
    iSupply->Discard();

    {
        AutoMutex a(iLockRaop);
        iResumePending = true;
    }

    Semaphore sem("PRWS", 0);

    iSupply->OutputDrain(MakeFunctor(sem, &Semaphore::Signal));
    sem.Wait();

    // Only reopen audio server if a TryStop() hasn't come in.
    AutoMutex a(iLockRaop);
    if (!iStopped) {
        iControlServer.Open();
        iAudioServer.Open();
    }
    LOG(kMedia, "<ProtocolRaop::OutputDiscontinuity\n");
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
    static const TUint kJiffiesPerSample = Jiffies::PerSample(kSampleRate);
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
            // Lock doesn't need to be held for this; code that opens server from other thread must check iStopped before opening it.
            iControlServer.Close();
            iAudioServer.Close();
        }
    }
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

void ProtocolRaop::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    LOG(kMedia, ">ProtocolRaop::NotifyStarving mode: %.*s, sid: %u, starving: %u\n", PBUF(aMode), aStreamId, aStarving);
    AutoMutex a(iLockRaop);
    if (aStarving) {
        iDiscontinuity = true;
        DoInterrupt();
    }
}

void ProtocolRaop::ResendReceive(const RaopPacketAudio& aPacket)
{
    LOG(kMedia, ">ProtocolRaop::ResendReceive timestamp: %u, seq: %u\n", aPacket.Timestamp(), aPacket.Header().Seq());
    IRepairable* repairable = iRepairableAllocator.Allocate(aPacket);
    try {
        iRepairer.OutputAudio(*repairable);
    }
    catch (RepairerBufferFull&) {
        LOG(kMedia, "ProtocolRaop::ResendReceive RepairerBufferFull\n");
        AutoMutex a(iLockRaop);
        iDiscontinuity = true;
    }
    catch (RepairerStreamRestarted&) {
        LOG(kMedia, "ProtocolRaop::ResendReceive RepairerStreamRestarted\n");
        AutoMutex a(iLockRaop);
        iDiscontinuity = true;
    }
}

TUint ProtocolRaop::SendFlush(TUint aSeq, TUint aTime)
{
    LOG(kMedia, "ProtocolRaop::SendFlush\n");
    AutoMutex a(iLockRaop);

    if (!iActive) {
        // It's possible that the RAOP session is still active, so this is a
        // valid call from the source module, but the pipeline has been unable
        // to play the stream for some reason (network issue, change in
        // protocol) and TryStop() has been called which has caused Stream() to
        // return, so no valid flush can be sent.
        return MsgFlush::kIdInvalid;
    }

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
    , iLatency(kDefaultLatencySamples)
    , iLock("RACL")
    , iOpen(false)
    , iExit(false)
{
    iThread = new ThreadFunctor("RaopControlServer", MakeFunctor(*this, &RaopControlServer::Run), kPriority-1, kSessionStackBytes);
    iThread->Start();
}

void RaopControlServer::Open()
{
    AutoMutex a(iLock);
    if (!iOpen) {
        iServer.Open();
        iOpen = true;
    }
}

void RaopControlServer::Close()
{
    AutoMutex a(iLock);
    if (iOpen) {
        iServer.Close();
        iOpen = false;
    }
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
    //iLatency = kDefaultLatencySamples; // Persist previous latency on assumption that next device to connect will have same (or similar) latency to last device. Attempts to avoid audio ramp down/up caused by unnecessarily changing delay.
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
                    const TUint latency = iLatency;
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
                    iResendReceiver.ResendReceive(audioPacket);
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
    catch (NetworkError&) {
        // Will handle this by timing out on receive.
    }
}


// RaopResendRangeRequester

RaopResendRangeRequester::RaopResendRangeRequester(IRaopResendRequester& aResendRequester)
    : iResendRequester(aResendRequester)
{
}

void RaopResendRangeRequester::RequestResendSequences(const std::vector<const IResendRange*> aRanges)
{
    LOG(kMedia, ">RaopResendRangeRequester::RequestResendSequences");
    for (auto range : aRanges) {
        const TUint start = range->Start();
        const TUint end = range->End();
        const TUint count = (end-start)+1;  // +1 to include start packet.
        LOG(kMedia, " %d->%d", start, end);
        iResendRequester.RequestResend(start, count);
    }
    LOG(kMedia, "\n");
}


// RepairerTimer

RepairerTimer::RepairerTimer(Environment& aEnv, const TChar* aId)
    : iTimer(aEnv, MakeFunctor(*this, &RepairerTimer::TimerFired), aId)
{
}

RepairerTimer::~RepairerTimer()
{
    iTimer.Cancel();
}

void RepairerTimer::Start(Functor aFunctor, TUint aFireInMs)
{
    iFunctor = aFunctor;
    iTimer.FireIn(aFireInMs);
}

void RepairerTimer::Cancel()
{
    iTimer.Cancel();
}

void RepairerTimer::TimerFired()
{
    Functor functor = iFunctor;
    iFunctor = Functor();   // Clear iFunctor member here in case Start() is called within functor callback.
    functor();
}


// ResendRange

ResendRange::ResendRange()
    : iStart(0)
    , iEnd(0)
{
}

void ResendRange::Set(TUint aStart, TUint aEnd)
{
    iStart = aStart;
    iEnd = aEnd;
}

TUint ResendRange::Start() const
{
    return iStart;
}

TUint ResendRange::End() const
{
    return iEnd;
}


// RaopAudioServer

RaopAudioServer::RaopAudioServer(SocketUdpServer& aServer)
    : iServer(aServer)
    , iInterrupted(false)
    , iLock("RASL")
    , iOpen(false)
{
}

RaopAudioServer::~RaopAudioServer()
{
    iServer.ReadInterrupt();
    iServer.ClearWaitForOpen();
}

void RaopAudioServer::Open()
{
    AutoMutex a(iLock);
    if (!iOpen) {
        iServer.Open();
        iOpen = true;
    }
}

void RaopAudioServer::Close()
{
    AutoMutex a(iLock);
    if (iOpen) {
        iServer.Close();
        iOpen = false;
    }
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
        //if (iInterrupted) {
        //    THROW(ReaderError);
        //}
        try {
            iServer.Read(aBuf);
            iServer.ReadFlush();
            return;
        }
        catch (ReaderError&) {
            // Either no data, user abort or invalid header

            if (iInterrupted) {
                LOG(kMedia, "RaopAudioServer::ReadPacket ReaderError iInterrupted %d\n", iInterrupted);
            }
            iServer.ReadFlush();
            THROW(ReaderError);
        }
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
