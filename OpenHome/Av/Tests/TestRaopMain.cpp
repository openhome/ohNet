#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

extern void TestRaop();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestRaop();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
