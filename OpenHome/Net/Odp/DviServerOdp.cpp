#include <OpenHome/Net/Odp/DviServerOdp.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Private/DviServer.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Odp/DviOdp.h>
#include <OpenHome/Net/Odp/Odp.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Debug-ohMediaPlayer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DviSessionOdp

const Brn DviSessionOdp::kUserAgentDefault("Odp");

DviSessionOdp::DviSessionOdp(DvStack& aDvStack, TIpAddress aAdapter)
    : iAdapter(aAdapter)
    , iWriteLock("Odp1")
    , iShutdownSem("Odp2", 1)
{
    iReadBuffer = new Srs<1024>(*this);
    iReaderUntil = new ReaderUntilS<kMaxReadBytes>(*iReadBuffer);
    iWriteBuffer = new Sws<kWriteBufferBytes>(*this);
    iProtocol = new DviOdp(aDvStack, *this);
}

DviSessionOdp::~DviSessionOdp()
{
    iReadBuffer->ReadInterrupt();
    iShutdownSem.Wait();
    iWriteLock.Wait();
    /* Nothing to do inside this lock.  Taking it after calling iProtocol->Disable() confirms
       that no evented update is currently using iWriteBuffer. */
    iWriteLock.Signal();
    delete iProtocol;
    delete iReaderUntil;
    delete iReadBuffer;
    delete iWriteBuffer;
}

void DviSessionOdp::Run()
{
    iShutdownSem.Wait();

    try {
        iProtocol->Announce();
        for (;;) {
            Brn request = iReaderUntil->ReadUntil(Ascii::kLf);
            try {
                iProtocol->Process(request);
            }
            catch (AssertionFailed&) {
                throw;
            }
            catch (Exception& ex) {
                LOG2(kOdp, kError, "DviSessionOdp::Run - %s parsing request:\n%.*s\n", ex.Message(), PBUF(request));
            }
        }
    }
    catch (AssertionFailed&) {
        throw;
    }
    catch (Exception&) {
    }

    iProtocol->Disable();
    iShutdownSem.Signal();
}

IWriter& DviSessionOdp::WriteLock()
{
    iWriteLock.Wait();
    return *iWriteBuffer;
}

void DviSessionOdp::WriteUnlock()
{
    iWriteLock.Signal();
}

void DviSessionOdp::WriteEnd()
{
    iWriteBuffer->Write(Ascii::kLf);
    iWriteBuffer->WriteFlush();
}

TIpAddress DviSessionOdp::Adapter() const
{
    return iAdapter;
}

const Brx& DviSessionOdp::ClientUserAgentDefault() const
{
    return kUserAgentDefault;
}


// DviServerOdp

DviServerOdp::DviServerOdp(DvStack& aDvStack, TUint aNumSessions, TUint aPort)
    : DviServer(aDvStack)
    , iNumSessions(aNumSessions)
    , iPort(aPort)
{
    Initialise();
}

DviServerOdp::~DviServerOdp()
{
    Deinitialise();
}

TUint DviServerOdp::Port() const
{
    return iPort;
}

SocketTcpServer* DviServerOdp::CreateServer(const NetworkAdapter& aNif)
{
    auto server = new SocketTcpServer(iDvStack.Env(), "OdpServer", iPort, aNif.Address());
    if (iPort == 0) {
        iPort = server->Port();
    }
    for (TUint i=0; i<iNumSessions; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("OdpSession%d", i);
        thName.PtrZ();
        auto session = new DviSessionOdp(iDvStack, aNif.Address());
        server->Add(reinterpret_cast<const TChar*>(thName.Ptr()), session);
    }

    return server;
}

void DviServerOdp::NotifyServerDeleted(TIpAddress /*aInterface*/)
{
}
