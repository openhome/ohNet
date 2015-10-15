#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/DviStack.h>

#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>


namespace OpenHome {
namespace Av {
    class AnimatorBasic;
namespace Test {
    class TestMediaPlayer;
} // namespace Test
} // namespace Av
namespace Web {
namespace Test {

class HelperDeviceListHandler
{
public:
    HelperDeviceListHandler(const OpenHome::Brx& aExpectedFriendlyName);
    void Added(OpenHome::Net::CpDevice& aDevice);
    void Removed(OpenHome::Net::CpDevice& aDevice);
    const OpenHome::Brx& GetPresentationUrl() const;
private:
    OpenHome::Brh iFriendlyName;
    OpenHome::Bws<OpenHome::Uri::kMaxUriBytes> iPresentationUrl;
    mutable OpenHome::Mutex iLock;
};

// ConfigApps are not expected to check the existence of ConfigVals at startup.
// This means that the ConfigManager will assert when the config page is loaded
// if a ConfigVal included in the ConfigApp doesn't exist in the ConfigManager.

// This test exploits that behaviour to check if the ConfigApp is valid by
// loading the web page and initiating long-polling. If the ConfigManager
// doesn't assert, the ConfigVals in the ConfigApp are all valid.

// As a side-effect, this test also checks that the (default) language mapping
// for ConfigOptions is valid (i.e., the mapping file is correctly formed, and
// mapping entries for each ConfigOption are listed in the same order that they
// are programmatically added to the ConfigOption).

class SuiteConfigUi : public TestFramework::SuiteUnitTest, private INonCopyable
{
private:
    static const TUint kMaxUiTabs = 4;
    static const TUint kUiSendQueueSize = 32;
protected:
    SuiteConfigUi(OpenHome::Net::CpStack& aCpStack, OpenHome::Net::DvStack& aDvStack);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void Run();
    void TestGetStaticResource();
    void TestLongPollCreate();
    void TestLongPoll();
protected:
    virtual void InitialiseMediaPlayer(const OpenHome::Brx& aUdn, const TChar* aRoom, const TChar* aProductName, const OpenHome::Brx& aTuneInPartnerId, const OpenHome::Brx& aTidalId, const OpenHome::Brx& aQobuzIdSecret, const OpenHome::Brx& aUserAgent) = 0;
    virtual void PopulateUriList() = 0;
protected:
    OpenHome::Net::CpStack& iCpStack;
    OpenHome::Net::DvStack& iDvStack;
    OpenHome::Av::Test::TestMediaPlayer* iMediaPlayer;
    std::vector<Uri*> iUris;
    HelperDeviceListHandler* iDeviceListHandler;
private:
    OpenHome::Media::AnimatorBasic* iAnimator;
    OpenHome::ThreadFunctor* iMediaPlayerThread;
};

} // namespace Test
} // namespace Web
} // namespace OpenHome
