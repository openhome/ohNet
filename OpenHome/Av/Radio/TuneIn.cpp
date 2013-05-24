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
#include <OpenHome/Av/Radio/RadioDatabase.h>

using namespace OpenHome;
using namespace OpenHome::Av;

const Brn RadioPresetsTuneIn::kTuneInPresetsRequest("http://opml.radiotime.com/Browse.ashx?&c=presets&options=recurse:tuneShows");
const Brn RadioPresetsTuneIn::kFormats("&formats=mp3,wma,aac,wmvideo,ogg");
const Brn RadioPresetsTuneIn::kPartnerId("&partnerId=ah2rjr68");
const Brn RadioPresetsTuneIn::kUsername("&username=");

RadioPresetsTuneIn::RadioPresetsTuneIn(Environment& aEnv, IRadioDatabaseWriter& aDbWriter, const Brx& aUserName)
    : iLock("RPTI")
    , iEnv(aEnv)
    , iDbWriter(aDbWriter)
    , iWriteBuffer(iSocket)
    , iWriterRequest(iWriteBuffer)
    , iReadBuffer(iSocket)
    , iReaderResponse(aEnv, iReadBuffer)
{
    Bws<256> uriBuf;
    uriBuf.Append(kTuneInPresetsRequest);
    uriBuf.Append(kFormats);
    uriBuf.Append(kPartnerId);
    uriBuf.Append(kUsername);
    uriBuf.Append(aUserName);
    iRequestUri.Replace(uriBuf);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iRefreshThread = new ThreadFunctor("RPTI", MakeFunctor(*this, &RadioPresetsTuneIn::RefreshThread));
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
    try {
        Endpoint ep(80, iRequestUri.Host());
        const TUint timeout = iEnv.InitParams().TcpConnectTimeoutMs();
        iSocket.Connect(ep, timeout);

        iWriterRequest.WriteMethod(Http::kMethodGet, iRequestUri.PathAndQuery(), Http::eHttp10);
        Http::WriteHeaderHost(iWriterRequest, iRequestUri);
        Http::WriteHeaderConnectionClose(iWriterRequest);
        iWriterRequest.WriteFlush();

        iReaderResponse.Read(kReadResponseTimeoutMs);
        const HttpStatus& status = iReaderResponse.Status();
        if (status != HttpStatus::kOk) {
            THROW(HttpError);
        }
        TUint length = iHeaderContentLength.ContentLength();
        ASSERT(length != 0); // we assume that TuneIn doesn't chunk its responses
        Bwh buf(length); // FIXME - avoid dynamic allocation like this at all costs
        while (length > 0) {
            TUint readBytes = (length<kReadBufBytes? length : kReadBufBytes);
            buf.Append(iReadBuffer.Read(readBytes));
            length -= readBytes;
        }
        Log::Print("Response from TuneIn is...\n\n");
        Log::Print(buf);
        Log::Print("\n\n");
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
}
