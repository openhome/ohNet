#include "CpTopology3.h"

#include <Debug.h>
#include <Parser.h>
#include <Ascii.h>
#include <XmlParser.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpTopology3Source

CpTopology3Source::CpTopology3Source(CpTopology2Group& aGroup, TUint aIndex)
    : iGroup(aGroup)
    , iIndex(aIndex)
{
}

const Brx& CpTopology3Source::Name() const
{
	return (iGroup.SourceName(iIndex));
}

const Brx& CpTopology3Source::Type() const
{
	return (iGroup.SourceType(iIndex));
}

const Brx& CpTopology3Source::Group() const
{
	return (iGroup.Name());
}

CpDevice& CpTopology3Source::Device() const
{
	return (iGroup.Device());
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

TUint CpTopology3Source::EvaluateSourceCount()
{
    iSourceCount = 0;
    
    TUint children = (TUint)iChildList.size();
    
    if (children == 0) {
        if (iGroup.SourceVisible(iIndex)) {
            iSourceCount = 1;
        }
    }
    else {
        std::vector<CpTopology3Group*>::iterator it = iChildList.begin();
        
        while (it != iChildList.end()) {
            iSourceCount += (*it)->EvaluateSourceCount();
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

const Brx& CpTopology3Source::SourceGroup(TUint aIndex) const
{
    TUint index = aIndex;
    
    if (iChildList.size() == 0) {
        return (iGroup.Name());
    }
    else {
        std::vector<CpTopology3Group*>::const_iterator it = iChildList.begin();
        
        while (it != iChildList.end()) {
            TUint count = (*it)->SourceCount();
            if (count > index) {
                return ((*it)->SourceGroup(index));
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

CpTopology3Group::CpTopology3Group(CpTopology2Group& aGroup, CpTopology3Room& aRoom)
	: iGroup(aGroup)
	, iRoom(aRoom)
	, iParent(0)
	, iParentSourceIndex(0)
	, iRoot(false)
{
	iGroup.AddRef();

	for (TUint i = 0; i < iGroup.SourceCount(); i++) {
		iSourceList.push_back(new CpTopology3Source(iGroup, i));
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

TBool CpTopology3Group::Root() const
{
	return (iRoot);
}

void CpTopology3Group::SetRoot(TBool aValue)
{
	iRoot = aValue;
}

TUint CpTopology3Group::EvaluateSourceCount()
{
    iSourceCount = 0;

    std::vector<CpTopology3Source*>::iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        iSourceCount += (*it)->EvaluateSourceCount();
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

CpTopology3Source& CpTopology3Group::Source(TUint aIndex) const
{
	ASSERT(aIndex < iSourceList.size());
	return (*iSourceList[aIndex]);
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

const Brx& CpTopology3Group::SourceGroup(TUint aIndex) const
{
    TUint index = aIndex;
    
    std::vector<CpTopology3Source*>::const_iterator it = iSourceList.begin();
    
    while (it != iSourceList.end()) {
        TUint count = (*it)->SourceCount();
        if (count > index) {
            return ((*it)->SourceGroup(index));
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

void CpTopology3Group::GroupVolumeLimitChanged()
{
    LOG(kTopology, "CpTopology3Group::GroupVolumeLimitChanged\n");
	iRoom.GroupVolumeLimitChanged(*this);
}

void CpTopology3Group::GroupVolumeChanged()
{
    LOG(kTopology, "CpTopology3Group::GroupVolumeChanged\n");
	iRoom.GroupVolumeChanged(*this);
}

void CpTopology3Group::GroupBalanceChanged()
{
    LOG(kTopology, "CpTopology3Group::GroupBalanceChanged\n");
	iRoom.GroupBalanceChanged(*this);
}

void CpTopology3Group::GroupFadeChanged()
{
    LOG(kTopology, "CpTopology3Group::GroupFadeChanged\n");
	iRoom.GroupFadeChanged(*this);
}

void CpTopology3Group::GroupMuteChanged()
{
    LOG(kTopology, "CpTopology3Group::GroupMuteChanged\n");
	iRoom.GroupMuteChanged(*this);
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
	, iRefCount(1)
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

	// Check if this is the first group

	if (iCurrentGroup == 0) {
		aGroup.SetRoot(true);
		iGroupList.push_back(&aGroup);
		iRootList.push_back(&aGroup);
		iCurrentGroup = &aGroup;
		iSourceCount = EvaluateSourceCount();
		iHandler.RoomAdded(*this);
		return;
	}
	std::vector<CpTopology3Group*>::iterator it;

	// Check if this has an existing parent
	
	it = iGroupList.begin();
	
	while (it != iGroupList.end()) {
		if ((*it)->AddIfIsChild(aGroup)) {
			if (aGroup.IsCurrentDescendentOf(*iCurrentGroup)) {
				iCurrentGroup = &aGroup;
				iHandler.RoomSourceChanged(*this);
			}
			iGroupList.push_back(&aGroup);
			iSourceCount = EvaluateSourceCount();
			iHandler.RoomChanged(*this);
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
			group->SetRoot(false);
			if (group == iCurrentGroup) {
				if (!group->IsCurrentDescendentOf(aGroup)) {
					iCurrentGroup = &aGroup;
					iHandler.RoomSourceChanged(*this);
				}
			}
			break;
		}
		it++;
	}
    
	aGroup.SetRoot(true);
	iGroupList.push_back(&aGroup);
	iRootList.push_back(&aGroup);
	iSourceCount = EvaluateSourceCount();
	iHandler.RoomChanged(*this);
}

void CpTopology3Room::GroupRemoved(CpTopology3Group& aGroup)
{
    LOG(kTopology, "CpTopology3Room::GroupRemoved(");
    LOG(kTopology, iName);
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, ")\n");

	CpTopology3Group* candidate = 0;

	if (aGroup.HasParent()) {
		candidate = &aGroup.Parent();
	}

	std::vector<CpTopology3Group*>::iterator it = iGroupList.begin();
	
	while (it != iGroupList.end()) {
		if (*it == &aGroup) {
			iGroupList.erase(it);
			break;
		}
		it++;
	}
	
	if (aGroup.Root()) {
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
		if (!(*it)->Root() && !(*it)->HasParent()) { // indicates this group has been orphaned
            (*it)->SetRoot(true);
            iRootList.push_back(*it);
		}
		it++;
	}

	iSourceCount = EvaluateSourceCount();

	// check for last group in this room
	
	if (iGroupList.size() == 0) {
		iHandler.RoomRemoved(*this);
		RemoveRef();
		return;
	}

	// if this is the current group, assign a new one

	if (iCurrentGroup == &aGroup) {
		if (candidate == 0) {
			candidate = *iRootList.begin();
		}
		iCurrentGroup = &candidate->CurrentDescendent();
		iHandler.RoomSourceChanged(*this);
	}

	iHandler.RoomChanged(*this);
}


void CpTopology3Room::GroupStandbyChanged(CpTopology3Group& /*aGroup*/)
{
	iHandler.RoomStandbyChanged(*this);
}

void CpTopology3Room::GroupSourceIndexChanged(CpTopology3Group& aGroup)
{
	if (iCurrentGroup == &aGroup) {
		iHandler.RoomSourceChanged(*this);
	}
}

void CpTopology3Room::GroupSourceListChanged(CpTopology3Group& /*aGroup*/)
{
	iSourceCount = EvaluateSourceCount();
	iHandler.RoomChanged(*this);
}

void CpTopology3Room::GroupVolumeLimitChanged(CpTopology3Group& /*aGroup*/)
{
	iHandler.RoomVolumeLimitChanged(*this);
}

void CpTopology3Room::GroupVolumeChanged(CpTopology3Group& /*aGroup*/)
{
	iHandler.RoomVolumeChanged(*this);
}

void CpTopology3Room::GroupBalanceChanged(CpTopology3Group& /*aGroup*/)
{
	iHandler.RoomBalanceChanged(*this);
}

void CpTopology3Room::GroupFadeChanged(CpTopology3Group& /*aGroup*/)
{
	iHandler.RoomFadeChanged(*this);
}

void CpTopology3Room::GroupMuteChanged(CpTopology3Group& /*aGroup*/)
{
	iHandler.RoomMuteChanged(*this);
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

TUint CpTopology3Room::EvaluateSourceCount()
{
    TUint count = 0;
    
	if (iRootList.size() > 0) {
		std::vector<CpTopology3Group*>::const_iterator it = iRootList.begin();
		while (it != iRootList.end()) {
			count += (*it)->EvaluateSourceCount();
			it++;
		}
	}
    
	return (count);
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

const Brx& CpTopology3Room::SourceGroup(TUint aIndex) const
{
    TUint index = aIndex;
    
    std::vector<CpTopology3Group*>::const_iterator it = iRootList.begin();
    
    while (it != iRootList.end()) {
        TUint count = (*it)->SourceCount();
        if (count > index) {
            return ((*it)->SourceGroup(index));
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

const Brx& CpTopology3Room::CurrentSourceName() const
{
	ASSERT(iCurrentGroup)
	if (iCurrentGroup != 0) {
		CpTopology2Group group = iCurrentGroup->Group();
		TUint index = group.SourceIndex();
	    return (group.SourceName(index));
	}

	return (Brx::Empty());
}

const Brx& CpTopology3Room::CurrentSourceType() const
{
	if (iCurrentGroup != 0) {
		CpTopology2Group group = iCurrentGroup->Group();
		TUint index = group.SourceIndex();
	    return (group.SourceType(index));
	}

	return (Brx::Empty());
}

const Brx& CpTopology3Room::CurrentSourceGroup() const
{
	if (iCurrentGroup != 0) {
	    return (iCurrentGroup->Group().Name());
	}

	return (Brx::Empty());
}

CpDevice& CpTopology3Room::CurrentSourceDevice() const
{
	if (iCurrentGroup != 0) {
	    return (iCurrentGroup->Group().Device());
	}

	ASSERTS();

	return (*(CpDevice*)0);
}

TBool CpTopology3Room::HasVolumeControl() const
{
    return (iCurrentGroup->Group().HasVolumeControl());
}

TUint CpTopology3Room::VolumeMax() const
{
    return (iCurrentGroup->Group().VolumeMax());
}

TUint CpTopology3Room::VolumeUnity() const
{
    return (iCurrentGroup->Group().VolumeUnity());
}

TUint CpTopology3Room::VolumeSteps() const
{
    return (iCurrentGroup->Group().VolumeSteps());
}

TUint CpTopology3Room::VolumeMilliDbPerStep() const
{
    return (iCurrentGroup->Group().VolumeMilliDbPerStep());
}

TUint CpTopology3Room::FadeMax() const
{
    return (iCurrentGroup->Group().FadeMax());
}

TUint CpTopology3Room::BalanceMax() const
{
    return (iCurrentGroup->Group().BalanceMax());
}

TUint CpTopology3Room::VolumeLimit() const
{
    return (iCurrentGroup->Group().VolumeLimit());
}

TUint CpTopology3Room::Volume() const
{
    return (iCurrentGroup->Group().Volume());
}

void CpTopology3Room::SetVolume(TUint aValue)
{
    iCurrentGroup->Group().SetVolume(aValue);
}

void CpTopology3Room::VolumeInc()
{
    iCurrentGroup->Group().VolumeInc();
}

void CpTopology3Room::VolumeDec()
{
    iCurrentGroup->Group().VolumeDec();
}

TInt CpTopology3Room::Balance() const
{
    return (iCurrentGroup->Group().Balance());
}

void CpTopology3Room::SetBalance(TInt aValue)
{
    iCurrentGroup->Group().SetBalance(aValue);
}

void CpTopology3Room::BalanceInc()
{
    iCurrentGroup->Group().BalanceInc();
}

void CpTopology3Room::BalanceDec()
{
    iCurrentGroup->Group().BalanceDec();
}

TInt CpTopology3Room::Fade() const
{
    return (iCurrentGroup->Group().Fade());
}

void CpTopology3Room::SetFade(TInt aValue)
{
    iCurrentGroup->Group().SetFade(aValue);
}

void CpTopology3Room::FadeInc()
{
    iCurrentGroup->Group().FadeInc();
}

void CpTopology3Room::FadeDec()
{
    iCurrentGroup->Group().FadeDec();
}

TBool CpTopology3Room::Mute() const
{
    return (iCurrentGroup->Group().Mute());
}

void CpTopology3Room::SetMute(TBool aValue)
{
    iCurrentGroup->Group().SetMute(aValue);
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

void CpTopology3::GroupVolumeLimitChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3::GroupVolumeLimitChanged\n");
    ((CpTopology3Group*)aGroup.UserData())->GroupVolumeLimitChanged();
}

void CpTopology3::GroupVolumeChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3::GroupVolumeChanged\n");
	((CpTopology3Group*)aGroup.UserData())->GroupVolumeChanged();
}

void CpTopology3::GroupBalanceChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3::GroupBalanceChanged\n");
    ((CpTopology3Group*)aGroup.UserData())->GroupBalanceChanged();
}

void CpTopology3::GroupFadeChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3::GroupFadeChanged\n");
    ((CpTopology3Group*)aGroup.UserData())->GroupFadeChanged();
}

void CpTopology3::GroupMuteChanged(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3::GroupMuteChanged\n");
	((CpTopology3Group*)aGroup.UserData())->GroupMuteChanged();
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

