#include <OhNet.h>
#include <CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void UpnpLibrary::StartCp(TIpAddress aSubnet)
{
    Stack::NetworkInterfaceList().SetCurrentSubnet(aSubnet);
    new CpiStack();
}
