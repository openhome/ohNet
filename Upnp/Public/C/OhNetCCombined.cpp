#include <C/OhNet.h>
#include <OhNet.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void STDCALL OhNetLibraryStartCombined(TIpAddress aSubnet)
{
    UpnpLibrary::StartCombined(aSubnet);
}
