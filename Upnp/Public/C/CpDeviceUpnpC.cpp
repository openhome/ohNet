#include <C/CpDeviceUpnp.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <CpiDeviceUpnp.h>
#include <FunctorCpiDevice.h>

using namespace Zapp;

HandleCpDeviceList CpDeviceListCreateUpnpAll(ZappCallbackDevice aAdded, void* aPtrAdded,
                                             ZappCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (ZappFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (ZappFunctorDevice)aRemoved);
    CpiDeviceList* list = new CpiDeviceListUpnpAll(added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList CpDeviceListCreateUpnpRoot(ZappCallbackDevice aAdded, void* aPtrAdded,
                                              ZappCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (ZappFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (ZappFunctorDevice)aRemoved);
    CpiDeviceList* list = new CpiDeviceListUpnpRoot(added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList CpDeviceListCreateUpnpUuid(const char* aUuid,
                                              ZappCallbackDevice aAdded, void* aPtrAdded,
                                              ZappCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (ZappFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (ZappFunctorDevice)aRemoved);
    const Brn uuid(aUuid);
    CpiDeviceList* list = new CpiDeviceListUpnpUuid(uuid, added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList CpDeviceListCreateUpnpDeviceType(const char* aDomainName, const char* aDeviceType, uint32_t aVersion,
                                                    ZappCallbackDevice aAdded, void* aPtrAdded,
                                                    ZappCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (ZappFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (ZappFunctorDevice)aRemoved);
    const Brn domain(aDomainName);
    const Brn type(aDeviceType);
    CpiDeviceList* list = new CpiDeviceListUpnpDeviceType(domain, type, aVersion, added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList CpDeviceListCreateUpnpServiceType(const char* aDomainName, const char* aServiceType, uint32_t aVersion,
                                                     ZappCallbackDevice aAdded, void* aPtrAdded,
                                                     ZappCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (ZappFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (ZappFunctorDevice)aRemoved);
    const Brn domain(aDomainName);
    const Brn type(aServiceType);
    CpiDeviceList* list = new CpiDeviceListUpnpServiceType(domain, type, aVersion, added, removed);
    list->Start();
    return (THandle)list;
}
