#include "TestMediaPlayer.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/KvpStore.h>
#include "RamStore.h"
#include <OpenHome/Av/UpnpAv/UpnpAv.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>
#include <OpenHome/Av/Utils/IconDriverSongcastSender.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Net/Private/ShellCommandDebug.h>
#include <OpenHome/Private/Parser.h>

#include "openssl/bio.h"
#include "openssl/pem.h"

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

// TestMediaPlayer

const Brn TestMediaPlayer::kSongcastSenderIconFileName("SongcastSenderIcon");

TestMediaPlayer::TestMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, const TChar* aTuneInUserName, const Brx& aTidalId, IPullableClock* aPullableClock)
    : iDisabled("test", 0)
    , iSongcastTimestamper(aDvStack.Env())
    , iTidalId(aTidalId)
{
    Debug::SetLevel(Debug::kEvent);
    Bws<256> friendlyName;
    friendlyName.Append(aRoom);
    friendlyName.Append(':');
    friendlyName.Append(aProductName);

    // create UPnP device
    iDevice = new DvDeviceStandard(aDvStack, aUdn, *this);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Source");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", friendlyName.PtrZ());
    iDevice->SetAttribute("Upnp.Manufacturer", "OpenHome");
    iDevice->SetAttribute("Upnp.ModelName", "TestMediaPlayer");

    // create separate UPnP device for standard MediaRenderer
    Bws<256> buf(aUdn);
    buf.Append("-MediaRenderer");
    // The renderer name should be <room name>:<UPnP AV source name> to allow
    // our control point to match the renderer device to the upnp av source.
    //
    // FIXME - will have to allow this to be dynamically changed at runtime if
    // someone changes the name of the UPnP AV source.
    // Disable device -> change name -> re-enable device.
    Bws<256> rendererName(aRoom);
    rendererName.Append(":");
    rendererName.Append(SourceUpnpAv::kSourceName);
    iDeviceUpnpAv = new DvDeviceStandard(aDvStack, buf);
    iDeviceUpnpAv->SetAttribute("Upnp.Domain", "upnp.org");
    iDeviceUpnpAv->SetAttribute("Upnp.Type", "MediaRenderer");
    iDeviceUpnpAv->SetAttribute("Upnp.Version", "1");
    friendlyName.Append(":MediaRenderer");
    iDeviceUpnpAv->SetAttribute("Upnp.FriendlyName", rendererName.PtrZ());
    iDeviceUpnpAv->SetAttribute("Upnp.Manufacturer", "OpenHome");
    iDeviceUpnpAv->SetAttribute("Upnp.ModelName", "TestMediaPlayer");

    // create read/write store.  This creates a number of static (constant) entries automatically
    // FIXME - to be removed; this only exists to populate static data
    iRamStore = new RamStore();

    // create a read/write store using the new config framework
    iConfigRamStore = new ConfigRamStore();

    // FIXME - available store keys should be listed somewhere
    iConfigRamStore->Write(Brn("Product.Room"), Brn(aRoom));
    iConfigRamStore->Write(Brn("Product.Name"), Brn(aProductName));
    iConfigRamStore->Write(Brn("Radio.TuneInUserName"), Brn(aTuneInUserName));

    // create MediaPlayer
    iMediaPlayer = new MediaPlayer(aDvStack, *iDevice, *iRamStore, *iConfigRamStore, aPullableClock);
    iPipelineObserver = new LoggingPipelineObserver();
    iMediaPlayer->Pipeline().AddObserver(*iPipelineObserver);

    // register our PowerDownUpnp function with the PowerManager
    IPowerManager& powerManager = iMediaPlayer->PowerManager();
    iPowerObserver = powerManager.Register(*this, kPowerPriorityLowest);

    // create a shell
    iShell = new Shell(aDvStack.Env(), 0);
    Log::Print("Shell running on port %u\n", iShell->Port());
    iShellDebug = new ShellCommandDebug(*iShell);
}

