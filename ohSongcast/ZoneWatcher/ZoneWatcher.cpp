#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Debug.h>

#include "../Ohm.h"

#include <vector>
#include <stdio.h>

#ifdef _WIN32

#pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case

#define CDECL __cdecl

#include <conio.h>

int mygetch()
{
    return (_getch());
}

#else

#define CDECL

#include <termios.h>
#include <unistd.h>

int mygetch()
{
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

#endif

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class Watcher
{
public:
	Watcher(TIpAddress aInterface);
	void Run();
	~Watcher();
private:
	TIpAddress iInterface;
	OhzSocket iSocket;
	Srs<1000> iBuffer;
	ThreadFunctor* iThread;
};

Watcher::Watcher(TIpAddress aInterface)
	: iInterface(aInterface)
	, iBuffer(iSocket)
{

	iSocket.Open(iInterface, 4);
	iThread = new ThreadFunctor("WATC", MakeFunctor(*this, &Watcher::Run), kPriorityNormal, 64 * 1024);
	iThread->Start();
}

Watcher::~Watcher()
{
	iSocket.ReadInterrupt();
	delete (iThread);
}

void Watcher::Run()
{
	try {

		for (;;) {
			OhzHeader header;
	        
			try {
				header.Internalise(iBuffer);
			}
			catch (OhzError&) {
				printf("Erroneous OHZ message\n");
				iBuffer.ReadFlush();
				continue;
			}

			if (header.MsgType() == OhzHeader::kMsgTypeZoneQuery) {
				OhzHeaderZoneQuery headerZoneQuery;
				headerZoneQuery.Internalise(iBuffer, header);
				Bws<1000> zone(iBuffer.Read(headerZoneQuery.ZoneBytes()));
				zone.Append('\0');
				printf("ZONE QUERY: %s\n", (TChar*)zone.Ptr());
			}
			else if (header.MsgType() == OhzHeader::kMsgTypeZoneUri) {
				OhzHeaderZoneUri headerZoneUri;
				headerZoneUri.Internalise(iBuffer, header);
				Bws<1000> zone(iBuffer.Read(headerZoneUri.ZoneBytes()));
				zone.Append('\0');
				Bws<1000> uri(iBuffer.Read(headerZoneUri.UriBytes()));
				uri.Append('\0');
				printf("ZONE URI: %s = %s\n", (TChar*)zone.Ptr(), (TChar*)uri.Ptr());
			}
			else if (header.MsgType() == OhzHeader::kMsgTypePresetQuery) {
				OhzHeaderPresetQuery headerPresetQuery;
				headerPresetQuery.Internalise(iBuffer, header);
				printf("PRESET QUERY: %d\n", headerPresetQuery.Preset());
			}
			else if (header.MsgType() == OhzHeader::kMsgTypePresetInfo) {
				OhzHeaderPresetInfo headerPresetInfo;
				headerPresetInfo.Internalise(iBuffer, header);
				Bws<1000> info(iBuffer.Read(headerPresetInfo.MetadataBytes()));
				info.Append('\0');
				printf("PRESET INFO: %d = %s\n", headerPresetInfo.Preset(), (TChar*)info.Ptr());
			}

			iBuffer.ReadFlush();
		}
	}
	catch (ReaderError&) {
		return;
	}
	catch (Exception e) {
		printf("Exception in %s at line number %d\n", e.File(), e.Line());
		printf("Press 'q' to close program \n");
	}
}

int CDECL main(int aArgc, char* aArgv[])
{
	//Debug::SetLevel(Debug::kAll);

    OptionParser parser;
    
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);

    if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    InitialisationParams* initParams = InitialisationParams::Create();

    UpnpLibrary::Initialise(initParams);

    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[optionAdapter.Value()]->Subnet();
    TIpAddress interface = (*subnetList)[optionAdapter.Value()]->Address();
    UpnpLibrary::DestroySubnetList(subnetList);

    printf("Using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

	Watcher* watcher = new Watcher(interface);

    for (;;) {
    	int key = mygetch();
    	
    	if (key == 'q') {
    		break;
    	}
	}

	delete (watcher);
}

