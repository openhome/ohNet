#ifndef HEADER_DVSERVERUPNPC
#define HEADER_DVSERVERUPNPC

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvDevice
 * @ingroup Device
 * @{
 */

DllExport THandle DvServerUpnpCreate();
DllExport void DvServerUpnpDestroy(THandle aServer);
DllExport void DvServerUpnpAddDevice(THandle aServer, DvDeviceC aDevice);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVSERVERUPNPC