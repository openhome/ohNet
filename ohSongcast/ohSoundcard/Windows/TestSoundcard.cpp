#include <ZappTypes.h>
#include <Zapp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>
#include <Thread.h>
#include <OptionParser.h>
#include <Debug.h>

#include <vector>
#include <stdio.h>

#include "Soundcard.h"

#pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case

#include <conio.h>

int mygetch()
{
    return (_getch());
}

using namespace Zapp;
using namespace Zapp::TestFramework;

int __cdecl main(int aArgc, char* aArgv[])
{
	//Debug::SetLevel(Debug::kMedia);
	
    OptionParser parser;
    
    OptionString optionName("-n", "--name", Brn("TestSoundcard"), "[name] name of the soundcard");
    parser.AddOption(&optionName);
    
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] multicast channel");
    parser.AddOption(&optionChannel);

    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);

    OptionUint optionTtl("-t", "--ttl", 1, "[ttl] ttl");
    parser.AddOption(&optionTtl);

    OptionBool optionMulticast("-m", "--multicast", "[multicast] use multicast instead of unicast");
    parser.AddOption(&optionMulticast);

    OptionBool optionDisabled("-d", "--disabled", "[disabled] start up disabled");
    parser.AddOption(&optionDisabled);

    OptionUint optionPreset("-p", "--preset", 0, "[0..99] preset number");
    parser.AddOption(&optionPreset);

    if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    std::vector<NetworkInterface*>* ifs = Os::NetworkListInterfaces(false);
    
	ASSERT(ifs->size() > 0 && optionAdapter.Value() < ifs->size());
    
	TIpAddress iface = (*ifs)[optionAdapter.Value()]->Address();
    
	for (TUint i=0; i<ifs->size(); i++) {
        delete (*ifs)[i];
    }
    
	delete ifs;
    
    printf("Using network interface %d.%d.%d.%d\n", iface&0xff, (iface>>8)&0xff, (iface>>16)&0xff, (iface>>24)&0xff);

    const TChar* name(optionName.CString());
    TUint channel = optionChannel.Value();
    TUint ttl = optionTtl.Value();
    TBool multicast = optionMulticast.Value();
    TBool disabled = optionDisabled.Value();
    TUint preset = optionPreset.Value();

    Soundcard* soundcard = Soundcard::Create(name, channel, iface, ttl, multicast, !disabled, preset);

	if (soundcard == 0) {
		printf("Soundcard error\n");
		return(1);
	}

	printf("name = %s\n", name);
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
                soundcard->SetMulticast(false);
                printf("unicast\n");
            }
            else {
                multicast = true;
                soundcard->SetMulticast(true);
                printf("multicast\n");
            }
        }

        if (key == 'e') {
            if (disabled) {
                disabled = false;
                soundcard->SetEnabled(true);
                printf("enabled\n");
            }
            else {
                disabled = true;
                soundcard->SetEnabled(false);
                printf("disabled\n");
            }
        }
    }
       
    delete (soundcard);

	printf("\n");
	
    return (0);
}
