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
    virtual void RoomVolumeLimitChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomVolumeChanged(CpTopology3Room& aRoom) = 0;
    virtual void RoomBalanceChanged(CpTopology3Room& aRoom) = 0;
    virtual void RoomFadeChanged(CpTopology3Room& aRoom) = 0;
	virtual void RoomMuteChanged(CpTopology3Room& aRoom) = 0;
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
    const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
    const Brx& SourceGroup(TUint aIndex) const;
    CpDevice& SourceDevice(TUint aIndex) const;

	TBool HasParent() const;
	CpTopology3Group& Parent() const;
	TUint ParentSourceIndex() const;

	TBool Root() const;
	void SetRoot(TBool aValue);
	TUint EvaluateSourceCount();
	TBool IsCurrentDescendentOf(CpTopology3Group& aGroup) const;
	CpTopology3Group& CurrentDescendent();
	CpTopology3Source& Source(TUint aIndex) const;

	void GroupStandbyChanged();
	void GroupSourceIndexChanged();
	void GroupSourceListChanged();
    void GroupVolumeLimitChanged();
	void GroupVolumeChanged();
    void GroupBalanceChanged();
    void GroupFadeChanged();
	void GroupMuteChanged();
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
	TBool iRoot;
    std::vector<CpTopology3Source*> iSourceList;
    TUint iSourceCount;
};

class CpTopology3Source : private INonCopyable
{
public:
	CpTopology3Source(CpTopology2Group& aGroup, TUint aIndex);

	const Brx& Name() const;
    const Brx& Type() const;
    const Brx& Group() const;
    CpDevice& Device() const;

	TUint ChildCount() const;
	CpTopology3Group& Child(TUint aIndex) const;
	
	void AddChild(CpTopology3Group& aGroup);
	void RemoveChild(CpTopology3Group& aGroup);
	void ClearChildren();

    TUint EvaluateSourceCount();
    TUint SourceCount() const;
    const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
    const Brx& SourceGroup(TUint aIndex) const;
    CpDevice& SourceDevice(TUint aIndex) const;

	~CpTopology3Source();
	
private:
    CpTopology2Group& iGroup;
    TUint iIndex;
    std::vector<CpTopology3Group*> iChildList;
    TUint iSourceCount;
};

class CpTopology3;

class CpTopology3Room : private INonCopyable
{
	static const TUint kMaxNameBytes = 20;

public:
    CpTopology3Room(const Brx& aName, ICpTopology3Handler& aHandler);

	// functions accessible within ICpTopology3Handler callbacks

    void AddRef();
    void RemoveRef();
    TBool Standby() const;
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
    TUint VolumeMax() const;
    TUint VolumeUnity() const;
    TUint VolumeSteps() const;
    TUint VolumeMilliDbPerStep() const;
    TUint FadeMax() const;
    TUint BalanceMax() const;
    TUint VolumeLimit() const;
    TUint Volume() const;
    TInt Balance() const;
    TInt Fade() const;
    TBool Mute() const;
    void SetUserData(void* aValue);
    void* UserData() const;

	// functions always accessible
    void SetStandby(TBool aValue);
    void SetSourceIndex(TUint aIndex);
    void SetVolume(TUint aValue);
    void VolumeInc();
    void VolumeDec();
    void SetBalance(TInt aValue);
    void BalanceInc();
    void BalanceDec();
    void SetFade(TInt aValue);
    void FadeInc();
    void FadeDec();
    void SetMute(TBool aValue);

	void GroupAdded(CpTopology3Group& aGroup);
	void GroupStandbyChanged(CpTopology3Group& aGroup);
	void GroupSourceIndexChanged(CpTopology3Group& aGroup);
	void GroupSourceListChanged(CpTopology3Group& aGroup);
    void GroupVolumeLimitChanged(CpTopology3Group& aGroup);
	void GroupVolumeChanged(CpTopology3Group& aGroup);
    void GroupBalanceChanged(CpTopology3Group& aGroup);
    void GroupFadeChanged(CpTopology3Group& aGroup);
	void GroupMuteChanged(CpTopology3Group& aGroup);
	void GroupRemoved(CpTopology3Group& aGroup);

    ~CpTopology3Room();

private:
	TUint EvaluateSourceCount();
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
    TUint iRefCount;
    TBool iHasVolumeControl;
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
    virtual void GroupVolumeLimitChanged(CpTopology2Group& aGroup);
	virtual void GroupVolumeChanged(CpTopology2Group& aGroup);
    virtual void GroupBalanceChanged(CpTopology2Group& aGroup);
    virtual void GroupFadeChanged(CpTopology2Group& aGroup);
	virtual void GroupMuteChanged(CpTopology2Group& aGroup);
	virtual void GroupRemoved(CpTopology2Group& aGroup);

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
	ICpTopology3Handler& iHandler;
	CpTopology2* iTopology2;
    std::list<CpTopology3Room*> iRoomList;
};

} // namespace Net
} // namespace OpenHome
