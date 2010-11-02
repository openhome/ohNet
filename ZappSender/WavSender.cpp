#include <ZappTypes.h>
#include <Core/DvDevice.h>
#include <Zapp.h>
#include <Core/CpDevice.h>
#include <Core/CpDeviceUpnp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>
#include <Thread.h>
#include <OptionParser.h>
#include <Debug.h>

#include <vector>
#include <stdio.h>

#include "OhmSender.h"

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

using namespace Zapp;
using namespace Zapp::TestFramework;

class WavSender
{
public:
	static const TUint kPeriodMs = 5;
	static const TUint kSpeedNormal = 100;
    static const TUint kSpeedMin = 75;
	static const TUint kSpeedMax = 150;
	static const TUint kMaxPacketBytes = 4096;
	
public:
	WavSender(OhmSender* aSender, const Brx& aUri, const TByte* aData, TUint aSampleCount, TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth);
	void Start();
	void Pause();
	void SetSpeed(TUint aValue);
	void Restart();
	~WavSender();
	
private:
	void CalculatePacketBytes();
	void TimerExpired();
	
private:
	OhmSender* iSender;
	Bws<OhmSender::kMaxTrackUriBytes> iUri;
	const TByte* iData;
	TUint iSampleCount;
	TUint iSampleRate;
	TUint iBitRate;
	TUint iChannels;
	TUint iBitDepth;
	TUint iTotalBytes;
	Timer iTimer;
	Mutex iMutex;
	TBool iPaused;
	TUint iSpeed;
	TUint iIndex;
	TUint iPacketBytes;
};

WavSender::WavSender(OhmSender* aSender, const Brx& aUri, const TByte* aData, TUint aSampleCount, TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth)
	: iSender(aSender)
	, iUri(aUri)
	, iData(aData)
	, iSampleCount(aSampleCount)
	, iSampleRate(aSampleRate)
	, iBitRate(aBitRate)
	, iChannels(aChannels)
	, iBitDepth(aBitDepth)
	, iTotalBytes(aSampleCount * aChannels * aBitDepth / 8)
	, iTimer(MakeFunctor(*this, &WavSender::TimerExpired))
	, iMutex("WAVP")
	, iPaused(false)
	, iSpeed(kSpeedNormal)
	, iIndex(0)
{
	CalculatePacketBytes();
}

void WavSender::Start()
{
    iSender->SetAudioFormat(iSampleRate, iBitRate, iChannels, iBitDepth, true, Brn("WAV"));
	iSender->SetEnabled(true);
	iTimer.FireIn(kPeriodMs);
}

void WavSender::Pause()
{
	iMutex.Wait();

	if (iPaused) {
		iPaused = false;
		iTimer.FireIn(kPeriodMs);
	}
	else {
		iPaused = true;
	}
	
	iMutex.Signal();
}

void WavSender::Restart()
{
	iMutex.Wait();
	iIndex = 0;
	iMutex.Signal();
}

void WavSender::SetSpeed(TUint aSpeed)
{
	iMutex.Wait();
	iSpeed = aSpeed;
	CalculatePacketBytes();
	iMutex.Signal();
}

void WavSender::CalculatePacketBytes()
{
    TUint bytespersample = iChannels * iBitDepth / 8;
    #
	TUint bytes = (iSampleRate * iSpeed * bytespersample * kPeriodMs) / (1000 * 100);
	
    if (bytes > kMaxPacketBytes) {
        bytes = kMaxPacketBytes;
    }
	
	TUint samples = bytes / bytespersample;
	
	iPacketBytes = samples * bytespersample;
}

void WavSender::TimerExpired()
{
	iMutex.Wait();
	
	if (!iPaused) {
	    if (iIndex == 0) {
            iSender->StartTrack(0, iSampleCount, iUri, Brx::Empty());
	    }
	    
		if (iIndex + iPacketBytes <= iTotalBytes) {
			iSender->SendAudio(&iData[iIndex], iPacketBytes);
            iIndex += iPacketBytes;
		}
		else {
            iSender->SendAudio(&iData[iIndex], iTotalBytes - iIndex);
            iSender->StartTrack(0, iSampleCount);
            TUint remaining = iPacketBytes + iIndex - iTotalBytes;
            iSender->SendAudio(&iData[0], remaining);
            iIndex = remaining;
		}
	
		iTimer.FireIn(kPeriodMs);
	}
	
	iMutex.Signal();
}

