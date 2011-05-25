#include "ReceiverManager.h"

#include <Ascii.h>
#include <Maths.h>
#include <Arch.h>
#include <Debug.h>

using namespace OpenHome::Net;

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

// ReceiverManager

ReceiverManager::ReceiverManager(Functor aStatusChanged, Functor aListChanged, const Brx& aReceiverName)
	: iStatusChanged(aStatusChanged)
	, iListChanged(aListChanged)
	, iReceiverName(aReceiverName)
	, iTimerListChanged(MakeFunctor(*this, &ReceiverManager::TimerListChangedExpired))
	, iMutex("SCRM")
	, iStatus(eOff)
	, iCurrentRoom(0)
{
	iHouse = new House(*this);
}

ReceiverManager::EStatus ReceiverManager::Status() const
{
	iMutex.Wait();
	EStatus status = iStatus;
	iMutex.Signal();
	return (status);
}

void ReceiverManager::List(Bwx& aReceiverList) const
{
	iMutex.Wait();
	aReceiverList.Replace(iList);
	iMutex.Signal();
}

void ReceiverManager::Select(Bwx& aReceiverName)
{
	iReceiverName.Replace(aReceiverName);
}

void ReceiverManager::Refresh()
{
	iHouse->Refresh();
}

ReceiverManager::~ReceiverManager()
{
	delete (iHouse);
	iTimerListChanged.Cancel();
}

void ReceiverManager::RoomAdded(IRoom& aRoom)
{
	iRoomList.push_back(&aRoom);
	UpdateList();
}

void ReceiverManager::RoomChanged(IRoom& /* aRoom */)
{
	UpdateList();
}

void ReceiverManager::RoomRemoved(IRoom& aRoom)
{
	std::vector<IRoom*>::iterator it = iRoomList.begin();

	while (it != iRoomList.end()) {
		if (*it == &aRoom) {
			iRoomList.erase(it);
			UpdateList();
			return;
		}
	it++;
	}

	ASSERTS();
}

void ReceiverManager::RoomStandbyChanged(IRoom& /* aRoom */)
{
	UpdateStatus();
}

void ReceiverManager::RoomSourceChanged(IRoom& /* aRoom */)
{
	UpdateStatus();
}

void ReceiverManager::RoomVolumeLimitChanged(IRoom& /* aRoom */)
{
}

void ReceiverManager::RoomVolumeChanged(IRoom& /* aRoom */)
{
}

void ReceiverManager::RoomBalanceChanged(IRoom& /* aRoom */)
{
}

void ReceiverManager::RoomFadeChanged(IRoom& /* aRoom */)
{
}

void ReceiverManager::RoomMuteChanged(IRoom& /* aRoom */)
{
	UpdateStatus();
}

void ReceiverManager::UpdateList()
{
	iNewList.SetBytes(0);

	IRoom* currentRoom = NULL;
	TUint currentSource;

	std::vector<IRoom*>::iterator it = iRoomList.begin();

	while (it != iRoomList.end()) {
		IRoom* room = *it;

		TUint count = room->SourceCount();

		TUint index = 0;

		TUint receivers[kMaxReceiversPerRoom];

		for (TUint i = 0; i < count; i++) {
			if (room->SourceType(i) == Brn("Receiver")) {
				if (index < kMaxReceiversPerRoom) {
					receivers[index++] = i;
				}
			}
		}

		if (index > 0) {
			TUint remaining = iNewList.MaxBytes() - iNewList.Bytes();

			Bws<kMaxNameBytes> name;

			const Brx& r = room->Name();

			for (TUint i = 0; i < index; i++) {
				TUint j = receivers[i];
				const Brx& g = room->SourceGroup(j);
				if (r.Bytes() + g.Bytes() + 3 <= kMaxNameBytes) {
					name.Replace(r);
					name.Append(' ');
					name.Append('(');
					name.Append(g);
					name.Append(')');

					if (remaining > name.Bytes()) {
						iNewList.Append(name);
						iNewList.Append('\n');

						if (name == iReceiverName) {
							currentRoom = room;
							currentSource = j;
						}
					}
				}
			}
		}
	it++;
	}

	TBool changed = false;

	iMutex.Wait();

	if (iList != iNewList) {
		changed = true;
		iList.Replace(iNewList);
		iCurrentRoom = currentRoom;
		iCurrentSource = currentSource;
	}

	iMutex.Signal();

	if (changed) {
		iTimerListChanged.FireIn(kTimerListChangedTimeoutMs);
		UpdateStatus();
	}
}

void ReceiverManager::UpdateStatus()
{
	printf("update\n");

	EStatus status = eOff;

	if (iCurrentRoom) {
		status = eOn;
	}

	TBool changed = false;

	iMutex.Wait();

	if (iStatus != status) {
		iStatus = status;
		changed = true;
	}

	iMutex.Signal();

	if (changed) {
		iStatusChanged();
	}
}

void ReceiverManager::TimerListChangedExpired()
{
	iListChanged();
}
