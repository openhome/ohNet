#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Network.h>

using namespace OpenHome;
using namespace OpenHome::Net;

EOhNetLibraryInitError STDCALL OhNetLibraryStartDv()
{
    try {
        UpnpLibrary::StartDv();
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
