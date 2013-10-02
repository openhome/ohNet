#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/RaopHeader.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecRaop : public CodecAlacBase
{
public:
    CodecRaop();
    ~CodecRaop();
private: // from CodecBase
    TBool Recognise();
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewRaop()
{ // static
    return new CodecRaop();
}


// CodecRaop

CodecRaop::CodecRaop() 
{
    LOG(kCodec, "CodecRaop::CodecRaop\n");
}

CodecRaop::~CodecRaop()
{
    LOG(kCodec, "CodecRaop::~CodecRaop\n");
}

TBool CodecRaop::Recognise()
{
    LOG(kCodec, "CodecRaop::Recognise\n");
    Bws<4> buf;
    iController->Read(buf, buf.Bytes());

    if (buf == Brn("Raop")) {
        LOG(kCodec, "CodecRaop::Recognise airplay\n");
        return true;
    }

    return false;
}

void CodecRaop::StreamInitialise()
{
    LOG(kCodec, "CodecRaop::StreamInitialise\n");

    iContainer = new Mpeg4MediaInfoBase(*iController);
    CodecAlacBase::Initialise();
}

TBool CodecRaop::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecRaop::TrySeek(%u, %llu)\n", aStreamId, aSample);
    return false;
}

void CodecRaop::StreamCompleted()
{
    LOG(kCodec, "CodecRaop::StreamCompleted\n");
    CodecAlacBase::StreamCompleted();
}

void CodecRaop::Process() 
{
    //LOG(kCodec, "CodecRaop::Process\n");

    iInBuf.SetBytes(0);

    try {
        // read in a packet worth of raop data
        Bws<sizeof(RaopDataHeader)> binheader;
        iController->Read(binheader, sizeof(RaopDataHeader));   // extract header
        Brn audio(binheader);
        RaopDataHeader header(audio);
        iController->Read(iInBuf, header.Bytes());
        Decode();
    }
    catch (CodecStreamStart&) {
        iStreamStarted = true;
        LOG(kCodec, "CodecRaop::Process caught CodecStreamStart\n");
    }
    catch (CodecStreamEnded&) {
        iStreamEnded = true;
        LOG(kCodec, "CodecRaop::Process caught CodecStreamEnded\n");
    }

    OutputFinal();
}
