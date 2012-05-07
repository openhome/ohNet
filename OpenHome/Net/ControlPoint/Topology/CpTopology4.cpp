#include "CpTopology4.h"

#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Net/Private/XmlParser.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpTopology4Source

CpTopology4Source::CpTopology4Source(CpTopology4Group& aGroup, TUint aIndex)
    : iGroup(aGroup)
    , iIndex(aIndex)
{
}

const Brx& CpTopology4Source::Name() const
{
    return (iGroup.Group().SourceName(iIndex));
}

const Brx& CpTopology4Source::Type() const
{
    return (iGroup.Group().SourceType(iIndex));
}

const Brx& CpTopology4Source::Group() const
{
    return (iGroup.Group().Name());
}

CpDevice& CpTopology4Source::Device() const
{
    return (iGroup.Group().Device());
}
    
TUint CpTopology4Source::ChildCount() const
{
    return (TUint)iChildList.size();
}

CpTopology4Group& CpTopology4Source::Child(TUint aIndex) const
{
    ASSERT(aIndex < iChildList.size());
    return (*iChildList[aIndex]);
}
    
void CpTopology4Source::AddChild(CpTopology4Group& aGroup)
{
    iChildList.push_back(&aGroup);
}

void CpTopology4Source::RemoveChild(CpTopology4Group& aGroup)
{
    std::vector<CpTopology4Group*>::iterator it = iChildList.begin();
    
    while (it != iChildList.end()) {
        if (*it == &aGroup) {
            iChildList.erase(it);
            return;
        }
        it++;
    }
    
    ASSERTS();
}

void CpTopology4Source::ClearChildren()
{
    // the reason we don't just iterate normally over the child list is because
    // the ClearParent function does itself change the child list, which
    // messes with our iterator
    
    while (iChildList.size() != 0) {
        std::vector<CpTopology4Group*>::iterator it = iChildList.begin();
        (*it)->ClearParent();
    }
}

TUint CpTopology4Source::EvaluateSources(std::vector<CpTopology4Source*>& aVector)
{
    iSourceCount = 0;
    
    if (iChildList.size() == 0) {
        if (iGroup.Group().SourceVisible(iIndex)) {
            iSourceCount = 1;
            aVector.push_back(this);
        }
    }
    else {
        std::vector<CpTopology4Group*>::iterator it = iChildList.begin();
        
        while (it != iChildList.end()) {
            iSourceCount += (*it)->EvaluateSources(aVector);
            it++;
        }
    }

    return (iSourceCount);
}

void CpTopology4Source::Select()
{
    iGroup.Group().SetSourceIndex(iIndex);
}

CpTopology4Group& CpTopology4Source::Owner() const
{
    return (iGroup);
}

TUint CpTopology4Source::SourceCount() const
{
    return (iSourceCount);
}

CpTopology4Source::~CpTopology4Source()
{
    ASSERT(iChildList.size() == 0);
}
    
// CpTopology4Group

CpTopology4Group::CpTopology4Group(CpTopology3Group& aGroup, CpTopology4Room& aRoom)
    : iGroup(aGroup)
    , iRoom(aRoom)
    , iParent(0)
    , iParentSourceIndex(0)
    , iIsRoot(false)
{
    iGroup.AddRef();

    for (TUint i = 0; i < iGroup.SourceCount(); i++) {
        iSourceList.push_back(new CpTopology4Source(*this, i));
    }
}

CpTopology3Group& CpTopology4Group::Group() const
{
    return (iGroup);
}

CpTopology4Room& CpTopology4Group::Room() const
{
    return (iRoom);
}

CpTopology4Group::~CpTopology4Group()
{
    std::vector<CpTopology4Source*>::iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        delete (*it);
        it++;
    }
    
    iGroup.RemoveRef();
}

const Brx& CpTopology4Group::Name() const
{
    return (iGroup.Name());
}

TBool CpTopology4Group::HasParent() const
{
    return (iParent != NULL);
}

