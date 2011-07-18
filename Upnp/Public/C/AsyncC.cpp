#include <C/Async.h>
#include <FunctorAsync.h>
#include <OhNetTypes.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class AsyncOutput : public IAsyncOutput
{
public:
    AsyncOutput(OhNetCallbackAsyncOutput aOutput);
    void Output(const TChar* aKey, const TChar* aValue);
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
