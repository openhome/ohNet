#include <OpenHome/Media/Codec/RaopContainer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Av/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

// this is a fake container constructed for airplay

RaopContainer::RaopContainer(Selector& aSelector)
{
	LOG(kMedia, "Checking for Raop container\n");

    try {
		Bws<60> data;
		aSelector.Peek(data, 0, 4);

		LOG(kMedia, "data %x {", data[0]);
		LOG(kMedia, data);
		LOG(kMedia, "}\n");

		if(data != Brn("Raop")) {
			THROW(MediaCodecRaopNotFound);
		}

		iContainerSize = 4;

		aSelector.iCodecContainer->SetName(Brn("alas"));  // this is used for codec recognition - streamed alac
		aSelector.iCodecContainer->SetDuration(0); 		  // continual stream

		// fmtp should hold the sdp fmtp numbers from e.g. a=fmtp:96 4096 0 16 40 10 14 2 255 0 0 44100
		// extract enough info from this for codec selector, then pass the raw fmtp through for alac decoder
		aSelector.Peek(data, 4, 60);
		Parser fmtp(data);

		LOG(kMedia, "fmtp [");
        LOG(kMedia, fmtp.NextLine());
        LOG(kMedia, "]\n");
        
        fmtp.Set(data);

		try {
			fmtp.Next();			// ?
			fmtp.Next();			// max_samples_per_frame
			fmtp.Next();			// 7a
			aSelector.iCodecContainer->SetBitDepth(Uint(fmtp.Next()));	// bit depth
			fmtp.Next();			// rice_historymult
			fmtp.Next();			// rice_initialhistory
			fmtp.Next();			// rice_kmodifier
			aSelector.iCodecContainer->SetChannels(Uint(fmtp.Next()));    // 7f - I think that this is channels
			fmtp.Next();			// 80
			fmtp.Next();			// 82
			fmtp.Next();			// 86
			TUint rate = Uint(fmtp.NextLine());
			aSelector.iCodecContainer->SetTimescale(rate);
			aSelector.iCodecContainer->SetSampleRate(rate);
		}
		catch(AsciiError) {
			THROW(MediaCodecRaopNotFound);
		}
		fmtp.Set(data);
		TUint bytes = fmtp.NextLine().Bytes()+1; //size of fmtp string
		data.SetBytes(bytes);
		aSelector.iCodecContainer->SetCodecSpecificData(data); // pass raw fmtp to alac decoder

		iContainerSize += bytes;

		LOG(kMedia, "Selector::DoRecognise, Raop found %d bytes\n", bytes);
    }
    catch(MediaCodecStreamCorrupt) {
    	THROW(MediaCodecRaopNotFound); // not enough data found to be Raop container
    }
}

TUint32 RaopContainer::ContainerSize() const
{
    return iContainerSize;
}
