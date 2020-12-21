#ifndef HEADER_CPDEVICEUPNPC
#define HEADER_CPDEVICEUPNPC

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * CpDeviceCGetAttribute supports the following keys for devices created by
 * one of the lists below:
 *  Location     - host portion of uri to the device
 *  DeviceXml    - copy of the device XML
 *  FriendlyName - user displayable name for the device
 *
 * All key names are case sensitive
 */

/**
 * @addtogroup CpDeviceList
 * @ingroup ControlPoint
 * @{
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
DllExport HandleCpDeviceList STDCALL CpDeviceListCreateUpnpAll(OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                               OhNetCallbackDevice aRemoved, void* aPtrRemoved);

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
DllExport HandleCpDeviceList STDCALL CpDeviceListCreateUpnpRoot(OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                                OhNetCallbackDevice aRemoved, void* aPtrRemoved);

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
DllExport HandleCpDeviceList STDCALL CpDeviceListCreateUpnpUuid(const char* aUuid,
                                                                OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                                OhNetCallbackDevice aRemoved, void* aPtrRemoved);

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
DllExport HandleCpDeviceList STDCALL CpDeviceListCreateUpnpDeviceType(const char* aDomainName, const char* aDeviceType, uint32_t aVersion,
                                                                      OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                                      OhNetCallbackDevice aRemoved, void* aPtrRemoved);

/**
 * Create a list of the UPnP devices of a given service type on the current subnet
 *
 * @param[in] aDomainName  The domain name of the target service
 * @param[in] aServiceType The type of the target service
 * @param[in] aVersion     The version number of the target service
 * @param[in] aAdded       Function pointer which is called when a device is added to the list
 * @param[in] aPtrAdded    Will be passed as the second parameter to aAdded
 * @param[in] aRemoved     Function pointer which is called when a device is removed from the list
 * @param[in] aPtrRemoved  Will be passed as the second parameter to aRemoved
 *
 * @return  Handle to the list.  Use CpDeviceListDestroy to later destroy the list.
 */
DllExport HandleCpDeviceList STDCALL CpDeviceListCreateUpnpServiceType(const char* aDomainName, const char* aServiceType, uint32_t aVersion,
                                                                       OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                                       OhNetCallbackDevice aRemoved, void* aPtrRemoved);

/**
 * Supplement normal UPnP discovery by checking a past known location for a device
 *
 * @param[in] aList        Device list, previously returned from a CpDeviceListCreateUpnpXxx function
 * @param[in] aLocation    Uri to previous location for device xml
 */
DllExport void STDCALL CpDeviceListUpnpTryAdd(HandleCpDeviceList aList, const char* aLocation);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_CPDEVICEUPNPC
