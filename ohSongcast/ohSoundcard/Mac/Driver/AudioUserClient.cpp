#include "AudioUserClient.h"
#include <IOKit/IOLib.h>


OSDefineMetaClassAndStructors(AudioUserClient, IOUserClient);


const IOExternalMethodDispatch AudioUserClient::iMethods[eNumDriverMethods] =
{
    // eOpen
    {
        (IOExternalMethodAction)&AudioUserClient::DispatchOpen, 0, 0, 0, 0
    },
    // eClose
    {
        (IOExternalMethodAction)&AudioUserClient::DispatchClose, 0, 0, 0, 0
    },
    // eSetEnabled
    {
        (IOExternalMethodAction)&AudioUserClient::DispatchSetEnabled, 1, 0, 0, 0
    },
    // eSetActive
    {
        (IOExternalMethodAction)&AudioUserClient::DispatchSetActive, 1, 0, 0, 0
    },
    // eSetEndpoint
    {
        (IOExternalMethodAction)&AudioUserClient::DispatchSetEndpoint, 2, 0, 0, 0
    },
    // eSetTtl
    {
        (IOExternalMethodAction)&AudioUserClient::DispatchSetTtl, 1, 0, 0, 0
    }
};


IOReturn AudioUserClient::externalMethod(uint32_t aSelector, IOExternalMethodArguments* aArgs, IOExternalMethodDispatch* aDispatch, OSObject* aTarget, void* aReference)
{
    if (aSelector < eNumDriverMethods)
    {
        aDispatch = (IOExternalMethodDispatch*)&iMethods[aSelector];
        if (!aTarget) {
            aTarget = this;
        }
    }

    return IOUserClient::externalMethod(aSelector, aArgs, aDispatch, aTarget, aReference);
}


bool AudioUserClient::start(IOService* aProvider)
{
    IOLog("ohSoundcard AudioUserClient[%p]::start(%p) ...\n", this, aProvider);

    // set the device that this user client is to talk to
    iDevice = OSDynamicCast(AudioDevice, aProvider);
    if (!iDevice)
        goto Error;

    if (!IOUserClient::start(aProvider))
        goto Error;

    IOLog("ohSoundcard AudioUserClient[%p]::start(%p) ok\n", this, aProvider);
    return true;

Error:
    IOLog("ohSoundcard AudioUserClient[%p]::start(%p) fail\n", this, aProvider);
    return false;    
}


void AudioUserClient::stop(IOService* aProvider)
{
    IOLog("ohSoundcard AudioUserClient[%p]::stop(%p)\n", this, aProvider);
    IOUserClient::stop(aProvider);
}


IOReturn AudioUserClient::clientClose()
{
    IOLog("ohSoundcard AudioUserClient[%p]::clientClose()\n", this);

    // user has called IOServiceClose - make sure the close has been called
    Close();

    // terminate the user client - don't call the base class clientClose()
    terminate();

    return kIOReturnSuccess;
}


IOReturn AudioUserClient::DeviceOk()
{
    if (iDevice == 0 || isInactive()) {
        return kIOReturnNotAttached;
    }
    else if (!iDevice->isOpen(this)) {
        return kIOReturnNotOpen;
    }
    else {
        return kIOReturnSuccess;
    }
}


IOReturn AudioUserClient::GetEngine(AudioEngine** aEngine)
{
    if (iDevice == 0 || isInactive()) {
        return kIOReturnNotAttached;
    }
    else if (!iDevice->isOpen(this)) {
        return kIOReturnNotOpen;
    }

    *aEngine = iDevice->Engine();

    return (*aEngine != 0) ? kIOReturnSuccess : kIOReturnError;
}


// eOpen

IOReturn AudioUserClient::DispatchOpen(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs)
{
    return aTarget->Open();
}

IOReturn AudioUserClient::Open()
{
    if (iDevice == 0 || isInactive()) {
        IOLog("ohSoundcard AudioUserClient[%p]::Open() not attached\n", this);
        return kIOReturnNotAttached;
    }
    else if (!iDevice->open(this)) {
        IOLog("ohSoundcard AudioUserClient[%p]::Open() exclusive access\n", this);
        return kIOReturnExclusiveAccess;
    }

    IOLog("ohSoundcard AudioUserClient[%p]::Open() ok\n", this);
    return kIOReturnSuccess;
}


// eClose

IOReturn AudioUserClient::DispatchClose(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs)
{
    return aTarget->Close();
}

IOReturn AudioUserClient::Close()
{
    IOReturn ret = DeviceOk();
    if (ret != kIOReturnSuccess) {
        IOLog("ohSoundcard AudioUserClient[%p]::Close() returns %x\n", this, ret);
        return ret;
    }

    iDevice->close(this);
    IOLog("ohSoundcard AudioUserClient[%p]::Close() ok\n", this);
    return kIOReturnSuccess;
}


// eSetEnabled

IOReturn AudioUserClient::DispatchSetEnabled(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs)
{
    return aTarget->SetEnabled(aArgs->scalarInput[0]);
}

IOReturn AudioUserClient::SetEnabled(uint64_t aEnabled)
{
    IOReturn ret = DeviceOk();
    if (ret != kIOReturnSuccess) {
        IOLog("ohSoundcard AudioUserClient[%p]::SetEnabled(%llu) returns %x\n", this, aEnabled, ret);
        return ret;
    }

    IOLog("ohSoundcard AudioUserClient[%p]::SetEnabled(%llu)\n", this, aEnabled);
    return kIOReturnSuccess;
}


// eSetActive

IOReturn AudioUserClient::DispatchSetActive(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs)
{
    return aTarget->SetActive(aArgs->scalarInput[0]);
}

IOReturn AudioUserClient::SetActive(uint64_t aActive)
{
    AudioEngine* engine = 0;
    IOReturn ret = GetEngine(&engine);
    if (engine) {
        engine->SetActive(aActive);
    }
    else {
        IOLog("ohSoundcard AudioUserClient[%p]::SetActive(%llu) returns %x\n", this, aActive, ret);
    }
    return ret;
}


// eSetEndpoint

IOReturn AudioUserClient::DispatchSetEndpoint(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs)
{
    return aTarget->SetEndpoint(aArgs->scalarInput[0], aArgs->scalarInput[1]);
}

IOReturn AudioUserClient::SetEndpoint(uint64_t aIpAddress, uint64_t aPort)
{
    AudioEngine* engine = 0;
    IOReturn ret = GetEngine(&engine);
    if (engine) {
        engine->SetEndpoint(aIpAddress, aPort);
    }
    else {
        IOLog("ohSoundcard AudioUserClient[%p]::SetEndpoint(%llu, %llu) returns %x\n", this, aIpAddress, aPort, ret);
    }
    return ret;
}


// eSetTtl

IOReturn AudioUserClient::DispatchSetTtl(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs)
{
    return aTarget->SetTtl(aArgs->scalarInput[0]);
}

IOReturn AudioUserClient::SetTtl(uint64_t aTtl)
{
    AudioEngine* engine = 0;
    IOReturn ret = GetEngine(&engine);
    if (engine) {
        engine->SetTtl(aTtl);
    }
    else {
        IOLog("ohSoundcard AudioUserClient[%p]::SetTtl(%llu) returns %x\n", this, aTtl, ret);
    }
    return ret;
}



