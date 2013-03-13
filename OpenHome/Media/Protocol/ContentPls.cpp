#include <OpenHome/Media/Protocol/ContentPls.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

/* Example pls file

[playlist]
NumberOfEntries=3

File1=http://streamexample.com:80
Title1=My Favorite Online Radio
Length1=-1

File2=http://example.com/song.mp3
Title2=Remote MP3
Length2=286

File3=/home/myaccount/album.flac
Title3=Local album
Length3=3487

Version=2

*/

// ContentPls

TBool ContentPls::Recognise(const Brx& /*aUri*/, const Brx& aMimeType, const Brx& aData)
{
    if (Ascii::CaseInsensitiveEquals(aMimeType, Brn("audio/x-scpls"))) {
        return true;
    }
    if (Ascii::Contains(aData, Brn("[playlist]"))) {
        return true;
    }
    return false;
}

ProtocolStreamResult ContentPls::Stream(Srx& aReader, TUint64 aTotalBytes, TUint64& aOffset)
{
    LOG(kMedia, "ContentPls::Stream\n");

    TBool stopped = false;
    TBool streamSucceeded = false;
    try {
        // Find [playlist]
        while (!iIsPlaylist) {
            Brn line = ReadLine(aReader, aTotalBytes, aOffset);
            if (line == Brn("[playlist]")) {
                iIsPlaylist = true;
            }
        }

        while (!stopped) {
            Brn line = ReadLine(aReader, aTotalBytes, aOffset);
            Parser parser(line);
            Brn key = parser.Next('=');
            if (key.BeginsWith(Brn("File"))) {
                Brn value = parser.Next();
                ProtocolStreamResult res = iProtocolSet->Stream(value);
                if (res == EProtocolStreamStopped) {
                    stopped = true;
                }
                else if (res == EProtocolStreamSuccess) {
                    streamSucceeded = true;
                }
            }
        }
    }
    catch (ReaderError&) {
    }

    if (stopped) {
        return EProtocolStreamStopped;
    }
    else if (iPartialLine.Bytes() > 0) {
        // break in stream.  Return an error and let caller attempt to re-establish connection
        return EProtocolStreamErrorRecoverable;
    }
    else if (streamSucceeded) {
        return EProtocolStreamSuccess;
    }
    return EProtocolStreamErrorUnrecoverable;
}

void ContentPls::Reset()
{
    ContentProcessor::Reset();
    iIsPlaylist = false;
}
