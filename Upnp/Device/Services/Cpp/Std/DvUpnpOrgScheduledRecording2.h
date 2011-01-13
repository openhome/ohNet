#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP
#define HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the upnp.org:ScheduledRecording:2 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgScheduledRecording2Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgScheduledRecording2Cpp() {}
    /**
     * Set the value of the LastChange property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyLastChange(const std::string& aValue);
    /**
     * Get a copy of the value of the LastChange property
     */
    void GetPropertyLastChange(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgScheduledRecording2Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action GetSortCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * GetSortCapabilities must be overridden if this is called.
     */
    void EnableActionGetSortCapabilities();
    /**
     * Signal that the action GetPropertyList is supported.
     * The action's availability will be published in the device's service.xml.
     * GetPropertyList must be overridden if this is called.
     */
    void EnableActionGetPropertyList();
    /**
     * Signal that the action GetAllowedValues is supported.
     * The action's availability will be published in the device's service.xml.
     * GetAllowedValues must be overridden if this is called.
     */
    void EnableActionGetAllowedValues();
    /**
     * Signal that the action GetStateUpdateID is supported.
     * The action's availability will be published in the device's service.xml.
     * GetStateUpdateID must be overridden if this is called.
     */
    void EnableActionGetStateUpdateID();
    /**
     * Signal that the action BrowseRecordSchedules is supported.
     * The action's availability will be published in the device's service.xml.
     * BrowseRecordSchedules must be overridden if this is called.
     */
    void EnableActionBrowseRecordSchedules();
    /**
     * Signal that the action BrowseRecordTasks is supported.
     * The action's availability will be published in the device's service.xml.
     * BrowseRecordTasks must be overridden if this is called.
     */
    void EnableActionBrowseRecordTasks();
    /**
     * Signal that the action CreateRecordSchedule is supported.
     * The action's availability will be published in the device's service.xml.
     * CreateRecordSchedule must be overridden if this is called.
     */
    void EnableActionCreateRecordSchedule();
    /**
     * Signal that the action DeleteRecordSchedule is supported.
     * The action's availability will be published in the device's service.xml.
     * DeleteRecordSchedule must be overridden if this is called.
     */
    void EnableActionDeleteRecordSchedule();
    /**
     * Signal that the action GetRecordSchedule is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRecordSchedule must be overridden if this is called.
     */
    void EnableActionGetRecordSchedule();
    /**
     * Signal that the action EnableRecordSchedule is supported.
     * The action's availability will be published in the device's service.xml.
     * EnableRecordSchedule must be overridden if this is called.
     */
    void EnableActionEnableRecordSchedule();
    /**
     * Signal that the action DisableRecordSchedule is supported.
     * The action's availability will be published in the device's service.xml.
     * DisableRecordSchedule must be overridden if this is called.
     */
    void EnableActionDisableRecordSchedule();
    /**
     * Signal that the action DeleteRecordTask is supported.
     * The action's availability will be published in the device's service.xml.
     * DeleteRecordTask must be overridden if this is called.
     */
    void EnableActionDeleteRecordTask();
    /**
     * Signal that the action GetRecordTask is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRecordTask must be overridden if this is called.
     */
    void EnableActionGetRecordTask();
    /**
     * Signal that the action EnableRecordTask is supported.
     * The action's availability will be published in the device's service.xml.
     * EnableRecordTask must be overridden if this is called.
     */
    void EnableActionEnableRecordTask();
    /**
     * Signal that the action DisableRecordTask is supported.
     * The action's availability will be published in the device's service.xml.
     * DisableRecordTask must be overridden if this is called.
     */
    void EnableActionDisableRecordTask();
    /**
     * Signal that the action ResetRecordTask is supported.
     * The action's availability will be published in the device's service.xml.
     * ResetRecordTask must be overridden if this is called.
     */
    void EnableActionResetRecordTask();
    /**
     * Signal that the action GetRecordScheduleConflicts is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRecordScheduleConflicts must be overridden if this is called.
     */
    void EnableActionGetRecordScheduleConflicts();
    /**
     * Signal that the action GetRecordTaskConflicts is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRecordTaskConflicts must be overridden if this is called.
     */
    void EnableActionGetRecordTaskConflicts();
private:
    /**
     * GetSortCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSortCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSortCapabilities was called.
     */
    virtual void GetSortCapabilities(uint32_t aVersion, std::string& aSortCaps, uint32_t& aSortLevelCap);
    /**
     * GetPropertyList action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPropertyList action for the owning device.
     * Must be implemented iff EnableActionGetPropertyList was called.
     */
    virtual void GetPropertyList(uint32_t aVersion, const std::string& aDataTypeID, std::string& aPropertyList);
    /**
     * GetAllowedValues action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetAllowedValues action for the owning device.
     * Must be implemented iff EnableActionGetAllowedValues was called.
     */
    virtual void GetAllowedValues(uint32_t aVersion, const std::string& aDataTypeID, const std::string& aFilter, std::string& aPropertyInfo);
    /**
     * GetStateUpdateID action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStateUpdateID action for the owning device.
     * Must be implemented iff EnableActionGetStateUpdateID was called.
     */
    virtual void GetStateUpdateID(uint32_t aVersion, uint32_t& aId);
    /**
     * BrowseRecordSchedules action.
     *
     * Will be called when the device stack receives an invocation of the
     * BrowseRecordSchedules action for the owning device.
     * Must be implemented iff EnableActionBrowseRecordSchedules was called.
     */
    virtual void BrowseRecordSchedules(uint32_t aVersion, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * BrowseRecordTasks action.
     *
     * Will be called when the device stack receives an invocation of the
     * BrowseRecordTasks action for the owning device.
     * Must be implemented iff EnableActionBrowseRecordTasks was called.
     */
    virtual void BrowseRecordTasks(uint32_t aVersion, const std::string& aRecordScheduleID, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * CreateRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionCreateRecordSchedule was called.
     */
    virtual void CreateRecordSchedule(uint32_t aVersion, const std::string& aElements, std::string& aRecordScheduleID, std::string& aResult, uint32_t& aUpdateID);
    /**
     * DeleteRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionDeleteRecordSchedule was called.
     */
    virtual void DeleteRecordSchedule(uint32_t aVersion, const std::string& aRecordScheduleID);
    /**
     * GetRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionGetRecordSchedule was called.
     */
    virtual void GetRecordSchedule(uint32_t aVersion, const std::string& aRecordScheduleID, const std::string& aFilter, std::string& aResult, uint32_t& aUpdateID);
    /**
     * EnableRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * EnableRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionEnableRecordSchedule was called.
     */
    virtual void EnableRecordSchedule(uint32_t aVersion, const std::string& aRecordScheduleID);
    /**
     * DisableRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisableRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionDisableRecordSchedule was called.
     */
    virtual void DisableRecordSchedule(uint32_t aVersion, const std::string& aRecordScheduleID);
    /**
     * DeleteRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteRecordTask action for the owning device.
     * Must be implemented iff EnableActionDeleteRecordTask was called.
     */
    virtual void DeleteRecordTask(uint32_t aVersion, const std::string& aRecordTaskID);
    /**
     * GetRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordTask action for the owning device.
     * Must be implemented iff EnableActionGetRecordTask was called.
     */
    virtual void GetRecordTask(uint32_t aVersion, const std::string& aRecordTaskID, const std::string& aFilter, std::string& aResult, uint32_t& aUpdateID);
    /**
     * EnableRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * EnableRecordTask action for the owning device.
     * Must be implemented iff EnableActionEnableRecordTask was called.
     */
    virtual void EnableRecordTask(uint32_t aVersion, const std::string& aRecordTaskID);
    /**
     * DisableRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisableRecordTask action for the owning device.
     * Must be implemented iff EnableActionDisableRecordTask was called.
     */
    virtual void DisableRecordTask(uint32_t aVersion, const std::string& aRecordTaskID);
    /**
     * ResetRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * ResetRecordTask action for the owning device.
     * Must be implemented iff EnableActionResetRecordTask was called.
     */
    virtual void ResetRecordTask(uint32_t aVersion, const std::string& aRecordTaskID);
    /**
     * GetRecordScheduleConflicts action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordScheduleConflicts action for the owning device.
     * Must be implemented iff EnableActionGetRecordScheduleConflicts was called.
     */
    virtual void GetRecordScheduleConflicts(uint32_t aVersion, const std::string& aRecordScheduleID, std::string& aRecordScheduleConflictIDList, uint32_t& aUpdateID);
    /**
     * GetRecordTaskConflicts action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordTaskConflicts action for the owning device.
     * Must be implemented iff EnableActionGetRecordTaskConflicts was called.
     */
    virtual void GetRecordTaskConflicts(uint32_t aVersion, const std::string& aRecordTaskID, std::string& aRecordTaskConflictIDList, uint32_t& aUpdateID);
private:
    DvProviderUpnpOrgScheduledRecording2Cpp();
    void DoGetSortCapabilities(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetPropertyList(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetAllowedValues(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetStateUpdateID(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBrowseRecordSchedules(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBrowseRecordTasks(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCreateRecordSchedule(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteRecordSchedule(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRecordSchedule(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoEnableRecordSchedule(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisableRecordSchedule(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteRecordTask(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRecordTask(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoEnableRecordTask(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisableRecordTask(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoResetRecordTask(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRecordScheduleConflicts(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRecordTaskConflicts(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP

