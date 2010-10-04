#include <DviStack.h>
#include <Stack.h>
#include <DviServerUpnp.h>
#include <DviDevice.h>
#include <DviSubscription.h>
#include <Printer.h>

using namespace Zapp;

// DviStack

DviStack::DviStack()
    : iBootId(1)
    , iNextBootId(2)
{
    Stack::SetDviStack(this);
    iDviServerUpnp = new DviServerUpnp;
    iDviDeviceMap = new DviDeviceMap;
    iSubscriptionManager = new DviSubscriptionManager;
}

DviStack::~DviStack()
{
    delete iDviServerUpnp;
    delete iDviDeviceMap;
    delete iSubscriptionManager;
}

TUint DviStack::BootId()
{
    Zapp::Mutex& lock = Stack::Mutex();
    lock.Wait();
    DviStack* self = DviStack::Self();
    TUint id = self->iBootId;
    lock.Signal();
    return id;
}

TUint DviStack::NextBootId()
{
    Zapp::Mutex& lock = Stack::Mutex();
    lock.Wait();
    DviStack* self = DviStack::Self();
    TUint id = self->iNextBootId;
    lock.Signal();
    return id;
}

void DviStack::UpdateBootId()
{
    Zapp::Mutex& lock = Stack::Mutex();
    lock.Wait();
    DviStack* self = DviStack::Self();
    self->iBootId = self->iNextBootId;
    self->iNextBootId++;
    lock.Signal();
}

DviServerUpnp& DviStack::ServerUpnp()
{
    DviStack* self = DviStack::Self();
    return *(self->iDviServerUpnp);
}

DviDeviceMap& DviStack::DeviceMap()
{
    DviStack* self = DviStack::Self();
    return *(self->iDviDeviceMap);
}

DviSubscriptionManager& DviStack::SubscriptionManager()
{
    DviStack* self = DviStack::Self();
    return *(self->iSubscriptionManager);
}

DviStack* DviStack::Self()
{
    return (DviStack*)Stack::DviStack();
}
