#include <DviStack.h>
#include <Stack.h>
#include <DviServerUpnp.h>
#include <DviDevice.h>
#include <DviSubscription.h>
#include <Printer.h>
#include <DviServerWebSocket.h>
#include <Bonjour.h>
#include <MdnsProvider.h> // replace this to allow clients to set an alternative Bonjour implementation

using namespace OpenHome::Net;

// DviStack

DviStack::DviStack()
    : iBootId(1)
    , iNextBootId(2)
    , iMdns(NULL)
{
    Stack::SetDviStack(this);
    TUint port = (Stack::InitParams().DvIsBonjourEnabled()? 80 : 0);
    iDviServerUpnp = new DviServerUpnp(port);
    iDviDeviceMap = new DviDeviceMap;
    iSubscriptionManager = new DviSubscriptionManager;
    iDviServerWebSocket = new DviServerWebSocket;
    if (Stack::InitParams().DvIsBonjourEnabled()) {
        iMdns = new OpenHome::Net::MdnsProvider(""); // replace this to allow clients to set an alternative Bonjour implementation
    }
}

DviStack::~DviStack()
{
    delete iMdns;
    delete iDviServerWebSocket;
    delete iDviServerUpnp;
    delete iDviDeviceMap;
    delete iSubscriptionManager;
}

TUint DviStack::BootId()
{
    OpenHome::Net::Mutex& lock = Stack::Mutex();
    lock.Wait();
    DviStack* self = DviStack::Self();
    TUint id = self->iBootId;
    lock.Signal();
    return id;
}

TUint DviStack::NextBootId()
{
    OpenHome::Net::Mutex& lock = Stack::Mutex();
    lock.Wait();
    DviStack* self = DviStack::Self();
    TUint id = self->iNextBootId;
    lock.Signal();
    return id;
}

void DviStack::UpdateBootId()
{
    OpenHome::Net::Mutex& lock = Stack::Mutex();
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

IMdnsProvider* DviStack::MdnsProvider()
{
    DviStack* self = DviStack::Self();
    return self->iMdns;
}

DviStack* DviStack::Self()
{
    return (DviStack*)Stack::DviStack();
}
