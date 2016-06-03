#include <OpenHome/Av/FriendlyNameAdapter.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Net/Core/DvDevice.h>

using namespace OpenHome;
using namespace OpenHome::Av;


FriendlyNameAttributeUpdater::FriendlyNameAttributeUpdater(IFriendlyNameObservable& aFriendlyNameObservable,
                                                           Net::DvDevice& aDvDevice)
    : iFriendlyNameObservable(aFriendlyNameObservable)
    , iDvDevice(aDvDevice)
    , iLock("DNCL")
{
    iThread = new ThreadFunctor("UpnpNameChanger", MakeFunctor(*this, &FriendlyNameAttributeUpdater::Run));
    iThread->Start();

    iId = iFriendlyNameObservable.RegisterFriendlyNameObserver(
        MakeFunctorGeneric<const Brx&>(*this, &FriendlyNameAttributeUpdater::Observer));
}

FriendlyNameAttributeUpdater::~FriendlyNameAttributeUpdater()
{
    iFriendlyNameObservable.DeregisterFriendlyNameObserver(iId);
    delete iThread;
}

void FriendlyNameAttributeUpdater::Observer(const Brx& aNewFriendlyName)
{
    AutoMutex a(iLock);
    if (iFullName!=aNewFriendlyName)
    {
        iFullName.Replace(aNewFriendlyName);
        iThread->Signal();
    }

}

void FriendlyNameAttributeUpdater::Run()
{
    try {
        for (;;) {
            iThread->Wait();
            AutoMutex a(iLock);
            iDvDevice.SetAttribute("Upnp.FriendlyName", iFullName.PtrZ());
        }
    }
    catch (ThreadKill&) {}
}
