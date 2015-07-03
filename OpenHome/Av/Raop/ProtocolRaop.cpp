#include <OpenHome/Av/Raop/ProtocolRaop.h>
#include <OpenHome/Av/Raop/UdpServer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Media/SupplyAggregator.h>

EXCEPTION(ResendTimeout);
EXCEPTION(ResendInvalid);
EXCEPTION(InvalidHeader);   // FIXME - remove
EXCEPTION(InvalidRtpHeader)
EXCEPTION(RaopAudioServerClosed);

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;


// RtpHeaderFixed

RtpHeaderFixed::RtpHeaderFixed()
{
}

RtpHeaderFixed::RtpHeaderFixed(const Brx& aRtpHeader)
{
    Replace(aRtpHeader);
}

void RtpHeaderFixed::Replace(const Brx& aRtpHeader)
{
    if (aRtpHeader.Bytes() != kHeaderBytes) {
        THROW(InvalidRtpHeader);
    }

    iVersion = (aRtpHeader[0] & 0xc0) >> 6;
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
        iTimestamp = readerBinary.ReadUintBe(4);
        iSsrc = readerBinary.ReadUintBe(4);
    }
    catch (ReaderError&) {
        THROW(InvalidRtpHeader);
    }
}

void RtpHeaderFixed::Clear()
{
    iVersion = 0;
    iPadding = 0;
    iExtension = 0;
    iCsrcCount = 0;
    iMarker = 0;
    iPayloadType = 0;
    iSequenceNumber = 0;
    iTimestamp = 0;
    iSsrc = 0;
}

TBool RtpHeaderFixed::Padding() const
{
    return iPadding;
}

TBool RtpHeaderFixed::Extension() const
{
    return iExtension;
}

TUint RtpHeaderFixed::CsrcCount() const
{
    return iCsrcCount;
}

TBool RtpHeaderFixed::Marker() const
{
    return iMarker;
}

TUint RtpHeaderFixed::Type() const
{
    return iPayloadType;
}

TUint RtpHeaderFixed::Seq() const
{
    return iSequenceNumber;
}

TUint RtpHeaderFixed::Timestamp() const
{
    return iTimestamp;
}

TUint RtpHeaderFixed::Ssrc() const
{
    return iSsrc;
}


// RtpPacketRaop

RtpPacketRaop::RtpPacketRaop()
{
}

RtpPacketRaop::RtpPacketRaop(const Brx& aRtpPacket)
{
    Replace(aRtpPacket);
}

void RtpPacketRaop::Replace(const Brx& aRtpPacket)
{
    iHeader.Replace(Brn(aRtpPacket.Ptr(), RtpHeaderFixed::kHeaderBytes));
    const TUint offset = RtpHeaderFixed::kHeaderBytes;
    iPayload.Replace(aRtpPacket.Ptr()+offset, aRtpPacket.Bytes()-offset);
}

void RtpPacketRaop::Clear()
{
    iHeader.Clear();
    iPayload.Replace(Brx::Empty());
}

const RtpHeaderFixed& RtpPacketRaop::Header() const
{
    return iHeader;
}

const Brx& RtpPacketRaop::Payload() const
{
    return iPayload;
}


// RtpPacket

