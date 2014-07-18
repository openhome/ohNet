#include <OpenHome/Net/Cpp/CpDeviceUpnp.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/CpiDeviceUpnp.h>
#include <OpenHome/Net/Cpp/FunctorCpDevice.h>
#include <OpenHome/Net/Private/FunctorCpiDevice.h>
#include <OpenHome/Net/Private/Globals.h>

using namespace OpenHome;
using namespace OpenHome::Net;


// CpDeviceListCppUpnpAll

CpDeviceListCppUpnpAll::CpDeviceListCppUpnpAll(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved)
    : CpDeviceListCpp(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpAll(*gCpStack, added, removed);
    iList->Start();
}


// CpDeviceListCppUpnpRoot

CpDeviceListCppUpnpRoot::CpDeviceListCppUpnpRoot(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved)
    : CpDeviceListCpp(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpRoot(*gCpStack, added, removed);
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
    iList = new CpiDeviceListUpnpUuid(*gCpStack, uuid, added, removed);
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
    iList = new CpiDeviceListUpnpDeviceType(*gCpStack, domain, type, aVersion, added, removed);
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
    iList = new CpiDeviceListUpnpServiceType(*gCpStack, domain, type, aVersion, added, removed);
    iList->Start();

}
