#include <Core/CpUpnpOrgScheduledRecording2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncGetSortCapabilitiesUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aSortCaps, TUint& aSortLevelCap);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iSortCaps;
    TUint& iSortLevelCap;
};

SyncGetSortCapabilitiesUpnpOrgScheduledRecording2::SyncGetSortCapabilitiesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aSortCaps, TUint& aSortLevelCap)
    : iService(aService)
    , iSortCaps(aSortCaps)
    , iSortLevelCap(aSortLevelCap)
{
}

void SyncGetSortCapabilitiesUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps, iSortLevelCap);
}


class SyncGetPropertyListUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncGetPropertyListUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aPropertyList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iPropertyList;
};

SyncGetPropertyListUpnpOrgScheduledRecording2::SyncGetPropertyListUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aPropertyList)
    : iService(aService)
    , iPropertyList(aPropertyList)
{
}

void SyncGetPropertyListUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPropertyList(aAsync, iPropertyList);
}


class SyncGetAllowedValuesUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncGetAllowedValuesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aPropertyInfo);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iPropertyInfo;
};

SyncGetAllowedValuesUpnpOrgScheduledRecording2::SyncGetAllowedValuesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aPropertyInfo)
    : iService(aService)
    , iPropertyInfo(aPropertyInfo)
{
}

void SyncGetAllowedValuesUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetAllowedValues(aAsync, iPropertyInfo);
}


class SyncGetStateUpdateIDUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncGetStateUpdateIDUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, TUint& aId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    TUint& iId;
};

SyncGetStateUpdateIDUpnpOrgScheduledRecording2::SyncGetStateUpdateIDUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, TUint& aId)
    : iService(aService)
    , iId(aId)
{
}

void SyncGetStateUpdateIDUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateUpdateID(aAsync, iId);
}


class SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2::SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aService)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordSchedules(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncBrowseRecordTasksUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncBrowseRecordTasksUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iResult;
    TUint& iNumberReturned;
    TUint& iTotalMatches;
    TUint& iUpdateID;
};

SyncBrowseRecordTasksUpnpOrgScheduledRecording2::SyncBrowseRecordTasksUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
    : iService(aService)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordTasksUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordTasks(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateRecordScheduleUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncCreateRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iRecordScheduleID;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncCreateRecordScheduleUpnpOrgScheduledRecording2::SyncCreateRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
    : iService(aService)
    , iRecordScheduleID(aRecordScheduleID)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncCreateRecordScheduleUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateRecordSchedule(aAsync, iRecordScheduleID, iResult, iUpdateID);
}


class SyncDeleteRecordScheduleUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
};

SyncDeleteRecordScheduleUpnpOrgScheduledRecording2::SyncDeleteRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService)
    : iService(aService)
{
}

void SyncDeleteRecordScheduleUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordSchedule(aAsync);
}


class SyncGetRecordScheduleUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncGetRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncGetRecordScheduleUpnpOrgScheduledRecording2::SyncGetRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aResult, TUint& aUpdateID)
    : iService(aService)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordSchedule(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordScheduleUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncEnableRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
};

SyncEnableRecordScheduleUpnpOrgScheduledRecording2::SyncEnableRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService)
    : iService(aService)
{
}

void SyncEnableRecordScheduleUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordSchedule(aAsync);
}


class SyncDisableRecordScheduleUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncDisableRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
};

SyncDisableRecordScheduleUpnpOrgScheduledRecording2::SyncDisableRecordScheduleUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService)
    : iService(aService)
{
}

void SyncDisableRecordScheduleUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordSchedule(aAsync);
}


class SyncDeleteRecordTaskUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncDeleteRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
};

SyncDeleteRecordTaskUpnpOrgScheduledRecording2::SyncDeleteRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService)
    : iService(aService)
{
}

void SyncDeleteRecordTaskUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordTask(aAsync);
}


class SyncGetRecordTaskUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncGetRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aResult, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iResult;
    TUint& iUpdateID;
};

SyncGetRecordTaskUpnpOrgScheduledRecording2::SyncGetRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aResult, TUint& aUpdateID)
    : iService(aService)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTask(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordTaskUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncEnableRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
};

SyncEnableRecordTaskUpnpOrgScheduledRecording2::SyncEnableRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService)
    : iService(aService)
{
}

void SyncEnableRecordTaskUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordTask(aAsync);
}


class SyncDisableRecordTaskUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncDisableRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
};

SyncDisableRecordTaskUpnpOrgScheduledRecording2::SyncDisableRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService)
    : iService(aService)
{
}

void SyncDisableRecordTaskUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordTask(aAsync);
}


class SyncResetRecordTaskUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncResetRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
};

