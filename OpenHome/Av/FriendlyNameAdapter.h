#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Net/Core/DvDevice.h>

namespace OpenHome {
namespace Av {

class FriendlyNameAttributeUpdater
    : private OpenHome::INonCopyable
{
public:
    FriendlyNameAttributeUpdater(
        IFriendlyNameObservable& aFriendlyNameObservable,
        Net::DvDevice& aDvDevice,
        const Brx& aAppend);
    FriendlyNameAttributeUpdater(
        IFriendlyNameObservable& aFriendlyNameObservable,
        OpenHome::Net::DvDevice& aDvDevice);
    ~FriendlyNameAttributeUpdater();

private:
    void Observer(const Brx& aNewFriendlyName);
    void Run();

private:
    static const TUint kMaxFriendlyNameDeviceType = 30;

    IFriendlyNameObservable& iFriendlyNameObservable;
    Net::DvDevice& iDvDevice;
    TUint iId;
    const OpenHome::Bwh iAppend;
    Mutex iLock;
    ThreadFunctor* iThread;
    Bws<IFriendlyNameObservable::kMaxFriendlyNameBytes+kMaxFriendlyNameDeviceType+1> iFullName;
};

}
}

