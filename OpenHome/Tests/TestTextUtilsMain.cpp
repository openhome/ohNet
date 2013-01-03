#include <OpenHome/Private/TestFramework.h>

extern void TestTextUtils();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestTextUtils();
    delete lib;
}
