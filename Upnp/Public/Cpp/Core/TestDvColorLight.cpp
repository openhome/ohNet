#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Core/DvDevice.h>
#include <Core/DvOpenhomeOrgTestColorLight1.h>
#include <Zapp.h>
#include <MimeTypes.h>
#include <Printer.h>

#include <stdlib.h>
#include <vector>
#include <sys/stat.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

class ProviderColorLight : public DvProviderOpenhomeOrgTestColorLight1
{
public:
    ProviderColorLight(DvDevice& aDevice);
private:
    void GetName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFriendlyName);
    void SetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aRed, TUint aGreen, TUint aBlue);
    void GetColor(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue);
    void GetMaxColors(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue);
};

class DeviceColorLight : public IResourceManager
{
public:
    DeviceColorLight(const Brx& aConfigDir);
    ~DeviceColorLight();
private:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter);
private:
    DvDevice* iDevice;
    ProviderColorLight* iColorLight;
    Brh iConfigDir;
};


ProviderColorLight::ProviderColorLight(DvDevice& aDevice)
    : DvProviderOpenhomeOrgTestColorLight1(aDevice)
{
    EnableActionGetName();
    EnableActionSetColor();
    EnableActionGetColor();
    EnableActionGetMaxColors();
}

void ProviderColorLight::GetName(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseString& aFriendlyName)
{
    const Brn name("Test color zigbee light");
    aResponse.Start();
    aFriendlyName.Write(name);
    aFriendlyName.WriteFlush();
    aResponse.End();
}

void ProviderColorLight::SetColor(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aRed, TUint aGreen, TUint aBlue)
{
    Log::Print("SetColor: r=%u, g=%u, b=%u\n", aRed, aGreen, aBlue);
    aResponse.Start();
    aResponse.End();
}

void ProviderColorLight::GetColor(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue)
{
    Log::Print("GetColor\n");
    aResponse.Start();
    aRed.Write(0);
    aGreen.Write(0);
    aBlue.Write(0);
    aResponse.End();
}

void ProviderColorLight::GetMaxColors(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue)
{
    Log::Print("GetMaxColors\n");
    aResponse.Start();
    aRed.Write(5);
    aGreen.Write(6);
    aBlue.Write(5);
    aResponse.End();
}


DeviceColorLight::DeviceColorLight(const Brx& aConfigDir)
    : iConfigDir(aConfigDir)
{
    iDevice = new DvDevice(Brn("device-OpenhomeColorLight"), *this);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "TestColorLight");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "_OpenhomeTestColorLight");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "Test zigbee light");
    iDevice->SetAttribute("Upnp.ModelName", "Test zigbee light");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "123456");
    iDevice->SetAttribute("Upnp.Upc", "123456654321");
    iColorLight = new ProviderColorLight(*iDevice);
    iDevice->SetEnabled();
}

DeviceColorLight::~DeviceColorLight()
{
    delete iColorLight;
    delete iDevice;
}

void DeviceColorLight::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, IResourceWriter& aResourceWriter)
{
    const Brn kIndexFile("index.html");
    Bwh filePath(iConfigDir);
    Brn file;
    if (aUriTail.Bytes() == 0) {
        file.Set(kIndexFile);
    }
    else {
        file.Set(aUriTail);
    }
    const TByte sep =
#ifdef _WIN32
                      '\\';
#else
                      '/';
#endif
    filePath.Grow(filePath.Bytes() + 1 + file.Bytes()+1);
    filePath.Append(sep);
    filePath.Append(file);
    filePath.PtrZ();

    const char* path = (const char*)filePath.Ptr();
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        return;
    }
    static const TUint kMaxReadSize = 4096;
    struct stat fileStats;
    (void)stat(path, &fileStats);
    TUint bytes = (TUint)fileStats.st_size;
    const char* mime = NULL;
    for (TUint i=filePath.Bytes()-1; i>0; i--) {
        if (filePath[i] == '/' || filePath[i] == '\\') {
            break;
        }    
        if (filePath[i] == '.') {
            const char* ext = (const char*)filePath.Split(i+1, filePath.Bytes()-i-1).Ptr();
            if (strcmp(ext, "html") == 0 || strcmp(ext, "htm") == 0) {
                mime = kZappMimeTypeHtml;
            }
            break;
        }
    }
    aResourceWriter.WriteResourceBegin(bytes, mime);
    do {
        TByte buf[kMaxReadSize];
        TUint size = (bytes<kMaxReadSize? bytes : kMaxReadSize);
        (void)fread(buf, size, 1, fd);
        aResourceWriter.WriteResource(buf, size);
        bytes -= size;
    } while (bytes > 0);
    aResourceWriter.WriteResourceEnd();
    (void)fclose(fd);
}


void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    Brn emptyString("");
    OptionString config("-c", "--config", emptyString, "[full dir path] to folder containing web UI");
    parser.AddOption(&config);
    OptionBool loopback("-l", "--loopback", "Use the loopback adapter only");
    parser.AddOption(&loopback);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (config.Value().Bytes() == 0) {
        parser.DisplayHelp();
        return;
    }

    if (loopback.IsSet()) {
        aInitParams->SetUseLoopbackNetworkInterface();
    }
    aInitParams->SetDvNumWebSocketThreads(5);
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartDv();

    Print("TestDvColorLight - starting ('q' to quit)\n");
    DeviceColorLight* device = new DeviceColorLight(config.Value());
    while (getchar() != 'q') {
        ;
    }
    delete device;
    Print("TestDvColorLight - exiting\n");

    UpnpLibrary::Close();
}
