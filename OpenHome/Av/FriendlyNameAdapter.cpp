
#include <OpenHome/Av/FriendlyNameAdapter.h>
#include <OpenHome/Private/Debug.h>


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;

static const TUint kMaxFriendlyNameDeviceType = 30;

FriendlyNameAttributeUpdater::FriendlyNameAttributeUpdater(
        IFriendlyNameObservable& aFriendlyNameObservable,
        DvDevice& aDvDevice,
        const Brx& aAppend)
        : iFriendlyNameObservable(aFriendlyNameObservable)
        , iDvDevice(aDvDevice)
        , iAppend(aAppend)
{
    iId = iFriendlyNameObservable.RegisterFriendlyNameObserver(
        MakeFunctorGeneric<const Brx&>(*this, &FriendlyNameAttributeUpdater::Observer));
}

FriendlyNameAttributeUpdater::FriendlyNameAttributeUpdater(
        IFriendlyNameObservable& aFriendlyNameObservable,
        DvDevice& aDvDevice)
        : FriendlyNameAttributeUpdater(aFriendlyNameObservable, aDvDevice, Brx::Empty())
{
}

FriendlyNameAttributeUpdater::~FriendlyNameAttributeUpdater()
{
    iFriendlyNameObservable.DeregisterFriendlyNameObserver(iId);
}

const OpenHome::Brx& FriendlyNameAttributeUpdater::Appendage()
{
    return iAppend;
}

void FriendlyNameAttributeUpdater::Observer(const Brx& aNewFriendlyName)
{
    Bws<IFriendlyNameObservable::kMaxFriendlyNameBytes+kMaxFriendlyNameDeviceType+1> fullName;
    fullName.Replace(aNewFriendlyName);
    fullName.Append(iAppend);

    // apply change to DvDevice
    if(iDvDevice.Enabled()) // must be disabled to change attribute
    {
        // Note: the device must only be disabled here as there is no mutex protection
        Semaphore sema("ufn", 0);
        iDvDevice.SetDisabled(MakeFunctor(sema, &Semaphore::Signal));
        sema.Wait();
        iDvDevice.SetAttribute("Upnp.FriendlyName", fullName.PtrZ());
        iDvDevice.SetEnabled();
    }
    else
    {
        iDvDevice.SetAttribute("Upnp.FriendlyName", fullName.PtrZ());
    }
}



