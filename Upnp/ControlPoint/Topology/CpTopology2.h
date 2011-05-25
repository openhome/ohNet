#ifndef HEADER_TOPOLOGY2
#define HEADER_TOPOLOGY2

#include <OhNetTypes.h>
#include <Fifo.h>
#include <Thread.h>
#include <Core/CpAvOpenhomeOrgProduct1.h>
#include <Core/CpAvOpenhomeOrgVolume1.h>

#include <vector>

#include "CpTopology1.h"

namespace OpenHome {
namespace Net {

class CpTopology2Group;

class ICpTopology2Handler
{
public:
	virtual void GroupAdded(CpTopology2Group& aGroup) = 0;
	virtual void GroupStandbyChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupSourceIndexChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupSourceListChanged(CpTopology2Group& aGroup) = 0;
    virtual void GroupVolumeLimitChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupVolumeChanged(CpTopology2Group& aGroup) = 0;
    virtual void GroupBalanceChanged(CpTopology2Group& aGroup) = 0;
    virtual void GroupFadeChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupMuteChanged(CpTopology2Group& aGroup) = 0;
	virtual void GroupRemoved(CpTopology2Group& aDevice) = 0;
	~ICpTopology2Handler() {}
};

class ICpTopology2GroupHandler
{
public:
    virtual void SetSourceIndex(TUint aIndex) = 0;
    virtual void SetStandby(TBool aValue) = 0;
    virtual void SetVolume(TUint aValue) = 0;
    virtual void VolumeInc() = 0;
    virtual void VolumeDec() = 0;
    virtual void SetBalance(TInt aValue) = 0;
    virtual void BalanceInc() = 0;
    virtual void BalanceDec() = 0;
    virtual void SetFade(TInt aValue) = 0;
    virtual void FadeInc() = 0;
    virtual void FadeDec() = 0;
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

class CpTopology2Group
{
	friend class CpTopology2Product;
	friend class CpTopology2MediaRenderer;

	static const TUint kMaxRoomBytes = 20;
	static const TUint kMaxNameBytes = 20;
	
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
    TUint VolumeMax() const;
    TUint VolumeUnity() const;
    TUint VolumeSteps() const;
    TUint VolumeMilliDbPerStep() const;
    TUint FadeMax() const;
    TUint BalanceMax() const;
    TUint VolumeLimit() const;
    TUint Volume() const;
    void SetVolume(TUint aValue);
    void VolumeInc();
    void VolumeDec();
    TInt Balance() const;
    void SetBalance(TInt aValue);
    void BalanceInc();
    void BalanceDec();
    TInt Fade() const;
    void SetFade(TInt aValue);
    void FadeInc();
    void FadeDec();
    TBool Mute() const;
    void SetMute(TBool aValue);
    void SetUserData(void* aValue);
	void* UserData() const;
	
public: // for test purposes
    CpTopology2Group(CpDevice& aDevice, ICpTopology2GroupHandler& aHandler, TBool aStandby, const Brx& aRoom, const Brx& aName, TUint aSourceIndex, TUint aVolumeMax, TUint aVolumeUnity, TUint aVolumeSteps, TUint aVolumeMilliDbPerStep, TUint aBalanceMax, TUint aFadeMax, TUint aVolumelimit, TUint aVolume, TInt aBalance, TUint aFade, TBool aMute);
    CpTopology2Group(CpDevice& aDevice, ICpTopology2GroupHandler& aHandler, TBool aStandby, const Brx& aRoom, const Brx& aName, TUint aSourceIndex);
    void AddSource(const Brx& aName, const Brx& aType, TBool aVisible);
    void UpdateRoom(const Brx& aValue);
    void UpdateName(const Brx& aValue);
    void UpdateSourceIndex(TUint aValue);
    void UpdateStandby(TBool aValue);
    void UpdateSource(TUint aIndex, const Brx& aName, const Brx& aType, TBool aVisible);
    void UpdateVolumeLimit(TUint aValue);
    void UpdateVolume(TUint aValue);
    void UpdateBalance(TInt aValue);
    void UpdateFade(TInt aValue);
    void UpdateMute(TBool aValue);
    ~CpTopology2Group();

private:
    CpDevice& iDevice;
	ICpTopology2GroupHandler& iHandler;
	TBool iStandby;
	Bws<kMaxRoomBytes> iRoom;
	Bws<kMaxNameBytes> iName;
	TUint iSourceIndex;
	TBool iHasVolumeControl;
	TUint iVolumeMax;
	TUint iVolumeUnity;
	TUint iVolumeSteps;
	TUint iVolumeMilliDbPerStep;
	TUint iBalanceMax;
	TUint iFadeMax;
	TUint iVolumeLimit; 
	TUint iVolume;
	TInt iBalance;
	TInt iFade;
	TBool iMute;
	void* iUserData;
    TUint iRefCount;
    std::vector<CpTopology2Source*> iSourceList;
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
    virtual void SetVolume(TUint aValue) = 0;
    virtual void VolumeInc() = 0;
    virtual void VolumeDec() = 0;
    virtual void SetBalance(TInt aValue) = 0;
    virtual void BalanceInc() = 0;
    virtual void BalanceDec() = 0;
    virtual void SetFade(TInt aValue) = 0;
    virtual void FadeInc() = 0;
    virtual void FadeDec() = 0;
    virtual void SetMute(TBool aValue) = 0;

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
    virtual void VolumeInc();
    virtual void VolumeDec();
    virtual void SetBalance(TInt aValue);
    virtual void BalanceInc();
    virtual void BalanceDec();
    virtual void SetFade(TInt aValue);
    virtual void FadeInc();
    virtual void FadeDec();
    virtual void SetMute(TBool aValue);

	void CallbackSetSourceIndex(IAsync& aAsync);		
	void CallbackSetStandby(IAsync& aAsync);		
	void CallbackSetVolume(IAsync& aAsync);		
    void CallbackVolumeInc(IAsync& aAsync);     
    void CallbackVolumeDec(IAsync& aAsync);     
    void CallbackSetBalance(IAsync& aAsync);
    void CallbackBalanceInc(IAsync& aAsync);     
    void CallbackBalanceDec(IAsync& aAsync);     
    void CallbackSetFade(IAsync& aAsync);
    void CallbackFadeInc(IAsync& aAsync);     
    void CallbackFadeDec(IAsync& aAsync);     
	void CallbackSetMute(IAsync& aAsync);		

	void ProcessSourceXml(const Brx& aXml, TBool aInitial);
	void EventProductInitialEvent();
	void EventProductRoomChanged();	
	void EventProductNameChanged();	
	void EventProductStandbyChanged();	
	void EventProductSourceIndexChanged();	
	void EventProductSourceXmlChanged();	
	void EventPreampInitialEvent();
    void EventPreampVolumeLimitChanged();    
	void EventPreampVolumeChanged();	
    void EventPreampBalanceChanged();    
    void EventPreampFadeChanged();    
	void EventPreampMuteChanged();	

private:
	ICpTopology2Handler& iHandler;
	CpProxyAvOpenhomeOrgProduct1* iServiceProduct;
	CpProxyAvOpenhomeOrgVolume1* iServiceVolume;
	CpTopology2Group* iGroup;
	FunctorAsync iFunctorSetSourceIndex;
	FunctorAsync iFunctorSetStandby;
	FunctorAsync iFunctorSetVolume;
    FunctorAsync iFunctorVolumeInc;
    FunctorAsync iFunctorVolumeDec;
    FunctorAsync iFunctorSetBalance;
    FunctorAsync iFunctorBalanceInc;
    FunctorAsync iFunctorBalanceDec;
    FunctorAsync iFunctorSetFade;
    FunctorAsync iFunctorFadeInc;
    FunctorAsync iFunctorFadeDec;
	FunctorAsync iFunctorSetMute;
};

/*
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
*/

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

	void DeviceRemoved(CpDevice& aDevice);

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
	virtual void GroupRemoved(CpTopology2Group& aDevice);

	void Run();
	
private:
	CpTopology1* iTopology1;
	Fifo<CpTopology2Job*> iFree;
	Fifo<CpTopology2Job*> iReady;
	ThreadFunctor* iThread;
    std::vector<CpTopology2Device*> iDeviceList;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TOPOLOGY2
