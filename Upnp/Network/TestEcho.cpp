#include <Standard.h>
#include <Thread.h>
#include <Network.h>
#include <TestFramework.h>
#include <Debug.h>
#include <Stream.h>
#include <Os.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

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


void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
//    Debug::SetLevel(Debug::kNetwork);

    std::vector<NetworkInterface*>* ifs = Os::NetworkListInterfaces();
    ASSERT(ifs->size() > 0);
    TIpAddress addr = (*ifs)[0]->Address();
    Print("Using network interface %d.%d.%d.%d\n", addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    Semaphore sem("", 0);
    SocketTcpServer* server = new SocketTcpServer("ECHO", 1025, addr);
    server->Add("ECHO", new EchoSession(sem));

    sem.Wait();
    delete ifs;

    UpnpLibrary::Close();
}

