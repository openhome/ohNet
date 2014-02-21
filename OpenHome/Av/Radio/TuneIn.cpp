#include <OpenHome/Av/Radio/TuneIn.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Media/PipelineManager.h>

using namespace OpenHome;
using namespace OpenHome::Av;

const Brn RadioPresetsTuneIn::kTuneInPresetsRequest("http://opml.radiotime.com/Browse.ashx?&c=presets&options=recurse:tuneShows");
//const Brn RadioPresetsTuneIn::kFormats("&formats=mp3,wma,aac,wmvideo,ogg");
const Brn RadioPresetsTuneIn::kPartnerId("&partnerId=ah2rjr68");
const Brn RadioPresetsTuneIn::kUsername("&username=");

typedef struct MimeTuneInPair
{
    const TChar* iMimeType;
    const TChar* iTuneInFormat;
} MimeTuneInPair;

RadioPresetsTuneIn::RadioPresetsTuneIn(Environment& aEnv, Media::PipelineManager& aPipeline, IPresetDatabaseWriter& aDbWriter, const Brx& aUserName)
    : iLock("RPTI")
    , iEnv(aEnv)
    , iDbWriter(aDbWriter)
    , iWriteBuffer(iSocket)
    , iWriterRequest(iWriteBuffer)
    , iReadBuffer(iSocket)
    , iReaderResponse(aEnv, iReadBuffer)
    , iSupportedFormats("&formats=")
{
    const MimeTuneInPair kTypes[] = {{"audio/mpeg", "mp3"}
                                    ,{"audio/x-ms-wma", "wma"}
                                    ,{"audio/aac", "aac"}
                                    ,{"video/x-ms-wmv", "wmvideo"}
                                    ,{"application/ogg", "ogg"}};
    const TUint maxFormats = sizeof(kTypes)/sizeof(kTypes[0]);
    TBool first = true;
    for (TUint i=0; i<maxFormats; i++) {
        Brn mimeType(kTypes[i].iMimeType);
        if (aPipeline.SupportsMimeType(mimeType)) {
            if (first) {
                first = false;
            }
            else {
                iSupportedFormats.Append(",");
            }
            iSupportedFormats.Append(kTypes[i].iTuneInFormat);
        }
    }
    Log::Print("iSupportedFormats = ");
    Log::Print(iSupportedFormats);
    Log::Print("\n");
    Bws<256> uriBuf;
    uriBuf.Append(kTuneInPresetsRequest);
    uriBuf.Append(iSupportedFormats);
    uriBuf.Append(kPartnerId);
    uriBuf.Append(kUsername);
    uriBuf.Append(aUserName);
    iRequestUri.Replace(uriBuf);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iRefreshThread = new ThreadFunctor("TuneInRefresh", MakeFunctor(*this, &RadioPresetsTuneIn::RefreshThread));
    iRefreshThread->Start();
    iRefreshTimer = new Timer(aEnv, MakeFunctor(*this, &RadioPresetsTuneIn::TimerCallback));
    Refresh();
}

RadioPresetsTuneIn::~RadioPresetsTuneIn()
{
    // FIXME - not remotely threadsafe atm
    iSocket.Interrupt(true);
    iRefreshTimer->Cancel();
    delete iRefreshThread;
    delete iRefreshTimer;
}

void RadioPresetsTuneIn::Refresh()
{
    iRefreshThread->Signal();
}

void RadioPresetsTuneIn::TimerCallback()
{
    Refresh();
}

void RadioPresetsTuneIn::RefreshThread()
{
    for (;;) {
        iRefreshThread->Wait();
        iRefreshTimer->FireIn(kRefreshRateMs);
        try {
            iSocket.Open(iEnv);
            DoRefresh();
            iSocket.Close();
        }
        catch (NetworkError&) {
        }
    }
}

