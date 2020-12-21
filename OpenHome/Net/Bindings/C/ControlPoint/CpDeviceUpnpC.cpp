#include <OpenHome/Net/C/CpDeviceUpnp.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/CpiDeviceUpnp.h>
#include <OpenHome/Net/Private/FunctorCpiDevice.h>
#include <OpenHome/Net/Private/Globals.h>

using namespace OpenHome;
using namespace OpenHome::Net;

HandleCpDeviceList STDCALL CpDeviceListCreateUpnpAll(OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                     OhNetCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (OhNetFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (OhNetFunctorDevice)aRemoved);
    CpiDeviceList* list = new CpiDeviceListUpnpAll(*gCpStack, added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList STDCALL CpDeviceListCreateUpnpRoot(OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                      OhNetCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (OhNetFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (OhNetFunctorDevice)aRemoved);
    CpiDeviceList* list = new CpiDeviceListUpnpRoot(*gCpStack, added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList STDCALL CpDeviceListCreateUpnpUuid(const char* aUuid,
                                                      OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                      OhNetCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (OhNetFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (OhNetFunctorDevice)aRemoved);
    const Brn uuid(aUuid);
    CpiDeviceList* list = new CpiDeviceListUpnpUuid(*gCpStack, uuid, added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList STDCALL CpDeviceListCreateUpnpDeviceType(const char* aDomainName, const char* aDeviceType, uint32_t aVersion,
                                                            OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                            OhNetCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (OhNetFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (OhNetFunctorDevice)aRemoved);
    const Brn domain(aDomainName);
    const Brn type(aDeviceType);
    CpiDeviceList* list = new CpiDeviceListUpnpDeviceType(*gCpStack, domain, type, aVersion, added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList STDCALL CpDeviceListCreateUpnpServiceType(const char* aDomainName, const char* aServiceType, uint32_t aVersion,
                                                             OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                             OhNetCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (OhNetFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (OhNetFunctorDevice)aRemoved);
    const Brn domain(aDomainName);
    const Brn type(aServiceType);
    CpiDeviceList* list = new CpiDeviceListUpnpServiceType(*gCpStack, domain, type, aVersion, added, removed);
    list->Start();
    return (THandle)list;
}

void STDCALL CpDeviceListUpnpTryAdd(HandleCpDeviceList aList, const char* aLocation)
{
    CpiDeviceListUpnp* list = reinterpret_cast<CpiDeviceListUpnp*>(aList);
    ASSERT(list != NULL);
    Brn location(aLocation);
    list->TryAdd(location);
}
