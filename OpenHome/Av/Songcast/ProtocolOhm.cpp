#include <OpenHome/Av/Songcast/ProtocolOhm.h>
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

/* The Join Timeout represents the time within which the Ohm sender
   must see a join message before it decides that no receivers
   are interested in its channel and stops sending audio. The receiver
   can be in one of two Join Modes: Master or Slave. Each mode has
   its own timeout. The Master Join Timeout is a randomly generated time
   between 1/8 and 2/8 of the Join Timeout. The randomisation is performed
   each time a timer is primed with the timeout. The Slave Join Timeout
   is a randomly generated time between 3/8 and 4/8 of the Join Timeout.
   Again, the randomisation is performed each time a timer is primed with
   the timeout. When a receiver starts listening to a Ohm channel it
   is in Master Join Mode: it sends a join message immediately and then
   waits for the Master Join Timeout. If it sees a join message sent
   by another receiver during this period then it moves to Slave Join Mode.
   Otherwise, when the timeout expires it sends a join message and waits for
   the Master Join Timeout again. In Slave Join Mode it does not send join
   messages; it merely monitors join messages sent by the Master. Every time
   a join message is seen the Slave Join Timeout is restarted. If this timeout
   expires without seeing a join message from another receiver, then it moves
   back to Master Join Mode. This system of operation tends to select a single
   receiver as Master. If this Master stops receiving then one of the remaining
   Slaves will tend to be randomly selected as the new Master. If there are
   no Slaves left then the sender will stop sending after the Join Timeout. */


// ProtocolOhm

ProtocolOhm::ProtocolOhm(Environment& aEnv, IOhmMsgFactory& aFactory, Media::TrackFactory& aTrackFactory, IOhmTimestamper& aTimestamper, const Brx& aMode)
    : ProtocolOhBase(aEnv, aTrackFactory, aTimestamper, "ohm", aMode)
    , iEnv(aEnv)
	, iFactory(aFactory)
    , iSocket(aEnv)
    , iReadBuffer(iSocket)
{
    iTimerJoin = new Timer(aEnv, MakeFunctor(*this, &ProtocolOhm::SendJoin));
    iTimerListen = new Timer(aEnv, MakeFunctor(*this, &ProtocolOhm::SendListen));
}

ProtocolOhm::~ProtocolOhm()
{
    delete iTimerJoin;
    delete iTimerListen;
}

void ProtocolOhm::Stop()
{
    iReadBuffer.ReadInterrupt();
}

void ProtocolOhm::Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint)
{
	iEndpoint.Replace(aEndpoint);
	iSocket.OpenMulticast(aInterface, aTtl, iEndpoint);
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
				case OhmHeader::kMsgTypeSlave:
					break;
				case OhmHeader::kMsgTypeAudio:
					Add(iFactory.CreateAudioBlob(iReadBuffer, header));
					break;
				case OhmHeader::kMsgTypeTrack:
					Add(iFactory.CreateTrack(iReadBuffer, header));
					receivedTrack = true;
					joinComplete = receivedMetatext;
					break;
				case OhmHeader::kMsgTypeMetatext:
					Add(iFactory.CreateMetatext(iReadBuffer, header));
					receivedMetatext = true;
					joinComplete = receivedTrack;
					break;
				case OhmHeader::kMsgTypeResend:
					ResendSeen();
					break;
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
				case OhmHeader::kMsgTypeSlave:
					break;
				case OhmHeader::kMsgTypeListen:
                    iTimerListen->FireIn((kTimerListenTimeoutMs >> 1) - iEnv.Random(kTimerListenTimeoutMs >> 3)); // listen secondary timeout
					break;
				case OhmHeader::kMsgTypeAudio:
					Add(iFactory.CreateAudioBlob(iReadBuffer, header));
					break;
				case OhmHeader::kMsgTypeTrack:
					Add(iFactory.CreateTrack(iReadBuffer, header));
					break;
				case OhmHeader::kMsgTypeMetatext:
					Add(iFactory.CreateMetatext(iReadBuffer, header));
					break;
				case OhmHeader::kMsgTypeResend:
					ResendSeen();
					break;
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
   	iTimerJoin->Cancel();
    iTimerListen->Cancel();
	iSocket.Close();
}

void ProtocolOhm::RequestResend(const Brx& aFrames)
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

TUint ProtocolOhm::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS(); // FIXME
    return 0;
}

void ProtocolOhm::SendJoin()
{
    Send(OhmHeader::kMsgTypeJoin);
    iTimerJoin->FireIn(kTimerJoinTimeoutMs);
}

void ProtocolOhm::SendListen()
{
    Send(OhmHeader::kMsgTypeListen);
    iTimerListen->FireIn((kTimerListenTimeoutMs >> 2) - iEnv.Random(kTimerListenTimeoutMs >> 3)); // listen primary timeout
}

void ProtocolOhm::Send(TUint aType)
{
    Bws<OhmHeader::kHeaderBytes> buffer;
    WriterBuffer writer(buffer);
    OhmHeader msg(aType, 0);
    msg.Externalise(writer);
    iSocket.Send(buffer, iEndpoint);
}
