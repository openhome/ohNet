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

class IFriendlyNameObservable;
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
    static ISource* NewRaop(IMediaPlayer& aMediaPlayer, IFriendlyNameObservable& aFriendlyNameObservable, const Brx& aMacAddr);
    static ISource* NewReceiver(IMediaPlayer& aMediaPlayer,
                                IOhmTimestamper* aTxTimestamper,
                                IOhmTimestampMapper* aTxTsMapper,
                                IOhmTimestamper* aRxTimestamper,
                                IOhmTimestampMapper* aRxTsMapper,
                                const Brx& aSenderIconFileName);

    static const TChar* kSourceTypePlaylist;
    static const TChar* kSourceTypeRadio;
    static const TChar* kSourceTypeUpnpAv;
    static const TChar* kSourceTypeRaop;
    static const TChar* kSourceTypeReceiver;

    static const Brn kSourceNamePlaylist;
    static const Brn kSourceNameRadio;
    static const Brn kSourceNameUpnpAv;
    static const Brn kSourceNameRaop;
    static const Brn kSourceNameReceiver;
};

} // namespace Av
} // namespaceOpenHome

