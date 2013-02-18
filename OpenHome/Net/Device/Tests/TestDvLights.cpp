#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestLights1.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/MimeTypes.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/File.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

#define MAKE_COLOR(r,g,b,a) (TUint)(a<<24 | r<<16 | g<<8 | b)

class Light : private INonCopyable
{
public:
    Light(const TChar* aRoom, const TChar* aName, TUint aPosX, TUint aPosY, TUint aPosZ, TUint aColor);
    const Brx& Room() const { return iRoom; }
    const Brx& Name() const { return iName; }
    TUint PosX() const { return iPosX; }
    TUint PosY() const { return iPosY; }
    TUint PosZ() const { return iPosZ; }
    TUint Color() const { return iColor; }
    void SetColor(TUint aColor) { iColor = aColor; }
private:
    Brh iRoom;
    Brh iName;
    TUint iPosX;
    TUint iPosY;
    TUint iPosZ;
    TUint iColor;
};

Light::Light(const TChar* aRoom, const TChar* aName, TUint aPosX, TUint aPosY, TUint aPosZ, TUint aColor)
    : iRoom(aRoom)
    , iName(aName)
    , iPosX(aPosX)
    , iPosY(aPosY)
    , iPosZ(aPosZ)
    , iColor(aColor)
{
}


class ProviderLights : public DvProviderOpenhomeOrgTestLights1
{
public:
    ProviderLights(DvDevice& aDevice, TUint aMode);
    ~ProviderLights();
private:
    void InitMode1();
    void InitMode2();
    void InitMode3();
private:
    void GetCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aCount);
    void GetRoom(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aRoomName);
    void GetName(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aFriendlyName);
    void GetPosition(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseUint& aX, IDvInvocationResponseUint& aY, IDvInvocationResponseUint& aZ);
    void SetColor(IDvInvocation& aInvocation, TUint aIndex, TUint aColor);
    void GetColor(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseUint& aColor);
    void GetColorComponents(IDvInvocation& aInvocation, TUint aColor, IDvInvocationResponseUint& aBrightness, IDvInvocationResponseUint& aRed, IDvInvocationResponseUint& aGreen, IDvInvocationResponseUint& aBlue);
private:
    std::vector<Light*> iLights;
};

class DeviceLights : public IResourceManager
{
public:
    DeviceLights(TUint aMode, const Brx& aConfigDir);
    ~DeviceLights();
private:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
private:
    DvDeviceStandard* iDevice;
    ProviderLights* iLights;
    Brh iConfigDir;
};


ProviderLights::ProviderLights(DvDevice& aDevice, TUint aMode)
    : DvProviderOpenhomeOrgTestLights1(aDevice)
{
    EnableActionGetCount();
    EnableActionGetRoom();
    EnableActionGetName();
    EnableActionGetPosition();
    EnableActionSetColor();
    EnableActionGetColor();
    EnableActionGetColorComponents();

    switch (aMode)
    {
    case 1:
        InitMode1();
        break;
    case 2:
        InitMode2();
        break;
    case 3:
        InitMode3();
        break;
    default:
        ASSERTS();
        break;
    }
}

ProviderLights::~ProviderLights()
{
    for (TUint i=0; i<iLights.size(); i++) {
        delete iLights[i];
    }
}

void ProviderLights::InitMode1()
{
    iLights.push_back(new Light("Lounge", "Ceiling1", 150, 180, 200, MAKE_COLOR(255, 255, 255, 255)));
    iLights.push_back(new Light("Lounge", "Ceiling2", 650, 180, 200, MAKE_COLOR(128, 255, 255, 255)));
    iLights.push_back(new Light("Lounge", "Reading", 400, 30, 135, MAKE_COLOR(0, 255, 255, 255)));
}

void ProviderLights::InitMode2()
{
    iLights.push_back(new Light("Lounge", "Ceiling1", 150, 180, 200, MAKE_COLOR(255, 255, 255, 255)));
    iLights.push_back(new Light("Lounge", "Ceiling2", 650, 180, 200, MAKE_COLOR(128, 255, 255, 255)));
    iLights.push_back(new Light("Lounge", "Reading", 400, 30, 135, MAKE_COLOR(0, 255, 255, 255)));
    iLights.push_back(new Light("Kitchen", "Kitchen", 160, 120, 200, MAKE_COLOR(0, 255, 255, 255)));
    iLights.push_back(new Light("Hall", "Hall", 120, 60, 200, MAKE_COLOR(0, 255, 255, 255)));
}

void ProviderLights::InitMode3()
{
    iLights.push_back(new Light("Lounge", "Ceiling1", 150, 180, 200, MAKE_COLOR(255, 255, 255, 255)));
    iLights.push_back(new Light("Lounge", "Ceiling2", 650, 180, 200, MAKE_COLOR(128, 255, 255, 255)));
    iLights.push_back(new Light("Lounge", "Reading", 400, 30, 135, MAKE_COLOR(0, 255, 255, 255)));
    iLights.push_back(new Light("Kitchen", "Kitchen", 160, 120, 200, MAKE_COLOR(0, 255, 255, 255)));
    iLights.push_back(new Light("Hall", "Hall", 120, 60, 200, MAKE_COLOR(0, 255, 255, 255)));
    iLights.push_back(new Light("Bedroom1", "Ceiling", 225, 150, 200, MAKE_COLOR(64, 32, 32, 255)));
    iLights.push_back(new Light("Bedroom1", "Bedside1", 90, 15, 100, MAKE_COLOR(0, 255, 255, 255)));
    iLights.push_back(new Light("Bedroom1", "Bedside2", 360, 15, 100, MAKE_COLOR(0, 255, 255, 255)));
    iLights.push_back(new Light("Bedroom2", "Ceiling", 150, 150, 200, MAKE_COLOR(0, 255, 255, 255)));
}

