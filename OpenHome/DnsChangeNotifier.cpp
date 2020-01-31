#include <OpenHome/Private/DnsChangeNotifier.h>
#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Thread.h>

#include <utility>
#include <vector>

using namespace OpenHome;


// DnsChangeNotifier

const TUint IDnsChangeNotifier::kIdInvalid = 0;

DnsChangeNotifier::DnsChangeNotifier(const TChar* aTestHostName)
    : iLock("DNSC")
    , iTestHostName(aTestHostName)
    , iNextId(kIdInvalid + 1)
{
    iThread = new ThreadFunctor("DnsChangeNotifier", MakeFunctor(*this, &DnsChangeNotifier::NotifThread), kPriorityHigh);
    iThread->Start();
}

DnsChangeNotifier::~DnsChangeNotifier()
{
    delete iThread;
}

void DnsChangeNotifier::SetTestHostName(const TChar* aHostName)
{
    AutoMutex _(iLock);
    iTestHostName.Set(aHostName);
}

TUint DnsChangeNotifier::Register(Functor aCallback)
{
    AutoMutex _(iLock);
    const TUint id = iNextId++;
    iObservers.push_back(std::pair<TUint, Functor>(id, aCallback));
    return id;
}

void DnsChangeNotifier::Deregister(TUint aId)
{
    AutoMutex _(iLock);
    const TUint count = (TUint)iObservers.size();
    for (TUint i=0; i<count; i++) {
        if (iObservers[i].first == aId) {
            iObservers.erase(iObservers.begin() + i);
            break;
        }
    }
}

void DnsChangeNotifier::DnsChanged()
{
    Log::Print("DnsChangeNotifier::DnsChanged\n");
    iThread->Signal();
}

void DnsChangeNotifier::NotifThread()
{
    for (;;) {
        iThread->Wait();
        (void)WaitForDnsAvailable();
        {
            AutoMutex _(iLock);
            const TUint count = (TUint)iObservers.size();
            for (TUint i = 0; i < count; i++) {
                try {
                    iObservers[i].second();
                }
                catch (Exception&) {}
            }
        }
    }
}

TBool DnsChangeNotifier::WaitForDnsAvailable()
{
    // retry (indirect) call to getaddrinfo until either success or timeout
    const TUint retryMs[] = { 250, 500, 1000, 2000, 3000, 4000 };
    const TUint numElems = sizeof retryMs / sizeof retryMs[0];
    for (TUint i=0; i<numElems; i++) {
        Thread::Sleep(retryMs[i]);
        try {
            iLock.Wait();
            const Brn hostName(iTestHostName);
            iLock.Signal();
            Endpoint ep(80, hostName);
            return true;
        }
        catch (NetworkError&) {}
    }
    return false;
}
