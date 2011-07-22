#include "ReceiverManager3.h"

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

// ReceiverManager3Receiver

ReceiverManager3Receiver::ReceiverManager3Receiver(IReceiverManager3Handler& aHandler, ReceiverManager2Receiver& aReceiver, ReceiverManager3& aManager)
	: iHandler(aHandler)
	, iReceiver(aReceiver)
	, iManager(aManager)
	, iRefCount(1)
	, iUserData(0)
{
	iReceiver.AddRef();
	iStatus = EvaluateStatus();
	iHandler.ReceiverAdded(*this);
}

ReceiverManager3Receiver::EStatus ReceiverManager3Receiver::EvaluateStatus()
{
	if (iReceiver.Selected()) {
		return (iManager.Status(iReceiver));
	}

	return (eDisconnected);
}

const Brx& ReceiverManager3Receiver::Udn() const
{
	return (iReceiver.Device().Udn());
}

const Brx& ReceiverManager3Receiver::Room() const
{
	return (iReceiver.Room());
}

const Brx& ReceiverManager3Receiver::Group() const
{
	return (iReceiver.Group());
}

const Brx& ReceiverManager3Receiver::Name() const
{
	return (iReceiver.Name());
}

ReceiverManager3Receiver::EStatus ReceiverManager3Receiver::Status() const
{
	return (iStatus);
}

void ReceiverManager3Receiver::Play()
{
	iManager.Play(iReceiver);
}

void ReceiverManager3Receiver::Stop()
{
	iManager.Stop(iReceiver);
}

void ReceiverManager3Receiver::Standby()
{
	iManager.Standby(iReceiver);
}

void ReceiverManager3Receiver::SetUserData(void* aValue)
{
	iUserData = aValue;
}

void* ReceiverManager3Receiver::UserData() const
{
	return (iUserData);
}

void ReceiverManager3Receiver::AddRef()
{
    iRefCount++;
}

void ReceiverManager3Receiver::RemoveRef()
{
	if (--iRefCount == 0) {
		delete (this);
    }
}

void ReceiverManager3Receiver::Changed()
{
	EStatus status = EvaluateStatus();

	if (iStatus != status) {
		iStatus = status;
		iHandler.ReceiverChanged(*this);
	}
}

void ReceiverManager3Receiver::Removed()
{
	iHandler.ReceiverRemoved(*this);
	RemoveRef();
}

ReceiverManager3Receiver::~ReceiverManager3Receiver()
{
	iReceiver.RemoveRef();
}

// ReceiverManager

ReceiverManager3::ReceiverManager3(IReceiverManager3Handler& aHandler, const Brx& aUri, const Brx& aMetadata)
	: iHandler(aHandler)
	, iUri(aUri)
	, iMetadata(aMetadata)
{
	iReceiverManager = new ReceiverManager2(*this);
}

void ReceiverManager3::Refresh()
{
	iReceiverManager->Refresh();
}

void ReceiverManager3::SetMetadata(const Brx& aMetadata)
{
	iMetadata.Replace(aMetadata);
}

ReceiverManager3Receiver::EStatus ReceiverManager3::Status(ReceiverManager2Receiver& aReceiver)
{
	Bws<kMaxUriBytes> uri;
	aReceiver.SenderUri(uri);

	if (uri != iUri) {
		return (ReceiverManager3Receiver::eDisconnected);
	}

	Bws<kMaxTransportStateBytes> state;
	aReceiver.TransportState(state);

	if (state == Brn("Stopped") ) {
		return (ReceiverManager3Receiver::eDisconnected);
	}

	if (state == Brn("Buffering") ) {
		return (ReceiverManager3Receiver::eConnecting);
	}

	return (ReceiverManager3Receiver::eConnected);
}

void ReceiverManager3::Play(ReceiverManager2Receiver& aReceiver)
{
	aReceiver.SetSender(iUri, iMetadata);
	aReceiver.Play();
}

void ReceiverManager3::Stop(ReceiverManager2Receiver& aReceiver)
{
	aReceiver.Stop();
}

void ReceiverManager3::Standby(ReceiverManager2Receiver& aReceiver)
{
	aReceiver.Standby();
}

ReceiverManager3::~ReceiverManager3()
{
	delete (iReceiverManager);
}

// IReceiverManager2Handler

void ReceiverManager3::ReceiverAdded(ReceiverManager2Receiver& aReceiver)
{
	ReceiverManager3Receiver* receiver = new ReceiverManager3Receiver(iHandler, aReceiver, *this);
	aReceiver.SetUserData(receiver);
}

void ReceiverManager3::ReceiverChanged(ReceiverManager2Receiver& aReceiver)
{
	ReceiverManager3Receiver* receiver = (ReceiverManager3Receiver*)(aReceiver.UserData());
	ASSERT(receiver);
	receiver->Changed();
}

void ReceiverManager3::ReceiverRemoved(ReceiverManager2Receiver& aReceiver)
{
	ReceiverManager3Receiver* receiver = (ReceiverManager3Receiver*)(aReceiver.UserData());
    LOG(kTopology, "ReceiverManager3::~ReceiverRemoved %x\n", receiver);
	ASSERT(receiver);
	receiver->Removed();
}
