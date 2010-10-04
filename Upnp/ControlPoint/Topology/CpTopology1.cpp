#include "CpTopology1.h"

#include <Debug.h>

using namespace Zapp;

// CpTopology1Job

CpTopology1Job::CpTopology1Job(ICpTopology1Handler& aHandler)
{
	iHandler = &aHandler;
	iDevice = 0;
}
	
void CpTopology1Job::Set(CpDevice& aDevice, ICpTopology1HandlerFunction aFunction)
{
	iDevice = &aDevice;
	iFunction = aFunction;
	iDevice->AddRef();
}

void CpTopology1Job::Execute()
{
	if (iDevice) {
		(iHandler->*iFunction)(*iDevice);
		iDevice->RemoveRef();
		iDevice = 0;
	}
	else {
		THROW(ThreadKill);
	}
}

// CpTopology1

CpTopology1::CpTopology1(ICpTopology1Handler& aHandler)
	: iFree(kMaxJobCount)
	, iReady(kMaxJobCount)
{
	for (TUint i = 0; i < kMaxJobCount; i++) {
		iFree.Write(new CpTopology1Job(aHandler));
	}
	
    FunctorCpDevice productAdded = MakeFunctorCpDevice(*this, &CpTopology1::ProductAdded);
    FunctorCpDevice productRemoved = MakeFunctorCpDevice(*this, &CpTopology1::ProductRemoved);
    FunctorCpDevice upnpAdded = MakeFunctorCpDevice(*this, &CpTopology1::UpnpAdded);
    FunctorCpDevice upnpRemoved = MakeFunctorCpDevice(*this, &CpTopology1::UpnpRemoved);
    
    iDeviceListProduct = new CpDeviceListUpnpServiceType(Brn("linn.co.uk"), Brn("Product"), 3, productAdded, productRemoved);
    iDeviceListUpnp = new CpDeviceListUpnpDeviceType(Brn("upnp.org"), Brn("MediaRenderer"), 1, upnpAdded, upnpRemoved);

	iThread = new ThreadFunctor("TOP1", MakeFunctor(*this, &CpTopology1::Run));
	iThread->Start();
}

CpTopology1::~CpTopology1()
{
	delete (iDeviceListUpnp);
	delete (iDeviceListProduct);
	
	iReady.Write(iFree.Read());

	delete (iThread);
	
	for (TUint i = 0; i < kMaxJobCount; i++) {
		delete (iFree.Read());
	}
}
    
void CpTopology1::Refresh()
{
	iDeviceListProduct->Refresh();
	iDeviceListUpnp->Refresh();
}
    
void CpTopology1::ProductAdded(CpDevice& aDevice)
{
    LOG(kTopology, "CpTopology1::ProductAdded ");
    LOG(kTopology, aDevice.Udn());
    LOG(kTopology, "\n");

	CpTopology1Job* job = iFree.Read();
	job->Set(aDevice, &ICpTopology1Handler::ProductAdded);
	iReady.Write(job);
}

void CpTopology1::ProductRemoved(CpDevice& aDevice)
{
    LOG(kTopology, "CpTopology1::ProductRemoved ");
    LOG(kTopology, aDevice.Udn());
    LOG(kTopology, "\n");
    
	CpTopology1Job* job = iFree.Read();
	job->Set(aDevice, &ICpTopology1Handler::ProductRemoved);
	iReady.Write(job);
}

void CpTopology1::UpnpAdded(CpDevice& aDevice)
{
    LOG(kTopology, "CpTopology1::UpnpAdded ");
    LOG(kTopology, aDevice.Udn());
    LOG(kTopology, "\n");
    
	CpTopology1Job* job = iFree.Read();
	job->Set(aDevice, &ICpTopology1Handler::UpnpAdded);
	iReady.Write(job);
}

void CpTopology1::UpnpRemoved(CpDevice& aDevice)
{
    LOG(kTopology, "CpTopology1::UpnpRemoved ");
    LOG(kTopology, aDevice.Udn());
    LOG(kTopology, "\n");
    
	CpTopology1Job* job = iFree.Read();
	job->Set(aDevice, &ICpTopology1Handler::UpnpRemoved);
	iReady.Write(job);
}

void CpTopology1::Run()
{
    for (;;)
    {
    	CpTopology1Job* job = iReady.Read();
    	
    	try {
	    	job->Execute();
	    	iFree.Write(job);
	    }
	    catch (ThreadKill)
	    {
	    	iFree.Write(job);
	    	break;
	    }
    }
}
