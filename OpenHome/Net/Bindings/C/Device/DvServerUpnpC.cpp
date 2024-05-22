#include <OpenHome/Net/C/DvServerUpnp.h>
#include <OpenHome/Net/Core/DvServerUpnp.h>
#include "DviDeviceC.h"
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Os.h>

using namespace OpenHome;
using namespace OpenHome::Net;

THandle STDCALL DvServerUpnpCreate()
{
    try {
        return new DvServerUpnp(*gDvStack);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

void STDCALL DvServerUpnpDestroy(THandle aServer)
{
    try {
        DvServerUpnp* server = reinterpret_cast<DvServerUpnp*>(aServer);
        delete server;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvServerUpnpAddDevice(THandle aServer, DvDeviceC aDevice)
{
    try {
        DvServerUpnp* server = reinterpret_cast<DvServerUpnp*>(aServer);
        ASSERT(server != NULL);
        DvDevice* device = DviDeviceC::DeviceFromHandle(aDevice);
        ASSERT(device != NULL);
        server->AddDevice(*device);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}
