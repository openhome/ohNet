#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/CpiDeviceUpnp.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>
#include <OpenHome/Net/Private/FunctorCpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


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
