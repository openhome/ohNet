#include <OpenHome/Av/Scd/Receiver/ProtocolScd.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Av/Scd/Receiver/SupplyScd.h>
#include <OpenHome/Av/Scd/Receiver/OhMetadata.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Debug.h>

#include <memory>

using namespace OpenHome;
using namespace OpenHome::Scd;
using namespace OpenHome::Media;

const TUint ProtocolScd::kVersionMajor = 1;
const TUint ProtocolScd::kVersionMinor = 0;

ProtocolScd::ProtocolScd(Environment& aEnv, Media::TrackFactory& aTrackFactory)
    : ProtocolNetwork(aEnv)
    , iLock("PSCD")
    , iScdFactory(1, // Ready
                  1, // MetadataDidl
                  1, // MetadataOh
                  2, // Format
                  1, // Audio
                  1, // MetatextDidl
                  1, // MetatextOh
                  1, // Halt
                  1, // Disconnect
                  0, // Seek - currently unsupported
                  0  // Skip - currently unsupported
                  )
    , iTrackFactory(aTrackFactory)
    , iStreamFormat(nullptr)
{
    Debug::AddLevel(Debug::kScd);
}

ProtocolScd::~ProtocolScd()
{
    if (iStreamFormat != nullptr) {
        iStreamFormat->RemoveRef();
    }
}

void ProtocolScd::Initialise(Media::MsgFactory& aMsgFactory, Media::IPipelineElementDownstream& aDownstream)
{
    iSupply.reset(new SupplyScd(aMsgFactory, aDownstream));
}

void ProtocolScd::Interrupt(TBool aInterrupt)
{
    AutoMutex _(iLock);
    if (aInterrupt) {
        iStopped = true;
    }
    iTcpClient.Interrupt(aInterrupt);
}

ProtocolStreamResult ProtocolScd::Stream(const Brx& aUri)
{
    iUri.Replace(aUri);
    if (iUri.Scheme() != Brn("scd")) {
        return EProtocolErrorNotSupported;
    }
    LOG(kMedia, "ProtocolScd::Stream(%.*s)\n", PBUF(aUri));
    {
        AutoMutex _(iLock);
        iStreamId = IPipelineIdProvider::kStreamIdInvalid;
        iNextFlushId = MsgFlush::kIdInvalid;
        iStarted = iStopped = iUnrecoverableError = iExit = false;
        iFormatReqd = true;
    }

    for (; !iExit && !iStopped;) {
        try {
            if (iUnrecoverableError) {
                return EProtocolStreamErrorUnrecoverable;
            }
            for (;;) {
                Close();
                if (Connect(iUri, 0)) { // slightly dodgy - relies on implementation ignoring iUri's scheme
                    iStarted = true;
                    break;
                }
                if (!iStarted) {
                    LOG(kMedia, "ProtocolScd - failed to connect to sender\n");
                    return EProtocolStreamErrorUnrecoverable;
                }
                Thread::Sleep(500); /* This code runs in a fairly high priority thread.
                                       Avoid it busy-looping, preventing action invocation
                                       threads from being scheduled and changing the active
                                       url/mode. */
            }
            //Log::Print("\n\n\n");
            {
                ScdMsg* ready = iScdFactory.CreateMsgReady();
                AutoScdMsg _(ready);
                ready->Externalise(iWriterBuf);
            }
            for (;;) {
                auto msg = iScdFactory.CreateMsg(iReaderBuf);
                AutoScdMsg _(msg);
                msg->Process(*this);
            }
        }
        catch (AssertionFailed&) {
            throw;
        }
        catch (Exception& ex) {
            if (!iExit) {
                LOG2(kMedia, kError, "Exception - %s - in ProtocolScd::Stream\n", ex.Message());
            }
        }
    }
    iSupply->Flush();
    {
        AutoMutex _(iLock);
        if (iStopped && iNextFlushId != MsgFlush::kIdInvalid) {
            iSupply->OutputFlush(iNextFlushId);
        }
        // clear iStreamId to prevent TrySeek or TryStop returning a valid flush id
        iStreamId = IPipelineIdProvider::kStreamIdInvalid;
        return iStopped? EProtocolStreamStopped : EProtocolStreamSuccess;
    }
}

ProtocolGetResult ProtocolScd::Get(IWriter& /*aWriter*/, const Brx& /*aUri*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return EProtocolGetErrorNotSupported;
}

TUint ProtocolScd::TryStop(TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamId != aStreamId || aStreamId == IPipelineIdProvider::kStreamIdInvalid) {
        return MsgFlush::kIdInvalid;
    }
    if (iNextFlushId == MsgFlush::kIdInvalid) {
        /* If a valid flushId is set then We've previously promised to send a Flush but haven't
        got round to it yet.  Re-use the same id for any other requests that come in before
        our main thread gets a chance to issue a Flush */
        iNextFlushId = iFlushIdProvider->NextFlushId();
    }
    iStopped = true;
    iTcpClient.Interrupt(true);
    return iNextFlushId;
}

