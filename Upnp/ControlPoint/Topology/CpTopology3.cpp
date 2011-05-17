#include "CpTopology3.h"

#include <Debug.h>
#include <Parser.h>
#include <Ascii.h>
#include <XmlParser.h>

using namespace Zapp;

// CpTopology3Source

CpTopology3Source::CpTopology3Source(CpTopology2Group& aGroup, TUint aIndex)
    : iGroup(aGroup)
    , iIndex(aIndex)
{
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

TUint CpTopology3Source::Evaluate()
{
    iSourceCount = 0;
    
    TUint children = iChildList.size();
    
    if (children == 0) {
        if (iGroup.SourceVisible(iIndex)) {
            iSourceCount = 1;
        }
    }
    else {
        std::vector<CpTopology3Group*>::iterator it = iChildList.begin();
        
        while (it != iChildList.end()) {
            iSourceCount += (*it)->Evaluate();
            it++;
        }
    }

    return (iSourceCount);
}

TUint CpTopology3Source::SourceCount() const
{
    return (iSourceCount);
}

const Brx& CpTopology3Source::SourceName(TUint aIndex) const
{
    TUint index = aIndex;
    
    if (iChildList.size() == 0) {
        return (iGroup.SourceName(iIndex));
    }
    else {
        std::vector<CpTopology3Group*>::const_iterator it = iChildList.begin();
        
        while (it != iChildList.end()) {
            TUint count = (*it)->SourceCount();
            if (count > index) {
                return ((*it)->SourceName(index));
            }
            index -= count;
            it++;
        }
    }
    
    ASSERTS();
    return (Brx::Empty());
}

const Brx& CpTopology3Source::SourceType(TUint aIndex) const
{
    TUint index = aIndex;
    
    if (iChildList.size() == 0) {
        return (iGroup.SourceType(iIndex));
    }
    else {
        std::vector<CpTopology3Group*>::const_iterator it = iChildList.begin();
        
        while (it != iChildList.end()) {
            TUint count = (*it)->SourceCount();
            if (count > index) {
                return ((*it)->SourceType(index));
            }
            index -= count;
            it++;
        }
    }
    
    ASSERTS();
    return (Brx::Empty());
}

CpDevice& CpTopology3Source::SourceDevice(TUint aIndex) const
{
    TUint index = aIndex;
    
    if (iChildList.size() == 0) {
        return (iGroup.Device());
    }
    else {
        std::vector<CpTopology3Group*>::const_iterator it = iChildList.begin();
        
        while (it != iChildList.end()) {
            TUint count = (*it)->SourceCount();
            if (count > index) {
                return ((*it)->SourceDevice(index));
            }
            index -= count;
            it++;
        }
    }
    
    ASSERTS();

    return (*(CpDevice*)0);
}

CpTopology3Source::~CpTopology3Source()
{
	ASSERT(iChildList.size() == 0);
}
	
// CpTopology3Group

CpTopology3Group::CpTopology3Group(CpTopology2Group& aGroup)
	: iGroup(aGroup)
	, iParent(0)
	, iParentSourceIndex(0)
	, iRoot(false)
{
	iGroup.AddRef();

	for (TUint i = 0; i < iGroup.SourceCount(); i++) {
		iSourceList.push_back(new CpTopology3Source(iGroup, i));
	}
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

CpTopology2Group& CpTopology3Group::Group() const
{
	return (iGroup);
}

TBool CpTopology3Group::IsAttachedTo(CpTopology2Group& aGroup) const
{
	return (&iGroup == &aGroup);
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

TBool CpTopology3Group::Root() const
{
	return (iRoot);
}

void CpTopology3Group::SetRoot(TBool aValue)
{
	iRoot = aValue;
}

TUint CpTopology3Group::Evaluate()
{
    iSourceCount = 0;

    std::vector<CpTopology3Source*>::iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        iSourceCount += (*it)->Evaluate();
        it++;
    }

    return (iSourceCount);
}

TUint CpTopology3Group::SourceCount() const
{
    return (iSourceCount);
}

const Brx& CpTopology3Group::SourceName(TUint aIndex) const
{
    TUint index = aIndex;
    
    std::vector<CpTopology3Source*>::const_iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        TUint count = (*it)->SourceCount();
        if (count > index) {
            return ((*it)->SourceName(index));
        }
        index -= count;
        it++;
    }
    
    ASSERTS();
    return (Brx::Empty());
}

const Brx& CpTopology3Group::SourceType(TUint aIndex) const
{
    TUint index = aIndex;
    
    std::vector<CpTopology3Source*>::const_iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        TUint count = (*it)->SourceCount();
        if (count > index) {
            return ((*it)->SourceType(index));
        }
        index -= count;
        it++;
    }
    
    ASSERTS();

    return (Brx::Empty());
}

