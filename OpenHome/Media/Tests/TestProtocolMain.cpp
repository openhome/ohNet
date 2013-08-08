#include "TestProtocol.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Tests/Cdecl.h>
#include <OpenHome/Media/Tests/GetCh.h>

using namespace OpenHome;
using namespace OpenHome::Media;

TestProtocol* CreateTestProtocol(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
{
    return new TestProtocol(aEnv, aDvStack, aUrl, aAdapter, aSenderUdn, aSenderFriendlyName, aSenderChannel);
}

int CDECL main(int aArgc, char* aArgv[])
{
    return OpenHome::Media::ExecuteTestProtocol(aArgc, aArgv, CreateTestProtocol);
}
