#include "OhmReceiver.h"
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Debug.h>

#include <stdio.h>

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

OhmReceiver::OhmReceiver(TIpAddress aInterface, TUint aTtl, IOhmReceiverDriver& aDriver)
	: iInterface(aInterface)
	, iTtl(aTtl)
	, iDriver(&aDriver)
	, iMutexMode("OHRM")
	, iMutexTransport("OHRT")
	, iPlaying("OHRP", 0)
	, iZoning("OHRZ", 0)
	, iStopped("OHRS", 0)
	, iNullStop("OHRN", 0)
	, iLatency(0)
	, iTransportState(eStopped)
	, iPlayMode(eNone)
	, iZoneMode(false)
	, iTerminating(false)
	, iEndpointNull(0, Brn("0.0.0.0"))
	, iRxZone(iSocketZone)
    , iTimerZoneQuery(MakeFunctor(*this, &OhmReceiver::SendZoneQuery))
	, iFactory(500, 10, 10)
	, iRepairing(false)
    , iTimerRepair(MakeFunctor(*this, &OhmReceiver::TimerRepairExpired))
{
	iProtocolMulticast = new OhmProtocolMulticast(*this, iFactory);
	iProtocolUnicast = new OhmProtocolUnicast(*this, iFactory);
    iThread = new ThreadFunctor("OHRT", MakeFunctor(*this, &OhmReceiver::Run), kThreadPriority, kThreadStackBytes);
    iThread->Start();
    iThreadZone = new ThreadFunctor("OHRZ", MakeFunctor(*this, &OhmReceiver::RunZone), kThreadZonePriority, kThreadZoneStackBytes);
    iThreadZone->Start();
}

OhmReceiver::~OhmReceiver()
{
	iMutexTransport.Wait();

	StopLocked();

	iTerminating = true;

	iThread->Signal();
	iThreadZone->Signal();

	delete (iThread);
	delete (iThreadZone);
	delete (iProtocolMulticast);
	delete (iProtocolUnicast);
	
	iMutexTransport.Signal();
}

TUint OhmReceiver::Ttl() const
{
	iMutexTransport.Wait();

	TUint ttl = iTtl;

	iMutexTransport.Signal();

	return (ttl);
}

TIpAddress OhmReceiver::Interface() const
{
	iMutexTransport.Wait();

	TIpAddress iface = iInterface;

	iMutexTransport.Signal();

	return (iface);
}

void OhmReceiver::SetTtl(TUint aValue)
{
	iMutexTransport.Wait();
	iMutexMode.Wait();

	if (iTransportState != eStopped) {
		switch (iPlayMode)
		{
		case eNone:
			iTtl = aValue;
			break;
		case eMulticast:
			iProtocolMulticast->Stop();
			iStopped.Wait();
			iTtl = aValue;
			iTransportState = eDisconnected;
			iDriver->Disconnected();
			iThread->Signal();
			iPlaying.Wait();
			break;
		case eUnicast:
			iProtocolUnicast->Stop();
			iStopped.Wait();
			iTtl = aValue;
			iTransportState = eDisconnected;
			iDriver->Disconnected();
			iThread->Signal();
			iPlaying.Wait();
			break;
		case eNull:
			iTtl = aValue;
			break;
		}
	}
	else {
		iTtl = aValue;
	}

	iMutexMode.Signal();
	iMutexTransport.Signal();
}

void OhmReceiver::SetInterface(TIpAddress aValue)
{
	iMutexTransport.Wait();
	iMutexMode.Wait();

	if (iTransportState != eStopped) {
		switch (iPlayMode)
		{
		case eNone:
			iInterface = aValue;
			break;
		case eMulticast:
			iProtocolMulticast->Stop();
			iStopped.Wait();
			iTransportState = eDisconnected;
			iDriver->Disconnected();
			iInterface = aValue;
			iThread->Signal();
			iPlaying.Wait();
			break;
		case eUnicast:
			iProtocolUnicast->Stop();
			iStopped.Wait();
			iTransportState = eDisconnected;
			iDriver->Disconnected();
			iInterface = aValue;
			iThread->Signal();
			iPlaying.Wait();
			break;
		case eNull:
			iInterface = aValue;
			break;
		}
	}
	else {
		iInterface = aValue;
	}

	iMutexMode.Signal();
	iMutexTransport.Signal();
}

