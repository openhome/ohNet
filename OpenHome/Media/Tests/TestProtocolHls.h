#pragma once

#include <OpenHome/Types.h>

namespace OpenHome {
    class Environment;
namespace Media {

class Protocol;

class HlsTestFactory
{
public:
    static Protocol* NewTestableHls(Environment& aEnv, IHlsReader* aReaderM3u, IHlsReader* aReaderSegment, IHlsTimer* aTimer, ISemaphore* aM3uReaderSem);
};

} // namespace Media
} // namespace OpenHome

