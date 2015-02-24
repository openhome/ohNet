#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Radio/ContentProcessorFactory.h>

/**
 *
 * https://tools.ietf.org/html/draft-pantos-http-live-streaming-14
 *
 * HLS uses a variant of M3U which adds its own tags of the form:
 *  #EXT-X-*
 *
 * In particular, a "master playlist" M3U/M3U8 (utf-8 encoded M3U) should
 * contain at least one stream variant (which will be a link to another M3U containing
 * one or more renditions).
 *
 * The stream variant tag has the following form:
 *  #EXT-X-STREAM-INF
 *
 *
 * An example master playlist is as follows:

   #EXTM3U
   #EXT-X-STREAM-INF:BANDWIDTH=1280000,AVERAGE-BANDWIDTH=1000000
   http://example.com/low.m3u8
   #EXT-X-STREAM-INF:BANDWIDTH=2560000,AVERAGE-BANDWIDTH=2000000
   http://example.com/mid.m3u8
   #EXT-X-STREAM-INF:BANDWIDTH=7680000,AVERAGE-BANDWIDTH=6000000
   http://example.com/hi.m3u8
   #EXT-X-STREAM-INF:BANDWIDTH=65000,CODECS="mp4a.40.5"
   http://example.com/audio-only.m3u8

 */


namespace OpenHome {
namespace Av {

class ContentM3uX : public Media::ContentProcessor
{
private: // from ContentProcessor
    TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData) override;
    Media::ProtocolStreamResult Stream(Media::IProtocolReader& aReader, TUint64 aTotalBytes) override;
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Av;


ContentProcessor* ContentProcessorFactory::NewM3uX()
{ // static
    return new ContentM3uX();
}


// ContentPls

TBool ContentM3uX::Recognise(const Brx& /*aUri*/, const Brx& aMimeType, const Brx& aData)
{
    Bws<100> mimeType(aMimeType);
    mimeType;
    Bws<100> data(aData);
    data;
    if (Ascii::CaseInsensitiveEquals(aMimeType, Brn("application/x-mpegurl")) ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("application/vnd.apple.mpegurl"))/* ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("audio/x-mpegurl")) ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("audio/mpegurl"))*/) {
            // Comparing against audio/x-mpegurl or audio/mpegurl alone could
            // clash with other M3U files.
        return true;
    }
    if (Ascii::Contains(aData, Brn("#EXTM3U")) &&
        Ascii::Contains(aData, Brn("#EXT-X-STREAM-INF"))) {
        return true;
    }
    return false;
}

// FIXME - need to iterate over to find highest quality stream first
// Currently, TuneIn only provides one master playlist per stream quality (and we
// receive streams ordered by quality).
ProtocolStreamResult ContentM3uX::Stream(IProtocolReader& aReader, TUint64 aTotalBytes)
{
    LOG(kMedia, "ContentM3uX::Stream\n");

    TUint64 bytesRemaining = aTotalBytes;
    TBool stopped = false;
    TBool streamSucceeded = false;
    try {
        while (!stopped) {
            Brn line = ReadLine(aReader, bytesRemaining);
            if (line.Bytes() == 0 || line.BeginsWith(Brn("#"))) {
                continue; // empty/comment line
            }

            // Only want to stream one variant, but one or more may fail.
            // If that is the case, definitely want to fall through to other variants.
            Parser p(line);
            Brn scheme = p.Next(':');
            ProtocolStreamResult res;
            if (scheme == Brn("http") || scheme == Brn("HTTP")) {
                Bws<Uri::kMaxUriBytes> uriHls("hls");
                TUint offset = scheme.Bytes();
                uriHls.Append(line.Ptr()+offset, line.Bytes()-offset);
                res = iProtocolSet->Stream(uriHls);
            }
            else {
                res = iProtocolSet->Stream(line);
            }
            if (res == EProtocolStreamStopped) {
                stopped = true;
            }
            else if (res == EProtocolStreamSuccess) {
                streamSucceeded = true;
            }
        }
    }
    catch (ReaderError&) {
    }

    if (stopped) {
        return EProtocolStreamStopped;
    }
    else if (bytesRemaining > 0 && bytesRemaining < aTotalBytes) {
        // break in stream.  Return an error and let caller attempt to re-establish connection
        return EProtocolStreamErrorRecoverable;
    }
    else if (streamSucceeded) {
        return EProtocolStreamSuccess;
    }
    return EProtocolStreamErrorUnrecoverable;
}