WavSender::~WavSender()
{
	iTimer.Cancel();
	delete (iSender);
}

static void RandomiseUdn(Bwh& aUdn)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    TUint max = nif->Address();
    delete nif;
    (void)Ascii::AppendDec(buf, Random(max));
    aUdn.Append(buf);
    aUdn.PtrZ();
}

int main(int aArgc, char* aArgv[])
{
	//Debug::SetLevel(Debug::kNetwork);
	
    OptionParser parser;
    
    OptionString optionFile("-f", "--file", Brn(""), "[file] wav file to send");
    parser.AddOption(&optionFile);
    
    OptionString optionName("-n", "--name", Brn("Openhome WavSender"), "[name] name of the sender");
    parser.AddOption(&optionName);
    
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);

    OptionUint adapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&adapter);

    if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    std::vector<NetworkInterface*>* ifs = Os::NetworkListInterfaces(false);
    ASSERT(ifs->size() > 0 && adapter.Value() < ifs->size());
    TIpAddress interface = (*ifs)[adapter.Value()]->Address();
    for (TUint i=0; i<ifs->size(); i++) {
        delete (*ifs)[i];
    }
    delete ifs;
    
    printf("Using network interface %d.%d.%d.%d\n", interface&0xff, (interface>>8)&0xff, (interface>>16)&0xff, (interface>>24)&0xff);

	Brhz file(optionFile.Value());
    Brhz name(optionName.Value());
    TUint channel = optionChannel.Value();
    
    if (file.Bytes() == 0) {
    	printf("No wav file specified\n");
    	return (1);
    }
    
    // Read WAV file
    
    FILE* pFile = fopen(file.CString(), "r");
    
    if (pFile == 0) {
    	printf("Unable to open specified wav file\n");
    	return (1);
    }
    
    TByte* header = new TByte[44];
    
    size_t count = fread((void*)header, 1, 44, pFile);
    
    if (count != 44)
    {
    	printf("Unable to read the specified wav file\n");
    	return (1);
    }
    
    if (header[0] != 'R' || header[1] != 'I' || header[2] != 'F' || header[3] != 'F')
    {
    	printf("Invalid wav file\n");
    	return (1);
    }
    
    TUint header0;
    TUint header1;
    TUint header2;
    TUint header3;

    header0 = header[4];
    header1 = header[5];
    header2 = header[6];
    header3 = header[7];

    // TUint chunkSize = header0 | (header1 << 8) | (header2 << 16) | (header3 << 24);
    
    if (header[8] != 'W' || header[9] != 'A' || header[10] != 'V' || header[11] != 'E')
    {
    	printf("Invalid wav file\n");
    	return (1);
    }
    
    if (header[12] != 'f' || header[13] != 'm' || header[14] != 't' || header[15] != ' ')
    {
    	printf("Invalid wav file\n");
    	return (1);
    }
    
    header0 = header[16];
    header1 = header[17];
    header2 = header[18];
    header3 = header[19];

    TUint subChunk1Size = header0 | (header1 << 8) | (header2 << 16) | (header3 << 24);
    
    if (subChunk1Size != 16)
    {
    	printf("Unsupported wav file\n");
    	return (1);
    }
    
    header0 = header[20];
    header1 = header[21];

    TUint audioFormat = header0 | (header1 << 8);
    
    if (audioFormat != 1)
    {
    	printf("Unsupported wav file\n");
    	return (1);
    }
    
    header0 = header[22];
    header1 = header[23];

    TUint numChannels = header0 | (header1 << 8);
    
    header0 = header[24];
    header1 = header[25];
    header2 = header[26];
    header3 = header[27];

    TUint sampleRate = header0 | (header1 << 8) | (header2 << 16) | (header3 << 24);
    
    header0 = header[28];
    header1 = header[29];
    header2 = header[30];
    header3 = header[31];

    TUint byteRate = header0 | (header1 << 8) | (header2 << 16) | (header3 << 24);
    
    //header0 = header[32];
    //header1 = header[33];

    //TUint blockAlign = header0 | (header1 << 8);
    
    header0 = header[34];
    header1 = header[35];

    TUint bitsPerSample = header0 | (header1 << 8);
    
    if (header[36] != 'd' || header[37] != 'a' || header[38] != 't' || header[39] != 'a')
    {
    	printf("Invalid wav file\n");
    	return (1);
    }
    
    header0 = header[40];
    header1 = header[41];
    header2 = header[42];
    header3 = header[43];

    TUint subChunk2Size = header0 | (header1 << 8) | (header2 << 16) | (header3 << 24);
    
    TByte* data = new TByte[subChunk2Size];
    
    count = fread((void*)data, 1, subChunk2Size, pFile);
    
    if (count != subChunk2Size)
    {
    	printf("Unable to read wav file\n");
    	return (1);
    }
    
    fclose(pFile);
    
    // Convert sample data
    
    TByte* sample = new TByte[4];
    
  	TUint bytesPerSample = bitsPerSample / 8;
	TUint sampleCount = subChunk2Size / bytesPerSample / numChannels;
  	
    TUint scount = subChunk2Size / bytesPerSample;
    
    TUint pindex = 0;
    
    while (scount-- > 0)
    {
    	TUint bcount = bytesPerSample;

	    TUint sindex = 0;
	    
	    while (bcount-- > 0)
	    {
	    	sample[sindex++] = data[pindex++];
	    }
	    
    	bcount = bytesPerSample;
    	
    	sindex = 0;

	    while (bcount-- > 0)
	    {
	    	data[--pindex] = sample[sindex++];
	    }
	    
		pindex += bytesPerSample;	    
    }
    
    InitialisationParams* initParams = InitialisationParams::Create();

    UpnpLibrary::Initialise(initParams);
    
    UpnpLibrary::StartDv();

	Bwh udn("device");
    RandomiseUdn(udn);

    DvDevice* device = new DvDevice(udn);
    
    device->SetAttribute("Upnp.Domain", "music.openhome.org");
    device->SetAttribute("Upnp.Type", "Sender");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", name.CString());
    device->SetAttribute("Upnp.Manufacturer", "Openhome");
    device->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    device->SetAttribute("Upnp.ModelDescription", "Openhome WavSender");
    device->SetAttribute("Upnp.ModelName", "Openhome WavSender");
    device->SetAttribute("Upnp.ModelNumber", "1");
    device->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    device->SetAttribute("Upnp.SerialNumber", "Not Applicable");
    device->SetAttribute("Upnp.Upc", "Not Applicable");

	OhmSender* sender = new OhmSender(*device, interface, name, channel);
	
    WavSender* wavsender = new WavSender(sender, file, data, sampleCount, sampleRate, byteRate * 8, numChannels, bitsPerSample);
    
    device->SetEnabled();

	wavsender->Start();
	
	TUint speed = WavSender::kSpeedNormal;
	
	printf("q = quit, f = faster, s = slower, n = normal, p = pause, r = restart\n");
	
    while (true) {
    	int key = mygetch();
    	
    	if (key == 'q') {
    		break;
    	}

    	if (key == 'f') {
            if (speed < WavSender::kSpeedMax) {
        		speed++;
        		wavsender->SetSpeed(speed);
            }
    		printf("%d\n", speed);
    	}

      	if (key == 's') {
      		if (speed > WavSender::kSpeedMin) {
    			speed--;
	    		wavsender->SetSpeed(speed);
    		}
    		printf("%d\n", speed);
    	}

        if (key == 'n') {
            speed = WavSender::kSpeedNormal;
            wavsender->SetSpeed(speed);
            printf("%d\n", speed);
        }

        if (key == 'p') {
            wavsender->Pause();
            printf("pause\n");
        }

        if (key == 'r') {
            wavsender->Restart();
            printf("restart\n");
        }
    }
       
    delete (wavsender);

    delete (device);
    
	printf("\n");
	
    return (0);
}

