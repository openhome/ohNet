#include <OpenHome/Net/Core/CpTopology.h>

#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Net/Private/XmlParser.h>

#include "CpTopology4.h"

using namespace OpenHome;
using namespace OpenHome::Net;

class CpTopologyRoom : public IRoom
{
public:
    CpTopologyRoom(CpTopology4Room& aRoom);
    virtual void AddRef();
    virtual void RemoveRef();
    virtual IRoom::EStandby Standby() const;
    virtual void SetStandby(TBool aValue);
    virtual const Brx& Name() const;
    virtual TUint SourceCount() const;
    virtual const Brx& SourceName(TUint aIndex) const;
    virtual const Brx& SourceType(TUint aIndex) const;
    virtual const Brx& SourceGroup(TUint aIndex) const;
    virtual CpDevice& SourceDevice(TUint aIndex) const;
    virtual const Brx& CurrentSourceName() const;
    virtual const Brx& CurrentSourceType() const;
    virtual const Brx& CurrentSourceGroup() const;
    virtual CpDevice& CurrentSourceDevice() const;
    virtual void SetSourceIndex(TUint aIndex);
    virtual TBool HasVolumeControl() const;
    virtual TUint Volume() const;
	virtual void SetVolume(TUint aValue);
	virtual void VolumeInc();
	virtual void VolumeDec();
	virtual TBool Mute() const;
	virtual void SetMute(TBool aValue);
	virtual TUint VolumeLimit() const;
    virtual void SetUserData(void* aValue);
    virtual void* UserData() const;
    ~CpTopologyRoom();

private:
    CpTopology4Room& iRoom;
    TUint iRefCount;
    void* iUserData;
};

CpTopologyRoom::CpTopologyRoom(CpTopology4Room& aRoom)
    : iRoom(aRoom)
    , iRefCount(1)
    , iUserData(0)
{
    iRoom.AddRef();
}

void CpTopologyRoom::AddRef()
{
    iRefCount++;
}

void CpTopologyRoom::RemoveRef()
{
    if (--iRefCount == 0) {
        delete (this);
    }
}


CpTopologyRoom::~CpTopologyRoom()
{
    iRoom.RemoveRef();
}

IRoom::EStandby CpTopologyRoom::Standby() const
{
    return ((IRoom::EStandby)iRoom.Standby());
}


void CpTopologyRoom::SetStandby(TBool aValue)
{
    iRoom.SetStandby(aValue);
}


const Brx& CpTopologyRoom::Name() const
{
    return (iRoom.Name());
}


TUint CpTopologyRoom::SourceCount() const
{
    return (iRoom.SourceCount());
}


const Brx& CpTopologyRoom::SourceName(TUint aIndex) const
{
    return (iRoom.SourceName(aIndex));
}


const Brx& CpTopologyRoom::SourceType(TUint aIndex) const
{
    return (iRoom.SourceType(aIndex));
}


const Brx& CpTopologyRoom::SourceGroup(TUint aIndex) const
{
    return (iRoom.SourceGroup(aIndex));
}

CpDevice& CpTopologyRoom::SourceDevice(TUint aIndex) const
{
    return (iRoom.SourceDevice(aIndex));
}


const Brx& CpTopologyRoom::CurrentSourceName() const
{
    return (iRoom.CurrentSourceName());
}

const Brx& CpTopologyRoom::CurrentSourceType() const
{
    return (iRoom.CurrentSourceType());
}

const Brx& CpTopologyRoom::CurrentSourceGroup() const
{
    return (iRoom.CurrentSourceGroup());
}

CpDevice& CpTopologyRoom::CurrentSourceDevice() const
{
    return (iRoom.CurrentSourceDevice());
}

void CpTopologyRoom::SetSourceIndex(TUint aIndex)
{
    iRoom.SetSourceIndex(aIndex);
}

TBool CpTopologyRoom::HasVolumeControl() const
{
    return (iRoom.HasVolumeControl());
}

TUint CpTopologyRoom::Volume() const
{
	return iRoom.Volume();
}

void CpTopologyRoom::SetVolume(TUint aValue)
{
	iRoom.SetVolume(aValue);
}

void  CpTopologyRoom::VolumeInc()
{
	iRoom.VolumeInc();
}

void CpTopologyRoom::VolumeDec()
{
	iRoom.VolumeDec();
}

TBool CpTopologyRoom::Mute() const
{
	return iRoom.Mute();
}

void CpTopologyRoom::SetMute(TBool aValue)
{
	iRoom.SetMute(aValue);
}

TUint CpTopologyRoom::VolumeLimit() const
{
	return iRoom.VolumeLimit();
}

void CpTopologyRoom::SetUserData(void* aValue)
{
    iUserData = aValue;
}


void* CpTopologyRoom::UserData() const
{
    return (iUserData);
}

// CpTopology

class CpTopology : public IHouse, ICpTopology4Handler
{
public:
    CpTopology(IHouseHandler& aHandler);
    ~CpTopology();
private:
    // IHouse
    virtual void Refresh();
    
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

private:
    IHouseHandler& iHandler;
    CpTopology4* iTopology;
};

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

// CpTopology

CpTopology::CpTopology(IHouseHandler& aHandler)
    : iHandler(aHandler)
{
    LOG(kTopology, "CpTopology::CpTopology\n");
    iTopology = new CpTopology4(*this);
    LOG(kTopology, "CpTopology::CpTopology created layer 4\n");
}

CpTopology::~CpTopology()
{
    delete iTopology;

    LOG(kTopology, "CpTopology::~CpTopology deleted layer 4\n");
}

void CpTopology::Refresh()
{
    iTopology->Refresh();
}
    
void CpTopology::RoomAdded(CpTopology4Room& aRoom)
{
    CpTopologyRoom* room = new CpTopologyRoom(aRoom);
    aRoom.SetUserData(room);
    iHandler.RoomAdded(*room);
}

void CpTopology::RoomChanged(CpTopology4Room& aRoom)
{
    iHandler.RoomChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomRemoved(CpTopology4Room& aRoom)
{
    CpTopologyRoom* room = (CpTopologyRoom*)aRoom.UserData();
    iHandler.RoomRemoved(*room);
    room->RemoveRef();
}

void CpTopology::RoomStandbyChanged(CpTopology4Room& aRoom)
{
    iHandler.RoomStandbyChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomSourceChanged(CpTopology4Room& aRoom)
{
    iHandler.RoomSourceChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomVolumeControlChanged(CpTopology4Room& aRoom)
{
    iHandler.RoomVolumeControlChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomVolumeChanged(CpTopology4Room& aRoom)
{
    iHandler.RoomVolumeChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomMuteChanged(CpTopology4Room& aRoom)
{
    iHandler.RoomMuteChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomVolumeLimitChanged(CpTopology4Room& aRoom)
{
    iHandler.RoomVolumeLimitChanged(*(CpTopologyRoom*)aRoom.UserData());
}

// House

House::House(IHouseHandler& aHandler)
{
    iHouse = new CpTopology(aHandler);
}

void House::Refresh()
{
    iHouse->Refresh();
}

House::~House()
{
    delete (iHouse);
}

