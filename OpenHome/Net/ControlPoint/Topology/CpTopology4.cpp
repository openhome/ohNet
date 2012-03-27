#include "CpTopology4.h"

#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpTopology4Room

CpTopology4Room::CpTopology4Room(CpTopology3Room& aRoom, ICpTopology4Handler& aHandler)
	: iRoom(aRoom)
    , iHandler(aHandler)
	, iHasVolumeControl(false)
	, iServiceVolume(0)
	, iRefCount(1)
	, iUserData(0)
{
	iRoom.AddRef();

	iFunctorSetVolume = MakeFunctorAsync(*this, &CpTopology4Room::CallbackSetVolume);
    iFunctorVolumeInc = MakeFunctorAsync(*this, &CpTopology4Room::CallbackVolumeInc);
	iFunctorVolumeDec = MakeFunctorAsync(*this, &CpTopology4Room::CallbackVolumeDec);
	iFunctorSetMute = MakeFunctorAsync(*this, &CpTopology4Room::CallbackSetMute);

	RoomVolumeControlChanged();
}

CpTopology4Room::~CpTopology4Room()
{
	iRoom.RemoveRef();

	if(iServiceVolume)
	{
		delete (iServiceVolume);
	}
}

void CpTopology4Room::AddRef()
{
	iRefCount++;
}

void CpTopology4Room::RemoveRef()
{
	if (--iRefCount == 0) {
        delete this;
    }
}

const Brx& CpTopology4Room::Name() const
{
	return iRoom.Name();
}

TUint CpTopology4Room::SourceCount() const
{
	return iRoom.SourceCount();
}

const Brx& CpTopology4Room::SourceName(TUint aIndex) const
{
	return iRoom.SourceName(aIndex);
}

const Brx& CpTopology4Room::SourceType(TUint aIndex) const
{
	return iRoom.SourceType(aIndex);
}

const Brx& CpTopology4Room::SourceGroup(TUint aIndex) const
{
	return iRoom.SourceGroup(aIndex);
}

CpDevice& CpTopology4Room::SourceDevice(TUint aIndex) const
{
	return iRoom.SourceDevice(aIndex);
}

const Brx& CpTopology4Room::CurrentSourceName() const
{
	return iRoom.CurrentSourceName();
}

const Brx& CpTopology4Room::CurrentSourceType() const
{
	return iRoom.CurrentSourceType();
}

const Brx& CpTopology4Room::CurrentSourceGroup() const
{
	return iRoom.CurrentSourceGroup();
}

CpDevice& CpTopology4Room::CurrentSourceDevice() const
{
	return iRoom.CurrentSourceDevice();
}

TBool CpTopology4Room::HasVolumeControl() const
{
	return iHasVolumeControl;
}

void CpTopology4Room::SetVolume(TUint aValue)
{
	if(iServiceVolume)
	{
		iServiceVolume->BeginSetVolume(aValue, iFunctorSetVolume);
	}
}

void CpTopology4Room::VolumeInc()
{
	if(iServiceVolume)
	{
		iServiceVolume->BeginVolumeInc(iFunctorVolumeInc);
	}
}

void CpTopology4Room::VolumeDec()
{
	if(iServiceVolume)
	{
		iServiceVolume->BeginVolumeDec(iFunctorVolumeDec);
	}
}

void CpTopology4Room::SetMute(TBool aValue)
{
	if(iServiceVolume)
	{
		iServiceVolume->BeginSetMute(aValue, iFunctorSetMute);
	}
}

CpTopology4Room::EStandby CpTopology4Room::Standby() const
{
	return ((CpTopology4Room::EStandby)iRoom.Standby());
}

TUint CpTopology4Room::Volume() const
{
	return iVolume;
}

TBool CpTopology4Room::Mute() const
{
	return iMute;
}

TUint CpTopology4Room::VolumeLimit() const
{
	return iVolumeLimit;
}

void CpTopology4Room::SetUserData(void* aValue)
{
	iUserData = aValue;
}

void* CpTopology4Room::UserData() const
{
	return iUserData;
}

void CpTopology4Room::SetStandby(TBool aValue)
{
	iRoom.SetStandby(aValue);
}

void CpTopology4Room::SetSourceIndex(TUint aIndex)
{
	iRoom.SetSourceIndex(aIndex);
}

