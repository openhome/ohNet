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

// OhmProtocolUnicast

OhmProtocolUnicast::OhmProtocolUnicast(IOhmReceiver& aReceiver, IOhmMsgFactory& aFactory)
    : iReceiver(&aReceiver)
	, iFactory(&aFactory)
    , iReadBuffer(iSocket)
    , iTimerJoin(MakeFunctor(*this, &OhmProtocolUnicast::SendJoin))
    , iTimerListen(MakeFunctor(*this, &OhmProtocolUnicast::SendListen))
    , iTimerLeave(MakeFunctor(*this, &OhmProtocolUnicast::TimerLeaveExpired))
{
}

void OhmProtocolUnicast::HandleAudio(const OhmHeader& aHeader)
{
	Broadcast(iFactory->CreateAudio(iReadBuffer, aHeader));

	if (iLeaving) {
		iTimerLeave.Cancel();
		SendLeave();
		iReadBuffer.ReadInterrupt();
	}
}

void OhmProtocolUnicast::HandleTrack(const OhmHeader& aHeader)
{
	Broadcast(iFactory->CreateTrack(iReadBuffer, aHeader));
}

void OhmProtocolUnicast::HandleMetatext(const OhmHeader& aHeader)
{
	Broadcast(iFactory->CreateMetatext(iReadBuffer, aHeader));
}

void OhmProtocolUnicast::HandleSlave(const OhmHeader& aHeader)
{
    OhmHeaderSlave headerSlave;
    headerSlave.Internalise(iReadBuffer, aHeader);
        	
    iSlaveCount = headerSlave.SlaveCount();

	ReaderBinary reader(iReadBuffer);

    for (TUint i = 0; i < iSlaveCount; i++) {
        TIpAddress address = reader.ReadUintLe(4); // utterly confused due to ohNet's ridiculous decision to pass IpAddresses around memory in BE form
        TUint port = reader.ReadUintBe(2);
        iSlaveList[i].SetAddress(address);
        iSlaveList[i].SetPort(port);
    }
}

void OhmProtocolUnicast::RequestResend(const Brx& aFrames)
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

void OhmProtocolUnicast::Broadcast(OhmMsg& aMsg)
{
	if (iSlaveCount > 0)
	{
		WriterBuffer writer(iMessageBuffer);

		writer.Flush();

		aMsg.Externalise(writer);

        for (TUint i = 0; i < iSlaveCount; i++) {
        	iSocket.Send(iMessageBuffer, iSlaveList[i]);
        }
	}

	iReceiver->Add(aMsg);
}

void OhmProtocolUnicast::Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint)
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

				switch(header.MsgType()) {
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
					break;
				case OhmHeader::kMsgTypeListen:
                    iTimerListen.FireIn((kTimerListenTimeoutMs >> 1) - Random(kTimerListenTimeoutMs >> 3)); // listen secondary timeout
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

	iLeaving = false;

   	iTimerJoin.Cancel();
    iTimerListen.Cancel();
	iTimerLeave.Cancel();
    
	iSocket.Close();
}

void OhmProtocolUnicast::Stop()
{
    iLeaving = true;
    iTimerLeave.FireIn(kTimerLeaveTimeoutMs);
}

void OhmProtocolUnicast::EmergencyStop()
{
	SendLeave();
	TimerLeaveExpired();
}

void OhmProtocolUnicast::SendJoin()
{
    Send(OhmHeader::kMsgTypeJoin);
    iTimerJoin.FireIn(kTimerJoinTimeoutMs);
}

void OhmProtocolUnicast::SendListen()
{
    Send(OhmHeader::kMsgTypeListen);
    iTimerListen.FireIn((kTimerListenTimeoutMs >> 2) - Random(kTimerListenTimeoutMs >> 3)); // listen primary timeout
}

void OhmProtocolUnicast::SendLeave()
{
    Send(OhmHeader::kMsgTypeLeave);
}

void OhmProtocolUnicast::Send(TUint aType)
{
    Bws<OhmHeader::kHeaderBytes> buffer;
    WriterBuffer writer(buffer);

    OhmHeader msg(aType, 0);
    msg.Externalise(writer);
    
    try {
        iSocket.Send(buffer, iEndpoint);
    }
    catch (NetworkError&)
    {
    }
}

void OhmProtocolUnicast::TimerLeaveExpired()
{
	SendLeave();
	iReadBuffer.ReadInterrupt();
}

