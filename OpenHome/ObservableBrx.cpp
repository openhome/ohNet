#include <OpenHome/ObservableBrx.h>
#include <algorithm>

using namespace OpenHome;

ObservableBrx::ObservableBrx(Bwx* aData)
: iData(aData)
, iMutex("obs")
{}

ObservableBrx::~ObservableBrx()
{
    AutoMutex am(iMutex);
    ASSERT(iObservers.empty());
}

void ObservableBrx::Replace(const Brx& aNewData)
{
    AutoMutex am(iMutex);
    iData->Replace(aNewData);
    std::for_each(iObservers.begin(), iObservers.end(), [&](FunctorBrx& aObserver) {
        aObserver(*iData);
    });
}

void ObservableBrx::AddObserver(FunctorBrx aObserver)
{
    AutoMutex am(iMutex);
    iObservers.emplace_back(aObserver);
    aObserver(*iData); // Do initial notification
}

void ObservableBrx::RemoveObserver(FunctorBrx aObserver)
{
    AutoMutex am(iMutex);
    auto it = std::find(iObservers.begin(), iObservers.end(), aObserver);
    if ( it != iObservers.end() )
        iObservers.erase(it);
}