TestMediaPlayer::~TestMediaPlayer()
{
    delete iPowerObserver;
    ASSERT(!iDevice->Enabled());
    delete iMediaPlayer;
    delete iPipelineObserver;
    delete iShellDebug;
    delete iShell;
    delete iDevice;
    delete iDeviceUpnpAv;
    delete iRamStore;
    delete iConfigRamStore;
}

void TestMediaPlayer::StopPipeline()
{
    TUint waitCount = 0;
    if (TryDisable(*iDevice)) {
        waitCount++;
    }
    if (TryDisable(*iDeviceUpnpAv)) {
        waitCount++;
    }
    while (waitCount > 0) {
        iDisabled.Wait();
        waitCount--;
    }
    iMediaPlayer->Quit();
}

void TestMediaPlayer::AddAttribute(const TChar* aAttribute)
{
    iMediaPlayer->AddAttribute(aAttribute);
}

void TestMediaPlayer::Run()
{
    RegisterPlugins(iMediaPlayer->Env());
    iMediaPlayer->Start();
    iDevice->SetEnabled();
    iDeviceUpnpAv->SetEnabled();

    iConfigRamStore->Print();

    Log::Print("\nFull (software) media player\n");
    Log::Print("Intended to be controlled via a separate, standard CP (Kinsky etc.)\n");

    Log::Print("Press <q> followed by <enter> to quit:\n");
    Log::Print("\n");
    while (getchar() != 'q')    // getchar catches stdin, getch does not.....
        ;

    //IPowerManager& powerManager = iMediaPlayer->PowerManager();
    //powerManager.PowerDown(); // FIXME - this should probably be replaced by a normal shutdown procedure
    iConfigRamStore->Print();
}

PipelineManager& TestMediaPlayer::Pipeline()
{
    return iMediaPlayer->Pipeline();
}

DvDeviceStandard* TestMediaPlayer::Device()
{
    return iDevice;
}

void TestMediaPlayer::RegisterPlugins(Environment& aEnv)
{
    const Brn kSupportedProtocols( 
        "http-get:*:audio/x-flac:*,"    // Flac
        "http-get:*:audio/wav:*,"       // Wav
        "http-get:*:audio/wave:*,"      // Wav
        "http-get:*:audio/x-wav:*,"     // Wav
        "http-get:*:audio/aiff:*,"      // AIFF
        "http-get:*:audio/x-aiff:*,"    // AIFF
        "http-get:*:audio/x-m4a:*,"     // Alac
        "http-get:*:audio/x-scpls:*,"   // M3u (content processor)
        "http-get:*:text/xml:*,"        // Opml ??  (content processor)
        "http-get:*:audio/aac:*,"       // Aac
        "http-get:*:audio/aacp:*,"      // Aac
        "http-get:*:audio/mp4:*,"       // Mpeg4 (container)
        "http-get:*:audio/ogg:*,"       // Vorbis
        "http-get:*:audio/x-ogg:*,"     // Vorbis
        "http-get:*:application/ogg:*," // Vorbis
        "tidalhifi.com:*:*:*,"          // Tidal
        );
    DoRegisterPlugins(aEnv, kSupportedProtocols);
}

// FIXME - DO NOT use this with production code
/* Should ideally generate a key at runtime instead, avoiding the possibility
   of someone viewing RO data for any rom image and gaining access to the private
   key for all of a manufacturer's devices */
