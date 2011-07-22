#include "ReceiverManager1.h"

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

// ReceiverManager1Room

ReceiverManager1Room::ReceiverManager1Room(IReceiverManager1Handler& aHandler, IRoom& aRoom)
	: iHandler(aHandler)
	, iRoom(aRoom)
	, iSelected(0)
	, iRefCount(1)
{
	iRoom.AddRef();

	TUint count = iRoom.SourceCount();

	CpDevice* selectedDevice = 0;

	if (iRoom.CurrentSourceType() == Brn("Receiver")) {
		selectedDevice = &iRoom.CurrentSourceDevice();
	}

	for (TUint i = 0; i < count; i++) {
		if (iRoom.SourceType(i) == Brn("Receiver")) {
			CpDevice& device = iRoom.SourceDevice(i);
			const Brx& group = iRoom.SourceGroup(i);
			const Brx& name = iRoom.SourceName(i);

			ReceiverManager1Receiver* receiver = new ReceiverManager1Receiver(*this, group, name, i, device);

			if (selectedDevice == &device) {
				iSelected = receiver;
			}

			iReceiverList.push_back(receiver);
			iHandler.ReceiverAdded(*receiver);
		}
	}
}

IRoom& ReceiverManager1Room::Room() const
{
	return (iRoom);
}

const Brx& ReceiverManager1Room::Name() const
{
	return (iRoom.Name());
}

void ReceiverManager1Room::AddRef()
{
    iRefCount++;
}

void ReceiverManager1Room::RemoveRef()
{
	if (--iRefCount == 0) {
        delete this;
    }
}

void ReceiverManager1Room::SourceChanged()
{
	if (iSelected) {
		ReceiverManager1Receiver* receiver = iSelected;
		iSelected = 0;
		iHandler.ReceiverChanged(*receiver);
	}

	if (iRoom.CurrentSourceType() == Brn("Receiver")) {
		CpDevice& device = iRoom.CurrentSourceDevice();

		std::vector<ReceiverManager1Receiver*>::iterator it = iReceiverList.begin();

		while (it != iReceiverList.end()) {
			ReceiverManager1Receiver* receiver = *it;
			if (&receiver->Device() == &device) {
				iSelected = receiver;
				iHandler.ReceiverChanged(*iSelected);
				break;
			}
			it++;
		}
	}
}

void ReceiverManager1Room::Changed()
{
	TUint count = iRoom.SourceCount();

	CpDevice* selectedDevice = 0;

	if (iRoom.CurrentSourceType() == Brn("Receiver")) {
		selectedDevice = &iRoom.CurrentSourceDevice();
	}

	std::vector<ReceiverManager1Receiver*> toadd;
	std::vector<ReceiverManager1Receiver*> todelete;
	std::vector<ReceiverManager1Receiver*>::iterator it;

	// create initial toadd list

	for (TUint i = 0; i < count; i++) {
		if (iRoom.SourceType(i) == Brn("Receiver")) {
			CpDevice& device = iRoom.SourceDevice(i);
			const Brx& group = iRoom.SourceGroup(i);
			const Brx& name = iRoom.SourceName(i);

			ReceiverManager1Receiver* receiver = new ReceiverManager1Receiver(*this, group, name, i, device);

			toadd.push_back(receiver);
		}
	}

	// scan old list

	it = iReceiverList.begin();

	while (it != iReceiverList.end()) {
		ReceiverManager1Receiver* receiver = *it;

		TBool found = false;

		std::vector<ReceiverManager1Receiver*>::iterator it2 = toadd.begin();

		while (it2 != toadd.end()) {
			ReceiverManager1Receiver* candidate = *it2;
			if (candidate->Device().Udn() == receiver->Device().Udn()) {
				receiver->SetSourceIndex(candidate->SourceIndex()); // update source index
				delete (candidate);
				toadd.erase(it2);
				found = true;
				break;
			}

			it2++;
		}

		if (!found) {
			todelete.push_back(receiver);
		}

		it++;
	}

	// apply todelete list

	it = todelete.begin();

	while (it != todelete.end()) {
		ReceiverManager1Receiver* receiver = *it;

		std::vector<ReceiverManager1Receiver*>::iterator it2 = iReceiverList.begin();

		while (it2 != iReceiverList.end()) {
			if (receiver == *it2) {
				if (&receiver->Device() == selectedDevice) {
					iSelected = 0;
				}
				iHandler.ReceiverRemoved(*receiver);
				receiver->RemoveRef();
				iReceiverList.erase(it2);
				break;
			}

			it2++;
		}

		it++;
	}

	// apply toadd list

	it = toadd.begin();

	while (it != toadd.end()) {
		ReceiverManager1Receiver* receiver = *it;
		iReceiverList.push_back(receiver);
		if (&receiver->Device() == selectedDevice) {
			iSelected = receiver;
		}
		iHandler.ReceiverAdded(*receiver);
		it++;
	}
}

