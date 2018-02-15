#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Net/Private/XmlFetcher.h>
#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpStack

CpStack::CpStack(OpenHome::Environment& aStack)
    : iEnv(aStack)
{
    iEnv.SetCpStack(this);
    iInvocationManager = new OpenHome::Net::InvocationManager(*this);
    iXmlFetchManager = new OpenHome::Net::XmlFetchManager(*this);
    iSubscriptionManager = new CpiSubscriptionManager(*this);
    iDeviceListUpdater = new CpiDeviceListUpdater();
    iEnv.CreateMdnsProvider(); // will only be created if it has been enabled first: Env.InitParams.SetDvEnableBonjour
}

CpStack::~CpStack()
{
    delete iDeviceListUpdater;
    delete iSubscriptionManager;
    delete iXmlFetchManager;
    delete iInvocationManager;
}

InvocationManager& CpStack::InvocationManager()
{
    return *iInvocationManager;
}

OpenHome::Net::XmlFetchManager& CpStack::XmlFetchManager()
{
    return *iXmlFetchManager;
}

CpiSubscriptionManager& CpStack::SubscriptionManager()
{
    return *iSubscriptionManager;
}

CpiDeviceListUpdater& CpStack::DeviceListUpdater()
{
    return *iDeviceListUpdater;
}
