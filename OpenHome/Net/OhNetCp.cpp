#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void UpnpLibrary::StartCp(TIpAddress aSubnet)
{
    Stack::NetworkAdapterList().SetCurrentSubnet(aSubnet);
    new CpiStack();
}
