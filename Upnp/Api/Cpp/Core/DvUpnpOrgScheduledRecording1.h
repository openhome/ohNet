#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING1
#define HEADER_DVUPNPORGSCHEDULEDRECORDING1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ScheduledRecording:1
 */
class DvServiceUpnpOrgScheduledRecording1 : public DvService
{
public:
    virtual ~DvServiceUpnpOrgScheduledRecording1() {}
    void SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
protected:
    DvServiceUpnpOrgScheduledRecording1(DvDevice& aDevice);
    void EnableActionGetSortCapabilities();
    void EnableActionGetPropertyList();
    void EnableActionGetAllowedValues();
    void EnableActionGetStateUpdateID();
    void EnableActionBrowseRecordSchedules();
    void EnableActionBrowseRecordTasks();
    void EnableActionCreateRecordSchedule();
    void EnableActionDeleteRecordSchedule();
    void EnableActionGetRecordSchedule();
    void EnableActionEnableRecordSchedule();
    void EnableActionDisableRecordSchedule();
    void EnableActionDeleteRecordTask();
    void EnableActionGetRecordTask();
    void EnableActionEnableRecordTask();
    void EnableActionDisableRecordTask();
    void EnableActionResetRecordTask();
    void EnableActionGetRecordScheduleConflicts();
    void EnableActionGetRecordTaskConflicts();
private:
    virtual void GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps, IInvocationResponseUint& aSortLevelCap);
    virtual void GetPropertyList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aDataTypeID, IInvocationResponseString& aPropertyList);
    virtual void GetAllowedValues(IInvocationResponse& aResponse, TUint aVersion, const Brx& aDataTypeID, const Brx& aFilter, IInvocationResponseString& aPropertyInfo);
    virtual void GetStateUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId);
    virtual void BrowseRecordSchedules(IInvocationResponse& aResponse, TUint aVersion, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    virtual void BrowseRecordTasks(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    virtual void CreateRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aElements, IInvocationResponseString& aRecordScheduleID, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID);
    virtual void DeleteRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID);
    virtual void GetRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, const Brx& aFilter, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID);
    virtual void EnableRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID);
    virtual void DisableRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID);
    virtual void DeleteRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID);
    virtual void GetRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID, const Brx& aFilter, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID);
    virtual void EnableRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID);
    virtual void DisableRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID);
    virtual void ResetRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID);
    virtual void GetRecordScheduleConflicts(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, IInvocationResponseString& aRecordScheduleConflictIDList, IInvocationResponseUint& aUpdateID);
    virtual void GetRecordTaskConflicts(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID, IInvocationResponseString& aRecordTaskConflictIDList, IInvocationResponseUint& aUpdateID);
private:
    DvServiceUpnpOrgScheduledRecording1();
    void DoGetSortCapabilities(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetPropertyList(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetAllowedValues(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetStateUpdateID(IDvInvocation& aInvocation, TUint aVersion);
    void DoBrowseRecordSchedules(IDvInvocation& aInvocation, TUint aVersion);
    void DoBrowseRecordTasks(IDvInvocation& aInvocation, TUint aVersion);
    void DoCreateRecordSchedule(IDvInvocation& aInvocation, TUint aVersion);
    void DoDeleteRecordSchedule(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRecordSchedule(IDvInvocation& aInvocation, TUint aVersion);
    void DoEnableRecordSchedule(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisableRecordSchedule(IDvInvocation& aInvocation, TUint aVersion);
    void DoDeleteRecordTask(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRecordTask(IDvInvocation& aInvocation, TUint aVersion);
    void DoEnableRecordTask(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisableRecordTask(IDvInvocation& aInvocation, TUint aVersion);
    void DoResetRecordTask(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRecordScheduleConflicts(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRecordTaskConflicts(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING1

