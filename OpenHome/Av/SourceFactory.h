#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Optional.h>

namespace OpenHome {
namespace Net {
    class DvDevice;
}
namespace Media {
    class IClockPuller;
}
namespace Av {

class ISource;
class IMediaPlayer;
class IOhmTimestamper;

class SourceFactory
{
public:
    static ISource* NewPlaylist(IMediaPlayer& aMediaPlayer);
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer);
    static ISource* NewRadio(IMediaPlayer& aMediaPlayer, const Brx& aTuneInPartnerId);
    static ISource* NewUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice);
    static ISource* NewRaop(IMediaPlayer& aMediaPlayer, Optional<Media::IClockPuller> aClockPuller, const Brx& aMacAddr);
    static ISource* NewReceiver(IMediaPlayer& aMediaPlayer,
                                Optional<Media::IClockPuller> aClockPuller,
                                Optional<IOhmTimestamper> aTxTimestamper,
                                Optional<IOhmTimestamper> aRxTimestamper);

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

