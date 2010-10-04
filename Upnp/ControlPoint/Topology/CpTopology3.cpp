#include "CpTopology3.h"

#include <Debug.h>
#include <Parser.h>
#include <Ascii.h>
#include <XmlParser.h>

using namespace Zapp;

// CpTopology3Source

CpTopology3Source::CpTopology3Source()
{
}
	
TUint CpTopology3Source::ChildCount() const
{
	return (iChildList.size());
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
	std::vector<CpTopology3Group*>::iterator it = iChildList.begin();
	
	while (it != iChildList.end()) {
		(*it)->ClearParent();
		it++;
	}
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

	for (TUint i = 0; i < aGroup.SourceCount(); i++) {
		iSourceList.push_back(new CpTopology3Source);
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

const CpTopology2Group& CpTopology3Group::Group() const
{
	return (iGroup);
}

TBool CpTopology3Group::IsAttachedTo(CpTopology2Group& aGroup)
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

TUint CpTopology3Group::SourceCount() const
{
    return iSourceList.size();
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
	if (iParent) {
		iParent->RemoveChild(*this, iParentSourceIndex);
	}

	iParent = &aGroup;
	iParentSourceIndex = aSourceIndex;
	
	iParent->AddChild(*this, iParentSourceIndex);
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
	, iRoom(aGroup.Room())
	, iActive(false)
	, iSourceCount(0)
	, iRefCount(1)
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

void CpTopology3Room::ReportGroups()
{
	std::vector<CpTopology3Group*>::iterator it;
	
    LOG(kTopology, "=== GROUPS ===\n");

	it = iGroupList.begin();

	while (it != iGroupList.end()) {
	    LOG(kTopology, (*it)->Group().Room());
	    LOG(kTopology, ":");
	    LOG(kTopology, (*it)->Group().Name());
	    LOG(kTopology, ":");
	    LOG(kTopology, (*it)->Group().Device().Udn());
	    LOG(kTopology, "\n");
		it++;
	}

    LOG(kTopology, "=== ROOTS  ===\n");

	it = iRootList.begin();

	while (it != iRootList.end()) {
	    LOG(kTopology, (*it)->Group().Room());
	    LOG(kTopology, ":");
	    LOG(kTopology, (*it)->Group().Name());
	    LOG(kTopology, ":");
	    LOG(kTopology, (*it)->Group().Device().Udn());
	    LOG(kTopology, "\n");
		it++;
	}

    LOG(kTopology, "==============\n");
}

void CpTopology3Room::EvaluateSourceCount()
{
	TUint count = 0;
	
	std::vector<CpTopology3Group*>::iterator it = iRootList.begin();
	
	while (it != iRootList.end()) {
		count += (*it)->SourceCount();
		it++;
	}
	
	iSourceCount = count;
	
	if (iActive) {
		iHandler.RoomSourceListChanged(*this);
	}
}

// ICpTopology2Handler
    
void CpTopology3Room::GroupAdded(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3Room::GroupAdded(");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Device().Udn());
    LOG(kTopology, ") in ");
    LOG(kTopology, iRoom);
    LOG(kTopology, "\n");

	CpTopology3Group* group = new CpTopology3Group(aGroup);
	
	// Hook into parent, unless root
	
	std::vector<CpTopology3Group*>::iterator it = iGroupList.begin();
	
	while (it != iGroupList.end()) {
		if ((*it)->AddIfIsChild(*group)) {
			iGroupList.push_back(group);
			EvaluateSourceCount();
			return;
		}
		it++;
	}
	
	group->SetRoot(true);
	iGroupList.push_back(group);
	iRootList.push_back(group);
	EvaluateSourceCount();
}

void CpTopology3Room::GroupRemoved(CpTopology2Group& aGroup)
{
    LOG(kTopology, "CpTopology3Room::GroupRemoved(");
    LOG(kTopology, aGroup.Room());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Name());
    LOG(kTopology, ":");
    LOG(kTopology, aGroup.Device().Udn());
    LOG(kTopology, ") in ");
    LOG(kTopology, iRoom);
    LOG(kTopology, "\n");

	std::vector<CpTopology3Group*>::iterator it = iGroupList.begin();
	
	while (it != iGroupList.end()) {
		if ((*it)->IsAttachedTo(aGroup)) {
			CpTopology3Group* group = (*it);

			iGroupList.erase(it);

			if (group->Root()) {
				it = iRootList.begin();

				TBool found = false;
				
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

					TBool added = false;
										
					std::vector<CpTopology3Group*>::iterator it2 = iGroupList.begin();
					
					while (it2 != iGroupList.end()) {
						if ((*it2)->AddIfIsChild(*(*it))) {
							added = true;
							break;		
						}
						it2++;
					}
					
					if (!added) {
						(*it)->SetRoot(true);
						iRootList.push_back(*it);
					}
				}
				it++;
			}

			EvaluateSourceCount();
			return;
		}
		it++;
	}
	ASSERTS();
}


void CpTopology3Room::GroupStandbyChanged(CpTopology2Group& /*aGroup*/)
{
}

void CpTopology3Room::GroupSourceIndexChanged(CpTopology2Group& /*aGroup*/)
{
}

void CpTopology3Room::GroupSourceListChanged(CpTopology2Group& /*aGroup*/)
{
	EvaluateSourceCount();
}

void CpTopology3Room::GroupVolumeChanged(CpTopology2Group& /*aGroup*/)
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

const Brx& CpTopology3Room::Room() const
{
	return (iRoom);
}

const Brx& CpTopology3Room::SourceName(TUint /*aIndex*/) const
{
	return (Brx::Empty());
}

const Brx& CpTopology3Room::SourceType(TUint /*aIndex*/) const
{
	return (Brx::Empty());
}

/*
CpDevice& CpTopology3Room::SourceDevice(TUint aIndex) const
{
	return (CpDevice());
}
*/

TBool CpTopology3Room::HasVolumeControl() const
{
	return (false);
}

TUint CpTopology3Room::Volume() const
{
	return (0);
}

void CpTopology3Room::SetVolume(TUint /*aValue*/) const
{
}

TBool CpTopology3Room::Mute() const
{
	return (false);
}

void CpTopology3Room::SetMute(TBool /*aValue*/)
{
}

// CpTopology3

CpTopology3::CpTopology3(ICpTopology3Handler& aHandler)
	: iHandler(aHandler)
{
	iTopology2 = new CpTopology2(*this);
}

CpTopology3::~CpTopology3()
{
	delete (iTopology2);
	ASSERT(iRoomList.size() == 0);
}
    
void CpTopology3::Refresh()
{
	iTopology2->Refresh();
}
// ICpTopology2Handler
    
void CpTopology3::GroupAdded(CpTopology2Group& aGroup)
{
	std::list<CpTopology3Room*>::iterator it = iRoomList.begin();
	
	while (it != iRoomList.end()) {
		if ((*it)->Room() == aGroup.Room()) {
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

void CpTopology3::GroupVolumeChanged(CpTopology2Group& aGroup)
{
	((CpTopology3Room*)aGroup.UserData())->GroupVolumeChanged(aGroup);
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
    LOG(kTopology, aRoom.Room());
    LOG(kTopology, "\n");

	iRoomList.push_back(&aRoom);
		
	iHandler.RoomAdded(aRoom);
}

void CpTopology3::RoomStandbyChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomStandbyChanged ");
    LOG(kTopology, aRoom.Room());
    LOG(kTopology, "\n");

	iHandler.RoomStandbyChanged(aRoom);
}

void CpTopology3::RoomSourceIndexChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomSourceIndexChanged ");
    LOG(kTopology, aRoom.Room());
    LOG(kTopology, "\n");

	iHandler.RoomSourceIndexChanged(aRoom);
}

void CpTopology3::RoomSourceListChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomSourceListChanged ");
    LOG(kTopology, aRoom.Room());
    LOG(kTopology, "\n");

	iHandler.RoomSourceListChanged(aRoom);
}

void CpTopology3::RoomVolumeChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomVolumeChanged ");
    LOG(kTopology, aRoom.Room());
    LOG(kTopology, "\n");

	iHandler.RoomVolumeChanged(aRoom);
}

void CpTopology3::RoomMuteChanged(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomMuteChanged ");
    LOG(kTopology, aRoom.Room());
    LOG(kTopology, "\n");

	iHandler.RoomMuteChanged(aRoom);
}

void CpTopology3::RoomRemoved(CpTopology3Room& aRoom)
{
    LOG(kTopology, "CpTopology3::RoomRemoved ");
    LOG(kTopology, aRoom.Room());
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

