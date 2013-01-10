#include "OhmReceiver.h"
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Debug.h>

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

using namespace OpenHome;
using namespace OpenHome::Av;

// OhmProtocolMulticast

// The Join Timeout represents the time within which the Ohm sender
// must see a join message before it decides that no receivers
// are interested in its channel and stops sending audio. The receiver
// can be in one of two Join Modes: Master or Slave. Each mode has
// its own timeout. The Master Join Timeout is a randomly generated time
// between 1/8 and 2/8 of the Join Timeout. The randomisation is performed
// each time a timer is primed with the timeout. The Slave Join Timeout
// is a randomly generated time between 3/8 and 4/8 of the Join Timeout.
// Again, the randomisation is performed each time a timer is primed with
// the timeout. When a receiver starts listening to a Ohm channel it
// is in Master Join Mode: it sends a join message immediately and then
// waits for the Master Join Timeout. If it sees a join message sent
// by another receiver during this period then it moves to Slave Join Mode.
// Otherwise, when the timeout expires it sends a join message and waits for
// the Master Join Timeout again. In Slave Join Mode it does not send join
// messages; it merely monitors join messages sent by the Master. Every time
// a join message is seen the Slave Join Timeout is restarted. If this timeout
// expires without seeing a join message from another receiver, then it moves
// back to Master Join Mode. This system of operation tends to select a single
// receiver as Master. If this Master stops receiving then one of the remaining
// Slaves will tend to be randomly selected as the new Master. If there are
// no Slaves left then the sender will stop sending after the Join Timeout.
       


OhmProtocolMulticast::OhmProtocolMulticast(Environment& aEnv, IOhmReceiver& aReceiver, IOhmMsgFactory& aFactory)
    : iReceiver(&aReceiver)
	, iFactory(&aFactory)
    , iSocket(aEnv)
    , iReadBuffer(iSocket)
    , iTimerJoin(aEnv, MakeFunctor(*this, &OhmProtocolMulticast::SendJoin))
    , iTimerListen(aEnv, MakeFunctor(*this, &OhmProtocolMulticast::SendListen))
{
}

void OhmProtocolMulticast::RequestResend(const Brx& aFrames)
{
	TUint bytes = aFrames.Bytes();

	if (bytes > 0)
	{
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

void OhmProtocolMulticast::Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint)
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

				switch(header.MsgType()) {
				case OhmHeader::kMsgTypeJoin:
				case OhmHeader::kMsgTypeListen:
				case OhmHeader::kMsgTypeLeave:
				case OhmHeader::kMsgTypeSlave:
					break;
				case OhmHeader::kMsgTypeAudio:
					iReceiver->Add(iFactory->CreateAudio(iReadBuffer, header));
					break;
				case OhmHeader::kMsgTypeTrack:
					iReceiver->Add(iFactory->CreateTrack(iReadBuffer, header));
					receivedTrack = true;
					joinComplete = receivedMetatext;
					break;
				case OhmHeader::kMsgTypeMetatext:
					iReceiver->Add(iFactory->CreateMetatext(iReadBuffer, header));
					receivedMetatext = true;
					joinComplete = receivedTrack;
					break;
				case OhmHeader::kMsgTypeResend:
					iReceiver->ResendSeen();
					break;
				}

                iReadBuffer.ReadFlush();
			}
            catch (OhmError&) {
            }
		}
            
		iTimerJoin.Cancel();

		// Phase 2, periodically send listen if required

	    iTimerListen.FireIn((kTimerListenTimeoutMs >> 2) - Random(kTimerListenTimeoutMs >> 3)); // listen primary timeout
	    
        for (;;) {
            try {
                header.Internalise(iReadBuffer);

				switch(header.MsgType()) {
				case OhmHeader::kMsgTypeJoin:
				case OhmHeader::kMsgTypeLeave:
				case OhmHeader::kMsgTypeSlave:
					break;
				case OhmHeader::kMsgTypeListen:
                    iTimerListen.FireIn((kTimerListenTimeoutMs >> 1) - Random(kTimerListenTimeoutMs >> 3)); // listen secondary timeout
					break;
				case OhmHeader::kMsgTypeAudio:
					iReceiver->Add(iFactory->CreateAudio(iReadBuffer, header));
					break;
				case OhmHeader::kMsgTypeTrack:
					iReceiver->Add(iFactory->CreateTrack(iReadBuffer, header));
					break;
				case OhmHeader::kMsgTypeMetatext:
					iReceiver->Add(iFactory->CreateMetatext(iReadBuffer, header));
					break;
				case OhmHeader::kMsgTypeResend:
					iReceiver->ResendSeen();
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
   	iTimerJoin.Cancel();
    iTimerListen.Cancel();
	iSocket.Close();
}

void OhmProtocolMulticast::Stop()
{
    iReadBuffer.ReadInterrupt();
}

void OhmProtocolMulticast::SendListen()
{
    Send(OhmHeader::kMsgTypeListen);
    iTimerListen.FireIn((kTimerListenTimeoutMs >> 2) - Random(kTimerListenTimeoutMs >> 3)); // listen primary timeout
}

void OhmProtocolMulticast::SendJoin()
{
    Send(OhmHeader::kMsgTypeJoin);
    iTimerJoin.FireIn(kTimerJoinTimeoutMs);
}

void OhmProtocolMulticast::Send(TUint aType)
{
    Bws<OhmHeader::kHeaderBytes> buffer;
    WriterBuffer writer(buffer);

    OhmHeader msg(aType, 0);
    msg.Externalise(writer);
    
    iSocket.Send(buffer, iEndpoint);
}

