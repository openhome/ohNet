#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING2
#define HEADER_DVUPNPORGSCHEDULEDRECORDING2

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
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
class DvProviderUpnpOrgScheduledRecording2 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgScheduledRecording2() {}
    /**
     * Set the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyLastChange(const Brx& aValue);
    /**
     * Get a copy of the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
     */
    void GetPropertyLastChange(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgScheduledRecording2(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgScheduledRecording2(DviDevice& aDevice);
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
    virtual void GetSortCapabilities(IDvInvocation& aInvocation, IDvInvocationResponseString& aSortCaps, IDvInvocationResponseUint& aSortLevelCap);
    /**
     * GetPropertyList action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPropertyList action for the owning device.
     * Must be implemented iff EnableActionGetPropertyList was called.
     */
    virtual void GetPropertyList(IDvInvocation& aInvocation, const Brx& aDataTypeID, IDvInvocationResponseString& aPropertyList);
    /**
     * GetAllowedValues action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetAllowedValues action for the owning device.
     * Must be implemented iff EnableActionGetAllowedValues was called.
     */
    virtual void GetAllowedValues(IDvInvocation& aInvocation, const Brx& aDataTypeID, const Brx& aFilter, IDvInvocationResponseString& aPropertyInfo);
    /**
     * GetStateUpdateID action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStateUpdateID action for the owning device.
     * Must be implemented iff EnableActionGetStateUpdateID was called.
     */
    virtual void GetStateUpdateID(IDvInvocation& aInvocation, IDvInvocationResponseUint& aId);
    /**
     * BrowseRecordSchedules action.
     *
     * Will be called when the device stack receives an invocation of the
     * BrowseRecordSchedules action for the owning device.
     * Must be implemented iff EnableActionBrowseRecordSchedules was called.
     */
    virtual void BrowseRecordSchedules(IDvInvocation& aInvocation, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IDvInvocationResponseString& aResult, IDvInvocationResponseUint& aNumberReturned, IDvInvocationResponseUint& aTotalMatches, IDvInvocationResponseUint& aUpdateID);
    /**
     * BrowseRecordTasks action.
     *
     * Will be called when the device stack receives an invocation of the
     * BrowseRecordTasks action for the owning device.
     * Must be implemented iff EnableActionBrowseRecordTasks was called.
     */
    virtual void BrowseRecordTasks(IDvInvocation& aInvocation, const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IDvInvocationResponseString& aResult, IDvInvocationResponseUint& aNumberReturned, IDvInvocationResponseUint& aTotalMatches, IDvInvocationResponseUint& aUpdateID);
    /**
     * CreateRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionCreateRecordSchedule was called.
     */
    virtual void CreateRecordSchedule(IDvInvocation& aInvocation, const Brx& aElements, IDvInvocationResponseString& aRecordScheduleID, IDvInvocationResponseString& aResult, IDvInvocationResponseUint& aUpdateID);
    /**
     * DeleteRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionDeleteRecordSchedule was called.
     */
    virtual void DeleteRecordSchedule(IDvInvocation& aInvocation, const Brx& aRecordScheduleID);
    /**
     * GetRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionGetRecordSchedule was called.
     */
    virtual void GetRecordSchedule(IDvInvocation& aInvocation, const Brx& aRecordScheduleID, const Brx& aFilter, IDvInvocationResponseString& aResult, IDvInvocationResponseUint& aUpdateID);
    /**
     * EnableRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * EnableRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionEnableRecordSchedule was called.
     */
    virtual void EnableRecordSchedule(IDvInvocation& aInvocation, const Brx& aRecordScheduleID);
    /**
     * DisableRecordSchedule action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisableRecordSchedule action for the owning device.
     * Must be implemented iff EnableActionDisableRecordSchedule was called.
     */
    virtual void DisableRecordSchedule(IDvInvocation& aInvocation, const Brx& aRecordScheduleID);
    /**
     * DeleteRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteRecordTask action for the owning device.
     * Must be implemented iff EnableActionDeleteRecordTask was called.
     */
    virtual void DeleteRecordTask(IDvInvocation& aInvocation, const Brx& aRecordTaskID);
    /**
     * GetRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordTask action for the owning device.
     * Must be implemented iff EnableActionGetRecordTask was called.
     */
    virtual void GetRecordTask(IDvInvocation& aInvocation, const Brx& aRecordTaskID, const Brx& aFilter, IDvInvocationResponseString& aResult, IDvInvocationResponseUint& aUpdateID);
    /**
     * EnableRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * EnableRecordTask action for the owning device.
     * Must be implemented iff EnableActionEnableRecordTask was called.
     */
    virtual void EnableRecordTask(IDvInvocation& aInvocation, const Brx& aRecordTaskID);
    /**
     * DisableRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisableRecordTask action for the owning device.
     * Must be implemented iff EnableActionDisableRecordTask was called.
     */
    virtual void DisableRecordTask(IDvInvocation& aInvocation, const Brx& aRecordTaskID);
    /**
     * ResetRecordTask action.
     *
     * Will be called when the device stack receives an invocation of the
     * ResetRecordTask action for the owning device.
     * Must be implemented iff EnableActionResetRecordTask was called.
     */
    virtual void ResetRecordTask(IDvInvocation& aInvocation, const Brx& aRecordTaskID);
    /**
     * GetRecordScheduleConflicts action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordScheduleConflicts action for the owning device.
     * Must be implemented iff EnableActionGetRecordScheduleConflicts was called.
     */
    virtual void GetRecordScheduleConflicts(IDvInvocation& aInvocation, const Brx& aRecordScheduleID, IDvInvocationResponseString& aRecordScheduleConflictIDList, IDvInvocationResponseUint& aUpdateID);
    /**
     * GetRecordTaskConflicts action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRecordTaskConflicts action for the owning device.
     * Must be implemented iff EnableActionGetRecordTaskConflicts was called.
     */
    virtual void GetRecordTaskConflicts(IDvInvocation& aInvocation, const Brx& aRecordTaskID, IDvInvocationResponseString& aRecordTaskConflictIDList, IDvInvocationResponseUint& aUpdateID);
private:
    DvProviderUpnpOrgScheduledRecording2();
    void Construct();
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

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING2

