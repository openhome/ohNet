#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/TestFramework.h>

#include <vector>
#include <stdio.h>

#include "ReceiverManager2.h"


#ifdef _WIN32
#define CDECL __cdecl
#else
#define CDECL 
#endif


namespace OpenHome {
namespace Net {

	class ReceiverManager2Logger : IReceiverManager2Handler
	{
	public:
		ReceiverManager2Logger();
		virtual void ReceiverAdded(ReceiverManager2Receiver& aReceiver);
		virtual void ReceiverChanged(ReceiverManager2Receiver& aReceiver);
		virtual void ReceiverRemoved(ReceiverManager2Receiver& aReceiver);
		~ReceiverManager2Logger();
	private:
		ReceiverManager2* iReceiverManager;
	};

} // namespace Net
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

ReceiverManager2Logger::ReceiverManager2Logger()
{
	iReceiverManager = new ReceiverManager2(*this);
}

ReceiverManager2Logger::~ReceiverManager2Logger()
{
	delete (iReceiverManager);
}

void ReceiverManager2Logger::ReceiverAdded(ReceiverManager2Receiver& aReceiver)
{
    Print("Added   ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(")");
	if (aReceiver.Selected()) {
		Print(" Selected ");
	}
	else {
		Print(" Not Selected ");
	}
	Bws<10000> state;
	aReceiver.TransportState(state);
	Print(state);
    Print(" ");
	Bws<10000> uri;
	aReceiver.SenderUri(uri);
	Print(uri);
    Print("\n");
}

void ReceiverManager2Logger::ReceiverChanged(ReceiverManager2Receiver& aReceiver)
{
    Print("Changed ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(")");
	if (aReceiver.Selected()) {
		Print(" Selected ");
	}
	else {
		Print(" Not Selected ");
	}
	Bws<10000> state;
	aReceiver.TransportState(state);
	Print(state);
    Print(" ");
	Bws<10000> uri;
	aReceiver.SenderUri(uri);
	Print(uri);
    Print("\n");
}

void ReceiverManager2Logger::ReceiverRemoved(ReceiverManager2Receiver& aReceiver)
{
    Print("Removed ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(")");
    Print("\n");
}

int CDECL main(int aArgc, char* aArgv[])
{
	InitialisationParams* initParams = InitialisationParams::Create();

    OptionParser parser;
    
    OptionUint optionDuration("-d", "--duration", 30, "Number of seconds to run the test");

    parser.AddOption(&optionDuration);
    
    if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    UpnpLibrary::Initialise(initParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);

    //Debug::SetLevel(Debug::kTopology);

	ReceiverManager2Logger* logger = new ReceiverManager2Logger();
	
    Blocker* blocker = new Blocker;
    blocker->Wait(optionDuration.Value());
    delete blocker;
	
	delete (logger);

	UpnpLibrary::Close();
}
