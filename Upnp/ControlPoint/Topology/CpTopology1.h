#ifndef HEADER_TOPOLOGY1
#define HEADER_TOPOLOGY1

#include <ZappTypes.h>
#include <Fifo.h>
#include <Thread.h>
#include <Core/CpDeviceUpnp.h>
#include <Core/FunctorCpDevice.h>

namespace Zapp {

class ICpTopology1Handler
{
public:
	virtual void ProductAdded(CpDevice& aDevice) = 0;
	virtual void ProductRemoved(CpDevice& aDevice) = 0;
	virtual void UpnpAdded(CpDevice& aDevice) = 0;
	virtual void UpnpRemoved(CpDevice& aDevice) = 0;
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
	void UpnpAdded(CpDevice& aDevice);
	void UpnpRemoved(CpDevice& aDevice);

	void Run();
	
private:
	CpDeviceListUpnpServiceType* iDeviceListProduct;
	CpDeviceListUpnpDeviceType* iDeviceListUpnp;
	Fifo<CpTopology1Job*> iFree;
	Fifo<CpTopology1Job*> iReady;
	ThreadFunctor* iThread;
};

} // namespace Zapp

#endif // HEADER_TOPOLOGY1
