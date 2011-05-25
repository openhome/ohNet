#include <AsyncPrivate.h>
#include <FunctorAsync.h>
#include <OhNetTypes.h>
#include <Thread.h>
#include <CpProxy.h>

using namespace OpenHome::Net;

FunctorAsync& SyncProxyAction::Functor()
{
    return iFunctor;
}

void SyncProxyAction::Wait()
{
    iSem.Wait();
    if (iError) {
        THROW(ProxyError);
    }
}

SyncProxyAction::SyncProxyAction()
    : iSem("SYNC", 0)
    , iError(false)
{
    iFunctor = MakeFunctorAsync(*this, &SyncProxyAction::Completed);
}

SyncProxyAction::~SyncProxyAction()
{
}    

void SyncProxyAction::Completed(IAsync& aAsync)
{
    try {
        CompleteRequest(aAsync);
    }
    catch(ProxyError&) {
        iError = true;
        iSem.Signal();
        THROW(ProxyError);
    }
    iSem.Signal();
}
