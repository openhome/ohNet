#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <utility>
#include <vector>

namespace OpenHome {

class IDnsChangeNotifier
{
public:
    static const TUint kIdInvalid;
public:
    virtual TUint Register(Functor aCallback) = 0;
    virtual void Deregister(TUint aId) = 0;
    virtual ~IDnsChangeNotifier() {}
};

class IDnsChangeObserver
{
public:
    virtual void DnsChanged() = 0;
    virtual ~IDnsChangeObserver() {}
};

class DnsChangeNotifier : public IDnsChangeNotifier, public IDnsChangeObserver
{
public:
    DnsChangeNotifier(const TChar* aTestHostName);
    ~DnsChangeNotifier();
    void SetTestHostName(const TChar* aHostName);
private: // from IDnsChangeNotifier
    TUint Register(Functor aCallback);
    void Deregister(TUint aId);
private: // from IDnsChangeObserver
    static void DnsChanged(void* aPtr);
    void DnsChanged();
private:
    void NotifThread();
    TBool WaitForDnsAvailable();
private:
    Mutex iLock;
    Brn iTestHostName;
    ThreadFunctor* iThread;
    std::vector<std::pair<TUint, Functor> > iObservers;
    TUint iNextId;
};

}
