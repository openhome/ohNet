#include "TestRadio.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Tests/Cdecl.h>
#include <OpenHome/Media/Tests/GetCh.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;

TestRadio* CreateRadio(Net::DvStack& aDvStack, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
{
    return new TestRadio(aDvStack, aAdapter, aSenderUdn, aSenderFriendlyName, aSenderChannel);
}

int CDECL main(int aArgc, char* aArgv[])
{
    std::vector<const TChar*> presets;
    presets.push_back("http://opml.radiotime.com/Tune.ashx?id=s2377&formats=mp3,wma,aac,wmvideo,ogg&partnerId=ah2rjr68&username=chisholmsi&c=ebrowse");   // (Planet Rock, AAC, 22.05KHz, mono)
    presets.push_back("http://opml.radiotime.com/Tune.ashx?id=s24940&formats=mp3,wma,aac,wmvideo,ogg&partnerId=ah2rjr68&username=chisholmsi&c=ebrowse");  // (Radio 2, AAC)

    return OpenHome::Av::Test::ExecuteTestRadio(aArgc, aArgv, CreateRadio, presets);
}