CpDevice& CpTopology3Group::SourceDevice(TUint aIndex) const
{
    TUint index = aIndex;
    
    std::vector<CpTopology3Source*>::const_iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        TUint count = (*it)->SourceCount();
        if (count > index) {
            return ((*it)->SourceDevice(index));
        }
        index -= count;
        it++;
    }
    
    ASSERTS();

    return (*(CpDevice*)0);
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

// CpTopology3Room

CpTopology3Room::CpTopology3Room(ICpTopology3Handler& aHandler, CpTopology2Group& aGroup)
	: iHandler(aHandler)
	, iName(aGroup.Room())
	, iActive(false)
	, iSourceCount(0)
	, iRefCount(1)
	, iUserData(0)
{
	GroupAdded(aGroup);
	iHandler.RoomAdded(*this);
	iActive = true;
}

CpTopology3Room::~CpTopology3Room()
{
	ASSERT(iGroupList.size() == 0);
	iHandler.RoomRemoved(*this);
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
    
void CpTopology3Room::GroupAdded(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3Room::GroupAdded(");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, ") in ");
    LOG(kTopology, iName);
    LOG(kTopology, "\n");

	CpTopology3Group* group = new CpTopology3Group(aGroup);
	
	// Check if this has an existing parent
	
	std::vector<CpTopology3Group*>::iterator it = iGroupList.begin();
	
	while (it != iGroupList.end()) {
		if ((*it)->AddIfIsChild(*group)) {
			iGroupList.push_back(group);
			Evaluate();
			return;
		}
		it++;
	}
	
	// Check if this is the parent of an existing root
	
    it = iRootList.begin();
    
    while (it != iRootList.end()) {
        if (group->AddIfIsChild(*(*it))) {
            (*it)->SetRoot(false);
            iRootList.erase(it);
            break;
        }
        it++;
    }
    
    // so, this is a root
    
	group->SetRoot(true);
	iGroupList.push_back(group);
	iRootList.push_back(group);
	Evaluate();
}

void CpTopology3Room::GroupRemoved(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3Room::GroupRemoved(");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, ") in ");
    LOG(kTopology, iName);
    LOG(kTopology, "\n");

	std::vector<CpTopology3Group*>::iterator it = iGroupList.begin();
	
    CpTopology3Group* group = 0;
    
	while (it != iGroupList.end()) {
		if ((*it)->IsAttachedTo(aGroup)) {
			group = (*it);
			iGroupList.erase(it);
			break;
		}
		it++;
	}
	
	ASSERT(group != 0);

	if (group->Root()) {
        TBool found = false;
        
		it = iRootList.begin();

		while (it != iRootList.end()) {
			if ((*it)->IsAttachedTo(aGroup)) {
				found = true;
				iRootList.erase(it);
				break;
			}
			it++;
		}
		
		ASSERT(found);
	}
	else {
		group->ClearParent();
	}
			
	group->ClearChildren();
	
	delete (group);
			
	// check for last group in this room
	
	if (iGroupList.size() == 0) {
		RemoveRef();
		return;
	}
			 
	// now check orphaned groups
	// remap them or change them to root groups
	
	it = iGroupList.begin();
	
	while (it != iGroupList.end()) {
		if (!(*it)->Root() && !(*it)->HasParent()) { // indicates this group has been orphaned
            (*it)->SetRoot(true);
            iRootList.push_back(*it);
		}
		it++;
	}

	Evaluate();
}


void CpTopology3Room::GroupStandbyChanged(CpTopology2Group& /*aGroup*/)
{
}

void CpTopology3Room::GroupSourceIndexChanged(CpTopology2Group& /*aGroup*/)
{
}

void CpTopology3Room::GroupSourceListChanged(CpTopology2Group& /*aGroup*/)
{
	Evaluate();
}

void CpTopology3Room::GroupVolumeLimitChanged(CpTopology2Group& /*aGroup*/)
{
}

void CpTopology3Room::GroupVolumeChanged(CpTopology2Group& /*aGroup*/)
{
}

void CpTopology3Room::GroupBalanceChanged(CpTopology2Group& /*aGroup*/)
{
}

void CpTopology3Room::GroupFadeChanged(CpTopology2Group& /*aGroup*/)
{
}

void CpTopology3Room::GroupMuteChanged(CpTopology2Group& /*aGroup*/)
{
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

TUint CpTopology3Room::SourceIndex() const
{
	return (0);
}

TBool CpTopology3Room::Standby() const
{
	return (false);
}

void CpTopology3Room::SetSourceIndex(TUint /*aIndex*/)
{
}

void CpTopology3Room::SetStandby(TBool /*aValue*/)
{
}

const Brx& CpTopology3Room::Name() const
{
	return (iName);
}

void CpTopology3Room::Evaluate()
{
    ASSERT(iRootList.size() > 0);
    
    TUint count = 0;
    
    std::vector<CpTopology3Group*>::const_iterator it = iRootList.begin();
    
    iRoot = (*it);
    
    while (it != iRootList.end()) {
        count += (*it)->Evaluate();
        it++;
    }
    
    iSourceCount = count;
    
    if (iActive) {
        iHandler.RoomChanged(*this);
    }
}

const Brx& CpTopology3Room::SourceName(TUint aIndex) const
{
    TUint index = aIndex;
    
    std::vector<CpTopology3Group*>::const_iterator it = iRootList.begin();
    
    while (it != iRootList.end()) {
        TUint count = (*it)->SourceCount();
        if (count > index) {
            return ((*it)->SourceName(index));
        }
        index -= count;
        it++;
    }
    
	ASSERTS();

    return (Brx::Empty());
}

const Brx& CpTopology3Room::SourceType(TUint aIndex) const
{
    TUint index = aIndex;
    
    std::vector<CpTopology3Group*>::const_iterator it = iRootList.begin();
    
    while (it != iRootList.end()) {
        TUint count = (*it)->SourceCount();
        if (count > index) {
            return ((*it)->SourceType(index));
        }
        index -= count;
        it++;
    }
    
    ASSERTS();
    return (Brx::Empty());
}

CpDevice& CpTopology3Room::SourceDevice(TUint aIndex) const
{
    TUint index = aIndex;
    
    std::vector<CpTopology3Group*>::const_iterator it = iRootList.begin();
    
    while (it != iRootList.end()) {
        TUint count = (*it)->SourceCount();
        if (count > index) {
            return ((*it)->SourceDevice(index));
        }
        index -= count;
        it++;
    }
    
    ASSERTS();
    
    return (*(CpDevice*)0);
}

TBool CpTopology3Room::HasVolumeControl() const
{
    return (iRoot->Group().HasVolumeControl());
}

TUint CpTopology3Room::VolumeMax() const
{
    return (iRoot->Group().VolumeMax());
}

TUint CpTopology3Room::VolumeUnity() const
{
    return (iRoot->Group().VolumeUnity());
}

TUint CpTopology3Room::VolumeSteps() const
{
    return (iRoot->Group().VolumeSteps());
}

TUint CpTopology3Room::VolumeMilliDbPerStep() const
{
    return (iRoot->Group().VolumeMilliDbPerStep());
}

TUint CpTopology3Room::FadeMax() const
{
    return (iRoot->Group().FadeMax());
}

TUint CpTopology3Room::BalanceMax() const
{
    return (iRoot->Group().BalanceMax());
}

TUint CpTopology3Room::VolumeLimit() const
{
    return (iRoot->Group().VolumeLimit());
}

TUint CpTopology3Room::Volume() const
{
    return (iRoot->Group().Volume());
}

void CpTopology3Room::SetVolume(TUint aValue)
{
    iRoot->Group().SetVolume(aValue);
}

void CpTopology3Room::VolumeInc()
{
    iRoot->Group().VolumeInc();
}

void CpTopology3Room::VolumeDec()
{
    iRoot->Group().VolumeDec();
}

TInt CpTopology3Room::Balance() const
{
    return (iRoot->Group().Balance());
}

void CpTopology3Room::SetBalance(TInt aValue)
{
    iRoot->Group().SetBalance(aValue);
}

void CpTopology3Room::BalanceInc()
{
    iRoot->Group().BalanceInc();
}

void CpTopology3Room::BalanceDec()
{
    iRoot->Group().BalanceDec();
}

TInt CpTopology3Room::Fade() const
{
    return (iRoot->Group().Fade());
}

void CpTopology3Room::SetFade(TInt aValue)
{
    iRoot->Group().SetFade(aValue);
}

void CpTopology3Room::FadeInc()
{
    iRoot->Group().FadeInc();
}

void CpTopology3Room::FadeDec()
{
    iRoot->Group().FadeDec();
}

TBool CpTopology3Room::Mute() const
{
    return (iRoot->Group().Mute());
}

void CpTopology3Room::SetMute(TBool aValue)
{
    iRoot->Group().SetMute(aValue);
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
	delete (iTopology2);
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
	std::list<CpTopology3Room*>::iterator it = iRoomList.begin();
	
	while (it != iRoomList.end()) {
		if ((*it)->Name() == aGroup.Room()) {
			aGroup.SetUserData(*it);
			(*it)->GroupAdded(aGroup);
			return;
		}
		it++;
	}

	CpTopology3Room* room = new CpTopology3Room(*this, aGroup);
	
	aGroup.SetUserData(room);
}

void CpTopology3::GroupStandbyChanged(CpTopology2Group& aGroup)
{
	((CpTopology3Room*)aGroup.UserData())->GroupStandbyChanged(aGroup);
}

void CpTopology3::GroupSourceIndexChanged(CpTopology2Group& aGroup)
{
	((CpTopology3Room*)aGroup.UserData())->GroupSourceIndexChanged(aGroup);
}

void CpTopology3::GroupSourceListChanged(CpTopology2Group& aGroup)
{
	((CpTopology3Room*)aGroup.UserData())->GroupSourceListChanged(aGroup);
}

void CpTopology3::GroupVolumeLimitChanged(CpTopology2Group& aGroup)
{
    ((CpTopology3Room*)aGroup.UserData())->GroupVolumeLimitChanged(aGroup);
}

void CpTopology3::GroupVolumeChanged(CpTopology2Group& aGroup)
{
	((CpTopology3Room*)aGroup.UserData())->GroupVolumeChanged(aGroup);
}

void CpTopology3::GroupBalanceChanged(CpTopology2Group& aGroup)
{
    ((CpTopology3Room*)aGroup.UserData())->GroupBalanceChanged(aGroup);
}

void CpTopology3::GroupFadeChanged(CpTopology2Group& aGroup)
{
    ((CpTopology3Room*)aGroup.UserData())->GroupFadeChanged(aGroup);
}

void CpTopology3::GroupMuteChanged(CpTopology2Group& aGroup)
{
	((CpTopology3Room*)aGroup.UserData())->GroupMuteChanged(aGroup);
}

void CpTopology3::GroupRemoved(CpTopology2Group& aGroup)
{
	((CpTopology3Room*)aGroup.UserData())->GroupRemoved(aGroup);
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
    LOG(kTopology, "CpTopology3::RoomSourceListChanged ");
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

void CpTopology3::RoomSourceIndexChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomSourceIndexChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

	iHandler.RoomSourceIndexChanged(aRoom);
}

void CpTopology3::RoomVolumeLimitChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomVolumeLimitChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomVolumeLimitChanged(aRoom);
}

void CpTopology3::RoomVolumeChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomVolumeChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

	iHandler.RoomVolumeChanged(aRoom);
}

void CpTopology3::RoomBalanceChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomBalanceChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomBalanceChanged(aRoom);
}

void CpTopology3::RoomFadeChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomFadeChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

    iHandler.RoomFadeChanged(aRoom);
}

void CpTopology3::RoomMuteChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomMuteChanged ");
    LOG(kTopology, aRoom.Name());
    LOG(kTopology, "\n");

	iHandler.RoomMuteChanged(aRoom);
}


