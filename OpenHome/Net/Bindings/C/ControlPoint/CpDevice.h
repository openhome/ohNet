#ifndef HEADER_CPDEVICEC
#define HEADER_CPDEVICEC

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpDevice
 * @ingroup ControlPoint
 * @{
 */

/**
 * Opaque handle to a device
 */
typedef THandle CpDeviceC;

/**
 * Opaque handle to a list of devices
 */
typedef THandle HandleCpDeviceList;

/**
 * Read a device's udn (aka uuid, aka name)
 *
 * @param[in]  aDevice       Device originally returned to a 'added' version of DeviceListChanged
 *
 * @return  const pointer to the udn.
 */
DllExport const char* STDCALL CpDeviceCUdn(CpDeviceC aDevice);

/**
 * Read a device's udn (aka uuid, aka name)
 *
 * @param[in]  aDevice       Device originally returned to a 'added' version of DeviceListChanged
 * @param[out] aUdn          const pointer to the udn.  Ownership remains with aDevice.
 * @param[out] aLen          Length (in bytes) of aUdn
 */
DllExport void STDCALL CpDeviceCGetUdn(CpDeviceC aDevice, const char** aUdn, uint32_t* aLen);

/**
 * Claim a reference to a device.
 *
 * Devices passed to DeviceListChanged cannot be used outside the callback
 * unless the client claims a reference to it.
 *
 * @param[in]  aDevice       Device originally returned to a 'added' version of DeviceListChanged
 */
DllExport void STDCALL CpDeviceCAddRef(CpDeviceC aDevice);

/**
 * Release a reference to a device.
 *
 * The device will be destroyed when the last reference is released.
 * Each call to CpDeviceCAddRef() must be matched by exactly one call to CpDeviceCRemoveRef()
 *
 * @param[in]  aDevice       Device.  Probably passed to the 'removed' version of DeviceListChanged
 */
DllExport void STDCALL CpDeviceCRemoveRef(CpDeviceC aDevice);

/**
 * Read an attribute of the device.
 *
 * @param[in]  aDevice       Device originally returned to a 'added' version of DeviceListChanged
 * @param[in]  aKey          One from a protocol-specific list of available keys
 * @param[out] aValue        Nul-terminated attribute matching aKey.
 *                           Ownership is transferred to the caller.
 *
 * @return  1 if the attribute was available; 0 if it was not available
 */
DllExport int32_t STDCALL CpDeviceCGetAttribute(CpDeviceC aDevice, const char* aKey, char** aValue);

/**
 * Callback which will be run when devices are added to or removed from a protocol-specific list
 *
 * @param[in]  aPtr          Client-specified data
 * @param[in]  aDevice       Newly added/removed device.  The callback should add a
 *                           reference if it will want to use aDevice outside this
 *                           callback; any reference should normally be removed if
 *                           the device has been removed from its container list.
 */
typedef void (STDCALL *OhNetCallbackDevice)(void* aPtr, CpDeviceC aDevice);

/* @} */
/**
 * @addtogroup CpDeviceList
 * @ingroup ControlPoint
 * @{
 */

/**
 * Destroy a device list.
 * 'Removed' callbacks will not be run for the list's contents.
 *
 * @param[in]  aListHandle   List handle returned earlier from a protocol-specific constructor
 */
DllExport void STDCALL CpDeviceListDestroy(HandleCpDeviceList aListHandle);

/**
 * Refresh a device list.
 * 'Added'  or 'Removed' callbacks will be run if the list's contents change.
 *
 * @param[in]  aListHandle   List handle returned earlier from a protocol-specific constructor
 */
DllExport void STDCALL CpDeviceListRefresh(HandleCpDeviceList aListHandle);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_CPDEVICEC
