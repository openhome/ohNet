#include <OpenHome/Private/TestFramework.h>

extern void TestBuffer();
extern void TestThread();
extern void TestFifo();
extern void TestFile();
extern void TestTimer();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestBuffer();
    TestThread();
    TestFifo();
    TestFile();
    TestTimer();








    delete aInitParams;
    Net::UpnpLibrary::Close();
}