void ProtocolScd::Process(ScdMsgReady& aMsg)
{
    //Log::Print("ScdMsgReady\n");
    const TUint major = aMsg.Major();
    if (major != kVersionMajor) {
        iUnrecoverableError = true;
        LOG(kScd, "ProtocolScd received ScdMsgReady with unsupported major version (%u)\n", major);
        THROW(ScdError);
    }
}

void ProtocolScd::Process(ScdMsgMetadataDidl& aMsg)
{
    //Log::Print("ScdMsgMetadataDidl\n");
    auto track = iTrackFactory.CreateTrack(aMsg.Uri(), aMsg.Metadata());
    OutputTrack(track);
}

void ProtocolScd::Process(ScdMsgMetadataOh& aMsg)
{
    //Log::Print("ScdMsgMetadataOh\n");
    auto track = OhMetadata::ToTrack(aMsg.Metadata(), iTrackFactory);
    OutputTrack(track);
}

void ProtocolScd::Process(ScdMsgFormat& aMsg)
{
    //Log::Print("ScdMsgFormat\n");
    if (iStreamFormat != nullptr) {
        iStreamFormat->RemoveRef();
    }
    iStreamFormat = &aMsg;
    iStreamFormat->AddRef();
    OutputStream();
    iFormatReqd = false;
}

void ProtocolScd::Process(ScdMsgAudio& aMsg)
{
    //Log::Print("ScdMsgAudio - samples = %u\n", aMsg.NumSamples());
    if (iFormatReqd) {
        OutputStream();
        iFormatReqd = false;
    }
    iSupply->OutputData(aMsg.Audio());
}

void ProtocolScd::Process(ScdMsgMetatextDidl& aMsg)
{
    //Log::Print("ScdMsgMetatextDidl\n");
    iSupply->OutputMetadata(aMsg.Metatext());
}

void ProtocolScd::Process(ScdMsgMetatextOh& aMsg)
{
    //Log::Print("ScdMsgMetatextOh\n");
    OhMetadata::ToDidlLite(aMsg.Metatext(), iMetadata);
    iSupply->OutputMetadata(iMetadata);
}

void ProtocolScd::Process(ScdMsgHalt& /*aMsg*/)
{
    //Log::Print("ScdMsgHalt\n");
    iSupply->OutputHalt();
}

void ProtocolScd::Process(ScdMsgDisconnect& /*aMsg*/)
{
    //Log::Print("ScdMsgDisconnect\n");
    iExit = true;
    THROW(ScdError); // force Stream out of its inner msg readiing loop
}

void ProtocolScd::Process(ScdMsgSeek& /*aMsg*/)
{
    ASSERTS();
}

void ProtocolScd::Process(ScdMsgSkip& /*aMsg*/)
{
    ASSERTS();
}

void ProtocolScd::OutputTrack(Track* aTrack)
{
    iSupply->OutputTrack(*aTrack);
    aTrack->RemoveRef();
    iFormatReqd = true;
}

void ProtocolScd::OutputStream()
{
    if (iStreamFormat == nullptr) {
        LOG2(kError, kMedia, "ProtocolScd received Audio but no Format\n");
        iUnrecoverableError = true;
        THROW(ScdError);
    }

    const TUint bytesPerSample =   (iStreamFormat->BitDepth() / 8)
                                 * iStreamFormat->SampleRate()
                                 * iStreamFormat->NumChannels();
    const TUint64 bytesTotal = iStreamFormat->SamplesTotal() * bytesPerSample;
    PcmStreamInfo pcmStream;
    SpeakerProfile stereo;
    pcmStream.Set(iStreamFormat->BitDepth(), iStreamFormat->SampleRate(),
                  iStreamFormat->NumChannels(), AudioDataEndian::Big,
                  stereo, iStreamFormat->SampleStart());
    pcmStream.SetCodec(iStreamFormat->CodecName(), iStreamFormat->Lossless());
    auto broadcast = iStreamFormat->BroadcastAllowed()? Multiroom::Allowed : Multiroom::Forbidden;
    {
        AutoMutex _(iLock);
        iStreamId = iIdProvider->NextStreamId();
    }
    iSupply->OutputPcmStream(Brx::Empty(), bytesTotal,
                             iStreamFormat->Seekable(), iStreamFormat->Live(),
                             broadcast, *this, iStreamId, pcmStream);
}
