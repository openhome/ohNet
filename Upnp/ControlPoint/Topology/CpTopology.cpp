#include <Core/CpTopology.h>

#include <Debug.h>
#include <Parser.h>
#include <Ascii.h>
#include <XmlParser.h>

#include "CpTopology3.h"

using namespace OpenHome::Net;

class CpTopologyRoom : public IRoom
{
public:
    CpTopologyRoom(CpTopology3Room& aRoom);
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
	virtual CpDevice& VolumeDevice() const;
	virtual void SetUserData(void* aValue);
    virtual void* UserData() const;
    
private:
    CpTopology3Room& iRoom;
    void* iUserData;
};

CpTopologyRoom::CpTopologyRoom(CpTopology3Room& aRoom)
    : iRoom(aRoom)
{
}

void CpTopologyRoom::AddRef()
{
}


void CpTopologyRoom::RemoveRef()
{
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

CpDevice& CpTopologyRoom::VolumeDevice() const
{
    return (iRoom.VolumeDevice());
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

class CpTopology : public IHouse, ICpTopology3Handler
{
public:
    CpTopology(IHouseHandler& aHandler);
    ~CpTopology();
private:
    // IHouse
    virtual void Refresh();
    
    // ICpTopology3Handler
    virtual void RoomAdded(CpTopology3Room& aRoom);
    virtual void RoomChanged(CpTopology3Room& aRoom);
    virtual void RoomRemoved(CpTopology3Room& aRoom);
    virtual void RoomStandbyChanged(CpTopology3Room& aRoom);
    virtual void RoomSourceChanged(CpTopology3Room& aRoom);
    virtual void RoomVolumeControlChanged(CpTopology3Room& aRoom);

private:
    IHouseHandler& iHandler;
    CpTopology3* iTopology;
};

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

// CpTopology

CpTopology::CpTopology(IHouseHandler& aHandler)
    : iHandler(aHandler)
{
    iTopology = new CpTopology3(*this);
}

CpTopology::~CpTopology()
{
    delete iTopology;
}

void CpTopology::Refresh()
{
    iTopology->Refresh();
}
    
void CpTopology::RoomAdded(CpTopology3Room& aRoom)
{
    CpTopologyRoom* room = new CpTopologyRoom(aRoom);
    aRoom.SetUserData(room);
    iHandler.RoomAdded(*room);
}

void CpTopology::RoomChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomRemoved(CpTopology3Room& aRoom)
{
    iHandler.RoomRemoved(*(CpTopologyRoom*)aRoom.UserData());
    delete ((CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomStandbyChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomStandbyChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomSourceChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomSourceChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomVolumeControlChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomVolumeControlChanged(*(CpTopologyRoom*)aRoom.UserData());
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

