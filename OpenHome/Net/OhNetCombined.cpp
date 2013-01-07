#include <OpenHome/Net/Core/OhNet.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void Library::StartCombined(TIpAddress aSubnet, CpStack*& aCpStack, DvStack*& aDvStack)
{
    aCpStack = StartCp(aSubnet);
    aDvStack = StartDv();
}

void UpnpLibrary::StartCombined(TIpAddress aSubnet)
{ // static
    UpnpLibrary::StartCp(aSubnet);
    UpnpLibrary::StartDv();
}
