#include <CpiStack.h>
#include <Stack.h>
#include <CpiService.h>
#include <XmlFetcher.h>
#include <CpiSubscription.h>
#include <CpiDevice.h>
#include <Printer.h>

using namespace Zapp;

// CpiStack

CpiStack::CpiStack()
{
    Stack::SetCpiStack(this);
    iInvocationManager = new Zapp::InvocationManager;
    iXmlFetchManager = new Zapp::XmlFetchManager;
    iSubscriptionManager = new CpiSubscriptionManager;
    iDeviceListUpdater = new CpiDeviceListUpdater;
}

CpiStack::~CpiStack()
{
    delete iDeviceListUpdater;
    delete iSubscriptionManager;
    delete iXmlFetchManager;
    delete iInvocationManager;
}

InvocationManager& CpiStack::InvocationManager()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iInvocationManager);
}

Zapp::XmlFetchManager& CpiStack::XmlFetchManager()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iXmlFetchManager);
}

CpiSubscriptionManager& CpiStack::SubscriptionManager()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iSubscriptionManager);
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
