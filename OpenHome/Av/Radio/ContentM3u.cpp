#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Radio/ContentProcessorFactory.h>

/* Example pls file

#EXTM3U

#EXTINF:123,Sample title
C:\Documents and Settings\I\My Music\Sample.mp3

#EXTINF:321,Example title
C:\Documents and Settings\I\My Music\Greatest Hits\Example.ogg

*/

namespace OpenHome {
namespace Av {

class ContentM3u : public Media::ContentProcessor
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


ContentProcessor* ContentProcessorFactory::NewM3u()
{ // static
    return new ContentM3u();
}


// ContentM3u

TBool ContentM3u::Recognise(const Brx& /*aUri*/, const Brx& aMimeType, const Brx& aData)
{
    if (Ascii::CaseInsensitiveEquals(aMimeType, Brn("audio/x-mpegurl")) ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("audio/mpegurl"))) {
        return true;
    }
    if (Ascii::Contains(aData, Brn("#EXTM3U")) && !Ascii::Contains(aData, Brn("#EXT-X-"))) {
        return true;
    }
    return false;
}

ProtocolStreamResult ContentM3u::Stream(IProtocolReader& aReader, TUint64 aTotalBytes)
{
    LOG(kMedia, "ContentM3u::Stream\n");

    TUint64 bytesRemaining = aTotalBytes;
    TBool stopped = false;
    TBool streamSucceeded = false;
    try {
        while (!stopped) {
            Brn line = ReadLine(aReader, bytesRemaining);
            if (line.Bytes() == 0 || line.BeginsWith(Brn("#"))) {
                continue; // empty/comment line
            }
            ProtocolStreamResult res = iProtocolSet->Stream(line);
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