RtpPacket::RtpPacket(const Brx& aRtpPacket)
    : iHeader(Brn(aRtpPacket.Ptr(), RtpHeaderFixed::kHeaderBytes))
{
    static const TUint offset = RtpHeaderFixed::kHeaderBytes;
    Brn packetRemaining(aRtpPacket.Ptr()+offset, aRtpPacket.Bytes()-offset);
    ReaderBuffer readerBuffer(packetRemaining);
    ReaderBinary readerBinary(readerBuffer);

    try {
        const TUint kHeaderSizeIncCsrc = RtpHeaderFixed::kHeaderBytes+iHeader.CsrcCount()*4;
        if (aRtpPacket.Bytes() < kHeaderSizeIncCsrc) {
            // Not enough bytes in packet to satisfy reported CRSC count.
            THROW(InvalidRtpHeader);
        }
        for (TUint i=0; i<iHeader.CsrcCount(); i++) {
            iCsrc.push_back(readerBinary.ReadUintBe(4));
        }

        TUint headerSizeFull = kHeaderSizeIncCsrc;
        if (iHeader.Extension()) {
            const TUint kHeaderSizeInclHeaderExtension = kHeaderSizeIncCsrc+4;
            if (aRtpPacket.Bytes() < kHeaderSizeInclHeaderExtension) {
                THROW(InvalidRtpHeader);
            }
            iHeaderExtensionProfile = readerBinary.ReadUintBe(2);
            iHeaderExtensionBytes = readerBinary.ReadUintBe(2)*4;

            headerSizeFull = kHeaderSizeInclHeaderExtension+iHeaderExtensionBytes;
            if (aRtpPacket.Bytes() < headerSizeFull) {
                THROW(InvalidRtpHeader);
            }
            iData.Replace(aRtpPacket.Ptr()+kHeaderSizeInclHeaderExtension, iHeaderExtensionBytes);
        }

        TUint paddingBytes = 0;
        if (iHeader.Padding()) {
            paddingBytes = aRtpPacket[aRtpPacket.Bytes()-1];
        }

        const TUint kPayloadBytes = aRtpPacket.Bytes()-headerSizeFull-paddingBytes;
        if (kPayloadBytes == 0 || aRtpPacket.Bytes() != headerSizeFull+kPayloadBytes+paddingBytes) {
            THROW(InvalidRtpHeader);
        }
        iData.Append(aRtpPacket.Ptr()+headerSizeFull, kPayloadBytes);
        iPayload.Set(iData.Ptr()+iHeaderExtensionBytes, iData.Bytes()-iHeaderExtensionBytes);
    }
    catch (ReaderError&) {
        THROW(InvalidRtpHeader);
    }
}

const RtpHeaderFixed& RtpPacket::Header() const
{
    return iHeader;
}

