#include <OpenHome/Av/Songcast/ProtocolOhu.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>
#include <OpenHome/Av/Songcast/OhmSocket.h>
#include <OpenHome/Av/Songcast/ProtocolOhBase.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Functor.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// ProtocolOhu

ProtocolOhu::ProtocolOhu(Environment& aEnv, IOhmMsgFactory& aMsgFactory, Media::TrackFactory& aTrackFactory, IOhmTimestamper& aTimestamper, const Brx& aMode)
    : ProtocolOhBase(aEnv, aMsgFactory, aTrackFactory, aTimestamper, "ohu", aMode)
    , iSocket(aEnv)
    , iReadBuffer(iSocket)
{
    iTimerJoin = new Timer(aEnv, MakeFunctor(*this, &ProtocolOhu::SendJoin));
    iTimerListen = new Timer(aEnv, MakeFunctor(*this, &ProtocolOhu::SendListen));
    iTimerLeave = new Timer(aEnv, MakeFunctor(*this, &ProtocolOhu::TimerLeaveExpired));
}

ProtocolOhu::~ProtocolOhu()
{
    // FIXME - any synchronisation required to ensure other threads have shut down before we start destroying objects?
    delete iTimerJoin;
    delete iTimerListen;
    delete iTimerLeave;
}

void ProtocolOhu::HandleAudio(const OhmHeader& aHeader)
{
    Broadcast(iMsgFactory.CreateAudioBlob(iReadBuffer, aHeader));

    if (iLeaving) {
        iTimerLeave->Cancel();
        SendLeave();
        iReadBuffer.ReadInterrupt();
    }
}

void ProtocolOhu::HandleTrack(const OhmHeader& aHeader)
{
    Broadcast(iMsgFactory.CreateTrack(iReadBuffer, aHeader));
}

void ProtocolOhu::HandleMetatext(const OhmHeader& aHeader)
{
    Broadcast(iMsgFactory.CreateMetatext(iReadBuffer, aHeader));
}

void ProtocolOhu::HandleSlave(const OhmHeader& aHeader)
{
    OhmHeaderSlave headerSlave;
    headerSlave.Internalise(iReadBuffer, aHeader);
    iSlaveCount = headerSlave.SlaveCount();

    ReaderBinary reader(iReadBuffer);
    for (TUint i = 0; i < iSlaveCount; i++) {
        TIpAddress address = reader.ReadUintLe(4);
        TUint port = reader.ReadUintBe(2);
        iSlaveList[i].SetAddress(address);
        iSlaveList[i].SetPort(port);
    }
}

void ProtocolOhu::RequestResend(const Brx& aFrames)
{
    const TUint bytes = aFrames.Bytes();
    if (bytes > 0) {
        Bws<OhmHeader::kHeaderBytes + 400> buffer;
        WriterBuffer writer(buffer);
        OhmHeaderResend headerResend(bytes / 4);
        OhmHeader header(OhmHeader::kMsgTypeResend, headerResend.MsgBytes());
        header.Externalise(writer);
        headerResend.Externalise(writer);
        writer.Write(aFrames);
        iSocket.Send(buffer, iEndpoint);
    }
}

TUint ProtocolOhu::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS(); // FIXME
    return 0;
}

void ProtocolOhu::Broadcast(OhmMsg* aMsg)
{
    if (iSlaveCount > 0) {
        WriterBuffer writer(iMessageBuffer);
        writer.Flush();
        aMsg->Externalise(writer);
        for (TUint i = 0; i < iSlaveCount; i++) {
            iSocket.Send(iMessageBuffer, iSlaveList[i]);
        }
    }

    Add(aMsg);
}

