#ifndef HEADER_TOPOLOGY4
#define HEADER_TOPOLOGY4

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>

#include <list>

#include "CpTopology3.h"

namespace OpenHome {
namespace Net {

class CpTopology4Room;

class ICpTopology4Handler
{
public:
    virtual void RoomAdded(CpTopology4Room& aRoom) = 0;
    virtual void RoomChanged(CpTopology4Room& aRoom) = 0;
    virtual void RoomRemoved(CpTopology4Room& aRoom) = 0;
    virtual void RoomStandbyChanged(CpTopology4Room& aRoom) = 0;
    virtual void RoomSourceChanged(CpTopology4Room& aRoom) = 0;
    virtual void RoomVolumeControlChanged(CpTopology4Room& aRoom) = 0;
	virtual void RoomVolumeChanged(CpTopology4Room& aRoom) = 0;
	virtual void RoomMuteChanged(CpTopology4Room& aRoom) = 0;
	virtual void RoomVolumeLimitChanged(CpTopology4Room& aRoom) = 0;
    ~ICpTopology4Handler() {}
};

class CpTopology4Room : private INonCopyable
{
public:
    enum EStandby {
        eOn,
        eMixed,
        eOff
    };

public:
    CpTopology4Room(CpTopology3Room& aRoom, ICpTopology4Handler& aHandler);
    ~CpTopology4Room();

    // functions which must be called from ICpTopology4Handler callback thread

    void AddRef();
    void RemoveRef();
    const Brx& Name() const;
    TUint SourceCount() const;
    const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
    const Brx& SourceGroup(TUint aIndex) const;
    CpDevice& SourceDevice(TUint aIndex) const;
    const Brx& CurrentSourceName() const;
    const Brx& CurrentSourceType() const;
    const Brx& CurrentSourceGroup() const;
    CpDevice& CurrentSourceDevice() const;
    TBool HasVolumeControl() const;
	TUint Volume() const;
	TBool Mute() const;
	TUint VolumeLimit() const;
    EStandby Standby() const;
    void SetUserData(void* aValue);
    void* UserData() const;

    // functions which must NOT be called from ICpTopology4Handler callback thread

    void SetStandby(TBool aValue);
    void SetSourceIndex(TUint aIndex);

	void SetVolume(TUint aValue);
	void VolumeInc();
	void VolumeDec();
	void SetMute(TBool aValue);

    void RoomAdded();
    void RoomChanged();
    void RoomRemoved();
    void RoomStandbyChanged();
    void RoomSourceChanged();
    void RoomVolumeControlChanged();
	void RoomVolumeChanged();
	void RoomMuteChanged();
	void RoomVolumeLimitChanged();

	void EventInitialEvent();
	void EventVolumeChanged();
	void EventMuteChanged();
	void EventVolumeLimitChanged();

	void CallbackSetVolume(IAsync& aAsync);
	void CallbackVolumeInc(IAsync& aAsync);
	void CallbackVolumeDec(IAsync& aAsync);
    void CallbackSetMute(IAsync& aAsync);

private:
	CpTopology3Room& iRoom;
	ICpTopology4Handler& iHandler;

	TBool iHasVolumeControl;
    CpProxyAvOpenhomeOrgVolume1* iServiceVolume;
    
	FunctorAsync iFunctorSetVolume;
	FunctorAsync iFunctorVolumeInc;
	FunctorAsync iFunctorVolumeDec;
    FunctorAsync iFunctorSetMute;

	TUint iVolume;
	TBool iMute;
	TUint iVolumeLimit;

	TUint iRefCount;
	void* iUserData;
};


typedef void (ICpTopology4Handler::*ICpTopology4HandlerFunction)(CpTopology4Room&);

class CpTopology4Job
{
public:
    CpTopology4Job(ICpTopology4Handler& aHandler);
    void Set(CpTopology4Room& aRoom, ICpTopology4HandlerFunction aFunction);
    virtual void Execute();
private:
    ICpTopology4Handler* iHandler;
    CpTopology4Room* iRoom;
    ICpTopology4HandlerFunction iFunction;
};


class CpTopology4 : public ICpTopology3Handler, public ICpTopology4Handler, private INonCopyable
{
    static const TUint kMaxJobCount = 20;
    
public:
    CpTopology4(ICpTopology4Handler& aHandler);
    
    void Refresh();
    
    ~CpTopology4();
    
private:
    // ICpTopology3Handler
    virtual void RoomAdded(CpTopology3Room& aRoom);
    virtual void RoomChanged(CpTopology3Room& aRoom);
    virtual void RoomRemoved(CpTopology3Room& aRoom);
    virtual void RoomStandbyChanged(CpTopology3Room& aRoom);
    virtual void RoomSourceChanged(CpTopology3Room& aRoom);
    virtual void RoomVolumeControlChanged(CpTopology3Room& aRoom);

	// ICpTopology4Handler
	virtual void RoomAdded(CpTopology4Room& aRoom);
    virtual void RoomChanged(CpTopology4Room& aRoom);
    virtual void RoomRemoved(CpTopology4Room& aRoom);
    virtual void RoomStandbyChanged(CpTopology4Room& aRoom);
    virtual void RoomSourceChanged(CpTopology4Room& aRoom);
    virtual void RoomVolumeControlChanged(CpTopology4Room& aRoom);
	virtual void RoomVolumeChanged(CpTopology4Room& aRoom);
	virtual void RoomMuteChanged(CpTopology4Room& aRoom);
	virtual void RoomVolumeLimitChanged(CpTopology4Room& aRoom);

    void Run();
    
private:
    std::list<CpTopology4Room*> iRoomList;
	CpTopology3* iTopology3;
    Fifo<CpTopology4Job*> iFree;
    Fifo<CpTopology4Job*> iReady;
    ThreadFunctor* iThread;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TOPOLOGY4