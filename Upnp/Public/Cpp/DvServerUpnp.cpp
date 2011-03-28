#include <DvServerUpnp.h>
#include <Core/DvDevice.h>
#include <DviDevice.h>
#include <DviServerUpnp.h>

using namespace Zapp;

DvServerUpnp::DvServerUpnp()
{
    iServer = new DviServerUpnp();
}

DvServerUpnp::~DvServerUpnp()
{
    delete iServer;
}

void DvServerUpnp::AddDevice(DvDevice& aDevice)
{
    aDevice.Device().SetCustomData("Upnp", "Server", iServer);
}
