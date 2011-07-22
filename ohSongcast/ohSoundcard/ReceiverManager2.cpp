#include "ReceiverManager2.h"

#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Debug.h>

// Assumes only one Receiver per group (UPnP device)

using namespace OpenHome;
using namespace OpenHome::Net;

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

// ReceiverManager2Job

ReceiverManager2Job::ReceiverManager2Job(IReceiverManager2Handler& aHandler)
{
	iHandler = &aHandler;
	iReceiver = 0;
}
	
void ReceiverManager2Job::Set(ReceiverManager2Receiver& aReceiver, IReceiverManager2HandlerFunction aFunction)
{
	iReceiver = &aReceiver;
	iFunction = aFunction;
	iReceiver->AddRef();
}

void ReceiverManager2Job::Execute()
{
	if (iReceiver) {
		(iHandler->*iFunction)(*iReceiver);
		iReceiver->RemoveRef();
		iReceiver = 0;
	}
	else {
		THROW(ThreadKill);
	}
}

// ReceiverManager2Receiver

ReceiverManager2Receiver::ReceiverManager2Receiver(IReceiverManager2Handler& aHandler, ReceiverManager1Receiver& aReceiver)
	: iHandler(aHandler)
	, iReceiver(aReceiver)
	, iMutex("RM2R")
	, iRefCount(1)
	, iUserData(0)
{
	iReceiver.AddRef();

    iFunctorStop = MakeFunctorAsync(*this, &ReceiverManager2Receiver::CallbackStop);
    iFunctorPlay = MakeFunctorAsync(*this, &ReceiverManager2Receiver::CallbackPlay);
    iFunctorSetSender = MakeFunctorAsync(*this, &ReceiverManager2Receiver::CallbackSetSender);

	iServiceReceiver = new CpProxyAvOpenhomeOrgReceiver1(iReceiver.Device());

	Functor functorInitial = MakeFunctor(*this, &ReceiverManager2Receiver::EventReceiverInitialEvent);

    iServiceReceiver->SetPropertyInitialEvent(functorInitial); 

	iServiceReceiver->Subscribe();
}

CpDevice& ReceiverManager2Receiver::Device() const
{
	return (iReceiver.Device());
}

const Brx& ReceiverManager2Receiver::Room() const
{
	return (iReceiver.Room());
}

const Brx& ReceiverManager2Receiver::Group() const
{
	return (iReceiver.Group());
}

const Brx& ReceiverManager2Receiver::Name() const
{
	return (iReceiver.Name());
}

TBool ReceiverManager2Receiver::Selected() const
{
	return (iReceiver.Selected());
}

void ReceiverManager2Receiver::TransportState(Bwx& aValue) const
{
	iMutex.Wait();
	try {
		aValue.ReplaceThrow(iTransportState);
	}
	catch (BufferOverflow) {
		aValue.Replace(Brx::Empty());
	}
	iMutex.Signal();
}

void ReceiverManager2Receiver::SenderUri(Bwx& aValue) const
{
	iMutex.Wait();
	try {
		aValue.ReplaceThrow(iUri);
	}
	catch (BufferOverflow) {
		aValue.Replace(Brx::Empty());
	}
	iMutex.Signal();
}

void ReceiverManager2Receiver::SenderMetadata(Bwx& aValue) const
{
	iMutex.Wait();
	try {
		aValue.ReplaceThrow(iMetadata);
	}
	catch (BufferOverflow) {
		aValue.Replace(Brx::Empty());
	}
	iMutex.Signal();
}

// Actions

void ReceiverManager2Receiver::Play()
{
	iReceiver.Select();
	iServiceReceiver->BeginPlay(iFunctorPlay);
}

void ReceiverManager2Receiver::Stop()
{
	iServiceReceiver->BeginStop(iFunctorStop);
}

void ReceiverManager2Receiver::Standby()
{
	iReceiver.Standby();
}

void ReceiverManager2Receiver::SetSender(const Brx& aUri, const Brx& aMetadata)
{
	iServiceReceiver->BeginSetSender(aUri, aMetadata, iFunctorSetSender);
}

// Action callbacks

void ReceiverManager2Receiver::CallbackStop(IAsync& /* aAsync */)
{
}

void ReceiverManager2Receiver::CallbackPlay(IAsync& /* aAsync */)
{
}

void ReceiverManager2Receiver::CallbackSetSender(IAsync& /* aAsync */)
{
}

// Event handlers

void ReceiverManager2Receiver::EventReceiverInitialEvent()
{
    Functor functorTransportState = MakeFunctor(*this, &ReceiverManager2Receiver::EventReceiverTransportStateChanged);
    Functor functorUri = MakeFunctor(*this, &ReceiverManager2Receiver::EventReceiverUriChanged);

    iServiceReceiver->SetPropertyTransportStateChanged(functorTransportState);    
    iServiceReceiver->SetPropertyUriChanged(functorUri); 
      
	iServiceReceiver->PropertyTransportState(iTransportState);
	iServiceReceiver->PropertyUri(iUri);
	iServiceReceiver->PropertyMetadata(iMetadata);

	iHandler.ReceiverAdded(*this);
}

