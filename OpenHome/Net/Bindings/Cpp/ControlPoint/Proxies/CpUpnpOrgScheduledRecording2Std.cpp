#include "CpUpnpOrgScheduledRecording2.h"
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


class SyncGetSortCapabilitiesUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aSortCaps, uint32_t& aSortLevelCap);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSortCapabilitiesUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iSortCaps;
    uint32_t& iSortLevelCap;
};

SyncGetSortCapabilitiesUpnpOrgScheduledRecording2Cpp::SyncGetSortCapabilitiesUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aSortCaps, uint32_t& aSortLevelCap)
    : iService(aProxy)
    , iSortCaps(aSortCaps)
    , iSortLevelCap(aSortLevelCap)
{
}

void SyncGetSortCapabilitiesUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSortCapabilities(aAsync, iSortCaps, iSortLevelCap);
}


class SyncGetPropertyListUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncGetPropertyListUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aPropertyList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPropertyListUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iPropertyList;
};

SyncGetPropertyListUpnpOrgScheduledRecording2Cpp::SyncGetPropertyListUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aPropertyList)
    : iService(aProxy)
    , iPropertyList(aPropertyList)
{
}

void SyncGetPropertyListUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPropertyList(aAsync, iPropertyList);
}


class SyncGetAllowedValuesUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncGetAllowedValuesUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aPropertyInfo);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetAllowedValuesUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iPropertyInfo;
};

SyncGetAllowedValuesUpnpOrgScheduledRecording2Cpp::SyncGetAllowedValuesUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aPropertyInfo)
    : iService(aProxy)
    , iPropertyInfo(aPropertyInfo)
{
}

void SyncGetAllowedValuesUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetAllowedValues(aAsync, iPropertyInfo);
}


class SyncGetStateUpdateIDUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncGetStateUpdateIDUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, uint32_t& aId);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStateUpdateIDUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    uint32_t& iId;
};

SyncGetStateUpdateIDUpnpOrgScheduledRecording2Cpp::SyncGetStateUpdateIDUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, uint32_t& aId)
    : iService(aProxy)
    , iId(aId)
{
}

void SyncGetStateUpdateIDUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateUpdateID(aAsync, iId);
}


class SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2Cpp::SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordSchedules(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncBrowseRecordTasksUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncBrowseRecordTasksUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowseRecordTasksUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iResult;
    uint32_t& iNumberReturned;
    uint32_t& iTotalMatches;
    uint32_t& iUpdateID;
};

SyncBrowseRecordTasksUpnpOrgScheduledRecording2Cpp::SyncBrowseRecordTasksUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iNumberReturned(aNumberReturned)
    , iTotalMatches(aTotalMatches)
    , iUpdateID(aUpdateID)
{
}

void SyncBrowseRecordTasksUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowseRecordTasks(aAsync, iResult, iNumberReturned, iTotalMatches, iUpdateID);
}


class SyncCreateRecordScheduleUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncCreateRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aRecordScheduleID, std::string& aResult, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCreateRecordScheduleUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iRecordScheduleID;
    std::string& iResult;
    uint32_t& iUpdateID;
};

SyncCreateRecordScheduleUpnpOrgScheduledRecording2Cpp::SyncCreateRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aRecordScheduleID, std::string& aResult, uint32_t& aUpdateID)
    : iService(aProxy)
    , iRecordScheduleID(aRecordScheduleID)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncCreateRecordScheduleUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCreateRecordSchedule(aAsync, iRecordScheduleID, iResult, iUpdateID);
}


class SyncDeleteRecordScheduleUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteRecordScheduleUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
};

SyncDeleteRecordScheduleUpnpOrgScheduledRecording2Cpp::SyncDeleteRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteRecordScheduleUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordSchedule(aAsync);
}


class SyncGetRecordScheduleUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncGetRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aResult, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordScheduleUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iResult;
    uint32_t& iUpdateID;
};

SyncGetRecordScheduleUpnpOrgScheduledRecording2Cpp::SyncGetRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aResult, uint32_t& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordSchedule(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordScheduleUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncEnableRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEnableRecordScheduleUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
};

SyncEnableRecordScheduleUpnpOrgScheduledRecording2Cpp::SyncEnableRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncEnableRecordScheduleUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordSchedule(aAsync);
}


class SyncDisableRecordScheduleUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncDisableRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDisableRecordScheduleUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
};

SyncDisableRecordScheduleUpnpOrgScheduledRecording2Cpp::SyncDisableRecordScheduleUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDisableRecordScheduleUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordSchedule(aAsync);
}


class SyncDeleteRecordTaskUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncDeleteRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDeleteRecordTaskUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
};

SyncDeleteRecordTaskUpnpOrgScheduledRecording2Cpp::SyncDeleteRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDeleteRecordTaskUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDeleteRecordTask(aAsync);
}


class SyncGetRecordTaskUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncGetRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aResult, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordTaskUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iResult;
    uint32_t& iUpdateID;
};

SyncGetRecordTaskUpnpOrgScheduledRecording2Cpp::SyncGetRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aResult, uint32_t& aUpdateID)
    : iService(aProxy)
    , iResult(aResult)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTask(aAsync, iResult, iUpdateID);
}


class SyncEnableRecordTaskUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncEnableRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncEnableRecordTaskUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
};

SyncEnableRecordTaskUpnpOrgScheduledRecording2Cpp::SyncEnableRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncEnableRecordTaskUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndEnableRecordTask(aAsync);
}


class SyncDisableRecordTaskUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncDisableRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDisableRecordTaskUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
};

SyncDisableRecordTaskUpnpOrgScheduledRecording2Cpp::SyncDisableRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncDisableRecordTaskUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisableRecordTask(aAsync);
}


class SyncResetRecordTaskUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncResetRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncResetRecordTaskUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
};

SyncResetRecordTaskUpnpOrgScheduledRecording2Cpp::SyncResetRecordTaskUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncResetRecordTaskUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndResetRecordTask(aAsync);
}


class SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aRecordScheduleConflictIDList, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iRecordScheduleConflictIDList;
    uint32_t& iUpdateID;
};

SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2Cpp::SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aRecordScheduleConflictIDList, uint32_t& aUpdateID)
    : iService(aProxy)
    , iRecordScheduleConflictIDList(aRecordScheduleConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordScheduleConflicts(aAsync, iRecordScheduleConflictIDList, iUpdateID);
}


class SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2Cpp : public SyncProxyAction
{
public:
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aRecordTaskConflictIDList, uint32_t& aUpdateID);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2Cpp() {}
private:
    CpProxyUpnpOrgScheduledRecording2Cpp& iService;
    std::string& iRecordTaskConflictIDList;
    uint32_t& iUpdateID;
};

SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2Cpp::SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2Cpp(CpProxyUpnpOrgScheduledRecording2Cpp& aProxy, std::string& aRecordTaskConflictIDList, uint32_t& aUpdateID)
    : iService(aProxy)
    , iRecordTaskConflictIDList(aRecordTaskConflictIDList)
    , iUpdateID(aUpdateID)
{
}

void SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRecordTaskConflicts(aAsync, iRecordTaskConflictIDList, iUpdateID);
}


CpProxyUpnpOrgScheduledRecording2Cpp::CpProxyUpnpOrgScheduledRecording2Cpp(CpDeviceCpp& aDevice)
    : CpProxy("schemas-upnp-org", "ScheduledRecording", 2, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgScheduledRecording2Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgScheduledRecording2Cpp::~CpProxyUpnpOrgScheduledRecording2Cpp()
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncGetSortCapabilities(std::string& aSortCaps, uint32_t& aSortLevelCap)
{
    SyncGetSortCapabilitiesUpnpOrgScheduledRecording2Cpp sync(*this, aSortCaps, aSortLevelCap);
    BeginGetSortCapabilities(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginGetSortCapabilities(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSortCapabilities, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSortCapabilities->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndGetSortCapabilities(IAsync& aAsync, std::string& aSortCaps, uint32_t& aSortLevelCap)
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
    aSortLevelCap = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncGetPropertyList(const std::string& aDataTypeID, std::string& aPropertyList)
{
    SyncGetPropertyListUpnpOrgScheduledRecording2Cpp sync(*this, aPropertyList);
    BeginGetPropertyList(aDataTypeID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginGetPropertyList(const std::string& aDataTypeID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetPropertyList, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPropertyList->InputParameters();
    {
        Brn buf((const TByte*)aDataTypeID.c_str(), (TUint)aDataTypeID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPropertyList->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndGetPropertyList(IAsync& aAsync, std::string& aPropertyList)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPropertyList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncGetAllowedValues(const std::string& aDataTypeID, const std::string& aFilter, std::string& aPropertyInfo)
{
    SyncGetAllowedValuesUpnpOrgScheduledRecording2Cpp sync(*this, aPropertyInfo);
    BeginGetAllowedValues(aDataTypeID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginGetAllowedValues(const std::string& aDataTypeID, const std::string& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetAllowedValues, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetAllowedValues->InputParameters();
    {
        Brn buf((const TByte*)aDataTypeID.c_str(), (TUint)aDataTypeID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetAllowedValues->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndGetAllowedValues(IAsync& aAsync, std::string& aPropertyInfo)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aPropertyInfo.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncGetStateUpdateID(uint32_t& aId)
{
    SyncGetStateUpdateIDUpnpOrgScheduledRecording2Cpp sync(*this, aId);
    BeginGetStateUpdateID(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginGetStateUpdateID(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStateUpdateID, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateUpdateID->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndGetStateUpdateID(IAsync& aAsync, uint32_t& aId)
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncBrowseRecordSchedules(const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    SyncBrowseRecordSchedulesUpnpOrgScheduledRecording2Cpp sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordSchedules(aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginBrowseRecordSchedules(const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowseRecordSchedules, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowseRecordSchedules->InputParameters();
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
    const Action::VectorParameters& outParams = iActionBrowseRecordSchedules->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndBrowseRecordSchedules(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncBrowseRecordTasks(const std::string& aRecordScheduleID, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
{
    SyncBrowseRecordTasksUpnpOrgScheduledRecording2Cpp sync(*this, aResult, aNumberReturned, aTotalMatches, aUpdateID);
    BeginBrowseRecordTasks(aRecordScheduleID, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginBrowseRecordTasks(const std::string& aRecordScheduleID, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowseRecordTasks, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionBrowseRecordTasks->InputParameters();
    {
        Brn buf((const TByte*)aRecordScheduleID.c_str(), (TUint)aRecordScheduleID.length());
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
    const Action::VectorParameters& outParams = iActionBrowseRecordTasks->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndBrowseRecordTasks(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aNumberReturned = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aTotalMatches = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncCreateRecordSchedule(const std::string& aElements, std::string& aRecordScheduleID, std::string& aResult, uint32_t& aUpdateID)
{
    SyncCreateRecordScheduleUpnpOrgScheduledRecording2Cpp sync(*this, aRecordScheduleID, aResult, aUpdateID);
    BeginCreateRecordSchedule(aElements, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginCreateRecordSchedule(const std::string& aElements, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCreateRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionCreateRecordSchedule->InputParameters();
    {
        Brn buf((const TByte*)aElements.c_str(), (TUint)aElements.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCreateRecordSchedule->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndCreateRecordSchedule(IAsync& aAsync, std::string& aRecordScheduleID, std::string& aResult, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecordScheduleID.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncDeleteRecordSchedule(const std::string& aRecordScheduleID)
{
    SyncDeleteRecordScheduleUpnpOrgScheduledRecording2Cpp sync(*this);
    BeginDeleteRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginDeleteRecordSchedule(const std::string& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordSchedule->InputParameters();
    {
        Brn buf((const TByte*)aRecordScheduleID.c_str(), (TUint)aRecordScheduleID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndDeleteRecordSchedule(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncGetRecordSchedule(const std::string& aRecordScheduleID, const std::string& aFilter, std::string& aResult, uint32_t& aUpdateID)
{
    SyncGetRecordScheduleUpnpOrgScheduledRecording2Cpp sync(*this, aResult, aUpdateID);
    BeginGetRecordSchedule(aRecordScheduleID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginGetRecordSchedule(const std::string& aRecordScheduleID, const std::string& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordSchedule->InputParameters();
    {
        Brn buf((const TByte*)aRecordScheduleID.c_str(), (TUint)aRecordScheduleID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordSchedule->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndGetRecordSchedule(IAsync& aAsync, std::string& aResult, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncEnableRecordSchedule(const std::string& aRecordScheduleID)
{
    SyncEnableRecordScheduleUpnpOrgScheduledRecording2Cpp sync(*this);
    BeginEnableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginEnableRecordSchedule(const std::string& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEnableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordSchedule->InputParameters();
    {
        Brn buf((const TByte*)aRecordScheduleID.c_str(), (TUint)aRecordScheduleID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndEnableRecordSchedule(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncDisableRecordSchedule(const std::string& aRecordScheduleID)
{
    SyncDisableRecordScheduleUpnpOrgScheduledRecording2Cpp sync(*this);
    BeginDisableRecordSchedule(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginDisableRecordSchedule(const std::string& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisableRecordSchedule, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordSchedule->InputParameters();
    {
        Brn buf((const TByte*)aRecordScheduleID.c_str(), (TUint)aRecordScheduleID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndDisableRecordSchedule(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncDeleteRecordTask(const std::string& aRecordTaskID)
{
    SyncDeleteRecordTaskUpnpOrgScheduledRecording2Cpp sync(*this);
    BeginDeleteRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginDeleteRecordTask(const std::string& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDeleteRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDeleteRecordTask->InputParameters();
    {
        Brn buf((const TByte*)aRecordTaskID.c_str(), (TUint)aRecordTaskID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndDeleteRecordTask(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncGetRecordTask(const std::string& aRecordTaskID, const std::string& aFilter, std::string& aResult, uint32_t& aUpdateID)
{
    SyncGetRecordTaskUpnpOrgScheduledRecording2Cpp sync(*this, aResult, aUpdateID);
    BeginGetRecordTask(aRecordTaskID, aFilter, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginGetRecordTask(const std::string& aRecordTaskID, const std::string& aFilter, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordTask->InputParameters();
    {
        Brn buf((const TByte*)aRecordTaskID.c_str(), (TUint)aRecordTaskID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aFilter.c_str(), (TUint)aFilter.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordTask->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndGetRecordTask(IAsync& aAsync, std::string& aResult, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncEnableRecordTask(const std::string& aRecordTaskID)
{
    SyncEnableRecordTaskUpnpOrgScheduledRecording2Cpp sync(*this);
    BeginEnableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginEnableRecordTask(const std::string& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEnableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEnableRecordTask->InputParameters();
    {
        Brn buf((const TByte*)aRecordTaskID.c_str(), (TUint)aRecordTaskID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndEnableRecordTask(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncDisableRecordTask(const std::string& aRecordTaskID)
{
    SyncDisableRecordTaskUpnpOrgScheduledRecording2Cpp sync(*this);
    BeginDisableRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginDisableRecordTask(const std::string& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisableRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisableRecordTask->InputParameters();
    {
        Brn buf((const TByte*)aRecordTaskID.c_str(), (TUint)aRecordTaskID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndDisableRecordTask(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncResetRecordTask(const std::string& aRecordTaskID)
{
    SyncResetRecordTaskUpnpOrgScheduledRecording2Cpp sync(*this);
    BeginResetRecordTask(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginResetRecordTask(const std::string& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionResetRecordTask, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionResetRecordTask->InputParameters();
    {
        Brn buf((const TByte*)aRecordTaskID.c_str(), (TUint)aRecordTaskID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndResetRecordTask(IAsync& aAsync)
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

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncGetRecordScheduleConflicts(const std::string& aRecordScheduleID, std::string& aRecordScheduleConflictIDList, uint32_t& aUpdateID)
{
    SyncGetRecordScheduleConflictsUpnpOrgScheduledRecording2Cpp sync(*this, aRecordScheduleConflictIDList, aUpdateID);
    BeginGetRecordScheduleConflicts(aRecordScheduleID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginGetRecordScheduleConflicts(const std::string& aRecordScheduleID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordScheduleConflicts, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordScheduleConflicts->InputParameters();
    {
        Brn buf((const TByte*)aRecordScheduleID.c_str(), (TUint)aRecordScheduleID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordScheduleConflicts->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndGetRecordScheduleConflicts(IAsync& aAsync, std::string& aRecordScheduleConflictIDList, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecordScheduleConflictIDList.assign((const char*)val.Ptr(), val.Bytes());
    }
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SyncGetRecordTaskConflicts(const std::string& aRecordTaskID, std::string& aRecordTaskConflictIDList, uint32_t& aUpdateID)
{
    SyncGetRecordTaskConflictsUpnpOrgScheduledRecording2Cpp sync(*this, aRecordTaskConflictIDList, aUpdateID);
    BeginGetRecordTaskConflicts(aRecordTaskID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::BeginGetRecordTaskConflicts(const std::string& aRecordTaskID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRecordTaskConflicts, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRecordTaskConflicts->InputParameters();
    {
        Brn buf((const TByte*)aRecordTaskID.c_str(), (TUint)aRecordTaskID.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRecordTaskConflicts->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgScheduledRecording2Cpp::EndGetRecordTaskConflicts(IAsync& aAsync, std::string& aRecordTaskConflictIDList, uint32_t& aUpdateID)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRecordTaskConflictIDList.assign((const char*)val.Ptr(), val.Bytes());
    }
    aUpdateID = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgScheduledRecording2Cpp::PropertyLastChange(std::string& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgScheduledRecording2Cpp::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

