#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Core/OhNet.h>

using namespace OpenHome;

extern void TestXmlParser();

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestXmlParser();
    delete lib;
}