static const Brn kPrivKey(
    "-----BEGIN RSA PRIVATE KEY-----\n"
    "MIIEpAIBAAKCAQEAmjVvXIDRvQ7lwY67haxeLtNJTz08+3daJCbMa1KkZygI5XFp\n"
    "CQLLDdnzCaXSTtqvs4Qew36hsujwOCpPP55SbJlTU0cQRDIINuWz8tpZOvvDjLJz\n"
    "msP0ZGysypJH8D5Imy4IIUi4iRKPtQIXF0ziFkchTW0xoLQBaRfrqvp5Mp7ivxOu\n"
    "cqOcaOzeEhHkT77u7OxZabCgW4QKz9Jvn9rfO50Pc3vOOqTrdTWm0Vlmu2yugncO\n"
    "knfm5RiTlp77d7oPo+9o19zs4eYlOyaM0EkpERSgrvxh6qUE67lEom97TQW9ZuUg\n"
    "EPPRAtCJpNoL4NTTckGA7qyNoR2UVw6xv3pLnwIDAQABAoIBAQCRVLKy9ySzjIqz\n"
    "tBS+kgfhEXcRmqESTRVC5N3ad3RBU9Wuhwd6WouLblBCU2i0sBzOjkF/9KPnvOhH\n"
    "xngReOAtQQLqhRqraoubUTgaM/XMROGyg6u3u91jl5fxAZOSsuAyf1tiIurnI/sT\n"
    "l/izGN4qKLcWBUa0MXDy3nxYEt6N+QEVN2X+8MugjlgygA7weKamtkSBImJWZMjc\n"
    "FcOiJe/NWKT3CPoGFeTyVEN/Nu0CbHACM4AHmEZ0q3jGv86UAEaEsMipuYawTNQU\n"
    "LwqMJX4Kpr4LL7uq2f39Nltx164crZfHLU2kxT7jOZGp2eHEXb5X4HKJDy1yWmq9\n"
    "c/I758vhAoGBAMthLiG5zmO1LOVBjhLsqQboZTs4G1CYINRXM1jznC7sElSBGvjY\n"
    "t2ycV6UESur78zuPw9qbogqHGrwPvsjXMW+KHdbQgh85LH+fWS1NDK3d+I+PZPgJ\n"
    "aTg6wTzX/Q5lL/SykuKha4VtLXxzIOsqiB5ngIbiwAc24/qZKiY9lnM7AoGBAMIb\n"
    "bbOfr+yUzgtptLy+Y53pQEtw3uzyoByFZKXeOYqDVWbf81990Hghsd2T2SFm727x\n"
    "Bw0wafAka6Pj0QnxQ0OVr1yiGKJHvRgEiXQGR0PoRIivU3oEbKe00FZGrcd+OgDr\n"
    "37DNTyXl4Oetha8aE1TxKRWYU438PSkaXFCNXvrtAoGBAMRTa1TjKHjXzB8CyUM7\n"
    "cW9Zp18jKjsCn65a/xY/E+W3vXoVpxPRID+YLIL/QdLUpFg6z7WXxzSidwxTprf6\n"
    "A57IlUVowjOh3XLVQCCa4EJ2pBrxMWa+rvO4xBEX7xCWXVS5jVF4wXJrkh0whfZ9\n"
    "eCjhgRC0kupj8m9Wq3l+ul1BAoGAcAkq2YmrHi+JefbqViLCFswhyyl70mH8Xln0\n"
    "DPTmW3eQnI9Yxt40rJIuOolywx/JxUwjWM5/5xbudisxZb62p1THYf1BoLEtiKZd\n"
    "u/U/vwdaP1aLJRtWp7nqolGrTkEiM5PxifgG3gYAOVjjl3zCeb20i/1fBM35czb+\n"
    "35OppcUCgYABdBgxnK6F3sl5ORk6V74aI3lhLdGyXZ06JX2/kjl47ICcJoYwExKK\n"
    "CB2RFnTL4wErJ/sBMm5WaWEl6p0eSul746dEXYotSmqfTZguytJ2cDGjsNw337MP\n"
    "bRNucN3L34/su+MowI8M/eShq4nfKLLw3TWor2EKzS0QGHy3DGrSmg==\n"
    "-----END RSA PRIVATE KEY-----"
    );

static const char kPubKey[] =
    "-----BEGIN PUBLIC KEY-----\n"
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAmjVvXIDRvQ7lwY67haxe\n"
    "LtNJTz08+3daJCbMa1KkZygI5XFpCQLLDdnzCaXSTtqvs4Qew36hsujwOCpPP55S\n"
    "bJlTU0cQRDIINuWz8tpZOvvDjLJzmsP0ZGysypJH8D5Imy4IIUi4iRKPtQIXF0zi\n"
    "FkchTW0xoLQBaRfrqvp5Mp7ivxOucqOcaOzeEhHkT77u7OxZabCgW4QKz9Jvn9rf\n"
    "O50Pc3vOOqTrdTWm0Vlmu2yugncOknfm5RiTlp77d7oPo+9o19zs4eYlOyaM0Ekp\n"
    "ERSgrvxh6qUE67lEom97TQW9ZuUgEPPRAtCJpNoL4NTTckGA7qyNoR2UVw6xv3pL\n"
    "nwIDAQAB\n"
    "-----END PUBLIC KEY-----\n";

