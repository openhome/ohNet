#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Exception.h>

EXCEPTION(NoEnvProbe)

using namespace OpenHome;

extern void TestException();
extern TBool gThrewWithNoEnv;

static TBool ThrowAndCatch()
{
    try {
        THROW(NoEnvProbe);
    }
    catch (NoEnvProbe&) {
        return true;
    }
    return false;
}

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    // before Initialise(): gEnv is still NULL
    gThrewWithNoEnv = ThrowAndCatch();

    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestException();
    delete aInitParams;
    Net::UpnpLibrary::Close();

    // after Close(): gEnv is NULL again.  Nothing left to report to, so this
    // only has to not crash the process.
    (void)ThrowAndCatch();
}
