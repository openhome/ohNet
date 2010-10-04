#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP
#define HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ScheduledRecording:2
 */
class DvServiceUpnpOrgScheduledRecording2Cpp : public DvService
{
public:
    virtual ~DvServiceUpnpOrgScheduledRecording2Cpp() {}
    void SetPropertyLastChange(const std::string& aValue);
    void GetPropertyLastChange(std::string& aValue);
protected:
    DvServiceUpnpOrgScheduledRecording2Cpp(DvDeviceStd& aDevice);
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
    virtual void GetSortCapabilities(uint32_t aVersion, std::string& aSortCaps, uint32_t& aSortLevelCap);
    virtual void GetPropertyList(uint32_t aVersion, const std::string& aDataTypeID, std::string& aPropertyList);
    virtual void GetAllowedValues(uint32_t aVersion, const std::string& aDataTypeID, const std::string& aFilter, std::string& aPropertyInfo);
    virtual void GetStateUpdateID(uint32_t aVersion, uint32_t& aId);
    virtual void BrowseRecordSchedules(uint32_t aVersion, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void BrowseRecordTasks(uint32_t aVersion, const std::string& aRecordScheduleID, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CreateRecordSchedule(uint32_t aVersion, const std::string& aElements, std::string& aRecordScheduleID, std::string& aResult, uint32_t& aUpdateID);
    virtual void DeleteRecordSchedule(uint32_t aVersion, const std::string& aRecordScheduleID);
    virtual void GetRecordSchedule(uint32_t aVersion, const std::string& aRecordScheduleID, const std::string& aFilter, std::string& aResult, uint32_t& aUpdateID);
    virtual void EnableRecordSchedule(uint32_t aVersion, const std::string& aRecordScheduleID);
    virtual void DisableRecordSchedule(uint32_t aVersion, const std::string& aRecordScheduleID);
    virtual void DeleteRecordTask(uint32_t aVersion, const std::string& aRecordTaskID);
    virtual void GetRecordTask(uint32_t aVersion, const std::string& aRecordTaskID, const std::string& aFilter, std::string& aResult, uint32_t& aUpdateID);
    virtual void EnableRecordTask(uint32_t aVersion, const std::string& aRecordTaskID);
    virtual void DisableRecordTask(uint32_t aVersion, const std::string& aRecordTaskID);
    virtual void ResetRecordTask(uint32_t aVersion, const std::string& aRecordTaskID);
    virtual void GetRecordScheduleConflicts(uint32_t aVersion, const std::string& aRecordScheduleID, std::string& aRecordScheduleConflictIDList, uint32_t& aUpdateID);
    virtual void GetRecordTaskConflicts(uint32_t aVersion, const std::string& aRecordTaskID, std::string& aRecordTaskConflictIDList, uint32_t& aUpdateID);
private:
    DvServiceUpnpOrgScheduledRecording2Cpp();
    void DoGetSortCapabilities(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetPropertyList(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetAllowedValues(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetStateUpdateID(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoBrowseRecordSchedules(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoBrowseRecordTasks(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoCreateRecordSchedule(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteRecordSchedule(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRecordSchedule(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoEnableRecordSchedule(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDisableRecordSchedule(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteRecordTask(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRecordTask(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoEnableRecordTask(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDisableRecordTask(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoResetRecordTask(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRecordScheduleConflicts(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRecordTaskConflicts(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP

