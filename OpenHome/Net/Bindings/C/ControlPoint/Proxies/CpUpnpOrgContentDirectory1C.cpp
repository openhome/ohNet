#include "CpUpnpOrgContentDirectory1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyUpnpOrgContentDirectory1C : public CpProxyC
{
public:
    CpProxyUpnpOrgContentDirectory1C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgContentDirectory1C();
    //CpProxyUpnpOrgContentDirectory1* Proxy() { return static_cast<CpProxyUpnpOrgContentDirectory1*>(iProxy); }

    void SyncGetSearchCapabilities(Brh& aSearchCaps);
    void BeginGetSearchCapabilities(FunctorAsync& aFunctor);
    void EndGetSearchCapabilities(IAsync& aAsync, Brh& aSearchCaps);

    void SyncGetSortCapabilities(Brh& aSortCaps);
    void BeginGetSortCapabilities(FunctorAsync& aFunctor);
    void EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps);

    void SyncGetSystemUpdateID(TUint& aId);
    void BeginGetSystemUpdateID(FunctorAsync& aFunctor);
    void EndGetSystemUpdateID(IAsync& aAsync, TUint& aId);

    void SyncBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    void BeginBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor);
    void EndBrowse(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);

    void SyncSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    void BeginSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor);
    void EndSearch(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);

    void SyncCreateObject(const Brx& aContainerID, const Brx& aElements, Brh& aObjectID, Brh& aResult);
    void BeginCreateObject(const Brx& aContainerID, const Brx& aElements, FunctorAsync& aFunctor);
    void EndCreateObject(IAsync& aAsync, Brh& aObjectID, Brh& aResult);

    void SyncDestroyObject(const Brx& aObjectID);
    void BeginDestroyObject(const Brx& aObjectID, FunctorAsync& aFunctor);
    void EndDestroyObject(IAsync& aAsync);

    void SyncUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue);
    void BeginUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue, FunctorAsync& aFunctor);
    void EndUpdateObject(IAsync& aAsync);

    void SyncImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID);
    void BeginImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor);
    void EndImportResource(IAsync& aAsync, TUint& aTransferID);

    void SyncExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID);
    void BeginExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor);
    void EndExportResource(IAsync& aAsync, TUint& aTransferID);

    void SyncStopTransferResource(TUint aTransferID);
    void BeginStopTransferResource(TUint aTransferID, FunctorAsync& aFunctor);
    void EndStopTransferResource(IAsync& aAsync);

    void SyncGetTransferProgress(TUint aTransferID, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);
    void BeginGetTransferProgress(TUint aTransferID, FunctorAsync& aFunctor);
    void EndGetTransferProgress(IAsync& aAsync, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);

    void SyncDeleteResource(const Brx& aResourceURI);
    void BeginDeleteResource(const Brx& aResourceURI, FunctorAsync& aFunctor);
    void EndDeleteResource(IAsync& aAsync);

    void SyncCreateReference(const Brx& aContainerID, const Brx& aObjectID, Brh& aNewID);
    void BeginCreateReference(const Brx& aContainerID, const Brx& aObjectID, FunctorAsync& aFunctor);
    void EndCreateReference(IAsync& aAsync, Brh& aNewID);

    void SetPropertyTransferIDsChanged(Functor& aFunctor);
    void SetPropertySystemUpdateIDChanged(Functor& aFunctor);
    void SetPropertyContainerUpdateIDsChanged(Functor& aFunctor);

    void PropertyTransferIDs(Brhz& aTransferIDs) const;
    void PropertySystemUpdateID(TUint& aSystemUpdateID) const;
    void PropertyContainerUpdateIDs(Brhz& aContainerUpdateIDs) const;
private:
    void TransferIDsPropertyChanged();
    void SystemUpdateIDPropertyChanged();
    void ContainerUpdateIDsPropertyChanged();
