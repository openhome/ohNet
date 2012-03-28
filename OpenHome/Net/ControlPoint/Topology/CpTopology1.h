#ifndef HEADER_TOPOLOGY1
#define HEADER_TOPOLOGY1

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>

namespace OpenHome {
namespace Net {

class ICpTopology1Handler
{
public:
    virtual void ProductAdded(CpDevice& aDevice) = 0;
    virtual void ProductRemoved(CpDevice& aDevice) = 0;
    ~ICpTopology1Handler() {}
};

typedef void (ICpTopology1Handler::*ICpTopology1HandlerFunction)(CpDevice&);

class CpTopology1Job
{
public:
    CpTopology1Job(ICpTopology1Handler& aHandler);
    void Set(CpDevice& aDevice, ICpTopology1HandlerFunction aFunction);
    virtual void Execute();
private:
    ICpTopology1Handler* iHandler;
    CpDevice* iDevice;
    ICpTopology1HandlerFunction iFunction;
};


class CpTopology1
{
    static const TUint kMaxJobCount = 20;
    
public:
    CpTopology1(ICpTopology1Handler& aHandler);
    
    void Refresh();
    
    ~CpTopology1();
    
private:
    void ProductAdded(CpDevice& aDevice);
    void ProductRemoved(CpDevice& aDevice);

    void Run();
    
private:
    CpDeviceList* iDeviceListProduct;
    Fifo<CpTopology1Job*> iFree;
    Fifo<CpTopology1Job*> iReady;
    ThreadFunctor* iThread;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TOPOLOGY1