void CpTopology4Room::RoomAdded()
{
	iHandler.RoomChanged(*this);
}

void CpTopology4Room::RoomChanged()
{
	iHandler.RoomChanged(*this);
}

void CpTopology4Room::RoomRemoved()
{
	iHandler.RoomRemoved(*this);
	RemoveRef();
}

void CpTopology4Room::RoomStandbyChanged()
{
	iHandler.RoomStandbyChanged(*this);
}

void CpTopology4Room::RoomSourceChanged()
{
	iHandler.RoomSourceChanged(*this);
}

void CpTopology4Room::RoomVolumeControlChanged()
{
	if(iServiceVolume)
	{
		iServiceVolume->Unsubscribe();
	}

	iHasVolumeControl = false;

	iHandler.RoomVolumeControlChanged(*this);

	if(iRoom.HasVolumeControl())
	{
		iServiceVolume = new CpProxyAvOpenhomeOrgVolume1(iRoom.VolumeDevice());

		Functor functorInitial = MakeFunctor(*this, &CpTopology4Room::EventInitialEvent);

		iServiceVolume->SetPropertyInitialEvent(functorInitial);

		iServiceVolume->Subscribe();
	}
}

void CpTopology4Room::RoomVolumeChanged()
{
	iHandler.RoomVolumeChanged(*this);
}

void CpTopology4Room::RoomMuteChanged()
{
	iHandler.RoomMuteChanged(*this);
}

void CpTopology4Room::RoomVolumeLimitChanged()
{
	iHandler.RoomVolumeLimitChanged(*this);
}

void CpTopology4Room::EventInitialEvent()
{
	iHasVolumeControl = true;

	Functor functorVolume = MakeFunctor(*this, &CpTopology4Room::EventVolumeChanged);
	Functor functorMute = MakeFunctor(*this, &CpTopology4Room::EventMuteChanged);
	Functor functorVolumeLimit = MakeFunctor(*this, &CpTopology4Room::EventVolumeLimitChanged);

	iServiceVolume->SetPropertyVolumeChanged(functorVolume);
	iServiceVolume->SetPropertyMuteChanged(functorMute);
	iServiceVolume->SetPropertyVolumeLimitChanged(functorVolumeLimit);

	iServiceVolume->PropertyVolume(iVolume);
	iServiceVolume->PropertyMute(iMute);
	iServiceVolume->PropertyVolumeLimit(iVolumeLimit);

	iHandler.RoomVolumeControlChanged(*this);
}

void CpTopology4Room::EventVolumeChanged()
{
	LOG(kTopology, "CpTopology4Room::EventVolumeChanged ");
    LOG(kTopology, Name());
    LOG(kTopology, "\n");

    iServiceVolume->PropertyVolume(iVolume);

    iHandler.RoomVolumeChanged(*this);
}

void CpTopology4Room::EventMuteChanged()
{
	LOG(kTopology, "CpTopology4Room::EventMuteChanged ");
    LOG(kTopology, Name());
    LOG(kTopology, "\n");

    iServiceVolume->PropertyMute(iMute);

    iHandler.RoomMuteChanged(*this);
}

void CpTopology4Room::EventVolumeLimitChanged()
{
	LOG(kTopology, "CpTopology4Room::EventVolumeLimitChanged ");
    LOG(kTopology, Name());
    LOG(kTopology, "\n");

    iServiceVolume->PropertyVolumeLimit(iVolumeLimit);

    iHandler.RoomVolumeLimitChanged(*this);
}

void CpTopology4Room::CallbackSetVolume(IAsync& /*aAsync*/)
{
}

void CpTopology4Room::CallbackVolumeInc(IAsync& /*aAsync*/)
{
}

void CpTopology4Room::CallbackVolumeDec(IAsync& /*aAsync*/)
{
}

void CpTopology4Room::CallbackSetMute(IAsync& /*aAsync*/)
{
}

// CpTopology4Job

CpTopology4Job::CpTopology4Job(ICpTopology4Handler& aHandler)
{
    iHandler = &aHandler;
    iRoom = 0;
}
    
void CpTopology4Job::Set(CpTopology4Room& aRoom, ICpTopology4HandlerFunction aFunction)
{
    iRoom = &aRoom;
    iFunction = aFunction;
    iRoom->AddRef();
}

