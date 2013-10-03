#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>

#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecOhm : public CodecBase, private IReader
{
public:
    CodecOhm(Av::OhmMsgFactory& aMsgFactory);
    ~CodecOhm();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType);
    TBool Recognise();
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
private: // from IReader
    Brn Read(TUint aBytes);
    Brn ReadUntil(TByte aSeparator);
    void ReadFlush();
    void ReadInterrupt();
private:
    Av::OhmMsgFactory& iMsgFactory;
    Bws<Av::OhmMsgAudioBlob::kMaxBytes> iBuf;
    TUint iOffset;
    TBool iStreamOutput;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;
using namespace OpenHome::Av;

CodecBase* CodecFactory::NewOhm()
{ // static
    // FIXME
    return NULL; // new CodecOhm();
}



CodecOhm::CodecOhm(OhmMsgFactory& aMsgFactory)
    : iMsgFactory(aMsgFactory)
{
}

CodecOhm::~CodecOhm()
{
}

TBool CodecOhm::SupportsMimeType(const Brx& /*aMimeType*/)
{
    return false;
}

TBool CodecOhm::Recognise()
{
    try {
        OhmHeader header;
        header.Internalise(*this);
        return true;
    }
    catch (OhmError&) {
    }
    return false;
}

void CodecOhm::StreamInitialise()
{
    iBuf.SetBytes(0);
    iOffset = 0;
    iStreamOutput = false;
}

void CodecOhm::Process()
{
    OhmHeader header;
    header.Internalise(*this);
    ASSERT(header.MsgType() == OhmHeader::kMsgTypeAudioBlob);
    OhmMsgAudio* msg = iMsgFactory.CreateAudioFromBlob(*this, header);

    const TUint sampleRate = msg->SampleRate();
    const TUint jiffiesPerSample = Jiffies::JiffiesPerSample(sampleRate);

    if (!iStreamOutput) {
        const TUint64 trackLengthJiffies = jiffiesPerSample * msg->SamplesTotal();
        iController->OutputDecodedStream(msg->BitRate(), msg->BitDepth(), sampleRate, msg->Channels(), msg->Codec(), trackLengthJiffies, msg->SampleStart(), msg->Lossless());
        iStreamOutput = true;
    }

    const TUint64 jiffiesStart = jiffiesPerSample * msg->SampleStart();
    iController->OutputAudioPcm(msg->Audio(), msg->Channels(), sampleRate, msg->BitDepth(), EMediaDataBigEndian, jiffiesStart);

    if (msg->Halt()) {
        iController->OutputHalt();
    }

    msg->RemoveRef();
}

TBool CodecOhm::TrySeek(TUint /*aStreamId*/, TUint64 /*aSample*/)
{
    return false;
}

Brn CodecOhm::Read(TUint aBytes)
{
    while (aBytes + iOffset > iBuf.Bytes()) {
        if (iOffset > 0) {
            Log::Print("WARNING: (CodecOhm) songcast frame has been split\n");
        }
        iBuf.Replace(iBuf.Split(iOffset));
        iOffset = 0;
        iController->ReadNextMsg(iBuf);
    }
    Brn buf(iBuf.Ptr() + iOffset, aBytes);
    iOffset += aBytes;
    if (iOffset == iBuf.Bytes()) {
        iOffset = 0;
        iBuf.SetBytes(0);
    }
    return buf;
}

Brn CodecOhm::ReadUntil(TByte /*aSeparator*/)
{
    ASSERTS(); // not implemented
    return Brn(NULL, 0);
}

void CodecOhm::ReadFlush()
{
    ASSERTS(); // not implemented
}

void CodecOhm::ReadInterrupt()
{
}
