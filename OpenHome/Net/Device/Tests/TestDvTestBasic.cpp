#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/DvStack.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Private/DviProviderSubscriptionLongPoll.h>

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
    void Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult);
    void Decrement(IDvInvocation& aInvocation, TInt aValue, IDvInvocationResponseInt& aResult);
    void Toggle(IDvInvocation& aInvocation, TBool aValue, IDvInvocationResponseBool& aResult);
    void EchoString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult);
    void EchoBinary(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseBinary& aResult);
    void SetUint(IDvInvocation& aInvocation, TUint aValueUint);
    void GetUint(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint);
    void SetInt(IDvInvocation& aInvocation, TInt aValueInt);
    void GetInt(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValueInt);
    void SetBool(IDvInvocation& aInvocation, TBool aValueBool);
    void GetBool(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValueBool);
    void SetMultiple(IDvInvocation& aInvocation, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void SetString(IDvInvocation& aInvocation, const Brx& aValueStr);
    void GetString(IDvInvocation& aInvocation, IDvInvocationResponseString& aValueStr);
    void SetBinary(IDvInvocation& aInvocation, const Brx& aValueBin);
    void GetBinary(IDvInvocation& aInvocation, IDvInvocationResponseBinary& aValueBin);
    void WriteFile(IDvInvocation& aInvocation, const Brx& aData, const Brx& aFileFullName);
    void Shutdown(IDvInvocation& aInvocation);
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
    EnablePropertyVarUint();
    EnablePropertyVarInt();
    EnablePropertyVarBool();
    EnablePropertyVarStr();
    EnablePropertyVarBin();
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

void ProviderTestBasic::Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(++aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::Decrement(IDvInvocation& aInvocation, TInt aValue, IDvInvocationResponseInt& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(--aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::Toggle(IDvInvocation& aInvocation, TBool aValue, IDvInvocationResponseBool& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(!aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::EchoString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::EchoBinary(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseBinary& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetUint(IDvInvocation& aInvocation, TUint aValueUint)
{
    SetPropertyVarUint(aValueUint);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetUint(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint)
{
    aInvocation.StartResponse();
    TUint val;
    GetPropertyVarUint(val);
    aValueUint.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetInt(IDvInvocation& aInvocation, TInt aValueInt)
{
    SetPropertyVarInt(aValueInt);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetInt(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValueInt)
{
    aInvocation.StartResponse();
    TInt val;
    GetPropertyVarInt(val);
    aValueInt.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetBool(IDvInvocation& aInvocation, TBool aValueBool)
{
    SetPropertyVarBool(aValueBool);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetBool(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValueBool)
{
    aInvocation.StartResponse();
    TBool val;
    GetPropertyVarBool(val);
    aValueBool.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetMultiple(IDvInvocation& aInvocation, TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    PropertiesLock();
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    PropertiesUnlock();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetString(IDvInvocation& aInvocation, const Brx& aValueStr)
{
    SetPropertyVarStr(aValueStr);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetString(IDvInvocation& aInvocation, IDvInvocationResponseString& aValueStr)
{
    aInvocation.StartResponse();
    Brhz val;
    GetPropertyVarStr(val);
    aValueStr.Write(val);
    aValueStr.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetBinary(IDvInvocation& aInvocation, const Brx& aValueBin)
{
    SetPropertyVarBin(aValueBin);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetBinary(IDvInvocation& aInvocation, IDvInvocationResponseBinary& aValueBin)
{
    aInvocation.StartResponse();
    Brh val;
    GetPropertyVarBin(val);
    aValueBin.Write(val);
    aValueBin.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::WriteFile(IDvInvocation& aInvocation, const Brx& aData, const Brx& aFileFullName)
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
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::Shutdown(IDvInvocation& aInvocation)
{
    aInvocation.StartResponse();
    aInvocation.EndResponse();
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
    iDevice->SetAttribute("Core.LongPollEnable", "");
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
    aInitParams->SetDvWebSocketPort(54320);
    aInitParams->SetDvUpnpServerPort(0);
    UpnpLibrary::Initialise(aInitParams);
    Debug::SetLevel(Debug::kDvWebSocket | Debug::kError | Debug::kDvInvocation | Debug::kDvEvent | Debug::kDvDevice);
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
