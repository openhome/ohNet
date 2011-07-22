#include "Services/DvAvOpenhomeOrgProduct1.h"
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Private/Arch.h>

#include <stdio.h>

#include "Product.h"

using namespace OpenHome;
using namespace OpenHome::Net;

using namespace Openhome::Av;

// CObservable

CObservable::CObservable()
{
}

void CObservable::Add(IObserver& aObserver)
{
	iObserverList.push_back(&aObserver);
}

void CObservable::InformObservers()
{
	for (std::vector<IObserver*>::iterator it = iObserverList.begin(); it != iObserverList.end(); ++it) {
		*it->Changed();
	}	
}

// CSource

CSource::CSource(const Brx& aSystemName, const Brx& aType, const Brx& aName, TBool aVisible, ILockable& aLockable)
	: iSystemName(aSystemName)
	, iType(aType)
	, iName(aName)
	, iVisible(aVisible)
	, iLockable(aLockable)
{
}

TBool CSource::Visible(Bwx& aSystemName, Bwx& aType, Bwx& aName)
{
	aSystemName.Replace(iSystemName);
	aType.Replace(iType);
	iLockable.Wait();
	aName.Replace(iName);
	TBool visible = iVisible;
	iMutex.Signal();
	return (visible);
}

void CSource::SetName(const Brx& aValue)
{
	iMutex.Wait();
	iName.Replace(aName);
	iMutex.Release();
	InformObservers();
}

void CSource::SetVisible(const Brx& aValue)
{
	iMutex.Wait();
	iVisible = aVisible;
	iMutex.Signal();
	InformObservers();
}

// CSourceManager

CSourceManager::CSourceManager()
	: iMutex("SRCM")
{
	UpdateSourceXml();
}

void CSourceManager::Add(CSource* aSource)
{
	iSourceList.push_back(aSource);
	aSource->Add(*this);
}

TUint CSourceManager::SourceCount() const
{
	return (iSourceList.size());
}

CSource& CSourceManager::Source(TUint aIndex)
{
	ASSERT(aIndex < iSourceList.size());
	return (*iSourceList[aIndex]);
}

void CSourceManager::Changed()
{
}

void CSourceManager::UpdateSourceXml()
{
    iSourceXml.Replace("<SourceList>");

    TUint count = iProduct.SourceCount();

    for (TUint i = 0; i < count; i++) {
        iSourceXml.Append("<Source>");

        Bws<Source::kMaxSourceNameBytes> name;
        iProduct.SourceName(i, name);

        LOG(kCommon,"name = ");
        LOG(kCommon, name);
        LOG(kCommon,"\n");

        Bwd escapedName(EscapedLength(name));
        Escape(name, escapedName);

        LOG(kCommon,"escapedName = ");
        LOG(kCommon, escapedName);
        LOG(kCommon,"\n");

        iSourceXml.Append("<Name>");
        iSourceXml.Append(escapedName);
        iSourceXml.Append("</Name>");

        iSourceXml.Append("<Type>");
        iSourceXml.Append(iProduct.SourceType(i));
        iSourceXml.Append("</Type>");

        iSourceXml.Append("<Visible>");
        if (iProduct.SourceVisible(i)) {
            iSourceXml.Append("true");
        }
        else {
            iSourceXml.Append("false");
        }
        iSourceXml.Append("</Visible>");

        iSourceXml.Append("</Source>");
    }

    iSourceXml.Append("</SourceList>");

    iSourceXmlChangeCount++;
}

// CProduct

CProduct::CProduct(DvDevice& aDevice
    , IStandbyHandler& aStandbyHandler
    , ISourceIndexHandler& aSourceIndexHandler
	, TBool aStandby
	, const TChar* aAttributes
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
	, const TChar* aProductImageUri)
    : DvProviderAvOpenhomeOrgProduct1(aDevice)
    , iStandbyHandler(aStandbyHandler)
    , iSourceIndexHandler(aSourceIndexHandler)
    , iSourceXmlChangeCount(0)
    , iMutex("PROD")
{
    aDevice.SetAttribute("Upnp.Domain", "av.openhome.org");
    aDevice.SetAttribute("Upnp.Type", "Product");
    aDevice.SetAttribute("Upnp.Version", "1");
    aDevice.SetAttribute("Upnp.FriendlyName", "Product");
    aDevice.SetAttribute("Upnp.Manufacturer", aManufacturerName);
    aDevice.SetAttribute("Upnp.ManufacturerUrl", aManufacturerUrl);
    aDevice.SetAttribute("Upnp.ModelDescription", aModelInfo);
    aDevice.SetAttribute("Upnp.ModelName", aModelName);
    aDevice.SetAttribute("Upnp.ModelNumber", "");
    aDevice.SetAttribute("Upnp.ModelUrl", aModelUrl);
    aDevice.SetAttribute("Upnp.SerialNumber", "");
    aDevice.SetAttribute("Upnp.Upc", "");

    EnableActionManufacturer();
    EnableActionModel();
    EnableActionProduct();
    EnableActionStandby();
    EnableActionSetStandby();
    EnableActionSourceCount();
    EnableActionSourceXml();
    EnableActionSourceIndex();
    EnableActionSetSourceIndex();
    EnableActionSetSourceIndexByName();
    EnableActionSource();
    EnableActionAttributes();
    EnableActionSourceXmlChangeCount();
    
    SetPropertyStandby(aStandby);
    SetPropertyAttributes(Brn(aAttributes));
    
    SetPropertyManufacturerName(Brn(aManufacturerName));
    SetPropertyManufacturerInfo(Brn(aManufacturerInfo));
    SetPropertyManufacturerUrl(Brn(aManufacturerUrl));
    SetPropertyManufacturerImageUri(Brn(aManufacturerImageUri));
    
    SetPropertyModelName(Brn(aModelName));
    SetPropertyModelInfo(Brn(aModelInfo));
    SetPropertyModelUrl(Brn(aModelUrl));
    SetPropertyModelImageUri(Brn(aModelImageUri));
    
    SetPropertyProductRoom(Brn(aProductRoom));
    SetPropertyProductName(Brn(aProductName));
    SetPropertyProductInfo(Brn(aProductInfo));
    SetPropertyProductUrl(Brn(aProductUrl));
    SetPropertyProductImageUri(Brn(aProductImageUri));
    
    SetPropertySourceIndex(0);
    SetPropertySourceCount(0);
    SetPropertySourceXml(Brn(""));
}

