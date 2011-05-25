#include <Core/CpTopology.h>

#include <Debug.h>
#include <Parser.h>
#include <Ascii.h>
#include <XmlParser.h>

#include "CpTopology3.h"

using namespace Zapp;

class CpTopologyRoom : public IRoom
{
public:
    CpTopologyRoom(CpTopology3Room& aRoom);
    virtual void AddRef();
    virtual void RemoveRef();
    virtual TBool Standby() const;
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
    virtual TUint VolumeMax() const;
    virtual TUint VolumeUnity() const;
    virtual TUint VolumeSteps() const;
    virtual TUint VolumeMilliDbPerStep() const;
    virtual TUint FadeMax() const;
    virtual TUint BalanceMax() const;
    virtual TUint VolumeLimit() const;
    virtual TUint Volume() const;
    virtual void SetVolume(TUint aValue);
    virtual void VolumeInc();
    virtual void VolumeDec();
    virtual TInt Balance() const;
    virtual void SetBalance(TInt aValue);
    virtual void BalanceInc();
    virtual void BalanceDec();
    virtual TInt Fade() const;
    virtual void SetFade(TInt aValue);
    virtual void FadeInc();
    virtual void FadeDec();
    virtual TBool Mute() const;
    virtual void SetMute(TBool aValue);
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


TBool CpTopologyRoom::Standby() const
{
    return (iRoom.Standby());
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

TUint CpTopologyRoom::VolumeMax() const
{
    return (iRoom.VolumeMax());
}

TUint CpTopologyRoom::VolumeUnity() const
{
    return (iRoom.VolumeUnity());
}

TUint CpTopologyRoom::VolumeSteps() const
{
    return (iRoom.VolumeSteps());
}

TUint CpTopologyRoom::VolumeMilliDbPerStep() const
{
    return (iRoom.VolumeMilliDbPerStep());
}

TUint CpTopologyRoom::FadeMax() const
{
    return (iRoom.FadeMax());
}

TUint CpTopologyRoom::BalanceMax() const
{
    return (iRoom.BalanceMax());
}

TUint CpTopologyRoom::VolumeLimit() const
{
    return (iRoom.VolumeLimit());
}

TUint CpTopologyRoom::Volume() const
{
    return (iRoom.Volume());
}


void CpTopologyRoom::SetVolume(TUint aValue)
{
    iRoom.SetVolume(aValue);
}


void CpTopologyRoom::VolumeInc()
{
    iRoom.VolumeInc();
}


void CpTopologyRoom::VolumeDec()
{
    iRoom.VolumeDec();
}


TInt CpTopologyRoom::Balance() const
{
    return (iRoom.Balance());
}


void CpTopologyRoom::SetBalance(TInt aValue)
{
    iRoom.SetBalance(aValue);
}


void CpTopologyRoom::BalanceInc()
{
    iRoom.BalanceInc();
}


void CpTopologyRoom::BalanceDec()
{
    iRoom.BalanceDec();
}


TInt CpTopologyRoom::Fade() const
{
    return (iRoom.Fade());
}


void CpTopologyRoom::SetFade(TInt aValue)
{
    iRoom.SetFade(aValue);
}


void CpTopologyRoom::FadeInc()
{
    iRoom.FadeInc();
}


void CpTopologyRoom::FadeDec()
{
    iRoom.FadeDec();
}


TBool CpTopologyRoom::Mute() const
{
    return (iRoom.Mute());
}


void CpTopologyRoom::SetMute(TBool aValue)
{
    iRoom.SetMute(aValue);
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
    virtual void RoomVolumeLimitChanged(CpTopology3Room& aRoom);
    virtual void RoomVolumeChanged(CpTopology3Room& aRoom);
    virtual void RoomBalanceChanged(CpTopology3Room& aRoom);
    virtual void RoomFadeChanged(CpTopology3Room& aRoom);
    virtual void RoomMuteChanged(CpTopology3Room& aRoom);

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

void CpTopology::RoomVolumeLimitChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomVolumeLimitChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomVolumeChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomVolumeChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomBalanceChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomBalanceChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomFadeChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomFadeChanged(*(CpTopologyRoom*)aRoom.UserData());
}

void CpTopology::RoomMuteChanged(CpTopology3Room& aRoom)
{
    iHandler.RoomMuteChanged(*(CpTopologyRoom*)aRoom.UserData());
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

