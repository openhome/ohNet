#ifndef HEADER_SOURCE_FACTORY
#define HEADER_SOURCE_FACTORY

#include <OpenHome/Types.h>

namespace OpenHome {
    class IObservableBrx;
namespace Net {
    class DvDevice;
}
namespace Media {
    class IPullableClock;
}
namespace Av {

class ISource;
class IMediaPlayer;
class IOhmTimestamper;

class SourceFactory
{
public:
    static ISource* NewPlaylist(IMediaPlayer& aMediaPlayer, const Brx& aSupportedProtocols);
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock, const Brx& aSupportedProtocols);
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock, const Brx& aSupportedProtocols, const Brx& aTuneInPartnerId);
    static ISource* NewUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice, const Brx& aSupportedProtocols);
    static ISource* NewRaop(IMediaPlayer& aMediaPlayer, const TChar* aHostName, IObservableBrx& aFriendlyName, const Brx& aMacAddr);
    static ISource* NewReceiver(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock, IOhmTimestamper* aTimestamper, const Brx& aSenderIconFileName);
};

} // namespace Av
} // namespaceOpenHome

#endif // HEADER_SOURCE_FACTORY
