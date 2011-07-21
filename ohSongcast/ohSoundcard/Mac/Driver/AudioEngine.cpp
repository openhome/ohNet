#include "AudioEngine.h"
#include <IOKit/audio/IOAudioStream.h>
#include <IOKit/IOLib.h>
#include <libkern/OSByteOrder.h>
#include <sys/kpi_socket.h>


OSDefineMetaClassAndStructors(AudioEngine, IOAudioEngine);


bool AudioEngine::init(OSDictionary* aProperties)
{
    IOLog("ohSoundcard AudioEngine[%p]::init(%p) ...\n", this, aProperties);

    uint64_t interval;
    uint64_t max32bit = (uint64_t)2 << 32;

    if (!IOAudioEngine::init(aProperties))
        goto Error;

    iTimer = 0;
    iOutputBuffer = 0;
    iOutputBufferBytes = 0;
    iCurrentBlock = 0;
    iNumBlocks = 16;
    iBlockFrames = 128;
    iSampleRate.whole = 44100;
    iSampleRate.fraction = 0;
    iCurrentFrame = 0;

    iActive = false;    
    iIpAddress = 0;
    iPort = 0;
    iTtl = 0;

    // calculate the timer interval making sure no overflows occur
    interval = 1000000000;
    interval *= iBlockFrames;
    interval /= iSampleRate.whole;
    if (interval >= max32bit)
        goto Error;
    iTimerIntervalNs = interval;
    
    IOLog("ohSoundcard AudioEngine[%p]::init(%p) ok\n", this, aProperties);
    return true;

Error:
    IOLog("ohSoundcard AudioEngine[%p]::init(%p) fail\n", this, aProperties);
    return false;
}


bool AudioEngine::initHardware(IOService* aProvider)
{
    IOLog("ohSoundcard AudioEngine[%p]::initHardware(%p) ...\n", this, aProvider);

    IOAudioStream* outStream = 0;
    IOWorkLoop* workLoop = 0;

    // initialise audio format data
    IOAudioStreamFormat format;
    format.fNumChannels = 2;
    format.fSampleFormat = kIOAudioStreamSampleFormatLinearPCM;
    format.fNumericRepresentation = kIOAudioStreamNumericRepresentationSignedInt;// float???
    format.fBitDepth = 32;
    format.fBitWidth = 32;
    format.fAlignment = kIOAudioStreamAlignmentHighByte;
    format.fByteOrder = kIOAudioStreamByteOrderBigEndian;
    format.fIsMixable = 1;
    format.fDriverTag = 0;

    // base class initialisation
    if (!IOAudioEngine::initHardware(aProvider))
        goto Error;

    setDescription("OpenHome Songcast Driver");
    setSampleRate(&iSampleRate);
    setNumSampleFramesPerBuffer(iNumBlocks * iBlockFrames);

    // create output stream
    outStream = new IOAudioStream;
    if (!outStream)
        goto Error;

    if (!outStream->initWithAudioEngine(this, kIOAudioStreamDirectionOutput, 1, "output stream"))
        goto Error;

    outStream->addAvailableFormat(&format, &iSampleRate, &iSampleRate);

    // allocate buffer
    iOutputBufferBytes = iBlockFrames * iNumBlocks * format.fNumChannels * format.fBitWidth / 8;
    iOutputBuffer = (void*)IOMalloc(iOutputBufferBytes);
    if (!iOutputBuffer)
        goto Error;
    
    if (outStream->setFormat(&format) != kIOReturnSuccess)
        goto Error;
    
    outStream->setSampleBuffer(iOutputBuffer, iOutputBufferBytes);
    if (addAudioStream(outStream) != kIOReturnSuccess)
        goto Error;

    outStream->release();

    
    // create the timer
    workLoop = getWorkLoop();
    if (!workLoop)
        goto Error;
    
    iTimer = IOTimerEventSource::timerEventSource(this, TimerFired);
    if (!iTimer)
        goto Error;
    
    if (workLoop->addEventSource(iTimer) != kIOReturnSuccess)
        goto Error;

    IOLog("ohSoundcard AudioEngine[%p]::initHardware(%p) ok\n", this, aProvider);
    return true;

Error:
    if (outStream)
        outStream->release();
    if (iOutputBuffer) {
        IOFree(iOutputBuffer, iOutputBufferBytes);
        iOutputBuffer = 0;
        iOutputBufferBytes = 0;
    }
    
    IOLog("ohSoundcard AudioEngine[%p]::initHardware(%p) fail\n", this, aProvider);
    return false;
}


