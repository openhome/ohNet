#include <OpenHome/Av/UpnpAv/FriendlyNameUpnpAv.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/SourceFactory.h>

#include <map>

using namespace OpenHome;
using namespace OpenHome::Av;


FriendlyNameManagerUpnpAv::FriendlyNameManagerUpnpAv(Product& aProduct)
    : iProduct(aProduct)
    , iNextObserverId(1)
    , iMutex("FNHM")
{
    // Observer methods called during registration.
    aProduct.AddNameObserver(*this);  // Callbacks: RoomChanged, NameChanged
    aProduct.AddObserver(*this);  // Callbacks: Started, SourceIndexChanged, SourceXmlChanged
}

FriendlyNameManagerUpnpAv::~FriendlyNameManagerUpnpAv()
{
    AutoMutex _(iMutex);
    ASSERT(iObservers.size() == 0);
}

TUint FriendlyNameManagerUpnpAv::RegisterFriendlyNameObserver(FunctorGeneric<const Brx&> aObserver)
{
    AutoMutex _(iMutex);
    const TUint id = iNextObserverId++;
    auto it = iObservers.insert(std::pair<TUint,FunctorGeneric<const Brx&>>(id, aObserver));
    ASSERT(it.second);
    aObserver(iFriendlyName);
    return id;
}

void FriendlyNameManagerUpnpAv::DeregisterFriendlyNameObserver(TUint aId)
{
    (void)iObservers.erase(aId);
}

void FriendlyNameManagerUpnpAv::RoomChanged(const Brx& aRoom)
{
    AutoMutex a(iMutex);
    if (iRoom!=aRoom)
    {
        iRoom.Replace(aRoom);
        ConstructFriendlyNameLocked();
        NotifyObserversLocked();
    }
}

void FriendlyNameManagerUpnpAv::NameChanged(const Brx& /*aName*/)
{
}

void FriendlyNameManagerUpnpAv::Started()
{
}

void FriendlyNameManagerUpnpAv::SourceIndexChanged()
{
}

void FriendlyNameManagerUpnpAv::SourceXmlChanged()
{
    Bws<ISource::kMaxSystemNameBytes> systemName;
    Bws<ISource::kMaxSourceTypeBytes> type;
    Bws<ISource::kMaxSourceNameBytes> name;
    TBool visible;
    const Brn targetType(SourceFactory::kSourceTypeUpnpAv);
    const TUint count = iProduct.SourceCount();
    for (TUint i=0; i<count; i++) {
        iProduct.GetSourceDetails(i, systemName, type, name, visible);
        if ((type == targetType)) {
            if (iSourceName != name) {
                iSourceName.Replace(name);
                ConstructFriendlyNameLocked();
                NotifyObserversLocked();
            }
            break;
        }
    }
}

void FriendlyNameManagerUpnpAv::ProductUrisChanged()
{
}

void FriendlyNameManagerUpnpAv::ConstructFriendlyNameLocked()
{
    iFriendlyName.Replace(iRoom);
    iFriendlyName.Append(':');
    iFriendlyName.Append(iSourceName);
}

void FriendlyNameManagerUpnpAv::NotifyObserversLocked()
{
    for (auto observer : iObservers) {
        observer.second(iFriendlyName);
    }
}
