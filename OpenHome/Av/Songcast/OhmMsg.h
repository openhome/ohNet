#ifndef HEADER_OHMMSG
#define HEADER_OHMMSG

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Fifo.h>

#include "Ohm.h"

namespace OpenHome {
namespace Av {

class OhmMsgAudio;
class OhmMsgTrack;
class OhmMsgMetatext;
class OhmMsgFactory;

class IOhmMsgProcessor
{
public:
	virtual void Process(OhmMsgAudio& aMsg) = 0;
	virtual void Process(OhmMsgTrack& aMsg) = 0;
	virtual void Process(OhmMsgMetatext& aMsg) = 0;
	virtual ~IOhmMsgProcessor() {}
};

class OhmMsg
{
public:
	void AddRef();
	void RemoveRef();
	TUint ResendCount() const;
	void IncrementResendCount();
	TBool TxTimestamped() const;
	TBool RxTimestamped() const;
	TUint TxTimestamp() const;
	TUint RxTimestamp() const;
	void SetTxTimestamp(TUint aValue);
	void SetRxTimestamp(TUint aValue);
	virtual void Process(IOhmMsgProcessor& aProcessor) = 0;
	virtual void Externalise(IWriter& aWriter) = 0;

protected:
	OhmMsg(OhmMsgFactory& aFactory, TUint aMsgType);
	void Create();
	
private:
	OhmMsgFactory* iFactory;
	TUint iMsgType;
	TUint iRefCount;
	TUint iResendCount;
	TBool iTxTimestamped;
	TBool iRxTimestamped;
	TUint iTxTimestamp;
	TUint iRxTimestamp;
};

class OhmMsgAudio : public OhmMsg
{
	friend class OhmMsgFactory;

public:
	static const TUint kMaxSampleBytes = 8 * 1024;
	static const TUint kMaxCodecBytes = 256;

private:
    static const TUint kHeaderBytes = 50; // not including codec name
    static const TUint kReserved = 0;
    static const TUint kFlagHalt = 1;
    static const TUint kFlagLossless = 2;
    static const TUint kFlagTimestamped = 4;
    static const TUint kFlagResent = 8;

public:
    TBool Halt() const;
    TBool Lossless() const;
    TBool Timestamped() const;
	TBool Resent() const;
    TUint Samples() const;
    TUint Frame() const;
    TUint NetworkTimestamp() const;
    TUint MediaLatency() const;
    TUint MediaTimestamp() const;
    TUint64 SampleStart() const;
    TUint64 SamplesTotal() const;
    TUint SampleRate() const;
    TUint BitRate() const;
    TInt VolumeOffset() const;
    TUint BitDepth() const;
    TUint Channels() const;
    const Brx& Codec() const;
	const Brx& Audio() const;

	void SetResent(TBool aValue);

