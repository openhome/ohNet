#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Codec/Id3v2.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

// CodecBase

CodecBase::~CodecBase()
{
}

void CodecBase::StreamCompleted()
{
}

CodecBase::CodecBase()
    : iController(NULL)
{
}

void CodecBase::Construct(ICodecController& aController, MsgFactory& aMsgFactory)
{
    iController = &aController;
    iMsgFactory = &aMsgFactory;
}


// CodecController

CodecController::CodecController(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IPipelineElementDownstream& aDownstreamElement)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iDownstreamElement(aDownstreamElement)
    , iActiveCodec(NULL)
    , iPendingMsg(NULL)
    , iAudioEncoded(NULL)
{
    iDecoderThread = new ThreadFunctor("CDEC", MakeFunctor(*this, &CodecController::CodecThread));
    iDecoderThread->Start();
}

CodecController::~CodecController()
{
    for (size_t i=0; i<iCodecs.size(); i++) {
        delete iCodecs[i];
    }
    delete iDecoderThread;
    if (iAudioEncoded != NULL) {
        iAudioEncoded->RemoveRef();
    }
}

void CodecController::AddCodec(CodecBase* aCodec)
{
    aCodec->Construct(*this, iMsgFactory);
    iCodecs.push_back(aCodec);
}

void CodecController::CodecThread()
{
    iStreamStarted = false;
    iQuit = false;
    while (!iQuit) {
        try {
            iQueueTrackData = false;
            iStreamEnded = false;
            iActiveCodec = NULL;

            // Find next start of stream marker, ignoring any audio or meta data we encounter
            while (!iStreamStarted && !iQuit) {
                Msg* msg = iUpstreamElement.Pull();
                msg = msg->Process(*this);
                if (msg != NULL) {
                    Queue(msg);
                }
            }
            if (iQuit) {
                break;
            }
            iQueueTrackData = true;
            iStreamStarted = iStreamEnded = false;

            // Read audio data then attempt to recognise it
            do {
                Msg* msg = iUpstreamElement.Pull();
                msg = msg->Process(*this);
                if (msg != NULL) {
                    Queue(msg);
                }
            } while (!iStreamEnded && (iAudioEncoded == NULL || iAudioEncoded->Bytes() < kMaxRecogniseBytes));
            if (iQuit) {
                break;
            }
            if (iStreamEnded) {
                if (iAudioEncoded != NULL) {
                    iAudioEncoded->RemoveRef();
                    iAudioEncoded = NULL;
                }
                continue;
            }
            /* we can only CopyTo a max of kMaxRecogniseBytes bytes.  If we have more data than this, 
                split the msg, select a codec then add the fragments back together before processing */
            MsgAudioEncoded* remaining = NULL;
            if (iAudioEncoded->Bytes() > kMaxRecogniseBytes) {
                remaining = iAudioEncoded->Split(kMaxRecogniseBytes);
            }
            iAudioEncoded->CopyTo(iReadBuf);
            Brn recogBuf(iReadBuf, kMaxRecogniseBytes);
            for (size_t i=0; i<iCodecs.size(); i++) {
                CodecBase* codec = iCodecs[i];
                if (codec->Recognise(recogBuf)) {
                    iActiveCodec = codec;
                    break;
                }
            }
            iAudioEncoded->Add(remaining);
            if (iActiveCodec == NULL) {
                // FIXME - send error indication down the pipeline?
                iAudioEncoded->RemoveRef();
                iAudioEncoded = NULL;
                continue;
            }

            // tell codec to process audio data
            // (blocks until end of stream or a flush)
            // FIXME - rework to deal with seeking
            try {
                iActiveCodec->Process();
            }
            catch (CodecStreamStart&) { }
            catch (CodecStreamEnded&) { }
            catch (CodecStreamCorrupt&) { }
            iActiveCodec->StreamCompleted();
        }
        catch (CodecStreamFlush&) {
            // FIXME
        }
    }
}

void CodecController::PullMsg()
{
    Msg* msg = iUpstreamElement.Pull();
    msg = msg->Process(*this);
    ASSERT_DEBUG(msg == NULL);
}

void CodecController::Queue(Msg* aMsg)
{
    iDownstreamElement.Push(aMsg);
}

void CodecController::Read(Bwx& aBuf, TUint aBytes)
{
    if (iStreamEnded) {
        Queue(iPendingMsg);
        iPendingMsg = NULL;
        if (iStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
    while (!iStreamEnded && (iAudioEncoded == NULL || iAudioEncoded->Bytes() < aBytes)) {
        Msg* msg = iUpstreamElement.Pull();
        msg = msg->Process(*this);
        if (msg != NULL && iStreamEnded) {
            iPendingMsg = msg;
        }
    }
    MsgAudioEncoded* remaining = NULL;
    if (iAudioEncoded->Bytes() > aBytes) {
        remaining = iAudioEncoded->Split(aBytes);
    }
    const TUint bytes = iAudioEncoded->Bytes();
    ASSERT(aBuf.Bytes() + bytes <= aBuf.MaxBytes());
    TByte* ptr = const_cast<TByte*>(aBuf.Ptr()) + aBuf.Bytes();
    iAudioEncoded->CopyTo(ptr);
    aBuf.SetBytes(aBuf.Bytes() + bytes);
    iAudioEncoded->RemoveRef();
    iAudioEncoded = remaining;
}

void CodecController::Output(MsgDecodedStream* aMsg)
{
    Queue(aMsg);
}

void CodecController::Output(MsgAudioPcm* aMsg)
{
    Queue(aMsg);
}

Msg* CodecController::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (!iQueueTrackData) {
        aMsg->RemoveRef();
    }
    else if (iAudioEncoded == NULL) {
        iAudioEncoded = aMsg;
    }
    else {
        iAudioEncoded->Add(aMsg);
    }
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // not expected at this stage of the pipeline
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this to be generated by a codec
    // FIXME - volkano has containers which also generate this
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgTrack* aMsg)
{
    iStreamStarted = iStreamEnded = true;
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgEncodedStream* aMsg)
{
    iStreamStarted = iStreamEnded = true;
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgMetaText* aMsg)
{
    if (!iQueueTrackData) {
        aMsg->RemoveRef();
    }
    else {
        Queue(aMsg);
    }
    return NULL;
}

Msg* CodecController::ProcessMsg(MsgHalt* aMsg)
{
    iStreamEnded = true;
    return aMsg;
}

Msg* CodecController::ProcessMsg(MsgFlush* aMsg)
{
    Queue(aMsg);
    THROW(CodecStreamFlush);
}

Msg* CodecController::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    iStreamEnded = true;
    return aMsg;
}
