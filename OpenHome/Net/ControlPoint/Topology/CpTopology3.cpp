#include "CpTopology3.h"

#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Net/Private/XmlParser.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpTopology3Source

CpTopology3Source::CpTopology3Source(CpTopology3Group& aGroup, TUint aIndex)
    : iGroup(aGroup)
    , iIndex(aIndex)
{
}

const Brx& CpTopology3Source::Name() const
{
	return (iGroup.Group().SourceName(iIndex));
}

const Brx& CpTopology3Source::Type() const
{
	return (iGroup.Group().SourceType(iIndex));
}

const Brx& CpTopology3Source::Group() const
{
	return (iGroup.Group().Name());
}

CpDevice& CpTopology3Source::Device() const
{
	return (iGroup.Group().Device());
}
	
TUint CpTopology3Source::ChildCount() const
{
	return (TUint)iChildList.size();
}

CpTopology3Group& CpTopology3Source::Child(TUint aIndex) const
{
	ASSERT(aIndex < iChildList.size());
	return (*iChildList[aIndex]);
}
	
void CpTopology3Source::AddChild(CpTopology3Group& aGroup)
{
	iChildList.push_back(&aGroup);
}

void CpTopology3Source::RemoveChild(CpTopology3Group& aGroup)
{
	std::vector<CpTopology3Group*>::iterator it = iChildList.begin();
	
	while (it != iChildList.end()) {
		if (*it == &aGroup) {
			iChildList.erase(it);
			return;
		}
		it++;
	}
	
	ASSERTS();
}

void CpTopology3Source::ClearChildren()
{
    // the reason we don't just iterate normally over the child list is because
    // the ClearParent function does itself change the child list, which
    // messes with our iterator
    
    while (iChildList.size() != 0) {
    	std::vector<CpTopology3Group*>::iterator it = iChildList.begin();
   		(*it)->ClearParent();
   	}
}

TUint CpTopology3Source::EvaluateSources(std::vector<CpTopology3Source*>& aVector)
{
    iSourceCount = 0;
    
    if (iChildList.size() == 0) {
        if (iGroup.Group().SourceVisible(iIndex)) {
            iSourceCount = 1;
			aVector.push_back(this);
        }
    }
    else {
        std::vector<CpTopology3Group*>::iterator it = iChildList.begin();
        
        while (it != iChildList.end()) {
            iSourceCount += (*it)->EvaluateSources(aVector);
            it++;
        }
    }

    return (iSourceCount);
}

void CpTopology3Source::Select()
{
	iGroup.Group().SetSourceIndex(iIndex);
}

CpTopology3Group& CpTopology3Source::Owner() const
{
	return (iGroup);
}

TUint CpTopology3Source::SourceCount() const
{
    return (iSourceCount);
}

CpTopology3Source::~CpTopology3Source()
{
	ASSERT(iChildList.size() == 0);
}
	
// CpTopology3Group

CpTopology3Group::CpTopology3Group(CpTopology2Group& aGroup, CpTopology3Room& aRoom)
	: iGroup(aGroup)
	, iRoom(aRoom)
	, iParent(0)
	, iParentSourceIndex(0)
	, iIsRoot(false)
{
	iGroup.AddRef();

	for (TUint i = 0; i < iGroup.SourceCount(); i++) {
		iSourceList.push_back(new CpTopology3Source(*this, i));
	}
}

CpTopology2Group& CpTopology3Group::Group() const
{
	return (iGroup);
}

CpTopology3Room& CpTopology3Group::Room() const
{
	return (iRoom);
}

CpTopology3Group::~CpTopology3Group()
{
	std::vector<CpTopology3Source*>::iterator it = iSourceList.begin();
	
	while (it != iSourceList.end()) {
		delete (*it);
		it++;
	}
	
	iGroup.RemoveRef();
}

const Brx& CpTopology3Group::Name() const
{
	return (iGroup.Name());
}

TBool CpTopology3Group::HasParent() const
{
	return (iParent != NULL);
}

CpTopology3Group& CpTopology3Group::Parent() const
{
	ASSERT(iParent);
	return (*iParent);
}

TUint CpTopology3Group::ParentSourceIndex() const
{
	ASSERT(iParent);
	return (iParentSourceIndex);
}

TBool CpTopology3Group::IsRoot() const
{
	return (iIsRoot);
}

