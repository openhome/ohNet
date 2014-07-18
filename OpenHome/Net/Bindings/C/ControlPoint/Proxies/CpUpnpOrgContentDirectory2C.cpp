#include "CpUpnpOrgContentDirectory2.h"
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

class CpProxyUpnpOrgContentDirectory2C : public CpProxyC
{
public:
    CpProxyUpnpOrgContentDirectory2C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgContentDirectory2C();
    //CpProxyUpnpOrgContentDirectory2* Proxy() { return static_cast<CpProxyUpnpOrgContentDirectory2*>(iProxy); }

    void SyncGetSearchCapabilities(Brh& aSearchCaps);
    void BeginGetSearchCapabilities(FunctorAsync& aFunctor);
    void EndGetSearchCapabilities(IAsync& aAsync, Brh& aSearchCaps);

    void SyncGetSortCapabilities(Brh& aSortCaps);
    void BeginGetSortCapabilities(FunctorAsync& aFunctor);
    void EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps);

    void SyncGetSortExtensionCapabilities(Brh& aSortExtensionCaps);
    void BeginGetSortExtensionCapabilities(FunctorAsync& aFunctor);
    void EndGetSortExtensionCapabilities(IAsync& aAsync, Brh& aSortExtensionCaps);

    void SyncGetFeatureList(Brh& aFeatureList);
    void BeginGetFeatureList(FunctorAsync& aFunctor);
    void EndGetFeatureList(IAsync& aAsync, Brh& aFeatureList);

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

    void SyncMoveObject(const Brx& aObjectID, const Brx& aNewParentID, Brh& aNewObjectID);
    void BeginMoveObject(const Brx& aObjectID, const Brx& aNewParentID, FunctorAsync& aFunctor);
    void EndMoveObject(IAsync& aAsync, Brh& aNewObjectID);

    void SyncImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID);
    void BeginImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor);
    void EndImportResource(IAsync& aAsync, TUint& aTransferID);

    void SyncExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID);
    void BeginExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor);
    void EndExportResource(IAsync& aAsync, TUint& aTransferID);

    void SyncDeleteResource(const Brx& aResourceURI);
    void BeginDeleteResource(const Brx& aResourceURI, FunctorAsync& aFunctor);
    void EndDeleteResource(IAsync& aAsync);

    void SyncStopTransferResource(TUint aTransferID);
    void BeginStopTransferResource(TUint aTransferID, FunctorAsync& aFunctor);
    void EndStopTransferResource(IAsync& aAsync);

    void SyncGetTransferProgress(TUint aTransferID, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);
    void BeginGetTransferProgress(TUint aTransferID, FunctorAsync& aFunctor);
    void EndGetTransferProgress(IAsync& aAsync, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);

    void SyncCreateReference(const Brx& aContainerID, const Brx& aObjectID, Brh& aNewID);
    void BeginCreateReference(const Brx& aContainerID, const Brx& aObjectID, FunctorAsync& aFunctor);
    void EndCreateReference(IAsync& aAsync, Brh& aNewID);

    void SetPropertySystemUpdateIDChanged(Functor& aFunctor);
    void SetPropertyContainerUpdateIDsChanged(Functor& aFunctor);
    void SetPropertyTransferIDsChanged(Functor& aFunctor);

    void PropertySystemUpdateID(TUint& aSystemUpdateID) const;
    void PropertyContainerUpdateIDs(Brhz& aContainerUpdateIDs) const;
    void PropertyTransferIDs(Brhz& aTransferIDs) const;
private:
    void SystemUpdateIDPropertyChanged();
    void ContainerUpdateIDsPropertyChanged();
    void TransferIDsPropertyChanged();
private:
    Mutex iLock;
    Action* iActionGetSearchCapabilities;
    Action* iActionGetSortCapabilities;
    Action* iActionGetSortExtensionCapabilities;
    Action* iActionGetFeatureList;
    Action* iActionGetSystemUpdateID;
    Action* iActionBrowse;
    Action* iActionSearch;
    Action* iActionCreateObject;
    Action* iActionDestroyObject;
    Action* iActionUpdateObject;
    Action* iActionMoveObject;
    Action* iActionImportResource;
    Action* iActionExportResource;
    Action* iActionDeleteResource;
    Action* iActionStopTransferResource;
    Action* iActionGetTransferProgress;
    Action* iActionCreateReference;
    PropertyUint* iSystemUpdateID;
    PropertyString* iContainerUpdateIDs;
    PropertyString* iTransferIDs;
    Functor iSystemUpdateIDChanged;
    Functor iContainerUpdateIDsChanged;
    Functor iTransferIDsChanged;
};


class SyncGetSearchCapabilitiesUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aSearchCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSearchCapabilitiesUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iSearchCaps;
};

SyncGetSearchCapabilitiesUpnpOrgContentDirectory2C::SyncGetSearchCapabilitiesUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aSearchCaps)
    : iService(aProxy)
    , iSearchCaps(aSearchCaps)
{
}

void SyncGetSearchCapabilitiesUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSearchCapabilities(aAsync, iSearchCaps);
}


class SyncGetSortCapabilitiesUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aSortCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iSortCaps;
};

SyncGetSortCapabilitiesUpnpOrgContentDirectory2C::SyncGetSortCapabilitiesUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aSortCaps)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
{
}

void SyncGetSortCapabilitiesUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps);
}


class SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aSortExtensionCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iSortExtensionCaps;
};

SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2C::SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aSortExtensionCaps)
    : iService(aProxy)
    , iSortExtensionCaps(aSortExtensionCaps)
{
}

void SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortExtensionCapabilities(aAsync, iSortExtensionCaps);
}


class SyncGetFeatureListUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncGetFeatureListUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aFeatureList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetFeatureListUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iFeatureList;
};

SyncGetFeatureListUpnpOrgContentDirectory2C::SyncGetFeatureListUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aFeatureList)
    : iService(aProxy)
    , iFeatureList(aFeatureList)
{
}

void SyncGetFeatureListUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetFeatureList(aAsync, iFeatureList);
}


class SyncGetSystemUpdateIDUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncGetSystemUpdateIDUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, TUint& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSystemUpdateIDUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    TUint& iId;
};

SyncGetSystemUpdateIDUpnpOrgContentDirectory2C::SyncGetSystemUpdateIDUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, TUint& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetSystemUpdateIDUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSystemUpdateID(aAsync, iId);
}


class SyncBrowseUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncBrowseUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseUpnpOrgContentDirectory2C::SyncBrowseUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowse(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncSearchUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncSearchUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSearchUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncSearchUpnpOrgContentDirectory2C::SyncSearchUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncSearchUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSearch(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateObjectUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncCreateObjectUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aObjectID, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateObjectUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iObjectID;
    Brh& iResult;
};

SyncCreateObjectUpnpOrgContentDirectory2C::SyncCreateObjectUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aObjectID, Brh& aResult)
    : iService(aProxy)
    , iObjectID(aObjectID)
    , iResult(aResult)
{
}

void SyncCreateObjectUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateObject(aAsync, iObjectID, iResult);
}


class SyncDestroyObjectUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncDestroyObjectUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDestroyObjectUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
};

SyncDestroyObjectUpnpOrgContentDirectory2C::SyncDestroyObjectUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy)
    : iService(aProxy)
{
}

void SyncDestroyObjectUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDestroyObject(aAsync);
}


class SyncUpdateObjectUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncUpdateObjectUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUpdateObjectUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
};

SyncUpdateObjectUpnpOrgContentDirectory2C::SyncUpdateObjectUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy)
    : iService(aProxy)
{
}

void SyncUpdateObjectUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndUpdateObject(aAsync);
}


class SyncMoveObjectUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncMoveObjectUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aNewObjectID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMoveObjectUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iNewObjectID;
};

SyncMoveObjectUpnpOrgContentDirectory2C::SyncMoveObjectUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aNewObjectID)
    : iService(aProxy)
    , iNewObjectID(aNewObjectID)
{
}

void SyncMoveObjectUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMoveObject(aAsync, iNewObjectID);
}


class SyncImportResourceUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncImportResourceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, TUint& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncImportResourceUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    TUint& iTransferID;
};

SyncImportResourceUpnpOrgContentDirectory2C::SyncImportResourceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, TUint& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncImportResourceUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndImportResource(aAsync, iTransferID);
}


class SyncExportResourceUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncExportResourceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, TUint& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncExportResourceUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    TUint& iTransferID;
};

SyncExportResourceUpnpOrgContentDirectory2C::SyncExportResourceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, TUint& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncExportResourceUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndExportResource(aAsync, iTransferID);
}


class SyncDeleteResourceUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncDeleteResourceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteResourceUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
};

SyncDeleteResourceUpnpOrgContentDirectory2C::SyncDeleteResourceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteResourceUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteResource(aAsync);
}


class SyncStopTransferResourceUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncStopTransferResourceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopTransferResourceUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
};

SyncStopTransferResourceUpnpOrgContentDirectory2C::SyncStopTransferResourceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy)
    : iService(aProxy)
{
}

void SyncStopTransferResourceUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopTransferResource(aAsync);
}


class SyncGetTransferProgressUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncGetTransferProgressUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransferProgressUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iTransferStatus;
    Brh& iTransferLength;
    Brh& iTransferTotal;
};

SyncGetTransferProgressUpnpOrgContentDirectory2C::SyncGetTransferProgressUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
    : iService(aProxy)
    , iTransferStatus(aTransferStatus)
    , iTransferLength(aTransferLength)
    , iTransferTotal(aTransferTotal)
{
}

void SyncGetTransferProgressUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransferProgress(aAsync, iTransferStatus, iTransferLength, iTransferTotal);
}


class SyncCreateReferenceUpnpOrgContentDirectory2C : public SyncProxyAction
{
public:
    SyncCreateReferenceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aNewID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateReferenceUpnpOrgContentDirectory2C() {};
private:
    CpProxyUpnpOrgContentDirectory2C& iService;
    Brh& iNewID;
};

SyncCreateReferenceUpnpOrgContentDirectory2C::SyncCreateReferenceUpnpOrgContentDirectory2C(CpProxyUpnpOrgContentDirectory2C& aProxy, Brh& aNewID)
    : iService(aProxy)
    , iNewID(aNewID)
{
}

void SyncCreateReferenceUpnpOrgContentDirectory2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateReference(aAsync, iNewID);
}

CpProxyUpnpOrgContentDirectory2C::CpProxyUpnpOrgContentDirectory2C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "ContentDirectory", 2, *reinterpret_cast<CpiDevice*>(aDevice))
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

    iActionGetSortExtensionCapabilities = new Action("GetSortExtensionCapabilities");
    param = new OpenHome::Net::ParameterString("SortExtensionCaps");
    iActionGetSortExtensionCapabilities->AddOutputParameter(param);

    iActionGetFeatureList = new Action("GetFeatureList");
    param = new OpenHome::Net::ParameterString("FeatureList");
    iActionGetFeatureList->AddOutputParameter(param);

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

    iActionMoveObject = new Action("MoveObject");
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionMoveObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewParentID");
    iActionMoveObject->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewObjectID");
    iActionMoveObject->AddOutputParameter(param);

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

    iActionDeleteResource = new Action("DeleteResource");
    param = new OpenHome::Net::ParameterString("ResourceURI");
    iActionDeleteResource->AddInputParameter(param);

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

    iActionCreateReference = new Action("CreateReference");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionCreateReference->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ObjectID");
    iActionCreateReference->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("NewID");
    iActionCreateReference->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory2C::SystemUpdateIDPropertyChanged);
    iSystemUpdateID = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "SystemUpdateID", functor);
    AddProperty(iSystemUpdateID);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory2C::ContainerUpdateIDsPropertyChanged);
    iContainerUpdateIDs = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "ContainerUpdateIDs", functor);
    AddProperty(iContainerUpdateIDs);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory2C::TransferIDsPropertyChanged);
    iTransferIDs = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TransferIDs", functor);
    AddProperty(iTransferIDs);
}

CpProxyUpnpOrgContentDirectory2C::~CpProxyUpnpOrgContentDirectory2C()
{
    DestroyService();
    delete iActionGetSearchCapabilities;
    delete iActionGetSortCapabilities;
    delete iActionGetSortExtensionCapabilities;
    delete iActionGetFeatureList;
    delete iActionGetSystemUpdateID;
    delete iActionBrowse;
    delete iActionSearch;
    delete iActionCreateObject;
    delete iActionDestroyObject;
    delete iActionUpdateObject;
    delete iActionMoveObject;
    delete iActionImportResource;
    delete iActionExportResource;
    delete iActionDeleteResource;
    delete iActionStopTransferResource;
    delete iActionGetTransferProgress;
    delete iActionCreateReference;
}

