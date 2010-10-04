#include <Std/CpDeviceUpnp.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <CpiDeviceUpnp.h>
#include <Std/FunctorCpDevice.h>
#include <FunctorCpiDevice.h>

using namespace Zapp;


// CpDeviceListCppUpnpAll

CpDeviceListCppUpnpAll::CpDeviceListCppUpnpAll(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved)
    : CpDeviceListCpp(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpAll(added, removed);
    iList->Start();
}


// CpDeviceListCppUpnpRoot

CpDeviceListCppUpnpRoot::CpDeviceListCppUpnpRoot(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved)
    : CpDeviceListCpp(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpRoot(added, removed);
    iList->Start();
}


// CpDeviceListCppUpnpUuid

CpDeviceListCppUpnpUuid::CpDeviceListCppUpnpUuid(const std::string& aUuid, FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved)
    : CpDeviceListCpp(aAdded, aRemoved)
{
    Brn uuid(aUuid.c_str());
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpUuid(uuid, added, removed);
    iList->Start();
}


// CpDeviceListCppUpnpDeviceType

CpDeviceListCppUpnpDeviceType::CpDeviceListCppUpnpDeviceType(const std::string& aDomainName, const std::string& aDeviceType, uint32_t aVersion,
                                                       FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved)
    : CpDeviceListCpp(aAdded, aRemoved)
{
    Brn domain(aDomainName.c_str());
    Brn type(aDeviceType.c_str());
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpDeviceType(domain, type, aVersion, added, removed);
    iList->Start();
}


// CpDeviceListCppUpnpServiceType

CpDeviceListCppUpnpServiceType::CpDeviceListCppUpnpServiceType(const std::string& aDomainName, const std::string& aServiceType, uint32_t aVersion,
                                                         FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved)
    : CpDeviceListCpp(aAdded, aRemoved)
{
    Brn domain(aDomainName.c_str());
    Brn type(aServiceType.c_str());
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpServiceType(domain, type, aVersion, added, removed);
    iList->Start();

}
