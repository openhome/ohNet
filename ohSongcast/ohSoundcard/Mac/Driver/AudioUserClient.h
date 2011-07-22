#ifndef HEADER_AUDIOUSERCLIENT
#define HEADER_AUDIOUSERCLIENT


#include <IOKit/IOUserClient.h>
#include "AudioDevice.h"

#define AudioUserClient org_openhome_ohSoundcard_userclient
#define AudioUserClientName "org_openhome_ohSoundcard_userclient"


class AudioUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(AudioUserClient);

public:
    virtual bool start(IOService* aProvider);
    virtual void stop(IOService* aProvider);
    virtual IOReturn clientClose();

private:
    static const IOExternalMethodDispatch iMethods[eNumDriverMethods];

    virtual IOReturn externalMethod(uint32_t aSelector, IOExternalMethodArguments* aArgs, IOExternalMethodDispatch* aDispatch, OSObject* aTarget, void* aReference);

    static IOReturn DispatchOpen(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchClose(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchSetEnabled(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchSetActive(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchSetEndpoint(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchSetTtl(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);

    IOReturn Open();
    IOReturn Close();
    IOReturn SetEnabled(uint64_t aEnabled);
    IOReturn SetActive(uint64_t aActive);
    IOReturn SetEndpoint(uint64_t aIpAddress, uint64_t aPort);
    IOReturn SetTtl(uint64_t aTtl);

    IOReturn DeviceOk();
    IOReturn GetEngine(AudioEngine** aEngine);
    
private:
    AudioDevice* iDevice;
};


#endif // HEADER_AUDIOUSERCLIENT



