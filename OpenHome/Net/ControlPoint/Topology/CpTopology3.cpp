#include "CpTopology3.h"

#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpTopology3Room

CpTopology3Group::CpTopology3Group(CpTopology2Group& aGroup, ICpTopology3Handler& aHandler)
	: iGroup(aGroup)
    , iHandler(aHandler)
	, iHasVolumeControl(false)
	, iServiceVolume(0)
	, iVolume(0)
	, iMute(false)
	, iVolumeLimit(0)
	, iRefCount(1)
	, iUserData(0)
{
	iGroup.AddRef();

	iFunctorSetVolume = MakeFunctorAsync(*this, &CpTopology3Group::CallbackSetVolume);
    iFunctorVolumeInc = MakeFunctorAsync(*this, &CpTopology3Group::CallbackVolumeInc);
	iFunctorVolumeDec = MakeFunctorAsync(*this, &CpTopology3Group::CallbackVolumeDec);
	iFunctorSetMute = MakeFunctorAsync(*this, &CpTopology3Group::CallbackSetMute);

	if(iGroup.HasVolumeControl())
	{
		iServiceVolume = new CpProxyAvOpenhomeOrgVolume1(iGroup.Device());

		Functor functorInitial = MakeFunctor(*this, &CpTopology3Group::EventInitialEvent);

		iServiceVolume->SetPropertyInitialEvent(functorInitial);
	}
}

CpTopology3Group::~CpTopology3Group()
{
	iGroup.RemoveRef();

	if(iServiceVolume)
	{
		delete (iServiceVolume);
		iServiceVolume = 0;
	}
}

void CpTopology3Group::AddRef()
{
	iRefCount++;
}

void CpTopology3Group::RemoveRef()
{
	if (--iRefCount == 0) {
        delete this;
    }
}

CpDevice& CpTopology3Group::Device() const
{
	return iGroup.Device();
}

const Brx& CpTopology3Group::Room() const
{
	return iGroup.Room();
}

const Brx& CpTopology3Group::Name() const
{
	return iGroup.Name();
}

TUint CpTopology3Group::SourceIndex() const
{
	return iGroup.SourceIndex();
}

TUint CpTopology3Group::SourceCount() const
{
	return iGroup.SourceCount();
}

const Brx& CpTopology3Group::SourceName(TUint aIndex) const
{
	return iGroup.SourceName(aIndex);
}

const Brx& CpTopology3Group::SourceType(TUint aIndex) const
{
	return iGroup.SourceType(aIndex);
}

TBool CpTopology3Group::SourceVisible(TUint aIndex) const
{
	return iGroup.SourceVisible(aIndex);
}

TBool CpTopology3Group::HasVolumeControl() const
{
	return iHasVolumeControl;
}

void CpTopology3Group::SetVolume(TUint aValue)
{
	if(iServiceVolume)
	{
		iServiceVolume->BeginSetVolume(aValue, iFunctorSetVolume);
	}
}

void CpTopology3Group::VolumeInc()
{
	if(iServiceVolume)
	{
		iServiceVolume->BeginVolumeInc(iFunctorVolumeInc);
	}
}

void CpTopology3Group::VolumeDec()
{
	if(iServiceVolume)
	{
		iServiceVolume->BeginVolumeDec(iFunctorVolumeDec);
	}
}

void CpTopology3Group::SetMute(TBool aValue)
{
	if(iServiceVolume)
	{
		iServiceVolume->BeginSetMute(aValue, iFunctorSetMute);
	}
}

TBool CpTopology3Group::Standby() const
{
	return (iGroup.Standby());
}

TUint CpTopology3Group::Volume() const
{
	return iVolume;
}

TBool CpTopology3Group::Mute() const
{
	return iMute;
}

TUint CpTopology3Group::VolumeLimit() const
{
	return iVolumeLimit;
}

void CpTopology3Group::SetUserData(void* aValue)
{
	iUserData = aValue;
}

void* CpTopology3Group::UserData() const
{
	return iUserData;
}

void CpTopology3Group::SetStandby(TBool aValue)
{
	iGroup.SetStandby(aValue);
}

