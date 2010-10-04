#ifndef HEADER_CPDEVICEUPNPC
#define HEADER_CPDEVICEUPNPC

#include <OsTypes.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * CpDeviceCGetAttribute supports the following keys for devices created by
 * one of the lists below:
 *  location     - host portion of uri to the device
 *  deviceXml    - copy of the device XML
 *  friendlyName - user displayable name for the device
 *
 * All key names are case sensitive
 */

/**
 * Create a list of all UPnP devices on the current subnet
 *
 * @param[in] aAdded       Function pointer which is called when a device is added to the list
 * @param[in] aPtrAdded    Will be passed as the second parameter to aAdded
 * @param[in] aRemoved     Function pointer which is called when a device is removed from the list
 * @param[in] aPtrRemoved  Will be passed as the second parameter to aRemoved
 *
 * @return  Handle to the list.  Use CpDeviceListDestroy to later destroy the list.
 */
DllExport HandleCpDeviceList CpDeviceListCreateUpnpAll(ZappCallbackDevice aAdded, void* aPtrAdded,
                                                       ZappCallbackDevice aRemoved, void* aPtrRemoved);

/**
 * Create a list of all root UPnP devices on the current subnet
 *
 * @param[in] aAdded       Function pointer which is called when a device is added to the list
 * @param[in] aPtrAdded    Will be passed as the second parameter to aAdded
 * @param[in] aRemoved     Function pointer which is called when a device is removed from the list
 * @param[in] aPtrRemoved  Will be passed as the second parameter to aRemoved
 *
 * @return  Handle to the list.  Use CpDeviceListDestroy to later destroy the list.
 */
DllExport HandleCpDeviceList CpDeviceListCreateUpnpRoot(ZappCallbackDevice aAdded, void* aPtrAdded,
                                                        ZappCallbackDevice aRemoved, void* aPtrRemoved);

/**
 * Create a list of the UPnP [0..1] devices with the given uuid (udn) on the current subnet
 *
 * @param[in] aUuid        The device uuid(/udn/name) to search for
 * @param[in] aAdded       Function pointer which is called when a device is added to the list
 * @param[in] aPtrAdded    Will be passed as the second parameter to aAdded
 * @param[in] aRemoved     Function pointer which is called when a device is removed from the list
 * @param[in] aPtrRemoved  Will be passed as the second parameter to aRemoved
 *
 * @return  Handle to the list.  Use CpDeviceListDestroy to later destroy the list.
 */
DllExport HandleCpDeviceList CpDeviceListCreateUpnpUuid(const char* aUuid,
                                                        ZappCallbackDevice aAdded, void* aPtrAdded,
                                                        ZappCallbackDevice aRemoved, void* aPtrRemoved);

/**
 * Create a list of the UPnP devices of a given device type on the current subnet
 *
 * @param[in] aDomainName  The domain name of the target device
 * @param[in] aDeviceType  The type of the target device
 * @param[in] aVersion     The version number of the target device
 * @param[in] aAdded       Function pointer which is called when a device is added to the list
 * @param[in] aPtrAdded    Will be passed as the second parameter to aAdded
 * @param[in] aRemoved     Function pointer which is called when a device is removed from the list
 * @param[in] aPtrRemoved  Will be passed as the second parameter to aRemoved
 *
 * @return  Handle to the list.  Use CpDeviceListDestroy to later destroy the list.
 */
DllExport HandleCpDeviceList CpDeviceListCreateUpnpDeviceType(const char* aDomainName, const char* aDeviceType, uint32_t aVersion,
                                                              ZappCallbackDevice aAdded, void* aPtrAdded,
                                                              ZappCallbackDevice aRemoved, void* aPtrRemoved);

/**
 * Create a list of the UPnP devices of a given service type on the current subnet
 *
 * @param[in] aDomainName  The domain name of the target service
 * @param[in] aServiceType  The type of the target service
 * @param[in] aVersion     The version number of the target service
 * @param[in] aAdded       Function pointer which is called when a device is added to the list
 * @param[in] aPtrAdded    Will be passed as the second parameter to aAdded
 * @param[in] aRemoved     Function pointer which is called when a device is removed from the list
 * @param[in] aPtrRemoved  Will be passed as the second parameter to aRemoved
 *
 * @return  Handle to the list.  Use CpDeviceListDestroy to later destroy the list.
 */
DllExport HandleCpDeviceList CpDeviceListCreateUpnpServiceType(const char* aDomainName, const char* aServiceType, uint32_t aVersion,
                                                               ZappCallbackDevice aAdded, void* aPtrAdded,
                                                               ZappCallbackDevice aRemoved, void* aPtrRemoved);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_CPDEVICEUPNPC
