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
    static Protocol* NewTestableHls(Environment& aEnv, IHttpSocket& aM3uSocket, IReaderBuffered& aM3uReader, IHttpSocket& aSegmentSocket, IReaderBuffered& aSegmentReader);
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_HLS_TEST_FACTORY
