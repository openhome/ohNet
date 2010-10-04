#ifndef HEADER_TOPOLOGY2
#define HEADER_TOPOLOGY2

#include <ZappTypes.h>
#include <Fifo.h>
#include <Thread.h>
#include <Core/CpLinnCoUkProduct3.h>
#include <Core/CpLinnCoUkPreamp4.h>
#include <Core/CpUpnpOrgRenderingControl1.h>

#include <vector>

#include "CpTopology1.h"

namespace Zapp {

class CpTopology2Group;

class ICpTopology2GroupHandler
{
public:
    virtual void SetSourceIndex(TUint aIndex) = 0;
    virtual void SetStandby(TBool aValue) = 0;
    virtual void SetVolume(TUint aValue) = 0;
    virtual void SetMute(TBool aValue) = 0;
	~ICpTopology2GroupHandler() {}
};

class CpTopology2Source
{
	friend class CpTopology2Group;
	
	static const TUint kMaxNameBytes = 20;
	static const TUint kMaxTypeBytes = 20;

private:
    CpTopology2Source(const Brx& aName, const Brx& aType, TBool aVisible);
    const Brx& Name() const;
    const Brx& Type() const;
    TBool Visible() const;
    void Update(const Brx& aName, const Brx& aType, TBool aVisible);
    
private:
	Bws<kMaxNameBytes> iName;
	Bws<kMaxTypeBytes> iType;
	TBool iVisible;
};

class CpTopology2;

class CpTopology2Group
{
	friend class CpTopology2Product;
	friend class CpTopology2MediaRenderer;

	static const TUint kMaxRoomBytes = 20;
	static const TUint kMaxNameBytes = 20;
	
private:
    CpTopology2Group(ICpTopology2GroupHandler& aHandler, CpDevice& aDevice, TBool aStandby, const Brx& aRoom, const Brx& aName, TUint aSourceIndex, TBool aHasVolumeControl, TUint aVolume, TBool aMute);
    void AddSource(const Brx& aName, const Brx& aType, TBool aVisible);
	void UpdateRoom(const Brx& aRoom);
	void UpdateName(const Brx& aName);
	void UpdateSourceIndex(TUint aIndex);
	void UpdateStandby(TBool aValue);
    void UpdateSource(TUint aIndex, const Brx& aName, const Brx& aType, TBool aVisible);
    void UpdateVolume(TUint aVolume);
    void UpdateMute(TBool aMute);
    ~CpTopology2Group();

public:
    void AddRef();
    void RemoveRef();
    CpDevice& Device() const;
    TBool Standby() const;
    void SetStandby(TBool aValue);
    const Brx& Room() const;
    const Brx& Name() const;
    TUint SourceCount() const;
    const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
    TBool SourceVisible(TUint aIndex) const;
    TUint SourceIndex() const;
    void SetSourceIndex(TUint aIndex);
    TBool HasVolumeControl() const;
    TUint Volume() const;
    void SetVolume(TUint aValue) const;
    TBool Mute() const;
    void SetMute(TBool aValue);
	void SetUserData(void* aPtr);
	void* UserData() const;
	
private:
	ICpTopology2GroupHandler& iHandler;
    CpDevice& iDevice;
	TBool iStandby;
	Bws<kMaxRoomBytes> iRoom;
	Bws<kMaxNameBytes> iName;
	TUint iSourceIndex;
	TBool iHasVolumeControl;
	TUint iVolume;
	TBool iMute;
	void* iUserData;
    TUint iRefCount;
    std::vector<CpTopology2Source*> iSourceList;
};


class ICpTopology2Handler
{
public:
	virtual void GroupAdded(CpTopology2Group& aGroup) = 0;
	virtual void GroupStandbyChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupSourceIndexChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupSourceListChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupVolumeChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupMuteChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupRemoved(CpTopology2Group& aDevice) = 0;
	~ICpTopology2Handler() {}
};

typedef void (ICpTopology2Handler::*ICpTopology2HandlerFunction)(CpTopology2Group&);

class CpTopology2Job
{
public:
	CpTopology2Job(ICpTopology2Handler& aHandler);
	void Set(CpTopology2Group& aGroup, ICpTopology2HandlerFunction aFunction);
    virtual void Execute();
private:
	ICpTopology2Handler* iHandler;
	CpTopology2Group* iGroup;
	ICpTopology2HandlerFunction iFunction;
};

class CpTopology2Device : public INonCopyable, public ICpTopology2GroupHandler
{
protected:
	CpTopology2Device(CpDevice& aDevice);
	
public:
	TBool IsAttachedTo(CpDevice& aDevice);
	virtual ~CpTopology2Device();

private:
	// ICpTopology2GroupHandler
    virtual void SetSourceIndex(TUint aIndex) = 0;
    virtual void SetStandby(TBool aValue) = 0;

protected:
	CpDevice& iDevice;
};

class CpTopology2Product : public CpTopology2Device 
{
public:
	CpTopology2Product(CpDevice& aDevice, ICpTopology2Handler& aHandler);
	virtual ~CpTopology2Product();

private:
	// ICpTopology2GroupHandler
    virtual void SetSourceIndex(TUint aIndex);
    virtual void SetStandby(TBool aValue);
    virtual void SetVolume(TUint aValue);
    virtual void SetMute(TBool aValue);

