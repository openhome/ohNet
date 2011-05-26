#ifndef HEADER_TOPOLOGY3
#define HEADER_TOPOLOGY3

#include <Standard.h>
#include <OhNetTypes.h>
#include <Fifo.h>
#include <Thread.h>

#include <vector>
#include <list>

#include "CpTopology2.h"

namespace OpenHome {
namespace Net {

class CpTopology3Room;

class ICpTopology3Handler
{
public:
	virtual void RoomAdded(CpTopology3Room& aRoom) = 0;
    virtual void RoomChanged(CpTopology3Room& aRoom) = 0;
    virtual void RoomRemoved(CpTopology3Room& aRoom) = 0;
	virtual void RoomStandbyChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomSourceChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomVolumeControlChanged(CpTopology3Room& aRoom) = 0;
	~ICpTopology3Handler() {}
};

class CpTopology3Source;

class CpTopology3Room;

class CpTopology3Group : private INonCopyable
{
public:
	CpTopology3Group(CpTopology2Group& aGroup, CpTopology3Room& aRoom);

	CpTopology2Group& Group() const;
	CpTopology3Room& Room() const;
	const Brx& Name() const;
	TUint SourceCount() const;

	TBool HasParent() const;
	CpTopology3Group& Parent() const;
	TUint ParentSourceIndex() const;

	TBool IsRoot() const;
	void SetIsRoot(TBool aValue);
	TUint EvaluateSources(std::vector<CpTopology3Source*>& aVector);
	TBool IsDescendentOf(CpTopology3Group& aGroup) const;
	TBool IsCurrentDescendentOf(CpTopology3Group& aGroup) const;
	CpTopology3Group& Root();
	CpTopology3Group& CurrentDescendent();
	CpTopology3Source& Source(TUint aIndex) const;

	void GroupStandbyChanged();
	void GroupSourceIndexChanged();
	void GroupSourceListChanged();
	void GroupRemoved();

	void ClearParent();
	void ClearChildren();
	void SetParent(CpTopology3Group& aGroup, TUint aSourceIndex);
	TBool AddIfIsChild(CpTopology3Group& aGroup);
	void AddChild(CpTopology3Group& aGroup, TUint aSourceIndex);
	void RemoveChild(CpTopology3Group& aGroup, TUint aSourceIndex);

	~CpTopology3Group();

private:
	CpTopology2Group& iGroup;
	CpTopology3Room& iRoom;
	CpTopology3Group* iParent;
	TUint iParentSourceIndex;
	TBool iIsRoot;
    std::vector<CpTopology3Source*> iSourceList;
    TUint iSourceCount;
};

class CpTopology3Source : private INonCopyable
{
public:
	CpTopology3Source(CpTopology3Group& aGroup, TUint aIndex);

	const Brx& Name() const;
    const Brx& Type() const;
    const Brx& Group() const;
    CpDevice& Device() const;

	void Select();

	CpTopology3Group& Owner() const;

	TUint ChildCount() const;
	CpTopology3Group& Child(TUint aIndex) const;
	
	void AddChild(CpTopology3Group& aGroup);
	void RemoveChild(CpTopology3Group& aGroup);
	void ClearChildren();

    TUint EvaluateSources(std::vector<CpTopology3Source*>& aVector);
    TUint SourceCount() const;

	~CpTopology3Source();
	
private:
    CpTopology3Group& iGroup;
    TUint iIndex;
    std::vector<CpTopology3Group*> iChildList;
    TUint iSourceCount;
};

class CpTopology3;

class CpTopology3Room : private INonCopyable
{
	static const TUint kMaxNameBytes = 20;

public:
	enum EStandby {
		eOn,
		eMixed,
		eOff
	};

public:
    CpTopology3Room(const Brx& aName, ICpTopology3Handler& aHandler);
    ~CpTopology3Room();

	// functions which must be called from ICpTopology3Handler callback thread

    void AddRef();
    void RemoveRef();
    const Brx& Name() const;
    TUint SourceCount() const;
    const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
    const Brx& SourceGroup(TUint aIndex) const;
    CpDevice& SourceDevice(TUint aIndex) const;
    const Brx& CurrentSourceName() const;
    const Brx& CurrentSourceType() const;
    const Brx& CurrentSourceGroup() const;
    CpDevice& CurrentSourceDevice() const;
    TBool HasVolumeControl() const;
	CpDevice& VolumeDevice() const;
	EStandby Standby() const;
    void SetUserData(void* aValue);
    void* UserData() const;

	// functions which must not be called from ICpTopology3Handler callback thread

    void SetStandby(TBool aValue);
    void SetSourceIndex(TUint aIndex);

	// private calls from CpTopology3Group

	void GroupAdded(CpTopology3Group& aGroup);
	void GroupStandbyChanged(CpTopology3Group& aGroup);
	void GroupSourceIndexChanged(CpTopology3Group& aGroup);
	void GroupSourceListChanged(CpTopology3Group& aGroup);
	void GroupRemoved(CpTopology3Group& aGroup);

private:
	void UpdateCurrentGroup(CpTopology3Group& aGroup);
	TUint EvaluateSources();
	void EvaluateStandby();
	void ReportGroups();

private:
	Bws<kMaxNameBytes> iName;
	ICpTopology3Handler& iHandler;
    std::vector<CpTopology3Group*> iGroupList;
    std::vector<CpTopology3Group*> iRootList;
    std::vector<CpTopology3Source*> iSourceList;
    CpTopology3Group* iCurrentGroup;
    TBool iActive;
	mutable Mutex iMutex;
    TUint iSourceCount;
	TUint iStandbyCount;
	EStandby iStandby;
    TUint iRefCount;
	CpDevice* iVolumeDevice;
    void* iUserData;
};


class CpTopology3 : public ICpTopology2Handler, public ICpTopology3Handler, private INonCopyable
{
public:
	CpTopology3(ICpTopology3Handler& aHandler);
    CpTopology3(ICpTopology3Handler& aHandler, ICpTopology2Handler** aTestInterface);
    void Refresh();
    virtual ~CpTopology3();
    
private:
	// ICpTopology2Handler
	virtual void GroupAdded(CpTopology2Group& aGroup);
	virtual void GroupStandbyChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceIndexChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceListChanged(CpTopology2Group& aGroup);
	virtual void GroupRemoved(CpTopology2Group& aGroup);

	// ICpTopology3Handler
	virtual void RoomAdded(CpTopology3Room& aRoom);
    virtual void RoomChanged(CpTopology3Room& aRoom);
    virtual void RoomRemoved(CpTopology3Room& aRoom);
	virtual void RoomStandbyChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceChanged(CpTopology3Room& aRoom);
	virtual void RoomVolumeControlChanged(CpTopology3Room& aRoom);

private:
	ICpTopology3Handler& iHandler;
	CpTopology2* iTopology2;
    std::list<CpTopology3Room*> iRoomList;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TOPOLOGY3
