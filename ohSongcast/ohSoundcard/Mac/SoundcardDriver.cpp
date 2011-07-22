#include "../Soundcard.h"
#include "Driver/AudioDeviceInterface.h"

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>

#include "../../Ohm.h"
#include "../../OhmSender.h"

#include <sys/utsname.h>
#include <IOKit/IOKitLib.h>


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

    io_connect_t iHandle;
};


} // namespace Net
} // namespace OpenHome


EXCEPTION(SoundcardError);

using namespace OpenHome;
using namespace OpenHome::Net;


OhmSenderDriverMac::OhmSenderDriverMac()
{
    // find the service
    io_service_t service;
    service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching(AudioDeviceName));
    if (service == 0) {
        printf("+++++++++++++++++++++++ error1 \n");
        THROW(SoundcardError);
    }

    // open the service
    kern_return_t res;
    res = IOServiceOpen(service, mach_task_self(), 0, &iHandle);
    if (res != KERN_SUCCESS) {
        printf("+++++++++++++++++++++++ error2 \n");
        THROW(SoundcardError);
    }


    res = IOConnectCallScalarMethod(iHandle, eOpen, 0, 0, 0, 0);

//    uint64_t args[2];
//    args[0] = 32;
//    res = IOConnectCallScalarMethod(iHandle, eSetEnabled, args, 1, 0, 0);
//    args[0] = 36;
//    res = IOConnectCallScalarMethod(handle, eSetTtl, args, 1, 0, 0);

//    res = IOConnectCallScalarMethod(handle, eClose, 0, 0, 0, 0);


    // close the service
//    res = IOServiceClose(handle);
}

// IOhmSenderDriver
void OhmSenderDriverMac::SetEnabled(TBool aValue)
{
    printf(aValue ? "OhmSenderDriverMac: Enabled\n" : "OhmSenderDriverMac: Disabled\n");
}

void OhmSenderDriverMac::SetEndpoint(const Endpoint& aEndpoint)
{
    printf("OhmSenderDriverMac: Endpoint %8x:%d\n", aEndpoint.Address(), aEndpoint.Port());

    uint64_t args[2];
    args[0] = aEndpoint.Address();
    args[1] = aEndpoint.Port();
    kern_return_t res = IOConnectCallScalarMethod(iHandle, eSetEndpoint, args, 2, 0, 0);
    if (res)
    {
    }
}

void OhmSenderDriverMac::SetActive(TBool aValue)
{
    printf(aValue ? "OhmSenderDriverMac: Active\n" : "OhmSenderDriverMac: Inactive\n");

    uint64_t arg = aValue ? 1 : 0;
    kern_return_t res = IOConnectCallScalarMethod(iHandle, eSetActive, &arg, 1, 0, 0);
    if (res)
    {
    }
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
    OhmSenderDriverMac* driver;
    try {
        driver = new OhmSenderDriverMac();
    }
    catch (SoundcardError) {
        return 0;
    }

    Soundcard* soundcard = new Soundcard(aSubnet, aChannel, aTtl, aMulticast, aEnabled, aPreset, aReceiverCallback, aReceiverPtr, aSubnetCallback, aSubnetPtr, computer, driver);
    return soundcard;
}




