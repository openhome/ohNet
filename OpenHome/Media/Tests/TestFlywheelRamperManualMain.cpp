#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;

extern void TestFlywheelRamperManual(Net::Library& aLib, TChar* aArgv[]);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestFlywheelRamperManual(*lib, aArgv);
    delete lib;
}
