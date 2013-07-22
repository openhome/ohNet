#include <OpenHome/OhNetTypes.h>
#include "TestRadio.h"

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

TestRadio* OpenHome::Av::Test::CreateRadio(Net::DvStack& aDvStack, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
{
    return new TestRadio(aDvStack, aAdapter, aSenderUdn, aSenderFriendlyName, aSenderChannel);
}

int CDECL main(int aArgc, char* aArgv[])
{
    return OpenHome::Av::Test::ExecuteTestRadio(aArgc, aArgv);
}