void OhmReceiver::Play(const Brx& aUri)
{
	iMutexTransport.Wait();

	StopLocked();

	iTransportState = eStarted;
	iDriver->Started();

	OpenHome::Uri uri;

	try {
		uri.Replace(aUri);
	}
	catch (UriError&) {
	}

	iMutexMode.Wait();

	iEndpoint.Replace(Endpoint(uri.Port(), uri.Host()));

	if (iEndpoint.Equals(iEndpointNull))
	{
		iZoneMode = false;
		iPlayMode = eNull;
		iTransportState = eConnected;
		iDriver->Connected();
		iThread->Signal();
		iPlaying.Wait();
	}
	else if (uri.Scheme() == Brn("ohz") && iEndpoint.Equals(iSocketZone.This())) {
		iZoneMode = true;
		iPlayMode = eNone;
		iZone.Replace(uri.PathAndQuery().Split(1));
		iThreadZone->Signal();
		iZoning.Wait();
	}
	else if (uri.Scheme() == Brn("ohm")) {
		iZoneMode = false;
		iPlayMode = eMulticast;
		iThread->Signal();
		iPlaying.Wait();
	}
	else if (uri.Scheme() == Brn("ohu")) {
		iZoneMode = false;
		iPlayMode = eUnicast;
		iThread->Signal();
		iPlaying.Wait();
	}
	else {
		iZoneMode = false;
		iPlayMode = eNull;
		iTransportState = eConnected;
		iDriver->Connected();
		iThread->Signal();
		iPlaying.Wait();
	}

	iMutexMode.Signal();
	iMutexTransport.Signal();
}

void OhmReceiver::PlayZoneMode(const Brx& aUri)
{
	iMutexTransport.Wait();

	OpenHome::Uri uri;

	try {
		uri.Replace(aUri);
	}
	catch (UriError&) {
		uri.Replace(Brn("ohm://0.0.0.0:0"));
	}

	Endpoint endpoint(uri.Port(), uri.Host());

	iMutexTransport.Signal();

	iMutexMode.Wait();

	if (iEndpoint.Equals(endpoint)) {
		iMutexMode.Signal();
		return;
	}

	switch (iPlayMode)
	{
	case eNone:
		break;
	case eMulticast:
		iProtocolMulticast->Stop();
		iStopped.Wait();
		break;
	case eUnicast:
		iProtocolUnicast->Stop();
		iStopped.Wait();
		break;
	case eNull:
		iNullStop.Signal();
		iStopped.Wait();
		break;
	}

	iMutexTransport.Wait();

	Reset();

	if (iTransportState != eStarted) {
		iDriver->Started();
	}

	iEndpoint.Replace(endpoint);

	if (iEndpoint.Equals(iEndpointNull))
	{
		iPlayMode = eNull;
		iTransportState = eConnected;
		iDriver->Connected();
		iThread->Signal();
		iPlaying.Wait();
	}
	else if (uri.Scheme() == Brn("ohm")) {
		iPlayMode = eMulticast;
		iTransportState = eStarted;
		iThread->Signal();
		iPlaying.Wait();
	}
	else if (uri.Scheme() == Brn("ohu")) {
		iPlayMode = eUnicast;
		iTransportState = eStarted;
		iThread->Signal();
		iPlaying.Wait();
	}
	else {
		iPlayMode = eNull;
		iTransportState = eConnected;
		iDriver->Connected();
		iThread->Signal();
		iPlaying.Wait();
	}

	iMutexMode.Signal();
	iMutexTransport.Signal();
}

void OhmReceiver::Stop()
{
	iMutexTransport.Wait();

	StopLocked();

	iMutexTransport.Signal();
}

void OhmReceiver::StopLocked()
{
	if (iTransportState == eStopped)
	{
		return;
	}

	iMutexMode.Wait();
	iMutexTransport.Signal();

	if (iZoneMode)
	{
		iSocketZone.ReadInterrupt();
		iStopped.Wait();
	}

	switch (iPlayMode)
	{
	case eNone:
		break;
	case eMulticast:
		iProtocolMulticast->Stop();
		iStopped.Wait();
		break;
	case eUnicast:
		iProtocolUnicast->Stop();
		iStopped.Wait();
		break;
	case eNull:
		iNullStop.Signal();
		iStopped.Wait();
		break;
	}

	iMutexTransport.Wait();

	Reset();

	iTransportState = eStopped;
	iDriver->Stopped();

	iMutexMode.Signal();
}

