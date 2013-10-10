#ifndef HEADER_ZONE_HANDLER
#define HEADER_ZONE_HANDLER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Media/Msg.h>

#include <vector>

namespace OpenHome {
    class Environment;
namespace Av {

class IZoneListener // receiver
{
public:
    virtual ~IZoneListener() {}
    virtual void ZoneUriChanged(const Brx& aZone, const Brx& aUri) = 0;
};

// sender interface, including
// SetId
// SetHome / SetCurrent ?  Or can this be inferred from [Start|Stop]Monitoring

// FIXME - preset handling

class ZoneHandler : public Thread
{
    static const TUint kMaxReadBytes = 1024;
    static const TUint kMaxWriteBytes = kMaxReadBytes;
    static const Brn kMulticastAddress;
    static const TUint kMulticastPort = 51972;
public:
    static const TUint kMaxZoneBytes = 256;
    static const Brn kProtocolZone;
public:
    ZoneHandler(Environment& aEnv);
    ~ZoneHandler();
    const Endpoint& MulticastEndpoint() const;
    void AddListener(IZoneListener& aListener);
    void RemoveListener(IZoneListener& aListener);
    void StartMonitoring(const Brx& aZone);
    void StopMonitoring();
private: // from Thread
    void Run();
private:
    void CurrentSubnetChanged();
    void InitialiseSockets(TIpAddress aInterface);
    void DestroySockets();
    void Skip(TUint aBytes);
private:
    Environment& iEnv;
    const Endpoint iEndpoint;
    TBool iQuit;
    Mutex iLock;
    Semaphore iSem;
    Mutex iZoneLock;
    Mutex iListenerLock;
    std::vector<IZoneListener*> iListeners;
    SocketUdpMulticast* iRxSocket;
    UdpReader iReader;
    Srs<kMaxReadBytes> iReadBuffer;
    SocketUdp iTxSocket;
    UdpWriter iWriter;
    Sws<kMaxWriteBytes> iWriteBuffer;
    Bws<kMaxZoneBytes> iRxZone;
    TUint iNacnId;
    Media::BwsTrackUri iUriBuf; // FIXME - needed?
    Media::BwsTrackMetaData iMetadataBuf; // FIXME - needed?
    Bws<kMaxZoneBytes> iZoneBuf;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_ZONE_HANDLER
