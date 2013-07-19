#ifndef HEADER_SOURCE_FACTORY
#define HEADER_SOURCE_FACTORY

#include <OpenHome/OhNetTypes.h>

namespace OpenHome {
namespace Net {
    class DvDevice;
}
namespace Av {

class ISource;
class IMediaPlayer;

class SourceFactory
{
public:
    static ISource* NewPlaylist(IMediaPlayer& aMediaPlayer, const TChar* aSupportedProtocols);
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer, const TChar* aSupportedProtocols);
    static ISource* NewUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice, const TChar* aSupportedProtocols);
    static ISource* NewRaop(IMediaPlayer& aMediaPlayer, const Brx& aDeviceName, TUint aDiscoveryPort);
};

} // namespace Av
} // namespaceOpenHome

#endif // HEADER_SOURCE_FACTORY
