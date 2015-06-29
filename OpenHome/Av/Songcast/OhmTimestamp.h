#ifndef HEADER_OHM_TIMESTAMP
#define HEADER_OHM_TIMESTAMP

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Network.h>

EXCEPTION(OhmTimestampNotFound);

namespace OpenHome {
    class Environment;
namespace Av {

class IOhmTimestamper
{
public:
    virtual ~IOhmTimestamper() {}
    virtual void Start(const Endpoint& aDst) = 0;
    virtual void Stop() = 0;
    virtual TUint Timestamp(TUint aFrame) = 0;
};


class IOhmTimestampMapper
{
public:
    virtual ~IOhmTimestampMapper() {}
    virtual TUint Map(TUint aTimestamp, TUint aSampleRate) = 0;
};


} // namespace Av
} // namespace OpenHome

#endif // HEADER_OHM_TIMESTAMP
