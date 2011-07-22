#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Debug.h>

#include <vector>
#include <stdio.h>

#include "Product.h"

#include <termios.h>
#include <unistd.h>

int mygetch(void)
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

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

using namespace Openhome::Av;

static void RandomiseUdn(Bwh& aUdn)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    NetworkAdapter* nif = Stack::NetworkAdapterList().CurrentInterface();
    TUint max = nif->Address();
    delete nif;
    (void)Ascii::AppendDec(buf, Random(max));
    aUdn.Append(buf);
    aUdn.PtrZ();
}

class CStandbyHandler : public IStandbyHandler
{
	void SetStandby(TBool aValue) {}
};

class CSourceIndexHandler : public ISourceIndexHandler
{
	void SetSourceIndex(TUint aValue) {}
};

int main(int aArgc, char* aArgv[])
{
	//Debug::SetLevel(Debug::kNetwork);
	
    OptionParser parser;
    
    OptionString optionUri("-u", "--uri", Brn(""), "[uri] uri to receive from");
    parser.AddOption(&optionUri);
    
    OptionString optionName("-n", "--name", Brn("Receiver"), "[name] name of the receiver");
    parser.AddOption(&optionName);
    
    OptionUint adapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&adapter);

    if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(false);
    ASSERT(ifs->size() > 0 && adapter.Value() < ifs->size());
    TIpAddress interface = (*ifs)[adapter.Value()]->Address();
    for (TUint i=0; i<ifs->size(); i++) {
        delete (*ifs)[i];
    }
    delete ifs;
    
    printf("Using network interface %d.%d.%d.%d\n", interface&0xff, (interface>>8)&0xff, (interface>>16)&0xff, (interface>>24)&0xff);

	Brhz uri(optionUri.Value());
    Brhz name(optionName.Value());
    
    if (uri.Bytes() == 0) {
    	printf("No uri specified\n");
    	return (1);
    }
    
    InitialisationParams* initParams = InitialisationParams::Create();

    UpnpLibrary::Initialise(initParams);
    
    UpnpLibrary::StartDv();

	Bwh udn("device");
    RandomiseUdn(udn);

    DvDevice* device = new DvDevice(udn);

	CStandbyHandler standbyhandler;
	CSourceIndexHandler sourceindexhandler;
	    
    CProduct* product = new CProduct(*device
    , standbyhandler
    , sourceindexhandler
    , false
    , ""
    , "Openhome"
    , "Connecting you to your home"
    , "http://www.openhome.org"
    , ""
    , "Receiver"
    , ""
    , "http://www.openhome.org"
    , ""
    , "Openhome"
    , "Receiver"
    , ""
    , "http://www.openhome.org"
    , "");
    
    device->SetEnabled();

	printf("q = quit\n");
	
    while (true) {
    	int key = mygetch();
    	
    	if (key == 'q') {
    		break;
    	}
    }
       
    delete (product);
    delete (device);
	printf("\n");
    return (0);
}

