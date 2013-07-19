#include <OpenHome/OhNetTypes.h>
#include "TestMediaPlayer.h"

#ifndef CDECL
# ifdef _WIN32
#  define CDECL __cdecl
# else
#  define CDECL
# endif
#endif

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;

TestMediaPlayer* OpenHome::Av::Test::CreateMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, TUint aMaxDriverJiffies, const TChar* aTuneInUserName)
{
    return new TestMediaPlayer(aDvStack, aUdn, aRoom, aProductName, aMaxDriverJiffies, aTuneInUserName);
}

int CDECL main(int aArgc, char* aArgv[])
{
    return OpenHome::Av::Test::ExecuteTestMediaPlayer(aArgc, aArgv);
}
