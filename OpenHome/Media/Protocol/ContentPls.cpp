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
    if (aMimeType.Bytes() == 0 && Ascii::Contains(aData, Brn("[playlist]"))) {
        return true;
    }
    return false;
}

ProtocolStreamResult ContentPls::Stream(Srx& aReader, TUint64 /*aRemainingBytes*/, TUint /*aMaxReadBytes*/)
{
    LOG(kMedia, "ContentPls::Stream\n");

    ProtocolStreamResult res = EProtocolStreamSuccess;
    TBool isPlaylist = false;
    try {
        // Find [playlist]
        for (;;) {
            Brn line = ReadLine(aReader);
            if (line == Brn("[playlist]")) {
                isPlaylist = true;
                break;
            }
        }
        if (!isPlaylist) {
            return EProtocolStreamErrorUnrecoverable;
        }

        while (res != EProtocolStreamStopped) {
            Brn line = ReadLine(aReader);
            Parser parser(line);
            Brn key = parser.Next('=');
            if (key.BeginsWith(Brn("File"))) {
                Brn value = parser.Next();
                res = iProtocolSet->Stream(value);
            }
        }
    }
    catch (ReaderError&) {
    }

    if (!isPlaylist) {
        return EProtocolStreamErrorUnrecoverable;
    }
    else if (res == EProtocolStreamStopped) {
        return res;
    }
    return EProtocolStreamSuccess;
}

Brn ContentPls::ReadLine(Srx& aReader)
{
    TBool done = false;
    while (!done) {
        Brn line;
        try {
            line.Set(Ascii::Trim(aReader.ReadUntil(Ascii::kLf)));
        }
        catch (ReaderError&) {
            line.Set(aReader.Snaffle());
            done = true;
        }
        if (line.Bytes() > 0) {
            LOG(kMedia, line);
            LOG(kMedia, "\n");
            return line;
        }
    }
    THROW(ReaderError);
}