void OhmReceiver::Run()
{
	for (;;) {
		iThread->Wait();

		if (iTerminating) {
			break;
		}

		TUint ttl(iTtl);
		TIpAddress iface(iInterface);
		Endpoint endpoint(iEndpoint);

		switch (iPlayMode) {
        case eNone:
			ASSERTS();
		case eMulticast:
			iPlaying.Signal();
			iProtocolMulticast->Play(iface, ttl, endpoint);
			break;
		case eUnicast:
			iPlaying.Signal();
			iProtocolUnicast->Play(iface, ttl, endpoint);
			break;
		case eNull:
			iPlaying.Signal();
			iNullStop.Wait();
			break;
		}

		iStopped.Signal();
	}
}

void OhmReceiver::SendZoneQuery()
{
	OhzHeaderZoneQuery headerZoneQuery(iZone);
	OhzHeader header(OhzHeader::kMsgTypeZoneQuery, headerZoneQuery.MsgBytes());

	WriterBuffer writer(iTxZone);
        
    writer.Flush();
    header.Externalise(writer);
    headerZoneQuery.Externalise(writer);
    writer.Write(iZone);

	iSocketZone.Send(iTxZone);

	iTimerZoneQuery.FireIn(kTimerZoneQueryDelayMs);
}

void OhmReceiver::RunZone()
{
    for (;;) {
        iThreadZone->Wait();

		if (iTerminating) {
			break;
		}

		iSocketZone.Open(iInterface, iTtl);
		iZoning.Signal();
		SendZoneQuery();

		try {
			for (;;) {
				OhzHeader header;
	        
				for (;;) {
        			try {
						header.Internalise(iRxZone);
						break;
					}
					catch (OhzError&) {
						iRxZone.ReadFlush();
					}
				}

				if (header.MsgType() == OhzHeader::kMsgTypeZoneUri) {
					OhzHeaderZoneUri headerZoneUri;
					headerZoneUri.Internalise(iRxZone, header);

					Brn msgZone = iRxZone.Read(headerZoneUri.ZoneBytes());
					Brn msgUri = iRxZone.Read(headerZoneUri.UriBytes());

					if (msgZone == iZone)
					{
						iTimerZoneQuery.Cancel();
						PlayZoneMode(msgUri);
					}
				}

				iRxZone.ReadFlush();
			}
		}
		catch (ReaderError&) {
		}

		iRxZone.ReadFlush();
		iTimerZoneQuery.Cancel();
		iSocketZone.Close();
        iStopped.Signal();
	}
}

TUint OhmReceiver::Latency(OhmMsgAudio& aMsg)
{
	TUint latency = aMsg.MediaLatency();

	if (latency != 0) {

		TUint multiplier = 48000 * 256;

		if ((aMsg.SampleRate() % 441) == 0)
		{
			multiplier = 44100 * 256;
		}

		latency = latency * 1000 / multiplier;

		LOG(kMedia, "LATENCY %d\n", latency);

		return (latency);
	}

	LOG(kMedia, "LATENCY %d\n", kDefaultLatency);

	return (kDefaultLatency);
}

void OhmReceiver::Reset()
{
	iTimerRepair.Cancel();

	if (iRepairing) {

		iRepairFirst->RemoveRef();

		while (iFifoRepair.SlotsUsed() > 0) {
			iFifoRepair.Read()->RemoveRef();
		}
	}

	iRepairing = false;

	iLatency = 0;
}

TBool OhmReceiver::RepairBegin(OhmMsgAudio& aMsg)
{
	LOG(kMedia, "BEGIN ON %d\n", aMsg.Frame());

	iRepairFirst = &aMsg;

    iTimerRepair.FireIn(Random(kInitialRepairTimeoutMs)); 

	return (true);
}

