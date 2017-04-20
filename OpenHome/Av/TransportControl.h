#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

namespace OpenHome {
namespace Av {

class ITransportActivator
{
public:
    virtual TBool TryActivate(const Brx& aMode) = 0;
    virtual ~ITransportActivator() {}
};

class ITransportRepeatRandomObserver
{
public:
    virtual void TransportRepeatChanged(TBool aRepeat) = 0;
    virtual void TransportRandomChanged(TBool aRandom) = 0;
    virtual ~ITransportRepeatRandomObserver() {}
};

class ITransportRepeatRandom
{
public:
    virtual void SetRepeat(TBool aRepeat) = 0;
    virtual void SetRandom(TBool aRandom) = 0;
    virtual void AddObserver(ITransportRepeatRandomObserver& aObserver) = 0;
    virtual void RemoveObserver(ITransportRepeatRandomObserver& aObserver) = 0;
};

class TransportRepeatRandom : public ITransportRepeatRandom
{
public:
    TransportRepeatRandom();
public: // from ITransportRepeatRandom
    void SetRepeat(TBool aRepeat) override;
    void SetRandom(TBool aRandom) override;
    void AddObserver(ITransportRepeatRandomObserver& aObserver) override;
    void RemoveObserver(ITransportRepeatRandomObserver& aObserver) override;
private:
    Mutex iLock;
    TBool iRepeat;
    TBool iRandom;
    std::vector<ITransportRepeatRandomObserver*> iObservers;
};

} // namespace Av
} // namespace OpenHome
