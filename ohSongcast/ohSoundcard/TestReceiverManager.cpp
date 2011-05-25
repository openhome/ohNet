#include <ZappTypes.h>
#include <Zapp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>
#include <Thread.h>
#include <OptionParser.h>
#include <Debug.h>
#include <TestFramework.h>

#include <vector>
#include <stdio.h>

#include "ReceiverManager.h"

namespace Zapp {

	class ReceiverManagerLogger
	{
	public:
		ReceiverManagerLogger(const Brx& aReceiverName);
		void ListUpdated();
		void StatusUpdated();
		~ReceiverManagerLogger();
	private:
		ReceiverManager* iReceiverManager;
	};

}

using namespace Zapp;
using namespace Zapp::TestFramework;

ReceiverManagerLogger::ReceiverManagerLogger(const Brx& aReceiverName)
{
	Functor listUpdated = MakeFunctor(*this, &ReceiverManagerLogger::ListUpdated);
    Functor statusUpdated = MakeFunctor(*this, &ReceiverManagerLogger::StatusUpdated);
	iReceiverManager = new ReceiverManager(statusUpdated, listUpdated, aReceiverName);
}

ReceiverManagerLogger::~ReceiverManagerLogger()
{
	delete (iReceiverManager);
}

void ReceiverManagerLogger::ListUpdated()
{
	Bws<ReceiverManager::kMaxListBytes> list;
	iReceiverManager->List(list);
    Print(list);
    Print("-----\n");
}

void ReceiverManagerLogger::StatusUpdated()
{
	ReceiverManager::EStatus status = iReceiverManager->Status();

	switch (status) {
	case ReceiverManager::eOff:
		Print("STATUS OFF\n");
		break;
	case ReceiverManager::eOn:
		Print("STATUS ON\n");
		break;
	case ReceiverManager::eListening:
		Print("STATUS LISTENING\n");
		break;
	default:
		Print("STATUS UNRECOGNISED\n");
		break;
	}
    Print("-----\n");
}


int __cdecl main(int aArgc, char* aArgv[])
{
	InitialisationParams* initParams = InitialisationParams::Create();

    OptionParser parser;
    
    OptionUint optionDuration("-d", "--duration", 30, "Number of seconds to run the test");

    parser.AddOption(&optionDuration);
    
    if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    UpnpLibrary::Initialise(initParams);
    
    UpnpLibrary::StartCp();

    //Debug::SetLevel(Debug::kTopology);

	ReceiverManagerLogger* logger = new ReceiverManagerLogger(Brn("Graham Darnell (Majik DS-I 2)"));
	
    Blocker* blocker = new Blocker;
    blocker->Wait(optionDuration.Value());
    delete blocker;

	Print("Wait complete\n");

	delete (logger);

	Print("Logger deleted\n");

    UpnpLibrary::Close();

	Print("Test complete\n");
}
