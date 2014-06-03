#include "CpUpnpOrgContentDirectory3.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncGetSearchCapabilitiesUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aSearchCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSearchCapabilitiesUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iSearchCaps;
};

SyncGetSearchCapabilitiesUpnpOrgContentDirectory3::SyncGetSearchCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aSearchCaps)
    : iService(aProxy)
    , iSearchCaps(aSearchCaps)
{
}

void SyncGetSearchCapabilitiesUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSearchCapabilities(aAsync, iSearchCaps);
}


class SyncGetSortCapabilitiesUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aSortCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iSortCaps;
};

SyncGetSortCapabilitiesUpnpOrgContentDirectory3::SyncGetSortCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aSortCaps)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
{
}

void SyncGetSortCapabilitiesUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps);
}


class SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aSortExtensionCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iSortExtensionCaps;
};

SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3::SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aSortExtensionCaps)
    : iService(aProxy)
    , iSortExtensionCaps(aSortExtensionCaps)
{
}

void SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortExtensionCapabilities(aAsync, iSortExtensionCaps);
}


class SyncGetFeatureListUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncGetFeatureListUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aFeatureList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetFeatureListUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iFeatureList;
};

SyncGetFeatureListUpnpOrgContentDirectory3::SyncGetFeatureListUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aFeatureList)
    : iService(aProxy)
    , iFeatureList(aFeatureList)
{
}

void SyncGetFeatureListUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetFeatureList(aAsync, iFeatureList);
}


class SyncGetSystemUpdateIDUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncGetSystemUpdateIDUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, TUint& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSystemUpdateIDUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    TUint& iId;
};

SyncGetSystemUpdateIDUpnpOrgContentDirectory3::SyncGetSystemUpdateIDUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, TUint& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetSystemUpdateIDUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSystemUpdateID(aAsync, iId);
}


class SyncGetServiceResetTokenUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncGetServiceResetTokenUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aResetToken);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetServiceResetTokenUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iResetToken;
};

SyncGetServiceResetTokenUpnpOrgContentDirectory3::SyncGetServiceResetTokenUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aResetToken)
    : iService(aProxy)
    , iResetToken(aResetToken)
{
}

void SyncGetServiceResetTokenUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetServiceResetToken(aAsync, iResetToken);
}


class SyncBrowseUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncBrowseUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseUpnpOrgContentDirectory3::SyncBrowseUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowse(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncSearchUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncSearchUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSearchUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncSearchUpnpOrgContentDirectory3::SyncSearchUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncSearchUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSearch(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateObjectUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncCreateObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aObjectID, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateObjectUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iObjectID;
    Brh& iResult;
};

SyncCreateObjectUpnpOrgContentDirectory3::SyncCreateObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aObjectID, Brh& aResult)
    : iService(aProxy)
    , iObjectID(aObjectID)
    , iResult(aResult)
{
}

void SyncCreateObjectUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateObject(aAsync, iObjectID, iResult);
}


class SyncDestroyObjectUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncDestroyObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDestroyObjectUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
};

SyncDestroyObjectUpnpOrgContentDirectory3::SyncDestroyObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy)
    : iService(aProxy)
{
}

void SyncDestroyObjectUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndDestroyObject(aAsync);
}


class SyncUpdateObjectUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncUpdateObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUpdateObjectUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
};

SyncUpdateObjectUpnpOrgContentDirectory3::SyncUpdateObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy)
    : iService(aProxy)
{
}

void SyncUpdateObjectUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndUpdateObject(aAsync);
}


class SyncMoveObjectUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncMoveObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aNewObjectID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMoveObjectUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iNewObjectID;
};

SyncMoveObjectUpnpOrgContentDirectory3::SyncMoveObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aNewObjectID)
    : iService(aProxy)
    , iNewObjectID(aNewObjectID)
{
}

void SyncMoveObjectUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndMoveObject(aAsync, iNewObjectID);
}


class SyncImportResourceUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncImportResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, TUint& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncImportResourceUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    TUint& iTransferID;
};

SyncImportResourceUpnpOrgContentDirectory3::SyncImportResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, TUint& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncImportResourceUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndImportResource(aAsync, iTransferID);
}


class SyncExportResourceUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncExportResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, TUint& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncExportResourceUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    TUint& iTransferID;
};

SyncExportResourceUpnpOrgContentDirectory3::SyncExportResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, TUint& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncExportResourceUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndExportResource(aAsync, iTransferID);
}


class SyncDeleteResourceUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncDeleteResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteResourceUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
};