CpTopology4Group& CpTopology4Group::Parent() const
{
    ASSERT(iParent);
    return (*iParent);
}

TUint CpTopology4Group::ParentSourceIndex() const
{
    ASSERT(iParent);
    return (iParentSourceIndex);
}

TBool CpTopology4Group::IsRoot() const
{
    return (iIsRoot);
}

void CpTopology4Group::SetIsRoot(TBool aValue)
{
    iIsRoot = aValue;
}

TUint CpTopology4Group::EvaluateSources(std::vector<CpTopology4Source*>& aVector)
{
    iSourceCount = 0;

    std::vector<CpTopology4Source*>::iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        iSourceCount += (*it)->EvaluateSources(aVector);
        it++;
    }

    return (iSourceCount);
}

TUint CpTopology4Group::SourceCount() const
{
    return (iSourceCount);
}

TBool CpTopology4Group::IsCurrentDescendentOf(CpTopology4Group& aGroup) const
{
    const CpTopology4Group* group = this;

    for (;;) {
        if (group == &aGroup) {
            return (true);
        }

        if (group->HasParent()) {
            TUint index = group->ParentSourceIndex();
            group = &group->Parent();
            if (group->Group().SourceIndex() == index) {
                continue;
            }
        }

        return (false);
    }
}

TBool CpTopology4Group::IsDescendentOf(CpTopology4Group& aGroup) const
{
    const CpTopology4Group* group = this;

    for (;;) {
        if (group == &aGroup) {
            return (true);
        }

        if (!group->HasParent()) {
            return (false);
        }

        group = &group->Parent();
    }
}

CpTopology4Group&  CpTopology4Group::CurrentDescendent()
{
    CpTopology4Group* group = this;

    for (;;) {
        TUint index = group->Group().SourceIndex();
        CpTopology4Source& source = group->Source(index);
        if (source.ChildCount() > 0) {
            group = &source.Child(0);
            continue;
        }
        return (*group);
    }
}

CpTopology4Group&  CpTopology4Group::Root()
{
    CpTopology4Group* group = this;

    for (;;) {
        if (group->HasParent()) {
            group = &group->Parent();
            continue;
        }
        return (*group);
    }
}

CpTopology4Source& CpTopology4Group::Source(TUint aIndex) const
{
    ASSERT(aIndex < iSourceList.size());
    return (*iSourceList[aIndex]);
}

void CpTopology4Group::ClearChildren()
{
    std::vector<CpTopology4Source*>::iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        (*it)->ClearChildren();
        it++;
    }
}

void CpTopology4Group::ClearParent()
{
    ASSERT(iParent != NULL);
    iParent->RemoveChild(*this, iParentSourceIndex);
    iParent = NULL;
}

void CpTopology4Group::SetParent(CpTopology4Group& aGroup, TUint aSourceIndex)
{
    ASSERT(iParent == NULL);
    iParent = &aGroup;
    iParentSourceIndex = aSourceIndex;
}

TBool CpTopology4Group::AddIfIsChild(CpTopology4Group& aGroup)
{
    const Brx& name = aGroup.Name();
    
    TUint count = iGroup.SourceCount();
    
    for (TUint i = 0; i < count; i++) {
        if (iGroup.SourceName(i) == name) {
            iSourceList[i]->AddChild(aGroup);
            aGroup.SetParent(*this, i);
            return (true);      
        }
    }

    return (false); 
}

void CpTopology4Group::AddChild(CpTopology4Group& aGroup, TUint aSourceIndex)
{
    ASSERT(aSourceIndex < iSourceList.size());
    iSourceList[aSourceIndex]->AddChild(aGroup);
}

void CpTopology4Group::RemoveChild(CpTopology4Group& aGroup, TUint aSourceIndex)
{
    ASSERT(aSourceIndex < iSourceList.size());
    iSourceList[aSourceIndex]->RemoveChild(aGroup);
}

void CpTopology4Group::GroupStandbyChanged()
{
    LOG(kTopology, "CpTopology4Group::GroupStandbyChanged\n");
    iRoom.GroupStandbyChanged(*this);
}

