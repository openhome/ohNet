#include <OpenHome/Net/C/Async.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class AsyncOutput : public IAsyncOutput
{
public:
    AsyncOutput(OhNetCallbackAsyncOutput aOutput);
    void Output(const TChar* aKey, const TChar* aValue);
    virtual ~AsyncOutput() {}
private:
    OhNetCallbackAsyncOutput iOutput;
};

AsyncOutput::AsyncOutput(OhNetCallbackAsyncOutput aOutput)
{
    iOutput = aOutput;
}

void AsyncOutput::Output(const TChar* aKey, const TChar* aValue)
{
    iOutput(aKey, aValue);
}


void STDCALL OhNetAsyncOutput(OhNetHandleAsync aAsync, OhNetCallbackAsyncOutput aOutput)
{
    AsyncOutput ao(aOutput);
    ((IAsync*)aAsync)->Output(ao);
}
