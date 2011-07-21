#ifndef HEADER_AUDIOENGINE
#define HEADER_AUDIOENGINE

#include <IOKit/audio/IOAudioEngine.h>
#include <IOKit/IOTimerEventSource.h>


class AudioEngine : public IOAudioEngine
{
    OSDeclareDefaultStructors(AudioEngine);

public:
    virtual bool init(OSDictionary* aProperties);
    virtual void free();

    void SetActive(uint64_t aActive);
    void SetEndpoint(uint64_t aIpAddress, uint64_t aPort);
    void SetTtl(uint64_t aTtl);
    
private:
    virtual bool initHardware(IOService* aProvider);
    virtual void stop(IOService* aProvider);

    virtual IOReturn performAudioEngineStart();
    virtual IOReturn performAudioEngineStop();
    virtual UInt32 getCurrentSampleFrame();
    virtual IOReturn performFormatChange(IOAudioStream* aAudioStream, const IOAudioStreamFormat* aNewFormat, const IOAudioSampleRate* aNewSampleRate);
    virtual IOReturn clipOutputSamples(const void* aMixBuffer, void* aSampleBuffer, UInt32 aFirstSampleFrame, UInt32 aNumSampleFrames, const IOAudioStreamFormat* aFormat, IOAudioStream* aStream);

    static void TimerFired(OSObject* aOwner, IOTimerEventSource* aSender);
    IOTimerEventSource* iTimer;
    void* iOutputBuffer;
    UInt32 iOutputBufferBytes;
    UInt32 iCurrentBlock;
    UInt32 iNumBlocks;
    UInt32 iBlockFrames;
    IOAudioSampleRate iSampleRate;
    UInt32 iTimerIntervalNs;
    UInt32 iCurrentFrame;

    bool iActive;
    uint64_t iIpAddress;
    uint64_t iPort;
    uint64_t iTtl;
};


typedef struct AudioHeader
{
    // common header fields
    uint8_t  iSignature[4];
    uint8_t  iVersion;
    uint8_t  iType;
    uint16_t iTotalBytes;

    // audio header fields
    uint8_t  iAudioHeaderBytes;
    uint8_t  iAudioFlags;
    uint16_t iAudioSampleCount;
    uint32_t iAudioFrame;
    uint32_t iAudioNetworkTimestamp;
    uint32_t iAudioMediaLatency;
    uint32_t iAudioMediaTimestamp;
    uint64_t iAudioStartSample;
    uint64_t iAudioTotalSamples;
    uint32_t iAudioSampleRate;
    uint32_t iAudioBitRate;
    uint16_t iAudioVolumeOffset;
    uint8_t  iAudioBitDepth;
    uint8_t  iAudioChannels;
    uint8_t  iAudioReserved;
    uint8_t  iAudioCodecNameBytes;
    uint8_t  iAudioCodecName[6];
    
} AudioHeader;


#endif // HEADER_AUDIOENGINE


