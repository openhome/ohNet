#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {
namespace Av {

class ITransportModes
{
public:
    virtual void Add(const Brx& aMode) = 0;
    virtual ~ITransportModes() {}
};

class ITransportActivator
{
public:
    virtual TBool TryActivate(const Brx& aMode) = 0;
    virtual ~ITransportActivator() {}
};

} // namespace Av
} // namespace OpenHome