void  OhmReceiver::RepairReset()
{
	LOG(kMedia, "RESET\n");

	iTimerRepair.Cancel();

	iRepairFirst->RemoveRef();

	while (iFifoRepair.SlotsUsed() > 0) {
		iFifoRepair.Read()->RemoveRef();
	}

	iTransportState = eDisconnected;
	iDriver->Disconnected();

	iLatency = 0;
}

TBool OhmReceiver::Repair(OhmMsgAudio& aMsg)
{
	// get the incoming frame number

	TUint frame = aMsg.Frame();

	LOG(kMedia, "GOT %d\n", frame);

	// get difference between this and the last frame send down the pipeline

	TInt diff = frame - iFrame;

	if (diff == 1) {
		// incoming frame is one greater than the last frame sent down the pipeline, so send this ...

		iFrame++;

		iDriver->Add(aMsg);

		// ... and see if the current first waiting frame is now also ready to be sent

		while (iRepairFirst->Frame() == iFrame + 1) {
			// ... yes, it is, so send it

			iFrame++;

			iDriver->Add(*iRepairFirst);

			// ... and see if there are further messages waiting in the fifo

			if (iFifoRepair.SlotsUsed() == 0) {
				// ... no, so we have completed the repair

				LOG(kMedia, "END\n");

				return (false);
			}

			// ... yes, so update the current first waiting frame and continue testing to see if this can also be sent

			iRepairFirst = iFifoRepair.Read();
		}

		// ... we're done

		return (true);
	}

	if (diff < 1) {
		// incoming frames is equal to or earlier than the last frame sent down the pipeline
		// in other words, it's a duplicate, so so discard it and continue

		aMsg.RemoveRef();

		return (true);
	}

	// Ok, its a frame that needs to be put into the backlog, but where?

	// compare it to the current first waiting frame

	diff = frame - iRepairFirst->Frame();

	if (diff < 0) {
		// it's earlier than the current first waiting message, so it should become the new current first waiting frame
		// and the old first waiting frame needs to be injected into the start of the backlog, so inject it into the end
		// and rotate the others (if there is space to add another frame)

		TUint count = iFifoRepair.SlotsUsed();

		if (count == kMaxRepairBacklogFrames) {
			// can't put another frame into the backlog

			RepairReset();

			return (false);
		}

		iFifoRepair.Write(iRepairFirst);

		if (count == 0) {
			iRepairLast = iRepairFirst->Frame();
		}

		for (TUint i = 0; i < count; i++) {
			iFifoRepair.Write(iFifoRepair.Read());
		}

		// replace the currently waiting message with this new one

		iRepairFirst = &aMsg;

		return (true);
	}

	if (diff == 0) {
		// it's equal to the currently first waiting frame, so discard it - it's a duplicate

		aMsg.RemoveRef();

		return (true);
	}

	// ok, it's after the currently first waiting frame, so it needs to go into the backlog

	// first check if the backlog is empty

	if (iFifoRepair.SlotsUsed() == 0) {
		// ... yes, so just inject it

		iFifoRepair.Write(&aMsg);

		// ... and always keep track of the latest frame in the backlog
		iRepairLast = frame;

		return (true);
	}

	// ok, so the backlog is not empty

	// is the incoming frame later than the last one currently in the backlog?

	diff = frame - iRepairLast;

	if (diff > 0) {
		// ... yes, so, again, just inject it (if there is space)

		TUint count = iFifoRepair.SlotsUsed();

		if (count == kMaxRepairBacklogFrames) {
			// can't put another frame into the backlog
			RepairReset();

			return (false);
		}

		iFifoRepair.Write(&aMsg);

		// ... and update the record of the last frame in the backlog

		iRepairLast = frame;

		return (true);
	}

	// is it a duplicate of the last frame in the backlog?

	if (diff == 0) {
		// ... yes, so discard
		aMsg.RemoveRef();

		return (true);
	}

	// ... no, so it has to go somewhere in the middle of the backlog, so iterate through and inject it at the right place (if there is space)

	TUint count = iFifoRepair.SlotsUsed();

	TBool found = false;

	for (TUint i = 0; i < count; i++) {
		OhmMsgAudio* msg = iFifoRepair.Read();
					
		if (!found) {
			diff = frame - msg->Frame();

			if (diff < 0) {
				if (count == kMaxRepairBacklogFrames) {
					// can't put another frame into the backlog
					iFifoRepair.Write(&aMsg);
					RepairReset();
					return (false);
				}

				iFifoRepair.Write(&aMsg);
				found = true;
			}
			else if (diff == 0) {
				aMsg.RemoveRef();
				found = true;
			}
		}

		iFifoRepair.Write(msg);
	}

	return (true);
}


