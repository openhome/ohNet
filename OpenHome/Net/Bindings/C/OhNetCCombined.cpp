#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

EOhNetLibraryInitError STDCALL OhNetLibraryStartCombined(uint32_t aSubnetV4)
{
    TIpAddress subnet;
    subnet.iFamily = kFamilyV4;
    subnet.iV4 = aSubnetV4;
    try {
        UpnpLibrary::StartCombined(subnet);
        gDvStack->Start();
    }
    catch (NetworkAddressInUse& ) {
        return eOhNetInitErrorNetworkAddressInUse;
    }
    catch (std::bad_alloc& ) {
        return eOhNetInitErrorNoMemory;
    }
    catch(...) {
        return eOhNetInitErrorGeneral;
    }
    return eOhNetInitErrorNone;
}