const Brx& RtpPacket::Payload() const
{
    return iPayload;
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
    , iControlServer(iServerManager.Find(aControlId), *this, *this)
    , iSupply(NULL)
    , iLockRaop("PRAL")
    , iSem("PRAS", 0)
    , iSemInputChanged("PRIC", 0)
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
            iAudioServer.ReadPacket(iAudioPacket);
            const TUint seqLast = iAudioPacket.Header().Seq();

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


            TBool shouldFlush = false;
            {
                AutoMutex a(iLock);
                if (iResumePending) {
                    const TBool seqInFlushRange = (iAudioPacket.Header().Seq() <= iFlushSeq);
                    const TBool timeInFlushRange = (iAudioPacket.Header().Timestamp() <= iFlushTime);
                    shouldFlush = (seqInFlushRange && timeInFlushRange);
                }
            }


            if (seqLast == seqExpected) {
                // The packet that was expected.
                iAudioDecryptor.Decrypt(iAudioPacket.Payload(), iAudioDecrypted);
                OutputAudio(iAudioDecrypted);
                seqExpected++;
            }
            else if (seqLast > seqExpected) {
                // Missed some packets.
                const TUint missed = seqLast-seqExpected;
                {
                    AutoMutex a(iLockRaop);
                    iResendSeqNext = seqExpected;
                    iResendCount = missed;
                    iTimerResend->FireIn(kResendTimeoutMs);
                    iControlServer.RequestResend(seqExpected, missed);
                    // Callbacks will come via ::ReceiveResend().
                }
                iSemResend.Wait();
            }
            else {
                // Packet is one that's already been seen. Ignore.
            }
        }
        catch (InvalidRtpHeader&) { 
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
        iTimerResend->FireIn(kResendTimeoutMs);
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

void ProtocolRaop::AudioResuming()
{
    AutoMutex a(iLockRaop);
    iStreamStart = true;
}

void ProtocolRaop::ReceiveResend(const RtpPacketRaop& aPacket)
{
    AutoMutex a(iLockRaop);
    if (iResendCount > 0) {
        if (aPacket.Header().Seq() == iResendSeqNext) {
            // Expected resend packet.

            iTimerResend->Cancel();

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
                iTimerResend->Cancel();
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

RaopControlServer::RaopControlServer(SocketUdpServer& aServer, IRaopAudioResumer& aAudioResumer, IRaopResendReceiver& aResendReceiver)
    : iClientPort(kInvalidServerPort)
    , iServer(aServer)
    , iAudioResumer(aAudioResumer)
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
                    Log::Print("RaopControlServer::Run packet.Extension(): %u\n", packet.Header().Extension());
                    if (packet.Header().Extension()) {
                        // (Re-)start of stream.
                        iAudioResumer.AudioResuming();
                    }

                    const TUint rtpTimestamp = packet.Header().Timestamp();
                    const Brx& payload = packet.Payload();
                    const TUint ntpTimeSecs = packet.Header().Ssrc();
                    const TUint ntpTimeSecsFract = Converter::BeUint32At(payload, 0);
                    const TUint rtpTimestampNextPacket = Converter::BeUint32At(payload, 4);

                    // FIXME - require this?
                    //TUint mclk = iI2sDriver.MclkCount();  // record current mclk count at dac - use this to calculate the drift
                    //mclk /= 256;  // convert to samples
                    iLock.Wait();
                    iLatency = rtpTimestampNextPacket-rtpTimestamp;
                    //iSenderSkew = rtpTimestamp - mclk;   // calculate count when this should play relative to current mclk count
                    iLock.Signal();
                    LOG(kMedia, "RaopControlServer::Run rtpTimestamp: %u, ntpTimeSecs: %u, ntpTimeSecsFract: %u, rtpTimestampNextPacket: %u, iLatency: %u, iSenderSkew: %u\n", rtpTimestamp, ntpTimeSecs, ntpTimeSecsFract, rtpTimestampNextPacket, iLatency, iSenderSkew);

                    payload;
                }
                else if (packet.Header().Type() == EResendResponse) {
                    iResendReceiver.ReceiveResend(packet);
                }
                else {
                    LOG(kMedia, "RaopControlServer::Run unexpected packet type: %u\n", packet.Header().Type());
                }

                iServer.ReadFlush();
            }
            catch (InvalidRtpHeader& aInvalidHeader) {
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

    // FIXME - construct an RtpPacket object, and have it write itself out to buffer.
    Bws<16> request(Brn(""));
    request.Append((TByte)0x80);
    request.Append((TByte)0xD5);
    request.Append((TByte)0x00);
    request.Append((TByte)0x01);
    request.Append((TByte)((aSeqStart >> 8) & 0xff));
    request.Append((TByte)((aSeqStart)& 0xff));
    request.Append((TByte)((aCount >> 8) & 0xff));
    request.Append((TByte)((aCount)& 0xff));

    try {
        iLock.Wait();
        iEndpoint.SetPort(iClientPort); // Send to client listening port.
        iLock.Signal();
        iServer.Send(request, iEndpoint);
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
    iDataBuffer.SetBytes(0);
    iSessionId = 0;
    iInterrupted = false;
    iServer.ReadFlush();    // Set to read next udp packet.
}

void RaopAudioServer::DoInterrupt()
{
    LOG(kMedia, "RaopAudioServer::DoInterrupt()\n");
    iInterrupted = true;
    iServer.ReadInterrupt();
}

void RaopAudioServer::ReadPacket(RtpPacketRaop& aPacket)
{
    LOG(kMedia, ">RaopAudioServer::ReadPacket\n");
    TUint seq = 0;

    for (;;) {
        try {
            aPacket.Clear();
            iServer.Read(iDataBuffer);
            aPacket.Replace(iDataBuffer);
        }
        catch (InvalidRtpHeader&) {
            LOG(kMedia, "RaopAudioServer::ReadPacket InvalidRtpHeader\n");
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

        // Only process audio type packets.
        // Encountering other type on this channel indicates corrupt packet; ignore.
        if (aPacket.Header().Type() == kTypeAudio) {
            // Process ID
            TUint sessionId = aPacket.Header().Ssrc();

            if (iSessionId == 0) {
                // Initialise session ID.
                iSessionId = sessionId;
                LOG(kMedia, "RaopAudioServer::ReadPacket new iSessionId: %u\n", iSessionId);
            }

            if (sessionId == iSessionId) {
                seq = aPacket.Header().Seq();
                LOG(kMedia, "RaopAudioServer::ReadPacket iSessionId: %u, seq: %u\n", iSessionId, seq);
                return;
            }

            // Rogue ID; ignore.
            LOG(kMedia, "RaopAudioServer::ReadPacket unexpected packet iSessionId: %u, seq: %u\n", iSessionId, seq);
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
    LOG(kMedia, ">RaopAudioDecryptor::Decrypt aEncryptedIn.Bytes(): %u\n", aEncryptedIn.Bytes());
    ASSERT(iKey.Bytes() > 0);
    ASSERT(iInitVector.Bytes() > 0);
    ASSERT(aAudioOut.MaxBytes() <= kPacketSizeBytes+aEncryptedIn.Bytes());

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