void AudioEngine::free()
{
    IOLog("ohSoundcard AudioEngine[%p]::free()\n", this);
    if (iOutputBuffer) {
        IOFree(iOutputBuffer, iOutputBufferBytes);
        iOutputBuffer = 0;
        iOutputBufferBytes = 0;
    }
    IOAudioEngine::free();
}


void AudioEngine::stop(IOService* aProvider)
{
    IOLog("ohSoundcard AudioEngine[%p]::stop(%p)\n", this, aProvider);
    IOAudioEngine::stop(aProvider);
}


IOReturn AudioEngine::performAudioEngineStart()
{
    IOLog("ohSoundcard AudioEngine[%p]::performAudioEngineStart() ...\n", this);

    takeTimeStamp(false);
    iCurrentBlock = 0;
    iCurrentFrame = 0;

    if (iTimer->setTimeout(iTimerIntervalNs) != kIOReturnSuccess)
        goto Error;
    
    IOLog("ohSoundcard AudioEngine[%p]::performAudioEngineStart() ok\n", this);
    return kIOReturnSuccess;

Error:
    IOLog("ohSoundcard AudioEngine[%p]::performAudioEngineStart() fail\n", this);
    return kIOReturnSuccess;
}


IOReturn AudioEngine::performAudioEngineStop()
{
    iTimer->cancelTimeout();
    
    IOLog("ohSoundcard AudioEngine[%p]::performAudioEngineStop()\n", this);
    return kIOReturnSuccess;
}


UInt32 AudioEngine::getCurrentSampleFrame()
{
    return iCurrentBlock * iBlockFrames;
}


IOReturn AudioEngine::performFormatChange(IOAudioStream* aAudioStream, const IOAudioStreamFormat* aNewFormat, const IOAudioSampleRate* aNewSampleRate)
{
    IOLog("ohSoundcard AudioEngine[%p]::performFormatChange()\n", this);
    return kIOReturnSuccess;
}


IOReturn AudioEngine::clipOutputSamples(const void* aMixBuffer, void* aSampleBuffer, UInt32 aFirstSampleFrame, UInt32 aNumSampleFrames, const IOAudioStreamFormat* aFormat, IOAudioStream* aStream)
{
    uint32_t offset = aFirstSampleFrame * aFormat->fNumChannels * aFormat->fBitWidth / 8;
    uint32_t bytes = aNumSampleFrames * aFormat->fNumChannels * aFormat->fBitWidth / 8;
    memcpy((uint8_t*)aSampleBuffer + offset, (uint8_t*)aMixBuffer + offset, bytes);
    
    return kIOReturnSuccess;
}


struct tmpaddr
{
	__uint8_t	sa_len;		/* total length */
	sa_family_t	sa_family;	/* [XSI] address family */
    unsigned short port;
    unsigned long addr;
    char zero[8];
};


