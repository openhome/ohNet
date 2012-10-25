#ifndef HEADER_PROCESSOR_PCM_UTILS
#define HEADER_PROCESSOR_PCM_UTILS

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

class ProcessorPcmBuf : public IPcmProcessor
{
    static const TUint kBufferGranularity = DecodedAudio::kMaxBytes;
public:
    Brn Buf() const;
    const TByte* Ptr() const;
protected:
    ProcessorPcmBuf();
    void CheckSize(TUint aAdditionalBytes);
    void ProcessFragment(const Brx& aData);
private: // from IPcmProcessor
    void BeginBlock();
    void EndBlock();
protected:
    Bwh iBuf;
};

class ProcessorPcmBufPacked : public ProcessorPcmBuf
{
public:
    ProcessorPcmBufPacked();
private: // from IPcmProcessor
    TBool ProcessFragment8(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment16(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment24(const Brx& aData, TUint aNumChannels);
    void ProcessSample8(const TByte* aSample, TUint aNumChannels);
    void ProcessSample16(const TByte* aSample, TUint aNumChannels);
    void ProcessSample24(const TByte* aSample, TUint aNumChannels);
};

class ProcessorPcmBufUnpacked : public ProcessorPcmBuf
{
public:
    ProcessorPcmBufUnpacked();
private: // from IPcmProcessor
    TBool ProcessFragment8(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment16(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment24(const Brx& aData, TUint aNumChannels);
    void ProcessSample8(const TByte* aSample, TUint aNumChannels);
    void ProcessSample16(const TByte* aSample, TUint aNumChannels);
    void ProcessSample24(const TByte* aSample, TUint aNumChannels);
};


} // namespace Media
} // namespace OpenHome

#endif // HEADER_PROCESSOR_PCM_UTILS