static void EncryptAndSetConfigVal(RSA* aPublicKey, ConfigText& aConfigText, const Brx& aVal)
{
    ASSERT(aVal.Bytes() > 0);
    Bws<256> src(aVal);
    src.PtrZ();
    Bws<256> encrypted;
    int encryptedLen = RSA_public_encrypt(src.Bytes(), src.Ptr(), const_cast<TByte*>(encrypted.Ptr()), aPublicKey, RSA_PKCS1_OAEP_PADDING);
    ASSERT(encryptedLen > 0);
    encrypted.SetBytes(encryptedLen);
    aConfigText.Set(encrypted);
}

void TestMediaPlayer::DoRegisterPlugins(Environment& aEnv, const Brx& aSupportedProtocols)
{
    // Add codecs
    iMediaPlayer->Add(Codec::CodecFactory::NewAac());
    iMediaPlayer->Add(Codec::CodecFactory::NewAiff());
    iMediaPlayer->Add(Codec::CodecFactory::NewAifc());
    iMediaPlayer->Add(Codec::CodecFactory::NewAlac());
    iMediaPlayer->Add(Codec::CodecFactory::NewAdts());
    iMediaPlayer->Add(Codec::CodecFactory::NewFlac());
    iMediaPlayer->Add(Codec::CodecFactory::NewVorbis());
    iMediaPlayer->Add(Codec::CodecFactory::NewWav());

    // Add protocol modules (Radio source can require several stacked Http instances)
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    // only add Tidal if we have credible login details
    if (iTidalId.Bytes() > 0) {
        Parser parser(iTidalId);
        Brn token = parser.Next(':');
        Brn username = parser.Next(':');
        Brn password = parser.Remaining();
        iMediaPlayer->Add(ProtocolFactory::NewTidal(aEnv, token, kPrivKey, iMediaPlayer->ConfigManagerInitialiser()));
        IConfigManagerReader& configMgr = iMediaPlayer->ConfigManagerReader();
        BIO* bio = BIO_new_mem_buf((void*)kPubKey, sizeof(kPubKey)-1);
        RSA* pubKey = PEM_read_bio_RSA_PUBKEY(bio, NULL, 0, NULL);
        BIO_free(bio);
        EncryptAndSetConfigVal(pubKey, configMgr.GetText(Brn("Tidal.Username")), username);
        EncryptAndSetConfigVal(pubKey, configMgr.GetText(Brn("Tidal.Password")), password);
        RSA_free(pubKey);
    }

    // Add sources
    iMediaPlayer->Add(SourceFactory::NewPlaylist(*iMediaPlayer, aSupportedProtocols));
    iMediaPlayer->Add(SourceFactory::NewRadio(*iMediaPlayer, aSupportedProtocols));
    iMediaPlayer->Add(SourceFactory::NewUpnpAv(*iMediaPlayer, *iDeviceUpnpAv, aSupportedProtocols));

    Bwh hostName(iDevice->Udn().Bytes()+1); // space for null terminator
    hostName.Replace(iDevice->Udn());
    Bws<12> macAddr;
    MacAddrFromUdn(aEnv, macAddr);
    const TChar* friendlyName;
    iDevice->GetAttribute("Upnp.FriendlyName", &friendlyName);
    iMediaPlayer->Add(SourceFactory::NewRaop(*iMediaPlayer, hostName.PtrZ(), friendlyName, macAddr));

    iMediaPlayer->Add(SourceFactory::NewReceiver(*iMediaPlayer, iSongcastTimestamper, kSongcastSenderIconFileName)); // FIXME - will want to replace timestamper with access to a driver on embedded platforms
}



