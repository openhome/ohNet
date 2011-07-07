#include "../Soundcard.h"

#include <OhNetTypes.h>
#include <OhNet.h>

#include "../../Ohm.h"
#include "../../OhmSender.h"

#include <sys/utsname.h>


namespace OpenHome {
namespace Net {

class OhmSenderDriverMac : public IOhmSenderDriver
{
public:
    OhmSenderDriverMac();

private:
    // IOhmSenderDriver
    virtual void SetEnabled(TBool aValue);
    virtual void SetEndpoint(const Endpoint& aEndpoint);
    virtual void SetActive(TBool aValue);
    virtual void SetTtl(TUint aValue);
    virtual void SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal);
};


} // namespace Net
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Net;


OhmSenderDriverMac::OhmSenderDriverMac()
{
}

// IOhmSenderDriver
void OhmSenderDriverMac::SetEnabled(TBool aValue)
{
    printf(aValue ? "OhmSenderDriverMac: Enabled\n" : "OhmSenderDriverMac: Disabled\n");
}

void OhmSenderDriverMac::SetEndpoint(const Endpoint& aEndpoint)
{
    printf("OhmSenderDriverMac: Endpoint %8x:%d\n", aEndpoint.Address(), aEndpoint.Port());
}

void OhmSenderDriverMac::SetActive(TBool aValue)
{
    printf(aValue ? "OhmSenderDriverMac: Active\n" : "OhmSenderDriverMac: Inactive\n");
}

void OhmSenderDriverMac::SetTtl(TUint aValue)
{
    printf("OhmSenderDriverMac: TTL %d\n", aValue);
}

void OhmSenderDriverMac::SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal)
{
    printf("OhmSenderDriverMac: TrackPosition %llu %llu\n", aSampleStart, aSamplesTotal);
}


// Soundcard - platform specific implementation of OpenHome::Net::Soundcard

Soundcard* Soundcard::Create(TIpAddress aSubnet, TUint aChannel, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr, SubnetCallback aSubnetCallback, void* aSubnetPtr)
{
    // get the computer name
    struct utsname name;
    if (uname(&name) < 0)
        return 0;

    Brn computer(name.nodename);

    // create the driver
    OhmSenderDriverMac* driver = new OhmSenderDriverMac();

    Soundcard* soundcard = new Soundcard(aSubnet, aChannel, aTtl, aMulticast, aEnabled, aPreset, aReceiverCallback, aReceiverPtr, aSubnetCallback, aSubnetPtr, computer, driver);
    return soundcard;
}




