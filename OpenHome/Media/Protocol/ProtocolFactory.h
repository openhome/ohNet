#ifndef HEADER_PIPELINE_PROTOCOL_FACTORY
#define HEADER_PIPELINE_PROTOCOL_FACTORY

namespace OpenHome {
class Environment;
namespace Media {

class Protocol;

class ProtocolFactory
{
public:
    static Protocol* NewHttp(Environment& aEnv);
    static Protocol* NewFile(Environment& aEnv);
};

class ContentProcessor;

class ContentProcessorFactory
{
public:
    static ContentProcessor* NewM3u();
    static ContentProcessor* NewPls();
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_PROTOCOL_FACTORY
