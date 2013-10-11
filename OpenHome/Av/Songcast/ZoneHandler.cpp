#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Env.h>
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

ZoneHandler::ZoneHandler(Environment& aEnv)
    : Thread("ZONH")
    , iEnv(aEnv)
    , iEndpoint(kMulticastPort, kMulticastAddress)
    , iQuit(false)
    , iLock("ZON1")
    , iSem("ZON2", 0)
    , iZoneLock("ZON3")
    , iListenerLock("ZON4")
    , iRxSocket(NULL)
    , iReadBuffer(iReader)
    , iTxSocket(aEnv)
    , iWriter(iTxSocket, iEndpoint)
    , iWriteBuffer(iWriter)
{
    iNacnId = iEnv.NetworkAdapterList().AddCurrentChangeListener(MakeFunctor(*this, &ZoneHandler::CurrentSubnetChanged));
    CurrentSubnetChanged(); // start listening on any initial subnet
    Start();
}

ZoneHandler::~ZoneHandler()
{
    ASSERT(iListeners.size() == 0);
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iNacnId);
    iQuit = true;
    if (iRxSocket != NULL) {
        iReader.ReadInterrupt();
    }
    else {
        iSem.Signal();
    }
    Join();
    delete iRxSocket;
}

const Endpoint& ZoneHandler::MulticastEndpoint() const
{
    return iEndpoint;
}

void ZoneHandler::AddListener(IZoneListener& aListener)
{
    iListenerLock.Wait();
    iListeners.push_back(&aListener);
    iListenerLock.Signal();
}

void ZoneHandler::RemoveListener(IZoneListener& aListener)
{
    iListenerLock.Wait();
    for (TUint i=0; i<iListeners.size(); i++) {
        if (iListeners[i] == &aListener) {
            iListeners.erase(iListeners.begin() + i);
            break;
        }
    }
    iListenerLock.Signal();
}

void ZoneHandler::StartMonitoring(const Brx& aZone)
{
    iZoneLock.Wait();
    iRxZone.Replace(aZone);
    iZoneLock.Signal();
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

void ZoneHandler::Run()
{
    while (!iQuit) {
        iSem.Wait();
        try {
            for (;;) {
                try {
                    OhzHeader header;
                    AutoMutex a(iLock);
                    if (iRxSocket == NULL) {
                        THROW(ReaderError);
                    }
                    header.Internalise(iReadBuffer);
                    switch (header.MsgType())
                    {
                    case OhzHeader::kMsgTypeZoneQuery:
                        // FIXME - not yet supported
                        Log::Print("WARNING: ZoneQuery msg received and ignored\n");
                        Skip(header.MsgBytes());
                        break;
                    case OhzHeader::kMsgTypeZoneUri:
                    {
                        OhzHeaderZoneUri zoneHeader;
                        zoneHeader.Internalise(iReadBuffer, header);
                        iZoneBuf.ReplaceThrow(iReadBuffer.Read(zoneHeader.ZoneBytes()));
                        iZoneLock.Wait();
                        const TBool zonesMatch = (iZoneBuf == iRxZone);
                        iZoneLock.Signal();
                        Brn uriBuf = iReadBuffer.Read(zoneHeader.UriBytes());
                        if (zonesMatch) {
                            iUriBuf.ReplaceThrow(uriBuf);
                            iListenerLock.Wait();
                            for (TUint i=0; i<iListeners.size(); i++) {
                                iListeners[i]->ZoneUriChanged(iZoneBuf, iUriBuf);
                            }
                            iListenerLock.Signal();
                        }
                    }
                        break;
                    case OhzHeader::kMsgTypePresetQuery:
                        // FIXME - not yet supported
                        Log::Print("WARNING: PresetQuery msg received and ignored\n");
                        Skip(header.MsgBytes());
                        break;
                    case OhzHeader::kMsgTypePresetInfo:
                        // FIXME - not yet supported
                        Log::Print("WARNING: PresetInfo msg received and ignored\n");
                        Skip(header.MsgBytes());
                        break;
                    default:
                        LOG2(kSongcast, kError, "WARNING: unexpected ohz msg type (%u) received\n", header.MsgType());
                        Skip(header.MsgBytes());
                        break;
                    }
                }
                catch (OhzError&) {
                    // FIXME - no code to sync onto next msg (the "ohz " header) in the (unlikely) case we receive an invalid/incomplete msg
                    LOG2(kSongcast, kError, "WARNING: OhzError caught in ZoneHandler::Run. "
                                            "We should have written code to resync to the next valid msg...\n");
                }
            }
        }
        catch (ReaderError&) {
        }
    }
}

void ZoneHandler::CurrentSubnetChanged()
{
    if (iRxSocket != NULL) {
        iReader.ReadInterrupt();
    }
    AutoMutex a(iLock);
    iSem.Clear();
    DestroySockets();
    static const TChar* kNifCookie = "ZoneHandler";
    NetworkAdapter* current = iEnv.NetworkAdapterList().CurrentAdapter(kNifCookie);
    if (current != NULL) {
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
    iRxSocket = NULL;
}

void ZoneHandler::Skip(TUint aBytes)
{
    while (aBytes > 0) {
        const TUint bytes = (aBytes>kMaxReadBytes? kMaxReadBytes : aBytes);
        (void)iReadBuffer.Read(bytes);
        aBytes -= bytes;
    }
}
