#include "ReceiverManager.h"

#include <Ascii.h>
#include <Maths.h>
#include <Arch.h>
#include <Debug.h>

using namespace Zapp;

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
	TUint count = aRoom.SourceCount();

	for (TUint i = 0; i < count; i++) {
		if (aRoom.SourceType(i) == Brn("Receiver")) {
			iRoomList.push_back(&aRoom);
			UpdateList();
			break;
		}
	}
}

void ReceiverManager::RoomChanged(IRoom& aRoom)
{
	TUint count = aRoom.SourceCount();

	for (TUint i = 0; i < count; i++) {
		if (aRoom.SourceType(i) == Brn("Receiver")) {
			UpdateList();
			break;
		}
	}
}

void ReceiverManager::RoomRemoved(IRoom& aRoom)
{
	TUint count = aRoom.SourceCount();

	for (TUint i = 0; i < count; i++) {
		if (aRoom.SourceType(i) == Brn("Receiver")) {
			std::vector<IRoom*>::iterator it = iRoomList.begin();
			TBool found = false;
			while (it != iRoomList.end()) {
				if (*it == &aRoom) {
					iRoomList.erase(it);
					found = true;
					break;
				}
			it++;
			}
			ASSERT(found);
			UpdateList();
			break;
		}
	}
}

void ReceiverManager::RoomStandbyChanged(IRoom& /* aRoom */)
{
	UpdateStatus();
}

void ReceiverManager::RoomSourceIndexChanged(IRoom& /* aRoom */)
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
	std::vector<IRoom*>::iterator it = iRoomList.begin();
	while (it != iRoomList.end()) {
		IRoom* room = *it;

		printf("about to get source count\n");

		TUint count = room->SourceCount();

		printf("count: %d\n", count);

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

			if (index == 1) {
				const Brx& name = room->Name();
				if (remaining >= name.Bytes() + 1) {
					iNewList.Append(name);
					iNewList.Append('\n');
				}
			}
			else {
				const Brx& name1 = room->Name();
				for (TUint i = 0; i < index; i++) {
					TUint j = receivers[i];
					const Brx& name2 = room->SourceName(j);
					if (remaining >= name1.Bytes() + name2.Bytes() + 3) {
						iNewList.Append(name1);
						iNewList.Append('(');
						iNewList.Append(name2);
						iNewList.Append(')');
						iNewList.Append('\n');
					}
				}
			}
		}
	it++;
	}

	iMutex.Wait();

	TBool changed = false;

	if (iList != iNewList) {
		changed = true;
		iList.Replace(iNewList);
	}

	iMutex.Signal();

	if (changed) {
		iTimerListChanged.FireIn(kTimerListChangedTimeoutMs);
	}
}

void ReceiverManager::UpdateStatus()
{
}

void ReceiverManager::TimerListChangedExpired()
{
	iListChanged();
}
