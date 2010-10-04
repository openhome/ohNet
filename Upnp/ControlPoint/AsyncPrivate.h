#ifndef HEADER_ASYNC_PRIVATE
#define HEADER_ASYNC_PRIVATE

#include <ZappTypes.h>
#include <FunctorAsync.h>
#include <Thread.h>

namespace Zapp {

class Async : public IAsync
{
public:
    enum EType
    {
        eInvocation
       ,eXmlFetch
    };
    virtual TUint Type() const = 0;
};


class SyncProxyAction
{
public:
    DllExport FunctorAsync& Functor();
    DllExport void Wait();
protected:
    DllExport SyncProxyAction();
    DllExport ~SyncProxyAction();
    virtual void CompleteRequest(IAsync& aAsync) = 0;
private:
    void Completed(IAsync& aAsync);
private:
    Semaphore iSem;
    FunctorAsync iFunctor;
    TBool iError;
};

} // namespace Zapp

#endif // HEADER_ASYNC_PRIVATE