#ifndef HEADER_SERVICE_PROXY
#define HEADER_SERVICE_PROXY

#include <Functor.h>
#include <ZappTypes.h>
#include <Exception.h>

EXCEPTION(ProxyError);

namespace Zapp {

class CpiDevice;
class CpiService;
class Mutex;

/**
 * Base class for all UPnP services
 */
class DllExportClass CpProxy
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
    DllExport void DestroyService();
    DllExport void ReportEvent(Functor aFunctor);
private:
    void PropertyChanged();
protected:
    enum SubscriptionStatus
    {
        eNotSubscribed
       ,eSubscribing
       ,eSubscribed
    };
protected:
    CpiService* iService;
    Mutex* iLock;
    SubscriptionStatus iCpSubscriptionStatus;
private:
    Functor iPropertyChanged;
    TBool iInitialEventDelivered;
    Functor iInitialEvent;

    friend class CpProxyC;
};

} // namespace Zapp

#endif // HEADER_SERVICE_PROXY
