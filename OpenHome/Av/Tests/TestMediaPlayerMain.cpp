#include "TestMediaPlayer.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Tests/Cdecl.h>
#include <OpenHome/Media/Tests/GetCh.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;

TestMediaPlayer* CreateMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, const TChar* aTuneInUserName)
{
    return new TestMediaPlayer(aDvStack, aUdn, aRoom, aProductName, aTuneInUserName);
}

int CDECL main(int aArgc, char* aArgv[])
{
#ifdef _WIN32
    char* noErrDlgs = getenv("NO_ERROR_DIALOGS");
    if (noErrDlgs != NULL && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
#endif // _WIN32
    return OpenHome::Av::Test::ExecuteTestMediaPlayer(aArgc, aArgv, CreateMediaPlayer);
}
