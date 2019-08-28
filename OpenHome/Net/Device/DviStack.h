/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_DVI_STACK
#define HEADER_DVI_STACK

#include <OpenHome/Types.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/DviServerUpnp.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Net/Private/DviServerWebSocket.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Bonjour.h>
#include <OpenHome/Net/Private/DviPropertyUpdateCollection.h>
#include <OpenHome/Net/Private/DviSsdpNotifier.h>
#include <OpenHome/Private/Standard.h>

#include <vector>

namespace OpenHome {
namespace Net {

class IControlPointObserver
{
public:
    virtual void NotifyControlPoint(const OpenHome::Brx& aControlPoint) = 0; // not allowed to throw
};

class IDvProtocolFactory;

class DvStack : private IStack, private INonCopyable
{
    static const TUint kMaxControlPointBytes = 1024;
public:
    DvStack(Environment& aEnv);
    Environment& Env() { return iEnv; }
    TUint BootId();
    TUint NextBootId();
    void UpdateBootId();
    DviServerUpnp& ServerUpnp();
    DviDeviceMap& DeviceMap();
    DviSubscriptionManager& SubscriptionManager();
    DviPropertyUpdateCollection& PropertyUpdateCollection();
    DviSsdpNotifierManager& SsdpNotifierManager();
    void AddProtocolFactory(IDvProtocolFactory* aProtocolFactory);
    std::vector<IDvProtocolFactory*>& ProtocolFactories();
    void AddControlPointObserver(IControlPointObserver& aObserver);
    void RemoveControlPointObserver(IControlPointObserver& aObserver);
    void NotifyControlPointUsed(const OpenHome::Brx& aControlPoint);
private:
    ~DvStack();
private:
    OpenHome::Environment& iEnv;
    Mutex iLock;
    TUint iBootId;
    TUint iNextBootId;
    DviServerUpnp* iDviServerUpnp;
    DviDeviceMap* iDviDeviceMap;
    DviSubscriptionManager* iSubscriptionManager;
    DviServerWebSocket* iDviServerWebSocket;
    DviPropertyUpdateCollection* iPropertyUpdateCollection;
    DviSsdpNotifierManager* iSsdpNotifierManager;
    std::vector<IDvProtocolFactory*> iProtocolFactories;
    std::vector<IControlPointObserver*> iControlPointObservers;
    Bws<kMaxControlPointBytes> iControlPoint;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_STACK