void CpTopology4Group::GroupSourceIndexChanged()
{
    LOG(kTopology, "CpTopology4Group::GroupSourceIndexChanged\n");
    iRoom.GroupSourceIndexChanged(*this);
}

void CpTopology4Group::GroupSourceListChanged()
{
    LOG(kTopology, "CpTopology4Group::GroupSourceListChanged\n");
    iRoom.GroupSourceListChanged(*this);
}

void CpTopology4Group::GroupRemoved()
{
    LOG(kTopology, "CpTopology4Group::GroupRemoved\n");
    iRoom.GroupRemoved(*this);
    delete(this);
}

void CpTopology4Group::GroupVolumeControlChanged()
{
	LOG(kTopology, "CpTopology4Group::GroupVolumeControlChanged\n");
    iRoom.GroupVolumeControlChanged(*this);
}

void CpTopology4Group::GroupVolumeChanged()
{
	LOG(kTopology, "CpTopology4Group::GroupVolumeChanged\n");
    iRoom.GroupVolumeChanged(*this);
}

void CpTopology4Group::GroupMuteChanged()
{
	LOG(kTopology, "CpTopology4Group::GroupMuteChanged\n");
    iRoom.GroupMuteChanged(*this);
}

void CpTopology4Group::GroupVolumeLimitChanged()
{
	LOG(kTopology, "CpTopology4Group::GroupVolumeLimitChanged\n");
    iRoom.GroupVolumeLimitChanged(*this);
}


// CpTopology4Room

CpTopology4Room::CpTopology4Room(const Brx& aName, ICpTopology4Handler& aHandler)
    : iName(aName)
    , iHandler(aHandler)
    , iCurrentGroup(0)
    , iActive(false)
    , iMutex("T3RM")
    , iSourceCount(0)
    , iStandbyCount(0)
    , iStandby(eOff)
    , iRefCount(1)
    , iUserData(0)
{
}

CpTopology4Room::~CpTopology4Room()
{
    ASSERT(iGroupList.size() == 0);
}

void CpTopology4Room::SetUserData(void* aValue)
{
    iUserData = aValue;
}

void* CpTopology4Room::UserData() const
{
    return (iUserData);
}

void CpTopology4Room::ReportGroups()
{
    std::vector<CpTopology4Group*>::const_iterator it;
    
    LOG(kTopology, "=== GROUPS ===\n");

    it = iGroupList.begin();

    while (it != iGroupList.end()) {
        LOG(kTopology, (*it)->Group().Room());
        LOG(kTopology, ":");
        LOG(kTopology, (*it)->Group().Name());
        LOG(kTopology, "\n");
        it++;
    }

    LOG(kTopology, "=== ROOTS  ===\n");

    it = iRootList.begin();

    while (it != iRootList.end()) {
        LOG(kTopology, (*it)->Group().Room());
        LOG(kTopology, ":");
        LOG(kTopology, (*it)->Group().Name());
        LOG(kTopology, "\n");
        it++;
    }

    LOG(kTopology, "==============\n");
}

// ICpTopology3Handler
    
