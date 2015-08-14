#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;

const Brn ZoneHandler::kMulticastAddress("239.255.255.250");
const Brn ZoneHandler::kProtocolZone("ohz");

ZoneHandler::ZoneHandler(Environment& aEnv, const Brx& aSenderZone)
    : Thread("ZoneHandler")
    , iEnv(aEnv)
    , iEndpoint(kMulticastPort, kMulticastAddress)
    , iSenderZone(aSenderZone)
    , iQuit(false)
    , iLockRxSocket("ZON1")
    , iSem("ZON2", 0)
    , iZoneLock("ZON3")
    , iLockListener("ZON4")
    , iLockTxSocket("ZON5")
    , iLockTxData("ZON6")
    , iRxSocket(nullptr)
    , iReadBuffer(iReader)
    , iTxSocket(aEnv)
    , iWriter(iTxSocket, iEndpoint)
    , iWriteBuffer(iWriter)
    , iSendZoneUriCount(0)
    , iPresetNumber(0)
    , iSendPresetInfoCount(0)
{
    if (Debug::TestLevel(Debug::kSongcast)) {
        Bws<256> buf("ZoneHandler.  SenderZone is ");
        buf.Append(aSenderZone);
        buf.Append("\n");
        Log::Print(buf);
    }
    iNacnId = iEnv.NetworkAdapterList().AddCurrentChangeListener(MakeFunctor(*this, &ZoneHandler::CurrentSubnetChanged), false);
    iTimerZoneUri = new Timer(aEnv, MakeFunctor(*this, &ZoneHandler::TimerZoneUriExpired), "ZoneHandlerUri");
    iTimerPresetInfo = new Timer(aEnv, MakeFunctor(*this, &ZoneHandler::TimerPresetInfoExpired), "ZoneHandlerPresetInfo");
    CurrentSubnetChanged(); // start listening on any initial subnet
    Start();
}

ZoneHandler::~ZoneHandler()
{
    ASSERT(iListeners.size() == 0);
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iNacnId);
    iQuit = true;
    if (iRxSocket != nullptr) {
        iReader.ReadInterrupt();
    }
    iSem.Signal();
    Join();
    delete iTimerZoneUri;
    delete iTimerPresetInfo;
    delete iRxSocket;
}

const Endpoint& ZoneHandler::MulticastEndpoint() const
{
    return iEndpoint;
}

void ZoneHandler::AddListener(IZoneListener& aListener)
{
    iLockListener.Wait();
    iListeners.push_back(&aListener);
    iLockListener.Signal();
}

void ZoneHandler::RemoveListener(IZoneListener& aListener)
{
    iLockListener.Wait();
    for (TUint i=0; i<iListeners.size(); i++) {
        if (iListeners[i] == &aListener) {
            iListeners.erase(iListeners.begin() + i);
            break;
        }
    }
    iLockListener.Signal();
}

void ZoneHandler::StartMonitoring(const Brx& aZone)
{
    iZoneLock.Wait();
    iRxZone.Replace(aZone);
    iZoneLock.Signal();

    AutoMutex a(iLockTxSocket);
    OhzHeaderZoneQuery headerZoneQuery(aZone);
    OhzHeader header(OhzHeader::kMsgTypeZoneQuery, headerZoneQuery.MsgBytes());
    header.Externalise(iWriteBuffer);
    headerZoneQuery.Externalise(iWriteBuffer);
    iWriteBuffer.Write(aZone);
    iWriteBuffer.WriteFlush();
}

void ZoneHandler::StopMonitoring()
{
    iZoneLock.Wait();
    iRxZone.Replace(Brx::Empty());
    iZoneLock.Signal();
}

void ZoneHandler::SetHomeSenderUri(const Brx& aUri)
{
    iLockTxData.Wait();
    iSenderUriHome.Replace(aUri);
    iLockTxData.Signal();
    SendZoneUri(3);
}

void ZoneHandler::SetCurrentSenderUri(const Brx& aUri)
{
    if (aUri.Bytes() > iSenderUriCurrent.MaxBytes()) {
        LOG2(kSongcast, kError, "ERROR: unexpectedly long currentSenderUri - ");
        LOG2(kSongcast, kError, aUri);
        LOG2(kSongcast, kError, "\n");
        return;
    }
    if (Debug::TestLevel(Debug::kSongcast)) {
        Bws<512> buf("ZoneHandler::SetCurrentSenderUri(");
        buf.Append(aUri);
        buf.Append(")\n");
        Log::Print(buf);
    }
    iLockTxData.Wait();
    iSenderUriCurrent.Replace(aUri);
    iLockTxData.Signal();
    SendZoneUri(3);
}

