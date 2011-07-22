#include <OpenHome/Net/Core/OhNet.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void UpnpLibrary::StartCombined(TIpAddress aSubnet)
{
    UpnpLibrary::StartCp(aSubnet);
    UpnpLibrary::StartDv();
}
