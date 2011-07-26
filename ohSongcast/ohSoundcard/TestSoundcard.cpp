#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Debug.h>

#include <vector>
#include <stdio.h>

#include "Soundcard.h"

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

void STDCALL loggerReceiver(void* /* aPtr */, ECallbackType aType, THandle aReceiver)
{
	const char* room = ReceiverRoom(aReceiver);
	const char* group = ReceiverGroup(aReceiver);
	const char* name = ReceiverName(aReceiver);
	EReceiverStatus status = ReceiverStatus(aReceiver);

	switch (aType) {
	case eAdded:
		printf("Added   %s %s %s %d\n", room, group, name, status);
		break;
	case eChanged:
		printf("Changed %s %s %s %d\n", room, group, name, status);
		break;
	case eRemoved:
		printf("Removed %s %s %s %d\n", room, group, name, status);
		break;
	}
}

void STDCALL loggerSubnet(void* /* aPtr */, ECallbackType aType, THandle aSubnet)
{
	TIpAddress address = SubnetAddress(aSubnet);
	const char* name = SubnetAdapterName(aSubnet);

	switch (aType) {
	case eAdded:
		printf("Added   %x %s \n", address, name);
		break;
	case eChanged:
		printf("Changed %x %s \n", address, name);
		break;
	case eRemoved:
		printf("Removed %x %s \n", address, name);
		break;
	}
}

int CDECL main(int /* aArgc */, char** /* aArgv[] */)
{
	TIpAddress subnet = 522;
    TUint channel = 0;
    TUint ttl = 4;
    TBool multicast = false;
    TBool disabled = false;
    TUint preset = 99;

	THandle soundcard = SoundcardCreate(subnet, channel, ttl, multicast, !disabled, preset, loggerReceiver, 0, loggerSubnet, 0);

	if (soundcard == 0) {
		printf("Soundcard error\n");
		return(1);
	}

	printf("preset = %d\n", preset);

    if (multicast) {
        printf("multicast\n");
    }
    else {
        printf("unicast\n");
    }

    if (disabled) {
        printf("disabled\n");
    }
    else {
        printf("enabled\n");
    }

	printf("q = quit, m = toggle multicast, e = toggle enabled\n");
	
    for (;;) {
    	int key = mygetch();
    	
    	if (key == 'q') {
    		break;
    	}

        if (key == 'm') {
            if (multicast) {
                multicast = false;
                SoundcardSetMulticast(soundcard, false);
                printf("unicast\n");
            }
            else {
                multicast = true;
                SoundcardSetMulticast(soundcard, true);
                printf("multicast\n");
            }
        }

        if (key == 'e') {
            if (disabled) {
                disabled = false;
                SoundcardSetEnabled(soundcard, true);
                printf("enabled\n");
            }
            else {
                disabled = true;
                SoundcardSetEnabled(soundcard, false);
                printf("disabled\n");
            }
        }
    }
    
	SoundcardDestroy(soundcard);

	printf("\n");
	
    return (0);
}
