#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

extern void TestMsg();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestMsg();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}