	virtual void Process(IOhmMsgProcessor& aProcessor);
	virtual void Externalise(IWriter& aWriter);

private:
	OhmMsgAudio(OhmMsgFactory& aFactory);
	void Create(IReader& aReader, const OhmHeader& aHeader);	
	void Create(TBool aHalt, TBool aLossless, TBool aTimestamped, TBool aResent, TUint aSamples, TUint aFrame, TUint aNetworkTimestamp, TUint aMediaLatency, TUint aMediaTimestamp, TUint64 aSampleStart, TUint64 aSamplesTotal, TUint aSampleRate, TUint aBitRate, TUint aVolumeOffset, TUint aBitDepth, TUint aChannels,  const Brx& aCodec, const Brx& aAudio);

private:
    TBool iHalt;
    TBool iLossless;
    TBool iTimestamped;
	TBool iResent;
    TUint iSamples;
    TUint iFrame;
    TUint iNetworkTimestamp;
    TUint iMediaLatency;
    TUint iMediaTimestamp;
    TUint64 iSampleStart;
    TUint64 iSamplesTotal;
    TUint iSampleRate;
    TUint iBitRate;
    TInt iVolumeOffset;
    TUint iBitDepth;
    TUint iChannels;
    Bws<kMaxCodecBytes> iCodec;
	Bws<kMaxSampleBytes> iAudio;
};

class OhmMsgTrack : public OhmMsg
{
	friend class OhmMsgFactory;

public:
	static const TUint kMaxUriBytes = 1 * 1024;
	static const TUint kMaxMetadataBytes = 4 * 1024;

private:
    static const TUint kHeaderBytes = 12;

public:
	TUint Sequence() const;
	const Brx& Uri() const;
	const Brx& Metadata() const;
	virtual void Process(IOhmMsgProcessor& aProcessor);
	virtual void Externalise(IWriter& aWriter);

private:
	OhmMsgTrack(OhmMsgFactory& aFactory);
	void Create(IReader& aReader, const OhmHeader& aHeader);	
	void Create(TUint aSequence, const Brx& aUri, const Brx& aMetadata);

private:
	TUint iSequence;
	Bws<kMaxUriBytes> iUri;
	Bws<kMaxMetadataBytes> iMetadata;
};

class OhmMsgMetatext : public OhmMsg
{
	friend class OhmMsgFactory;

public:
	static const TUint kMaxMetatextBytes = 1 * 1024;

private:
    static const TUint kHeaderBytes = 8;

public:
	TUint Sequence() const;
	const Brx& Metatext() const;
	virtual void Process(IOhmMsgProcessor& aProcessor);
	virtual void Externalise(IWriter& aWriter);

private:
	OhmMsgMetatext(OhmMsgFactory& aFactory);
	void Create(IReader& aReader, const OhmHeader& aHeader);	
	void Create(TUint aSequence, const Brx& aMetatext);

private:
	TUint iSequence;
	Bws<kMaxMetatextBytes> iMetatext;
};

class IOhmMsgFactory
{
public:
	virtual OhmMsg& Create(IReader& aReader, const OhmHeader& aHeader) = 0;
	virtual OhmMsgAudio& CreateAudio(IReader& aReader, const OhmHeader& aHeader) = 0;
	virtual OhmMsgTrack& CreateTrack(IReader& aReader, const OhmHeader& aHeader) = 0;
	virtual OhmMsgMetatext& CreateMetatext(IReader& aReader, const OhmHeader& aHeader) = 0;
	virtual OhmMsgAudio& CreateAudio(TBool aHalt, TBool aLossless, TBool aTimestamped, TBool aResent, TUint aSamples, TUint aFrame, TUint aNetworkTimestamp, TUint aMediaLatency, TUint aMediaTimestamp, TUint64 aSampleStart, TUint64 aSamplesTotal, TUint aSampleRate, TUint aBitRate, TUint aVolumeOffset, TUint aBitDepth, TUint aChannels,  const Brx& aCodec, const Brx& aAudio) = 0;
	virtual OhmMsgTrack& CreateTrack(TUint aSequence, const Brx& aUri, const Brx& aMetadata) = 0;
	virtual OhmMsgMetatext& CreateMetatext(TUint aSequence, const Brx& aMetatext) = 0;
	virtual ~IOhmMsgFactory() {}
};

class OhmMsgFactory : public IOhmMsgFactory, public IOhmMsgProcessor
{
	friend class OhmMsg;

public:
	OhmMsgFactory(TUint aAudioCount, TUint aTrackCount, TUint aMetatextCount);
	virtual OhmMsg& Create(IReader& aReader, const OhmHeader& aHeader);
	virtual OhmMsgAudio& CreateAudio(IReader& aReader, const OhmHeader& aHeader);
	virtual OhmMsgTrack& CreateTrack(IReader& aReader, const OhmHeader& aHeader);
	virtual OhmMsgMetatext& CreateMetatext(IReader& aReader, const OhmHeader& aHeader);
	virtual OhmMsgAudio& CreateAudio(TBool aHalt, TBool aLossless, TBool aTimestamped, TBool aResent, TUint aSamples, TUint aFrame, TUint aNetworkTimestamp, TUint aMediaLatency, TUint aMediaTimestamp, TUint64 aSampleStart, TUint64 aSamplesTotal, TUint aSampleRate, TUint aBitRate, TUint aVolumeOffset, TUint aBitDepth, TUint aChannels,  const Brx& aCodec, const Brx& aAudio);
	virtual OhmMsgTrack& CreateTrack(TUint aSequence, const Brx& aUri, const Brx& aMetadata);
	virtual OhmMsgMetatext& CreateMetatext(TUint aSequence, const Brx& aMetatext);
	~OhmMsgFactory();

private:
	void Lock();
	void Unlock();
	void Destroy(OhmMsg& aMsg);
	void Process(OhmMsgAudio& aMsg);
	void Process(OhmMsgTrack& aMsg);
	void Process(OhmMsgMetatext& aMsg);

private:
	Fifo<OhmMsgAudio*> iFifoAudio;
	Fifo<OhmMsgTrack*> iFifoTrack;
	Fifo<OhmMsgMetatext*> iFifoMetatext;
	Mutex iMutex;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_OHMMSG