void CpTopology4Room::GroupAdded(CpTopology4Group& aGroup)
{
    LOG(kTopology, "CpTopology4Room::GroupAdded(");
    LOG(kTopology, iName);
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, ")\n");

    iMutex.Wait();

    // Check if this is the first group

    if (iCurrentGroup == 0) {
        iCurrentGroup = &aGroup;
        aGroup.SetIsRoot(true);
        iGroupList.push_back(&aGroup);
        iRootList.push_back(&aGroup);
        if (aGroup.Group().Standby()) {
            iStandbyCount++;
            iStandby = eOn;
        }
        iSourceCount = EvaluateSources();
        iHandler.RoomAdded(*this);
        iMutex.Signal();
        return;
    }

    std::vector<CpTopology4Group*>::iterator it;

    // Check if this has an existing parent
    
    it = iGroupList.begin();
    
    while (it != iGroupList.end()) {
        if ((*it)->AddIfIsChild(aGroup)) {
            iGroupList.push_back(&aGroup);
            if (aGroup.IsCurrentDescendentOf(*iCurrentGroup)) {
                UpdateCurrentGroup(aGroup);
            }
            iSourceCount = EvaluateSources();
            iHandler.RoomChanged(*this);
            iMutex.Signal();
            return;
        }
        it++;
    }
    
    // Check if this is the parent of an existing root
    
    it = iRootList.begin();
    
    while (it != iRootList.end()) {
        CpTopology4Group* group = *it;
        if (aGroup.AddIfIsChild(*group)) {
            iRootList.erase(it);
            group->SetIsRoot(false);
            if (group == iCurrentGroup) {
                if (!group->IsCurrentDescendentOf(aGroup)) {
                    UpdateCurrentGroup(aGroup);
                }
            }
            break;
        }
        it++;
    }
    
    aGroup.SetIsRoot(true);
    iGroupList.push_back(&aGroup);
    iRootList.push_back(&aGroup);

	// evaluate standby

    if (aGroup.Group().Standby()) {
        iStandbyCount++;
		EvaluateStandby();
    }

    iSourceCount = EvaluateSources();
    
	iHandler.RoomChanged(*this);
    
	iMutex.Signal();
}

void CpTopology4Room::GroupRemoved(CpTopology4Group& aGroup)
{
    LOG(kTopology, "CpTopology4Room::GroupRemoved(");
    LOG(kTopology, iName);
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, ")\n");

    CpTopology4Group* parent = 0;

    if (aGroup.HasParent()) {
        parent = &aGroup.Parent();
    }

    iMutex.Wait();

    std::vector<CpTopology4Group*>::iterator it = iGroupList.begin();
    
    while (it != iGroupList.end()) {
        if (*it == &aGroup) {
            iGroupList.erase(it);
            break;
        }
        it++;
    }
    
    if (aGroup.IsRoot()) {
        it = iRootList.begin();
        while (it != iRootList.end()) {
            if (*it == &aGroup) {
                iRootList.erase(it);
                break;
            }
            it++;
        }
    }
    else {
        aGroup.ClearParent();
    }
            
    aGroup.ClearChildren();
    
    // now check orphaned groups
    // remap them or change them to root groups
    
    it = iGroupList.begin();
    
    while (it != iGroupList.end()) {
        if (!(*it)->IsRoot() && !(*it)->HasParent()) { // indicates this group has been orphaned
            (*it)->SetIsRoot(true);
            iRootList.push_back(*it);
        }
        it++;
    }

    iSourceCount = EvaluateSources();

    // check for last group in this room
    
    if (iGroupList.size() == 0) {
		iCurrentGroup = 0;
        iHandler.RoomRemoved(*this);
        iMutex.Signal();
        RemoveRef();
        return;
    }

    if (aGroup.Group().Standby()) {
        iStandbyCount--;
        EvaluateStandby();
    }

    // if this is the current group, assign a new one

    if (iCurrentGroup == &aGroup) {
        if (parent == 0) {
            parent = *iRootList.begin();
        }
        UpdateCurrentGroup(parent->CurrentDescendent());
    }

    iHandler.RoomChanged(*this);

    iMutex.Signal();
}

void CpTopology4Room::GroupVolumeControlChanged(CpTopology4Group& /*aGroup*/)
{
	iHandler.RoomVolumeControlChanged(*this);
}

void CpTopology4Room::GroupVolumeChanged(CpTopology4Group& /*aGroup*/)
{
	iHandler.RoomVolumeChanged(*this);
}

void CpTopology4Room::GroupMuteChanged(CpTopology4Group& /*aGroup*/)
{
	iHandler.RoomMuteChanged(*this);
}

void CpTopology4Room::GroupVolumeLimitChanged(CpTopology4Group& /*aGroup*/)
{
	iHandler.RoomVolumeLimitChanged(*this);
}


// Must be called with iMutex locked

