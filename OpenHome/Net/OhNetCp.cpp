#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/NetworkAdapterList.h>

using namespace OpenHome;
using namespace OpenHome::Net;

CpStack* Library::StartCp(TIpAddress aSubnet)
{
    iStack->NetworkAdapterList().SetCurrentSubnet(aSubnet);
    return new CpStack(*iStack);
}

void UpnpLibrary::StartCp(TIpAddress aSubnet)
{ // static
    gStack->NetworkAdapterList().SetCurrentSubnet(aSubnet);
    gCpStack = new CpStack(*gStack);
}
