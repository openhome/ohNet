#ifndef HEADER_AUDIODEVICE
#define HEADER_AUDIODEVICE

#include <IOKit/audio/IOAudioDevice.h>
#include "AudioDeviceInterface.h"
#include "AudioEngine.h"


// sleep/wake handling


class AudioDevice : public IOAudioDevice
{
    OSDeclareDefaultStructors(AudioDevice);

    virtual bool initHardware(IOService* aProvider);

public:
    AudioEngine* Engine()
    {
        if (audioEngines->getCount() != 0) {
            return OSDynamicCast(AudioEngine, audioEngines->getObject(0));
        }
        else {
            return 0;
        }
    }
};


#endif // HEADER_AUDIODEVICE