SyncResetRecordTaskUpnpOrgScheduledRecording2::SyncResetRecordTaskUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService)
    : iService(aService)
{
}

void SyncResetRecordTaskUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndResetRecordTask(aAsync);
}


class SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iRecordScheduleConflictIDList;
    TUint& iUpdateID;
};

SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2::SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
    : iService(aService)
    , iRecordScheduleConflictIDList(aRecordScheduleConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordScheduleConflicts(aAsync, iRecordScheduleConflictIDList, iUpdateID);
}


class SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2 : public SyncProxyAction
{
public:
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aRecordTaskConflictIDList, TUint& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgScheduledRecording2& iService;
    Brh& iRecordTaskConflictIDList;
    TUint& iUpdateID;
};

SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2::SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2(CpProxyUpnpOrgScheduledRecording2& aService, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
    : iService(aService)
    , iRecordTaskConflictIDList(aRecordTaskConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTaskConflicts(aAsync, iRecordTaskConflictIDList, iUpdateID);
}


CpProxyUpnpOrgScheduledRecording2::CpProxyUpnpOrgScheduledRecording2(CpDevice& aDevice)
{
    iService = new CpiService("schemas-upnp-org", "ScheduledRecording", 2, aDevice.Device());
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionGetSortCapabilities = new Action("GetSortCapabilities");
    param = new Zapp::ParameterString("SortCaps");
    iActionGetSortCapabilities->AddOutputParameter(param);
    param = new Zapp::ParameterUint("SortLevelCap");
    iActionGetSortCapabilities->AddOutputParameter(param);

    iActionGetPropertyList = new Action("GetPropertyList");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordSchedule";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordTask";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordScheduleParts";
    param = new Zapp::ParameterString("DataTypeID", allowedValues, 3);
    iActionGetPropertyList->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterString("PropertyList");
    iActionGetPropertyList->AddOutputParameter(param);

    iActionGetAllowedValues = new Action("GetAllowedValues");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordSchedule";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordTask";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordScheduleParts";
    param = new Zapp::ParameterString("DataTypeID", allowedValues, 3);
    iActionGetAllowedValues->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterString("Filter");
    iActionGetAllowedValues->AddInputParameter(param);
    param = new Zapp::ParameterString("PropertyInfo");
    iActionGetAllowedValues->AddOutputParameter(param);

    iActionGetStateUpdateID = new Action("GetStateUpdateID");
    param = new Zapp::ParameterUint("Id");
    iActionGetStateUpdateID->AddOutputParameter(param);

    iActionBrowseRecordSchedules = new Action("BrowseRecordSchedules");
    param = new Zapp::ParameterString("Filter");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new Zapp::ParameterUint("StartingIndex");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new Zapp::ParameterUint("RequestedCount");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new Zapp::ParameterString("SortCriteria");
    iActionBrowseRecordSchedules->AddInputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new Zapp::ParameterUint("NumberReturned");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new Zapp::ParameterUint("TotalMatches");
    iActionBrowseRecordSchedules->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionBrowseRecordSchedules->AddOutputParameter(param);

    iActionBrowseRecordTasks = new Action("BrowseRecordTasks");
    param = new Zapp::ParameterString("RecordScheduleID");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new Zapp::ParameterString("Filter");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new Zapp::ParameterUint("StartingIndex");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new Zapp::ParameterUint("RequestedCount");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new Zapp::ParameterString("SortCriteria");
    iActionBrowseRecordTasks->AddInputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new Zapp::ParameterUint("NumberReturned");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new Zapp::ParameterUint("TotalMatches");
    iActionBrowseRecordTasks->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionBrowseRecordTasks->AddOutputParameter(param);

    iActionCreateRecordSchedule = new Action("CreateRecordSchedule");
    param = new Zapp::ParameterString("Elements");
    iActionCreateRecordSchedule->AddInputParameter(param);
    param = new Zapp::ParameterString("RecordScheduleID");
    iActionCreateRecordSchedule->AddOutputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionCreateRecordSchedule->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionCreateRecordSchedule->AddOutputParameter(param);

    iActionDeleteRecordSchedule = new Action("DeleteRecordSchedule");
    param = new Zapp::ParameterString("RecordScheduleID");
    iActionDeleteRecordSchedule->AddInputParameter(param);

    iActionGetRecordSchedule = new Action("GetRecordSchedule");
    param = new Zapp::ParameterString("RecordScheduleID");
    iActionGetRecordSchedule->AddInputParameter(param);
    param = new Zapp::ParameterString("Filter");
    iActionGetRecordSchedule->AddInputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionGetRecordSchedule->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionGetRecordSchedule->AddOutputParameter(param);

    iActionEnableRecordSchedule = new Action("EnableRecordSchedule");
    param = new Zapp::ParameterString("RecordScheduleID");
    iActionEnableRecordSchedule->AddInputParameter(param);

    iActionDisableRecordSchedule = new Action("DisableRecordSchedule");
    param = new Zapp::ParameterString("RecordScheduleID");
    iActionDisableRecordSchedule->AddInputParameter(param);

    iActionDeleteRecordTask = new Action("DeleteRecordTask");
    param = new Zapp::ParameterString("RecordTaskID");
    iActionDeleteRecordTask->AddInputParameter(param);

    iActionGetRecordTask = new Action("GetRecordTask");
    param = new Zapp::ParameterString("RecordTaskID");
    iActionGetRecordTask->AddInputParameter(param);
    param = new Zapp::ParameterString("Filter");
    iActionGetRecordTask->AddInputParameter(param);
    param = new Zapp::ParameterString("Result");
    iActionGetRecordTask->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionGetRecordTask->AddOutputParameter(param);

    iActionEnableRecordTask = new Action("EnableRecordTask");
    param = new Zapp::ParameterString("RecordTaskID");
    iActionEnableRecordTask->AddInputParameter(param);

    iActionDisableRecordTask = new Action("DisableRecordTask");
    param = new Zapp::ParameterString("RecordTaskID");
    iActionDisableRecordTask->AddInputParameter(param);

    iActionResetRecordTask = new Action("ResetRecordTask");
    param = new Zapp::ParameterString("RecordTaskID");
    iActionResetRecordTask->AddInputParameter(param);

    iActionGetRecordScheduleConflicts = new Action("GetRecordScheduleConflicts");
    param = new Zapp::ParameterString("RecordScheduleID");
    iActionGetRecordScheduleConflicts->AddInputParameter(param);
    param = new Zapp::ParameterString("RecordScheduleConflictIDList");
    iActionGetRecordScheduleConflicts->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionGetRecordScheduleConflicts->AddOutputParameter(param);

    iActionGetRecordTaskConflicts = new Action("GetRecordTaskConflicts");
    param = new Zapp::ParameterString("RecordTaskID");
    iActionGetRecordTaskConflicts->AddInputParameter(param);
    param = new Zapp::ParameterString("RecordTaskConflictIDList");
    iActionGetRecordTaskConflicts->AddOutputParameter(param);
    param = new Zapp::ParameterUint("UpdateID");
    iActionGetRecordTaskConflicts->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgScheduledRecording2::LastChangePropertyChanged);
    iLastChange = new PropertyString("LastChange", functor);
    iService->AddProperty(iLastChange);
}

