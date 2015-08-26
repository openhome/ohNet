#ifndef HEADER_ZONE_HANDLER
#define HEADER_ZONE_HANDLER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Media/Pipeline/Msg.h>

#include <vector>

namespace OpenHome {
    class Environment;
    class Timer;
namespace Av {

class IZoneListener // receiver
{
public:
    virtual ~IZoneListener() {}
    virtual void ZoneUriChanged(const Brx& aZone, const Brx& aUri) = 0;
    virtual void NotifyPresetInfo(TUint aPreset, const Brx& aMetadata) = 0;
};

class ZoneHandler : public Thread
{
    static const TUint kMaxMetadataBytes = 1000;
    static const TUint kMaxReadBytes = 1024;
    static const TUint kMaxWriteBytes = kMaxReadBytes;
    static const Brn kMulticastAddress;
    static const TUint kMulticastPort = 51972;
    static const TUint kTimerZoneUriDelayMs = 100;
    static const TUint kTimerPresetInfoDelayMs = 100;
public:
    static const TUint kMaxZoneBytes = 256;
    static const Brn kProtocolZone;
public:
    ZoneHandler(Environment& aEnv, const Brx& aSenderZone);
    ~ZoneHandler();
    const Endpoint& MulticastEndpoint() const;
    void AddListener(IZoneListener& aListener);
    void RemoveListener(IZoneListener& aListener);
    void StartMonitoring(const Brx& aZone);
    void StopMonitoring();
    void SetHomeSenderUri(const Brx& aUri);
    void SetCurrentSenderUri(const Brx& aUri);
    void ClearCurrentSenderUri();
    void SetSenderMetadata(const Brx& aMetadata);
    void SetPreset(TUint aPreset);
private: // from Thread
    void Run() override;
private:
    void CurrentSubnetChanged();
    void InitialiseSockets(TIpAddress aInterface);
    void DestroySockets();
    void SendZoneUri(TUint aCount);
    void SendPresetInfo(TUint aCount);
    void TimerZoneUriExpired();
    void TimerPresetInfoExpired();
    void Skip(TUint aBytes);
private:
    Environment& iEnv;
    const Endpoint iEndpoint;
    const Bws<kMaxZoneBytes> iSenderZone;
    TBool iQuit;
    Mutex iLockRxSocket;
    Semaphore iSem;
    Mutex iZoneLock; // FIXME - rename
    Mutex iLockListener;
    Mutex iLockTxSocket;
    Mutex iLockTxData;
    std::vector<IZoneListener*> iListeners;
    SocketUdpMulticast* iRxSocket;
    UdpReader iReader;
    Srs<kMaxReadBytes> iReadBuffer;
    SocketUdp iTxSocket;
    UdpWriter iWriter;
    Sws<kMaxWriteBytes> iWriteBuffer;
    Bws<kMaxZoneBytes> iRxZone;
    TUint iNacnId;
    Bws<32> iSenderUriHome; // ohm or ohu uri returned from ZoneQuery requests
    Bws<32> iSenderUriCurrent; // only set if we're listening to another sender.  Over-rides iSenderUriHome
    TUint iSendZoneUriCount;
    TUint iPresetNumber;
    Bws<kMaxMetadataBytes> iSenderMetadataBuf; // only used locally but too large to put on the stack
    Bws<kMaxMetadataBytes> iRxPresetMetadata; // only used locally but too large to put on the stack
    TUint iSendPresetInfoCount;
    Timer* iTimerZoneUri;
    Timer* iTimerPresetInfo;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_ZONE_HANDLER
