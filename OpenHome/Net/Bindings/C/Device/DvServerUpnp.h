#ifndef HEADER_DVSERVERUPNPC
#define HEADER_DVSERVERUPNPC

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvDevice
 * @ingroup Device
 * @{
 */

/**
 * Create an additional UPnP device server.
 *
 * This should not be required in normal use of the stack but may be necessary for unusual
 * cases where a provider is required to make blocking calls to a proxy.
 *
 * @return  Handle to a new server instance.
 */
DllExport THandle STDCALL DvServerUpnpCreate();

/**
 * Destroy an additional UPnP server.
 *
 * Must be called once for each call to DvServerUpnpCreate().  Any devices added to the server
 * will no longer be available over the network but will still need to be manually destroyed.
 *
 * @param[in] aServer   Handle returned by DvServerUpnpCreate()
 */
DllExport void STDCALL DvServerUpnpDestroy(THandle aServer);

/**
 * Publish a device using an additional UPnP server
 *
 * Must be called before the device is enabled.
 * The device will be published by the additional server only.
 *
 * @param[in] aServer   Handle returned by DvServerUpnpCreate()
 * @param[in] aDevice   Handle returned by DvDeviceCreate[NoResources]
 */
DllExport void STDCALL DvServerUpnpAddDevice(THandle aServer, DvDeviceC aDevice);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVSERVERUPNPC
