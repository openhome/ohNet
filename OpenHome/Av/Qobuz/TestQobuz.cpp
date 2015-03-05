#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Qobuz/Qobuz.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>

namespace OpenHome {
namespace Av {

class TestQobuz : private ICredentialsState
{
public:
    TestQobuz(Environment& aEnv, const Brx& aId, const Brx& aSecret);
    virtual ~TestQobuz();
    void Start(const Brx& aUsername, const Brx& aPassword);
    void Test();
private: // from ICredentialsState
    void SetState(const Brx& aId, const Brx& aStatus, const Brx& aData) override;
private:
    Configuration::ConfigRamStore* iStore;
    Configuration::ConfigManager* iConfigManager;
    Qobuz* iQobuz;
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;

TestQobuz::TestQobuz(Environment& aEnv, const Brx& aId, const Brx& aSecret)
{
    iStore = new Configuration::ConfigRamStore();
    iConfigManager = new Configuration::ConfigManager(*iStore);
    iQobuz = new Qobuz(aEnv, aId, aSecret, *this, *iConfigManager);
}

TestQobuz::~TestQobuz()
{
    delete iQobuz;
    delete iConfigManager;
    delete iStore;
}

void TestQobuz::Start(const Brx& aUsername, const Brx& aPassword)
{
    iQobuz->CredentialsChanged(aUsername, aPassword);
    //iQobuz->UpdateStatus();
}

void TestQobuz::Test()
{
    iQobuz->TryLoginLocked();
    static const TChar* kTracks[] = { "7343778"
                                    };

    const TUint numElems = sizeof(kTracks)/sizeof(kTracks[0]);
    Bws<1024> streamUrl;
    for (TUint i=0; i<numElems; i++) {
        Brn trackId(kTracks[i]);
        iQobuz->TryGetStreamUrl(trackId, streamUrl);
        Log::Print("trackId %s returned url %s\n", kTracks[i], streamUrl.PtrZ());
    }
}

void TestQobuz::SetState(const Brx& /*aId*/, const Brx& aStatus, const Brx& aData)
{
    Log::Print("SetState: aStatus = ");
    Log::Print(aStatus);
    Log::Print(", aData = ");
    Log::Print(aData);
    Log::Print("\n");
}



void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    Environment* env = Net::UpnpLibrary::Initialise(aInitParams);

    OptionParser parser;
    OptionString optionId("", "--id", Brn(""), "Qobuz app id");
    parser.AddOption(&optionId);
    OptionString optionSecret("", "--secret", Brn(""), "Qobuz app secret");
    parser.AddOption(&optionSecret);
    OptionString optionUsername("", "--username", Brn(""), "Username");
    parser.AddOption(&optionUsername);
    OptionString optionPassword("", "--password", Brn(""), "Password");
    parser.AddOption(&optionPassword);
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);
    if (!parser.Parse(args) || parser.HelpDisplayed()) {
        return;
    }

    Debug::SetLevel(Debug::kError | Debug::kApplication6);
    TestQobuz* qobuz = new TestQobuz(*env, optionId.Value(), optionSecret.Value());
    qobuz->Start(optionUsername.Value(), optionPassword.Value());
    qobuz->Test();
    delete qobuz;
    Net::UpnpLibrary::Close();
}