void CpTopology3Group::SetSourceIndex(TUint aIndex)
{
	iGroup.SetSourceIndex(aIndex);
}

void CpTopology3Group::GroupAdded()
{
	iHandler.GroupAdded(*this);

	if(iServiceVolume)
	{
		iServiceVolume->Subscribe();
	}
}

void CpTopology3Group::GroupStandbyChanged()
{
	iHandler.GroupStandbyChanged(*this);
}

void CpTopology3Group::GroupSourceIndexChanged()
{
	iHandler.GroupSourceIndexChanged(*this);
}

void CpTopology3Group::GroupSourceListChanged()
{
	iHandler.GroupSourceListChanged(*this);
}

void CpTopology3Group::GroupRemoved()
{
	iHandler.GroupRemoved(*this);
	RemoveRef();
}

void CpTopology3Group::EventInitialEvent()
{
	iHasVolumeControl = true;

	Functor functorVolume = MakeFunctor(*this, &CpTopology3Group::EventVolumeChanged);
	Functor functorMute = MakeFunctor(*this, &CpTopology3Group::EventMuteChanged);
	Functor functorVolumeLimit = MakeFunctor(*this, &CpTopology3Group::EventVolumeLimitChanged);

	iServiceVolume->SetPropertyVolumeChanged(functorVolume);
	iServiceVolume->SetPropertyMuteChanged(functorMute);
	iServiceVolume->SetPropertyVolumeLimitChanged(functorVolumeLimit);

	iServiceVolume->PropertyVolume(iVolume);
	iServiceVolume->PropertyMute(iMute);
	iServiceVolume->PropertyVolumeLimit(iVolumeLimit);

	iHandler.GroupVolumeControlChanged(*this);
}

void CpTopology3Group::EventVolumeChanged()
{
	LOG(kTopology, "CpTopology3Group::EventVolumeChanged ");
    LOG(kTopology, Name());
    LOG(kTopology, "\n");

    iServiceVolume->PropertyVolume(iVolume);

    iHandler.GroupVolumeChanged(*this);
}

void CpTopology3Group::EventMuteChanged()
{
	LOG(kTopology, "CpTopology3Group::EventMuteChanged ");
    LOG(kTopology, Name());
    LOG(kTopology, "\n");

    iServiceVolume->PropertyMute(iMute);

    iHandler.GroupMuteChanged(*this);
}

void CpTopology3Group::EventVolumeLimitChanged()
{
	LOG(kTopology, "CpTopology3Group::EventVolumeLimitChanged ");
    LOG(kTopology, Name());
    LOG(kTopology, "\n");

    iServiceVolume->PropertyVolumeLimit(iVolumeLimit);

    iHandler.GroupVolumeLimitChanged(*this);
}

void CpTopology3Group::CallbackSetVolume(IAsync& /*aAsync*/)
{
}

void CpTopology3Group::CallbackVolumeInc(IAsync& /*aAsync*/)
{
}

void CpTopology3Group::CallbackVolumeDec(IAsync& /*aAsync*/)
{
}

void CpTopology3Group::CallbackSetMute(IAsync& /*aAsync*/)
{
}

// CpTopology3Job

CpTopology3Job::CpTopology3Job(ICpTopology3Handler& aHandler)
{
    iHandler = &aHandler;
    iGroup = 0;
}
    
void CpTopology3Job::Set(CpTopology3Group& aGroup, ICpTopology3HandlerFunction aFunction)
{
    iGroup = &aGroup;
    iFunction = aFunction;
    iGroup->AddRef();
}

void CpTopology3Job::Execute()
{
    if (iGroup) {
        (iHandler->*iFunction)(*iGroup);
        iGroup->RemoveRef();
        iGroup = 0;
    }
    else {
        THROW(ThreadKill);
    }
}

// CpTopology3

CpTopology3::CpTopology3(ICpTopology3Handler& aHandler)
	: iFree(kMaxJobCount)
    , iReady(kMaxJobCount)
{
	for (TUint i = 0; i < kMaxJobCount; i++) {
        iFree.Write(new CpTopology3Job(aHandler));
    }

    iTopology2 = new CpTopology2(*this);

	iThread = new ThreadFunctor("TOP3", MakeFunctor(*this, &CpTopology3::Run));
    iThread->Start();
}

CpTopology3::~CpTopology3()
{
    LOG(kTopology, "CpTopology3::~CpTopology3\n");
    delete (iTopology2);
    LOG(kTopology, "CpTopology3::~CpTopology3 deleted layer 2\n");
    ASSERT(iGroupList.size() == 0);

	iReady.Write(iFree.Read()); // this null job causes the thread to complete

	delete (iThread);
    
    LOG(kTopology, "CpTopology3::~CpTopology3 deleted thread\n");

    for (TUint i = 0; i < kMaxJobCount; i++) {
        delete (iFree.Read());
    }

    LOG(kTopology, "CpTopology3::~CpTopology3 deleted jobs\n");
}
    
void CpTopology3::Refresh()
{
    ASSERT(iTopology2);
    iTopology2->Refresh();
}

// ICpTopology2Handler

void CpTopology3::GroupAdded(CpTopology2Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupAdded\n");

	CpTopology3Group* group = new CpTopology3Group(aGroup, *this);
	aGroup.SetUserData(group);
	group->GroupAdded();
}

void CpTopology3::GroupStandbyChanged(CpTopology2Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupStandbyChanged\n");
    ((CpTopology3Group*)aGroup.UserData())->GroupStandbyChanged();
}

void CpTopology3::GroupSourceIndexChanged(CpTopology2Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupSourceIndexChanged\n");
    ((CpTopology3Group*)aGroup.UserData())->GroupSourceIndexChanged();
}

void CpTopology3::GroupSourceListChanged(CpTopology2Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupSourceListChanged\n");
    ((CpTopology3Group*)aGroup.UserData())->GroupSourceListChanged();
}

void CpTopology3::GroupRemoved(CpTopology2Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupRemoved\n");
    ((CpTopology3Group*)aGroup.UserData())->GroupRemoved();
}

// ICpTopology3Handler

void CpTopology3::GroupAdded(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupAdded ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

	iGroupList.push_back(&aGroup);

    CpTopology3Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology3Handler::GroupAdded);
    iReady.Write(job);
}

void CpTopology3::GroupStandbyChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupStandbyChanged ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology3Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology3Handler::GroupStandbyChanged);
    iReady.Write(job);
}

void CpTopology3::GroupSourceIndexChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupSourceIndexChanged ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology3Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology3Handler::GroupSourceIndexChanged);
    iReady.Write(job);
}

void CpTopology3::GroupSourceListChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupSourceListChanged ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology3Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology3Handler::GroupSourceListChanged);
    iReady.Write(job);
}

void CpTopology3::GroupRemoved(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupRemoved ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

	std::list<CpTopology3Group*>::iterator it = iGroupList.begin();
    
    while (it != iGroupList.end()) {
        if (*it == &aGroup) {
            iGroupList.erase(it);

			CpTopology3Job* job = iFree.Read();
			job->Set(aGroup, &ICpTopology3Handler::GroupRemoved);
			iReady.Write(job);
			return;
		}
		it++;
	}

	ASSERTS();
}

void CpTopology3::GroupVolumeControlChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupVolumeControlChanged ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology3Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology3Handler::GroupVolumeControlChanged);
    iReady.Write(job);
}

void CpTopology3::GroupVolumeChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupVolumeChanged ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology3Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology3Handler::GroupVolumeChanged);
    iReady.Write(job);
}

void CpTopology3::GroupMuteChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupMuteChanged ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology3Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology3Handler::GroupMuteChanged);
    iReady.Write(job);
}

void CpTopology3::GroupVolumeLimitChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology3::GroupVolumeLimitChanged ");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, "\n");

    CpTopology3Job* job = iFree.Read();
    job->Set(aGroup, &ICpTopology3Handler::GroupVolumeLimitChanged);
    iReady.Write(job);
}


void CpTopology3::Run()
{
	LOG(kTopology, "CpTopology3::Run Started\n");

    for (;;)
    {
        CpTopology3Job* job = iReady.Read();
        
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

	LOG(kTopology, "CpTopology3::Run Exiting\n");
}