void ReceiverManager1Room::Removed()
{
	std::vector<ReceiverManager1Receiver*>::iterator it = iReceiverList.begin();

	while (it != iReceiverList.end()) {
		ReceiverManager1Receiver* receiver = *it;
		iHandler.ReceiverRemoved(*receiver);
		receiver->RemoveRef();
		it++;
	}

	RemoveRef();
}

TBool ReceiverManager1Room::Selected(const ReceiverManager1Receiver& aReceiver)
{
	return (iSelected == &aReceiver);
}

void ReceiverManager1Room::Select(const ReceiverManager1Receiver& aReceiver)
{
	iRoom.SetSourceIndex(aReceiver.SourceIndex());
}

void ReceiverManager1Room::Standby()
{
	iRoom.SetStandby(true);
}

ReceiverManager1Room::~ReceiverManager1Room()
{
	iRoom.RemoveRef();
}

// ReceiverManager1Receiver

ReceiverManager1Receiver::ReceiverManager1Receiver(ReceiverManager1Room& aRoom, const Brx& aGroup, const Brx& aName, TUint aSourceIndex, CpDevice& aDevice)
	: iRoom(aRoom)
	, iGroup(aGroup)
	, iName(aName)
	, iSourceIndex(aSourceIndex)
	, iDevice(aDevice)
	, iUserData(0)
	, iRefCount(1)
{
	iRoom.AddRef();
}

const Brx& ReceiverManager1Receiver::Room() const
{
	return (iRoom.Name());
}

const Brx& ReceiverManager1Receiver::Group() const
{
	return (iGroup);
}

const Brx& ReceiverManager1Receiver::Name() const
{
	return (iName);
}

TBool ReceiverManager1Receiver::Selected() const
{
	return (iRoom.Selected(*this));
}

void ReceiverManager1Receiver::Select()
{
	iRoom.Select(*this);
}

void ReceiverManager1Receiver::Standby()
{
	iRoom.Standby();
}

CpDevice& ReceiverManager1Receiver::Device() const
{
	return (iDevice);
}

void ReceiverManager1Receiver::SetUserData(void* aValue)
{
	iUserData = aValue;
}

void* ReceiverManager1Receiver::UserData() const
{
	return (iUserData);
}

void ReceiverManager1Receiver::AddRef()
{
    iRefCount++;
}

void ReceiverManager1Receiver::RemoveRef()
{
	if (--iRefCount == 0) {
		return;
    }
}

TUint ReceiverManager1Receiver::SourceIndex() const
{
	return (iSourceIndex);
}

void ReceiverManager1Receiver::SetSourceIndex(TUint aValue)
{
	iSourceIndex = aValue;
}


ReceiverManager1Receiver::~ReceiverManager1Receiver()
{
	iRoom.RemoveRef();
}

// ReceiverManager

ReceiverManager1::ReceiverManager1(IReceiverManager1Handler& aHandler)
	: iHandler(aHandler)
{
	iHouse = new House(*this);
}

void ReceiverManager1::Refresh()
{
	iHouse->Refresh();
}

ReceiverManager1::~ReceiverManager1()
{
	delete (iHouse);
}

void ReceiverManager1::RoomAdded(IRoom& aRoom)
{
	ReceiverManager1Room* room = new ReceiverManager1Room(iHandler, aRoom);
	aRoom.SetUserData(room);
}

void ReceiverManager1::RoomChanged(IRoom& aRoom)
{
	ReceiverManager1Room* room = (ReceiverManager1Room*)(aRoom.UserData());
	ASSERT(room);
	room->Changed();
}

void ReceiverManager1::RoomRemoved(IRoom& aRoom)
{
	ReceiverManager1Room* room = (ReceiverManager1Room*)(aRoom.UserData());
	ASSERT(room);
	room->Removed();
}

void ReceiverManager1::RoomStandbyChanged(IRoom& /* aRoom */)
{
}

void ReceiverManager1::RoomSourceChanged(IRoom& aRoom)
{
	ReceiverManager1Room* room = (ReceiverManager1Room*)(aRoom.UserData());
	ASSERT(room);
	room->SourceChanged();
}

void ReceiverManager1::RoomVolumeControlChanged(IRoom& /* aRoom */)
{
}