void ReceiverManager2Receiver::EventReceiverTransportStateChanged()
{
	iMutex.Wait();
	iServiceReceiver->PropertyTransportState(iTransportState);
	iMutex.Signal();
	iHandler.ReceiverChanged(*this);
}

void ReceiverManager2Receiver::EventReceiverUriChanged()
{
	iMutex.Wait();
	iServiceReceiver->PropertyUri(iUri);
	iServiceReceiver->PropertyMetadata(iMetadata);
	iMutex.Signal();
	iHandler.ReceiverChanged(*this);
}

void ReceiverManager2Receiver::ChangedSelected()
{
	iHandler.ReceiverChanged(*this);
}

void ReceiverManager2Receiver::Removed()
{
	iHandler.ReceiverRemoved(*this);
	RemoveRef();
}

// Public API

void ReceiverManager2Receiver::AddRef()
{
	iRefCount++;
}

void ReceiverManager2Receiver::RemoveRef()
{
	if (--iRefCount == 0) {
		delete (this);
	}
}

void ReceiverManager2Receiver::SetUserData(void* aValue)
{
	iUserData = aValue;
}

void* ReceiverManager2Receiver::UserData() const
{
	return (iUserData);
}

ReceiverManager2Receiver::~ReceiverManager2Receiver()
{
	delete (iServiceReceiver);
	iReceiver.RemoveRef();
}

// ReceiverManager

ReceiverManager2::ReceiverManager2(IReceiverManager2Handler& aHandler)
	: iHandler(aHandler)
	, iFree(kMaxJobCount)
	, iReady(kMaxJobCount)
{
	for (TUint i = 0; i < kMaxJobCount; i++) {
		iFree.Write(new ReceiverManager2Job(aHandler));
	}
	
	iReceiverManager = new ReceiverManager1(*this);

	iThread = new ThreadFunctor("RM2T", MakeFunctor(*this, &ReceiverManager2::Run));
	iThread->Start();
}

void ReceiverManager2::Refresh()
{
	iReceiverManager->Refresh();
}

ReceiverManager2::~ReceiverManager2()
{
    LOG(kTopology, "ReceiverManager2::~ReceiverManager2\n");

	delete (iReceiverManager);
    
	iReady.Write(iFree.Read()); // this null job causes the thread to complete

	delete (iThread);
	
    LOG(kTopology, "ReceiverManager2::~ReceiverManager2 deleted thread\n");

	for (TUint i = 0; i < kMaxJobCount; i++) {
		delete (iFree.Read());
	}

    LOG(kTopology, "ReceiverManager2::~ReceiverManager2 deleted jobs\n");
}

// IReceiverManager1Handler

void ReceiverManager2::ReceiverAdded(ReceiverManager1Receiver& aReceiver)
{
	ReceiverManager2Receiver* receiver = new ReceiverManager2Receiver(*this, aReceiver);
	aReceiver.SetUserData(receiver);
}

void ReceiverManager2::ReceiverChanged(ReceiverManager1Receiver& aReceiver)
{
	ReceiverManager2Receiver* receiver = (ReceiverManager2Receiver*)(aReceiver.UserData());
	ASSERT(receiver);
	receiver->ChangedSelected();
}

void ReceiverManager2::ReceiverRemoved(ReceiverManager1Receiver& aReceiver)
{
	ReceiverManager2Receiver* receiver = (ReceiverManager2Receiver*)(aReceiver.UserData());
	ASSERT(receiver);
	receiver->Removed();
}

// IReceiverManager2Handler

void ReceiverManager2::ReceiverAdded(ReceiverManager2Receiver& aReceiver)
{
	ReceiverManager2Job* job = iFree.Read();
	job->Set(aReceiver, &IReceiverManager2Handler::ReceiverAdded);
	iReady.Write(job);
}

void ReceiverManager2::ReceiverChanged(ReceiverManager2Receiver& aReceiver)
{
	ReceiverManager2Job* job = iFree.Read();
	job->Set(aReceiver, &IReceiverManager2Handler::ReceiverChanged);
	iReady.Write(job);
}

void ReceiverManager2::ReceiverRemoved(ReceiverManager2Receiver& aReceiver)
{
	ReceiverManager2Job* job = iFree.Read();
	job->Set(aReceiver, &IReceiverManager2Handler::ReceiverRemoved);
	iReady.Write(job);
}


void ReceiverManager2::Run()
{
    LOG(kTopology, "ReceiverManager2::Run Started\n");

    for (;;)
    {
	    LOG(kTopology, "ReceiverManager2::Run wait for job\n");

    	ReceiverManager2Job* job = iReady.Read();
    	
	    LOG(kTopology, "ReceiverManager2::Run execute job\n");

    	try {
	    	job->Execute();
	    	iFree.Write(job);
	    }
	    catch (ThreadKill)
	    {
	    	iFree.Write(job);
	    	break;
	    }
    }

    LOG(kTopology, "ReceiverManager2::Run Exiting\n");
}
