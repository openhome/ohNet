#include <OpenHome/Private/TestFramework.h>

extern void TestReporter();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    auto lib = new OpenHome::Net::Library(aInitParams);
    TestReporter();
    delete lib;
}