void ProtocolOhu::Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint)
{
    iLeaving = false;
    iSlaveCount = 0;
    iEndpoint.Replace(aEndpoint);
    iSocket.OpenUnicast(aInterface, aTtl);
    try {
        OhmHeader header;
        SendJoin();

        // Phase 1, periodically send join until Track and Metatext have been received
        TBool joinComplete = false;
        TBool receivedTrack = false;
        TBool receivedMetatext = false;

        while (!joinComplete) {
            try {
                header.Internalise(iReadBuffer);

                switch (header.MsgType())
                {
                case OhmHeader::kMsgTypeJoin:
                case OhmHeader::kMsgTypeListen:
                case OhmHeader::kMsgTypeLeave:
                    break;
                case OhmHeader::kMsgTypeAudio:
                    HandleAudio(header);
                    break;
                case OhmHeader::kMsgTypeTrack:
                    HandleTrack(header);
                    receivedTrack = true;
                    joinComplete = receivedMetatext;
                    break;
                case OhmHeader::kMsgTypeMetatext:
                    HandleMetatext(header);
                    receivedMetatext = true;
                    joinComplete = receivedTrack;
                    break;
                case OhmHeader::kMsgTypeSlave:
                    HandleSlave(header);
                    break;
                case OhmHeader::kMsgTypeResend:
                    ResendSeen();
                    break;
                default:
                    ASSERTS();
                }

                iReadBuffer.ReadFlush();
            }
            catch (OhmError&) {
            }
        }
            
        iTimerJoin->Cancel();

        // Phase 2, periodically send listen if required
        iTimerListen->FireIn((kTimerListenTimeoutMs >> 2) - iEnv.Random(kTimerListenTimeoutMs >> 3)); // listen primary timeout
        for (;;) {
            try {
                header.Internalise(iReadBuffer);

                switch (header.MsgType())
                {
                case OhmHeader::kMsgTypeJoin:
                case OhmHeader::kMsgTypeLeave:
                    break;
                case OhmHeader::kMsgTypeListen:
                    iTimerListen->FireIn((kTimerListenTimeoutMs >> 1) - iEnv.Random(kTimerListenTimeoutMs >> 3)); // listen secondary timeout
                    break;
                case OhmHeader::kMsgTypeAudio:
                    HandleAudio(header);
                    break;
                case OhmHeader::kMsgTypeTrack:
                    HandleTrack(header);
                    break;
                case OhmHeader::kMsgTypeMetatext:
                    HandleMetatext(header);
                    break;
                case OhmHeader::kMsgTypeSlave:
                    HandleSlave(header);
                    break;
                case OhmHeader::kMsgTypeResend:
                    ResendSeen();
                    break;
                default:
                    ASSERTS();
                }

                iReadBuffer.ReadFlush();
            }
            catch (OhmError&) {
            }
        }
    }
    catch (ReaderError&) {
    }
    
    iReadBuffer.ReadFlush();
    iLeaving = false;
    iTimerJoin->Cancel();
    iTimerListen->Cancel();
    iTimerLeave->Cancel();
    iSocket.Close();
}

void ProtocolOhu::Stop()
{
    iLeaving = true;
    iTimerLeave->FireIn(kTimerLeaveTimeoutMs);
}

/*void ProtocolOhu::EmergencyStop()
{
    SendLeave();
    TimerLeaveExpired();
}*/

void ProtocolOhu::SendJoin()
{
    Send(OhmHeader::kMsgTypeJoin);
    iTimerJoin->FireIn(kTimerJoinTimeoutMs);
}

void ProtocolOhu::SendListen()
{
    Send(OhmHeader::kMsgTypeListen);
    iTimerListen->FireIn((kTimerListenTimeoutMs >> 2) - iEnv.Random(kTimerListenTimeoutMs >> 3)); // listen primary timeout
}

void ProtocolOhu::SendLeave()
{
    Send(OhmHeader::kMsgTypeLeave);
}

void ProtocolOhu::Send(TUint aType)
{
    Bws<OhmHeader::kHeaderBytes> buffer;
    WriterBuffer writer(buffer);
    OhmHeader msg(aType, 0);
    msg.Externalise(writer);
    try {
        iSocket.Send(buffer, iEndpoint);
    }
    catch (NetworkError&) {
    }
}

void ProtocolOhu::TimerLeaveExpired()
{
    SendLeave();
    iReadBuffer.ReadInterrupt();
}
