#include <OpenHome/Private/TestFramework.h>

extern void TestTimerMock();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::Library lib(aInitParams);
    TestTimerMock();
}

