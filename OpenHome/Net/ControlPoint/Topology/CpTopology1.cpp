#include "CpTopology1.h"

#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Net;

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
    
    iDeviceListProduct = new CpDeviceListUpnpServiceType(Brn("av.openhome.org"), Brn("Product"), 1, productAdded, productRemoved);

    iThread = new ThreadFunctor("TOP1", MakeFunctor(*this, &CpTopology1::Run));
    iThread->Start();
}

CpTopology1::~CpTopology1()
{
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
