#ifndef HEADER_SERVICE_PROXY
#define HEADER_SERVICE_PROXY

#include <Functor.h>
#include <ZappTypes.h>
#include <Exception.h>

EXCEPTION(ProxyError);

namespace Zapp {

class CpiService;
class Mutex;

/**
 * Base class for all UPnP services
 */
class CpProxy
{
public:
    /**
     * Subscribe to notification of changes in state variables.
     * Use SetProperty[stateVarName]Changed() to register a callback on change
     * in a given variable or SetPropertyChangesComplete() to register a callback
     * which runs after each group of 1..n changes is processed.
     */
    void Subscribe();
    /**
     * Unsubscribe to notification of changes in state variables.
     * No further notifications will be published until Subscribe() is called again.
     */
    void Unsubscribe();
    /**
     * Register a callback which will run after each group of 1..n changes to
     * state variable is processed.
     *
     * @param[in]  aFunctor  The callback to be run
     */
    DllExport void SetPropertyChanged(Functor& aFunctor);
protected:
    DllExport CpProxy();
    DllExport virtual ~CpProxy();
    DllExport TBool ReportEvent();
private:
    void Construct();
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
    Functor iPropertyChanged;

    friend class CpProxyC;
};

} // namespace Zapp

#endif // HEADER_SERVICE_PROXY
