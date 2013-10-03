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
    static ISource* NewPlaylist(IMediaPlayer& aMediaPlayer, const Brx& aSupportedProtocols);
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer, const Brx& aSupportedProtocols);
    static ISource* NewUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice, const Brx& aSupportedProtocols);
    static ISource* NewRaop(IMediaPlayer& aMediaPlayer, const TChar* aHostName, const Brx& aDeviceName, TUint aDiscoveryPort);
};

} // namespace Av
} // namespaceOpenHome

#endif // HEADER_SOURCE_FACTORY