SyncDeleteResourceUpnpOrgContentDirectory3::SyncDeleteResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteResourceUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteResource(aAsync);
}


class SyncStopTransferResourceUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncStopTransferResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopTransferResourceUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
};

SyncStopTransferResourceUpnpOrgContentDirectory3::SyncStopTransferResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy)
    : iService(aProxy)
{
}

void SyncStopTransferResourceUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopTransferResource(aAsync);
}


class SyncGetTransferProgressUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncGetTransferProgressUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransferProgressUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iTransferStatus;
    Brh& iTransferLength;
    Brh& iTransferTotal;
};

SyncGetTransferProgressUpnpOrgContentDirectory3::SyncGetTransferProgressUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
    : iService(aProxy)
    , iTransferStatus(aTransferStatus)
    , iTransferLength(aTransferLength)
    , iTransferTotal(aTransferTotal)
{
}

void SyncGetTransferProgressUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransferProgress(aAsync, iTransferStatus, iTransferLength, iTransferTotal);
}


class SyncCreateReferenceUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncCreateReferenceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aNewID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateReferenceUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iNewID;
};

SyncCreateReferenceUpnpOrgContentDirectory3::SyncCreateReferenceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aNewID)
    : iService(aProxy)
    , iNewID(aNewID)
{
}

void SyncCreateReferenceUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateReference(aAsync, iNewID);
}


class SyncFreeFormQueryUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncFreeFormQueryUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aQueryResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncFreeFormQueryUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iQueryResult;
    TUint& iUpdateID;
};

SyncFreeFormQueryUpnpOrgContentDirectory3::SyncFreeFormQueryUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aQueryResult, TUint& aUpdateID)
    : iService(aProxy)
    , iQueryResult(aQueryResult)
    , iUpdateID(aUpdateID)
{
}

void SyncFreeFormQueryUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndFreeFormQuery(aAsync, iQueryResult, iUpdateID);
}


class SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3 : public SyncProxyAction
{
public:
    SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aFFQCapabilities);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3() {}
private:
    CpProxyUpnpOrgContentDirectory3& iService;
    Brh& iFFQCapabilities;
};

SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3::SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3& aProxy, Brh& aFFQCapabilities)
    : iService(aProxy)
    , iFFQCapabilities(aFFQCapabilities)
{
}

void SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetFreeFormQueryCapabilities(aAsync, iFFQCapabilities);
}


CpProxyUpnpOrgContentDirectory3::CpProxyUpnpOrgContentDirectory3(CpDevice& aDevice)
    : CpProxy("schemas-upnp-org", "ContentDirectory", 3, aDevice.Device())
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

    iActionGetServiceResetToken = new Action("GetServiceResetToken");
    param = new OpenHome::Net::ParameterString("ResetToken");
    iActionGetServiceResetToken->AddOutputParameter(param);

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

    iActionFreeFormQuery = new Action("FreeFormQuery");
    param = new OpenHome::Net::ParameterString("ContainerID");
    iActionFreeFormQuery->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CDSView");
    iActionFreeFormQuery->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("QueryRequest");
    iActionFreeFormQuery->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("QueryResult");
    iActionFreeFormQuery->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionFreeFormQuery->AddOutputParameter(param);

    iActionGetFreeFormQueryCapabilities = new Action("GetFreeFormQueryCapabilities");
    param = new OpenHome::Net::ParameterString("FFQCapabilities");
    iActionGetFreeFormQueryCapabilities->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory3::SystemUpdateIDPropertyChanged);
    iSystemUpdateID = new PropertyUint(aDevice.Device().GetCpStack().Env(), "SystemUpdateID", functor);
    AddProperty(iSystemUpdateID);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory3::ContainerUpdateIDsPropertyChanged);
    iContainerUpdateIDs = new PropertyString(aDevice.Device().GetCpStack().Env(), "ContainerUpdateIDs", functor);
    AddProperty(iContainerUpdateIDs);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory3::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory3::TransferIDsPropertyChanged);
    iTransferIDs = new PropertyString(aDevice.Device().GetCpStack().Env(), "TransferIDs", functor);
    AddProperty(iTransferIDs);
}

CpProxyUpnpOrgContentDirectory3::~CpProxyUpnpOrgContentDirectory3()
{
    DestroyService();
    delete iActionGetSearchCapabilities;
    delete iActionGetSortCapabilities;
    delete iActionGetSortExtensionCapabilities;
    delete iActionGetFeatureList;
    delete iActionGetSystemUpdateID;
    delete iActionGetServiceResetToken;
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
    delete iActionFreeFormQuery;
    delete iActionGetFreeFormQueryCapabilities;
}

