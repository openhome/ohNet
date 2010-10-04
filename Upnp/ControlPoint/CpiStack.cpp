#include <CpiStack.h>
#include <Stack.h>
#include <CpiService.h>
#include <XmlFetcher.h>
#include <CpiSubscription.h>
#include <Printer.h>

using namespace Zapp;

// CpiStack

CpiStack::CpiStack()
{
    Stack::SetCpiStack(this);
    iInvocationManager = new Zapp::InvocationManager;
    iXmlFetchManager = new Zapp::XmlFetchManager;
    iSubscriptionManager = new Zapp::SubscriptionManager;
}

CpiStack::~CpiStack()
{
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

Zapp::SubscriptionManager& CpiStack::SubscriptionManager()
{
    CpiStack* self = CpiStack::Self();
    return *(self->iSubscriptionManager);
}

CpiStack* CpiStack::Self()
{
    return (CpiStack*)Stack::CpiStack();
}
