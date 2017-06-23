#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/Scd/ScdMsg.h>

namespace OpenHome {
    class Environment;
namespace Scd {
namespace Sender {
    class IScdMsgReservoir;


class ScdSession : public SocketTcpSession
                 , private IScdMsgProcessor
{
public:
    ScdSession(IScdMsgReservoir& aReservoir, ScdMsgFactory& aFactory);
    ~ScdSession();
private: // from SocketTcpSession
    void Run() override;
private: // from IScdMsgProcessor
    void Process(ScdMsgReady& aMsg) override;
    void Process(ScdMsgMetadataDidl& aMsg) override;
    void Process(ScdMsgMetadataOh& aMsg) override;
    void Process(ScdMsgFormat& aMsg) override;
    void Process(ScdMsgAudio& aMsg) override;
    void Process(ScdMsgMetatextDidl& aMsg) override;
    void Process(ScdMsgMetatextOh& aMsg) override;
    void Process(ScdMsgHalt& aMsg) override;
    void Process(ScdMsgDisconnect& aMsg) override;
    void Process(ScdMsgSeek& aMsg) override;
    void Process(ScdMsgSkip& aMsg) override;
private:
    IScdMsgReservoir& iReservoir;
    ScdMsgFactory& iFactory;
    Srx* iReadBuf;
    Swx* iWriteBuf;
    ScdMsg* iMetadata;
    ScdMsg* iFormat;
    ScdMsg* iMetatext;
    TUint64 iSampleStart;
};

class ScdServer
{
public:
    ScdServer(Environment& aEnv, IScdMsgReservoir& aReservoir, ScdMsgFactory& aFactory);
    ~ScdServer();
    OpenHome::Endpoint Endpoint() const;
private:
    void AdapterChanged();
private:
    Environment& iEnv;
    IScdMsgReservoir& iReservoir;
    ScdMsgFactory& iFactory;
    mutable Mutex iLock;
    SocketTcpServer* iServer;
    TUint iCurrentChangeId;
    OpenHome::Endpoint iEndpoint;
};

}
}
}