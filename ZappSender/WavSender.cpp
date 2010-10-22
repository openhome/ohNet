#include <ZappTypes.h>
#include <Core/DvDevice.h>
#include <Zapp.h>
#include <Core/CpDevice.h>
#include <Core/CpDeviceUpnp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>

#include <vector>

#include "OhmSender.h"

using namespace Zapp;

static void RandomiseUdn(Bwh& aUdn)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    TUint max = nif->Address();
    delete nif;
    (void)Ascii::AppendDec(buf, Random(max));
    aUdn.Append(buf);
    aUdn.PtrZ();
}

int main(int argc, char* argv[])
{
    InitialisationParams* initParams = InitialisationParams::Create();

    UpnpLibrary::Initialise(initParams);
    
    UpnpLibrary::StartDv();

	Bwh udn("device");
    RandomiseUdn(udn);

    DvDevice* device = new DvDevice(udn);
    
    device->SetAttribute("Upnp.Domain", "zapp.org");
    device->SetAttribute("Upnp.Type", "MultipusSender");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", "WavPlayer");
    device->SetAttribute("Upnp.Manufacturer", "Linn Products Limited");
    device->SetAttribute("Upnp.ManufacturerUrl", "http://www.linn.co.uk");
    device->SetAttribute("Upnp.ModelDescription", "Multipus Wav Player");
    device->SetAttribute("Upnp.ModelName", "WavPlayer");
    device->SetAttribute("Upnp.ModelNumber", "1");
    device->SetAttribute("Upnp.ModelUrl", "http://www.linn.co.uk");
    device->SetAttribute("Upnp.SerialNumber", "123456");
    device->SetAttribute("Upnp.Upc", "123456789");

	OhmSender* sender = new OhmSender(*device);
	
    device->SetEnabled();
    
    Mutex mutex("WAIT");
    
    mutex.Wait();
    
    delete (sender);
    
    return (0);
}