void CpProxyUpnpOrgContentDirectory3::SyncGetSearchCapabilities(Brh& aSearchCaps)
{
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory3 sync(*this, aSearchCaps);
    BeginGetSearchCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginGetSearchCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSearchCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSearchCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndGetSearchCapabilities(IAsync& aAsync, Brh& aSearchCaps)
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

void CpProxyUpnpOrgContentDirectory3::SyncGetSortCapabilities(Brh& aSortCaps)
{
    SyncGetSortCapabilitiesUpnpOrgContentDirectory3 sync(*this, aSortCaps);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps)
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

void CpProxyUpnpOrgContentDirectory3::SyncGetSortExtensionCapabilities(Brh& aSortExtensionCaps)
{
    SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3 sync(*this, aSortExtensionCaps);
    BeginGetSortExtensionCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginGetSortExtensionCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortExtensionCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortExtensionCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndGetSortExtensionCapabilities(IAsync& aAsync, Brh& aSortExtensionCaps)
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

void CpProxyUpnpOrgContentDirectory3::SyncGetFeatureList(Brh& aFeatureList)
{
    SyncGetFeatureListUpnpOrgContentDirectory3 sync(*this, aFeatureList);
    BeginGetFeatureList(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginGetFeatureList(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetFeatureList, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetFeatureList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndGetFeatureList(IAsync& aAsync, Brh& aFeatureList)
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

void CpProxyUpnpOrgContentDirectory3::SyncGetSystemUpdateID(TUint& aId)
{
    SyncGetSystemUpdateIDUpnpOrgContentDirectory3 sync(*this, aId);
    BeginGetSystemUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginGetSystemUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSystemUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSystemUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndGetSystemUpdateID(IAsync& aAsync, TUint& aId)
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

void CpProxyUpnpOrgContentDirectory3::SyncGetServiceResetToken(Brh& aResetToken)
{
    SyncGetServiceResetTokenUpnpOrgContentDirectory3 sync(*this, aResetToken);
    BeginGetServiceResetToken(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginGetServiceResetToken(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetServiceResetToken, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetServiceResetToken->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndGetServiceResetToken(IAsync& aAsync, Brh& aResetToken)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetServiceResetToken"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResetToken);
}

void CpProxyUpnpOrgContentDirectory3::SyncBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseUpnpOrgContentDirectory3 sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowse, aFunctor);
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndBrowse(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
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

void CpProxyUpnpOrgContentDirectory3::SyncSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncSearchUpnpOrgContentDirectory3 sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSearch, aFunctor);
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndSearch(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
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

void CpProxyUpnpOrgContentDirectory3::SyncCreateObject(const Brx& aContainerID, const Brx& aElements, Brh& aObjectID, Brh& aResult)
{
    SyncCreateObjectUpnpOrgContentDirectory3 sync(*this, aObjectID, aResult);
    BeginCreateObject(aContainerID, aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginCreateObject(const Brx& aContainerID, const Brx& aElements, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aElements));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndCreateObject(IAsync& aAsync, Brh& aObjectID, Brh& aResult)
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

void CpProxyUpnpOrgContentDirectory3::SyncDestroyObject(const Brx& aObjectID)
{
    SyncDestroyObjectUpnpOrgContentDirectory3 sync(*this);
    BeginDestroyObject(aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginDestroyObject(const Brx& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDestroyObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDestroyObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndDestroyObject(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory3::SyncUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    SyncUpdateObjectUpnpOrgContentDirectory3 sync(*this);
    BeginUpdateObject(aObjectID, aCurrentTagValue, aNewTagValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionUpdateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUpdateObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aCurrentTagValue));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewTagValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndUpdateObject(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory3::SyncMoveObject(const Brx& aObjectID, const Brx& aNewParentID, Brh& aNewObjectID)
{
    SyncMoveObjectUpnpOrgContentDirectory3 sync(*this, aNewObjectID);
    BeginMoveObject(aObjectID, aNewParentID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginMoveObject(const Brx& aObjectID, const Brx& aNewParentID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMoveObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionMoveObject->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aNewParentID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMoveObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndMoveObject(IAsync& aAsync, Brh& aNewObjectID)
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

void CpProxyUpnpOrgContentDirectory3::SyncImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID)
{
    SyncImportResourceUpnpOrgContentDirectory3 sync(*this, aTransferID);
    BeginImportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionImportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionImportResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSourceURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDestinationURI));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndImportResource(IAsync& aAsync, TUint& aTransferID)
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

void CpProxyUpnpOrgContentDirectory3::SyncExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID)
{
    SyncExportResourceUpnpOrgContentDirectory3 sync(*this, aTransferID);
    BeginExportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionExportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionExportResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSourceURI));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDestinationURI));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionExportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndExportResource(IAsync& aAsync, TUint& aTransferID)
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

void CpProxyUpnpOrgContentDirectory3::SyncDeleteResource(const Brx& aResourceURI)
{
    SyncDeleteResourceUpnpOrgContentDirectory3 sync(*this);
    BeginDeleteResource(aResourceURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginDeleteResource(const Brx& aResourceURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteResource->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aResourceURI));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndDeleteResource(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory3::SyncStopTransferResource(TUint aTransferID)
{
    SyncStopTransferResourceUpnpOrgContentDirectory3 sync(*this);
    BeginStopTransferResource(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginStopTransferResource(TUint aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStopTransferResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStopTransferResource->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndStopTransferResource(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory3::SyncGetTransferProgress(TUint aTransferID, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
{
    SyncGetTransferProgressUpnpOrgContentDirectory3 sync(*this, aTransferStatus, aTransferLength, aTransferTotal);
    BeginGetTransferProgress(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginGetTransferProgress(TUint aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetTransferProgress, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetTransferProgress->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTransferProgress->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndGetTransferProgress(IAsync& aAsync, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal)
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

void CpProxyUpnpOrgContentDirectory3::SyncCreateReference(const Brx& aContainerID, const Brx& aObjectID, Brh& aNewID)
{
    SyncCreateReferenceUpnpOrgContentDirectory3 sync(*this, aNewID);
    BeginCreateReference(aContainerID, aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginCreateReference(const Brx& aContainerID, const Brx& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateReference, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateReference->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aObjectID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateReference->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndCreateReference(IAsync& aAsync, Brh& aNewID)
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

void CpProxyUpnpOrgContentDirectory3::SyncFreeFormQuery(const Brx& aContainerID, TUint aCDSView, const Brx& aQueryRequest, Brh& aQueryResult, TUint& aUpdateID)
{
    SyncFreeFormQueryUpnpOrgContentDirectory3 sync(*this, aQueryResult, aUpdateID);
    BeginFreeFormQuery(aContainerID, aCDSView, aQueryRequest, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginFreeFormQuery(const Brx& aContainerID, TUint aCDSView, const Brx& aQueryRequest, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionFreeFormQuery, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionFreeFormQuery->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aContainerID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aCDSView));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aQueryRequest));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionFreeFormQuery->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndFreeFormQuery(IAsync& aAsync, Brh& aQueryResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("FreeFormQuery"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aQueryResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory3::SyncGetFreeFormQueryCapabilities(Brh& aFFQCapabilities)
{
    SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3 sync(*this, aFFQCapabilities);
    BeginGetFreeFormQueryCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3::BeginGetFreeFormQueryCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetFreeFormQueryCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetFreeFormQueryCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3::EndGetFreeFormQueryCapabilities(IAsync& aAsync, Brh& aFFQCapabilities)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetFreeFormQueryCapabilities"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aFFQCapabilities);
}

void CpProxyUpnpOrgContentDirectory3::SetPropertySystemUpdateIDChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSystemUpdateIDChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory3::SetPropertyContainerUpdateIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iContainerUpdateIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory3::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory3::SetPropertyTransferIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransferIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory3::PropertySystemUpdateID(TUint& aSystemUpdateID) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSystemUpdateID = iSystemUpdateID->Value();
}

void CpProxyUpnpOrgContentDirectory3::PropertyContainerUpdateIDs(Brhz& aContainerUpdateIDs) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aContainerUpdateIDs.Set(iContainerUpdateIDs->Value());
}

void CpProxyUpnpOrgContentDirectory3::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgContentDirectory3::PropertyTransferIDs(Brhz& aTransferIDs) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTransferIDs.Set(iTransferIDs->Value());
}

void CpProxyUpnpOrgContentDirectory3::SystemUpdateIDPropertyChanged()
{
    ReportEvent(iSystemUpdateIDChanged);
}

void CpProxyUpnpOrgContentDirectory3::ContainerUpdateIDsPropertyChanged()
{
    ReportEvent(iContainerUpdateIDsChanged);
}

void CpProxyUpnpOrgContentDirectory3::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

void CpProxyUpnpOrgContentDirectory3::TransferIDsPropertyChanged()
{
    ReportEvent(iTransferIDsChanged);
}

