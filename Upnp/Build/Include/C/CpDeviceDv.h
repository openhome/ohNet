#ifndef HEADER_CPDEVICEDVC
#define HEADER_CPDEVICEDVC

#include <C/CpDevice.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpDevice
 * @ingroup ControlPoint
 * @{
 */

/**
 * Create a Control point device which communicates directly with a device stack's device
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Device handle
 */
DllExport CpDeviceC CpDeviceDvCreate(DvDeviceC aDevice);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_CPDEVICEDVC
