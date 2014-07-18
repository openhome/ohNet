#ifndef HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1CPP
#define HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1CPP

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
 * Provider for the openhome.org:SubscriptionLongPoll:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Subscribe is supported.
     * The action's availability will be published in the device's service.xml.
     * Subscribe must be overridden if this is called.
     */
    void EnableActionSubscribe();
    /**
     * Signal that the action Unsubscribe is supported.
     * The action's availability will be published in the device's service.xml.
     * Unsubscribe must be overridden if this is called.
     */
    void EnableActionUnsubscribe();
    /**
     * Signal that the action Renew is supported.
     * The action's availability will be published in the device's service.xml.
     * Renew must be overridden if this is called.
     */
    void EnableActionRenew();
    /**
     * Signal that the action GetPropertyUpdates is supported.
     * The action's availability will be published in the device's service.xml.
     * GetPropertyUpdates must be overridden if this is called.
     */
    void EnableActionGetPropertyUpdates();
private:
    /**
     * Subscribe action.
     *
     * Will be called when the device stack receives an invocation of the
     * Subscribe action for the owning device.
     * Must be implemented iff EnableActionSubscribe was called.
     */
    virtual void Subscribe(IDvInvocationStd& aInvocation, const std::string& aClientId, const std::string& aUdn, const std::string& aService, uint32_t aRequestedDuration, std::string& aSid, uint32_t& aDuration);
    /**
     * Unsubscribe action.
     *
     * Will be called when the device stack receives an invocation of the
     * Unsubscribe action for the owning device.
     * Must be implemented iff EnableActionUnsubscribe was called.
     */
    virtual void Unsubscribe(IDvInvocationStd& aInvocation, const std::string& aSid);
    /**
     * Renew action.
     *
     * Will be called when the device stack receives an invocation of the
     * Renew action for the owning device.
     * Must be implemented iff EnableActionRenew was called.
     */
    virtual void Renew(IDvInvocationStd& aInvocation, const std::string& aSid, uint32_t aRequestedDuration, uint32_t& aDuration);
    /**
     * GetPropertyUpdates action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPropertyUpdates action for the owning device.
     * Must be implemented iff EnableActionGetPropertyUpdates was called.
     */
    virtual void GetPropertyUpdates(IDvInvocationStd& aInvocation, const std::string& aClientId, std::string& aUpdates);
private:
    DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp();
    void DoSubscribe(IDviInvocation& aInvocation);
    void DoUnsubscribe(IDviInvocation& aInvocation);
    void DoRenew(IDviInvocation& aInvocation);
    void DoGetPropertyUpdates(IDviInvocation& aInvocation);
private:
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1CPP

