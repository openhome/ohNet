#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING1
#define HEADER_DVUPNPORGSCHEDULEDRECORDING1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ScheduledRecording:1
 */
class DvProviderUpnpOrgScheduledRecording1 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgScheduledRecording1() {}
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
protected:
    DvProviderUpnpOrgScheduledRecording1(DvDevice& aDevice);
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
    DvProviderUpnpOrgScheduledRecording1();
    void DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetPropertyList(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetAllowedValues(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStateUpdateID(IDviInvocation& aInvocation, TUint aVersion);
    void DoBrowseRecordSchedules(IDviInvocation& aInvocation, TUint aVersion);
    void DoBrowseRecordTasks(IDviInvocation& aInvocation, TUint aVersion);
    void DoCreateRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoEnableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoEnableRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisableRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoResetRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRecordScheduleConflicts(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRecordTaskConflicts(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING1

