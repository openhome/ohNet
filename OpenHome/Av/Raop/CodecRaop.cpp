#include <OpenHome/Av/Raop/CodecRaop.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Av/Raop/RaopHeader.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;
using namespace OpenHome::Av;


// CodecRaop

CodecRaop::CodecRaop() 
    : CodecAlacBase("RAOP")
{
    LOG(kCodec, "CodecRaop::CodecRaop\n");
}

CodecRaop::~CodecRaop()
{
    LOG(kCodec, "CodecRaop::~CodecRaop\n");
}

TBool CodecRaop::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    LOG(kCodec, "CodecRaop::Recognise\n");
    if (aStreamInfo.RawPcm()) {
        return false;
    }
    Bws<4> buf;
    iController->Read(buf, buf.MaxBytes());

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
    try {
        iContainer->Process();
    }
    catch (MediaMpeg4EndOfData&) {
        THROW(CodecStreamEnded);
    }
    catch (MediaMpeg4FileInvalid&) {
        THROW(CodecStreamCorrupt);
    }

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
        if (sizeof(RaopDataHeader) > binheader.Bytes()) {
            THROW(CodecStreamEnded);
        }
        Brn audio(binheader);
        RaopDataHeader header(audio);
        iController->Read(iInBuf, header.Bytes());
        if (iInBuf.Bytes() < header.Bytes()) {
            THROW(CodecStreamEnded);
        }
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