CpProxyUpnpOrgScheduledRecording2::~CpProxyUpnpOrgScheduledRecording2()
{
    delete iService;
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

void CpProxyUpnpOrgScheduledRecording2::SyncGetSortCapabilities(Brh& aSortCaps, TUint& aSortLevelCap)
{
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording2 sync(*this, aSortCaps, aSortLevelCap);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps, TUint& aSortLevelCap)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSortCapabilities"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSortCaps);
    aSortLevelCap = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SyncGetPropertyList(const Brx& aDataTypeID, Brh& aPropertyList)
{
    SyncGetPropertyListUpnpOrgScheduledRecording2 sync(*this, aPropertyList);
    BeginGetPropertyList(aDataTypeID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginGetPropertyList(const Brx& aDataTypeID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetPropertyList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPropertyList->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDataTypeID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPropertyList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndGetPropertyList(IAsync& aAsync, Brh& aPropertyList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPropertyList"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPropertyList);
}

void CpProxyUpnpOrgScheduledRecording2::SyncGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, Brh& aPropertyInfo)
{
    SyncGetAllowedValuesUpnpOrgScheduledRecording2 sync(*this, aPropertyInfo);
    BeginGetAllowedValues(aDataTypeID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginGetAllowedValues(const Brx& aDataTypeID, const Brx& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetAllowedValues, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetAllowedValues->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aDataTypeID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aFilter));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetAllowedValues->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndGetAllowedValues(IAsync& aAsync, Brh& aPropertyInfo)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetAllowedValues"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aPropertyInfo);
}

void CpProxyUpnpOrgScheduledRecording2::SyncGetStateUpdateID(TUint& aId)
{
    SyncGetStateUpdateIDUpnpOrgScheduledRecording2 sync(*this, aId);
    BeginGetStateUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginGetStateUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStateUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndGetStateUpdateID(IAsync& aAsync, TUint& aId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStateUpdateID"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SyncBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2 sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordSchedules(aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginBrowseRecordSchedules(const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndBrowseRecordSchedules(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BrowseRecordSchedules"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SyncBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    SyncBrowseRecordTasksUpnpOrgScheduledRecording2 sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordTasks(aRecordScheduleID, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginBrowseRecordTasks(const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndBrowseRecordTasks(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BrowseRecordTasks"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SyncCreateRecordSchedule(const Brx& aElements, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
{
    SyncCreateRecordScheduleUpnpOrgScheduledRecording2 sync(*this, aRecordScheduleID, aResult, aUpdateID);
    BeginCreateRecordSchedule(aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginCreateRecordSchedule(const Brx& aElements, FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndCreateRecordSchedule(IAsync& aAsync, Brh& aRecordScheduleID, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CreateRecordSchedule"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordScheduleID);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SyncDeleteRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording2 sync(*this);
    BeginDeleteRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginDeleteRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndDeleteRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteRecordSchedule"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgScheduledRecording2::SyncGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID)
{
    SyncGetRecordScheduleUpnpOrgScheduledRecording2 sync(*this, aResult, aUpdateID);
    BeginGetRecordSchedule(aRecordScheduleID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginGetRecordSchedule(const Brx& aRecordScheduleID, const Brx& aFilter, FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndGetRecordSchedule(IAsync& aAsync, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordSchedule"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SyncEnableRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncEnableRecordScheduleUpnpOrgScheduledRecording2 sync(*this);
    BeginEnableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginEnableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEnableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndEnableRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EnableRecordSchedule"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgScheduledRecording2::SyncDisableRecordSchedule(const Brx& aRecordScheduleID)
{
    SyncDisableRecordScheduleUpnpOrgScheduledRecording2 sync(*this);
    BeginDisableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginDisableRecordSchedule(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordSchedule->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndDisableRecordSchedule(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisableRecordSchedule"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgScheduledRecording2::SyncDeleteRecordTask(const Brx& aRecordTaskID)
{
    SyncDeleteRecordTaskUpnpOrgScheduledRecording2 sync(*this);
    BeginDeleteRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginDeleteRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndDeleteRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DeleteRecordTask"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgScheduledRecording2::SyncGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, Brh& aResult, TUint& aUpdateID)
{
    SyncGetRecordTaskUpnpOrgScheduledRecording2 sync(*this, aResult, aUpdateID);
    BeginGetRecordTask(aRecordTaskID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginGetRecordTask(const Brx& aRecordTaskID, const Brx& aFilter, FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndGetRecordTask(IAsync& aAsync, Brh& aResult, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordTask"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SyncEnableRecordTask(const Brx& aRecordTaskID)
{
    SyncEnableRecordTaskUpnpOrgScheduledRecording2 sync(*this);
    BeginEnableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginEnableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEnableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndEnableRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EnableRecordTask"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgScheduledRecording2::SyncDisableRecordTask(const Brx& aRecordTaskID)
{
    SyncDisableRecordTaskUpnpOrgScheduledRecording2 sync(*this);
    BeginDisableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginDisableRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndDisableRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisableRecordTask"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgScheduledRecording2::SyncResetRecordTask(const Brx& aRecordTaskID)
{
    SyncResetRecordTaskUpnpOrgScheduledRecording2 sync(*this);
    BeginResetRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginResetRecordTask(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionResetRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionResetRecordTask->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndResetRecordTask(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ResetRecordTask"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgScheduledRecording2::SyncGetRecordScheduleConflicts(const Brx& aRecordScheduleID, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
{
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2 sync(*this, aRecordScheduleConflictIDList, aUpdateID);
    BeginGetRecordScheduleConflicts(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginGetRecordScheduleConflicts(const Brx& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordScheduleConflicts, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordScheduleConflicts->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordScheduleID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordScheduleConflicts->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndGetRecordScheduleConflicts(IAsync& aAsync, Brh& aRecordScheduleConflictIDList, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordScheduleConflicts"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordScheduleConflictIDList);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SyncGetRecordTaskConflicts(const Brx& aRecordTaskID, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
{
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2 sync(*this, aRecordTaskConflictIDList, aUpdateID);
    BeginGetRecordTaskConflicts(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2::BeginGetRecordTaskConflicts(const Brx& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordTaskConflicts, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordTaskConflicts->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRecordTaskID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordTaskConflicts->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgScheduledRecording2::EndGetRecordTaskConflicts(IAsync& aAsync, Brh& aRecordTaskConflictIDList, TUint& aUpdateID)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRecordTaskConflicts"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRecordTaskConflictIDList);
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgScheduledRecording2::PropertyLastChange(Brhz& aLastChange) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgScheduledRecording2::LastChangePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLastChangeChanged != NULL) {
        iLastChangeChanged();
    }
}

