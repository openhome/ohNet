#ifndef HEADER_CPDEVICECPPUPNP
#define HEADER_CPDEVICECPPUPNP

#include <ZappTypes.h>
#include <Std/CpDevice.h>
#include <Std/FunctorCpDevice.h>

#include <string>

namespace Zapp {

/**
 * CpDeviceCpp::GetAttribute supports the following keys for devices created by
 * one of the lists below:
 *  location     - host portion of uri to the device
 *  deviceXml    - copy of the device XML
 *  friendlyName - user displayable name for the device
 *
 * All key names are case sensitive
 */

/**
 * List of all UPnP devices on the current subnet
 */
class CpDeviceListCppUpnpAll : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpAll(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

/**
 * List of all root UPnP devices on the current subnet
 */
class CpDeviceListCppUpnpRoot : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpRoot(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

/**
 * List of all UPnP devices with a given uuid (udn) on the current subnet
 */
class CpDeviceListCppUpnpUuid : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpUuid(const std::string& aUuid, FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

/**
 * List of all UPnP devices of a given device type on the current subnet
 */
class CpDeviceListCppUpnpDeviceType : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpDeviceType(const std::string& aDomainName, const std::string& aDeviceType, uint32_t aVersion,
                               FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

/**
 * List of all UPnP devices of a given service type on the current subnet
 */
class CpDeviceListCppUpnpServiceType : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpServiceType(const std::string& aDomainName, const std::string& aServiceType, uint32_t aVersion,
                                FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

} // namespace Zapp

#endif // HEADER_CPDEVICECPPUPNP
