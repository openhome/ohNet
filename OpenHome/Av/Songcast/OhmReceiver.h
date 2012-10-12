#ifndef HEADER_OHMRECEIVER
#define HEADER_OHMRECEIVER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Fifo.h>

#include "Ohm.h"
#include "OhmMsg.h"
#include "OhmSocket.h"

namespace OpenHome {
namespace Av {

enum EOhmReceiverTransportState
{
	eStopped,
	eStarted,
	eConnected,
	ePlaying,
	eDisconnected
};

enum EOhmReceiverPlayMode
{
	eNone,
	eMulticast,
	eUnicast,
	eNull,
};

// IOhmReceiverDriver defines the interface between the OhmReceiver and the msg pipeline
// OhmReceiver guarantees a continuous sequence of audio frames are passed to the driver

class IOhmReceiverDriver
{
public:
	virtual void Add(OhmMsg& aMsg) = 0;
	virtual void Timestamp(OhmMsg& aMsg) = 0;
	virtual void Started() = 0;
	virtual void Connected() = 0;
	virtual void Playing() = 0;
	virtual void Disconnected() = 0;
	virtual void Stopped() = 0;
	virtual ~IOhmReceiverDriver() {}
};

// IOhmReceiver defines the interface between the OhmProtocols and OhmReceiver

class IOhmReceiver
{
public:
	virtual void Add(OhmMsg& aMsg) = 0;
	virtual void ResendSeen() = 0;
	virtual ~IOhmReceiver() {}
};

class OhmProtocolMulticast
{
    static const TUint kMaxFrameBytes = 16*1024;
    static const TUint kAddMembershipDelayMs = 100;
    
    static const TUint kTimerJoinTimeoutMs = 300;
    static const TUint kTimerListenTimeoutMs = 10000;
    
public:
	OhmProtocolMulticast(IOhmReceiver& aReceiver, IOhmMsgFactory& aFactory);
    void Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint);
	void Stop();
	void RequestResend(const Brx& aFrames);

private:
    void SendJoin();
    void SendListen();
    void Send(TUint aType);

private:
	IOhmReceiver* iReceiver;
	IOhmMsgFactory* iFactory;
    OhmSocket iSocket;
    Srs<kMaxFrameBytes> iReadBuffer;
    Endpoint iEndpoint;
    Timer iTimerJoin;
    Timer iTimerListen;
};

class OhmProtocolUnicast
{
    static const TUint kMaxFrameBytes = 16*1024;
    static const TUint kAddMembershipDelayMs = 100;
    
    static const TUint kTimerJoinTimeoutMs = 300;
    static const TUint kTimerListenTimeoutMs = 10000;
    static const TUint kTimerLeaveTimeoutMs = 50;
	static const TUint kMaxSlaveCount = 4;
    
public:
	OhmProtocolUnicast(IOhmReceiver& aReceiver, IOhmMsgFactory& aFactory);
	void SetInterface(TIpAddress aValue);
    void SetTtl(TUint aValue);
    void Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint);
	void Stop();
	void EmergencyStop();
	void RequestResend(const Brx& aFrames);

private:
	void HandleAudio(const OhmHeader& aHeader);
	void HandleTrack(const OhmHeader& aHeader);
	void HandleMetatext(const OhmHeader& aHeader);
	void HandleSlave(const OhmHeader& aHeader);
	void Broadcast(OhmMsg& aMsg);
    void SendJoin();
    void SendListen();
    void SendLeave();
    void Send(TUint aType);
    void TimerLeaveExpired();

private:
	IOhmReceiver* iReceiver;
	IOhmMsgFactory* iFactory;
    OhmSocket iSocket;
    Srs<kMaxFrameBytes> iReadBuffer;
    Endpoint iEndpoint;
    Timer iTimerJoin;
    Timer iTimerListen;
    Timer iTimerLeave;
	TBool iLeaving;
	TUint iSlaveCount;
    Endpoint iSlaveList[kMaxSlaveCount];
	Bws<kMaxFrameBytes> iMessageBuffer;
};

class OhmReceiver : public IOhmReceiver, public IOhmMsgProcessor
{
    static const TUint kThreadPriority = kPriorityNormal;
    static const TUint kThreadStackBytes = 64 * 1024;

    static const TUint kThreadZonePriority = kPriorityNormal;
    static const TUint kThreadZoneStackBytes = 64 * 1024;

	static const TUint kMaxUriBytes = 100;

	static const TUint kMaxZoneBytes = 100;
	static const TUint kMaxZoneFrameBytes = 1024;

	static const TUint kTimerZoneQueryDelayMs = 100;

	static const TUint kDefaultLatency = 50;

	static const TUint kMaxRepairBacklogFrames = 200;
	static const TUint kMaxRepairMissedFrames = 20;

	static const TUint kInitialRepairTimeoutMs = 10;
	static const TUint kSubsequentRepairTimeoutMs = 30;

public:
    OhmReceiver(TIpAddress aInterface, TUint aTtl, IOhmReceiverDriver& aDriver);

	TIpAddress Interface() const;
	TUint Ttl() const;

	void SetInterface(TIpAddress aValue);
    void SetTtl(TUint aValue);

	void Play(const Brx& aUri);
	void Stop();
    
    ~OhmReceiver();

private:
	void Run();
	void RunZone();
	void StopLocked();
	void SendZoneQuery();
	void PlayZoneMode(const Brx& aUri);
	void Reset();
	void RepairReset();
	void TimerRepairExpired();

	TBool RepairBegin(OhmMsgAudio& aMsg);
	TBool Repair(OhmMsgAudio& aMsg);

	TUint Latency(OhmMsgAudio& aMsg);
	
	// IOhmReceiver
	virtual void Add(OhmMsg& aMsg);
	virtual void ResendSeen();

	// IOhmMsgProcessor
	virtual void Process(OhmMsgAudio& aMsg);
	virtual void Process(OhmMsgTrack& aMsg);
	virtual void Process(OhmMsgMetatext& aMsg);

private:
	TIpAddress iInterface;
	TUint iTtl;
    IOhmReceiverDriver* iDriver;
	ThreadFunctor* iThread;
	ThreadFunctor* iThreadZone;
	mutable Mutex iMutexMode;
	mutable Mutex iMutexTransport;
	Semaphore iPlaying;
	Semaphore iZoning;
	Semaphore iStopped;
	Semaphore iNullStop;
	TUint iLatency;									// [iMutexTransport] 0 = first audio message of stream not yet received
	EOhmReceiverTransportState iTransportState;		// [iMutexTransport]
	EOhmReceiverPlayMode iPlayMode;
	TBool iZoneMode;
	TBool iTerminating;
	Endpoint iEndpointNull;
	OhmProtocolMulticast* iProtocolMulticast;
	OhmProtocolUnicast* iProtocolUnicast;
	OpenHome::Uri iUri;
	Endpoint iEndpoint;
	Endpoint iZoneEndpoint;
    OhzSocket iSocketZone;
    Bws<kMaxZoneBytes> iZone;
    Srs<kMaxZoneFrameBytes> iRxZone;
    Bws<kMaxZoneFrameBytes> iTxZone;
	Timer iTimerZoneQuery;
	OhmMsgFactory iFactory;
	TUint iFrame;
	TBool iRepairing;
	TUint iRepairLast;
	OhmMsgAudio* iRepairFirst;
	FifoLite<OhmMsgAudio*, kMaxRepairBacklogFrames> iFifoRepair;
	Timer iTimerRepair;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_OHMRECEIVER