void CProduct::Manufacturer(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aName, IInvocationResponseString& aInfo, IInvocationResponseString& aUrl, IInvocationResponseString& aImageUri)
{
	Brhz name;
	Brhz info;
	Brhz url;
	Brhz image;
    GetPropertyManufacturerName(name);
    GetPropertyManufacturerInfo(info);
    GetPropertyManufacturerUrl(url);
    GetPropertyManufacturerImageUri(image);
    aResponse.Start();
    aName.Write(name);
    aName.WriteFlush();
    aInfo.Write(info);
    aInfo.WriteFlush();
    aUrl.Write(url);
    aUrl.WriteFlush();
	aImageUri.Write(image);
	aImageUri.WriteFlush();
    aResponse.End();
}

void CProduct::Model(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aName, IInvocationResponseString& aInfo, IInvocationResponseString& aUrl, IInvocationResponseString& aImageUri)
{
	Brhz name;
	Brhz info;
	Brhz url;
	Brhz image;
    GetPropertyModelName(name);
    GetPropertyModelInfo(info);
    GetPropertyModelUrl(url);
    GetPropertyModelImageUri(image);
    aResponse.Start();
    aName.Write(name);
    aName.WriteFlush();
    aInfo.Write(info);
    aInfo.WriteFlush();
    aUrl.Write(url);
    aUrl.WriteFlush();
	aImageUri.Write(image);
	aImageUri.WriteFlush();
    aResponse.End();
}

void CProduct::Product(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aRoom, IInvocationResponseString& aName, IInvocationResponseString& aInfo, IInvocationResponseString& aUrl, IInvocationResponseString& aImageUri)
{
	Brhz room;
	Brhz name;
	Brhz info;
	Brhz url;
	Brhz image;
    GetPropertyProductRoom(room);
    GetPropertyProductName(name);
    GetPropertyProductInfo(info);
    GetPropertyProductUrl(url);
    GetPropertyProductImageUri(image);
    aResponse.Start();
    aRoom.Write(room);
    aRoom.WriteFlush();
    aName.Write(name);
    aName.WriteFlush();
    aInfo.Write(info);
    aInfo.WriteFlush();
    aUrl.Write(url);
    aUrl.WriteFlush();
	aImageUri.Write(image);
	aImageUri.WriteFlush();
    aResponse.End();
}

void CProduct::Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue)
{
	TBool value;
    GetPropertyStandby(value);
    aResponse.Start();
    aValue.Write(value);
    aResponse.End();
}

void CProduct::SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aValue)
{
    aResponse.Start();
    aResponse.End();

    if (SetPropertyStandby(aValue)) {
    	iStandbyHandler.SetStandby(aValue);
    }
}

void CProduct::SourceCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue)
{
	TUint value;
    GetPropertySourceCount(value);
    aResponse.Start();
    aValue.Write(value);
    aResponse.End();
}

void CProduct::SourceXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue)
{
	Brhz value;
    GetPropertySourceXml(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
}

void CProduct::SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue)
{
	TUint value;
    GetPropertySourceIndex(value);
    aResponse.Start();
    aValue.Write(value);
    aResponse.End();
}

void CProduct::SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aValue)
{
	TUint count;
    GetPropertySourceCount(count);
	if (aValue < count) {
	    aResponse.Start();
	    aResponse.End();
	    if (SetPropertySourceIndex(aValue)) {
	    	iSourceIndexHandler.SetSourceIndex(aValue);
	    }
	}
	else {
		aResponse.Error(802, Brn("Source index out of range"));
	}
}

void CProduct::SetSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue)
{
}

void CProduct::Source(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aSystemName, IInvocationResponseString& aType, IInvocationResponseString& aName, IInvocationResponseBool& aVisible)
{
	TUint count;
    GetPropertySourceCount(count);
	if (aValue < count) {
		CSource* source = iSourceList[aValue);
	    aResponse.Start();
	    aSystemName.Write(source->SystemName());
	    aSystemName.WriteFlush();
	    aType.Write(source->Type());
	    aType.WriteFlush();
	    aName.Write(source->Name());
	    aName.WriteFlush();
	    aVisible.Write(source->Visible());
	    aResponse.End();
	}
	else {
		aResponse.Error(802, Brn("Source index out of range"));
	}
}

void CProduct::Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue)
{
	Brhz value;
    GetPropertyAttributes(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
}

void CProduct::SourceXmlChangeCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue)
{
	iMutex.Wait();
	TUint value = iSourceXmlChangeCount;
	iMutex.Signal();
    aResponse.Start();
    aValue.Write(value);
    aResponse.End();
}


