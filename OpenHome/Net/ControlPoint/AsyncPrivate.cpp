#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/Error.h>

using namespace OpenHome;
using namespace OpenHome::Net;

FunctorAsync& SyncProxyAction::Functor()
{
    return iFunctor;
}

void SyncProxyAction::Wait()
{
    iSem.Wait();
    if ((Error::ELevel)iError.Level() != Error::eNone) {
        throw(iError);
    }
}

SyncProxyAction::SyncProxyAction()
    : iSem("SYNC", 0)
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
    catch(ProxyError& aProxyError) {
        iError = aProxyError;
        iSem.Signal();
        throw;
    }
    iSem.Signal();
}