void ProviderLights::GetCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aCount)
{
    aInvocation.StartResponse();
    aCount.Write((TUint)iLights.size());
    aInvocation.EndResponse();
}

void ProviderLights::GetRoom(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aRoomName)
{
    Light* light = iLights[aIndex];
    aInvocation.StartResponse();
    aRoomName.Write(light->Room());
    aRoomName.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderLights::GetName(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aFriendlyName)
{
    Light* light = iLights[aIndex];
    aInvocation.StartResponse();
    aFriendlyName.Write(light->Name());
    aFriendlyName.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderLights::GetPosition(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseUint& aX, IDvInvocationResponseUint& aY, IDvInvocationResponseUint& aZ)
{
    Light* light = iLights[aIndex];
    aInvocation.StartResponse();
    aX.Write(light->PosX());
    aY.Write(light->PosY());
    aZ.Write(light->PosZ());
    aInvocation.EndResponse();
}

void ProviderLights::SetColor(IDvInvocation& aInvocation, TUint aIndex, TUint aColor)
{
    Light* light = iLights[aIndex];
    light->SetColor(aColor);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderLights::GetColor(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseUint& aColor)
{
    Light* light = iLights[aIndex];
    aInvocation.StartResponse();
    aColor.Write(light->Color());
    aInvocation.EndResponse();
}

void ProviderLights::GetColorComponents(IDvInvocation& aInvocation, TUint aColor, IDvInvocationResponseUint& aBrightness, IDvInvocationResponseUint& aRed, IDvInvocationResponseUint& aGreen, IDvInvocationResponseUint& aBlue)
{
    aInvocation.StartResponse();
    aBrightness.Write(aColor>>24);
    aRed.Write((aColor>>16)&0xff);
    aGreen.Write((aColor>>8)&0xff);
    aBlue.Write(aColor&0xff);
    aInvocation.EndResponse();
}


static Bwh gDeviceName("device");

static void RandomiseUdn(Bwh& aUdn)
{
#if 0
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    std::vector<NetworkAdapter*>* subnetList = gEnv->NetworkAdapterList().CreateSubnetList();
    TUint max = (*subnetList)[0]->Address();
    TUint seed = gDvStack->ServerUpnp().Port((*subnetList)[0]->Address());
    SetRandomSeed(seed);
    gEnv->NetworkAdapterList().DestroySubnetList(subnetList);
    (void)Ascii::AppendDec(buf, Random(max));
    aUdn.Append(buf);
    aUdn.PtrZ();
#else
    // !!!! temp hack to simplify Craig's 2 day trial
    const Brn name("-lights-Ws");
    aUdn.Grow(aUdn.Bytes() + name.Bytes() + 1);
    aUdn.Append(name);
    aUdn.PtrZ();
#endif
}

DeviceLights::DeviceLights(TUint aMode, const Brx& aConfigDir)
    : iConfigDir(aConfigDir)
{
    RandomiseUdn(gDeviceName);
    iDevice = new DvDeviceStandard(*gDvStack, gDeviceName, *this);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "TestLights");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "ohNet Lights");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ModelName", "ohNet Lights v1");
    iLights = new ProviderLights(*iDevice, aMode);
    iDevice->SetEnabled();
}

DeviceLights::~DeviceLights()
{
    delete iLights;
    delete iDevice;
}

void DeviceLights::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, std::vector<char*>& /*aLanguageList*/, IResourceWriter& aResourceWriter)
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
            static const char* mimeMappings[][2] = {{"html", kOhNetMimeTypeHtml}
                                                   ,{"htm",  kOhNetMimeTypeHtml}
                                                   ,{"jpg",  kOhNetMimeTypeJpeg}
                                                   ,{"jpeg", kOhNetMimeTypeJpeg}
                                                   ,{"gif",  kOhNetMimeTypeGif}
                                                   ,{"png",  kOhNetMimeTypePng}
                                                   ,{"bmp",  kOhNetMimeTypeBmp}
                                                   ,{"xml",  kOhNetMimeTypeXml}
                                                   ,{"js",   kOhNetMimeTypeJs}
                                                   ,{"css",  kOhNetMimeTypeCss}
                                                   ,{NULL ,  NULL}};
            const char* ext = (const char*)filePath.Split(i+1, filePath.Bytes()-i-1).Ptr();
            TUint index = 0;
            while (mimeMappings[index][0] != NULL) {
                if (strcmp(ext, mimeMappings[index][0]) == 0) {
                    mime = mimeMappings[index][1];
                    break;
                }
                index++;
            }
            break;
        }
    }
    Print("selected mime %s\n", mime);
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
    OptionUint mode("-m", "--mode", 1, "[1..3] select from list of hard-coded lighting systems");
    parser.AddOption(&mode);
    Brn emptyString("");
    OptionString config("-c", "--config", emptyString, "[full dir path] to folder containing web UI");
    parser.AddOption(&config);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (config.Value().Bytes()==0 || mode.Value()==0 || mode.Value()>3) {
        parser.DisplayHelp();
        return;
    }

    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartDv();
    Debug::SetLevel(Debug::kError);

    Print("TestDvLights - starting\n");
    DeviceLights* device = new DeviceLights(mode.Value(), config.Value());
    while (getchar() != 'q') {
        ;
    }
    delete device;
    Print("TestDvLights - exiting\n");

    UpnpLibrary::Close();
}
