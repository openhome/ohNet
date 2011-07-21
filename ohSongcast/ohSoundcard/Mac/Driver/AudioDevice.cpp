#include "AudioDevice.h"
#include "AudioEngine.h"
#include <IOKit/IOLib.h>


OSDefineMetaClassAndStructors(AudioDevice, IOAudioDevice);


bool AudioDevice::initHardware(IOService* aProvider)
{
    IOLog("ohSoundcard AudioDevice[%p]::initHardware(%p) ...\n", this, aProvider);

    IOAudioEngine* engine = 0;

    // initialise base class
    if (!IOAudioDevice::initHardware(aProvider))
        goto Error;

    // set device names
    setDeviceName("OpenHome Songcast Device");
    setDeviceShortName("ohSongcastDevice");
    setManufacturerName("OpenHome.org");

    // create, initialise and activate the audio engine
    engine = new AudioEngine();
    if (!engine)
        goto Error;

    if (!engine->init(0))
        goto Error;

    if (activateAudioEngine(engine) != kIOReturnSuccess)
        goto Error;
    
    // the engine must be released as it is retained when passed to activateAudioEngine
    engine->release();

    IOLog("ohSoundcard AudioDevice[%p]::initHardware(%p) ok\n", this, aProvider);
    return true;

Error:
    if (engine)
        engine->release();

    IOLog("ohSoundcard AudioDevice[%p]::initHardware(%p) fail\n", this, aProvider);
    return false;
}



