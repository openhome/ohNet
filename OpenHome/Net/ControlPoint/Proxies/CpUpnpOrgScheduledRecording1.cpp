#include "CpUpnpOrgScheduledRecording1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncGetSortCapabilitiesUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aSortCaps, TUint& aSortLevelCap);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iSortCaps;
    TUint& iSortLevelCap;
};

SyncGetSortCapabilitiesUpnpOrgScheduledRecording1::SyncGetSortCapabilitiesUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aSortCaps, TUint& aSortLevelCap)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
    , iSortLevelCap(aSortLevelCap)
{
}

void SyncGetSortCapabilitiesUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps, iSortLevelCap);
}


class SyncGetPropertyListUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncGetPropertyListUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aPropertyList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPropertyListUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iPropertyList;
};

SyncGetPropertyListUpnpOrgScheduledRecording1::SyncGetPropertyListUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aPropertyList)
    : iService(aProxy)
    , iPropertyList(aPropertyList)
{
}

void SyncGetPropertyListUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPropertyList(aAsync, iPropertyList);
}


class SyncGetAllowedValuesUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncGetAllowedValuesUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aPropertyInfo);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetAllowedValuesUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iPropertyInfo;
};

SyncGetAllowedValuesUpnpOrgScheduledRecording1::SyncGetAllowedValuesUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aPropertyInfo)
    : iService(aProxy)
    , iPropertyInfo(aPropertyInfo)
{
}

void SyncGetAllowedValuesUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetAllowedValues(aAsync, iPropertyInfo);
}


class SyncGetStateUpdateIDUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncGetStateUpdateIDUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, TUint& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStateUpdateIDUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    TUint& iId;
};

SyncGetStateUpdateIDUpnpOrgScheduledRecording1::SyncGetStateUpdateIDUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, TUint& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetStateUpdateIDUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateUpdateID(aAsync, iId);
}


class SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1::SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordSchedules(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncBrowseRecordTasksUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncBrowseRecordTasksUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseRecordTasksUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseRecordTasksUpnpOrgScheduledRecording1::SyncBrowseRecordTasksUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordTasksUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordTasks(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateRecordScheduleUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncCreateRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateRecordScheduleUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iRecordScheduleID;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncCreateRecordScheduleUpnpOrgScheduledRecording1::SyncCreateRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordScheduleID(aRecordScheduleID)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncCreateRecordScheduleUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateRecordSchedule(aAsync, iRecordScheduleID, iResult, iUpdateID);
}


class SyncDeleteRecordScheduleUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteRecordScheduleUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
};

SyncDeleteRecordScheduleUpnpOrgScheduledRecording1::SyncDeleteRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteRecordScheduleUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordSchedule(aAsync);
}


class SyncGetRecordScheduleUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncGetRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordScheduleUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncGetRecordScheduleUpnpOrgScheduledRecording1::SyncGetRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordSchedule(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordScheduleUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncEnableRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEnableRecordScheduleUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
};

SyncEnableRecordScheduleUpnpOrgScheduledRecording1::SyncEnableRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy)
    : iService(aProxy)
{
}

void SyncEnableRecordScheduleUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordSchedule(aAsync);
}


class SyncDisableRecordScheduleUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncDisableRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDisableRecordScheduleUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
};

SyncDisableRecordScheduleUpnpOrgScheduledRecording1::SyncDisableRecordScheduleUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy)
    : iService(aProxy)
{
}

void SyncDisableRecordScheduleUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordSchedule(aAsync);
}


class SyncDeleteRecordTaskUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncDeleteRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteRecordTaskUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
};

SyncDeleteRecordTaskUpnpOrgScheduledRecording1::SyncDeleteRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteRecordTaskUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordTask(aAsync);
}


class SyncGetRecordTaskUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncGetRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordTaskUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncGetRecordTaskUpnpOrgScheduledRecording1::SyncGetRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aResult, TUint& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTask(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordTaskUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncEnableRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEnableRecordTaskUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
};

SyncEnableRecordTaskUpnpOrgScheduledRecording1::SyncEnableRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy)
    : iService(aProxy)
{
}

void SyncEnableRecordTaskUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordTask(aAsync);
}


class SyncDisableRecordTaskUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncDisableRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDisableRecordTaskUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
};

SyncDisableRecordTaskUpnpOrgScheduledRecording1::SyncDisableRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy)
    : iService(aProxy)
{
}

void SyncDisableRecordTaskUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordTask(aAsync);
}


class SyncResetRecordTaskUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncResetRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncResetRecordTaskUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
};

SyncResetRecordTaskUpnpOrgScheduledRecording1::SyncResetRecordTaskUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy)
    : iService(aProxy)
{
}

void SyncResetRecordTaskUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndResetRecordTask(aAsync);
}


class SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iRecordScheduleConflictIDList;
    TUint& iUpdateID;
};

SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1::SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordScheduleConflictIDList(aRecordScheduleConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordScheduleConflicts(aAsync, iRecordScheduleConflictIDList, iUpdateID);
}


class SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1 : public SyncProxyAction
{
public:
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aRecordTaskConflictIDList, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1() {}
private:
    CpProxyUpnpOrgScheduledRecording1& iService;
    Brh& iRecordTaskConflictIDList;
    TUint& iUpdateID;
};

SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1::SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1(CpProxyUpnpOrgScheduledRecording1& aProxy, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
    : iService(aProxy)
    , iRecordTaskConflictIDList(aRecordTaskConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTaskConflicts(aAsync, iRecordTaskConflictIDList, iUpdateID);
}


CpProxyUpnpOrgScheduledRecording1::CpProxyUpnpOrgScheduledRecording1(CpDevice& aDevice)
    : CpProxy("schemas-upnp-org", "ScheduledRecording", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetSortCapabilities = new Action("GetSortCapabilities");
    param = new OpenHome::Net::ParameterString("SortCaps");
    iActionGetSortCapabilities->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("SortLevelCap");
    iActionGetSortCapabilities->AddOutputParameter(param);

    iActionGetPropertyList = new Action("GetPropertyList");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordSchedule";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordTask";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordScheduleParts";
    param = new OpenHome::Net::ParameterString("DataTypeID", allowedValues, 3);
    iActionGetPropertyList->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("PropertyList");
    iActionGetPropertyList->AddOutputParameter(param);

    iActionGetAllowedValues = new Action("GetAllowedValues");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordSchedule";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordTask";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordScheduleParts";
    param = new OpenHome::Net::ParameterString("DataTypeID", allowedValues, 3);
    iActionGetAllowedValues->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterString("Filter");
    iActionGetAllowedValues->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("PropertyInfo");
    iActionGetAllowedValues->AddOutputParameter(param);

    iActionGetStateUpdateID = new Action("GetStateUpdateID");
    param = new OpenHome::Net::ParameterUint("Id");
    iActionGetStateUpdateID->AddOutputParameter(param);

    iActionBrowseRecordSchedules = new Action("BrowseRecordSchedules");
    param = new OpenHome::Net::ParameterString("Filter");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionBrowseRecordSchedules->AddOutputParameter(param);

    iActionBrowseRecordTasks = new Action("BrowseRecordTasks");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("StartingIndex");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedCount");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SortCriteria");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("NumberReturned");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("TotalMatches");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionBrowseRecordTasks->AddOutputParameter(param);

    iActionCreateRecordSchedule = new Action("CreateRecordSchedule");
    param = new OpenHome::Net::ParameterString("Elements");
    iActionCreateRecordSchedule->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionCreateRecordSchedule->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionCreateRecordSchedule->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionCreateRecordSchedule->AddOutputParameter(param);

    iActionDeleteRecordSchedule = new Action("DeleteRecordSchedule");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionDeleteRecordSchedule->AddInputParameter(param);

    iActionGetRecordSchedule = new Action("GetRecordSchedule");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionGetRecordSchedule->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionGetRecordSchedule->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionGetRecordSchedule->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionGetRecordSchedule->AddOutputParameter(param);

    iActionEnableRecordSchedule = new Action("EnableRecordSchedule");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionEnableRecordSchedule->AddInputParameter(param);

    iActionDisableRecordSchedule = new Action("DisableRecordSchedule");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionDisableRecordSchedule->AddInputParameter(param);

    iActionDeleteRecordTask = new Action("DeleteRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionDeleteRecordTask->AddInputParameter(param);

    iActionGetRecordTask = new Action("GetRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionGetRecordTask->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Filter");
    iActionGetRecordTask->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionGetRecordTask->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionGetRecordTask->AddOutputParameter(param);

    iActionEnableRecordTask = new Action("EnableRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionEnableRecordTask->AddInputParameter(param);

    iActionDisableRecordTask = new Action("DisableRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionDisableRecordTask->AddInputParameter(param);

    iActionResetRecordTask = new Action("ResetRecordTask");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionResetRecordTask->AddInputParameter(param);

    iActionGetRecordScheduleConflicts = new Action("GetRecordScheduleConflicts");
    param = new OpenHome::Net::ParameterString("RecordScheduleID");
    iActionGetRecordScheduleConflicts->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("RecordScheduleConflictIDList");
    iActionGetRecordScheduleConflicts->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionGetRecordScheduleConflicts->AddOutputParameter(param);

    iActionGetRecordTaskConflicts = new Action("GetRecordTaskConflicts");
    param = new OpenHome::Net::ParameterString("RecordTaskID");
    iActionGetRecordTaskConflicts->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("RecordTaskConflictIDList");
    iActionGetRecordTaskConflicts->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("UpdateID");
    iActionGetRecordTaskConflicts->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgScheduledRecording1::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgScheduledRecording1::~CpProxyUpnpOrgScheduledRecording1()
{
    DestroyService();
    delete iActionGetSortCapabilities;
    delete iActionGetPropertyList;
    delete iActionGetAllowedValues;
    delete iActionGetStateUpdateID;
    delete iActionBrowseRecordSchedules;
    delete iActionBrowseRecordTasks;
    delete iActionCreateRecordSchedule;
    delete iActionDeleteRecordSchedule;
    delete iActionGetRecordSchedule;
    delete iActionEnableRecordSchedule;
    delete iActionDisableRecordSchedule;
    delete iActionDeleteRecordTask;
    delete iActionGetRecordTask;
    delete iActionEnableRecordTask;
    delete iActionDisableRecordTask;
    delete iActionResetRecordTask;
    delete iActionGetRecordScheduleConflicts;
    delete iActionGetRecordTaskConflicts;
}

void CpProxyUpnpOrgScheduledRecording1::SyncGetSortCapabilities(Brh& aSortCaps, TUint& aSortLevelCap)
{
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording1 sync(*this, aSortCaps, aSortLevelCap);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps, TUint& aSortLevelCap)
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
    aSortLevelCap = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1::SyncGetPropertyList(const Brx& aDataTypeID, Brh& aPropertyList)
{
    SyncGetPropertyListUpnpOrgScheduledRecording1 sync(*this, aPropertyList);
    BeginGetPropertyList(aDataTypeID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginGetPropertyList(const Brx& aDataTypeID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetPropertyList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPropertyList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDataTypeID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPropertyList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndGetPropertyList(IAsync& aAsync, Brh& aPropertyList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPropertyList"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPropertyList);
}

void CpProxyUpnpOrgScheduledRecording1::SyncGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, Brh& aPropertyInfo)
{
    SyncGetAllowedValuesUpnpOrgScheduledRecording1 sync(*this, aPropertyInfo);
    BeginGetAllowedValues(aDataTypeID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetAllowedValues, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetAllowedValues->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDataTypeID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetAllowedValues->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndGetAllowedValues(IAsync& aAsync, Brh& aPropertyInfo)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetAllowedValues"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPropertyInfo);
}

void CpProxyUpnpOrgScheduledRecording1::SyncGetStateUpdateID(TUint& aId)
{
    SyncGetStateUpdateIDUpnpOrgScheduledRecording1 sync(*this, aId);
    BeginGetStateUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginGetStateUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStateUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndGetStateUpdateID(IAsync& aAsync, TUint& aId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStateUpdateID"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1::SyncBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording1 sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordSchedules(aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowseRecordSchedules, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowseRecordSchedules->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSortCriteria));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowseRecordSchedules->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndBrowseRecordSchedules(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BrowseRecordSchedules"));

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

void CpProxyUpnpOrgScheduledRecording1::SyncBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseRecordTasksUpnpOrgScheduledRecording1 sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordTasks(aRecordScheduleID, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowseRecordTasks, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowseRecordTasks->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aStartingIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedCount));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSortCriteria));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowseRecordTasks->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndBrowseRecordTasks(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BrowseRecordTasks"));

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

void CpProxyUpnpOrgScheduledRecording1::SyncCreateRecordSchedule(const Brx& aElements, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
{
    SyncCreateRecordScheduleUpnpOrgScheduledRecording1 sync(*this, aRecordScheduleID, aResult, aUpdateID);
    BeginCreateRecordSchedule(aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginCreateRecordSchedule(const Brx& aElements, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aElements));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateRecordSchedule->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndCreateRecordSchedule(IAsync& aAsync, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordScheduleID);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1::SyncDeleteRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording1 sync(*this);
    BeginDeleteRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginDeleteRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndDeleteRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1::SyncGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID)
{
    SyncGetRecordScheduleUpnpOrgScheduledRecording1 sync(*this, aResult, aUpdateID);
    BeginGetRecordSchedule(aRecordScheduleID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordSchedule->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndGetRecordSchedule(IAsync& aAsync, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1::SyncEnableRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncEnableRecordScheduleUpnpOrgScheduledRecording1 sync(*this);
    BeginEnableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginEnableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEnableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndEnableRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EnableRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1::SyncDisableRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncDisableRecordScheduleUpnpOrgScheduledRecording1 sync(*this);
    BeginDisableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginDisableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndDisableRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisableRecordSchedule"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1::SyncDeleteRecordTask(const Brx& aRecordTaskID)
{
    SyncDeleteRecordTaskUpnpOrgScheduledRecording1 sync(*this);
    BeginDeleteRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginDeleteRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndDeleteRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1::SyncGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID)
{
    SyncGetRecordTaskUpnpOrgScheduledRecording1 sync(*this, aResult, aUpdateID);
    BeginGetRecordTask(aRecordTaskID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordTask->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndGetRecordTask(IAsync& aAsync, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1::SyncEnableRecordTask(const Brx& aRecordTaskID)
{
    SyncEnableRecordTaskUpnpOrgScheduledRecording1 sync(*this);
    BeginEnableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginEnableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEnableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndEnableRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EnableRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1::SyncDisableRecordTask(const Brx& aRecordTaskID)
{
    SyncDisableRecordTaskUpnpOrgScheduledRecording1 sync(*this);
    BeginDisableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginDisableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndDisableRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisableRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1::SyncResetRecordTask(const Brx& aRecordTaskID)
{
    SyncResetRecordTaskUpnpOrgScheduledRecording1 sync(*this);
    BeginResetRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginResetRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionResetRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionResetRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndResetRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ResetRecordTask"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgScheduledRecording1::SyncGetRecordScheduleConflicts(const Brx& aRecordScheduleID, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
{
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording1 sync(*this, aRecordScheduleConflictIDList, aUpdateID);
    BeginGetRecordScheduleConflicts(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginGetRecordScheduleConflicts(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordScheduleConflicts, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordScheduleConflicts->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordScheduleConflicts->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndGetRecordScheduleConflicts(IAsync& aAsync, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordScheduleConflicts"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordScheduleConflictIDList);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1::SyncGetRecordTaskConflicts(const Brx& aRecordTaskID, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
{
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording1 sync(*this, aRecordTaskConflictIDList, aUpdateID);
    BeginGetRecordTaskConflicts(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording1::BeginGetRecordTaskConflicts(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordTaskConflicts, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordTaskConflicts->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordTaskConflicts->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording1::EndGetRecordTaskConflicts(IAsync& aAsync, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordTaskConflicts"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordTaskConflictIDList);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording1::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgScheduledRecording1::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgScheduledRecording1::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

