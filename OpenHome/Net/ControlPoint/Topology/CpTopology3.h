#ifndef HEADER_TOPOLOGY3
#define HEADER_TOPOLOGY3

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>

#include <list>

#include "CpTopology2.h"

namespace OpenHome {
namespace Net {

class CpTopology3Group;

class ICpTopology3Handler
{
public:
    virtual void GroupAdded(CpTopology3Group& aGroup) = 0;
    virtual void GroupStandbyChanged(CpTopology3Group& aGroup) = 0;
    virtual void GroupSourceIndexChanged(CpTopology3Group& aGroup) = 0;
    virtual void GroupSourceListChanged(CpTopology3Group& aGroup) = 0;
    virtual void GroupRemoved(CpTopology3Group& aGroup) = 0;
	virtual void GroupVolumeControlChanged(CpTopology3Group& aGroup) = 0;
	virtual void GroupVolumeChanged(CpTopology3Group& aGroup) = 0;
	virtual void GroupMuteChanged(CpTopology3Group& aGroup) = 0;
	virtual void GroupVolumeLimitChanged(CpTopology3Group& aGroup) = 0;
    ~ICpTopology3Handler() {}
};

class CpTopology3Group : private INonCopyable
{
public:
    CpTopology3Group(CpTopology2Group& aGroup, ICpTopology3Handler& aHandler);
    ~CpTopology3Group();

    // functions which must be called from ICpTopology3Handler callback thread

    void AddRef();
    void RemoveRef();
	CpDevice& Device() const;
	const Brx& Room() const;
    const Brx& Name() const;
    TUint SourceCount() const;
	TUint SourceIndex() const;
	const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
    TBool SourceVisible(TUint aIndex) const;
    TBool HasVolumeControl() const;
	TUint Volume() const;
	TBool Mute() const;
	TUint VolumeLimit() const;
    TBool Standby() const;
    void SetUserData(void* aValue);
    void* UserData() const;

    // functions which must NOT be called from ICpTopology3Handler callback thread

    void SetStandby(TBool aValue);
    void SetSourceIndex(TUint aIndex);

	void SetVolume(TUint aValue);
	void VolumeInc();
	void VolumeDec();
	void SetMute(TBool aValue);

    void GroupAdded();
    void GroupStandbyChanged();
    void GroupSourceIndexChanged();
    void GroupSourceListChanged();
    void GroupRemoved();

	void EventInitialEvent();
	void EventVolumeChanged();
	void EventMuteChanged();
	void EventVolumeLimitChanged();

	void CallbackSetVolume(IAsync& aAsync);
	void CallbackVolumeInc(IAsync& aAsync);
	void CallbackVolumeDec(IAsync& aAsync);
    void CallbackSetMute(IAsync& aAsync);

private:
	CpTopology2Group& iGroup;
	ICpTopology3Handler& iHandler;

	TBool iHasVolumeControl;
    CpProxyAvOpenhomeOrgVolume1* iServiceVolume;
    
	FunctorAsync iFunctorSetVolume;
	FunctorAsync iFunctorVolumeInc;
	FunctorAsync iFunctorVolumeDec;
    FunctorAsync iFunctorSetMute;

	TUint iVolume;
	TBool iMute;
	TUint iVolumeLimit;

	TUint iRefCount;
	void* iUserData;
};


typedef void (ICpTopology3Handler::*ICpTopology3HandlerFunction)(CpTopology3Group&);

class CpTopology3Job
{
public:
    CpTopology3Job(ICpTopology3Handler& aHandler);
    void Set(CpTopology3Group& aGroup, ICpTopology3HandlerFunction aFunction);
    virtual void Execute();
private:
    ICpTopology3Handler* iHandler;
    CpTopology3Group* iGroup;
    ICpTopology3HandlerFunction iFunction;
};


class CpTopology3 : public ICpTopology2Handler, public ICpTopology3Handler, private INonCopyable
{
    static const TUint kMaxJobCount = 20;
    
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
    virtual void GroupRemoved(CpTopology2Group& aDevice);

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

    void Run();
    
private:
    std::list<CpTopology3Group*> iGroupList;
	CpTopology2* iTopology2;
    Fifo<CpTopology3Job*> iFree;
    Fifo<CpTopology3Job*> iReady;
    ThreadFunctor* iThread;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TOPOLOGY3