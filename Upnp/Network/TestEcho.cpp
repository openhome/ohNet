#include <Standard.h>
#include <Thread.h>
#include <Network.h>
#include <TestFramework.h>
#include <Debug.h>
#include <Stream.h>
#include <OsWrapper.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class EchoSession : public SocketTcpSession
{
public:
    EchoSession(Semaphore& aSem)
        : iSem(aSem)
    {
        iStream = new Srs<200>(*this);
    }
    
    ~EchoSession()
    {
        delete iStream;
    }

    void Run()
    {
        const Brn exitUnix("exit");
        const Brn exitDos("exit\r");
        TBool done = false;
        while (!done) {
            try {
                Brn buf = iStream->ReadUntil('\n');
                Write(buf);
                Write('\n');
                if (buf.Equals(exitUnix) || buf.Equals(exitDos))
                    done = true;
            }
            catch (ReaderError&) {
                break;
            }
        }
        iSem.Signal();
    }

private:
    Srs<200>* iStream;
    Semaphore& iSem;
};


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::Initialise(aInitParams);
//    Debug::SetLevel(Debug::kNetwork);

    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(false);
    ASSERT(ifs->size() > 0);
    TIpAddress addr = (*ifs)[0]->Address();
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Using network interface %s\n\n", buf.Ptr());
    Semaphore sem("", 0);
    SocketTcpServer* server = new SocketTcpServer("ECHO", 1025, addr);
    server->Add("ECHO", new EchoSession(sem));

    sem.Wait();
    delete ifs;

    Net::UpnpLibrary::Close();
}