void CpTopology3Group::SetIsRoot(TBool aValue)
{
	iIsRoot = aValue;
}

TUint CpTopology3Group::EvaluateSources(std::vector<CpTopology3Source*>& aVector)
{
    iSourceCount = 0;

    std::vector<CpTopology3Source*>::iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        iSourceCount += (*it)->EvaluateSources(aVector);
        it++;
    }

    return (iSourceCount);
}

TUint CpTopology3Group::SourceCount() const
{
    return (iSourceCount);
}

TBool CpTopology3Group::IsCurrentDescendentOf(CpTopology3Group& aGroup) const
{
	const CpTopology3Group* group = this;

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

TBool CpTopology3Group::IsDescendentOf(CpTopology3Group& aGroup) const
{
	const CpTopology3Group* group = this;

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

CpTopology3Group&  CpTopology3Group::CurrentDescendent()
{
	CpTopology3Group* group = this;

	for (;;) {
		TUint index = group->Group().SourceIndex();
		CpTopology3Source& source = group->Source(index);
		if (source.ChildCount() > 0) {
			group = &source.Child(0);
			continue;
		}
		return (*group);
	}
}

CpTopology3Group&  CpTopology3Group::Root()
{
	CpTopology3Group* group = this;

	for (;;) {
		if (group->HasParent()) {
			group = &group->Parent();
			continue;
		}
		return (*group);
	}
}

CpTopology3Source& CpTopology3Group::Source(TUint aIndex) const
{
	ASSERT(aIndex < iSourceList.size());
	return (*iSourceList[aIndex]);
}

void CpTopology3Group::ClearChildren()
{
	std::vector<CpTopology3Source*>::iterator it = iSourceList.begin();
	
	while (it != iSourceList.end()) {
        (*it)->ClearChildren();
        it++;
	}
}

void CpTopology3Group::ClearParent()
{
	ASSERT(iParent != NULL);
	iParent->RemoveChild(*this, iParentSourceIndex);
	iParent = NULL;
}

void CpTopology3Group::SetParent(CpTopology3Group& aGroup, TUint aSourceIndex)
{
    ASSERT(iParent == NULL);
	iParent = &aGroup;
	iParentSourceIndex = aSourceIndex;
}

TBool CpTopology3Group::AddIfIsChild(CpTopology3Group& aGroup)
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

void CpTopology3Group::AddChild(CpTopology3Group& aGroup, TUint aSourceIndex)
{
	ASSERT(aSourceIndex < iSourceList.size());
	iSourceList[aSourceIndex]->AddChild(aGroup);
}

void CpTopology3Group::RemoveChild(CpTopology3Group& aGroup, TUint aSourceIndex)
{
	ASSERT(aSourceIndex < iSourceList.size());
	iSourceList[aSourceIndex]->RemoveChild(aGroup);
}

void CpTopology3Group::GroupStandbyChanged()
{
    LOG(kTopology, "CpTopology3Group::GroupStandbyChanged\n");
	iRoom.GroupStandbyChanged(*this);
}

void CpTopology3Group::GroupSourceIndexChanged()
{
    LOG(kTopology, "CpTopology3Group::GroupSourceIndexChanged\n");
	iRoom.GroupSourceIndexChanged(*this);
}

void CpTopology3Group::GroupSourceListChanged()
{
    LOG(kTopology, "CpTopology3Group::GroupSourceListChanged\n");
	iRoom.GroupSourceListChanged(*this);
}

void CpTopology3Group::GroupRemoved()
{
    LOG(kTopology, "CpTopology3Group::GroupRemoved\n");
	iRoom.GroupRemoved(*this);
	delete(this);
}


// CpTopology3Room

CpTopology3Room::CpTopology3Room(const Brx& aName, ICpTopology3Handler& aHandler)
	: iName(aName)
	, iHandler(aHandler)
	, iCurrentGroup(0)
	, iActive(false)
	, iMutex("T3RM")
	, iSourceCount(0)
	, iStandbyCount(0)
	, iStandby(eOff)
	, iRefCount(1)
	, iVolumeDevice(0)
	, iUserData(0)
{
}

CpTopology3Room::~CpTopology3Room()
{
	ASSERT(iGroupList.size() == 0);
}

void CpTopology3Room::SetUserData(void* aValue)
{
    iUserData = aValue;
}

void* CpTopology3Room::UserData() const
{
    return (iUserData);
}

void CpTopology3Room::ReportGroups()
{
	std::vector<CpTopology3Group*>::const_iterator it;
	
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

// ICpTopology2Handler
    
void CpTopology3Room::GroupAdded(CpTopology3Group& aGroup)
{
    LOG(kTopology, "CpTopology3Room::GroupAdded(");
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
		if (aGroup.Group().HasVolumeControl()) {
			iVolumeDevice = &aGroup.Group().Device();
		}
		if (aGroup.Group().Standby()) {
			iStandbyCount++;
			iStandby = eOn;
		}
		iSourceCount = EvaluateSources();
		iHandler.RoomAdded(*this);
		iMutex.Signal();
		return;
	}

	// evaluate standby

	if (aGroup.Group().Standby()) {
		iStandbyCount++;
		EvaluateStandby();
	}

	std::vector<CpTopology3Group*>::iterator it;

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
		CpTopology3Group* group = *it;
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
	iSourceCount = EvaluateSources();
	iHandler.RoomChanged(*this);
	iMutex.Signal();
}

void CpTopology3Room::GroupRemoved(CpTopology3Group& aGroup)
{
    LOG(kTopology, "CpTopology3Room::GroupRemoved(");
    LOG(kTopology, iName);
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, ")\n");

	CpTopology3Group* parent = 0;

	if (aGroup.HasParent()) {
		parent = &aGroup.Parent();
	}

	iMutex.Wait();

	std::vector<CpTopology3Group*>::iterator it = iGroupList.begin();
	
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


// Must be called with iMutex locked

void CpTopology3Room::UpdateCurrentGroup(CpTopology3Group& aGroup)
{
	CpTopology2Group& root = aGroup.Root().Group();
	CpDevice& device = root.Device();

	if (root.HasVolumeControl()) {
		if (iVolumeDevice != &device) {
			iVolumeDevice = &device;
			iHandler.RoomVolumeControlChanged(*this);
		}
	}
	else {
		if (iVolumeDevice != 0) {
			iVolumeDevice = 0;
			iHandler.RoomVolumeControlChanged(*this);
		}
	}

	iCurrentGroup = &aGroup;
	iHandler.RoomSourceChanged(*this);
}

void CpTopology3Room::GroupStandbyChanged(CpTopology3Group& aGroup)
{
	aGroup.Group().Standby() ? iStandbyCount++ : iStandbyCount--;
	EvaluateStandby();
}

void CpTopology3Room::EvaluateStandby()
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


void CpTopology3Room::GroupSourceIndexChanged(CpTopology3Group& aGroup)
{
	iMutex.Wait();

	if (iCurrentGroup->IsDescendentOf(aGroup)) {
		UpdateCurrentGroup(aGroup.CurrentDescendent());
	}

	iMutex.Signal();
}

void CpTopology3Room::GroupSourceListChanged(CpTopology3Group& /*aGroup*/)
{
	iSourceCount = EvaluateSources();
	iHandler.RoomChanged(*this);
}

void CpTopology3Room::AddRef()
{
    iRefCount++;
}

void CpTopology3Room::RemoveRef()
{
    if (--iRefCount == 0) {
        delete this;
    }
}

TUint CpTopology3Room::SourceCount() const
{
	return (iSourceCount);
}

void CpTopology3Room::SetSourceIndex(TUint aIndex)
{
	iMutex.Wait();

	if (aIndex >= iSourceCount) {
		iMutex.Signal();
		return;
	}

	CpTopology3Source* source = iSourceList[aIndex];

	source->Select();

	CpTopology3Group* group = &source->Owner();

	while (group->HasParent()) {
		TUint index = group->ParentSourceIndex();
		group = &group->Parent();
		group->Source(index).Select();
	}

	iMutex.Signal();
}

void CpTopology3Room::SetStandby(TBool aValue)
{
	iMutex.Wait();

	std::vector<CpTopology3Group*>::iterator it = iGroupList.begin();
	
	while (it != iGroupList.end()) {
		(*it)->Group().SetStandby(aValue);
	}
	
	iMutex.Signal();	
}

const Brx& CpTopology3Room::Name() const
{
    return (iName);
}

TUint CpTopology3Room::EvaluateSources()
{
	iSourceList.clear();

    TUint count = 0;
    
	if (iRootList.size() > 0) {
		std::vector<CpTopology3Group*>::const_iterator it = iRootList.begin();
		while (it != iRootList.end()) {
			count += (*it)->EvaluateSources(iSourceList);
			it++;
		}
	}
    
	return (count);
}


const Brx& CpTopology3Room::SourceName(TUint aIndex) const
{
	ASSERT(aIndex < iSourceCount);
	return (iSourceList[aIndex]->Name());
}

const Brx& CpTopology3Room::SourceType(TUint aIndex) const
{
	ASSERT(aIndex < iSourceCount);
	return (iSourceList[aIndex]->Type());
}

const Brx& CpTopology3Room::SourceGroup(TUint aIndex) const
{
	ASSERT(aIndex < iSourceCount);
	return (iSourceList[aIndex]->Group());
}

CpDevice& CpTopology3Room::SourceDevice(TUint aIndex) const
{
	ASSERT(aIndex < iSourceCount);
	return (iSourceList[aIndex]->Device());
}

const Brx& CpTopology3Room::CurrentSourceName() const
{
	ASSERT(iCurrentGroup);
	CpTopology2Group& group = iCurrentGroup->Group();
	return (group.SourceName(group.SourceIndex()));
}

const Brx& CpTopology3Room::CurrentSourceType() const
{
	ASSERT(iCurrentGroup);
	CpTopology2Group& group = iCurrentGroup->Group();
	return (group.SourceType(group.SourceIndex()));
}

const Brx& CpTopology3Room::CurrentSourceGroup() const
{
	ASSERT(iCurrentGroup);
	CpTopology2Group& group = iCurrentGroup->Group();
    return (group.Name());
}

CpDevice& CpTopology3Room::CurrentSourceDevice() const
{
	ASSERT(iCurrentGroup);
	CpTopology2Group& group = iCurrentGroup->Group();
    return (group.Device());
}

TBool CpTopology3Room::HasVolumeControl() const
{
	return (iVolumeDevice != 0);
}

CpDevice& CpTopology3Room::VolumeDevice() const
{
	ASSERT(iVolumeDevice);
	return (*iVolumeDevice);
}

CpTopology3Room::EStandby CpTopology3Room::Standby() const
{
	return (iStandby);
}

// CpTopology3

CpTopology3::CpTopology3(ICpTopology3Handler& aHandler)
	: iHandler(aHandler)
{
	iTopology2 = new CpTopology2(*this);
}

CpTopology3::CpTopology3(ICpTopology3Handler& aHandler, ICpTopology2Handler** aTestInterface)
    : iHandler(aHandler)
    , iTopology2(0)
{
    *aTestInterface = this;
}

CpTopology3::~CpTopology3()
{
	LOG(kTopology, "CpTopology3::~CpTopology3\n");
	delete (iTopology2);
	LOG(kTopology, "CpTopology3::~CpTopology3 deleted layer 2\n");
	ASSERT(iRoomList.size() == 0);
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
	CpTopology3Room* room = 0;

	std::list<CpTopology3Room*>::iterator it = iRoomList.begin();
	
	while (it != iRoomList.end()) {
		if ((*it)->Name() == aGroup.Room()) {
			room = *it;
			break;
		}
		it++;
	}

	if (room == 0) {
		room = new CpTopology3Room(aGroup.Room(), *this);
	}

	CpTopology3Group* group = new CpTopology3Group(aGroup, *room);

	aGroup.SetUserData(group);

	room->GroupAdded(*group);
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
    
void CpTopology3::RoomAdded(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomAdded ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

	iRoomList.push_back(&aRoom);
		
	iHandler.RoomAdded(aRoom);
}

void CpTopology3::RoomChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomChanged(aRoom);
}

void CpTopology3::RoomRemoved(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomRemoved ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    std::list<CpTopology3Room*>::iterator it = iRoomList.begin();
    
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

void CpTopology3::RoomStandbyChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomStandbyChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

	iHandler.RoomStandbyChanged(aRoom);
}

void CpTopology3::RoomSourceChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomSourceChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

	iHandler.RoomSourceChanged(aRoom);
}

void CpTopology3::RoomVolumeControlChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomVolumeControlChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

	iHandler.RoomVolumeControlChanged(aRoom);
}

