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

#include "ReceiverManager3.h"


#ifdef _WIN32
#define CDECL __cdecl
#else
#define CDECL 
#endif


namespace OpenHome {
namespace Net {

	class ReceiverManager3Logger : IReceiverManager3Handler
	{
	public:
		ReceiverManager3Logger(const Brx& aUri);
		virtual void ReceiverAdded(ReceiverManager3Receiver& aReceiver);
		virtual void ReceiverChanged(ReceiverManager3Receiver& aReceiver);
		virtual void ReceiverRemoved(ReceiverManager3Receiver& aReceiver);
		~ReceiverManager3Logger();
	private:
		ReceiverManager3* iReceiverManager;
	};

} // namespace Net
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

// ohz://239.255.255.250:51972/0026-0f21-88aa

ReceiverManager3Logger::ReceiverManager3Logger(const Brx& aValue)
{
	iReceiverManager = new ReceiverManager3(*this, aValue, Brx::Empty());
}

ReceiverManager3Logger::~ReceiverManager3Logger()
{
	delete (iReceiverManager);
}

void ReceiverManager3Logger::ReceiverAdded(ReceiverManager3Receiver& aReceiver)
{
    Print("Added   ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(") ");

	switch(aReceiver.Status()) {
	case ReceiverManager3Receiver::eDisconnected:
		Print("Disconnected");
		break;
	case ReceiverManager3Receiver::eConnecting:
		Print("Connecting");
		break;
	case ReceiverManager3Receiver::eConnected:
		Print("Connected");
		break;
	}

	Print("\n");
}

void ReceiverManager3Logger::ReceiverChanged(ReceiverManager3Receiver& aReceiver)
{
    Print("Changed ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(") ");

	switch(aReceiver.Status()) {
	case ReceiverManager3Receiver::eDisconnected:
		Print("Disconnected");
		break;
	case ReceiverManager3Receiver::eConnecting:
		Print("Connecting");
		break;
	case ReceiverManager3Receiver::eConnected:
		Print("Connected");
		break;
	}

    Print("\n");
}

void ReceiverManager3Logger::ReceiverRemoved(ReceiverManager3Receiver& aReceiver)
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
    
    OptionString optionUri("-u", "--uri", Brx::Empty(), "Uri to monitor");

    parser.AddOption(&optionUri);

	if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    UpnpLibrary::Initialise(initParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);

    Debug::SetLevel(Debug::kTopology);

	ReceiverManager3Logger* logger = new ReceiverManager3Logger(optionUri.Value());
	
    Blocker* blocker = new Blocker;
    blocker->Wait(optionDuration.Value());

	delete blocker;
	
	delete (logger);

	UpnpLibrary::Close();
}