void ZoneHandler::ClearCurrentSenderUri()
{
    iLockTxData.Wait();
    TBool sendUpdates = false;
    if (iSenderUriCurrent.Bytes() > 0) {
        iSenderUriCurrent.Replace(Brx::Empty());
        sendUpdates = true;
    }
    iLockTxData.Signal();
    LOG(kSongcast, "ZoneHandler::ClearCurrentSenderUri - sendUpdates=%u\n", sendUpdates)
    if (sendUpdates) {
        SendZoneUri(3);
    }
}

void ZoneHandler::SetSenderMetadata(const Brx& aMetadata)
{
    iLockTxData.Wait();
    iSenderMetadataBuf.Replace(aMetadata);
    iLockTxData.Signal();
}

void ZoneHandler::SetPreset(TUint aPreset)
{
    iLockTxData.Wait();
    iPresetNumber = aPreset;
    iLockTxData.Signal();
    SendPresetInfo(3); // FIXME - do we need to advertise Preset changes? (we could just wait for a query)
}

void ZoneHandler::Run()
{
    while (!iQuit) {
        iSem.Wait();
        try {
            for (;;) {
                try {
                    OhzHeader header;
                    AutoMutex a(iLockRxSocket);
                    if (iRxSocket == nullptr) {
                        THROW(ReaderError);
                    }
                    iReadBuffer.ReadFlush();
                    header.Internalise(iReadBuffer);
                    switch (header.MsgType())
                    {
                    case OhzHeader::kMsgTypeZoneQuery:
                    {
                        OhzHeaderZoneQuery headerZoneQuery;
                        headerZoneQuery.Internalise(iReadBuffer, header);
                        Brn zone = iReadBuffer.Read(headerZoneQuery.ZoneBytes());
                        if (zone == iSenderZone) {
                            if (Debug::TestLevel(Debug::kSongcast)) {
                                Bws<256> buf("ZoneHandler::Run ZoneQuery for ");
                                buf.Append(zone);
                                buf.Append("\n");
                                Log::Print(buf);
                            }
                            SendZoneUri(1);
                        }
                    }
                        break;
                    case OhzHeader::kMsgTypeZoneUri:
                    {
                        OhzHeaderZoneUri zoneHeader;
                        zoneHeader.Internalise(iReadBuffer, header);
                        Brn zoneBuf = iReadBuffer.Read(zoneHeader.ZoneBytes());
                        iZoneLock.Wait();
                        const TBool zonesMatch = (zoneBuf == iRxZone);
                        iZoneLock.Signal();
                        Brn uriBuf = iReadBuffer.Read(zoneHeader.UriBytes());
                        if (zonesMatch) {
                            iLockListener.Wait();
                            for (TUint i=0; i<iListeners.size(); i++) {
                                iListeners[i]->ZoneUriChanged(zoneBuf, uriBuf);
                            }
                            iLockListener.Signal();
                        }
                    }
                        break;
                    case OhzHeader::kMsgTypePresetQuery:
                    {
                        LOG(kSongcast, "ZoneHandler::Run received preset query\n");
                        OhzHeaderPresetQuery headerPresetQuery;
                        headerPresetQuery.Internalise(iReadBuffer, header);
                        const TUint preset = headerPresetQuery.Preset();
                        if (preset != 0) {
                            iLockTxData.Wait();
                            const TBool matches = (preset == iPresetNumber);
                            iLockTxData.Signal();
                            if (matches) {
                                SendPresetInfo(1);
                            }
                        }
                    }
                        break;
                    case OhzHeader::kMsgTypePresetInfo:
                    {
                        LOG(kSongcast, "ZoneHandler::Run received presetinfo\n");
                        OhzHeaderPresetInfo headerPresetInfo;
                        headerPresetInfo.Internalise(iReadBuffer, header);
                        const TUint metadataBytes = headerPresetInfo.MetadataBytes();
                        if (metadataBytes > iRxPresetMetadata.MaxBytes()) {
                            LOG2(kSongcast, kError, "ERROR: metadata for preset %u is too long - %u bytes.\n", headerPresetInfo.Preset(), metadataBytes);
                            (void)iReadBuffer.Read(metadataBytes);
                        }
                        else {
                            iRxPresetMetadata.Replace(iReadBuffer.Read(metadataBytes));
                            iLockListener.Wait();
                            for (TUint i=0; i<iListeners.size(); i++) {
                                iListeners[i]->NotifyPresetInfo(headerPresetInfo.Preset(), iRxPresetMetadata);
                            }
                            iLockListener.Signal();
                        }
                    }
                        break;
                    default:
                        LOG2(kSongcast, kError, "WARNING: unexpected ohz msg type (%u) received\n", header.MsgType());
                        Skip(header.MsgBytes());
                        break;
                    }
                }
                catch (OhzError&) {
                }
            }
        }
        catch (ReaderError&) {
        }
    }
}

