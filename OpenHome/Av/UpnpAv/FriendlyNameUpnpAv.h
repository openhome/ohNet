#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <map>

namespace OpenHome {
namespace Av {

class FriendlyNameManagerUpnpAv : public IFriendlyNameObservable
                                , public IProductNameObserver
                                , private IProductObserver
{
public:
    FriendlyNameManagerUpnpAv(Product& aProduct);
    ~FriendlyNameManagerUpnpAv();
private: // from IFriendlyNameObservable
    TUint RegisterFriendlyNameObserver(FunctorGeneric<const Brx&> aObserver) override;
    void DeregisterFriendlyNameObserver(TUint aId) override;
private: // from IProductNameObserver
    void RoomChanged(const Brx& aRoom) override;
    void NameChanged(const Brx& aName) override;
private: // from IProductObserver
    void Started() override;
    void SourceIndexChanged() override;
    void SourceXmlChanged() override;
    void ProductUrisChanged() override;
private:
    void UpdateDetails();
    void ConstructFriendlyNameLocked();
    void NotifyObserversLocked();
private:
    Product& iProduct;
    Bws<Product::kMaxRoomBytes> iRoom;
    Bws<ISource::kMaxSourceNameBytes> iSourceName;
    Bws<kMaxFriendlyNameBytes> iFriendlyName;
    TUint iNextObserverId;
    std::map<TUint, FunctorGeneric<const Brx&>> iObservers;
    Mutex iMutex;
};

} // namespace Av
} // namespace OpenHome
