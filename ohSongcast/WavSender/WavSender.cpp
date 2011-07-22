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

#include "../OhmSender.h"

#include "Icon.h"

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

class PcmSender
{
public:
	static const TUint kPeriodMs = 5;
	static const TUint kSpeedNormal = 100;
    static const TUint kSpeedMin = 75;
	static const TUint kSpeedMax = 150;
	static const TUint kMaxPacketBytes = 4096;
	
public:
	PcmSender(OhmSender* aSender, OhmSenderDriver* aDriver, const Brx& aUri, const TByte* aData, TUint aSampleCount, TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth);
	void Start();
	void Pause();
	void SetSpeed(TUint aValue);
	void Restart();
	~PcmSender();
	
private:
	void CalculatePacketBytes();
	void TimerExpired();
	
private:
    OhmSender* iSender;
    OhmSenderDriver* iDriver;
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

PcmSender::PcmSender(OhmSender* aSender, OhmSenderDriver* aDriver, const Brx& aUri, const TByte* aData, TUint aSampleCount, TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth)
	: iSender(aSender)
	, iDriver(aDriver)
	, iUri(aUri)
	, iData(aData)
	, iSampleCount(aSampleCount)
	, iSampleRate(aSampleRate)
	, iBitRate(aBitRate)
	, iChannels(aChannels)
	, iBitDepth(aBitDepth)
	, iTotalBytes(aSampleCount * aChannels * aBitDepth / 8)
	, iTimer(MakeFunctor(*this, &PcmSender::TimerExpired))
	, iMutex("WAVP")
	, iPaused(false)
	, iSpeed(kSpeedNormal)
	, iIndex(0)
{
	CalculatePacketBytes();
}

void PcmSender::Start()
{
    iDriver->SetAudioFormat(iSampleRate, iBitRate, iChannels, iBitDepth, true, Brn("WAV"));
	iSender->SetEnabled(true);
	iTimer.FireIn(kPeriodMs);
}

void PcmSender::Pause()
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

void PcmSender::Restart()
{
	iMutex.Wait();
	iIndex = 0;
	iMutex.Signal();
}

void PcmSender::SetSpeed(TUint aSpeed)
{
	iMutex.Wait();
	iSpeed = aSpeed;
	CalculatePacketBytes();
	iMutex.Signal();
}

void PcmSender::CalculatePacketBytes()
{
    TUint bytespersample = iChannels * iBitDepth / 8;
    
	TUint bytes = (iSampleRate * iSpeed * bytespersample * kPeriodMs) / (1000 * 100);
	
    if (bytes > kMaxPacketBytes) {
        bytes = kMaxPacketBytes;
    }
	
	TUint samples = bytes / bytespersample;
	
	iPacketBytes = samples * bytespersample;
}

void PcmSender::TimerExpired()
{
	iMutex.Wait();
	
	if (!iPaused) {
	    if (iIndex == 0) {
            iSender->SetTrack(iUri, Brx::Empty(), iSampleCount, 0);
            iSender->SetMetatext(Brn("PcmSender repeated play"));
	    }
	    
		if (iIndex + iPacketBytes <= iTotalBytes) {
			iDriver->SendAudio(&iData[iIndex], iPacketBytes);
            iIndex += iPacketBytes;
		}
		else {
            iDriver->SendAudio(&iData[iIndex], iTotalBytes - iIndex);
            iSender->SetTrack(iUri, Brx::Empty(), iSampleCount, 0);
            TUint remaining = iPacketBytes + iIndex - iTotalBytes;
            iDriver->SendAudio(&iData[0], remaining);
            iIndex = remaining;
		}
	
		iTimer.FireIn(kPeriodMs);
	}
	
	iMutex.Signal();
}

PcmSender::~PcmSender()
{
	iTimer.Cancel();
	delete (iSender);
	delete (iDriver);
}

static void RandomiseUdn(Bwh& aUdn, TIpAddress aAdapter)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    (void)Ascii::AppendDec(buf, Random(aAdapter));
    aUdn.Append(buf);
    aUdn.PtrZ();
}

