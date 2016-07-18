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
#include <OpenHome/Media/MimeTypeList.h>
#include <OpenHome/Private/NetworkAdapterList.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;

const Brn RadioPresetsTuneIn::kConfigKeyUsername("Radio.TuneInUserName");
const Brn RadioPresetsTuneIn::kConfigUsernameDefault("linnproducts");
const Brn RadioPresetsTuneIn::kTuneInPresetsRequest("http://opml.radiotime.com/Browse.ashx?&c=presets&options=recurse:tuneShows");
//const Brn RadioPresetsTuneIn::kFormats("&formats=mp3,wma,aac,wmvideo,ogg,hls");
const Brn RadioPresetsTuneIn::kPartnerId("&partnerId=");
const Brn RadioPresetsTuneIn::kUsername("&username=");

typedef struct MimeTuneInPair
{
    const TChar* iMimeType;
    const TChar* iTuneInFormat;
} MimeTuneInPair;

RadioPresetsTuneIn::RadioPresetsTuneIn(Environment& aEnv, const Brx& aPartnerId,
                                       IPresetDatabaseWriter& aDbWriter, IConfigInitialiser& aConfigInit,
                                       Credentials& aCredentialsManager, Media::MimeTypeList& aMimeTypeList)
    : iLock("RPTI")
    , iEnv(aEnv)
    , iDbWriter(aDbWriter)
    , iWriteBuffer(iSocket)
    , iWriterRequest(iWriteBuffer)
    , iReadBuffer(iSocket)
    , iReaderUntil(iReadBuffer)
    , iReaderResponse(aEnv, iReaderUntil)
    , iSupportedFormats("&formats=")
    , iPartnerId(aPartnerId)
{
    const MimeTuneInPair kTypes[] = {{"audio/mpeg", "mp3"}
                                    ,{"audio/x-ms-wma", "wma"}
                                    ,{"audio/aac", "aac"}
                                    ,{"video/x-ms-wmv", "wmvideo"}
                                    ,{"application/ogg", "ogg"}
                                    ,{"application/vnd.apple.mpegurl", "hls"} // https://tools.ietf.org/html/draft-pantos-http-live-streaming-14#section-10
                                    };
    const TUint maxFormats = sizeof(kTypes)/sizeof(kTypes[0]);
    TBool first = true;
    for (TUint i=0; i<maxFormats; i++) {
        Brn mimeType(kTypes[i].iMimeType);
        if (aMimeTypeList.Contains(kTypes[i].iMimeType)) {
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
    iConfigUsername = new ConfigText(aConfigInit, kConfigKeyUsername, kMaxUserNameBytes, kConfigUsernameDefault);
    iListenerId = iConfigUsername->Subscribe(MakeFunctorConfigText(*this, &RadioPresetsTuneIn::UsernameChanged));

    iNacnId = iEnv.NetworkAdapterList().AddCurrentChangeListener(MakeFunctor(*this, &RadioPresetsTuneIn::CurrentAdapterChanged), "TuneIn", false);

    new CredentialsTuneIn(aCredentialsManager, aPartnerId); // ownership transferred to aCredentialsManager
}

RadioPresetsTuneIn::~RadioPresetsTuneIn()
{
    // FIXME - not remotely threadsafe atm
    iSocket.Interrupt(true);
    iRefreshTimer->Cancel();
    iConfigUsername->Unsubscribe(iListenerId);
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iNacnId);
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

void RadioPresetsTuneIn::CurrentAdapterChanged()
{
    Refresh();
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
            LOG2(kError, kSources, "Error fetching TuneIn xml - status=%u\n", status.Code());
            THROW(HttpError);
        }

        Brn buf;
        for (;;) {
            iReaderUntil.ReadUntil('<');
            buf.Set(iReaderUntil.ReadUntil('>'));
            if (buf.BeginsWith(Brn("opml version="))) {
                break;
            }
        }
        for (;;) {
            iReaderUntil.ReadUntil('<');
            buf.Set(iReaderUntil.ReadUntil('>'));
            if (buf == Brn("status")) {
                break;
            }
        }
        buf.Set(iReaderUntil.ReadUntil('<'));
        const TUint statusCode = Ascii::Uint(buf);
        if (statusCode != 200) {
            LOG2(kError, kSources, "Error in TuneIn xml - statusCode=%u\n", statusCode);
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
            // Find the default container (there may be multiple containers if TuneIn folders are used)
            TBool foundDefault = false;
            for (; !foundDefault;) {
                iReaderUntil.ReadUntil('<');
                buf.Set(iReaderUntil.ReadUntil('>'));
                const TBool isContainer = buf.BeginsWith(Brn("outline type=\"container\""));
                if (!isContainer) {
                    continue;
                }
                Parser parser(buf);
                Brn attr;
                static const Brn kAttrDefault("is_default=\"true\"");
                while (parser.Remaining().Bytes() > 0) {
                    attr.Set(parser.Next());
                    if (attr == kAttrDefault) {
                        foundDefault = true;
                        break;
                    }
                }
            }
            // Read presets for the current container only
            for (;;) {
                iReaderUntil.ReadUntil('<');
                buf.Set(iReaderUntil.ReadUntil('>'));
                if (buf == Brn("/outline")) {
                    break;
                }
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
                    LOG2(kSources, kError, "No preset_id for TuneIn preset %.*s\n", PBUF(iPresetTitle));
                    continue;
                }
                if (presetNumber > maxPresets) {
                    LOG2(kSources, kError, "Ignoring preset number %u (index too high)\n", presetNumber);
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
            LOG2(kError, kSources, "Unexpected order of OPML elements.  Expected \"%s\", got %.*s\n", aKey, PBUF(key));
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
        LOG2(kError, kSources, "Unexpectedly long %s for preset - %.*s\n", aKey, PBUF(value));
        return false;
    }
    aValue.Replace(value);
//    Converter::FromXmlEscaped(aValue);
    return true;
}


// CredentialsTuneIn

const Brn CredentialsTuneIn::kId("tunein.com");

CredentialsTuneIn::CredentialsTuneIn(Credentials& aCredentialsManager, const Brx& aPartnerId)
{
    aCredentialsManager.Add(this);
    Bws<128> data("{\"partnerId\": \"");
    data.Append(aPartnerId);
    data.Append("\"}");
    aCredentialsManager.SetState(kId, Brx::Empty(), data);
}

const Brx& CredentialsTuneIn::Id() const
{
    return kId;
}

void CredentialsTuneIn::CredentialsChanged(const Brx& /*aUsername*/, const Brx& /*aPassword*/)
{
}

void CredentialsTuneIn::UpdateStatus()
{
}

void CredentialsTuneIn::Login(Bwx& aToken)
{
    aToken.Replace(Brx::Empty());
}

void CredentialsTuneIn::ReLogin(const Brx& /*aCurrentToken*/, Bwx& aNewToken)
{
    aNewToken.Replace(Brx::Empty());
}
