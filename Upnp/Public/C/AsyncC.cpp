#include <C/Async.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>

using namespace Zapp;


class AsyncOutput : public IAsyncOutput
{
public:
    AsyncOutput(ZappCallbackAsyncOutput aOutput);
    void Output(const TChar* aKey, const TChar* aValue);
private:
    ZappCallbackAsyncOutput iOutput;
};

AsyncOutput::AsyncOutput(ZappCallbackAsyncOutput aOutput)
{
    iOutput = aOutput;
}

void AsyncOutput::Output(const TChar* aKey, const TChar* aValue)
{
    iOutput(aKey, aValue);
}


void ZappAsyncOutput(ZappHandleAsync aAsync, ZappCallbackAsyncOutput aOutput)
{
    AsyncOutput ao(aOutput);
    ((IAsync*)aAsync)->Output(ao);
}
