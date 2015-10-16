#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

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
class IOhmTimestampMapper;

class SourceFactory
{
public:
    static ISource* NewPlaylist(IMediaPlayer& aMediaPlayer);
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer);
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer, const Brx& aTuneInPartnerId);
    static ISource* NewUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice);
    static ISource* NewRaop(IMediaPlayer& aMediaPlayer, const TChar* aHostName, IObservableBrx& aFriendlyName, const Brx& aMacAddr);
    static ISource* NewReceiver(IMediaPlayer& aMediaPlayer,
                                IOhmTimestamper* aTxTimestamper,
                                IOhmTimestampMapper* aTxTsMapper,
                                IOhmTimestamper* aRxTimestamper,
                                IOhmTimestampMapper* aRxTsMapper,
                                const Brx& aSenderIconFileName);
};

} // namespace Av
} // namespaceOpenHome