void TestMediaPlayer::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, std::vector<char*>& /*aLanguageList*/, IResourceWriter& aResourceWriter)
{
    if (aUriTail == kSongcastSenderIconFileName) {
        aResourceWriter.WriteResourceBegin(sizeof(kIconDriverSongcastSender), kIconDriverSongcastSenderMimeType);
        aResourceWriter.WriteResource(kIconDriverSongcastSender, sizeof(kIconDriverSongcastSender));
        aResourceWriter.WriteResourceEnd();
    }
}

void TestMediaPlayer::PowerUp()
{
    // FIXME - enable UPnP devices here?
    // - would need to account for two-stage create->run process either by
    //  - setting a flag here which is checked in Run() OR
    //  - registering with IPowerManager in Run() call
    //iDevice->SetEnabled();
    //iDeviceUpnpAv->SetEnabled();
}

void TestMediaPlayer::PowerDown()
{
    Log::Print("TestMediaPlayer::PowerDown\n");
    PowerDownDisable(*iDevice);
    PowerDownDisable(*iDeviceUpnpAv);
}

TUint TestMediaPlayer::Hash(const Brx& aBuf)
{
    TUint hash = 0;
    for (TUint i=0; i<aBuf.Bytes(); i++) {
        hash += aBuf[i];
    }
    return hash;
}

void TestMediaPlayer::GenerateMacAddr(Environment& aEnv, TUint aSeed, Bwx& aMacAddr)
{
    // Generate a 48-bit, 12-byte hex string.
    // Method:
    // - Generate two random numbers in the range 0 - 2^24
    // - Get the hex representation of these numbers
    // - Combine the two hex representations into the output buffer, aMacAddr
    const TUint maxLimit = 0x01000000;
    Bws<8> macBuf1;
    Bws<8> macBuf2;

    aEnv.SetRandomSeed(aSeed);
    TUint mac1 = aEnv.Random(maxLimit, 0);
    TUint mac2 = aEnv.Random(maxLimit, 0);

    Ascii::AppendHex(macBuf1, mac1);
    Ascii::AppendHex(macBuf2, mac2);

    aMacAddr.Append(macBuf1.Split(2));
    aMacAddr.Append(macBuf2.Split(2));
}

void TestMediaPlayer::MacAddrFromUdn(Environment& aEnv, Bwx& aMacAddr)
{
    TUint hash = Hash(iDevice->Udn());
    GenerateMacAddr(aEnv, hash, aMacAddr);
}

void TestMediaPlayer::PowerDownDisable(DvDevice& aDevice)
{
    if (aDevice.Enabled()) {
        aDevice.SetDisabled(MakeFunctor(*this, &TestMediaPlayer::PowerDownUpnpCallback));
    }
}

void TestMediaPlayer::PowerDownUpnpCallback()
{
    // do nothing; only exists to avoid lengthy Upnp shutdown waits during power fail
}

TBool TestMediaPlayer::TryDisable(DvDevice& aDevice)
{
    if (aDevice.Enabled()) {
        aDevice.SetDisabled(MakeFunctor(*this, &TestMediaPlayer::Disabled));
        return true;
    }
    return false;
}

void TestMediaPlayer::Disabled()
{
    iDisabled.Signal();
}


// TestMediaPlayerOptions

TestMediaPlayerOptions::TestMediaPlayerOptions()
    : iOptionRoom("-r", "--room", Brn(""), "room the Product service will report")
    , iOptionName("-n", "--name", Brn("SoftPlayer"), "Product name")
    , iOptionUdn("-u", "--udn", Brn(""), "Udn (optional - one will be generated if this is left blank)")
    , iOptionChannel("-c", "--channel", 0, "[0..65535] sender channel")
    , iOptionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use")
    , iOptionLoopback("-l", "--loopback", "Use loopback adapter")
    , iOptionTuneIn("-t", "--tunein", Brn("linnproducts"), "TuneIn user name")
    , iOptionTidal("", "--tidal", Brn(""), "Tidal login - token:username:password")
{
    iParser.AddOption(&iOptionRoom);
    iParser.AddOption(&iOptionName);
    iParser.AddOption(&iOptionUdn);
    iParser.AddOption(&iOptionChannel);
    iParser.AddOption(&iOptionAdapter);
    iParser.AddOption(&iOptionLoopback);
    iParser.AddOption(&iOptionTuneIn);
    iParser.AddOption(&iOptionTidal);
}

