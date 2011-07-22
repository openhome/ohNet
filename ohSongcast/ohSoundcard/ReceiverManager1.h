#ifndef HEADER_RECEIVER_MANAGER1
#define HEADER_RECEIVER_MANAGER1

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpTopology.h>

namespace OpenHome {
namespace Net {

class ReceiverManager1Receiver;

class IReceiverManager1Handler
{
public:
	virtual void ReceiverAdded(ReceiverManager1Receiver& aReceiver) = 0;
	virtual void ReceiverChanged(ReceiverManager1Receiver& aReceiver) = 0;
	virtual void ReceiverRemoved(ReceiverManager1Receiver& aReceiver) = 0;
	~IReceiverManager1Handler() {}
};

class ReceiverManager1Room;

class ReceiverManager1Receiver  : private INonCopyable
{
	friend class ReceiverManager1Room;

	static const TUint kMaxNameBytes = 20;
	static const TUint kMaxGroupBytes = 20;

public:
	ReceiverManager1Receiver(ReceiverManager1Room& aRoom, const Brx& aGroup, const Brx& aName, TUint aSourceIndex, CpDevice& aDevice);
	const Brx& Room() const;
	const Brx& Group() const;
	const Brx& Name() const;
	TUint SourceIndex() const;
	CpDevice& Device() const;

	void SetSourceIndex(TUint aValue);

	void Select();
	TBool Selected() const;

    void AddRef();
    void RemoveRef();
    void SetUserData(void* aValue);
	void* UserData() const;

	void Standby();

	~ReceiverManager1Receiver();

private:
	ReceiverManager1Room& iRoom;
	Bws<kMaxGroupBytes> iGroup;
	Bws<kMaxNameBytes> iName;
	TUint iSourceIndex;
	CpDevice& iDevice;
	void* iUserData;
    TUint iRefCount;
};

class ReceiverManager1;

class ReceiverManager1Room  : private INonCopyable
{
public:
	ReceiverManager1Room(IReceiverManager1Handler& aHandler, IRoom& aRoom);
	const Brx& Name() const;	
	IRoom& Room() const;
    void AddRef();
    void RemoveRef();
	void SourceChanged();
	void Changed();
	void Removed();
	void Standby();
	void Select(const ReceiverManager1Receiver& aReceiver);
	TBool Selected(const ReceiverManager1Receiver& aReceiver);
	~ReceiverManager1Room();
private:
	IReceiverManager1Handler& iHandler;
	IRoom& iRoom;
	ReceiverManager1Receiver* iSelected;
	std::vector<ReceiverManager1Receiver*> iReceiverList;
	TUint iRefCount;
};

class ReceiverManager1 : public IHouseHandler
{
public:
	static const TUint kMaxRoomBytes = 20;
	static const TUint kMaxGroupBytes = 20;

public:
	ReceiverManager1(IReceiverManager1Handler& aHandler);
    void Refresh();
    ~ReceiverManager1();

private:
	// IHouseHandler
    virtual void RoomAdded(IRoom& aRoom);
    virtual void RoomChanged(IRoom& aRoom);
    virtual void RoomRemoved(IRoom& aRoom);
    virtual void RoomStandbyChanged(IRoom& aRoom);
    virtual void RoomSourceChanged(IRoom& aRoom);
    virtual void RoomVolumeControlChanged(IRoom& aRoom);

private:
	IReceiverManager1Handler& iHandler;
    House* iHouse;
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

