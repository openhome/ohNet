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
    const OpenHome::Brx& Appendage();

private:
    void Observer(const Brx& aNewFriendlyName);

private:
    IFriendlyNameObservable& iFriendlyNameObservable;
    Net::DvDevice& iDvDevice;
    TUint iId;
    const OpenHome::Bwh iAppend;
};

}
}

