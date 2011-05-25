#ifndef HEADER_RECEIVERS
#define HEADER_RECEIVERS

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Timer.h>
#include <Exception.h>
#include <Functor.h>
#include <Core/CpTopology.h>

namespace OpenHome {
namespace Net {

class ReceiverManager : public IHouseHandler
{
	static const TUint kMaxReceiversPerRoom = 100;
	static const TUint kTimerListChangedTimeoutMs = 200;

public:
	static const TUint kMaxListBytes = 5000;
	static const TUint kMaxNameBytes = 50;

	enum EStatus {
		eOff,
		eOn,
		eListening
	};

public:
	ReceiverManager(Functor aStatusChanged, Functor aListChanged, const Brx& aReceiverName);
	EStatus Status() const;
	void List(Bwx& aReceiverList) const;
	void Select(Bwx& aReceiverName);
    void Refresh();
    ~ReceiverManager();

private:
	// IHouseHandler
    virtual void RoomAdded(IRoom& aRoom);
    virtual void RoomChanged(IRoom& aRoom);
    virtual void RoomRemoved(IRoom& aRoom);
    virtual void RoomStandbyChanged(IRoom& aRoom);
    virtual void RoomSourceChanged(IRoom& aRoom);
    virtual void RoomVolumeLimitChanged(IRoom& aRoom);
    virtual void RoomVolumeChanged(IRoom& aRoom);
    virtual void RoomBalanceChanged(IRoom& aRoom);
    virtual void RoomFadeChanged(IRoom& aRoom);
    virtual void RoomMuteChanged(IRoom& aRoom);

	void UpdateList();
	void UpdateStatus();
	void TimerListChangedExpired();

private:
    Functor iStatusChanged;
    Functor iListChanged;
	Bws<kMaxNameBytes> iReceiverName;
	Timer iTimerListChanged;
	mutable Mutex iMutex;
	EStatus iStatus;
	std::vector<IRoom*> iRoomList;
	Bws<kMaxListBytes> iList;
	Bws<kMaxListBytes> iNewList;
    House* iHouse;
	IRoom* iCurrentRoom;
	TUint iCurrentSource;
};



} // namespace Net
} // namespace OpenHome

#endif // HEADER_SOUNDCARD

