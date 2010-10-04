#include <Core/CpDeviceUpnp.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <CpiDeviceUpnp.h>
#include <Core/FunctorCpDevice.h>
#include <FunctorCpiDevice.h>

using namespace Zapp;


// CpDeviceListUpnpAll

CpDeviceListUpnpAll::CpDeviceListUpnpAll(FunctorCpDevice aAdded, FunctorCpDevice aRemoved)
    : CpDeviceList(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpAll(added, removed);
    iList->Start();
}


// CpDeviceListUpnpRoot

CpDeviceListUpnpRoot::CpDeviceListUpnpRoot(FunctorCpDevice aAdded, FunctorCpDevice aRemoved)
    : CpDeviceList(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpRoot(added, removed);
    iList->Start();
}


// CpDeviceListUpnpUuid

CpDeviceListUpnpUuid::CpDeviceListUpnpUuid(const Brx& aUuid, FunctorCpDevice aAdded, FunctorCpDevice aRemoved)
    : CpDeviceList(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpUuid(aUuid, added, removed);
    iList->Start();
}


// CpDeviceListUpnpDeviceType

CpDeviceListUpnpDeviceType::CpDeviceListUpnpDeviceType(const Brx& aDomainName, const Brx& aDeviceType, TUint aVersion,
                                                       FunctorCpDevice aAdded, FunctorCpDevice aRemoved)
    : CpDeviceList(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpDeviceType(aDomainName, aDeviceType, aVersion, added, removed);
    iList->Start();
}


// CpDeviceListUpnpServiceType

CpDeviceListUpnpServiceType::CpDeviceListUpnpServiceType(const Brx& aDomainName, const Brx& aServiceType, TUint aVersion,
                                                         FunctorCpDevice aAdded, FunctorCpDevice aRemoved)
    : CpDeviceList(aAdded, aRemoved)
{
    FunctorCpiDevice added, removed;
    GetAddedFunctor(added);
    GetRemovedFunctor(removed);
    iList = new CpiDeviceListUpnpServiceType(aDomainName, aServiceType, aVersion, added, removed);
    iList->Start();

}