void CpTopology4Room::UpdateCurrentGroup(CpTopology4Group& aGroup)
{
    CpTopology3Group& root = aGroup.Root().Group();
	CpTopology4Group* oldGroup = iCurrentGroup;

	LOG(kTopology, "CpTopology4Room::UpdateCurrentGroup(");
    LOG(kTopology, iName);
    LOG(kTopology, ":");
	LOG(kTopology, root.Name());
	LOG(kTopology, ":");
	LOG(kTopology, aGroup.Group().HasVolumeControl() ? Brn("Yes") : Brn("No"));
	LOG(kTopology, ":");
    LOG(kTopology, root.HasVolumeControl() ? Brn("Yes") : Brn("No"));
    LOG(kTopology, ")\n");

    iCurrentGroup = &aGroup;

	if (&oldGroup->Root().Group() != &root) {
		if(root.HasVolumeControl() || root.HasVolumeControl() != oldGroup->Group().HasVolumeControl()) {
			iHandler.RoomVolumeControlChanged(*this);
		}
    }

    iHandler.RoomSourceChanged(*this);
}

void CpTopology4Room::GroupStandbyChanged(CpTopology4Group& aGroup)
{
    aGroup.Group().Standby() ? iStandbyCount++ : iStandbyCount--;
    EvaluateStandby();
}

void CpTopology4Room::EvaluateStandby()
{
    EStandby standby = eOff;

    if (iStandbyCount > 0) {
        standby = eMixed;
        if (iStandbyCount == iGroupList.size()) {
            standby = eOn;
        }
    }

    if (iStandby != standby) {
        iStandby = standby;
        iHandler.RoomStandbyChanged(*this);
    }
}


void CpTopology4Room::GroupSourceIndexChanged(CpTopology4Group& aGroup)
{
    iMutex.Wait();

    if (iCurrentGroup->IsDescendentOf(aGroup)) {
        UpdateCurrentGroup(aGroup.CurrentDescendent());
    }

    iMutex.Signal();
}

