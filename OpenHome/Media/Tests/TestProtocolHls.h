#ifndef HEADER_PIPELINE_HLS_TEST_FACTORY
#define HEADER_PIPELINE_HLS_TEST_FACTORY

#include <OpenHome/Types.h>

namespace OpenHome {
    class Environment;
namespace Media {

class Protocol;

class HlsTestFactory
{
public:
    static Protocol* NewTestableHls(Environment& aEnv, IHlsReader* aReaderM3u, IHlsReader* aReaderSegment, ITimer* aTimer, ISemaphore* aM3uReaderSem);
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_HLS_TEST_FACTORY
