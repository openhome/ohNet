#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Net/Private/XmlFetcher.h>
#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpiStack

CpiStack::CpiStack()
{
    Stack::SetCpiStack(this);
    iInvocationManager = new OpenHome::Net::InvocationManager;
    iXmlFetchManager = new OpenHome::Net::XmlFetchManager;
    iSubscriptionManager = new CpiSubscriptionManager;
    iActiveDevices = new CpiActiveDevices;
    iDeviceListUpdater = new CpiDeviceListUpdater;
}

CpiStack::~CpiStack()
{
    delete iDeviceListUpdater;
    delete iActiveDevices;
    delete iSubscriptionManager;
    delete iXmlFetchManager;
    delete iInvocationManager;
}

InvocationManager& CpiStack::InvocationManager()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iInvocationManager);
}

OpenHome::Net::XmlFetchManager& CpiStack::XmlFetchManager()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iXmlFetchManager);
}

CpiSubscriptionManager& CpiStack::SubscriptionManager()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iSubscriptionManager);
}

CpiActiveDevices& CpiStack::ActiveDevices()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iActiveDevices);
}

CpiDeviceListUpdater& CpiStack::DeviceListUpdater()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iDeviceListUpdater);
}

CpiStack* CpiStack::Self()
{
    return (CpiStack*)Stack::CpiStack();
}
