#ifndef HEADER_SOURCE_FACTORY
#define HEADER_SOURCE_FACTORY

#include <OpenHome/OhNetTypes.h>

namespace OpenHome {
namespace Av {

class ISource;
class IMediaPlayer;

class SourceFactory
{
public:
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer, const TChar* aSupportedProtocols);
    static ISource* NewUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice, const TChar* aSupportedProtocols);
};

} // namespace Av
} // namespaceOpenHome

#endif // HEADER_SOURCE_FACTORY