void CpTopology4Room::GroupSourceListChanged(CpTopology4Group& /*aGroup*/)
{
    iSourceCount = EvaluateSources();
    iHandler.RoomChanged(*this);
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

TUint CpTopology4Room::SourceCount() const
{
    return (iSourceCount);
}

void CpTopology4Room::SetSourceIndex(TUint aIndex)
{
    iMutex.Wait();

    if (aIndex >= iSourceCount) {
        iMutex.Signal();
        return;
    }

    CpTopology4Source* source = iSourceList[aIndex];

    source->Select();

    CpTopology4Group* group = &source->Owner();

    while (group->HasParent()) {
        TUint index = group->ParentSourceIndex();
        group = &group->Parent();
        group->Source(index).Select();
    }

    iMutex.Signal();
}

void CpTopology4Room::SetStandby(TBool aValue)
{
    iMutex.Wait();

    std::vector<CpTopology4Group*>::iterator it = iGroupList.begin();
    
    while (it != iGroupList.end()) {
        (*it)->Group().SetStandby(aValue);
        it++;
    }
    
    iMutex.Signal();    
}

void CpTopology4Room::SetVolume(TUint aValue)
{
	iMutex.Wait();

	iCurrentGroup->Root().Group().SetVolume(aValue);

	iMutex.Signal();
}

void CpTopology4Room::VolumeInc()
{
	iMutex.Wait();

	iCurrentGroup->Root().Group().VolumeInc();

	iMutex.Signal();
}

void CpTopology4Room::VolumeDec()
{
	iMutex.Wait();

	iCurrentGroup->Root().Group().VolumeDec();

	iMutex.Signal();
}

void CpTopology4Room::SetMute(TBool aValue)
{
	iMutex.Wait();

	iCurrentGroup->Root().Group().SetMute(aValue);

	iMutex.Signal();
}

const Brx& CpTopology4Room::Name() const
{
    return (iName);
}

TUint CpTopology4Room::EvaluateSources()
{
    iSourceList.clear();

    TUint count = 0;
    
    if (iRootList.size() > 0) {
        std::vector<CpTopology4Group*>::const_iterator it = iRootList.begin();
        while (it != iRootList.end()) {
            count += (*it)->EvaluateSources(iSourceList);
            it++;
        }
    }
    
    return (count);
}


const Brx& CpTopology4Room::SourceName(TUint aIndex) const
{
    ASSERT(aIndex < iSourceCount);
    return (iSourceList[aIndex]->Name());
}

const Brx& CpTopology4Room::SourceType(TUint aIndex) const
{
    ASSERT(aIndex < iSourceCount);
    return (iSourceList[aIndex]->Type());
}

const Brx& CpTopology4Room::SourceGroup(TUint aIndex) const
{
    ASSERT(aIndex < iSourceCount);
    return (iSourceList[aIndex]->Group());
}

CpDevice& CpTopology4Room::SourceDevice(TUint aIndex) const
{
    ASSERT(aIndex < iSourceCount);
    return (iSourceList[aIndex]->Device());
}

const Brx& CpTopology4Room::CurrentSourceName() const
{
    ASSERT(iCurrentGroup);
    CpTopology3Group& group = iCurrentGroup->Group();
    return (group.SourceName(group.SourceIndex()));
}

const Brx& CpTopology4Room::CurrentSourceType() const
{
    ASSERT(iCurrentGroup);
    CpTopology3Group& group = iCurrentGroup->Group();
    return (group.SourceType(group.SourceIndex()));
}

const Brx& CpTopology4Room::CurrentSourceGroup() const
{
    ASSERT(iCurrentGroup);
    CpTopology3Group& group = iCurrentGroup->Group();
    return (group.Name());
}

CpDevice& CpTopology4Room::CurrentSourceDevice() const
{
    ASSERT(iCurrentGroup);
    CpTopology3Group& group = iCurrentGroup->Group();
    return (group.Device());
}

TBool CpTopology4Room::HasVolumeControl() const
{
    return (iCurrentGroup->Root().Group().HasVolumeControl());
}

TUint CpTopology4Room::Volume() const
{
	return (iCurrentGroup->Root().Group().Volume());
}

TBool CpTopology4Room::Mute() const
{
	return (iCurrentGroup->Root().Group().Mute());
}

TUint CpTopology4Room::VolumeLimit() const
{
	return (iCurrentGroup->Root().Group().VolumeLimit());
}

CpTopology4Room::EStandby CpTopology4Room::Standby() const
{
    return (iStandby);
}

// CpTopology4

CpTopology4::CpTopology4(ICpTopology4Handler& aHandler)
    : iHandler(aHandler)
{
    iTopology3 = new CpTopology3(*this);
}

CpTopology4::CpTopology4(ICpTopology4Handler& aHandler, ICpTopology3Handler** aTestInterface)
    : iHandler(aHandler)
    , iTopology3(0)
{
    *aTestInterface = this;
}

CpTopology4::~CpTopology4()
{
    LOG(kTopology, "CpTopology4::~CpTopology4\n");
    delete (iTopology3);
    LOG(kTopology, "CpTopology4::~CpTopology4 deleted layer 3\n");
    ASSERT(iRoomList.size() == 0);
}
    
void CpTopology4::Refresh()
{
    ASSERT(iTopology3);
    iTopology3->Refresh();
}

// ICpTopology3Handler
    
void CpTopology4::GroupAdded(CpTopology3Group& aGroup)
{
    LOG(kTopology, "CpTopology4::GroupAdded\n");
    CpTopology4Room* room = 0;

    std::list<CpTopology4Room*>::iterator it = iRoomList.begin();
    
    while (it != iRoomList.end()) {
        if ((*it)->Name() == aGroup.Room()) {
            room = *it;
            break;
        }
        it++;
    }

    if (room == 0) {
        room = new CpTopology4Room(aGroup.Room(), *this);
    }

    CpTopology4Group* group = new CpTopology4Group(aGroup, *room);

    aGroup.SetUserData(group);

    room->GroupAdded(*group);
}

void CpTopology4::GroupStandbyChanged(CpTopology3Group& aGroup)
{
    LOG(kTopology, "CpTopology4::GroupStandbyChanged\n");
    ((CpTopology4Group*)aGroup.UserData())->GroupStandbyChanged();
}

void CpTopology4::GroupSourceIndexChanged(CpTopology3Group& aGroup)
{
    LOG(kTopology, "CpTopology4::GroupSourceIndexChanged\n");
    ((CpTopology4Group*)aGroup.UserData())->GroupSourceIndexChanged();
}

void CpTopology4::GroupSourceListChanged(CpTopology3Group& aGroup)
{
    LOG(kTopology, "CpTopology4::GroupSourceListChanged\n");
    ((CpTopology4Group*)aGroup.UserData())->GroupSourceListChanged();
}

void CpTopology4::GroupRemoved(CpTopology3Group& aGroup)
{
    LOG(kTopology, "CpTopology4::GroupRemoved\n");
    ((CpTopology4Group*)aGroup.UserData())->GroupRemoved();
}

void CpTopology4::GroupVolumeControlChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology4::GroupVolumeControlChanged\n");
    ((CpTopology4Group*)aGroup.UserData())->GroupVolumeControlChanged();
}