void TestMediaPlayerOptions::AddOption(Option* aOption)
{
    iParser.AddOption(aOption);
}

TBool TestMediaPlayerOptions::Parse(int aArgc, char* aArgv[])
{
    return iParser.Parse(aArgc, aArgv);
}

OptionString& TestMediaPlayerOptions::Room()
{
    return iOptionRoom;
}

OptionString& TestMediaPlayerOptions::Name()
{
    return iOptionName;
}

OptionString& TestMediaPlayerOptions::Udn()
{
    return iOptionUdn;
}

OptionUint& TestMediaPlayerOptions::Channel()
{
    return iOptionChannel;
}

OptionUint& TestMediaPlayerOptions::Adapter()
{
    return iOptionAdapter;
}

OptionBool& TestMediaPlayerOptions::Loopback()
{
    return iOptionLoopback;
}

OptionString& TestMediaPlayerOptions::TuneIn()
{
    return iOptionTuneIn;
}

OptionString& TestMediaPlayerOptions::Tidal()
{
    return iOptionTidal;
}


// TestMediaPlayerInit

OpenHome::Net::Library* TestMediaPlayerInit::CreateLibrary(TBool aLoopback, TUint aAdapter)
{
    InitialisationParams* initParams = InitialisationParams::Create();
    initParams->SetDvEnableBonjour();
    if (aLoopback == true) {
        initParams->SetUseLoopbackNetworkAdapter();
    }

//    Debug::SetLevel(Debug::kPipeline | Debug::kMedia);
    Net::Library* lib = new Net::Library(initParams);
    //Net::DvStack* dvStack = lib->StartDv();
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    const TUint adapterIndex = aAdapter;
    if (subnetList->size() <= adapterIndex) {
        Log::Print("ERROR: adapter %u doesn't exist\n", adapterIndex);
        ASSERTS();
    }
    Log::Print ("adapter list:\n");
    for (unsigned i=0; i<subnetList->size(); ++i) {
        TIpAddress addr = (*subnetList)[i]->Address();
        Log::Print ("  %d: %d.%d.%d.%d\n", i, addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    }
    //TIpAddress address = (*subnetList)[adapterIndex]->Address();
    TIpAddress subnet = (*subnetList)[adapterIndex]->Subnet();
    Library::DestroySubnetList(subnetList);
    lib->SetCurrentSubnet(subnet);
    Log::Print("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);
    return lib;
}

void TestMediaPlayerInit::SeedRandomNumberGenerator(Environment& aEnv, const Brx& aRoom, TIpAddress aAddress, DviServerUpnp& aServer)
{
    if (aRoom == Brx::Empty()) {
        Log::Print("ERROR: room must be set\n");
        ASSERTS();
    }
    // Re-seed random number generator with hash of (unique) room name + UPnP
    // device server port to avoid UDN clashes.
    TUint port = aServer.Port(aAddress);
    Log::Print("UPnP DV server using port: %u\n", port);
    TUint hash = 0;
    for (TUint i=0; i<aRoom.Bytes(); i++) {
        hash += aRoom[i];
    }
    hash += port;
    Log::Print("Seeding random number generator with: %u\n", hash);
    aEnv.SetRandomSeed(hash);
}

void TestMediaPlayerInit::AppendUniqueId(Environment& aEnv, const Brx& aUserUdn, const Brx& aDefaultUdn, Bwh& aOutput)
{
    if (aUserUdn.Bytes() == 0) {
        if (aOutput.MaxBytes() < aDefaultUdn.Bytes()) {
            aOutput.Grow(aDefaultUdn.Bytes());
        }
        aOutput.Replace(aDefaultUdn);
        RandomiseUdn(aEnv, aOutput);
    }
    else {
        if (aUserUdn.Bytes() > aOutput.MaxBytes()) {
            aOutput.Grow(aUserUdn.Bytes());
        }
        aOutput.Replace(aUserUdn);
    }
}
