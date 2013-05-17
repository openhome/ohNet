#include "SongcastingDriver.h"

using namespace OpenHome;
using namespace OpenHome::Media;

// SimpleSongcastingDriver

SimpleSongcastingDriver::SimpleSongcastingDriver(Net::DvStack& aDvStack, IPipelineElementUpstream& aPipeline, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
{
    iDevice = new Net::DvDeviceStandard(aDvStack, aSenderUdn);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Sender");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", aSenderFriendlyName);
    iDevice->SetAttribute("Upnp.Manufacturer", "Openhome");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "ohMediaPlayer SoftPlayer");
    iDevice->SetAttribute("Upnp.ModelName", "ohMediaPlayer SoftPlayer");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "");
    iDevice->SetAttribute("Upnp.Upc", "");

    iDriver = new DriverSongcastSender(aPipeline, kMaxDriverJiffies, aDvStack.Env(), *iDevice, aSenderUdn, aSenderChannel, aAdapter, false /*unicast*/);
    iDevice->SetEnabled();
}

SimpleSongcastingDriver::~SimpleSongcastingDriver()
{
    delete iDriver;
    delete iDevice;
}