void CpTopology4::GroupVolumeChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology4::GroupVolumeChanged\n");
    ((CpTopology4Group*)aGroup.UserData())->GroupVolumeChanged();
}

void CpTopology4::GroupMuteChanged(CpTopology3Group& aGroup) 
{
	LOG(kTopology, "CpTopology4::GroupMuteChanged\n");
    ((CpTopology4Group*)aGroup.UserData())->GroupMuteChanged();
}

void CpTopology4::GroupVolumeLimitChanged(CpTopology3Group& aGroup)
{
	LOG(kTopology, "CpTopology4::GroupVolumeLimitChanged\n");
    ((CpTopology4Group*)aGroup.UserData())->GroupVolumeLimitChanged();
}

// ICpTopology4Handler
    
void CpTopology4::RoomAdded(CpTopology4Room& aRoom)
{
    LOG(kTopology, "CpTopology4::RoomAdded ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iRoomList.push_back(&aRoom);
        
    iHandler.RoomAdded(aRoom);
}

void CpTopology4::RoomChanged(CpTopology4Room& aRoom)
{
    LOG(kTopology, "CpTopology4::RoomChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomChanged(aRoom);
}

void CpTopology4::RoomRemoved(CpTopology4Room& aRoom)
{
    LOG(kTopology, "CpTopology4::RoomRemoved ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    std::list<CpTopology4Room*>::iterator it = iRoomList.begin();
    
    while (it != iRoomList.end()) {
        if (*it == &aRoom) {
            iRoomList.erase(it);
            iHandler.RoomRemoved(aRoom);
            return;
        }
        it++;
    }
    
    ASSERTS();
}

void CpTopology4::RoomStandbyChanged(CpTopology4Room& aRoom)
{
    LOG(kTopology, "CpTopology4::RoomStandbyChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomStandbyChanged(aRoom);
}

void CpTopology4::RoomSourceChanged(CpTopology4Room& aRoom)
{
    LOG(kTopology, "CpTopology4::RoomSourceChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomSourceChanged(aRoom);
}

void CpTopology4::RoomVolumeControlChanged(CpTopology4Room& aRoom)
{
    LOG(kTopology, "CpTopology4::RoomVolumeControlChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomVolumeControlChanged(aRoom);
}

void CpTopology4::RoomVolumeChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomVolumeChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomVolumeChanged(aRoom);
}

void CpTopology4::RoomMuteChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomMuteChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomMuteChanged(aRoom);
}

void CpTopology4::RoomVolumeLimitChanged(CpTopology4Room& aRoom)
{
	LOG(kTopology, "CpTopology4::RoomVolumeLimitChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomVolumeLimitChanged(aRoom);
}

