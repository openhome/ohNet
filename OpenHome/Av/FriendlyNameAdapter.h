#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/Product.h>

namespace OpenHome {
    namespace Net {
        class DvDevice;
    }
namespace Av {

class FriendlyNameAttributeUpdater : private INonCopyable
{
public:
    FriendlyNameAttributeUpdater(IFriendlyNameObservable& aFriendlyNameObservable,
                                 Net::DvDevice& aDvDevice);
    ~FriendlyNameAttributeUpdater();
private:
    void Observer(const Brx& aNewFriendlyName);
    void Run();
private:
    static const TUint kMaxFriendlyNameDeviceType = 30;
    static const TUint kMaxNameBytes = IFriendlyNameObservable::kMaxFriendlyNameBytes + kMaxFriendlyNameDeviceType;

    IFriendlyNameObservable& iFriendlyNameObservable;
    Net::DvDevice& iDvDevice;
    TUint iId;
    Mutex iLock;
    ThreadFunctor* iThread;
    Bws<kMaxNameBytes> iFullName;
};

}
}
