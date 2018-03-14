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
    AutoSemaphoreSignal sem(iSem);
    try {
        CompleteRequest(aAsync);
    }
    catch (const ProxyError& aProxyError) {
        iError = aProxyError;
        throw;
    }
    catch (const AssertionFailed&) {
        // Don't lose callstack of original assertion.
        throw;
    }
    catch (const Exception&) {
        // No other type of exception expected to be thrown here.
        ASSERTS();
    }
}