void CpProxyUpnpOrgContentDirectory2C::SyncGetSearchCapabilities(Brh& aSearchCaps)
{
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory2C sync(*this, aSearchCaps);
    BeginGetSearchCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginGetSearchCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSearchCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSearchCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndGetSearchCapabilities(IAsync& aAsync, Brh& aSearchCaps)
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

void CpProxyUpnpOrgContentDirectory2C::SyncGetSortCapabilities(Brh& aSortCaps)
{
    SyncGetSortCapabilitiesUpnpOrgContentDirectory2C sync(*this, aSortCaps);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps)
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

void CpProxyUpnpOrgContentDirectory2C::SyncGetSortExtensionCapabilities(Brh& aSortExtensionCaps)
{
    SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2C sync(*this, aSortExtensionCaps);
    BeginGetSortExtensionCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginGetSortExtensionCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSortExtensionCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortExtensionCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndGetSortExtensionCapabilities(IAsync& aAsync, Brh& aSortExtensionCaps)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSortExtensionCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSortExtensionCaps);
}

void CpProxyUpnpOrgContentDirectory2C::SyncGetFeatureList(Brh& aFeatureList)
{
    SyncGetFeatureListUpnpOrgContentDirectory2C sync(*this, aFeatureList);
    BeginGetFeatureList(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginGetFeatureList(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetFeatureList, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetFeatureList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndGetFeatureList(IAsync& aAsync, Brh& aFeatureList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetFeatureList"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aFeatureList);
}

void CpProxyUpnpOrgContentDirectory2C::SyncGetSystemUpdateID(TUint& aId)
{
    SyncGetSystemUpdateIDUpnpOrgContentDirectory2C sync(*this, aId);
    BeginGetSystemUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginGetSystemUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSystemUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSystemUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndGetSystemUpdateID(IAsync& aAsync, TUint& aId)
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

void CpProxyUpnpOrgContentDirectory2C::SyncBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseUpnpOrgContentDirectory2C sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory2C::EndBrowse(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
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

void CpProxyUpnpOrgContentDirectory2C::SyncSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncSearchUpnpOrgContentDirectory2C sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory2C::EndSearch(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
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

void CpProxyUpnpOrgContentDirectory2C::SyncCreateObject(const Brx& aContainerID, const Brx& aElements, Brh& aObjectID, Brh& aResult)
{
    SyncCreateObjectUpnpOrgContentDirectory2C sync(*this, aObjectID, aResult);
    BeginCreateObject(aContainerID, aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginCreateObject(const Brx& aContainerID, const Brx& aElements, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory2C::EndCreateObject(IAsync& aAsync, Brh& aObjectID, Brh& aResult)
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

void CpProxyUpnpOrgContentDirectory2C::SyncDestroyObject(const Brx& aObjectID)
{
    SyncDestroyObjectUpnpOrgContentDirectory2C sync(*this);
    BeginDestroyObject(aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginDestroyObject(const Brx& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDestroyObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDestroyObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndDestroyObject(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory2C::SyncUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    SyncUpdateObjectUpnpOrgContentDirectory2C sync(*this);
    BeginUpdateObject(aObjectID, aCurrentTagValue, aNewTagValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionUpdateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUpdateObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentTagValue));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewTagValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndUpdateObject(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory2C::SyncMoveObject(const Brx& aObjectID, const Brx& aNewParentID, Brh& aNewObjectID)
{
    SyncMoveObjectUpnpOrgContentDirectory2C sync(*this, aNewObjectID);
    BeginMoveObject(aObjectID, aNewParentID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginMoveObject(const Brx& aObjectID, const Brx& aNewParentID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMoveObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionMoveObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewParentID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMoveObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndMoveObject(IAsync& aAsync, Brh& aNewObjectID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("MoveObject"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aNewObjectID);
}

void CpProxyUpnpOrgContentDirectory2C::SyncImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID)
{
    SyncImportResourceUpnpOrgContentDirectory2C sync(*this, aTransferID);
    BeginImportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory2C::EndImportResource(IAsync& aAsync, TUint& aTransferID)
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

void CpProxyUpnpOrgContentDirectory2C::SyncExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID)
{
    SyncExportResourceUpnpOrgContentDirectory2C sync(*this, aTransferID);
    BeginExportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory2C::EndExportResource(IAsync& aAsync, TUint& aTransferID)
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

void CpProxyUpnpOrgContentDirectory2C::SyncDeleteResource(const Brx& aResourceURI)
{
    SyncDeleteResourceUpnpOrgContentDirectory2C sync(*this);
    BeginDeleteResource(aResourceURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginDeleteResource(const Brx& aResourceURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDeleteResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aResourceURI));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndDeleteResource(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory2C::SyncStopTransferResource(TUint aTransferID)
{
    SyncStopTransferResourceUpnpOrgContentDirectory2C sync(*this);
    BeginStopTransferResource(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginStopTransferResource(TUint aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStopTransferResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStopTransferResource->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory2C::EndStopTransferResource(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory2C::SyncGetTransferProgress(TUint aTransferID, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
{
    SyncGetTransferProgressUpnpOrgContentDirectory2C sync(*this, aTransferStatus, aTransferLength, aTransferTotal);
    BeginGetTransferProgress(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginGetTransferProgress(TUint aTransferID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory2C::EndGetTransferProgress(IAsync& aAsync, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
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

void CpProxyUpnpOrgContentDirectory2C::SyncCreateReference(const Brx& aContainerID, const Brx& aObjectID, Brh& aNewID)
{
    SyncCreateReferenceUpnpOrgContentDirectory2C sync(*this, aNewID);
    BeginCreateReference(aContainerID, aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory2C::BeginCreateReference(const Brx& aContainerID, const Brx& aObjectID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory2C::EndCreateReference(IAsync& aAsync, Brh& aNewID)
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

void CpProxyUpnpOrgContentDirectory2C::SetPropertySystemUpdateIDChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSystemUpdateIDChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgContentDirectory2C::SetPropertyContainerUpdateIDsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iContainerUpdateIDsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgContentDirectory2C::SetPropertyTransferIDsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTransferIDsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgContentDirectory2C::PropertySystemUpdateID(TUint& aSystemUpdateID) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aSystemUpdateID = iSystemUpdateID->Value();
}

void CpProxyUpnpOrgContentDirectory2C::PropertyContainerUpdateIDs(Brhz& aContainerUpdateIDs) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aContainerUpdateIDs.Set(iContainerUpdateIDs->Value());
}

void CpProxyUpnpOrgContentDirectory2C::PropertyTransferIDs(Brhz& aTransferIDs) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTransferIDs.Set(iTransferIDs->Value());
}

void CpProxyUpnpOrgContentDirectory2C::SystemUpdateIDPropertyChanged()
{
    ReportEvent(iSystemUpdateIDChanged);
}

void CpProxyUpnpOrgContentDirectory2C::ContainerUpdateIDsPropertyChanged()
{
    ReportEvent(iContainerUpdateIDsChanged);
}

void CpProxyUpnpOrgContentDirectory2C::TransferIDsPropertyChanged()
{
    ReportEvent(iTransferIDsChanged);
}


THandle STDCALL CpProxyUpnpOrgContentDirectory2Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgContentDirectory2C(aDevice);
}

void STDCALL CpProxyUpnpOrgContentDirectory2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncGetSearchCapabilities(THandle aHandle, char** aSearchCaps)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginGetSearchCapabilities(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSearchCapabilities(functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndGetSearchCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aSearchCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncGetSortCapabilities(THandle aHandle, char** aSortCaps)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginGetSortCapabilities(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSortCapabilities(functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndGetSortCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aSortCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncGetSortExtensionCapabilities(THandle aHandle, char** aSortExtensionCaps)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortExtensionCaps;
    int32_t err = 0;
    try {
        proxyC->SyncGetSortExtensionCapabilities(buf_aSortExtensionCaps);
        *aSortExtensionCaps = buf_aSortExtensionCaps.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aSortExtensionCaps = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory2BeginGetSortExtensionCapabilities(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSortExtensionCapabilities(functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndGetSortExtensionCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aSortExtensionCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSortExtensionCaps;
    *aSortExtensionCaps = NULL;
    try {
        proxyC->EndGetSortExtensionCapabilities(*async, buf_aSortExtensionCaps);
        *aSortExtensionCaps = buf_aSortExtensionCaps.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncGetFeatureList(THandle aHandle, char** aFeatureList)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFeatureList;
    int32_t err = 0;
    try {
        proxyC->SyncGetFeatureList(buf_aFeatureList);
        *aFeatureList = buf_aFeatureList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aFeatureList = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory2BeginGetFeatureList(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetFeatureList(functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndGetFeatureList(THandle aHandle, OhNetHandleAsync aAsync, char** aFeatureList)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aFeatureList;
    *aFeatureList = NULL;
    try {
        proxyC->EndGetFeatureList(*async, buf_aFeatureList);
        *aFeatureList = buf_aFeatureList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncGetSystemUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginGetSystemUpdateID(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSystemUpdateID(functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndGetSystemUpdateID(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndBrowse(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndSearch(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginCreateObject(buf_aContainerID, buf_aElements, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndCreateObject(THandle aHandle, OhNetHandleAsync aAsync, char** aObjectID, char** aResult)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncDestroyObject(THandle aHandle, const char* aObjectID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginDestroyObject(THandle aHandle, const char* aObjectID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDestroyObject(buf_aObjectID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndDestroyObject(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndUpdateObject(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncMoveObject(THandle aHandle, const char* aObjectID, const char* aNewParentID, char** aNewObjectID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewParentID(aNewParentID);
    Brh buf_aNewObjectID;
    int32_t err = 0;
    try {
        proxyC->SyncMoveObject(buf_aObjectID, buf_aNewParentID, buf_aNewObjectID);
        *aNewObjectID = buf_aNewObjectID.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aNewObjectID = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgContentDirectory2BeginMoveObject(THandle aHandle, const char* aObjectID, const char* aNewParentID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewParentID(aNewParentID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginMoveObject(buf_aObjectID, buf_aNewParentID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndMoveObject(THandle aHandle, OhNetHandleAsync aAsync, char** aNewObjectID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aNewObjectID;
    *aNewObjectID = NULL;
    try {
        proxyC->EndMoveObject(*async, buf_aNewObjectID);
        *aNewObjectID = buf_aNewObjectID.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginImportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndImportResource(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginExportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndExportResource(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncDeleteResource(THandle aHandle, const char* aResourceURI)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginDeleteResource(THandle aHandle, const char* aResourceURI, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDeleteResource(buf_aResourceURI, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndDeleteResource(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncStopTransferResource(THandle aHandle, uint32_t aTransferID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginStopTransferResource(THandle aHandle, uint32_t aTransferID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStopTransferResource(aTransferID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndStopTransferResource(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncGetTransferProgress(THandle aHandle, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginGetTransferProgress(THandle aHandle, uint32_t aTransferID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetTransferProgress(aTransferID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndGetTransferProgress(THandle aHandle, OhNetHandleAsync aAsync, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgContentDirectory2SyncCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, char** aNewID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2BeginCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginCreateReference(buf_aContainerID, buf_aObjectID, functor);
}

int32_t STDCALL CpProxyUpnpOrgContentDirectory2EndCreateReference(THandle aHandle, OhNetHandleAsync aAsync, char** aNewID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgContentDirectory2SetPropertySystemUpdateIDChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySystemUpdateIDChanged(functor);
}

void STDCALL CpProxyUpnpOrgContentDirectory2SetPropertyContainerUpdateIDsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyContainerUpdateIDsChanged(functor);
}

void STDCALL CpProxyUpnpOrgContentDirectory2SetPropertyTransferIDsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTransferIDsChanged(functor);
}

void STDCALL CpProxyUpnpOrgContentDirectory2PropertySystemUpdateID(THandle aHandle, uint32_t* aSystemUpdateID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySystemUpdateID(*aSystemUpdateID);
}

void STDCALL CpProxyUpnpOrgContentDirectory2PropertyContainerUpdateIDs(THandle aHandle, char** aContainerUpdateIDs)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aContainerUpdateIDs;
    proxyC->PropertyContainerUpdateIDs(buf_aContainerUpdateIDs);
    *aContainerUpdateIDs = buf_aContainerUpdateIDs.Transfer();
}

void STDCALL CpProxyUpnpOrgContentDirectory2PropertyTransferIDs(THandle aHandle, char** aTransferIDs)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransferIDs;
    proxyC->PropertyTransferIDs(buf_aTransferIDs);
    *aTransferIDs = buf_aTransferIDs.Transfer();
}

