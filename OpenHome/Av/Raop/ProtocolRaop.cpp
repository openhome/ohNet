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


// ProtocolRaop

ProtocolRaop::ProtocolRaop(Environment& aEnv, Media::TrackFactory& aTrackFactory, IRaopVolumeEnabler& aVolume, IRaopDiscovery& aDiscovery, UdpServerManager& aServerManager, TUint aAudioId, TUint aControlId)
    : ProtocolNetwork(aEnv)
    , iTrackFactory(aTrackFactory)
    , iVolumeEnabled(false)
    , iVolume(aVolume)
    , iDiscovery(aDiscovery)
    , iServerManager(aServerManager)
    , iRaopAudio(iServerManager.Find(aAudioId))
    , iRaopControl(aEnv, iServerManager.Find(aControlId), *this)
    , iSupply(NULL)
    , iLockRaop("PRAL")
    , iSem("PRAS", 0)
    , iSemInputChanged("PRIC", 0)
{
}

ProtocolRaop::~ProtocolRaop()
{
    delete iSupply;
}

void ProtocolRaop::DoInterrupt()
{
    LOG(kMedia, "ProtocolRaop::DoInterrupt\n");

    iRaopAudio.DoInterrupt();
    iRaopControl.DoInterrupt();
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
    iRaopAudio.Reset();
    iRaopControl.Reset(ctrlPort);
    Brn audio;
    TUint16 expected = 0;
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
            TUint16 count = iRaopAudio.ReadPacket();

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

            iDiscovery.KeepAlive();

            if(aesSid != iDiscovery.AesSid()) {
                aesSid = iDiscovery.AesSid();       // aes key has been updated

                LOG(kMedia, "ProtocolRaop::Stream() new sid\n");

                iRaopAudio.Initialise(iDiscovery.Aeskey(), iDiscovery.Aesiv());
            }
            if(start) {
                LOG(kMedia, "ProtocolRaop::Stream() new container\n");
                start = false;        // create dummy container for codec recognition and initialisation
                OutputContainer(Brn(iDiscovery.Fmtp()));
                expected = count;   // init expected count
            }
            TInt padding = count;
            padding -= expected;

            if(padding >= 0) { //ignore if packet is out of order
                TUint SenderSkew, latency;
                iRaopControl.Time(SenderSkew, latency);

                // if there are missing packets request re-send and wait for response
                if(padding > 0) {
                    iRaopControl.RequestResend(expected, padding);
                    while(padding > 0) {
                        LOG(kMedia, "ProtocolRaop get resent data, padding %d\n", padding);
                        try {
                            iRaopControl.GetResentData(iResentData, expected);  //this will block until data received or timed out
                            iRaopControl.LockRx();  // don't allow any more data to be received while processing
                            LOG(kMedia, "ProtocolRaop received resent data, %d bytes\n", iResentData.Bytes());
                            Brn data(iResentData);
                            iRaopAudio.DecodePacket(SenderSkew, latency, data);
                            OutputAudio(iRaopAudio.Audio(), iRaopAudio.First());
                            padding--;
                            expected++;
                            iRaopControl.UnlockRx();
                        }
                        catch(ResendTimeout&) {
                            LOG(kMedia, "ProtocolRaop NOT received resent data, padding %d\n", padding);

                            //just mute if resent packets not available
                            //this assumes that iRaopAudio has already been set
                            iRaopAudio.SetMute();
                            while(padding--) {
                                OutputAudio(iRaopAudio.Audio(), iRaopAudio.First());
                            }
                        }
                        catch(ResendInvalid&) {
                            // may be corrupted or a redundant frame left from a previous timeout
                            LOG(kMedia, "ProtocolRaop unexpected data - ignore, padding %d\n", padding);
                        }
                    }
                }
                try {
                    iRaopAudio.DecodePacket(SenderSkew, latency); // send original
                    OutputAudio(iRaopAudio.Audio(), iRaopAudio.First());
                    expected = count+1;
                }
                catch (InvalidRtpHeader&) { // FIXME - redundant? Can be caught by outer exception handling below
                    LOG(kMedia, "ProtocolRaop::Stream caught InvalidHeader exception\n");
                }
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

void ProtocolRaop::OutputAudio(const Brx& aPacket, TBool /*aFirst*/)
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

TUint ProtocolRaop::SendFlush()
{
    LOG(kMedia, "ProtocolRaop::NotifySessionWait\n");
    AutoMutex a(iLockRaop);
    ASSERT(iActive);
    iNextFlushId = iFlushIdProvider->NextFlushId();
    iWaiting = true;
    DoInterrupt();
    return iNextFlushId;
}


// RaopControl

RaopControl::RaopControl(Environment& aEnv, SocketUdpServer& aServer, IRaopAudioResumer& aAudioResumer)
    : iClientPort(kInvalidServerPort)
    , iServer(aServer)
    , iReceive(iServer)
    , iAudioResumer(aAudioResumer)
    , iMutex("RAOC")
    , iMutexRx("RAOR")
    , iSemaResend("RAOC", 0) // FIXME - nothing else has a reference to this!
    , iResend(0)
    , iExit(false)
{
    iTimerExpiry = new Timer(aEnv, MakeFunctor(*this, &RaopControl::TimerExpired), "RaopControl");
    iThreadControl = new ThreadFunctor("RaopControl", MakeFunctor(*this, &RaopControl::Run), kPriority-1, kSessionStackBytes);
    iThreadControl->Start();
}

RaopControl::~RaopControl()
{
    iMutex.Wait();
    iExit = true;
    iMutex.Signal();
    iServer.ReadInterrupt();
    iServer.ClearWaitForOpen();
    delete iThreadControl;
    delete iTimerExpiry;
}

void RaopControl::LockRx()
{
    iMutexRx.Wait();
}

void RaopControl::UnlockRx()
{
    iMutexRx.Signal();
}

void RaopControl::DoInterrupt()
{
    LOG(kMedia, "RaopControl::DoInterrupt()\n");
    iMutex.Wait();
    iClientPort = kInvalidServerPort;
    if(iResend) {
        iResend = 0;
        iSemaResend.Signal();
    }

    iMutex.Signal();
}

void RaopControl::Reset(TUint aClientPort)
{
    iMutex.Wait();
    iClientPort = aClientPort;
    iMutex.Signal();
}

void RaopControl::Run()
{
    LOG(kMedia, "RaopControl::Run\n");
    iResend = 0;

    for (;;) {

        iMutex.Wait();
        if (iExit) {
            iMutex.Signal();
            return;
        }
        iMutex.Signal();

        try {
            iServer.Read(iPacket);
            iEndpoint.Replace(iServer.Sender());
            try {
                RtpPacketRaop packet(iPacket);
                if (packet.Header().Type() == ESync) {
                    Log::Print("RaopControl::Run packet.Extension(): %u\n", packet.Header().Extension());
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
                    iMutex.Wait();
                    iLatency = rtpTimestampNextPacket-rtpTimestamp;
                    //iSenderSkew = rtpTimestamp - mclk;   // calculate count when this should play relative to current mclk count
                    iMutex.Signal();
                    LOG(kMedia, "RaopControl::Run rtpTimestamp: %u, ntpTimeSecs: %u, ntpTimeSecsFract: %u, rtpTimestampNextPacket: %u, iLatency: %u, iSenderSkew: %u\n", rtpTimestamp, ntpTimeSecs, ntpTimeSecsFract, rtpTimestampNextPacket, iLatency, iSenderSkew);

                    payload;
                }
                else if (packet.Header().Type() == EResendResponse) {
                    iMutexRx.Wait();    // wait for processing of previous resend message
                    iMutex.Wait();
                    LOG(kMedia, "RaopControl::Run EResendResponse iResend: %u\n", iResend);

                    if (iResend) {            // ignore if unexpected (may have been delayed and timed out) // FIXME - is there a sequence number that can be waited on?
                        if (iResentData.Bytes() != 0) { // previous data hasn't been processed yet so fail
                            iResentData.SetBytes(0);
                        }
                        else {
                            iResentData.Replace(packet.Payload()); // FIXME - is full payload correct, or should SSRC be included?
                        }
                    }

                    const TBool resend = (iResend != 0);

                    iMutex.Signal();
                    iMutexRx.Signal();

                    // Inform audio thread that there is a resent packet waiting.
                    if (resend) {
                        iSemaResend.Signal();   // FIXME - can we do this without exposing a semaphore? - Have a call into this to request a resend, and a call into audio processing thread to receive resent packet?
                    }
                }
                else {
                    LOG(kMedia, "RaopControl::Run unexpected packet type: %u\n", packet.Header().Type());
                }

                iReceive.ReadFlush();
            }
            catch (InvalidRtpHeader& aInvalidHeader) {
                aInvalidHeader;
                LOG(kMedia, "RaopControl::Run caught InvalidRtpHeader\n");
                iReceive.ReadFlush();   // Unexpected, so ignore.
            }
        }
        catch (ReaderError&) {
            LOG(kMedia, "RaopControl::Run caught ReaderError\n");
            iReceive.ReadFlush();
            if (!iServer.IsOpen()) {
                iServer.WaitForOpen();
            }
        }
    }
}

void RaopControl::Time(TUint& aSenderSkew, TUint& aLatency)
{
    iMutex.Wait();
    aSenderSkew = iSenderSkew;
    aLatency = iLatency;
    iMutex.Signal();
}

void RaopControl::RequestResend(TUint aPacketId, TUint aPackets)
{
    LOG(kMedia, "RequestResend aPackets %d\n", aPackets);

    iMutex.Wait();
    TUint resend = iResend;
    if(resend == 0) {   // ignore if already requested data
        iResend = aPackets;
        iResentData.SetBytes(0);
        //while(iSemaResend.TryWait() != 0) {
        //    // this should never occur, but if it does it is recoverable
        //    LOG(kMedia, "******************* purge stale semaphore ****************\n");
        //}
    }
    else {
        LOG(kMedia, "RequestResend already active, resend %d\n", resend);
    }

    iMutex.Signal();

    if(resend == 0) {
        Bws<16> request(Brn(""));
        request.Append((TByte)0x80);
        request.Append((TByte)0xD5);
        request.Append((TByte)0x00);
        request.Append((TByte)0x01);
        request.Append((TByte)((aPacketId >> 8) & 0xff));
        request.Append((TByte)((aPacketId) & 0xff));
        request.Append((TByte)((aPackets >> 8) & 0xff));
        request.Append((TByte)((aPackets) & 0xff));

        try {
            iMutex.Wait();
            iEndpoint.SetPort(iClientPort); // send to client listening port
            iMutex.Signal();
            iServer.Send(request, iEndpoint);
        }
        catch(NetworkError) {
            // will handle this by timing out on receive
        }
    }
}


void RaopControl::GetResentData(Bwx& aData, TUint16 aCount)
{
    static const TUint kTimerExpiryTimeoutMs = 80; // set this to avoid loss of data in main stream buffer

    // must wait until resent data is received, or timed out

    iTimerExpiry->FireIn(kTimerExpiryTimeoutMs);

    LOG(kMedia, "RaopControl::GetResentData wait for data\n");
    iSemaResend.Wait(); // wait for resent data to be received or timeout
    iMutex.Wait();
    //if timed out, resent data will be empty
    aData.SetBytes(0);
    TBool valid = false;
    TBool timeout = false;
    if(iResentData.Bytes() >= 8) { // ensure valid
        TUint type = Converter::BeUint16At(iResentData, 0) & 0xffff;
        if(type == 0x8060) {
            TUint16 count = Converter::BeUint16At(iResentData, 2) & 0xffff;
            if(count == aCount) {
                aData.Replace(iResentData);
                iResend--;
                valid = true;
            }
            else{
                LOG(kMedia, "RaopControl::GetResentData invalid resent data count, is %d, should be %d\n", count, aCount);
            }
        }
        else {
            LOG(kMedia, "RaopControl::GetResentData Converter::BeUint16At(iResentData,0) %x\n", type);
        }
    }
    else {
        LOG(kMedia, "RaopControl::GetResentData iResentData.Bytes() %d\n", iResentData.Bytes());
        if(iResentData.Bytes() == 0) {
            timeout = true; // no data, so must have timed out
        }
    }
    iResentData.SetBytes(0);
    iMutex.Signal();
    if(timeout) {
        THROW(ResendTimeout);
    }
    if(!valid) {
        THROW(ResendInvalid);
    }
}


void RaopControl::TimerExpired()
{

    iMutex.Wait();
    LOG(kMedia, "RaopControl TimerExpired, iResend %d\n", iResend);
    if(iResend) {
        iResend = 0;        // not received sent frames
        iMutex.Signal();
        iSemaResend.Signal();
    }
    else {
        iMutex.Signal();
    }

}


// RaopAudio

RaopAudio::RaopAudio(SocketUdpServer& aServer)
    : iServer(aServer)
    , iFirst(false)
{
}

RaopAudio::~RaopAudio()
{
}

void RaopAudio::Reset()
{
    iDataBuffer.SetBytes(0);
    iAudio.SetBytes(0);
    iFirst = false;
    iAeskey.SetBytes(0);
    iAesiv.SetBytes(0);
    iInitId = true;
    iInterrupted = false;
    iServer.ReadFlush();  // set to read next udp packet
}

void RaopAudio::Initialise(const Brx& aAeskey, const Brx& aAesiv)
{
    iAeskey.Replace(aAeskey);
    iAesiv.Replace(aAesiv);
}

void RaopAudio::DoInterrupt()
{
    LOG(kMedia, "RaopAudio::DoInterrupt()\n");
    iInterrupted = true;
    iServer.ReadInterrupt();
}

TUint16 RaopAudio::ReadPacket()
{
    // Read a packet at a time and process it.
    //LOG(kMedia, ">RaopAudio::ReadPacket()\n");
    TUint16 count = 0;

    for (;;) {
        try {
            iServer.Read(iDataBuffer);
        }
        catch (ReaderError&) {
            iServer.ReadFlush();

            // Either no data, user abort or invalid header
            if (!iServer.IsOpen()) {
                LOG(kMedia, "RaopAudio::ReadPacket() RaopAudioServerClosed\n");
                THROW(RaopAudioServerClosed);
            }
            if (iInterrupted) {
                LOG(kMedia, "RaopAudio::ReadPacket() Exception, iInterrupted %d\n", iInterrupted);
                THROW(ReaderError);
            }
            if(iDataBuffer.Bytes() < 12) {  // may get here if kMaxReadBufferBytes not read
                continue;   // keep trying if not interrupted
            }
            return count;
        }
        iServer.ReadFlush();  // set to read next udp packet

        if(iDataBuffer.Bytes() < 12) {  // may get here if kMaxReadBufferBytes not read
            continue;
        }

        // Check header
        if((iDataBuffer[0] != 0x80)
                || !((iDataBuffer[1] == 0x60)
                || (iDataBuffer[1] == 0xe0))) {
            LOG(kMedia, "RaopAudio::ReadPacket() invalid header %x\n", iDataBuffer[0]);
            THROW(InvalidHeader); // invalid header
        }

        Log::Print("Audio packet first: %u\n", iDataBuffer[1] == 0xe0);
        if (iDataBuffer[1] == 0xe0) {
            iFirst = true;
        }
        else {
            iFirst = false;
        }

        // Process ID
        TUint32 id = Converter::BeUint32At(iDataBuffer, 8);
        //LOG(kMedia, "RaopAudio::ReadPacket() %d, id %d\n", iDataBuffer.Bytes(), id);

        if(iInitId) {
            iInitId = false;
            iId = id;   // appears to be random id generated by iTunes for each session
            LOG(kMedia, "RaopAudio::ReadPacket() New iId = %d\n", iId);
        }

        if(iId == id) {
            count = Converter::BeUint16At(iDataBuffer, 2);
            //LOG(kMedia, "RaopAudio::ReadPacket() iId = %d, count = %d\n", iId, count);
            break;  // packet with same id found
        }
        LOG(kMedia, "RaopAudio::ReadPacket() no data so retry\n");
        // rogue id so ignore
    }

    return count;
}

void RaopAudio::DecodePacket(TUint aSenderSkew, TUint aLatency)
{
    DecodePacket(aSenderSkew, aLatency, iDataBuffer);
}

void RaopAudio::DecodePacket(TUint /*aSenderSkew*/, TUint /*aLatency*/, const Brx& aPacket)
{
    //LOG(kMedia, "RaopAudio::DecodePacket() bytes %d\n", aData.Bytes());

    static const TUint kSizeBytes = sizeof(TUint);
    RtpPacketRaop packet(aPacket);    // May throw InvalidRtpHeader.
    const Brx& audio = packet.Payload();
    iAudio.SetBytes(0);

    if (kSizeBytes+audio.Bytes() > iAudio.MaxBytes()) {
        THROW(InvalidHeader);   // Invalid data received. FIXME - should really add different exception
    }

    WriterBuffer writerBuffer(iAudio);
    WriterBinary writerBinary(writerBuffer);
    writerBinary.WriteUint32Be(audio.Bytes());

    unsigned char* inBuf = const_cast<unsigned char*>(audio.Ptr());
    unsigned char* outBuf = const_cast<unsigned char*>(iAudio.Ptr()+iAudio.Bytes());
    unsigned char initVector[16];
    memcpy(initVector, iAesiv.Ptr(), sizeof(initVector));   // Use same initVector at start of each decryption block.

    AES_cbc_encrypt(inBuf, outBuf, audio.Bytes(), (AES_KEY*)iAeskey.Ptr(), initVector, AES_DECRYPT);
    const TUint audioRemaining = audio.Bytes() % 16;
    const TUint audioWritten = audio.Bytes()-audioRemaining;
    if (audioRemaining > 0) {
        // Copy remaining audio to outBuf if <16 bytes.
        memcpy(outBuf+audioWritten, inBuf+audioWritten, audioRemaining);
    }
    iAudio.SetBytes(kSizeBytes+audio.Bytes());
}

Brn RaopAudio::Audio()
{
    return(Brn(iAudio)); // FIXME - sort this out
}

TBool RaopAudio::First() const
{
    return iFirst;
}

void RaopAudio::SetMute()
{
    //((RaopDataHeader*)iAudio.Ptr())->SetMute();
}


// RtpHeaderFixed

RtpHeaderFixed::RtpHeaderFixed(const Brx& aRtpHeader)
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

TUint RtpHeaderFixed::Timestamp() const
{
    return iTimestamp;
}

TUint RtpHeaderFixed::Ssrc() const
{
    return iSsrc;
}


// RtpPacketRaop

RtpPacketRaop::RtpPacketRaop(const Brx& aRtpPacket)
    : iHeader(Brn(aRtpPacket.Ptr(), RtpHeaderFixed::kHeaderBytes))
{
    const TUint offset = RtpHeaderFixed::kHeaderBytes;
    iPayload.Set(aRtpPacket.Ptr()+offset, aRtpPacket.Bytes()-offset);
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
        const TUint kHeaderSizeIncCsrc = kMinHeaderBytes+iHeader.CsrcCount()*4;
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
            const TUint headerExtensionBytes = readerBinary.ReadUintBe(2)*4;

            headerSizeFull = kHeaderSizeInclHeaderExtension+headerExtensionBytes;
            if (aRtpPacket.Bytes() < headerSizeFull) {
                THROW(InvalidRtpHeader);
            }
            iHeaderExtension.Set(aRtpPacket.Ptr()+kHeaderSizeInclHeaderExtension, headerExtensionBytes);
        }

        TUint paddingBytes = 0;
        if (iHeader.Padding()) {
            paddingBytes = aRtpPacket[aRtpPacket.Bytes()-1];
        }

        const TUint kPayloadBytes = aRtpPacket.Bytes()-headerSizeFull-paddingBytes;
        if (kPayloadBytes == 0 || aRtpPacket.Bytes() != headerSizeFull+kPayloadBytes+paddingBytes) {
            THROW(InvalidRtpHeader);
        }
        iPayload.Set(aRtpPacket.Ptr()+headerSizeFull, kPayloadBytes);
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