void RadioPresetsTuneIn::DoRefresh()
{
    TBool startedUpdates = false;
    try {
        Endpoint ep(80, iRequestUri.Host());
        iSocket.Connect(ep, 20 * 1000); // hard-coded timeout.  Ignores .InitParams().TcpConnectTimeoutMs() on the assumption that is set for lan connections

        // FIXME - try sending If-Modified-Since header with request. See rfr2616 14.25
        // ... this may require that we use http 1.1 in the request, so cope with a chunked response
        iWriterRequest.WriteMethod(Http::kMethodGet, iRequestUri.PathAndQuery(), Http::eHttp10);
        const TUint port = (iRequestUri.Port() == -1? 80 : (TUint)iRequestUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iRequestUri.Host(), port);
        Http::WriteHeaderConnectionClose(iWriterRequest);
        iWriterRequest.WriteFlush();

        iReaderResponse.Read(kReadResponseTimeoutMs);
        const HttpStatus& status = iReaderResponse.Status();
        if (status != HttpStatus::kOk) {
            LOG2(kError, kProducts, "Error fetching TuneIn xml - status=%u\n", status.Code());
            THROW(HttpError);
        }

#if 1
        Brn buf;
        for (;;) {
            iReadBuffer.ReadUntil('<');
            buf.Set(iReadBuffer.ReadUntil('>'));
            if (buf.BeginsWith(Brn("opml version="))) {
                break;
            }
        }
        for (;;) {
            iReadBuffer.ReadUntil('<');
            buf.Set(iReadBuffer.ReadUntil('>'));
            if (buf == Brn("status")) {
                break;
            }
        }
        buf.Set(iReadBuffer.ReadUntil('<'));
        const TUint statusCode = Ascii::Uint(buf);
        if (statusCode != 200) {
            LOG2(kError, kProducts, "Error in TuneIn xml - statusCode=%u\n", statusCode);
            return;
        }

        iDbWriter.BeginSetPresets();
        startedUpdates = true;
        TUint presetIndex = 0;
        const TUint maxPresets = iDbWriter.MaxNumPresets();
        try {
            for (;presetIndex<maxPresets;) {
                iReadBuffer.ReadUntil('<');
                buf.Set(iReadBuffer.ReadUntil('>'));
                if (!buf.BeginsWith(Brn("outline type=\"audio\"")) &&
                    !buf.BeginsWith(Brn("outline type=\"link\""))) {
                    continue;
                }
                Parser parser(buf);
                (void)parser.Next('='); // outline type="audio" - ignore
                (void)parser.Next('\"');
                (void)parser.Next('\"');

                if (!ReadElement(parser, "text", iPresetTitle) ||
                    !ReadElement(parser, "URL", iPresetUrl)) {
                    continue;
                }
                Bws<Ascii::kMaxUintStringBytes> byteRateBuf;
                if (ValidateKey(parser, "bitrate")) {
                    (void)parser.Next('\"');
                    Brn value = parser.Next('\"');
                    TUint byteRate = Ascii::Uint(value);
                    byteRate *= 125; // convert from kbits/sec to bytes/sec
                    Ascii::AppendDec(byteRateBuf, byteRate);
                }

                const TChar* imageKey = "image";
                Brn imageKeyBuf(imageKey);
                Brn key = parser.Next('=');
                while (key.Bytes() > 0 && key != imageKeyBuf) {
                    (void)parser.Next('\"');
                    (void)parser.Next('\"');
                    key.Set(parser.Next('='));
                }
                if (key.Bytes() > 0) {
                    ReadValue(parser, imageKey, iPresetArtUrl);
                }
                else {
                    LOG(kProducts, "No art for TuneIn preset ");
                    LOG(kProducts, iPresetTitle);
                    LOG(kProducts, "\n");
                }

                iDidlLite.SetBytes(0);
                //iDidlLite.Append("<DIDL-Lite xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
                iDidlLite.Append("<DIDL-Lite xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\" xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
                iDidlLite.Append("<item id=\"\" parentID=\"\" restricted=\"True\">");
                iDidlLite.Append("<dc:title>");
                iDidlLite.Append(iPresetTitle);
                iDidlLite.Append("</dc:title>");
                iDidlLite.Append("<res protocolInfo=\"*:*:*:*\" bitrate=\"");
                iDidlLite.Append(byteRateBuf);
                iDidlLite.Append("\">");
                iDidlLite.Append(iPresetUrl);
                iDidlLite.Append("</res>");
                //iDidlLite.Append("<upnp:albumArtURI xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\">");
                iDidlLite.Append("<upnp:albumArtURI>");
                iDidlLite.Append(iPresetArtUrl);
                iDidlLite.Append("</upnp:albumArtURI>");
                //iDidlLite.Append("<upnp:class xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\">object.item.audioItem</upnp:class>");
                iDidlLite.Append("<upnp:class>object.item.audioItem</upnp:class>");
                iDidlLite.Append("</item>");
                iDidlLite.Append("</DIDL-Lite>");
                iDbWriter.SetPreset(presetIndex, iPresetUrl, iDidlLite);
                presetIndex++;
            }
        }
        catch (ReaderError&) {
        }
        for (; presetIndex<maxPresets; presetIndex++) {
            iDbWriter.ClearPreset(presetIndex);
        }

#else // OLD_DEBUGGING_CODE
        TUint length = iHeaderContentLength.ContentLength();
        ASSERT(length != 0); // we assume that TuneIn doesn't chunk its responses
        Bwh buf(length); // FIXME - avoid dynamic allocation like this at all costs
        while (length > 0) {
            TUint readBytes = (length<kReadBufBytes? length : kReadBufBytes);
            buf.Append(iReadBuffer.Read(readBytes));
            length -= readBytes;
        }
# if 1
        Log::Print("Response from TuneIn is...\n\n");
        Log::Print(buf);
        Log::Print("\n\n");
# endif
#endif // OLD_DEBUGGING_CODE
    }
    catch (NetworkError&) {
    }
    catch (NetworkTimeout&) {
    }
    catch (WriterError&) {
    }
    catch (HttpError&) {
    }
    catch (ReaderError&) {
    }
    if (startedUpdates) {
        iDbWriter.EndSetPresets();
    }
}

TBool RadioPresetsTuneIn::ReadElement(Parser& aParser, const TChar* aKey, Bwx& aValue)
{
    if (!ValidateKey(aParser, aKey)) {
        return false;
    }
    return ReadValue(aParser, aKey, aValue);
}

TBool RadioPresetsTuneIn::ValidateKey(Parser& aParser, const TChar* aKey)
{
    Brn key = aParser.Next('=');
    if (key != Brn(aKey)) {
        LOG2(kError, kProducts, "Unexpected order of OPML elements.  Expected \"%s\", got ", aKey);
        LOG2(kError, kProducts, key);
        LOG2(kError, kProducts, "\n");
        return false;
    }
    return true;
}

TBool RadioPresetsTuneIn::ReadValue(Parser& aParser, const TChar* aKey, Bwx& aValue)
{
    (void)aParser.Next('\"');
    Brn value = aParser.Next('\"');
    if (value.Bytes() > aValue.MaxBytes()) {
        LOG2(kError, kProducts, "Unexpectedly long %s for preset - ", aKey);
        LOG2(kError, kProducts, value);
        LOG2(kError, kProducts, "\n");
        return false;
    }
    aValue.Replace(value);
//    Converter::FromXmlEscaped(aValue);
    return true;
}
