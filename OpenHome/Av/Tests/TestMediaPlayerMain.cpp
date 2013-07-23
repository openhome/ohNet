#include <OpenHome/OhNetTypes.h>
#include "TestMediaPlayer.h"
#include <OpenHome/Media/Tests/W32Cdecl.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;

TestMediaPlayer* CreateMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, TUint aMaxDriverJiffies, const TChar* aTuneInUserName)
{
    return new TestMediaPlayer(aDvStack, aUdn, aRoom, aProductName, aMaxDriverJiffies, aTuneInUserName);
}

int CDECL main(int aArgc, char* aArgv[])
{
    return OpenHome::Av::Test::ExecuteTestMediaPlayer(aArgc, aArgv, CreateMediaPlayer);
}
