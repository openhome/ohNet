#ifndef HEADER_SERVICE_PROXY
#define HEADER_SERVICE_PROXY

#include <OpenHome/Functor.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Buffer.h>

#include <map>

EXCEPTION(ProxyError);

namespace OpenHome {
class Mutex;
namespace Net {

class CpiDevice;
class CpiService;
class IOutputProcessor;
class IInvocable;
class Property;

/**
 * @internal
 */
class IEventProcessor
{
public:
    virtual void EventUpdateStart() = 0;
    virtual void EventUpdate(const Brx& aName, const Brx& aValue, IOutputProcessor& aProcessor) = 0;
    virtual void EventUpdateEnd() = 0;
    virtual ~IEventProcessor() {}
};

/**
 * Base class for all proxies
 * @ingroup ControlPoint
 */
class DllExportClass CpProxy : private IEventProcessor
{
public:
    /**
     * Subscribe to notification of changes in state variables.
     * Use SetProperty[stateVarName]Changed() to register a callback on change
     * in a given variable or SetPropertyChangesComplete() to register a callback
     * which runs after each group of 1..n changes is processed.
     */
    DllExport void Subscribe();
    /**
     * Unsubscribe to notification of changes in state variables.
     * No further notifications will be published until Subscribe() is called again.
     */
    DllExport void Unsubscribe();
    /**
     * Register a callback which will run after each group of 1..n changes to
     * state variable is processed.
     *
     * @param[in]  aFunctor  The callback to be run
     */
    DllExport void SetPropertyChanged(Functor& aFunctor);
    /**
     * Register a callback which will run when the state of all properties becomes available.
     * This is often the first point at which UI elements can be fully initialised.
     *
     * @param[in]  aFunctor  The callback to be run
     */
    DllExport void SetPropertyInitialEvent(Functor& aFunctor);
protected:
    DllExport CpProxy(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice);
    DllExport virtual ~CpProxy();

    /**
     * Lock properties for reading.  Intended for use before reading a property's value.
     */
    DllExport void PropertyReadLock() const;
    /**
     * Signal that reading of a property's value has completed.
     * Must be called once for each call to PropertyReadLock().
     */
    DllExport void PropertyReadUnlock() const;
    /**
     * Add a property (aka state variable) to the service
     * Passes ownership of aProperty
     * Properties should ideally be added on construction of a Service.  Properties
     * which are added after a call to Subscribe() will not be updated until an
     * unsubscribe followed by re-subscribe.
     */
    DllExport void AddProperty(Property* aProperty);

    DllExport void DestroyService();
    DllExport void ReportEvent(Functor aFunctor);
private: // IEventProcessor
    DllExport void EventUpdateStart();
    DllExport void EventUpdate(const Brx& aName, const Brx& aValue, IOutputProcessor& aProcessor);
    DllExport void EventUpdateEnd();
private:
    void operator=(const CpProxy&);
protected:
    enum SubscriptionStatus
    {
        eNotSubscribed
       ,eSubscribing
       ,eSubscribed
    };
protected:
    CpiService* iService;
    IInvocable& iInvocable;
    Mutex* iLock;
    SubscriptionStatus iCpSubscriptionStatus;
private:
    Functor iPropertyChanged;
    TBool iInitialEventDelivered;
    Functor iInitialEvent;
    typedef std::map<Brn,Property*,BufferCmp> PropertyMap;
    PropertyMap iProperties;
    mutable Mutex* iPropertyReadLock;
    Mutex* iPropertyWriteLock;
    Mutex* iInitialEventLock;

    friend class CpProxyC;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SERVICE_PROXY
