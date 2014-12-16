#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Tidal/Tidal.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>

namespace OpenHome {
namespace Av {

class TestTidal : private ICredentialsState
{
public:
    TestTidal(Environment& aEnv, const Brx& aToken);
    ~TestTidal();
    void Start(const Brx& aUsername, const Brx& aPassword);
    void Test();
private: // from ICredentialsState
    void SetState(const Brx& aId, const Brx& aStatus, const Brx& aData) override;
private:
    Configuration::ConfigRamStore* iStore;
    Configuration::ConfigManager* iConfigManager;
    Tidal* iTidal;
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;

TestTidal::TestTidal(Environment& aEnv, const Brx& aToken)
{
    iStore = new Configuration::ConfigRamStore();
    iConfigManager = new Configuration::ConfigManager(*iStore);
    iTidal = new Tidal(aEnv, aToken, *this, *iConfigManager);
}

TestTidal::~TestTidal()
{
    delete iTidal;
    delete iConfigManager;
    delete iStore;
}

void TestTidal::Start(const Brx& aUsername, const Brx& aPassword)
{
    iTidal->CredentialsChanged(aUsername, aPassword);
    iTidal->UpdateStatus();
}

void TestTidal::Test()
{
    static const TChar* kTracks[] = { "21691876",
                                      "x25319855",
                                      "x17719348",
                                      "x36666349",
                                      "x25347004",
                                      "x23093712",
                                      "x20751430",
                                      "x18233701",
                                      "x18457099",
                                      "x31214177",
                                      "x25481067",
                                      "x33093661",
                                      "x30554888",
                                      "x24155300",
                                      "x20159140",
                                      "x2717446",
                                      "x16909477",
                                      "x36301127",
                                      "x9066215",
                                      "x18440593",
                                    };

    const TUint numElems = sizeof(kTracks)/sizeof(kTracks[0]);
    TUint count = 0;
    Bws<256> streamUrl;
    Bws<64> sessionId;
    iTidal->TryReLogin(sessionId, sessionId);
    for (;;) {
        for (TUint i=0; i<numElems; i++) {
            Log::Print("#%6u, %s\n", count++, kTracks[i]);
            Brn trackId(kTracks[i]);
            iTidal->TryGetStreamUrl(trackId, streamUrl);
            iTidal->TryLogout(sessionId);
            iTidal->TryLogin(sessionId);
            iTidal->TryGetStreamUrl(trackId, streamUrl);
        }
    }
}

void TestTidal::SetState(const Brx& /*aId*/, const Brx& /*aStatus*/, const Brx& /*aData*/)
{
}



void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    Environment* env = Net::UpnpLibrary::Initialise(aInitParams);

    OptionParser parser;
    OptionString optionToken("-t", "--token", Brn(""), "Tidal application token");
    parser.AddOption(&optionToken);
    OptionString optionUsername("-u", "--username", Brn(""), "Username");
    parser.AddOption(&optionUsername);
    OptionString optionPassword("-p", "--password", Brn(""), "Password");
    parser.AddOption(&optionPassword);
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);
    if (!parser.Parse(args) || parser.HelpDisplayed()) {
        return;
    }

    Debug::SetLevel(Debug::kError | Debug::kApplication6);
    TestTidal* tidal = new TestTidal(*env, optionToken.Value());
    tidal->Start(optionUsername.Value(), optionPassword.Value());
    tidal->Test();
    delete tidal;
    Net::UpnpLibrary::Close();
}
