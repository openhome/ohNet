#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviServerUpnp.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/DviServerWebSocket.h>
#include <OpenHome/Net/Private/Bonjour.h>
#include <OpenHome/Net/Private/DviPropertyUpdateCollection.h>
#include <OpenHome/Net/Private/DviProtocolLpec.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DvStack

DvStack::DvStack(OpenHome::Environment& aEnv)
    : iEnv(aEnv)
    , iBootId(1)
    , iNextBootId(2)
    , iControlPoint(OpenHome::Brx::Empty())
{
    iEnv.SetDvStack(this);
    iSsdpNotifierManager = new DviSsdpNotifierManager(*this);
    iPropertyUpdateCollection = new DviPropertyUpdateCollection(*this);
    InitialisationParams* initParams = iEnv.InitParams();
    TUint port = initParams->DvUpnpServerPort();
    iDviDeviceMap = new DviDeviceMap;
    iDviServerUpnp = new DviServerUpnp(*this, port);
    const TUint pubThPriority = initParams->DvPublisherThreadPriority();
    iSubscriptionManager = new DviSubscriptionManager(*this, pubThPriority);
    iDviServerWebSocket = new DviServerWebSocket(*this);
    iEnv.CreateMdnsProvider(); // will only be created if it has been enabled first: Env.InitParams.SetDvEnableBonjour
    if (initParams->DvNumLpecThreads() > 0) {
        port = initParams->DvLpecServerPort();
        AddProtocolFactory(new DviProtocolFactoryLpec(*this, port));
    }
}

DvStack::~DvStack()
{
    for (TUint i=0; i<iProtocolFactories.size(); i++) {
        delete iProtocolFactories[i];
    }
    delete iDviServerWebSocket;
    delete iDviServerUpnp;
    delete iDviDeviceMap;
    delete iSubscriptionManager;
    delete iPropertyUpdateCollection;
    delete iSsdpNotifierManager;
    ASSERT(iControlPointObservers.size() == 0);
}

TUint DvStack::BootId()
{
    OpenHome::Mutex& lock = iEnv.Mutex();
    lock.Wait();
    TUint id = iBootId;
    lock.Signal();
    return id;
}

TUint DvStack::NextBootId()
{
    OpenHome::Mutex& lock = iEnv.Mutex();
    lock.Wait();
    TUint id = iNextBootId;
    lock.Signal();
    return id;
}

void DvStack::UpdateBootId()
{
    OpenHome::Mutex& lock = iEnv.Mutex();
    lock.Wait();
    iBootId = iNextBootId;
    iNextBootId++;
    lock.Signal();
}

void DvStack::AddControlPointObserver(IControlPointObserver& aObserver)
{
    iControlPointObservers.push_back(&aObserver);
}

void DvStack::RemoveControlPointObserver(IControlPointObserver& aObserver)
{
    for (TUint i=0; i<iControlPointObservers.size(); i++) {
        if (iControlPointObservers[i] == &aObserver) {
            iControlPointObservers.erase(iControlPointObservers.begin() + i);
            break;
        }
    }
}

void DvStack::NotifyControlPointUsed(const OpenHome::Brx& aControlPoint)
{
    iControlPoint.Replace(aControlPoint);
    for (TUint i=0; i<iControlPointObservers.size(); i++) {
        iControlPointObservers[i]->NotifyControlPoint(aControlPoint);
    }
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

DviPropertyUpdateCollection& DvStack::PropertyUpdateCollection()
{
    return *iPropertyUpdateCollection;
}

DviSsdpNotifierManager& DvStack::SsdpNotifierManager()
{
    return *iSsdpNotifierManager;
}

void DvStack::AddProtocolFactory(IDvProtocolFactory* aProtocolFactory)
{
    iProtocolFactories.push_back(aProtocolFactory);
}

std::vector<IDvProtocolFactory*>& DvStack::ProtocolFactories()
{
    return iProtocolFactories;
}
