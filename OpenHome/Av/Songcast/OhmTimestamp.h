#ifndef HEADER_OHM_TIMESTAMP
#define HEADER_OHM_TIMESTAMP

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
    class Environment;
namespace Av {

class IOhmTimestamper
{
public:
    virtual ~IOhmTimestamper() {}
    virtual TUint Timestamp(TUint aFrame) = 0;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_OHM_TIMESTAMP
