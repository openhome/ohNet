#ifndef HEADER_TOPOLOGY4
#define HEADER_TOPOLOGY4

#include <OpenHome/Private/Standard.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>

#include <vector>
#include <list>

#include "CpTopology3.h"

namespace OpenHome {
namespace Net {

class CpTopology4Room;

class ICpTopology4Handler
{
public:
    virtual void RoomAdded(CpTopology4Room& aRoom) = 0;
    virtual void RoomChanged(CpTopology4Room& aRoom) = 0;
    virtual void RoomRemoved(CpTopology4Room& aRoom) = 0;
    virtual void RoomStandbyChanged(CpTopology4Room& aRoom) = 0;
    virtual void RoomSourceChanged(CpTopology4Room& aRoom) = 0;
    virtual void RoomVolumeControlChanged(CpTopology4Room& aRoom) = 0;
	virtual void RoomVolumeChanged(CpTopology4Room& aRoom) = 0;
	virtual void RoomMuteChanged(CpTopology4Room& aRoom) = 0;
	virtual void RoomVolumeLimitChanged(CpTopology4Room& aRoom) = 0;
    ~ICpTopology4Handler() {}
};

class CpTopology4Source;

class CpTopology4Room;

class CpTopology4Group : private INonCopyable
{
public:
    CpTopology4Group(CpTopology3Group& aGroup, CpTopology4Room& aRoom);

    CpTopology3Group& Group() const;
    CpTopology4Room& Room() const;
    const Brx& Name() const;
    TUint SourceCount() const;

    TBool HasParent() const;
    CpTopology4Group& Parent() const;
    TUint ParentSourceIndex() const;

    TBool IsRoot() const;
    void SetIsRoot(TBool aValue);
    TUint EvaluateSources(std::vector<CpTopology4Source*>& aVector);
    TBool IsDescendentOf(CpTopology4Group& aGroup) const;
    TBool IsCurrentDescendentOf(CpTopology4Group& aGroup) const;
    CpTopology4Group& Root();
    CpTopology4Group& CurrentDescendent();
    CpTopology4Source& Source(TUint aIndex) const;

    void GroupStandbyChanged();
    void GroupSourceIndexChanged();
    void GroupSourceListChanged();
    void GroupRemoved();
	void GroupVolumeControlChanged();
	void GroupVolumeChanged();
	void GroupMuteChanged();
	void GroupVolumeLimitChanged();

    void ClearParent();
    void ClearChildren();
    void SetParent(CpTopology4Group& aGroup, TUint aSourceIndex);
    TBool AddIfIsChild(CpTopology4Group& aGroup);
    void AddChild(CpTopology4Group& aGroup, TUint aSourceIndex);
    void RemoveChild(CpTopology4Group& aGroup, TUint aSourceIndex);

    ~CpTopology4Group();

private:
    CpTopology3Group& iGroup;
    CpTopology4Room& iRoom;
    CpTopology4Group* iParent;
    TUint iParentSourceIndex;
    TBool iIsRoot;
    std::vector<CpTopology4Source*> iSourceList;
    TUint iSourceCount;
};

class CpTopology4Source : private INonCopyable
{
public:
    CpTopology4Source(CpTopology4Group& aGroup, TUint aIndex);

    const Brx& Name() const;
    const Brx& Type() const;
    const Brx& Group() const;
    CpDevice& Device() const;

    void Select();

    CpTopology4Group& Owner() const;

    TUint ChildCount() const;
    CpTopology4Group& Child(TUint aIndex) const;
    
    void AddChild(CpTopology4Group& aGroup);
    void RemoveChild(CpTopology4Group& aGroup);
    void ClearChildren();

    TUint EvaluateSources(std::vector<CpTopology4Source*>& aVector);
    TUint SourceCount() const;

    ~CpTopology4Source();
    
private:
    CpTopology4Group& iGroup;
    TUint iIndex;
    std::vector<CpTopology4Group*> iChildList;
    TUint iSourceCount;
};

class CpTopology4;

class CpTopology4Room : private INonCopyable
{
    static const TUint kMaxNameBytes = 20;

public:
    enum EStandby {
        eOn,
        eMixed,
        eOff
    };

public:
    CpTopology4Room(const Brx& aName, ICpTopology4Handler& aHandler);
    ~CpTopology4Room();

