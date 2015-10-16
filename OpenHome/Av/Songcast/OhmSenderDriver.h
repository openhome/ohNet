#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>

namespace OpenHome {
namespace Av {

class IOhmSenderDriver
{
public:
    virtual void SetEnabled(TBool aValue) = 0;
    virtual void SetEndpoint(const Endpoint& aEndpoint, TIpAddress aAdapter) = 0;
    virtual void SetActive(TBool aValue) = 0;
    virtual void SetTtl(TUint aValue) = 0;
    virtual void SetLatency(TUint aValue) = 0;
    virtual void SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal) = 0;
    virtual void Resend(const Brx& aFrames) = 0;
    virtual ~IOhmSenderDriver() {}
};

} // namespace Av
} // namespace OpenHome


