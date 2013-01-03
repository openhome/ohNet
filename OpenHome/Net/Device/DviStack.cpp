#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/DviServerUpnp.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/DviServerWebSocket.h>
#include <OpenHome/Net/Private/Bonjour.h>
#include <OpenHome/Net/Private/MdnsProvider.h> // replace this to allow clients to set an alternative Bonjour implementation
#include <OpenHome/Net/Private/DviPropertyUpdateCollection.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DvStack

DvStack::DvStack(OpenHome::Net::Stack& aStack)
    : iStack(aStack)
    , iBootId(1)
    , iNextBootId(2)
    , iMdns(NULL)
{
    iStack.SetDvStack(this);
    iPropertyUpdateCollection = new DviPropertyUpdateCollection(*this);
    TUint port = iStack.InitParams().DvUpnpServerPort();
    iDviServerUpnp = new DviServerUpnp(*this, port);
    iDviDeviceMap = new DviDeviceMap;
    iSubscriptionManager = new DviSubscriptionManager(*this);
    iDviServerWebSocket = new DviServerWebSocket(*this);
    if (iStack.InitParams().DvIsBonjourEnabled()) {
        iMdns = new OpenHome::Net::MdnsProvider(iStack, ""); // replace this to allow clients to set an alternative Bonjour implementation
    }
}

DvStack::~DvStack()
{
    delete iMdns;
    delete iDviServerWebSocket;
    delete iDviServerUpnp;
    delete iDviDeviceMap;
    delete iSubscriptionManager;
    delete iPropertyUpdateCollection;
}

TUint DvStack::BootId()
{
    OpenHome::Mutex& lock = iStack.Mutex();
    lock.Wait();
    TUint id = iBootId;
    lock.Signal();
    return id;
}

TUint DvStack::NextBootId()
{
    OpenHome::Mutex& lock = iStack.Mutex();
    lock.Wait();
    TUint id = iNextBootId;
    lock.Signal();
    return id;
}

void DvStack::UpdateBootId()
{
    OpenHome::Mutex& lock = iStack.Mutex();
    lock.Wait();
    iBootId = iNextBootId;
    iNextBootId++;
    lock.Signal();
}

DviServerUpnp& DvStack::ServerUpnp()
{
    return *iDviServerUpnp;
}

DviDeviceMap& DvStack::DeviceMap()
{
    return *iDviDeviceMap;
}

DviSubscriptionManager& DvStack::SubscriptionManager()
{
    return *iSubscriptionManager;
}

IMdnsProvider* DvStack::MdnsProvider()
{
    return iMdns;
}

DviPropertyUpdateCollection& DvStack::PropertyUpdateCollection()
{
    return *iPropertyUpdateCollection;
}
