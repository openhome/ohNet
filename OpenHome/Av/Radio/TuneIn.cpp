#include <OpenHome/Av/Radio/TuneIn.h>
#include <OpenHome/Types.h>
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

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;

const Brn RadioPresetsTuneIn::kConfigUsernameBase("Radio.TuneInUserName");
const Brn RadioPresetsTuneIn::kConfigUsernameDefault("linnproducts");
const Brn RadioPresetsTuneIn::kTuneInPresetsRequest("http://opml.radiotime.com/Browse.ashx?&c=presets&options=recurse:tuneShows");
//const Brn RadioPresetsTuneIn::kFormats("&formats=mp3,wma,aac,wmvideo,ogg");
const Brn RadioPresetsTuneIn::kPartnerId("&partnerId=");
const Brn RadioPresetsTuneIn::kUsername("&username=");

typedef struct MimeTuneInPair
{
    const TChar* iMimeType;
    const TChar* iTuneInFormat;
} MimeTuneInPair;

RadioPresetsTuneIn::RadioPresetsTuneIn(Environment& aEnv, Media::PipelineManager& aPipeline, const Brx& aPartnerId, IPresetDatabaseWriter& aDbWriter, IConfigInitialiser& aConfigInit)
    : iLock("RPTI")
    , iEnv(aEnv)
    , iDbWriter(aDbWriter)
    , iWriteBuffer(iSocket)
    , iWriterRequest(iWriteBuffer)
    , iReadBuffer(iSocket)
    , iReaderResponse(aEnv, iReadBuffer)
    , iSupportedFormats("&formats=")
    , iPartnerId(aPartnerId)
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

    iReaderResponse.AddHeader(iHeaderContentLength);
    iRefreshThread = new ThreadFunctor("TuneInRefresh", MakeFunctor(*this, &RadioPresetsTuneIn::RefreshThread));
    iRefreshThread->Start();
    iRefreshTimer = new Timer(aEnv, MakeFunctor(*this, &RadioPresetsTuneIn::TimerCallback), "RadioPresetsTuneIn");

    // Get username from store.
    iConfigUsername = new ConfigText(aConfigInit, kConfigUsernameBase, kMaxUserNameBytes, kConfigUsernameDefault);
    iListenerId = iConfigUsername->Subscribe(MakeFunctorConfigText(*this, &RadioPresetsTuneIn::UsernameChanged));
}

RadioPresetsTuneIn::~RadioPresetsTuneIn()
{
    // FIXME - not remotely threadsafe atm
    iSocket.Interrupt(true);
    iRefreshTimer->Cancel();
    iConfigUsername->Unsubscribe(iListenerId);
    delete iConfigUsername;
    delete iRefreshThread;
    delete iRefreshTimer;
}

void RadioPresetsTuneIn::UpdateUsername(const Brx& aUsername)
{
    Bws<256> uriBuf;
    uriBuf.Append(kTuneInPresetsRequest);
    uriBuf.Append(iSupportedFormats);
    uriBuf.Append(kPartnerId);
    uriBuf.Append(iPartnerId);
    uriBuf.Append(kUsername);
    uriBuf.Append(aUsername);
    iRequestUri.Replace(uriBuf);
}

void RadioPresetsTuneIn::UsernameChanged(KeyValuePair<const Brx&>& aKvp)
{
    UpdateUsername(aKvp.Value());
    Refresh();
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
        const TUint maxPresets = iDbWriter.MaxNumPresets();
        if (iAllocatedPresets.size() == 0) {
            iAllocatedPresets.reserve(maxPresets);
            for (TUint i=0; i<maxPresets; i++) {
                iAllocatedPresets.push_back(0);
            }
        }
        else {
            std::fill(iAllocatedPresets.begin(), iAllocatedPresets.end(), 0);
        }
        try {
            for (;;) {
                iReadBuffer.ReadUntil('<');
                buf.Set(iReadBuffer.ReadUntil('>'));
                const TBool isAudio = buf.BeginsWith(Brn("outline type=\"audio\""));
                const TBool isLink = buf.BeginsWith(Brn("outline type=\"link\""));
                if (!(isAudio || isLink)) {
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
                Converter::FromXmlEscaped(iPresetUrl);
                if (isAudio) {
                    iPresetUri.Replace(iPresetUrl);
                    if (iPresetUri.Query().Bytes() > 0) {
                        iPresetUrl.Append(Brn("&c=ebrowse")); // ensure best quality stream is selected
                    }
                }
                Bws<Ascii::kMaxUintStringBytes> byteRateBuf;
                if (ValidateKey(parser, "bitrate", false)) {
                    (void)parser.Next('\"');
                    Brn value = parser.Next('\"');
                    TUint byteRate = Ascii::Uint(value);
                    byteRate *= 125; // convert from kbits/sec to bytes/sec
                    Ascii::AppendDec(byteRateBuf, byteRate);
                }
                const TChar* imageKey = "image";
                Brn imageKeyBuf(imageKey);
                const TChar* presetNumberKey = "preset_number";
                Brn presetNumberBuf(presetNumberKey);
                Brn key = parser.Next('=');
                TBool foundImage = false, foundPresetNumber= false;
                TUint presetNumber = UINT_MAX;
                while (key.Bytes() > 0 && !(foundImage && foundPresetNumber)) {
                    if (key == imageKeyBuf) {
                        foundImage = ReadValue(parser, imageKey, iPresetArtUrl);
                    }
                    else if (key == presetNumberBuf) {
                        Bws<Ascii::kMaxUintStringBytes> buf;
                        if (ReadValue(parser, presetNumberKey, buf)) {
                            try {
                                presetNumber = Ascii::Uint(buf);
                                foundPresetNumber = true;
                            }
                            catch (AsciiError&) {}
                        }
                    }
                    else {
                        (void)parser.Next('\"');
                        (void)parser.Next('\"');
                    }
                    key.Set(parser.Next('='));
                }
                if (!foundPresetNumber) {
                    LOG2(kProducts, kError, "No preset_id for TuneIn preset ");
                    LOG2(kProducts, kError, iPresetTitle);
                    LOG2(kProducts, kError, "\n");
                    continue;
                }
                if (presetNumber > maxPresets) {
                    LOG2(kProducts, kError, "Ignoring preset number %u (index too high)\n", presetNumber);
                    continue;
                }
                const TUint presetIndex = presetNumber-1;
                iAllocatedPresets[presetIndex] = 1;

                /* Only report changes if url has changed.
                   Changes in metadata only - e.g. . 'Station ABC (Genre 1)' -> 'Station ABC (Genre 2)' - are
                   deliberately suppressed.  These result in the preset id changing, likely causing control
                   points (certainly Kinsky/Kazoo) to reset their view.  The small benefit in having preset
                   titles updated is therefore outweighed by the cost of control points not coping well when
                   a station changes its preset id. */
                iDbWriter.ReadPreset(presetIndex, iDbUri, iDbMetaData);
                if (iDbUri == iPresetUrl) {
                    continue;
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
                WriterBuffer writer(iDidlLite);
                Converter::ToXmlEscaped(writer, iPresetUrl);
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
            }
        }
        catch (ReaderError&) {
        }
        for (TUint i=0; i<maxPresets; i++) {
            if (iAllocatedPresets[i] == 0) {
                iDbWriter.ClearPreset(i);
            }
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
    if (!ValidateKey(aParser, aKey, true)) {
        return false;
    }
    return ReadValue(aParser, aKey, aValue);
}

TBool RadioPresetsTuneIn::ValidateKey(Parser& aParser, const TChar* aKey, TBool aLogErrors)
{
    Brn key = aParser.Next('=');
    if (key != Brn(aKey)) {
        if (aLogErrors) {
            LOG2(kError, kProducts, "Unexpected order of OPML elements.  Expected \"%s\", got ", aKey);
            LOG2(kError, kProducts, key);
            LOG2(kError, kProducts, "\n");
        }
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
