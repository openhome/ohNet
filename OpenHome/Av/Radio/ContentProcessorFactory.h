#ifndef HEADER_CONTENT_PROCESSOR_FACTORY
#define HEADER_CONTENT_PROCESSOR_FACTORY

namespace OpenHome {
namespace Media {
    class ContentProcessor;
} // namespace Media
namespace Av {

class ContentProcessorFactory
{
public:
    static Media::ContentProcessor* NewM3u();
    static Media::ContentProcessor* NewM3uX();
    static Media::ContentProcessor* NewPls();
    static Media::ContentProcessor* NewOpml();
    static Media::ContentProcessor* NewAsx();
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CONTENT_PROCESSOR_FACTORY
