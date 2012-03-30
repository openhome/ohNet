#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Core/OhNet.h>

using namespace OpenHome;

extern void TestTimer();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::Initialise(aInitParams);
    TestTimer();
    Net::UpnpLibrary::Close();
}
