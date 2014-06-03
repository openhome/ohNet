#include "CpUpnpOrgContentDirectory3.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncGetSearchCapabilitiesUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aSearchCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSearchCapabilitiesUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iSearchCaps;
};

SyncGetSearchCapabilitiesUpnpOrgContentDirectory3Cpp::SyncGetSearchCapabilitiesUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aSearchCaps)
    : iService(aProxy)
    , iSearchCaps(aSearchCaps)
{
}

void SyncGetSearchCapabilitiesUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSearchCapabilities(aAsync, iSearchCaps);
}


class SyncGetSortCapabilitiesUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aSortCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iSortCaps;
};

SyncGetSortCapabilitiesUpnpOrgContentDirectory3Cpp::SyncGetSortCapabilitiesUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aSortCaps)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
{
}

void SyncGetSortCapabilitiesUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps);
}


class SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aSortExtensionCaps);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iSortExtensionCaps;
};

SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3Cpp::SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aSortExtensionCaps)
    : iService(aProxy)
    , iSortExtensionCaps(aSortExtensionCaps)
{
}

void SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortExtensionCapabilities(aAsync, iSortExtensionCaps);
}


class SyncGetFeatureListUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncGetFeatureListUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aFeatureList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetFeatureListUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iFeatureList;
};

SyncGetFeatureListUpnpOrgContentDirectory3Cpp::SyncGetFeatureListUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aFeatureList)
    : iService(aProxy)
    , iFeatureList(aFeatureList)
{
}

void SyncGetFeatureListUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetFeatureList(aAsync, iFeatureList);
}


class SyncGetSystemUpdateIDUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncGetSystemUpdateIDUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, uint32_t& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSystemUpdateIDUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    uint32_t& iId;
};

SyncGetSystemUpdateIDUpnpOrgContentDirectory3Cpp::SyncGetSystemUpdateIDUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, uint32_t& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetSystemUpdateIDUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSystemUpdateID(aAsync, iId);
}


class SyncGetServiceResetTokenUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncGetServiceResetTokenUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aResetToken);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetServiceResetTokenUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iResetToken;
};

SyncGetServiceResetTokenUpnpOrgContentDirectory3Cpp::SyncGetServiceResetTokenUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aResetToken)
    : iService(aProxy)
    , iResetToken(aResetToken)
{
}

void SyncGetServiceResetTokenUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetServiceResetToken(aAsync, iResetToken);
}


class SyncBrowseUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncBrowseUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncBrowseUpnpOrgContentDirectory3Cpp::SyncBrowseUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowse(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncSearchUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncSearchUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSearchUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncSearchUpnpOrgContentDirectory3Cpp::SyncSearchUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncSearchUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSearch(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateObjectUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncCreateObjectUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aObjectID, std::string& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateObjectUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iObjectID;
    std::string& iResult;
};

SyncCreateObjectUpnpOrgContentDirectory3Cpp::SyncCreateObjectUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aObjectID, std::string& aResult)
    : iService(aProxy)
    , iObjectID(aObjectID)
    , iResult(aResult)
{
}

void SyncCreateObjectUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateObject(aAsync, iObjectID, iResult);
}


class SyncDestroyObjectUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncDestroyObjectUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDestroyObjectUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
};

SyncDestroyObjectUpnpOrgContentDirectory3Cpp::SyncDestroyObjectUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDestroyObjectUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDestroyObject(aAsync);
}


class SyncUpdateObjectUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncUpdateObjectUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUpdateObjectUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
};

SyncUpdateObjectUpnpOrgContentDirectory3Cpp::SyncUpdateObjectUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncUpdateObjectUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndUpdateObject(aAsync);
}


class SyncMoveObjectUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncMoveObjectUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aNewObjectID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMoveObjectUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iNewObjectID;
};

SyncMoveObjectUpnpOrgContentDirectory3Cpp::SyncMoveObjectUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aNewObjectID)
    : iService(aProxy)
    , iNewObjectID(aNewObjectID)
{
}

void SyncMoveObjectUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndMoveObject(aAsync, iNewObjectID);
}


class SyncImportResourceUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncImportResourceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, uint32_t& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncImportResourceUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    uint32_t& iTransferID;
};

SyncImportResourceUpnpOrgContentDirectory3Cpp::SyncImportResourceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, uint32_t& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncImportResourceUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndImportResource(aAsync, iTransferID);
}


class SyncExportResourceUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncExportResourceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, uint32_t& aTransferID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncExportResourceUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    uint32_t& iTransferID;
};

SyncExportResourceUpnpOrgContentDirectory3Cpp::SyncExportResourceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, uint32_t& aTransferID)
    : iService(aProxy)
    , iTransferID(aTransferID)
{
}

void SyncExportResourceUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndExportResource(aAsync, iTransferID);
}


class SyncDeleteResourceUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncDeleteResourceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteResourceUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
};

SyncDeleteResourceUpnpOrgContentDirectory3Cpp::SyncDeleteResourceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteResourceUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteResource(aAsync);
}


class SyncStopTransferResourceUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncStopTransferResourceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopTransferResourceUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
};

SyncStopTransferResourceUpnpOrgContentDirectory3Cpp::SyncStopTransferResourceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStopTransferResourceUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopTransferResource(aAsync);
}


class SyncGetTransferProgressUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncGetTransferProgressUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTransferProgressUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iTransferStatus;
    std::string& iTransferLength;
    std::string& iTransferTotal;
};

SyncGetTransferProgressUpnpOrgContentDirectory3Cpp::SyncGetTransferProgressUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal)
    : iService(aProxy)
    , iTransferStatus(aTransferStatus)
    , iTransferLength(aTransferLength)
    , iTransferTotal(aTransferTotal)
{
}

void SyncGetTransferProgressUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTransferProgress(aAsync, iTransferStatus, iTransferLength, iTransferTotal);
}


class SyncCreateReferenceUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncCreateReferenceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aNewID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateReferenceUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iNewID;
};

SyncCreateReferenceUpnpOrgContentDirectory3Cpp::SyncCreateReferenceUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aNewID)
    : iService(aProxy)
    , iNewID(aNewID)
{
}

void SyncCreateReferenceUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateReference(aAsync, iNewID);
}


class SyncFreeFormQueryUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncFreeFormQueryUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aQueryResult, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncFreeFormQueryUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iQueryResult;
    uint32_t& iUpdateID;
};

SyncFreeFormQueryUpnpOrgContentDirectory3Cpp::SyncFreeFormQueryUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aQueryResult, uint32_t& aUpdateID)
    : iService(aProxy)
    , iQueryResult(aQueryResult)
    , iUpdateID(aUpdateID)
{
}

void SyncFreeFormQueryUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndFreeFormQuery(aAsync, iQueryResult, iUpdateID);
}


class SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3Cpp : public SyncProxyAction
{
public:
    SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aFFQCapabilities);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3Cpp() {}
private:
    CpProxyUpnpOrgContentDirectory3Cpp& iService;
    std::string& iFFQCapabilities;
};

SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3Cpp::SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3Cpp(CpProxyUpnpOrgContentDirectory3Cpp& aProxy, std::string& aFFQCapabilities)
    : iService(aProxy)
    , iFFQCapabilities(aFFQCapabilities)
{
}

void SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetFreeFormQueryCapabilities(aAsync, iFFQCapabilities);
}


CpProxyUpnpOrgContentDirectory3Cpp::CpProxyUpnpOrgContentDirectory3Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory3Cpp::SystemUpdateIDPropertyChanged);
    iSystemUpdateID = new PropertyUint(aDevice.Device().GetCpStack().Env(), "SystemUpdateID", functor);
    AddProperty(iSystemUpdateID);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory3Cpp::ContainerUpdateIDsPropertyChanged);
    iContainerUpdateIDs = new PropertyString(aDevice.Device().GetCpStack().Env(), "ContainerUpdateIDs", functor);
    AddProperty(iContainerUpdateIDs);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory3Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgContentDirectory3Cpp::TransferIDsPropertyChanged);
    iTransferIDs = new PropertyString(aDevice.Device().GetCpStack().Env(), "TransferIDs", functor);
    AddProperty(iTransferIDs);
}

CpProxyUpnpOrgContentDirectory3Cpp::~CpProxyUpnpOrgContentDirectory3Cpp()
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