void OhmReceiver::TimerRepairExpired()
{
	iMutexTransport.Wait();

	if (iRepairing) {
		LOG(kMedia, "REQUEST RESEND");

		Bws<kMaxRepairMissedFrames * 4> missed;
		WriterBuffer buffer(missed);
		WriterBinary writer(buffer);

		TUint count = 0;

		TUint start = iFrame + 1;
		TUint end = iRepairFirst->Frame();

		// phase 1 - request the frames between the last sent down the pipeline and the first waiting frame

		for (TUint i = start; i < end; i++) {
			writer.WriteUint32Be(i);
			LOG(kMedia, " %d", i);
			if (++count == kMaxRepairMissedFrames) {
				break;
			}
		}

		// phase 2 - if there is room add the missing frames in the backlog

		if (count < kMaxRepairMissedFrames) {
			TUint slots = iFifoRepair.SlotsUsed();

			for (TUint j = 0; j < slots; j++) {
				OhmMsgAudio* msg = iFifoRepair.Read();
				if (count < kMaxRepairMissedFrames) {
					start = end + 1;
					end = msg->Frame();
					for (TUint i = start; i < end; i++) {
						writer.WriteUint32Be(i);
						LOG(kMedia, " %d", i);
						if (++count == kMaxRepairMissedFrames) {
							break;
						}
					}
				}
				iFifoRepair.Write(msg);
			}
		}

		LOG(kMedia, "\n");

		switch (iPlayMode) {
		case eMulticast:
			iProtocolMulticast->RequestResend(missed);
			break;
		case eUnicast:
			iProtocolUnicast->RequestResend(missed);
			break;
		default:
			break;
		}

		// iTimerRepair.FireIn(Random(iLatency >> 1)); // check again a random time 1/2 of the audio latency
		iTimerRepair.FireIn(kSubsequentRepairTimeoutMs); // check again a random time 1/2 of the audio latency
	}

	iMutexTransport.Signal();
}

// IOhmReceiver

void OhmReceiver::Add(OhmMsg& aMsg)
{
	iDriver->Timestamp(aMsg);

	iMutexTransport.Wait();

	aMsg.Process(*this);

	iMutexTransport.Signal();
}

void OhmReceiver::ResendSeen()
{
	iMutexTransport.Wait();

	if (iRepairing) {
		// iTimerRepair.FireIn(Random(iLatency >> 2)); // delay repair timer by a random time between 0 and 1/4 of the audio latency
		iTimerRepair.FireIn(kSubsequentRepairTimeoutMs); // delay repair timer by a random time between 0 and 1/4 of the audio latency
	}

	iMutexTransport.Signal();
}

// IOhmMsgProcessor

void OhmReceiver::Process(OhmMsgAudio& aMsg)
{
	if (iLatency == 0) {
		iFrame = aMsg.Frame();
		iLatency = Latency(aMsg);
		iTransportState = ePlaying;
		iDriver->Playing();
		iDriver->Add(aMsg);
		return;
	}
	
	if (iRepairing) {
		iRepairing = Repair(aMsg);
		return;
	}

	TInt diff = aMsg.Frame() - iFrame;

	if (diff == 1) {
		iFrame++;
		iDriver->Add(aMsg);
	}
	else if (diff < 1) {
		aMsg.RemoveRef();
	}
	else {
		iRepairing = RepairBegin(aMsg);
	}
}

void OhmReceiver::Process(OhmMsgTrack& aMsg)
{
	if (iTransportState == eStarted) {
		iTransportState = eConnected;
		iDriver->Connected();
	}

	iDriver->Add(aMsg);
}

void OhmReceiver::Process(OhmMsgMetatext& aMsg)
{
	if (iTransportState == eStarted) {
		iTransportState = eConnected;
		iDriver->Connected();
	}

	iDriver->Add(aMsg);
}
