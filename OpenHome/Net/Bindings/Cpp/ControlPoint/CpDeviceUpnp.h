#ifndef HEADER_CPDEVICECPPUPNP
#define HEADER_CPDEVICECPPUPNP

#include <OpenHome/Types.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Cpp/FunctorCpDevice.h>

#include <string>

namespace OpenHome {
namespace Net {

/**
 * CpDeviceCpp::GetAttribute supports the following keys for devices created by
 * one of the lists below:
 *  Location     - host portion of uri to the device
 *  DeviceXml    - copy of the device XML
 *  FriendlyName - user displayable name for the device
 *
 * All key names are case sensitive
 */

/**
 * List of all UPnP devices on the current subnet
 * @ingroup ControlPoint
 */
class CpDeviceListCppUpnpAll : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpAll(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

/**
 * List of all root UPnP devices on the current subnet
 * @ingroup ControlPoint
 */
class CpDeviceListCppUpnpRoot : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpRoot(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

/**
 * List of all UPnP devices with a given uuid (udn) on the current subnet
 * @ingroup ControlPoint
 */
class CpDeviceListCppUpnpUuid : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpUuid(const std::string& aUuid, FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

/**
 * List of all UPnP devices of a given device type on the current subnet
 * @ingroup ControlPoint
 */
class CpDeviceListCppUpnpDeviceType : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpDeviceType(const std::string& aDomainName, const std::string& aDeviceType, uint32_t aVersion,
                               FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

/**
 * List of all UPnP devices of a given service type on the current subnet
 * @ingroup ControlPoint
 */
class CpDeviceListCppUpnpServiceType : public CpDeviceListCpp
{
public:
    CpDeviceListCppUpnpServiceType(const std::string& aDomainName, const std::string& aServiceType, uint32_t aVersion,
                                FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPDEVICECPPUPNP
