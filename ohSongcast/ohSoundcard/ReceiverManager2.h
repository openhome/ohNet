#ifndef HEADER_RECEIVER_MANAGER2
#define HEADER_RECEIVER_MANAGER2

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpAvOpenhomeOrgReceiver1.h>

#include "ReceiverManager1.h"

namespace OpenHome {
namespace Net {

class ReceiverManager2Receiver;

class IReceiverManager2Handler
{
public:
	virtual void ReceiverAdded(ReceiverManager2Receiver& aReceiver) = 0;
	virtual void ReceiverChanged(ReceiverManager2Receiver& aReceiver) = 0;
	virtual void ReceiverRemoved(ReceiverManager2Receiver& aReceiver) = 0;
	~IReceiverManager2Handler() {}
};

typedef void (IReceiverManager2Handler::*IReceiverManager2HandlerFunction)(ReceiverManager2Receiver&);

class ReceiverManager2Job
{
public:
	ReceiverManager2Job(IReceiverManager2Handler& aHandler);
	void Set(ReceiverManager2Receiver& aReceiver, IReceiverManager2HandlerFunction aFunction);
    virtual void Execute();

private:
	IReceiverManager2Handler* iHandler;
	ReceiverManager2Receiver* iReceiver;
	IReceiverManager2HandlerFunction iFunction;
};


class ReceiverManager2Receiver
{
public:
	ReceiverManager2Receiver(IReceiverManager2Handler& aHandler, ReceiverManager1Receiver& aReceiver);
	CpDevice& Device() const;
	const Brx& Room() const;
	const Brx& Group() const;
	const Brx& Name() const;
	TBool Selected() const;
	void TransportState(Bwx& aValue) const;
	void SenderUri(Bwx& aValue) const;
	void SenderMetadata(Bwx& aValue) const;

	void SetSender(const Brx& aUri, const Brx& aMetadata);
	void Play();
	void Stop();
	void Standby();

	void AddRef();
    void RemoveRef();
    void SetUserData(void* aValue);
	void* UserData() const;

	void ChangedSelected(); 
	void Removed();

	void CallbackPlay(IAsync& aAsync);		
	void CallbackStop(IAsync& aAsync);		
	void CallbackSetSender(IAsync& aAsync);		

	void EventReceiverInitialEvent();
	void EventReceiverTransportStateChanged();	
	void EventReceiverUriChanged();	

	~ReceiverManager2Receiver();

private:
	IReceiverManager2Handler& iHandler;
	ReceiverManager1Receiver& iReceiver;
	mutable Mutex iMutex;
	CpProxyAvOpenhomeOrgReceiver1* iServiceReceiver;
    TUint iRefCount;
	void* iUserData;
	FunctorAsync iFunctorStop;
	FunctorAsync iFunctorPlay;
	FunctorAsync iFunctorSetSender;
	Brhz iTransportState;
	Brhz iUri;
	Brhz iMetadata;
};

class ReceiverManager2 : public IReceiverManager1Handler, public IReceiverManager2Handler
{
	static const TUint kMaxJobCount = 20;

public:
	ReceiverManager2(IReceiverManager2Handler& aHandler);
    void Refresh();
    ~ReceiverManager2();

private:
	// IReceiverManager1Handler
	virtual void ReceiverAdded(ReceiverManager1Receiver& aReceiver);
	virtual void ReceiverChanged(ReceiverManager1Receiver& aReceiver);
	virtual void ReceiverRemoved(ReceiverManager1Receiver& aReceiver);

	// IReceiverManager2Handler
	virtual void ReceiverAdded(ReceiverManager2Receiver& aReceiver);
	virtual void ReceiverChanged(ReceiverManager2Receiver& aReceiver);
	virtual void ReceiverRemoved(ReceiverManager2Receiver& aReceiver);

	void Run();

private:
	IReceiverManager2Handler& iHandler;
	Fifo<ReceiverManager2Job*> iFree;
	Fifo<ReceiverManager2Job*> iReady;
    ReceiverManager1* iReceiverManager;
	ThreadFunctor* iThread;
};


/*
	enum EStatus {
		eOff,
		eOn,
		eListening
	};

	EStatus Status() const;
	TUint ReceiverCount() const;
	const Brx& ReceiverRoom(TUint aIndex) const;
	const Brx& ReceiverGroup(TUint aIndex) const;
	void Select(Brx& aReceiverRoom, Brx& aReceiverGroup);
*/

} // namespace Net
} // namespace OpenHome

#endif // HEADER_RECEIVER_MANAGER1

