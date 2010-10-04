#ifndef HEADER_CPDEVICEC
#define HEADER_CPDEVICEC

#include <OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

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
DllExport const char* CpDeviceCUdn(CpDeviceC aDevice);

/**
 * Claim a reference to a device.
 *
 * Devices passed to DeviceListChanged cannot be used outside the callback
 * unless the client claims a reference to it.
 *
 * @param[in]  aDevice       Device originally returned to a 'added' version of DeviceListChanged
 */
DllExport void CpDeviceCAddRef(CpDeviceC aDevice);

/**
 * Release a reference to a device.
 *
 * The device will be destroyed when the last reference is released.
 * Clients would normally release their reference to a device inside the 'removed'
 * version of DeviceListChanged
 *
 * @param[in]  aDevice       Device.  Probably passed to the 'removed' version of DeviceListChanged
 */
DllExport void CpDeviceCRemoveRef(CpDeviceC aDevice);

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
DllExport int32_t CpDeviceCGetAttribute(CpDeviceC aDevice, const char* aKey, char** aValue);

/**
 * Callback which will be run when devices are added to or removed from a protocol-specific list
 *
 * @param[in]  aPtr          Client-specified data
 * @param[in]  aDevice       Newly added/removed device.  The callback should add a
 *                           reference if it will want to use aDevice outside this
 *                           callback; any reference should normally be removed if
 *                           the device has been removed from its container list.
 */
typedef void (*ZappCallbackDevice)(void* aPtr, CpDeviceC aDevice);

/**
 * Destroy a device list.
 * 'Removed' callbacks will not be run for the list's contents.
 *
 * @param[in]  aListHandle   List handle returned earlier from a protocol-specific constructor
 */
DllExport void CpDeviceListDestroy(HandleCpDeviceList aListHandle);

/**
 * Refresh a device list.
 * 'Added'  or 'Removed' callbacks will be run if the list's contents change.
 *
 * @param[in]  aListHandle   List handle returned earlier from a protocol-specific constructor
 */
DllExport void CpDeviceListRefresh(HandleCpDeviceList aListHandle);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_CPDEVICEC