	void CallbackSetSourceIndex(IAsync& aAsync);		
	void CallbackSetStandby(IAsync& aAsync);		
	void CallbackSetVolume(IAsync& aAsync);		
	void CallbackSetMute(IAsync& aAsync);		

	void ProcessSourceXml(const Brx& aXml, TBool aInitial);
	void EventIgnorePropertyChanged();
	void EventProductPropertyChanged();
	void EventProductRoomChanged();	
	void EventProductNameChanged();	
	void EventProductStandbyChanged();	
	void EventProductSourceIndexChanged();	
	void EventProductSourceXmlChanged();	
	void EventPreampPropertyChanged();
	void EventVolumeChanged();	
	void EventMuteChanged();	

private:
	ICpTopology2Handler& iHandler;
	CpProxyLinnCoUkProduct3* iServiceProduct;
	CpProxyLinnCoUkPreamp4* iServicePreamp;
	CpTopology2Group* iGroup;
	FunctorAsync iFunctorSetSourceIndex;
	FunctorAsync iFunctorSetStandby;
	FunctorAsync iFunctorSetVolume;
	FunctorAsync iFunctorSetMute;
};

class CpTopology2MediaRenderer : public CpTopology2Device 
{
public:
	CpTopology2MediaRenderer(CpDevice& aDevice, ICpTopology2Handler& aHandler);
	virtual ~CpTopology2MediaRenderer();

private:
	// ICpTopology2GroupHandler
    virtual void SetSourceIndex(TUint aIndex);
    virtual void SetStandby(TBool aValue);
    virtual void SetVolume(TUint aValue);
    virtual void SetMute(TBool aValue);

	void CallbackSetVolume(IAsync& aAsync);		
	void CallbackSetMute(IAsync& aAsync);		

	void EventRenderingControlPropertyChanged();

	void ParseFriendlyName(const Brx& aFriendlyName, Brn& aRoom, Brn& aName);
	TBool ParseFriendlyNameBracketed(const Brx& aFriendlyName, Brn& aRoom, Brn& aName, TChar aOpen, TChar aClose);
	
	void ProcessLastChange();
	
private:
	ICpTopology2Handler& iHandler;
	CpProxyUpnpOrgRenderingControl1* iServiceRenderingControl;
	CpTopology2Group* iGroup;
	TUint iVolume;
	TBool iMute;
	TBool iHasVolume;
	TBool iHasTransport;
	FunctorAsync iFunctorSetVolume;
	FunctorAsync iFunctorSetMute;
};

class CpTopology2 : public ICpTopology1Handler, public ICpTopology2Handler
{
	static const TUint kMaxJobCount = 20;
	
public:
	CpTopology2(ICpTopology2Handler& aHandler);
	
    void Refresh();
    
    ~CpTopology2();
    
private:
	// ICpTopology1Handler
	virtual void ProductAdded(CpDevice& aDevice);
	virtual void ProductRemoved(CpDevice& aDevice);
	virtual void UpnpAdded(CpDevice& aDevice);
	virtual void UpnpRemoved(CpDevice& aDevice);

	void DeviceRemoved(CpDevice& aDevice);

	// ICpTopology2Handler
	virtual void GroupAdded(CpTopology2Group& aGroup);
	virtual void GroupStandbyChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceIndexChanged(CpTopology2Group& aGroup);
	virtual void GroupSourceListChanged(CpTopology2Group& aGroup);
	virtual void GroupVolumeChanged(CpTopology2Group& aGroup);
	virtual void GroupMuteChanged(CpTopology2Group& aGroup);
	virtual void GroupRemoved(CpTopology2Group& aDevice);

	void Run();
	
private:
	CpTopology1* iTopology1;
	Fifo<CpTopology2Job*> iFree;
	Fifo<CpTopology2Job*> iReady;
	ThreadFunctor* iThread;
    std::vector<CpTopology2Device*> iDeviceList;
};

} // namespace Zapp

#endif // HEADER_TOPOLOGY2
