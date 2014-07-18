#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP
#define HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

#include <string>

namespace OpenHome {
namespace Net {

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
     * Can only be called if EnablePropertyLastChange has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyLastChange(const std::string& aValue);
    /**
     * Get a copy of the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
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
     * Enable the LastChange property.
     */
    void EnablePropertyLastChange();
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
    virtual void GetSortCapabilities(IDvInvocationStd& aInvocation, std::string& aSortCaps, uint32_t& aSortLevelCap);
    /**
     * GetPropertyList action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPropertyList action for the owning device.
     * Must be implemented iff EnableActionGetPropertyList was called.
     */
    virtual void GetPropertyList(IDvInvocationStd& aInvocation, const std::string& aDataTypeID, std::string& aPropertyList);
    /**
     * GetAllowedValues action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetAllowedValues action for the owning device.
     * Must be implemented iff EnableActionGetAllowedValues was called.
     */
    virtual void GetAllowedValues(IDvInvocationStd& aInvocation, const std::string& aDataTypeID, const std::string& aFilter, std::string& aPropertyInfo);
    /**
     * GetStateUpdateID action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStateUpdateID action for the owning device.
     * Must be implemented iff EnableActionGetStateUpdateID was called.
     */
    virtual void GetStateUpdateID(IDvInvocationStd& aInvocation, uint32_t& aId);
    /**
     * BrowseRecordSchedules action.
     *
     * Will be called when the device stack receives an invocation of the
     * BrowseRecordSchedules action for the owning device.
     * Must be implemented iff EnableActionBrowseRecordSchedules was called.
     */
    virtual void BrowseRecordSchedules(IDvInvocationStd& aInvocation, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * BrowseRecordTasks action.
     *
     * Will be called when the device stack receives an invocation of the
     * BrowseRecordTasks action for the owning device.
     * Must be implemented iff EnableActionBrowseRecordTasks was called.
     */
    virtual void BrowseRecordTasks(IDvInvocationStd& aInvocation, const std::string& aRecordScheduleID, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * CreateRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionCreateRecordSchedule was called.
     */
    virtual void CreateRecordSchedule(IDvInvocationStd& aInvocation, const std::string& aElements, std::string& aRecordScheduleID, std::string& aResult, uint32_t& aUpdateID);
    /**
     * DeleteRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionDeleteRecordSchedule was called.
     */
    virtual void DeleteRecordSchedule(IDvInvocationStd& aInvocation, const std::string& aRecordScheduleID);
    /**
     * GetRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionGetRecordSchedule was called.
     */
    virtual void GetRecordSchedule(IDvInvocationStd& aInvocation, const std::string& aRecordScheduleID, const std::string& aFilter, std::string& aResult, uint32_t& aUpdateID);
    /**
     * EnableRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * EnableRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionEnableRecordSchedule was called.
     */
    virtual void EnableRecordSchedule(IDvInvocationStd& aInvocation, const std::string& aRecordScheduleID);
    /**
     * DisableRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisableRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionDisableRecordSchedule was called.
     */
    virtual void DisableRecordSchedule(IDvInvocationStd& aInvocation, const std::string& aRecordScheduleID);
    /**
     * DeleteRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteRecordTask action for the owning device.
     * Must be implemented iff EnableActionDeleteRecordTask was called.
     */
    virtual void DeleteRecordTask(IDvInvocationStd& aInvocation, const std::string& aRecordTaskID);
    /**
     * GetRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordTask action for the owning device.
     * Must be implemented iff EnableActionGetRecordTask was called.
     */
    virtual void GetRecordTask(IDvInvocationStd& aInvocation, const std::string& aRecordTaskID, const std::string& aFilter, std::string& aResult, uint32_t& aUpdateID);
    /**
     * EnableRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * EnableRecordTask action for the owning device.
     * Must be implemented iff EnableActionEnableRecordTask was called.
     */
    virtual void EnableRecordTask(IDvInvocationStd& aInvocation, const std::string& aRecordTaskID);
    /**
     * DisableRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisableRecordTask action for the owning device.
     * Must be implemented iff EnableActionDisableRecordTask was called.
     */
    virtual void DisableRecordTask(IDvInvocationStd& aInvocation, const std::string& aRecordTaskID);
    /**
     * ResetRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * ResetRecordTask action for the owning device.
     * Must be implemented iff EnableActionResetRecordTask was called.
     */
    virtual void ResetRecordTask(IDvInvocationStd& aInvocation, const std::string& aRecordTaskID);
    /**
     * GetRecordScheduleConflicts action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordScheduleConflicts action for the owning device.
     * Must be implemented iff EnableActionGetRecordScheduleConflicts was called.
     */
    virtual void GetRecordScheduleConflicts(IDvInvocationStd& aInvocation, const std::string& aRecordScheduleID, std::string& aRecordScheduleConflictIDList, uint32_t& aUpdateID);
    /**
     * GetRecordTaskConflicts action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordTaskConflicts action for the owning device.
     * Must be implemented iff EnableActionGetRecordTaskConflicts was called.
     */
    virtual void GetRecordTaskConflicts(IDvInvocationStd& aInvocation, const std::string& aRecordTaskID, std::string& aRecordTaskConflictIDList, uint32_t& aUpdateID);
private:
    DvProviderUpnpOrgScheduledRecording2Cpp();
    void DoGetSortCapabilities(IDviInvocation& aInvocation);
    void DoGetPropertyList(IDviInvocation& aInvocation);
    void DoGetAllowedValues(IDviInvocation& aInvocation);
    void DoGetStateUpdateID(IDviInvocation& aInvocation);
    void DoBrowseRecordSchedules(IDviInvocation& aInvocation);
    void DoBrowseRecordTasks(IDviInvocation& aInvocation);
    void DoCreateRecordSchedule(IDviInvocation& aInvocation);
    void DoDeleteRecordSchedule(IDviInvocation& aInvocation);
    void DoGetRecordSchedule(IDviInvocation& aInvocation);
    void DoEnableRecordSchedule(IDviInvocation& aInvocation);
    void DoDisableRecordSchedule(IDviInvocation& aInvocation);
    void DoDeleteRecordTask(IDviInvocation& aInvocation);
    void DoGetRecordTask(IDviInvocation& aInvocation);
    void DoEnableRecordTask(IDviInvocation& aInvocation);
    void DoDisableRecordTask(IDviInvocation& aInvocation);
    void DoResetRecordTask(IDviInvocation& aInvocation);
    void DoGetRecordScheduleConflicts(IDviInvocation& aInvocation);
    void DoGetRecordTaskConflicts(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING2CPP

