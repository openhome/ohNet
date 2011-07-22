#ifndef HEADER_OPENHOME_PRODUCT
#define HEADER_OPENHOME_PRODUCT

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>

//#include "DvAvOpenhomeOrgProduct1.h"

using namespace OpenHome::Net;

namespace Openhome {
namespace Av {

class ILockable
{
public:
	virtual void Wait() = 0;
	virtual void Signal() = 0;
	virtual ~ILockable() {}
};

class IObserver
{
	virtual void Changed() = 0;
	virtual ~IObserver() {}
};

// This observable class is not thread safe on adding observers

class CObservable
{
public:
	CObservable();
	void Add(IObserver& aObserver);

protected:
	void InformObservers() const;

private:
	std::vector<IObserver*> iObserverList;
};

class IStandbyHandler
{
public:
	virtual void SetStandby(TBool aValue) = 0;
	virtual ~IStandbyHandler() {}
};

class ISourceIndexHandler
{
public:
	virtual void SetSourceIndex(TUint aValue) = 0;
	virtual ~ISourceIndexHandler() {}
};

class CSourceManager;

class CSource : public CObservable
{
	friend class CSourceManager;
	
	static const TUint kMaxTypeBytes = 20;
	static const TUint kMaxNameBytes = 20;

public:
	TBool Visible(Bwx& aSystemName, Bwx& aType, Bwx& aName);
	void SetName(const Brx& aValue);
	void SetVisible(const Brx& aValue);
	void Add(IObserver& aObserver);	

private:
	void Wait();
	void Signal();
	CSource(const Brx& aSystemName, const Brx& aType, const Brx& aName, TBool aVisible, ILockable& aLockable);
	
private:
	Bws<kMaxNameBytes) iSystemName;
	Bws<kMaxTypeBytes) iType;
	Bws<kMaxNameBytes) iName;
	TBool iVisible;
	ILockable& iLockable;
};

class CSourceManager : public CObservable, public IObserver, ILockable
{
public:
	CSourceManager();
	CSource& Create(const Brx& aSystemName, const Brx& aType, const Brx& aName, TBool aVisible);
	TUint SourceCount() const;
	CSource& Source(TUint aIndex);

private:
	virtual void Changed();
	void UpdateSourceXml();
	
private:
	mutable Mutex iMutex;	
	std::vector<CSource*> iSourceList;
	Bws<kMaxSourceXmlBytes> iSourceXml;
};

class CProduct : public OpenHome::Net::DvProviderAvOpenhomeOrgProduct1
{
	static const TUint kMaxRoomBytes = 20;
	static const TUint kMaxNameBytes = 20;

public:
	CProduct(DvDevice& aDevice
	, IStandbyHandler& aStandbyHandler
    , ISourceIndexHandler& aSourceIndexHandler
	, TBool aStandby
	, const TChar* aAtrributes
	, const TChar* aManufacturerName
	, const TChar* aManufacturerInfo
	, const TChar* aManufacturerUrl
	, const TChar* aManufacturerImageUri
	, const TChar* aModelName
	, const TChar* aModelInfo
	, const TChar* aModelUrl
	, const TChar* aModelImageUri
	, const TChar* aProductRoom
	, const TChar* aProductName
	, const TChar* aProductInfo
	, const TChar* aProductUrl
	, const TChar* aProductImageUri);
    
    void SetRoom(const Brx& aRoom);
    void SetName(const Brx& aName);
    void SetStandby(TBool aStandby);
    
private:
    virtual void Manufacturer(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aName, IInvocationResponseString& aInfo, IInvocationResponseString& aUrl, IInvocationResponseString& aImageUri);
    virtual void Model(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aName, IInvocationResponseString& aInfo, IInvocationResponseString& aUrl, IInvocationResponseString& aImageUri);
    virtual void Product(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aRoom, IInvocationResponseString& aName, IInvocationResponseString& aInfo, IInvocationResponseString& aUrl, IInvocationResponseString& aImageUri);
    virtual void Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    virtual void SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aValue);
    virtual void SourceCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
    virtual void SourceXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
    virtual void SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aValue);
    virtual void SetSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue);
    virtual void Source(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aSystemName, IInvocationResponseString& aType, IInvocationResponseString& aName, IInvocationResponseBool& aVisible);
    virtual void Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void SourceXmlChangeCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);

private:
    IStandbyHandler& iStandbyHandler;
    ISourceIndexHandler& iSourceIndexHandler;
    TUint iSourceXmlChangeCount;
	mutable Mutex iMutex;
};

} // namespace Av
} // namespace Openhome

#endif // HEADER_OPENHOME_PRODUCT

