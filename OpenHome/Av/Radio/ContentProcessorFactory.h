#ifndef HEADER_CONTENT_PROCESSOR_FACTORY
#define HEADER_CONTENT_PROCESSOR_FACTORY

namespace OpenHome {
namespace Media {
    class ContentProcessor;
    class IMimeTypeList;
} // namespace Media
namespace Av {

class ContentProcessorFactory
{
public:
    static Media::ContentProcessor* NewM3u(Media::IMimeTypeList& aMimeTypeList);
    static Media::ContentProcessor* NewM3uX();
    static Media::ContentProcessor* NewPls(Media::IMimeTypeList& aMimeTypeList);
    static Media::ContentProcessor* NewOpml(Media::IMimeTypeList& aMimeTypeList);
    static Media::ContentProcessor* NewAsx();
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CONTENT_PROCESSOR_FACTORY