void CpTopology4Job::Execute()
{
    if (iRoom) {
        (iHandler->*iFunction)(*iRoom);
        iRoom->RemoveRef();
        iRoom = 0;
    }
    else {
        THROW(ThreadKill);
    }
}

// CpTopology4

CpTopology4::CpTopology4(ICpTopology4Handler& aHandler)
	: iFree(kMaxJobCount)
    , iReady(kMaxJobCount)
{
	for (TUint i = 0; i < kMaxJobCount; i++) {
        iFree.Write(new CpTopology4Job(aHandler));
    }

    iTopology3 = new CpTopology3(*this);

	iThread = new ThreadFunctor("TOP4", MakeFunctor(*this, &CpTopology4::Run));
    iThread->Start();
}

CpTopology4::~CpTopology4()
{
    LOG(kTopology, "CpTopology4::~CpTopology4\n");
    delete (iTopology3);
    LOG(kTopology, "CpTopology4::~CpTopology4 deleted layer 3\n");
    ASSERT(iRoomList.size() == 0);

	iReady.Write(iFree.Read()); // this null job causes the thread to complete

	delete (iThread);
    
    LOG(kTopology, "CpTopology4::~CpTopology4 deleted thread\n");

    for (TUint i = 0; i < kMaxJobCount; i++) {
        delete (iFree.Read());
    }

    LOG(kTopology, "CpTopology4::~CpTopology4 deleted jobs\n");
}
    
void CpTopology4::Refresh()
{
    ASSERT(iTopology3);
    iTopology3->Refresh();
}

// ICpTopology3Handler

void CpTopology4::RoomAdded(CpTopology3Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomAdded\n");

	CpTopology4Room* room = new CpTopology4Room(aRoom, *this);
	aRoom.SetUserData(room);
	room->RoomAdded();
}

void CpTopology4::RoomChanged(CpTopology3Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomChanged\n");
    ((CpTopology4Room*)aRoom.UserData())->RoomChanged();
}

void CpTopology4::RoomRemoved(CpTopology3Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomRemoved\n");
    ((CpTopology4Room*)aRoom.UserData())->RoomRemoved();
}

void CpTopology4::RoomStandbyChanged(CpTopology3Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomStandbyChanged\n");
    ((CpTopology4Room*)aRoom.UserData())->RoomStandbyChanged();
}

void CpTopology4::RoomSourceChanged(CpTopology3Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomSourceChanged\n");
    ((CpTopology4Room*)aRoom.UserData())->RoomSourceChanged();
}

void CpTopology4::RoomVolumeControlChanged(CpTopology3Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomVolumeControlChanged\n");
    ((CpTopology4Room*)aRoom.UserData())->RoomVolumeControlChanged();
}

// ICpTopology4Handler

void CpTopology4::RoomAdded(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomAdded ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomAdded);
    iReady.Write(job);
}

void CpTopology4::RoomChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomChanged);
    iReady.Write(job);
}

void CpTopology4::RoomRemoved(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomRemoved ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomRemoved);
    iReady.Write(job);
}

void CpTopology4::RoomStandbyChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomStandbyChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomStandbyChanged);
    iReady.Write(job);
}

void CpTopology4::RoomSourceChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomSourceChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomSourceChanged);
    iReady.Write(job);
}

void CpTopology4::RoomVolumeControlChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomVolumeControlChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomVolumeControlChanged);
    iReady.Write(job);
}

void CpTopology4::RoomVolumeChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomVolumeChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomVolumeChanged);
    iReady.Write(job);
}

void CpTopology4::RoomMuteChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomMuteChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomMuteChanged);
    iReady.Write(job);
}

void CpTopology4::RoomVolumeLimitChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomVolumeLimitChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    CpTopology4Job* job = iFree.Read();
    job->Set(aRoom, &ICpTopology4Handler::RoomVolumeLimitChanged);
    iReady.Write(job);
}

void CpTopology4::Run()
{
	LOG(kTopology, "CpTopology4::Run Started\n");

    for (;;)
    {
        CpTopology4Job* job = iReady.Read();
        
        try {
            job->Execute();
            iFree.Write(job);
        }
        catch (ThreadKill)
        {
            iFree.Write(job);
            break;
        }
    }

	LOG(kTopology, "CpTopology4::Run Exiting\n");
}