void AudioEngine::TimerFired(OSObject* aOwner, IOTimerEventSource* aSender)
{
    if (aOwner)
    {
        AudioEngine* engine = OSDynamicCast(AudioEngine, aOwner);
        if (engine)
        {
            if (engine->iActive != 0)
            {
                uint32_t offset = engine->iCurrentBlock * engine->iBlockFrames * 2 * 4;
                void* block = (uint8_t*)engine->iOutputBuffer + offset;

                uint8_t channels = 2;
                uint8_t bitDepth = 24;
                uint32_t audioBytes = engine->iBlockFrames * channels * bitDepth / 8;
                uint32_t sampleRate = 44100;
                uint16_t sampleCount = engine->iBlockFrames;
                uint32_t frame = ++engine->iCurrentFrame;

                void* data = IOMalloc(sizeof(AudioHeader) + audioBytes);
            
                AudioHeader* header = (AudioHeader*)data;

                header->iSignature[0] = 'O';
                header->iSignature[1] = 'h';
                header->iSignature[2] = 'm';
                header->iSignature[3] = ' ';
                header->iVersion = 1;
                header->iType = 3;
                header->iAudioHeaderBytes = 50;
                header->iAudioNetworkTimestamp = 0;
                header->iAudioMediaLatency = 1000000;
                header->iAudioMediaTimestamp = 0;
                header->iAudioStartSample = 0;
                header->iAudioTotalSamples = 0;
                header->iAudioVolumeOffset = 0;
                header->iAudioReserved = 0;

                // set size of header + audio data
                header->iTotalBytes = OSSwapHostToBigInt16(sizeof(AudioHeader) + audioBytes);
            
                // lossless audio
                header->iAudioFlags = 2;

                header->iAudioSampleCount = OSSwapHostToBigInt16(sampleCount);
                header->iAudioFrame = OSSwapHostToBigInt32(frame);
                header->iAudioSampleRate = OSSwapHostToBigInt32(sampleRate);
                header->iAudioBitRate = OSSwapHostToBigInt32(sampleRate * channels * bitDepth);
                header->iAudioBitDepth = bitDepth;
                header->iAudioChannels = channels;
            
                // codec information
                header->iAudioCodecNameBytes = 6;
                header->iAudioCodecName[0]= 'P';
                header->iAudioCodecName[1]= 'C';
                header->iAudioCodecName[2]= 'M';
                header->iAudioCodecName[3]= '/';
                header->iAudioCodecName[4]= 'S';
                header->iAudioCodecName[5]= 'C';
                
                // copy audio data
                void* audioData = (void*)(header + 1);

                uint8_t* src = (uint8_t*)block;
                uint8_t* dst = (uint8_t*)audioData;
                uint32_t samples = sampleCount * channels;
                while (samples > 0) {
                    dst[0] = src[3];
                    dst[1] = src[2];
                    dst[2] = src[1];
                    
                    src += 4;
                    dst += 3;
                    samples--;
                }

                // send data
                socket_t socket;
                sock_socket(PF_INET, SOCK_DGRAM, 0, NULL, NULL, &socket);

                struct tmpaddr addr;
                memset(&addr, 0, sizeof(tmpaddr));
                addr.sa_len = sizeof(tmpaddr);
                addr.sa_family = AF_INET;
                addr.port = htons((uint16_t)engine->iPort);
                addr.addr = (uint32_t)engine->iIpAddress;
//                addr.port = htons(12345);
//                addr.addr = 70 << 24 | 7 << 16 | 2 << 8 | 10;
                sock_connect(socket, (const sockaddr*)&addr, 0);

                struct iovec sockdata;
                sockdata.iov_base = data;
                sockdata.iov_len = sizeof(AudioHeader) + audioBytes;
            
                struct msghdr msg;
                msg.msg_name = 0;
                msg.msg_namelen = 0;
                msg.msg_iov = &sockdata;
                msg.msg_iovlen = 1;
                msg.msg_control = 0;
                msg.msg_controllen = 0;
                msg.msg_flags = 0;
            
                size_t bytesSent;
                sock_send(socket, &msg, 0, &bytesSent);
                sock_close(socket);
            

                IOFree(data, sizeof(AudioHeader) + audioBytes);
            }
            
            engine->iCurrentBlock++;
            if (engine->iCurrentBlock >= engine->iNumBlocks) {
                engine->iCurrentBlock = 0;
                engine->takeTimeStamp();
            }
            aSender->setTimeout(engine->iTimerIntervalNs);
        }
    }
}


void AudioEngine::SetActive(uint64_t aActive)
{
    IOLog("ohSoundcard AudioEngine[%p]::SetActive(%llu)\n", this, aActive);
    iActive = aActive;
}


void AudioEngine::SetEndpoint(uint64_t aIpAddress, uint64_t aPort)
{
    IOLog("ohSoundcard AudioEngine[%p]::SetEndpoint(%llu, %llu)\n", this, aIpAddress, aPort);
    iIpAddress = aIpAddress;
    iPort = aPort;
}


void AudioEngine::SetTtl(uint64_t aTtl)
{
    IOLog("ohSoundcard AudioEngine[%p]::SetTtl(%llu)\n", this, aTtl);
    iTtl = aTtl;
}





