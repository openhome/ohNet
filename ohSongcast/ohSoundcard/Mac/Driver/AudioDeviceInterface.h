#ifndef HEADER_AUDIODEVICEINTERFACE
#define HEADER_AUDIODEVICEINTERFACE


#define AudioDevice org_openhome_ohSoundcard
#define AudioDeviceName "org_openhome_ohSoundcard"


enum EDriverMethod
{
    eOpen,              // ()
    eClose,             // ()
    eSetEnabled,        // (uint64_t aEnabled)
    eSetActive,         // (uint64_t aActive)
    eSetEndpoint,       // (uint64_t aIpAddress, uint64_t aPort)
    eSetTtl,            // (uint64_t aTtl)
    eNumDriverMethods
};


#endif // HEADER_AUDIODEVICEINTERFACE



