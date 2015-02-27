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
    void Reset() override;
    Media::ProtocolStreamResult Stream(Media::IProtocolReader& aReader, TUint64 aTotalBytes) override;
private:
    TUint iBandwidth;
    TBool iIsAudio;
    TBool iCacheNextUri;
    Bws<Uri::kMaxUriBytes> iUriHls;
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


// ContentM3uX

TBool ContentM3uX::Recognise(const Brx& /*aUri*/, const Brx& aMimeType, const Brx& aData)
{
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

void ContentM3uX::Reset()
{
    ContentProcessor::Reset();
    iBandwidth = 0;
    iIsAudio = false;
    iCacheNextUri = false;
    iUriHls.SetBytes(0);
}

// FIXME - need to iterate over to find highest quality stream first
// Currently, TuneIn only provides one master playlist per stream quality (and we
// receive streams ordered by quality).
ProtocolStreamResult ContentM3uX::Stream(IProtocolReader& aReader, TUint64 aTotalBytes)
{
    LOG(kMedia, "ContentM3uX::Stream\n");

    TUint64 bytesRemaining = aTotalBytes;
    try {
        for (;;) {
            Brn line = ReadLine(aReader, bytesRemaining);
            if (line.Bytes() == 0) {// || line.BeginsWith(Brn("#"))) {
                continue; // empty/comment line
            }

            // Only want to stream one variant, but one or more may fail.
            // If that is the case, definitely want to fall through to other variants.
            Parser p(line);
            Brn prefix = p.Next(':');

            if (prefix == Brn("#EXT-X-STREAM-INF")) {
                TUint attribBandwidth = 0;
                TBool attribAudio = false;
                while (!p.Finished()) {
                    Brn attrib = p.Next(',');
                    Parser attribParser(attrib);
                    Brn attribName = attribParser.Next('=');
                    Brn attribValue = attribParser.Next();
                    if (attribName == Brn("BANDWIDTH")) {   // required attrib
                        attribBandwidth = Ascii::Uint(attribValue);
                    }
                    else if (attribName == Brn("CODECS")) {
                        static const Brn kAudioCodecPrefix("\"mp4a");
                        if (attribValue.Bytes() >= kAudioCodecPrefix.Bytes()) {
                            if (Brn(attribValue.Ptr(), kAudioCodecPrefix.Bytes()) == kAudioCodecPrefix) {
                                attribAudio = true;
                            }
                        }
                    }
                }

                if (attribAudio && !iIsAudio) {
                    // Haven't found an audio-only stream yet, so cache it.
                    iCacheNextUri = true;
                    iBandwidth = attribBandwidth;
                    iIsAudio = true;
                }
                else if (attribAudio && attribBandwidth > iBandwidth) {
                    // Found higher-bandwidth audio-only stream, so cache it.
                    iCacheNextUri = true;
                    iBandwidth = attribBandwidth;
                }
                else if (!iIsAudio && attribBandwidth > iBandwidth) {
                    // Not explicitly an audio-only stream, but higher-bandwidth than existing, so cache it.
                    iCacheNextUri = true;
                    iBandwidth = attribBandwidth;
                }
            }
            else if (iCacheNextUri && (prefix == Brn("http") || prefix == Brn("HTTP"))) {
                iUriHls.Replace("hls");
                TUint offset = prefix.Bytes();
                iUriHls.Append(line.Ptr()+offset, line.Bytes()-offset);
                iCacheNextUri = false;
            }
        }
    }
    catch (ReaderError&) {
    }

    // Should get here via a ReaderError.
    // Need to check if entire M3U has been read, or if there was an unexpected break in stream.
    if (iUriHls.Bytes() == 0 && bytesRemaining == 0 && bytesRemaining < aTotalBytes) {
        // Parsed entire file and didn't find stream.
        return EProtocolStreamErrorUnrecoverable;
    }
    else if (iUriHls.Bytes() == 0 && bytesRemaining > 0 && bytesRemaining < aTotalBytes) {
        // Started parsing, but didn't finish.
        return EProtocolStreamErrorRecoverable;
    }
    else if (iUriHls.Bytes() == 0) {
        // Didn't find URL for unknown reason; give up.
        return EProtocolStreamErrorUnrecoverable;
    }

    TBool streamSucceeded = false;
    ProtocolStreamResult res = iProtocolSet->Stream(iUriHls);
    if (res == EProtocolStreamStopped) {
        return EProtocolStreamStopped;
    }
    else if (res == EProtocolStreamSuccess) {
        streamSucceeded = true;
    }

    if (!streamSucceeded && bytesRemaining > 0 && bytesRemaining < aTotalBytes) {
        // break in stream.  Return an error and let caller attempt to re-establish connection
        return EProtocolStreamErrorRecoverable;
    }
    else if (streamSucceeded) {
        return EProtocolStreamSuccess;
    }
    return EProtocolStreamErrorUnrecoverable;
}
