#pragma once

#include <OpenHome/Types.h>

namespace OpenHome {
    class Environment;
    class ITimerFactory;
namespace Media {

class Protocol;

class HlsTestFactory
{
public:
    static Protocol* NewTestableHls(Environment& aEnv, IHlsReader* aReaderM3u, IHlsReader* aReaderSegment, ITimerFactory* aTimerFactory, ISemaphore* aM3uReaderSem);
};

} // namespace Media
} // namespace OpenHome

