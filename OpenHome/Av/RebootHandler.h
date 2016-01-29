#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
namespace Av {

class IRebootHandler
{
public:
    virtual void Reboot(const Brx& aReason) = 0;
    virtual ~IRebootHandler() {}
};

} // namespace Av
} // namespace OpenHome
