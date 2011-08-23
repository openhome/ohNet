#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/DvStack.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/CpOpenhomeOrgTestBasic1.h>

#include <stdlib.h>
#include <vector>
#include <sys/stat.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class ProviderTestBasic : public DvProviderOpenhomeOrgTestBasic1
{
public:
    ProviderTestBasic(DvDevice& aDevice);
private:
    void Increment(IDvInvocationResponse& aResponse, TUint aVersion, TUint aValue, IDvInvocationResponseUint& aResult);
    void Decrement(IDvInvocationResponse& aResponse, TUint aVersion, TInt aValue, IDvInvocationResponseInt& aResult);
    void Toggle(IDvInvocationResponse& aResponse, TUint aVersion, TBool aValue, IDvInvocationResponseBool& aResult);
    void EchoString(IDvInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IDvInvocationResponseString& aResult);
    void EchoBinary(IDvInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IDvInvocationResponseBinary& aResult);
    void SetUint(IDvInvocationResponse& aResponse, TUint aVersion, TUint aValueUint);
    void GetUint(IDvInvocationResponse& aResponse, TUint aVersion, IDvInvocationResponseUint& aValueUint);
    void SetInt(IDvInvocationResponse& aResponse, TUint aVersion, TInt aValueInt);
    void GetInt(IDvInvocationResponse& aResponse, TUint aVersion, IDvInvocationResponseInt& aValueInt);
    void SetBool(IDvInvocationResponse& aResponse, TUint aVersion, TBool aValueBool);
    void GetBool(IDvInvocationResponse& aResponse, TUint aVersion, IDvInvocationResponseBool& aValueBool);
    void SetMultiple(IDvInvocationResponse& aResponse, TUint aVersion, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void SetString(IDvInvocationResponse& aResponse, TUint aVersion, const Brx& aValueStr);
    void GetString(IDvInvocationResponse& aResponse, TUint aVersion, IDvInvocationResponseString& aValueStr);
    void SetBinary(IDvInvocationResponse& aResponse, TUint aVersion, const Brx& aValueBin);
    void GetBinary(IDvInvocationResponse& aResponse, TUint aVersion, IDvInvocationResponseBinary& aValueBin);
    void WriteFile(IDvInvocationResponse& aResponse, TUint aVersion, const Brx& aData, const Brx& aFileFullName);
    void Shutdown(IDvInvocationResponse& aResponse, TUint aVersion);
};

class DeviceBasic : public IResourceManager
{
public:
    DeviceBasic(const Brx& aConfigDir);
    ~DeviceBasic();
private:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
private:
    DvDeviceStandard* iDevice;
    ProviderTestBasic* iTestBasic;
    Brh iConfigDir;
};


ProviderTestBasic::ProviderTestBasic(DvDevice& aDevice)
    : DvProviderOpenhomeOrgTestBasic1(aDevice)
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
    EnableActionWriteFile();
    EnableActionShutdown();
}

void ProviderTestBasic::Increment(IDvInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValue, IDvInvocationResponseUint& aResult)
{
    aResponse.Start();
    aResult.Write(++aValue);
    aResponse.End();
}

void ProviderTestBasic::Decrement(IDvInvocationResponse& aResponse, TUint /*aVersion*/, TInt aValue, IDvInvocationResponseInt& aResult)
{
    aResponse.Start();
    aResult.Write(--aValue);
    aResponse.End();
}

void ProviderTestBasic::Toggle(IDvInvocationResponse& aResponse, TUint /*aVersion*/, TBool aValue, IDvInvocationResponseBool& aResult)
{
    aResponse.Start();
    aResult.Write(!aValue);
    aResponse.End();
}

void ProviderTestBasic::EchoString(IDvInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValue, IDvInvocationResponseString& aResult)
{
    aResponse.Start();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::EchoBinary(IDvInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValue, IDvInvocationResponseBinary& aResult)
{
    aResponse.Start();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::SetUint(IDvInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValueUint)
{
    SetPropertyVarUint(aValueUint);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetUint(IDvInvocationResponse& aResponse, TUint /*aVersion*/, IDvInvocationResponseUint& aValueUint)
{
    aResponse.Start();
    TUint val;
    GetPropertyVarUint(val);
    aValueUint.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetInt(IDvInvocationResponse& aResponse, TUint /*aVersion*/, TInt aValueInt)
{
    SetPropertyVarInt(aValueInt);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetInt(IDvInvocationResponse& aResponse, TUint /*aVersion*/, IDvInvocationResponseInt& aValueInt)
{
    aResponse.Start();
    TInt val;
    GetPropertyVarInt(val);
    aValueInt.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetBool(IDvInvocationResponse& aResponse, TUint /*aVersion*/, TBool aValueBool)
{
    SetPropertyVarBool(aValueBool);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetBool(IDvInvocationResponse& aResponse, TUint /*aVersion*/, IDvInvocationResponseBool& aValueBool)
{
    aResponse.Start();
    TBool val;
    GetPropertyVarBool(val);
    aValueBool.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetMultiple(IDvInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    PropertiesLock();
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    PropertiesUnlock();
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::SetString(IDvInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValueStr)
{
    SetPropertyVarStr(aValueStr);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetString(IDvInvocationResponse& aResponse, TUint /*aVersion*/, IDvInvocationResponseString& aValueStr)
{
    aResponse.Start();
    Brhz val;
    GetPropertyVarStr(val);
    aValueStr.Write(val);
    aValueStr.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::SetBinary(IDvInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValueBin)
{
    SetPropertyVarBin(aValueBin);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetBinary(IDvInvocationResponse& aResponse, TUint /*aVersion*/, IDvInvocationResponseBinary& aValueBin)
{
    aResponse.Start();
    Brh val;
    GetPropertyVarBin(val);
    aValueBin.Write(val);
    aValueBin.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::WriteFile(IDvInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aData, const Brx& aFileFullName)
{
    TUint len = aFileFullName.Bytes();
    char* name = (char*)malloc(len+1);
    (void)memcpy(name, aFileFullName.Ptr(), aFileFullName.Bytes());
    name[len] = 0;
    FILE* fp = fopen(name, "wb");
    free(name);
    (void)fwrite(aData.Ptr(), aData.Bytes(), 1, fp);
    (void)fflush(fp);
    (void)fclose(fp);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::Shutdown(IDvInvocationResponse& aResponse, TUint /*aVersion*/)
{
    aResponse.Start();
    aResponse.End();
    putchar('q');
}


DeviceBasic::DeviceBasic(const Brx& aConfigDir)
    : iConfigDir(aConfigDir)
{
    iDevice = new DvDeviceStandard(Brn("device-ohNetTestBasic"), *this);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "_ohNetTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ModelName", "ohNet test device");
    iTestBasic = new ProviderTestBasic(*iDevice);
    iDevice->SetEnabled();
}

DeviceBasic::~DeviceBasic()
{
    delete iTestBasic;
    delete iDevice;
}

void DeviceBasic::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, std::vector<char*>& /*aLanguageList*/, IResourceWriter& aResourceWriter)
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
                mime = kOhNetMimeTypeHtml;
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


void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
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

    if (loopback.Value()) {
        aInitParams->SetUseLoopbackNetworkAdapter();
    }
    aInitParams->SetDvNumWebSocketThreads(5);
    aInitParams->SetDvWebSocketPort(54321);
    UpnpLibrary::Initialise(aInitParams);
    Debug::SetLevel(Debug::kDvWebSocket | Debug::kError);
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
