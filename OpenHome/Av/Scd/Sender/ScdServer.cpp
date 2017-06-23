#include <OpenHome/Av/Scd/Sender/ScdServer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Av/Scd/Sender/ScdSupply.h>
#include <OpenHome/Av/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Scd;
using namespace OpenHome::Scd::Sender;

// ScdSession

ScdSession::ScdSession(IScdMsgReservoir& aReservoir, ScdMsgFactory& aFactory)
    : iReservoir(aReservoir)
    , iFactory(aFactory)
    , iMetadata(nullptr)
    , iFormat(nullptr)
    , iMetatext(nullptr)
{
    iReadBuf = new Srs<4096>(*this);
    iWriteBuf = new Sws<8192>(*this);
}

ScdSession::~ScdSession()
{
    if (iMetadata != nullptr) {
        iMetadata->RemoveRef();
    }
    if (iFormat != nullptr) {
        iFormat->RemoveRef();
    }
    if (iMetatext != nullptr) {
        iMetatext->RemoveRef();
    }
}

void ScdSession::Run()
{
    try {
        ScdMsg* ready = iFactory.CreateMsgReady();
        ready->Externalise(*iWriteBuf);
        ready->RemoveRef();
        if (iMetadata != nullptr) {
            iMetadata->Externalise(*iWriteBuf);
        }
        if (iFormat != nullptr) {
            iFormat->Externalise(*iWriteBuf);
        }
        if (iMetatext != nullptr) {
            iMetatext->Externalise(*iWriteBuf);
        }
        for (;;) {
            auto msg = iReservoir.Pull();
            msg->Process(*this);
            msg->Externalise(*iWriteBuf);
            msg->RemoveRef();
        }
    }
    catch (AssertionFailed&) {
        throw;
    }
    catch (Exception& ex) {
        LOG2(kError, kScd, "Exception - %s - in ScdSession::Run()\n", ex.Message());
    }
}

void ScdSession::Process(ScdMsgReady& /*aMsg*/)
{
    //Log::Print("ScdMsgReady\n");
}

void ScdSession::Process(ScdMsgMetadataDidl& aMsg)
{
    //Log::Print("ScdMsgMetadataDidl\n");
    if (iMetadata != nullptr) {
        iMetadata->RemoveRef();
    }
    iMetadata = &aMsg;
    iMetadata->AddRef();
}

void ScdSession::Process(ScdMsgMetadataOh& aMsg)
{
    //Log::Print("ScdMsgMetadataOh\n");
    if (iMetadata != nullptr) {
        iMetadata->RemoveRef();
    }
    iMetadata = &aMsg;
    iMetadata->AddRef();
}

void ScdSession::Process(ScdMsgFormat& aMsg)
{
    //Log::Print("ScdMsgFormat\n");
    if (iFormat != nullptr) {
        iFormat->RemoveRef();
    }
    iFormat = &aMsg;
    iFormat->AddRef();
    iSampleStart = aMsg.SampleStart();
}

void ScdSession::Process(ScdMsgAudio& aMsg)
{
    ASSERT(iFormat != nullptr);
    iSampleStart += aMsg.NumSamples();
    //Log::Print("ScdMsgAudio - samples=%u, total=%llu\n", aMsg.NumSamples(), iSampleStart);
    //Thread::Sleep(1000);
}

void ScdSession::Process(ScdMsgMetatextDidl& aMsg)
{
    //Log::Print("ScdMsgMetatextDidl\n");
    if (iMetatext != nullptr) {
        iMetatext->RemoveRef();
    }
    iMetatext = &aMsg;
    iMetatext->AddRef();
}

void ScdSession::Process(ScdMsgMetatextOh& aMsg)
{
    //Log::Print("ScdMsgMetatextOh\n");
    if (iMetatext != nullptr) {
        iMetatext->RemoveRef();
    }
    iMetatext = &aMsg;
    iMetatext->AddRef();
}

void ScdSession::Process(ScdMsgHalt& /*aMsg*/)
{
    //Log::Print("ScdMsgHalt\n");
}

void ScdSession::Process(ScdMsgDisconnect& /*aMsg*/)
{
    //Log::Print("ScdMsgDisconnect\n");
}

void ScdSession::Process(ScdMsgSeek& /*aMsg*/)
{
}

void ScdSession::Process(ScdMsgSkip& /*aMsg*/)
{
}


//ScdServer

ScdServer::ScdServer(Environment& aEnv, IScdMsgReservoir& aReservoir, ScdMsgFactory& aFactory)
    : iEnv(aEnv)
    , iReservoir(aReservoir)
    , iFactory(aFactory)
    , iLock("SCDS")
    , iServer(nullptr)
{
    {
        AutoMutex _(iLock);
        iCurrentChangeId = iEnv.NetworkAdapterList().AddCurrentChangeListener(MakeFunctor(*this, &ScdServer::AdapterChanged), "ScdServer");
    }
    AdapterChanged();
}

ScdServer::~ScdServer()
{
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iCurrentChangeId);
    delete iServer;
}

OpenHome::Endpoint ScdServer::Endpoint() const
{
    return iEndpoint;
}

void ScdServer::AdapterChanged()
{
    AutoMutex _(iLock);
    AutoNetworkAdapterRef ref(iEnv, "ScdServer");
    auto current = ref.Adapter();
    delete iServer;
    if (current == nullptr) {
        iServer = nullptr;
        iEndpoint = Endpoint();
    }
    else {
        auto addr = current->Address();
        iServer = new SocketTcpServer(iEnv, "ScdSender", 0, addr);
        iServer->Add("ScdSession", new ScdSession(iReservoir, iFactory));
        iEndpoint.SetAddress(addr);
        iEndpoint.SetPort(iServer->Port());
    }
}
