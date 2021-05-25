#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Net/Private/Globals.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

// SuiteTcpClient

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    OptionParser parser;    

    OptionUint adapter("-i", "--interface", 0, "index of network adapter to use");
    parser.AddOption(&adapter);

    OptionBool send("-s", "--send", "Send");
    parser.AddOption(&send);

    OptionString endpoint("-a", "--address", Brn("239.255.255.250"), "Multicast address");
    parser.AddOption(&endpoint);

    OptionUint port("-p", "--port", 1968, "Multicast port");
    parser.AddOption(&port);

    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    Net::UpnpLibrary::InitialiseMinimal(aInitParams);

    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(*gEnv, Environment::ELoopbackExclude, false/* no ipv6*/, "TestMulticast");
    ASSERT(ifs->size() > 0 && adapter.Value() < ifs->size());
    TIpAddress addr = (*ifs)[adapter.Value()]->Address();
    for (TUint i=0; i<ifs->size(); i++) {
        (*ifs)[i]->RemoveRef("TestMulticast");
    }
    delete ifs;
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Using network interface %s\n\n", buf.Ptr());
    
    Endpoint multicast(port.Value(), endpoint.Value());
    
    if (send.Value() == false) {
        SocketUdpMulticast socket(*gEnv, addr, multicast);

        Endpoint actual(socket.Port(), multicast.Address());
        Bws<100> buf2;
        actual.AppendEndpoint(buf2);
        Print("Receiving from multicast endpoint %s\n", buf2.Ptr());
    
        Bwh message(10000);
        Endpoint sender = socket.Receive(message);
        Bws<100> buf3;
        sender.AppendEndpoint(buf3);
        
        if (message == Brn("Test message")) {
            Print("Received test messsge from %s\n", buf3.Ptr());
        }
        else {
            Print("Received unrecognised messsge from %s\n", buf3.Ptr());
        }
    }
    else {
        if (multicast.Port() == 0) {
            Print("Cannot send to port 0\n");
        }
        else {
            Bws<100> buf2;
            multicast.AppendEndpoint(buf2);
            Print("Sending test message to %s\n", buf2.Ptr());
        
            //SocketUdpMulticast socket(addr, multicast);
            SocketUdp socket(*gEnv, 0, addr);
            
            socket.Send(Brn("Test message"), multicast);
        }
    } 

    Net::UpnpLibrary::Close();
}