void CpProxyUpnpOrgContentDirectory3Cpp::SyncGetSearchCapabilities(std::string& aSearchCaps)
{
    SyncGetSearchCapabilitiesUpnpOrgContentDirectory3Cpp sync(*this, aSearchCaps);
    BeginGetSearchCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginGetSearchCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSearchCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSearchCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndGetSearchCapabilities(IAsync& aAsync, std::string& aSearchCaps)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSearchCaps.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncGetSortCapabilities(std::string& aSortCaps)
{
    SyncGetSortCapabilitiesUpnpOrgContentDirectory3Cpp sync(*this, aSortCaps);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndGetSortCapabilities(IAsync& aAsync, std::string& aSortCaps)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSortCaps.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncGetSortExtensionCapabilities(std::string& aSortExtensionCaps)
{
    SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3Cpp sync(*this, aSortExtensionCaps);
    BeginGetSortExtensionCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginGetSortExtensionCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortExtensionCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortExtensionCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndGetSortExtensionCapabilities(IAsync& aAsync, std::string& aSortExtensionCaps)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSortExtensionCaps.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncGetFeatureList(std::string& aFeatureList)
{
    SyncGetFeatureListUpnpOrgContentDirectory3Cpp sync(*this, aFeatureList);
    BeginGetFeatureList(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginGetFeatureList(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetFeatureList, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetFeatureList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndGetFeatureList(IAsync& aAsync, std::string& aFeatureList)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aFeatureList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncGetSystemUpdateID(uint32_t& aId)
{
    SyncGetSystemUpdateIDUpnpOrgContentDirectory3Cpp sync(*this, aId);
    BeginGetSystemUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginGetSystemUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSystemUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSystemUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndGetSystemUpdateID(IAsync& aAsync, uint32_t& aId)
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

void CpProxyUpnpOrgContentDirectory3Cpp::SyncGetServiceResetToken(std::string& aResetToken)
{
    SyncGetServiceResetTokenUpnpOrgContentDirectory3Cpp sync(*this, aResetToken);
    BeginGetServiceResetToken(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginGetServiceResetToken(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetServiceResetToken, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetServiceResetToken->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndGetServiceResetToken(IAsync& aAsync, std::string& aResetToken)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResetToken.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    SyncBrowseUpnpOrgContentDirectory3Cpp sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowse, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowse->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aBrowseFlag.c_str(), (TUint)aBrowseFlag.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), (TUint)aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowse->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndBrowse(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    SyncSearchUpnpOrgContentDirectory3Cpp sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSearch, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSearch->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aSearchCriteria.c_str(), (TUint)aSearchCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    {
        Brn buf((const TByte*)aSortCriteria.c_str(), (TUint)aSortCriteria.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSearch->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndSearch(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncCreateObject(const std::string& aContainerID, const std::string& aElements, std::string& aObjectID, std::string& aResult)
{
    SyncCreateObjectUpnpOrgContentDirectory3Cpp sync(*this, aObjectID, aResult);
    BeginCreateObject(aContainerID, aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginCreateObject(const std::string& aContainerID, const std::string& aElements, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateObject->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aElements.c_str(), (TUint)aElements.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndCreateObject(IAsync& aAsync, std::string& aObjectID, std::string& aResult)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aObjectID.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncDestroyObject(const std::string& aObjectID)
{
    SyncDestroyObjectUpnpOrgContentDirectory3Cpp sync(*this);
    BeginDestroyObject(aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginDestroyObject(const std::string& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDestroyObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDestroyObject->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndDestroyObject(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory3Cpp::SyncUpdateObject(const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue)
{
    SyncUpdateObjectUpnpOrgContentDirectory3Cpp sync(*this);
    BeginUpdateObject(aObjectID, aCurrentTagValue, aNewTagValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginUpdateObject(const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionUpdateObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUpdateObject->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aCurrentTagValue.c_str(), (TUint)aCurrentTagValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aNewTagValue.c_str(), (TUint)aNewTagValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndUpdateObject(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory3Cpp::SyncMoveObject(const std::string& aObjectID, const std::string& aNewParentID, std::string& aNewObjectID)
{
    SyncMoveObjectUpnpOrgContentDirectory3Cpp sync(*this, aNewObjectID);
    BeginMoveObject(aObjectID, aNewParentID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginMoveObject(const std::string& aObjectID, const std::string& aNewParentID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMoveObject, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionMoveObject->InputParameters();
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aNewParentID.c_str(), (TUint)aNewParentID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMoveObject->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndMoveObject(IAsync& aAsync, std::string& aNewObjectID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aNewObjectID.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncImportResource(const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID)
{
    SyncImportResourceUpnpOrgContentDirectory3Cpp sync(*this, aTransferID);
    BeginImportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginImportResource(const std::string& aSourceURI, const std::string& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionImportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionImportResource->InputParameters();
    {
        Brn buf((const TByte*)aSourceURI.c_str(), (TUint)aSourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDestinationURI.c_str(), (TUint)aDestinationURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionImportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndImportResource(IAsync& aAsync, uint32_t& aTransferID)
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

void CpProxyUpnpOrgContentDirectory3Cpp::SyncExportResource(const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID)
{
    SyncExportResourceUpnpOrgContentDirectory3Cpp sync(*this, aTransferID);
    BeginExportResource(aSourceURI, aDestinationURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginExportResource(const std::string& aSourceURI, const std::string& aDestinationURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionExportResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionExportResource->InputParameters();
    {
        Brn buf((const TByte*)aSourceURI.c_str(), (TUint)aSourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aDestinationURI.c_str(), (TUint)aDestinationURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionExportResource->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndExportResource(IAsync& aAsync, uint32_t& aTransferID)
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

void CpProxyUpnpOrgContentDirectory3Cpp::SyncDeleteResource(const std::string& aResourceURI)
{
    SyncDeleteResourceUpnpOrgContentDirectory3Cpp sync(*this);
    BeginDeleteResource(aResourceURI, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginDeleteResource(const std::string& aResourceURI, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteResource->InputParameters();
    {
        Brn buf((const TByte*)aResourceURI.c_str(), (TUint)aResourceURI.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndDeleteResource(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory3Cpp::SyncStopTransferResource(uint32_t aTransferID)
{
    SyncStopTransferResourceUpnpOrgContentDirectory3Cpp sync(*this);
    BeginStopTransferResource(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginStopTransferResource(uint32_t aTransferID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStopTransferResource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStopTransferResource->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aTransferID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndStopTransferResource(IAsync& aAsync)
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

void CpProxyUpnpOrgContentDirectory3Cpp::SyncGetTransferProgress(uint32_t aTransferID, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal)
{
    SyncGetTransferProgressUpnpOrgContentDirectory3Cpp sync(*this, aTransferStatus, aTransferLength, aTransferTotal);
    BeginGetTransferProgress(aTransferID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginGetTransferProgress(uint32_t aTransferID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgContentDirectory3Cpp::EndGetTransferProgress(IAsync& aAsync, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTransferStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTransferLength.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aTransferTotal.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncCreateReference(const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID)
{
    SyncCreateReferenceUpnpOrgContentDirectory3Cpp sync(*this, aNewID);
    BeginCreateReference(aContainerID, aObjectID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginCreateReference(const std::string& aContainerID, const std::string& aObjectID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateReference, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateReference->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aObjectID.c_str(), (TUint)aObjectID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateReference->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndCreateReference(IAsync& aAsync, std::string& aNewID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aNewID.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncFreeFormQuery(const std::string& aContainerID, uint32_t aCDSView, const std::string& aQueryRequest, std::string& aQueryResult, uint32_t& aUpdateID)
{
    SyncFreeFormQueryUpnpOrgContentDirectory3Cpp sync(*this, aQueryResult, aUpdateID);
    BeginFreeFormQuery(aContainerID, aCDSView, aQueryRequest, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginFreeFormQuery(const std::string& aContainerID, uint32_t aCDSView, const std::string& aQueryRequest, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionFreeFormQuery, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionFreeFormQuery->InputParameters();
    {
        Brn buf((const TByte*)aContainerID.c_str(), (TUint)aContainerID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aCDSView));
    {
        Brn buf((const TByte*)aQueryRequest.c_str(), (TUint)aQueryRequest.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionFreeFormQuery->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndFreeFormQuery(IAsync& aAsync, std::string& aQueryResult, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aQueryResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgContentDirectory3Cpp::SyncGetFreeFormQueryCapabilities(std::string& aFFQCapabilities)
{
    SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3Cpp sync(*this, aFFQCapabilities);
    BeginGetFreeFormQueryCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgContentDirectory3Cpp::BeginGetFreeFormQueryCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetFreeFormQueryCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetFreeFormQueryCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgContentDirectory3Cpp::EndGetFreeFormQueryCapabilities(IAsync& aAsync, std::string& aFFQCapabilities)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aFFQCapabilities.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgContentDirectory3Cpp::SetPropertySystemUpdateIDChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSystemUpdateIDChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory3Cpp::SetPropertyContainerUpdateIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iContainerUpdateIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory3Cpp::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory3Cpp::SetPropertyTransferIDsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransferIDsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgContentDirectory3Cpp::PropertySystemUpdateID(uint32_t& aSystemUpdateID) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSystemUpdateID = iSystemUpdateID->Value();
}

void CpProxyUpnpOrgContentDirectory3Cpp::PropertyContainerUpdateIDs(std::string& aContainerUpdateIDs) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iContainerUpdateIDs->Value();
    aContainerUpdateIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory3Cpp::PropertyLastChange(std::string& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory3Cpp::PropertyTransferIDs(std::string& aTransferIDs) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTransferIDs->Value();
    aTransferIDs.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgContentDirectory3Cpp::SystemUpdateIDPropertyChanged()
{
    ReportEvent(iSystemUpdateIDChanged);
}

void CpProxyUpnpOrgContentDirectory3Cpp::ContainerUpdateIDsPropertyChanged()
{
    ReportEvent(iContainerUpdateIDsChanged);
}

void CpProxyUpnpOrgContentDirectory3Cpp::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

void CpProxyUpnpOrgContentDirectory3Cpp::TransferIDsPropertyChanged()
{
    ReportEvent(iTransferIDsChanged);
}