    // functions which must be called from ICpTopology4Handler callback thread

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
	TUint Volume() const;
	TBool Mute() const;
	TUint VolumeLimit() const;
    EStandby Standby() const;
    void SetUserData(void* aValue);
    void* UserData() const;

    // functions which must NOT be called from ICpTopology4Handler callback thread

    void SetStandby(TBool aValue);
    void SetSourceIndex(TUint aIndex);

	void SetVolume(TUint aValue);
	void VolumeInc();
	void VolumeDec();
	void SetMute(TBool aValue);

    // private calls from CpTopology4Group

    void GroupAdded(CpTopology4Group& aGroup);
    void GroupStandbyChanged(CpTopology4Group& aGroup);
    void GroupSourceIndexChanged(CpTopology4Group& aGroup);
    void GroupSourceListChanged(CpTopology4Group& aGroup);
    void GroupRemoved(CpTopology4Group& aGroup);
	void GroupVolumeControlChanged(CpTopology4Group& aGroup);
	void GroupVolumeChanged(CpTopology4Group& aGroup);
	void GroupMuteChanged(CpTopology4Group& aGroup);
	void GroupVolumeLimitChanged(CpTopology4Group& aGroup);

private:
    void UpdateCurrentGroup(CpTopology4Group& aGroup);
    TUint EvaluateSources();
    void EvaluateStandby();
    void ReportGroups();

private:
    Bws<kMaxNameBytes> iName;
    ICpTopology4Handler& iHandler;
    std::vector<CpTopology4Group*> iGroupList;
    std::vector<CpTopology4Group*> iRootList;
    std::vector<CpTopology4Source*> iSourceList;
    CpTopology4Group* iCurrentGroup;
    TBool iActive;
    mutable Mutex iMutex;
    TUint iSourceCount;
    TUint iStandbyCount;
    EStandby iStandby;
    TUint iRefCount;
    void* iUserData;
};


class CpTopology4 : public ICpTopology3Handler, public ICpTopology4Handler, private INonCopyable
{
public:
    CpTopology4(ICpTopology4Handler& aHandler);
    CpTopology4(ICpTopology4Handler& aHandler, ICpTopology3Handler** aTestInterface);
    void Refresh();
    virtual ~CpTopology4();
    
private:
    // ICpTopology3Handler
    virtual void GroupAdded(CpTopology3Group& aGroup);
    virtual void GroupStandbyChanged(CpTopology3Group& aGroup);
    virtual void GroupSourceIndexChanged(CpTopology3Group& aGroup);
    virtual void GroupSourceListChanged(CpTopology3Group& aGroup);
    virtual void GroupRemoved(CpTopology3Group& aGroup);
	virtual void GroupVolumeControlChanged(CpTopology3Group& aGroup);
	virtual void GroupVolumeChanged(CpTopology3Group& aGroup);
	virtual void GroupMuteChanged(CpTopology3Group& aGroup);
	virtual void GroupVolumeLimitChanged(CpTopology3Group& aGroup);

    // ICpTopology4Handler
    virtual void RoomAdded(CpTopology4Room& aRoom);
    virtual void RoomChanged(CpTopology4Room& aRoom);
    virtual void RoomRemoved(CpTopology4Room& aRoom);
    virtual void RoomStandbyChanged(CpTopology4Room& aRoom);
    virtual void RoomSourceChanged(CpTopology4Room& aRoom);
    virtual void RoomVolumeControlChanged(CpTopology4Room& aRoom);
	virtual void RoomVolumeChanged(CpTopology4Room& aRoom);
	virtual void RoomMuteChanged(CpTopology4Room& aRoom);
	virtual void RoomVolumeLimitChanged(CpTopology4Room& aRoom);

private:
    ICpTopology4Handler& iHandler;
    CpTopology3* iTopology3;
    std::list<CpTopology4Room*> iRoomList;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TOPOLOGY4