private:
    Mutex iLock;
    Action* iActionGetSearchCapabilities;
    Action* iActionGetSortCapabilities;
    Action* iActionGetSystemUpdateID;
    Action* iActionBrowse;
    Action* iActionSearch;
    Action* iActionCreateObject;
    Action* iActionDestroyObject;
    Action* iActionUpdateObject;
    Action* iActionImportResource;
    Action* iActionExportResource;
    Action* iActionStopTransferResource;
    Action* iActionGetTransferProgress;
    Action* iActionDeleteResource;
    Action* iActionCreateReference;
    PropertyString* iTransferIDs;
    PropertyUint* iSystemUpdateID;
    PropertyString* iContainerUpdateIDs;
    Functor iTransferIDsChanged;
    Functor iSystemUpdateIDChanged;
    Functor iContainerUpdateIDsChanged;
};


class SyncGetSearchCapabilitiesUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aSearchCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSearchCapabilitiesUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    Brh& iSearchCaps;
};

SyncGetSearchCapabilitiesUpnpOrgContentDirectory1C::SyncGetSearchCapabilitiesUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aSearchCaps)
    : iService(aProxy)
    , iSearchCaps(aSearchCaps)
{
}

void SyncGetSearchCapabilitiesUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSearchCapabilities(aAsync, iSearchCaps);
}


class SyncGetSortCapabilitiesUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aSortCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    Brh& iSortCaps;
};

SyncGetSortCapabilitiesUpnpOrgContentDirectory1C::SyncGetSortCapabilitiesUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aSortCaps)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
{
}

void SyncGetSortCapabilitiesUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps);
}


class SyncGetSystemUpdateIDUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncGetSystemUpdateIDUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, TUint& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSystemUpdateIDUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    TUint& iId;
};

SyncGetSystemUpdateIDUpnpOrgContentDirectory1C::SyncGetSystemUpdateIDUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, TUint& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetSystemUpdateIDUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSystemUpdateID(aAsync, iId);
}


class SyncBrowseUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncBrowseUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseUpnpOrgContentDirectory1C::SyncBrowseUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowse(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncSearchUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncSearchUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSearchUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncSearchUpnpOrgContentDirectory1C::SyncSearchUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncSearchUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSearch(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateObjectUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncCreateObjectUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aObjectID, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateObjectUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    Brh& iObjectID;
    Brh& iResult;
};

SyncCreateObjectUpnpOrgContentDirectory1C::SyncCreateObjectUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aObjectID, Brh& aResult)
    : iService(aProxy)
    , iObjectID(aObjectID)
    , iResult(aResult)
{
}

void SyncCreateObjectUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateObject(aAsync, iObjectID, iResult);
}


class SyncDestroyObjectUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncDestroyObjectUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDestroyObjectUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
};

SyncDestroyObjectUpnpOrgContentDirectory1C::SyncDestroyObjectUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy)
    : iService(aProxy)
{
}

void SyncDestroyObjectUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDestroyObject(aAsync);
}


class SyncUpdateObjectUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncUpdateObjectUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUpdateObjectUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
};

SyncUpdateObjectUpnpOrgContentDirectory1C::SyncUpdateObjectUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy)
    : iService(aProxy)
{
}

void SyncUpdateObjectUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndUpdateObject(aAsync);
}


class SyncImportResourceUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncImportResourceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, TUint& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncImportResourceUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    TUint& iTransferID;
};

SyncImportResourceUpnpOrgContentDirectory1C::SyncImportResourceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, TUint& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncImportResourceUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndImportResource(aAsync, iTransferID);
}


class SyncExportResourceUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncExportResourceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, TUint& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncExportResourceUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    TUint& iTransferID;
};

SyncExportResourceUpnpOrgContentDirectory1C::SyncExportResourceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, TUint& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncExportResourceUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndExportResource(aAsync, iTransferID);
}


class SyncStopTransferResourceUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncStopTransferResourceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopTransferResourceUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
};

SyncStopTransferResourceUpnpOrgContentDirectory1C::SyncStopTransferResourceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy)
    : iService(aProxy)
{
}

void SyncStopTransferResourceUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopTransferResource(aAsync);
}


class SyncGetTransferProgressUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncGetTransferProgressUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransferProgressUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    Brh& iTransferStatus;
    Brh& iTransferLength;
    Brh& iTransferTotal;
};

SyncGetTransferProgressUpnpOrgContentDirectory1C::SyncGetTransferProgressUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
    : iService(aProxy)
    , iTransferStatus(aTransferStatus)
    , iTransferLength(aTransferLength)
    , iTransferTotal(aTransferTotal)
{
}

void SyncGetTransferProgressUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransferProgress(aAsync, iTransferStatus, iTransferLength, iTransferTotal);
}


class SyncDeleteResourceUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncDeleteResourceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteResourceUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
};

SyncDeleteResourceUpnpOrgContentDirectory1C::SyncDeleteResourceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteResourceUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteResource(aAsync);
}


class SyncCreateReferenceUpnpOrgContentDirectory1C : public SyncProxyAction
{
public:
    SyncCreateReferenceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aNewID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateReferenceUpnpOrgContentDirectory1C() {};
private:
    CpProxyUpnpOrgContentDirectory1C& iService;
    Brh& iNewID;
};

SyncCreateReferenceUpnpOrgContentDirectory1C::SyncCreateReferenceUpnpOrgContentDirectory1C(CpProxyUpnpOrgContentDirectory1C& aProxy, Brh& aNewID)
    : iService(aProxy)
    , iNewID(aNewID)
{
}

void SyncCreateReferenceUpnpOrgContentDirectory1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateReference(aAsync, iNewID);
}

CpProxyUpnpOrgContentDirectory1C::CpProxyUpnpOrgContentDirectory1C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "ContentDirectory", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetSearchCapabilities = new Action("GetSearchCapabilities");
    param = new OpenHome::Net::ParameterString("SearchCaps");
    iActionGetSearchCapabilities->AddOutputParameter(param);

    iActionGetSortCapabilities = new Action("GetSortCapabilities");
    param = new OpenHome::Net::ParameterString("SortCaps");
    iActionGetSortCapabilities->AddOutputParameter(param);

    iActionGetSystemUpdateID = new Action("GetSystemUpdateID");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionGetSystemUpdateID->AddOutputParameter(param);

    iActionBrowse = new Action("Browse");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionBrowse->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"BrowseMetadata";
    allowedValues[index++] = (TChar*)"BrowseDirectChildren";
    param = new OpenHome::Net::ParameterString("BrowseFlag", allowedValues, 2);
    iActionBrowse->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("Filter");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionBrowse->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionBrowse->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionBrowse->AddOutputParameter(param);

    iActionSearch = new Action("Search");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SearchCriteria");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionSearch->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionSearch->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionSearch->AddOutputParameter(param);

    iActionCreateObject = new Action("CreateObject");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionCreateObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Elements");
    iActionCreateObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionCreateObject->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionCreateObject->AddOutputParameter(param);

    iActionDestroyObject = new Action("DestroyObject");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionDestroyObject->AddInputParameter(param);

    iActionUpdateObject = new Action("UpdateObject");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionUpdateObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentTagValue");
    iActionUpdateObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewTagValue");
    iActionUpdateObject->AddInputParameter(param);

    iActionImportResource = new Action("ImportResource");
    param = new OpenHome::Net::ParameterString("SourceURI");
    iActionImportResource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("DestinationURI");
    iActionImportResource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("TransferID");
    iActionImportResource->AddOutputParameter(param);

    iActionExportResource = new Action("ExportResource");
    param = new OpenHome::Net::ParameterString("SourceURI");
    iActionExportResource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("DestinationURI");
    iActionExportResource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("TransferID");
    iActionExportResource->AddOutputParameter(param);

    iActionStopTransferResource = new Action("StopTransferResource");
    param = new OpenHome::Net::ParameterUint("TransferID");
    iActionStopTransferResource->AddInputParameter(param);

    iActionGetTransferProgress = new Action("GetTransferProgress");
    param = new OpenHome::Net::ParameterUint("TransferID");
    iActionGetTransferProgress->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"COMPLETED";
    allowedValues[index++] = (TChar*)"ERROR";
    allowedValues[index++] = (TChar*)"IN_PROGRESS";
    allowedValues[index++] = (TChar*)"STOPPED";
    param = new OpenHome::Net::ParameterString("TransferStatus", allowedValues, 4);
    iActionGetTransferProgress->AddOutputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("TransferLength");
    iActionGetTransferProgress->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("TransferTotal");
    iActionGetTransferProgress->AddOutputParameter(param);

    iActionDeleteResource = new Action("DeleteResource");
    param = new OpenHome::Net::ParameterString("ResourceURI");
    iActionDeleteResource->AddInputParameter(param);

    iActionCreateReference = new Action("CreateReference");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionCreateReference->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionCreateReference->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewID");
    iActionCreateReference->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1C::TransferIDsPropertyChanged);
    iTransferIDs = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TransferIDs", functor);
    AddProperty(iTransferIDs);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1C::SystemUpdateIDPropertyChanged);
    iSystemUpdateID = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "SystemUpdateID", functor);
    AddProperty(iSystemUpdateID);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory1C::ContainerUpdateIDsPropertyChanged);
    iContainerUpdateIDs = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "ContainerUpdateIDs", functor);
    AddProperty(iContainerUpdateIDs);
}