void ZoneHandler::CurrentSubnetChanged()
{
    if (iRxSocket != nullptr) {
        iReader.ReadInterrupt();
    }
    AutoMutex a(iLockRxSocket);
    iSem.Clear();
    DestroySockets();
    static const TChar* kNifCookie = "ZoneHandler";
    NetworkAdapter* current = iEnv.NetworkAdapterList().CurrentAdapter(kNifCookie);
    if (current != nullptr) {
        TIpAddress addr = current->Address();
        current->RemoveRef(kNifCookie);
        InitialiseSockets(addr);
    }
}

void ZoneHandler::InitialiseSockets(TIpAddress aInterface)
{
    iRxSocket = new SocketUdpMulticast(iEnv, aInterface, iEndpoint);
    iTxSocket.ReBind(0, aInterface);
    iReader.SetSocket(*iRxSocket);
    iSem.Signal();
}

void ZoneHandler::DestroySockets()
{
    iReader.ClearSocket();
    delete iRxSocket;
    iRxSocket = nullptr;
}

void ZoneHandler::SendZoneUri(TUint aCount)
{
    iLockTxData.Wait();
    iSendZoneUriCount += aCount;
    iLockTxData.Signal();
    iTimerZoneUri->FireIn(0);
}

void ZoneHandler::SendPresetInfo(TUint aCount)
{
    iLockTxData.Wait();
    iSendPresetInfoCount += aCount;
    iLockTxData.Signal();
    iTimerPresetInfo->FireIn(0);
}

void ZoneHandler::TimerZoneUriExpired()
{
    AutoMutex a(iLockTxData);
    try
    {
        Brn senderUri(iSenderUriCurrent.Bytes() > 0? iSenderUriCurrent : iSenderUriHome);
        AutoMutex b(iLockTxSocket);
        OhzHeaderZoneUri headerZoneUri(iSenderZone, senderUri);
        OhzHeader header(OhzHeader::kMsgTypeZoneUri, headerZoneUri.MsgBytes());
        header.Externalise(iWriteBuffer);
        headerZoneUri.Externalise(iWriteBuffer);
        iWriteBuffer.Write(iSenderZone);
        iWriteBuffer.Write(senderUri);
        LOG(kSongcast, "ZoneHandler::TimerZoneUriExpired %d\n", iSendZoneUriCount);
        if (Debug::TestLevel(Debug::kSongcast)) {
            Bws<400> buf("ZoneHandler::TimerZoneUriExpired count=");
            buf.AppendPrintf("%u, uri=", iSendZoneUriCount);
            buf.Append(senderUri);
            buf.Append("\n");
            Log::Print(buf);
        }
        iWriteBuffer.WriteFlush();
        
        iSendZoneUriCount--;
    }
    catch (OhzError&) {
        LOG2(kSongcast, kError, "ZoneHandler::TimerZoneUriExpired OhzError\n");
    }
    catch (WriterError&) {
        LOG2(kSongcast, kError, "ZoneHandler::TimerZoneUriExpired WriterError\n");
    }

    if (iSendZoneUriCount > 0) {
        iTimerZoneUri->FireIn(kTimerZoneUriDelayMs);
    }
}

void ZoneHandler::TimerPresetInfoExpired()
{
    AutoMutex a(iLockTxData);
    try
    {
        AutoMutex b(iLockTxSocket);
        OhzHeaderPresetInfo headerPresetInfo(iPresetNumber, iSenderMetadataBuf);
        OhzHeader header(OhzHeader::kMsgTypePresetInfo, headerPresetInfo.MsgBytes());
        header.Externalise(iWriteBuffer);
        headerPresetInfo.Externalise(iWriteBuffer);
        iWriteBuffer.Write(iSenderMetadataBuf);
        iWriteBuffer.WriteFlush();

        iSendPresetInfoCount--;
    }
    catch (OhzError&) {
        LOG2(kSongcast, kError, "ZoneHandler::TimerPresetInfoExpired OhzError\n");
    }
    catch (WriterError&) {
        LOG2(kSongcast, kError, "ZoneHandler::TimerPresetInfoExpired WriterError\n");
    }

    if (iSendPresetInfoCount > 0) {
        iTimerPresetInfo->FireIn(kTimerPresetInfoDelayMs);
    }
}

void ZoneHandler::Skip(TUint aBytes)
{
    while (aBytes > 0) {
        const TUint bytes = (aBytes>kMaxReadBytes? kMaxReadBytes : aBytes);
        (void)iReadBuffer.Read(bytes);
        aBytes -= bytes;
    }
}
