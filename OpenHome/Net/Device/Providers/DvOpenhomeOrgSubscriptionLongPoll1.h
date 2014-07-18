#ifndef HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1
#define HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1

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
 * Provider for the openhome.org:SubscriptionLongPoll:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgSubscriptionLongPoll1 : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgSubscriptionLongPoll1() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgSubscriptionLongPoll1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgSubscriptionLongPoll1(DviDevice& aDevice);
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
    virtual void Subscribe(IDvInvocation& aInvocation, const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration, IDvInvocationResponseString& aSid, IDvInvocationResponseUint& aDuration);
    /**
     * Unsubscribe action.
     *
     * Will be called when the device stack receives an invocation of the
     * Unsubscribe action for the owning device.
     * Must be implemented iff EnableActionUnsubscribe was called.
     */
    virtual void Unsubscribe(IDvInvocation& aInvocation, const Brx& aSid);
    /**
     * Renew action.
     *
     * Will be called when the device stack receives an invocation of the
     * Renew action for the owning device.
     * Must be implemented iff EnableActionRenew was called.
     */
    virtual void Renew(IDvInvocation& aInvocation, const Brx& aSid, TUint aRequestedDuration, IDvInvocationResponseUint& aDuration);
    /**
     * GetPropertyUpdates action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPropertyUpdates action for the owning device.
     * Must be implemented iff EnableActionGetPropertyUpdates was called.
     */
    virtual void GetPropertyUpdates(IDvInvocation& aInvocation, const Brx& aClientId, IDvInvocationResponseString& aUpdates);
private:
    DvProviderOpenhomeOrgSubscriptionLongPoll1();
    void Construct();
    void DoSubscribe(IDviInvocation& aInvocation);
    void DoUnsubscribe(IDviInvocation& aInvocation);
    void DoRenew(IDviInvocation& aInvocation);
    void DoGetPropertyUpdates(IDviInvocation& aInvocation);
private:
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1

