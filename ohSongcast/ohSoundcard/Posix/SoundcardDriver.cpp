#include "../Soundcard.h"

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>

#include "../../Ohm.h"
#include "../../OhmSender.h"

#include <sys/utsname.h>
#include <stdio.h>


namespace OpenHome {
namespace Net {

class OhmSenderDriverPosix : public IOhmSenderDriver
{
public:
    OhmSenderDriverPosix();

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


OhmSenderDriverPosix::OhmSenderDriverPosix()
{
}

// IOhmSenderDriver
void OhmSenderDriverPosix::SetEnabled(TBool aValue)
{
    printf(aValue ? "OhmSenderDriverPosix: Enabled\n" : "OhmSenderDriverPosix: Disabled\n");
}

void OhmSenderDriverPosix::SetEndpoint(const Endpoint& aEndpoint)
{
    printf("OhmSenderDriverPosix: Endpoint %8x:%d\n", aEndpoint.Address(), aEndpoint.Port());
}

void OhmSenderDriverPosix::SetActive(TBool aValue)
{
    printf(aValue ? "OhmSenderDriverPosix: Active\n" : "OhmSenderDriverPosix: Inactive\n");
}

void OhmSenderDriverPosix::SetTtl(TUint aValue)
{
    printf("OhmSenderDriverPosix: TTL %d\n", aValue);
}

void OhmSenderDriverPosix::SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal)
{
    printf("OhmSenderDriverPosix: TrackPosition %llu %llu\n", aSampleStart, aSamplesTotal);
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
    OhmSenderDriverPosix* driver = new OhmSenderDriverPosix();

    Soundcard* soundcard = new Soundcard(aSubnet, aChannel, aTtl, aMulticast, aEnabled, aPreset, aReceiverCallback, aReceiverPtr, aSubnetCallback, aSubnetPtr, computer, driver);
    return soundcard;
}




