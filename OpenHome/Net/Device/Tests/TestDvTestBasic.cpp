#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include "TestBasicDv.h"
#include <OpenHome/Net/Core/DvStack.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Private/DviProviderSubscriptionLongPoll.h>
#include <OpenHome/Private/File.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class DeviceTestBasic : public IResourceManager
{
public:
    DeviceTestBasic(DvStack& aDvStack, const Brx& aConfigDir);
    ~DeviceTestBasic();
private:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
private:
    DvDeviceStandard* iDevice;
    ProviderTestBasic* iTestBasic;
    Brh iConfigDir;
};



DeviceTestBasic::DeviceTestBasic(DvStack& aDvStack, const Brx& aConfigDir)
    : iConfigDir(aConfigDir)
{
    iDevice = new DvDeviceStandard(aDvStack, Brn("device-ohNetTestBasic"), *this);
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

DeviceTestBasic::~DeviceTestBasic()
{
    delete iTestBasic;
    delete iDevice;
}

void DeviceTestBasic::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, std::vector<char*>& /*aLanguageList*/, IResourceWriter& aResourceWriter)
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

    IFile* filePtr = NULL;

    const char* path = (const char*)filePath.Ptr();
    try {
        filePtr = IFile::Open(path, eFileReadOnly);
    }
    catch ( FileOpenError ) {
        return;
    }

    static const TUint kMaxReadSize = 4096;
    TUint bytes = filePtr->Bytes();
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
        Bws<kMaxReadSize> buf;
        TUint size = (bytes<kMaxReadSize? bytes : kMaxReadSize);
        filePtr->Read(buf, size);
        ASSERT(buf.Bytes() == size);
        aResourceWriter.WriteResource(buf.Ptr(), buf.Bytes());
        bytes -= size;
    } while (bytes > 0);
    aResourceWriter.WriteResourceEnd();
    delete filePtr;
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
    Library* lib = new Library(aInitParams);
    Debug::SetLevel(Debug::kDvWebSocket | Debug::kDvInvocation | Debug::kDvEvent | Debug::kDvDevice);
    Debug::SetSeverity(Debug::kSeverityError);
    
    DvStack* dvStack = lib->StartDv();

    Print("TestDvTestBasic - starting ('q' to quit)\n");
    DeviceTestBasic* device = new DeviceTestBasic(*dvStack, config.Value());
    while (getchar() != 'q') {
        ;
    }
    delete device;
    Print("TestDvTestBasic - exiting\n");

    delete lib;
}
