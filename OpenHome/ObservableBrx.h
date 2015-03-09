#pragma once

#include <OpenHome/Functor.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <vector>
#include <memory>

namespace OpenHome {

class IObservableBrx
{
public:
    // The argument to the callback is only valid for the
    // duration of the functor call: It may be destroyed or
    // invalidated once the functor returns.
    typedef FunctorGeneric<const Brx&> FunctorBrx;
public:
    // It is NOT safe to call these methods within the callback.
    virtual void AddObserver(FunctorBrx aObserver) = 0;
    virtual void RemoveObserver(FunctorBrx aObserver) = 0;
    virtual ~IObservableBrx() {}
};

class ObservableBrx : public IObservableBrx
{
public:
    ObservableBrx(Bwx* aData);
    ~ObservableBrx();
    void Replace(const Brx& aNewData); // aNewData is copied to underlying storage
public: // IObservableBrx
    void AddObserver(FunctorBrx aObserver) override;
    void RemoveObserver(FunctorBrx aObserver) override;
private:
    std::unique_ptr<Bwx> iData;
    mutable Mutex iMutex;
    std::vector<FunctorBrx> iObservers;
};

}

