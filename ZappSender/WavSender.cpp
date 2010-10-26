#include <ZappTypes.h>
#include <Core/DvDevice.h>
#include <Zapp.h>
#include <Core/CpDevice.h>
#include <Core/CpDeviceUpnp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>

#include <vector>
#include <stdio.h>

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

void DisplayHelp()
{
	printf("<ENTER> = exit, <h> = help\n");
}

int main(int argc, char* argv[])
{
    InitialisationParams* initParams = InitialisationParams::Create();

    UpnpLibrary::Initialise(initParams);
    
    UpnpLibrary::StartDv();

	Bwh udn("device");
    RandomiseUdn(udn);

    DvDevice* device = new DvDevice(udn);
    
    device->SetAttribute("Upnp.Domain", "music.openhome.org");
    device->SetAttribute("Upnp.Type", "Sender");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", "Openhome WavSender");
    device->SetAttribute("Upnp.Manufacturer", "Openhome");
    device->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    device->SetAttribute("Upnp.ModelDescription", "Openhome WavSender");
    device->SetAttribute("Upnp.ModelName", "Openhome WavSender");
    device->SetAttribute("Upnp.ModelNumber", "1");
    device->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    device->SetAttribute("Upnp.SerialNumber", "Not Applicable");
    device->SetAttribute("Upnp.Upc", "Not Applicable");

	OhmSender* sender = new OhmSender(*device, Brn("Test"), 123);
	
    device->SetEnabled();
    
    while (true) {
    	TChar key = getchar();
    	
    	if (key == '\n') {
    		break;
    	}
    	
    	if (key == 'h' || key == 'H')
    	{
    		DisplayHelp();
    	}
    }
    
    delete (sender);
    delete (device);
    
    return (0);
}

