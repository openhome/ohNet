#include <C/CpDeviceUpnp.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <CpiDeviceUpnp.h>
#include <FunctorCpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

HandleCpDeviceList STDCALL CpDeviceListCreateUpnpAll(OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                     OhNetCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (OhNetFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (OhNetFunctorDevice)aRemoved);
    CpiDeviceList* list = new CpiDeviceListUpnpAll(added, removed);
    list->Start();
    return (THandle)list;
}

HandleCpDeviceList STDCALL CpDeviceListCreateUpnpRoot(OhNetCallbackDevice aAdded, void* aPtrAdded,
                                                      OhNetCallbackDevice aRemoved, void* aPtrRemoved)
{
    FunctorCpiDevice added = MakeFunctorCpiDeviceC(aPtrAdded, (OhNetFunctorDevice)aAdded);
    FunctorCpiDevice removed = MakeFunctorCpiDeviceC(aPtrRemoved, (OhNetFunctorDevice)aRemoved);
    CpiDeviceList* list = new CpiDeviceListUpnpRoot(added, removed);
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
    CpiDeviceList* list = new CpiDeviceListUpnpUuid(uuid, added, removed);
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
    CpiDeviceList* list = new CpiDeviceListUpnpDeviceType(domain, type, aVersion, added, removed);
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
    CpiDeviceList* list = new CpiDeviceListUpnpServiceType(domain, type, aVersion, added, removed);
    list->Start();
    return (THandle)list;
}
