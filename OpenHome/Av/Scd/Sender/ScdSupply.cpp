#include <OpenHome/Av/Scd/Sender/ScdSupply.h>
#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>

#include <algorithm>
#include <string>

using namespace OpenHome;
using namespace OpenHome::Scd;
using namespace OpenHome::Scd::Sender;

// ScdSupply

const TUint ScdSupply::kMaxAudioDurationMs = 5;

ScdSupply::ScdSupply(ScdMsgFactory& aFactory)
    : iFactory(aFactory)
{
}

void ScdSupply::OutputMetadataDidl(const std::string& aUri, const std::string& aMetadata)
{
    auto msg = iFactory.CreateMsgMetadataDidl(aUri, aMetadata);
    iQueue.Enqueue(msg);
}

void ScdSupply::OutputMetadataOh(const OpenHomeMetadata& aMetadata)
{
    auto msg = iFactory.CreateMsgMetadataOh(aMetadata);
    iQueue.Enqueue(msg);
}

void ScdSupply::OutputFormat(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels,
                             TUint aBitRate, TUint64 aSampleStart, TUint64 aSamplesTotal,
                             TBool aSeekable, TBool iLossless, TBool aLive,
                             TBool aBroadcastAllowed, const std::string& aCodecName)
{
    auto msg = iFactory.CreateMsgFormat(aBitDepth, aSampleRate, aNumChannels,
                                        aBitRate, aSampleStart, aSamplesTotal,
                                        aSeekable, iLossless, aLive,
                                        aBroadcastAllowed, aCodecName);
    iQueue.Enqueue(msg);
    
    iSampleRate = aSampleRate;
    iBytesPerSample = (aBitDepth/8) * aNumChannels;
    iBytesPerAudioMsg = (iBytesPerSample * iSampleRate * kMaxAudioDurationMs) / 1000;
}

void ScdSupply::OutputAudio(const TByte* aData, TUint aBytes)
{
    TUint space = iBytesPerAudioMsg - iAudio.size();
    if (aBytes <= space) {
        iAudio.append(reinterpret_cast<const char*>(aData), aBytes);
        if (iBytesPerAudioMsg == iAudio.size()) {
            OutputAudio();
        }
    }
    else {
        TUint max = space;
        do {
            const TUint bytes = std::min(max, aBytes);
            iAudio.append(reinterpret_cast<const char*>(aData), bytes);
            aData += bytes;
            aBytes -= bytes;
            max = iBytesPerAudioMsg;
            if (iAudio.size() == iBytesPerAudioMsg) {
                OutputAudio();
            }
        } while (aBytes > 0);
    }
}

void ScdSupply::OutputMetatextDidl(const std::string& aMetatext)
{
    auto msg = iFactory.CreateMsgMetatextDidl(aMetatext);
    iQueue.Enqueue(msg);
}

void ScdSupply::OutputMetatextOh(const OpenHomeMetadata& aMetatext)
{
    auto msg = iFactory.CreateMsgMetatextOh(aMetatext);
    iQueue.Enqueue(msg);
}

void ScdSupply::OutputHalt()
{
    auto msg = iFactory.CreateMsgHalt();
    iQueue.Enqueue(msg);
}

void ScdSupply::OutputPendingSamples()
{
    const TUint excess = iAudio.size() % iBytesPerSample;
    if (excess > 0) {
        iAudio.erase(iAudio.size() - excess + 1, excess);
    }
    if (iAudio.size() > 0) {
        OutputAudio();
    }
}

void ScdSupply::OutputAudio()
{
    ASSERT(iAudio.size() > 0);
    ASSERT(iAudio.size() % iBytesPerSample == 0);
    const TUint numSamples = iAudio.size() / iBytesPerSample;
    auto msg = iFactory.CreateMsgAudio(iAudio, numSamples);
    iQueue.Enqueue(msg);
    iAudio.clear();
}

ScdMsg* ScdSupply::Pull()
{
    return iQueue.Dequeue();
}
