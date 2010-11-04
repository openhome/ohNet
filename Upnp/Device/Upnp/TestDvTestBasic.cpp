#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Core/DvDevice.h>
#include <Core/DvZappOrgTestBasic1.h>
#include <Core/CpZappOrgTestBasic1.h>
#include <Zapp.h>
#include <MimeTypes.h>

#include <vector>
#include <sys/stat.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

class ProviderTestBasic : public DvProviderZappOrgTestBasic1
{
public:
    ProviderTestBasic(DvDevice& aDevice);
private:
    void Increment(IInvocationResponse& aResponse, TUint aVersion, TUint aValue, IInvocationResponseUint& aResult);
    void Decrement(IInvocationResponse& aResponse, TUint aVersion, TInt aValue, IInvocationResponseInt& aResult);
    void Toggle(IInvocationResponse& aResponse, TUint aVersion, TBool aValue, IInvocationResponseBool& aResult);
    void EchoString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseString& aResult);
    void EchoBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseBinary& aResult);
    void SetUint(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint);
    void GetUint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValueUint);
    void SetInt(IInvocationResponse& aResponse, TUint aVersion, TInt aValueInt);
    void GetInt(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aValueInt);
    void SetBool(IInvocationResponse& aResponse, TUint aVersion, TBool aValueBool);
    void GetBool(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValueBool);
    void SetMultiple(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void SetString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueStr);
    void GetString(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValueStr);
    void SetBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueBin);
    void GetBinary(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aValueBin);
};

class DeviceBasic : public IResourceManager
{
public:
    DeviceBasic(const Brx& aConfigDir);
    ~DeviceBasic();
private:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter);
private:
    DvDevice* iDevice;
    ProviderTestBasic* iTestBasic;
    Brh iConfigDir;
};


ProviderTestBasic::ProviderTestBasic(DvDevice& aDevice)
    : DvProviderZappOrgTestBasic1(aDevice)
{
    SetPropertyVarUint(0);
    SetPropertyVarInt(0);
    SetPropertyVarBool(false);
    SetPropertyVarStr(Brx::Empty());
    SetPropertyVarBin(Brx::Empty());

    EnableActionIncrement();
    EnableActionDecrement();
    EnableActionToggle();
    EnableActionEchoString();
    EnableActionEchoBinary();
    EnableActionSetUint();
    EnableActionGetUint();
    EnableActionSetInt();
    EnableActionGetInt();
    EnableActionSetBool();
    EnableActionGetBool();
    EnableActionSetMultiple();
    EnableActionSetString();
    EnableActionGetString();
    EnableActionSetBinary();
    EnableActionGetBinary();
}

void ProviderTestBasic::Increment(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValue, IInvocationResponseUint& aResult)
{
    aResponse.Start();
    aResult.Write(++aValue);
    aResponse.End();
}

void ProviderTestBasic::Decrement(IInvocationResponse& aResponse, TUint /*aVersion*/, TInt aValue, IInvocationResponseInt& aResult)
{
    aResponse.Start();
    aResult.Write(--aValue);
    aResponse.End();
}

void ProviderTestBasic::Toggle(IInvocationResponse& aResponse, TUint /*aVersion*/, TBool aValue, IInvocationResponseBool& aResult)
{
    aResponse.Start();
    aResult.Write(!aValue);
    aResponse.End();
}

void ProviderTestBasic::EchoString(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValue, IInvocationResponseString& aResult)
{
    aResponse.Start();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::EchoBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValue, IInvocationResponseBinary& aResult)
{
    aResponse.Start();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::SetUint(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValueUint)
{
    SetPropertyVarUint(aValueUint);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetUint(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseUint& aValueUint)
{
    aResponse.Start();
    TUint val;
    GetPropertyVarUint(val);
    aValueUint.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetInt(IInvocationResponse& aResponse, TUint /*aVersion*/, TInt aValueInt)
{
    SetPropertyVarInt(aValueInt);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetInt(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseInt& aValueInt)
{
    aResponse.Start();
    TInt val;
    GetPropertyVarInt(val);
    aValueInt.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetBool(IInvocationResponse& aResponse, TUint /*aVersion*/, TBool aValueBool)
{
    SetPropertyVarBool(aValueBool);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetBool(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseBool& aValueBool)
{
    aResponse.Start();
    TBool val;
    GetPropertyVarBool(val);
    aValueBool.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetMultiple(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    PropertiesLock();
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    PropertiesUnlock();
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::SetString(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValueStr)
{
    SetPropertyVarStr(aValueStr);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetString(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseString& aValueStr)
{
    aResponse.Start();
    Brhz val;
    GetPropertyVarStr(val);
    aValueStr.Write(val);
    aValueStr.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::SetBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValueBin)
{
    SetPropertyVarBin(aValueBin);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseBinary& aValueBin)
{
    aResponse.Start();
    Brh val;
    GetPropertyVarBin(val);
    aValueBin.Write(val);
    aValueBin.WriteFlush();
    aResponse.End();
}


DeviceBasic::DeviceBasic(const Brx& aConfigDir)
    : iConfigDir(aConfigDir)
{
    iDevice = new DvDevice(Brn("device-ZappTestBasic"));
    iDevice->SetAttribute("Upnp.Domain", "zapp.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "_ZappTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.linn.co.uk");
    iDevice->SetAttribute("Upnp.ModelDescription", "Test service");
    iDevice->SetAttribute("Upnp.ModelName", "Zapp test device");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.linn.co.uk");
    iDevice->SetAttribute("Upnp.SerialNumber", "123456");
    iDevice->SetAttribute("Upnp.Upc", "123456654321");
    iTestBasic = new ProviderTestBasic(*iDevice);
    iDevice->SetEnabled();
}

DeviceBasic::~DeviceBasic()
{
    delete iTestBasic;
    delete iDevice;
}

void DeviceBasic::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, IResourceWriter& aResourceWriter)
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
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (config.Value().Bytes() == 0) {
        parser.DisplayHelp();
        return;
    }

    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartDv();

    Print("TestDvTestBasic - starting ('q' to quit)\n");
    DeviceBasic* device = new DeviceBasic(config.Value());
    while (getchar() != 'q') {
        ;
    }
    delete device;
    Print("TestDvTestBasic - exiting\n");

    UpnpLibrary::Close();
}
