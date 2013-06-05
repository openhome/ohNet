#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/RaopContainer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

// this is a fake container constructed for airplay

RaopContainer::RaopContainer(ICodecController& aController)
{
    LOG(kMedia, "Checking for Raop container\n");

    try {
        Bws<60> data;
        aController.Read(data, 4);

        LOG(kMedia, "data %x {", data[0]);
        LOG(kMedia, data);
        LOG(kMedia, "}\n");

        if(data != Brn("Raop")) {
            THROW(MediaCodecRaopNotFound);
        }

        // If RAOP is only used by alac, why bother going to extra lengths and creating a pseudo-identifier?
        //aSelector.iCodecContainer->SetName(Brn("alas"));  // this is used for codec recognition - streamed alac
        iSamplesTotal = 0;  // continual stream

        // fmtp should hold the sdp fmtp numbers from e.g. a=fmtp:96 4096 0 16 40 10 14 2 255 0 0 44100
        // extract enough info from this for codec selector, then pass the raw fmtp through for alac decoder
        // first read the number of bytes in for the fmtp
        data.SetBytes(0);
        aController.Read(data, 4);
        TUint bytes = Ascii::Uint(data);    // size of fmtp string
        data.SetBytes(0);
        aController.Read(data, bytes);     // FIXME - problem here; need to read variable amount of data (and we're not peeking)
        Parser fmtp(data);

        LOG(kMedia, "fmtp [");
        LOG(kMedia, fmtp.NextLine());
        LOG(kMedia, "]\n");
        
        fmtp.Set(data);

        try {
            fmtp.Next();            // ?
            fmtp.Next();            // max_samples_per_frame
            fmtp.Next();            // 7a
            iBitDepth = static_cast<TUint16>(Ascii::Uint(fmtp.Next()));  // bit depth
            fmtp.Next();            // rice_historymult
            fmtp.Next();            // rice_initialhistory
            fmtp.Next();            // rice_kmodifier
            iChannels = static_cast<TUint16>(Ascii::Uint(fmtp.Next()));    // 7f - I think that this is channels
            fmtp.Next();            // 80
            fmtp.Next();            // 82
            fmtp.Next();            // 86
            TUint rate = Ascii::Uint(fmtp.NextLine());
            iTimescale = rate;
            iSampleRate = rate;
        }
        catch(AsciiError) {
            THROW(MediaCodecRaopNotFound);
        }
        //fmtp.Set(data);
        //TUint bytes = fmtp.NextLine().Bytes()+1; //size of fmtp string
        data.SetBytes(bytes);
        iCodecSpecificData.Replace(data); // pass raw fmtp to alac decoder

        LOG(kMedia, "RaopContainer::RaopContainer found %d bytes\n", bytes);
    }
    catch(CodecStreamCorrupt) {
        THROW(MediaCodecRaopNotFound); // not enough data found to be Raop container
    }
}

RaopContainer::~RaopContainer()
{
}

const Brx& RaopContainer::CodecSpecificData()
{
    return iCodecSpecificData;
}

TUint32 RaopContainer::SampleRate()
{
    return iSampleRate;
}

TUint32 RaopContainer::Timescale()
{
    return iTimescale;
}

TUint16 RaopContainer::Channels()
{
    return iChannels;
}

TUint16 RaopContainer::BitDepth()
{
    return iBitDepth;
}

TUint64 RaopContainer::Duration()
{
    return iSamplesTotal;
}