CpProxyUpnpOrgContentDirectory1C::~CpProxyUpnpOrgContentDirectory1C()
{
    DestroyService();
    delete iActionGetSearchCapabilities;
    delete iActionGetSortCapabilities;
    delete iActionGetSystemUpdateID;
    delete iActionBrowse;
    delete iActionSearch;
    delete iActionCreateObject;
    delete iActionDestroyObject;
    delete iActionUpdateObject;
    delete iActionImportResource;
    delete iActionExportResource;
    delete iActionStopTransferResource;
    delete iActionGetTransferProgress;
    delete iActionDeleteResource;
    delete iActionCreateReference;
}

void CpProxyUpnpOrgContentDirectory1C::SyncGetSearchCapabilities(Brh& aSearchCaps)
{
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory1C sync(*this, aSearchCaps);
    BeginGetSearchCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginGetSearchCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSearchCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSearchCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndGetSearchCapabilities(IAsync& aAsync, Brh& aSearchCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSearchCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSearchCaps);
}

void CpProxyUpnpOrgContentDirectory1C::SyncGetSortCapabilities(Brh& aSortCaps)
{
    SyncGetSortCapabilitiesUpnpOrgContentDirectory1C sync(*this, aSortCaps);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSortCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSortCaps);
}

void CpProxyUpnpOrgContentDirectory1C::SyncGetSystemUpdateID(TUint& aId)
{
    SyncGetSystemUpdateIDUpnpOrgContentDirectory1C sync(*this, aId);
    BeginGetSystemUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginGetSystemUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSystemUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSystemUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndGetSystemUpdateID(IAsync& aAsync, TUint& aId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSystemUpdateID"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1C::SyncBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseUpnpOrgContentDirectory1C sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBrowse, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowse->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aBrowseFlag));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSortCriteria));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowse->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndBrowse(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Browse"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1C::SyncSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncSearchUpnpOrgContentDirectory1C sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSearch, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSearch->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSearchCriteria));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSortCriteria));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSearch->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndSearch(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Search"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1C::SyncCreateObject(const Brx& aContainerID, const Brx& aElements, Brh& aObjectID, Brh& aResult)
{
    SyncCreateObjectUpnpOrgContentDirectory1C sync(*this, aObjectID, aResult);
    BeginCreateObject(aContainerID, aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginCreateObject(const Brx& aContainerID, const Brx& aElements, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCreateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aElements));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndCreateObject(IAsync& aAsync, Brh& aObjectID, Brh& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateObject"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aObjectID);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
}

void CpProxyUpnpOrgContentDirectory1C::SyncDestroyObject(const Brx& aObjectID)
{
    SyncDestroyObjectUpnpOrgContentDirectory1C sync(*this);
    BeginDestroyObject(aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginDestroyObject(const Brx& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDestroyObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDestroyObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndDestroyObject(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DestroyObject"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory1C::SyncUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    SyncUpdateObjectUpnpOrgContentDirectory1C sync(*this);
    BeginUpdateObject(aObjectID, aCurrentTagValue, aNewTagValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionUpdateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUpdateObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentTagValue));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewTagValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndUpdateObject(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("UpdateObject"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory1C::SyncImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID)
{
    SyncImportResourceUpnpOrgContentDirectory1C sync(*this, aTransferID);
    BeginImportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionImportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionImportResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSourceURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDestinationURI));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndImportResource(IAsync& aAsync, TUint& aTransferID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ImportResource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aTransferID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1C::SyncExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID)
{
    SyncExportResourceUpnpOrgContentDirectory1C sync(*this, aTransferID);
    BeginExportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionExportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionExportResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSourceURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDestinationURI));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionExportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndExportResource(IAsync& aAsync, TUint& aTransferID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ExportResource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aTransferID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory1C::SyncStopTransferResource(TUint aTransferID)
{
    SyncStopTransferResourceUpnpOrgContentDirectory1C sync(*this);
    BeginStopTransferResource(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginStopTransferResource(TUint aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStopTransferResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStopTransferResource->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndStopTransferResource(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StopTransferResource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory1C::SyncGetTransferProgress(TUint aTransferID, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
{
    SyncGetTransferProgressUpnpOrgContentDirectory1C sync(*this, aTransferStatus, aTransferLength, aTransferTotal);
    BeginGetTransferProgress(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginGetTransferProgress(TUint aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetTransferProgress, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransferProgress->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransferProgress->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndGetTransferProgress(IAsync& aAsync, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTransferProgress"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTransferStatus);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTransferLength);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aTransferTotal);
}

void CpProxyUpnpOrgContentDirectory1C::SyncDeleteResource(const Brx& aResourceURI)
{
    SyncDeleteResourceUpnpOrgContentDirectory1C sync(*this);
    BeginDeleteResource(aResourceURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginDeleteResource(const Brx& aResourceURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aResourceURI));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndDeleteResource(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteResource"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgContentDirectory1C::SyncCreateReference(const Brx& aContainerID, const Brx& aObjectID, Brh& aNewID)
{
    SyncCreateReferenceUpnpOrgContentDirectory1C sync(*this, aNewID);
    BeginCreateReference(aContainerID, aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory1C::BeginCreateReference(const Brx& aContainerID, const Brx& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCreateReference, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateReference->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateReference->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory1C::EndCreateReference(IAsync& aAsync, Brh& aNewID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateReference"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aNewID);
}

void CpProxyUpnpOrgContentDirectory1C::SetPropertyTransferIDsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTransferIDsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgContentDirectory1C::SetPropertySystemUpdateIDChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSystemUpdateIDChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgContentDirectory1C::SetPropertyContainerUpdateIDsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iContainerUpdateIDsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgContentDirectory1C::PropertyTransferIDs(Brhz& aTransferIDs) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTransferIDs.Set(iTransferIDs->Value());
}

void CpProxyUpnpOrgContentDirectory1C::PropertySystemUpdateID(TUint& aSystemUpdateID) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aSystemUpdateID = iSystemUpdateID->Value();
}

void CpProxyUpnpOrgContentDirectory1C::PropertyContainerUpdateIDs(Brhz& aContainerUpdateIDs) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aContainerUpdateIDs.Set(iContainerUpdateIDs->Value());
}

void CpProxyUpnpOrgContentDirectory1C::TransferIDsPropertyChanged()
{
    ReportEvent(iTransferIDsChanged);
}

void CpProxyUpnpOrgContentDirectory1C::SystemUpdateIDPropertyChanged()
{
    ReportEvent(iSystemUpdateIDChanged);
}

void CpProxyUpnpOrgContentDirectory1C::ContainerUpdateIDsPropertyChanged()
{
    ReportEvent(iContainerUpdateIDsChanged);
}


THandle STDCALL CpProxyUpnpOrgContentDirectory1Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgContentDirectory1C(aDevice);
}

void STDCALL CpProxyUpnpOrgContentDirectory1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncGetSearchCapabilities(THandle aHandle, char** aSearchCaps)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSearchCaps;
    int32_t err = 0;
    try {
        proxyC->SyncGetSearchCapabilities(buf_aSearchCaps);
        *aSearchCaps = buf_aSearchCaps.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aSearchCaps = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginGetSearchCapabilities(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSearchCapabilities(functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndGetSearchCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aSearchCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSearchCaps;
    *aSearchCaps = NULL;
    try {
        proxyC->EndGetSearchCapabilities(*async, buf_aSearchCaps);
        *aSearchCaps = buf_aSearchCaps.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncGetSortCapabilities(THandle aHandle, char** aSortCaps)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortCaps;
    int32_t err = 0;
    try {
        proxyC->SyncGetSortCapabilities(buf_aSortCaps);
        *aSortCaps = buf_aSortCaps.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aSortCaps = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginGetSortCapabilities(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSortCapabilities(functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndGetSortCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aSortCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSortCaps;
    *aSortCaps = NULL;
    try {
        proxyC->EndGetSortCapabilities(*async, buf_aSortCaps);
        *aSortCaps = buf_aSortCaps.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncGetSystemUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetSystemUpdateID(*aId);
    }
    catch (ProxyError& ) {
        err = -1;
        *aId = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginGetSystemUpdateID(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSystemUpdateID(functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndGetSystemUpdateID(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetSystemUpdateID(*async, *aId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    int32_t err = 0;
    try {
        proxyC->SyncBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aResult = NULL;
        *aNumberReturned = 0;
        *aTotalMatches = 0;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndBrowse(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndBrowse(*async, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    int32_t err = 0;
    try {
        proxyC->SyncSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aResult = NULL;
        *aNumberReturned = 0;
        *aTotalMatches = 0;
        *aUpdateID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndSearch(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndSearch(*async, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    Brh buf_aObjectID;
    Brh buf_aResult;
    int32_t err = 0;
    try {
        proxyC->SyncCreateObject(buf_aContainerID, buf_aElements, buf_aObjectID, buf_aResult);
        *aObjectID = buf_aObjectID.Extract();
        *aResult = buf_aResult.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aObjectID = NULL;
        *aResult = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginCreateObject(buf_aContainerID, buf_aElements, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndCreateObject(THandle aHandle, OhNetHandleAsync aAsync, char** aObjectID, char** aResult)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aObjectID;
    *aObjectID = NULL;
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->EndCreateObject(*async, buf_aObjectID, buf_aResult);
        *aObjectID = buf_aObjectID.Extract();
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncDestroyObject(THandle aHandle, const char* aObjectID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    int32_t err = 0;
    try {
        proxyC->SyncDestroyObject(buf_aObjectID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginDestroyObject(THandle aHandle, const char* aObjectID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDestroyObject(buf_aObjectID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndDestroyObject(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDestroyObject(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    int32_t err = 0;
    try {
        proxyC->SyncUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndUpdateObject(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndUpdateObject(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    int32_t err = 0;
    try {
        proxyC->SyncImportResource(buf_aSourceURI, buf_aDestinationURI, *aTransferID);
    }
    catch (ProxyError& ) {
        err = -1;
        *aTransferID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginImportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndImportResource(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndImportResource(*async, *aTransferID);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    int32_t err = 0;
    try {
        proxyC->SyncExportResource(buf_aSourceURI, buf_aDestinationURI, *aTransferID);
    }
    catch (ProxyError& ) {
        err = -1;
        *aTransferID = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginExportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndExportResource(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndExportResource(*async, *aTransferID);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncStopTransferResource(THandle aHandle, uint32_t aTransferID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStopTransferResource(aTransferID);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginStopTransferResource(THandle aHandle, uint32_t aTransferID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStopTransferResource(aTransferID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndStopTransferResource(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStopTransferResource(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncGetTransferProgress(THandle aHandle, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTransferStatus;
    Brh buf_aTransferLength;
    Brh buf_aTransferTotal;
    int32_t err = 0;
    try {
        proxyC->SyncGetTransferProgress(aTransferID, buf_aTransferStatus, buf_aTransferLength, buf_aTransferTotal);
        *aTransferStatus = buf_aTransferStatus.Extract();
        *aTransferLength = buf_aTransferLength.Extract();
        *aTransferTotal = buf_aTransferTotal.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aTransferStatus = NULL;
        *aTransferLength = NULL;
        *aTransferTotal = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginGetTransferProgress(THandle aHandle, uint32_t aTransferID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetTransferProgress(aTransferID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndGetTransferProgress(THandle aHandle, OhNetHandleAsync aAsync, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aTransferStatus;
    *aTransferStatus = NULL;
    Brh buf_aTransferLength;
    *aTransferLength = NULL;
    Brh buf_aTransferTotal;
    *aTransferTotal = NULL;
    try {
        proxyC->EndGetTransferProgress(*async, buf_aTransferStatus, buf_aTransferLength, buf_aTransferTotal);
        *aTransferStatus = buf_aTransferStatus.Extract();
        *aTransferLength = buf_aTransferLength.Extract();
        *aTransferTotal = buf_aTransferTotal.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncDeleteResource(THandle aHandle, const char* aResourceURI)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    int32_t err = 0;
    try {
        proxyC->SyncDeleteResource(buf_aResourceURI);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginDeleteResource(THandle aHandle, const char* aResourceURI, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteResource(buf_aResourceURI, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndDeleteResource(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDeleteResource(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1SyncCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, char** aNewID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewID;
    int32_t err = 0;
    try {
        proxyC->SyncCreateReference(buf_aContainerID, buf_aObjectID, buf_aNewID);
        *aNewID = buf_aNewID.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aNewID = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1BeginCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginCreateReference(buf_aContainerID, buf_aObjectID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory1EndCreateReference(THandle aHandle, OhNetHandleAsync aAsync, char** aNewID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aNewID;
    *aNewID = NULL;
    try {
        proxyC->EndCreateReference(*async, buf_aNewID);
        *aNewID = buf_aNewID.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory1SetPropertyTransferIDsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTransferIDsChanged(functor);
}

void STDCALL CpProxyUpnpOrgContentDirectory1SetPropertySystemUpdateIDChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySystemUpdateIDChanged(functor);
}

void STDCALL CpProxyUpnpOrgContentDirectory1SetPropertyContainerUpdateIDsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyContainerUpdateIDsChanged(functor);
}

void STDCALL CpProxyUpnpOrgContentDirectory1PropertyTransferIDs(THandle aHandle, char** aTransferIDs)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransferIDs;
    proxyC->PropertyTransferIDs(buf_aTransferIDs);
    *aTransferIDs = buf_aTransferIDs.Transfer();
}

void STDCALL CpProxyUpnpOrgContentDirectory1PropertySystemUpdateID(THandle aHandle, uint32_t* aSystemUpdateID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySystemUpdateID(*aSystemUpdateID);
}

void STDCALL CpProxyUpnpOrgContentDirectory1PropertyContainerUpdateIDs(THandle aHandle, char** aContainerUpdateIDs)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aContainerUpdateIDs;
    proxyC->PropertyContainerUpdateIDs(buf_aContainerUpdateIDs);
    *aContainerUpdateIDs = buf_aContainerUpdateIDs.Transfer();
}