int CDECL main(int aArgc, char* aArgv[])
{
    OptionParser parser;
    
    OptionString optionFile("-f", "--file", Brn(""), "[file] wav file to send");
    parser.AddOption(&optionFile);
    
    OptionString optionName("-n", "--name", Brn("Openhome WavSender"), "[name] name of the sender");
    parser.AddOption(&optionName);
    
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);

    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);

    OptionUint optionTtl("-t", "--ttl", 1, "[ttl] ttl");
    parser.AddOption(&optionTtl);

    OptionBool optionMulticast("-m", "--multicast", "[multicast] use multicast instead of unicast");
    parser.AddOption(&optionMulticast);

    OptionBool optionDisabled("-d", "--disabled", "[disabled] start up disabled");
    parser.AddOption(&optionDisabled);

    if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    InitialisationParams* initParams = InitialisationParams::Create();

	UpnpLibrary::Initialise(initParams);

    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[optionAdapter.Value()]->Subnet();
    TIpAddress adapter = (*subnetList)[optionAdapter.Value()]->Address();
    UpnpLibrary::DestroySubnetList(subnetList);

    printf("Using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

	Brhz file(optionFile.Value());
    
    if (file.Bytes() == 0) {
    	printf("No wav file specified\n");
    	return (1);
    }
    
    Brhz name(optionName.Value());
    TUint channel = optionChannel.Value();
    TUint ttl = optionTtl.Value();
    TBool multicast = optionMulticast.Value();
    TBool disabled = optionDisabled.Value();

    // Read WAV file
    
    FILE* pFile = fopen(file.CString(), "rb");
    
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
    	printf("Unable to read wav file %d, %d\n", (int)count, subChunk2Size);
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
    
    UpnpLibrary::StartDv();

	Bwh udn("device");
    RandomiseUdn(udn, adapter);

    DvDeviceStandard* device = new DvDeviceStandard(udn);
    
    device->SetAttribute("Upnp.Domain", "av.openhome.org");
    device->SetAttribute("Upnp.Type", "Sender");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", name.CString());
    device->SetAttribute("Upnp.Manufacturer", "Openhome");
    device->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    device->SetAttribute("Upnp.ModelDescription", "Openhome WavSender");
    device->SetAttribute("Upnp.ModelName", "Openhome WavSender");
    device->SetAttribute("Upnp.ModelNumber", "1");
    device->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    device->SetAttribute("Upnp.SerialNumber", "");
    device->SetAttribute("Upnp.Upc", "");

    OhmSenderDriver* driver = new OhmSenderDriver();
    
	Brn icon(icon_png, icon_png_len);

	OhmSender* sender = new OhmSender(*device, *driver, name, channel, adapter, ttl, multicast, !disabled, icon, Brn("image/png"), 0);
	
    PcmSender* pcmsender = new PcmSender(sender, driver, file, data, sampleCount, sampleRate, byteRate * 8, numChannels, bitsPerSample);
    
    device->SetEnabled();

	pcmsender->Start();
	
	TUint speed = PcmSender::kSpeedNormal;
	
	printf("q = quit, f = faster, s = slower, n = normal, p = pause, r = restart, m = toggle multicast, e = toggle enabled\n");
	
    for (;;) {
    	int key = mygetch();
    	
    	if (key == 'q') {
    		break;
    	}

    	if (key == 'f') {
            if (speed < PcmSender::kSpeedMax) {
        		speed++;
        		pcmsender->SetSpeed(speed);
            }
    		printf("%d\n", speed);
    	}

      	if (key == 's') {
      		if (speed > PcmSender::kSpeedMin) {
    			speed--;
	    		pcmsender->SetSpeed(speed);
    		}
    		printf("%d\n", speed);
    	}

        if (key == 'n') {
            speed = PcmSender::kSpeedNormal;
            pcmsender->SetSpeed(speed);
            printf("%d\n", speed);
        }

        if (key == 'p') {
            pcmsender->Pause();
            printf("pause\n");
        }

        if (key == 'r') {
            pcmsender->Restart();
            printf("restart\n");
        }

        if (key == 'm') {
            if (multicast) {
                multicast = false;
                sender->SetMulticast(false);
                printf("unicast\n");
            }
            else {
                multicast = true;
                sender->SetMulticast(true);
                printf("multicast\n");
            }
        }

        if (key == 'e') {
            if (disabled) {
                disabled = false;
                sender->SetEnabled(true);
                printf("enabled\n");
            }
            else {
                disabled = true;
                sender->SetEnabled(false);
                printf("disabled\n");
            }
        }
    }
       
    delete (pcmsender);

    delete (device);
    
	printf("\n");
	
    return (0);
}
