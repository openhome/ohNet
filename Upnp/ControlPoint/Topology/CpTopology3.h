#ifndef HEADER_TOPOLOGY3
#define HEADER_TOPOLOGY3

#include <Standard.h>
#include <ZappTypes.h>
#include <Fifo.h>
#include <Thread.h>

#include <vector>
#include <list>

#include "CpTopology2.h"

namespace Zapp {

class CpTopology3Room;

class ICpTopology3Handler
{
public:
	virtual void RoomAdded(CpTopology3Room& aRoom) = 0;
	virtual void RoomStandbyChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomSourceIndexChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomSourceListChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomVolumeChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomMuteChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomRemoved(CpTopology3Room& aRoom) = 0;
	~ICpTopology3Handler() {}
};

class CpTopology3Source;

class CpTopology3Group : private INonCopyable
{
	friend class CpTopology3Room;
	friend class CpTopology3Source;
	
private:
	CpTopology3Group(CpTopology2Group& aGroup);
	const CpTopology2Group& Group() const;
	TBool IsAttachedTo(CpTopology2Group& aGroup);
	const Brx& Name() const;
	TBool HasParent() const;
	CpTopology3Group& Parent() const;
	TBool Root() const;
	void SetRoot(TBool aValue);
	TUint SourceCount() const;
	
	~CpTopology3Group();
	
private:
	void ClearParent();
	void ClearChildren();
	void SetParent(CpTopology3Group& aGroup, TUint aSourceIndex);
	TBool AddIfIsChild(CpTopology3Group& aGroup);
	void AddChild(CpTopology3Group& aGroup, TUint aSourceIndex);
	void RemoveChild(CpTopology3Group& aGroup, TUint aSourceIndex);
	
private:
	CpTopology2Group& iGroup;
	CpTopology3Group* iParent;
	TUint iParentSourceIndex;
	TBool iRoot;
    std::vector<CpTopology3Source*> iSourceList;
};

class CpTopology3Source
{
	friend class CpTopology3Group;

private:
	CpTopology3Source();
	
	TUint ChildCount() const;
	CpTopology3Group& Child(TUint aIndex) const;
	
	void AddChild(CpTopology3Group& aGroup);
	void RemoveChild(CpTopology3Group& aGroup);
	void ClearChildren();

	~CpTopology3Source();
	
private:
    std::vector<CpTopology3Group*> iChildList;
};

class CpTopology3;

class CpTopology3Room : public ICpTopology2Handler, private INonCopyable
{
	friend class CpTopology3;

	static const TUint kMaxRoomBytes = 20;

private:
    CpTopology3Room(ICpTopology3Handler& aHandler, CpTopology2Group& aGroup);

public:
    void AddRef();
    void RemoveRef();
    TBool Standby() const;
    void SetStandby(TBool aValue);
    const Brx& Room() const;
    TUint SourceCount() const;
    const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
    //CpDevice& SourceDevice(TUint aIndex) const;
    TUint SourceIndex() const;
    void SetSourceIndex(TUint aIndex);
    TBool HasVolumeControl() const;
    TUint Volume() const;
    void SetVolume(TUint aValue) const;
    TBool Mute() const;
    void SetMute(TBool aValue);

    ~CpTopology3Room();

private:
	// ICpTopology2Handler
	virtual void GroupAdded(CpTopology2Group& aGroup);
	virtual void GroupStandbyChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceIndexChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceListChanged(CpTopology2Group& aGroup);
	virtual void GroupVolumeChanged(CpTopology2Group& aGroup);
	virtual void GroupMuteChanged(CpTopology2Group& aGroup);
	virtual void GroupRemoved(CpTopology2Group& aGroup);

	void EvaluateSourceCount();
	void ReportGroups();

private:
	ICpTopology3Handler& iHandler;
	Bws<kMaxRoomBytes> iRoom;
    TBool iActive;
    TUint iSourceCount;
    TUint iRefCount;
    std::vector<CpTopology3Group*> iGroupList;
    std::vector<CpTopology3Group*> iRootList;
};


class CpTopology3 : public ICpTopology2Handler, public ICpTopology3Handler, private INonCopyable
{
public:
	CpTopology3(ICpTopology3Handler& aHandler);
	
    void Refresh();
    
    ~CpTopology3();
    
private:
	// ICpTopology2Handler
	virtual void GroupAdded(CpTopology2Group& aGroup);
	virtual void GroupStandbyChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceIndexChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceListChanged(CpTopology2Group& aGroup);
	virtual void GroupVolumeChanged(CpTopology2Group& aGroup);
	virtual void GroupMuteChanged(CpTopology2Group& aGroup);
	virtual void GroupRemoved(CpTopology2Group& aGroup);

	// ICpTopology3Handler
	virtual void RoomAdded(CpTopology3Room& aRoom);
	virtual void RoomStandbyChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceIndexChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceListChanged(CpTopology3Room& aRoom);
	virtual void RoomVolumeChanged(CpTopology3Room& aRoom);
	virtual void RoomMuteChanged(CpTopology3Room& aRoom);
	virtual void RoomRemoved(CpTopology3Room& aRoom);

private:
	ICpTopology3Handler& iHandler;
	CpTopology2* iTopology2;
    std::list<CpTopology3Room*> iRoomList;
};

} // namespace Zapp

#endif // HEADER_TOPOLOGY3
