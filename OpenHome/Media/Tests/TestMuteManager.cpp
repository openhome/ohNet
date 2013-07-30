#include <OpenHome/Private/TestFramework.h>

#include <OpenHome/Media/MuteManager.h>

using namespace OpenHome::TestFramework;
using namespace OpenHome;
using namespace OpenHome::Media;

//
// declaration of test suites (and auxiliary test class)
//

namespace OpenHome {
namespace Media {

class MuteTestable : public IMute
{
public:
    MuteTestable();
    bool Muted() const;
public:  // from IMute
    void Mute();
    void Unmute();
protected:
    bool iMuted;
};

class SuiteMuteCounted : public Suite
{
public:
    SuiteMuteCounted();
public:  // from Suite
    void Test();
private:
    MuteTestable iMute;
    MuteCounted iMuteCounted;
};

class SuiteMuteCollection : public Suite
{
public:
    SuiteMuteCollection();
public:  // from Suite
    void Test();
private:
    MuteTestable iFirstMute;
    MuteTestable iSecondMute;
    MuteTestable iThirdMute;
    MuteCollection iMuteCollection;
};

class SuiteMuteManager : public Suite
{
public:
    SuiteMuteManager();
public:  // from Suite
    void Test();
private:
    MuteTestable iFirstMute;  // to be used individually
    MuteTestable iSecondMute;  // to be wrapped in ref counting
    MuteTestable iThirdMute;  // to be part of collection
    MuteTestable iFourthMute;  // to be part of collection
    MuteNull iMuteNull;  // to be part of collection (at least exercised even though not testable)
    MuteCounted iMuteCounted;
    MuteCollection iMuteCollection;
    MuteManager iMuteManager;
};

}  // namespace Media
}  // namespace OpenHome

//
// implementation of test suites (and auxiliary test class)
//

// MuteTestable
MuteTestable::MuteTestable()
    : iMuted(false)
{
}

bool MuteTestable::Muted() const
{
    return iMuted;
}

void MuteTestable::Mute()
{
    iMuted = true;
}

void MuteTestable::Unmute()
{
    iMuted = false;
}

// SuiteMuteCounted
SuiteMuteCounted::SuiteMuteCounted()
    : Suite("reference-counted mute element")
    , iMute()
    , iMuteCounted(iMute)
{
}

void SuiteMuteCounted::Test()
{
    TEST(!iMute.Muted());
    TEST_THROWS(iMuteCounted.Unmute(), AssertionFailed);
    iMuteCounted.Mute();
    TEST(iMute.Muted());
    iMuteCounted.Mute();
    TEST(iMute.Muted());
    iMuteCounted.Unmute();
    TEST(iMute.Muted());
    iMuteCounted.Unmute();
    TEST(!iMute.Muted());
    TEST_THROWS(iMuteCounted.Unmute(), AssertionFailed);
}

// SuiteMuteCollection
SuiteMuteCollection::SuiteMuteCollection()
    : Suite("mute element collection")
    , iFirstMute()
    , iSecondMute()
    , iThirdMute()
    , iMuteCollection()
{
    iMuteCollection.Add(iFirstMute);
    iMuteCollection.Add(iSecondMute);
    iMuteCollection.Add(iThirdMute);
}

void SuiteMuteCollection::Test()
{
    // XXX test order of ops on underlying elements?
    TEST(!iFirstMute.Muted());  TEST(!iSecondMute.Muted());  TEST(!iThirdMute.Muted());
    iMuteCollection.Unmute();  // expecting NOP
    TEST(!iFirstMute.Muted());  TEST(!iSecondMute.Muted());  TEST(!iThirdMute.Muted());
    iMuteCollection.Mute();
    TEST(iFirstMute.Muted());  TEST(iSecondMute.Muted());  TEST(iThirdMute.Muted());
    iMuteCollection.Mute();  // expected to be idempotent op
    TEST(iFirstMute.Muted());  TEST(iSecondMute.Muted());  TEST(iThirdMute.Muted());
    iMuteCollection.Unmute();
    TEST(!iFirstMute.Muted());  TEST(!iSecondMute.Muted());  TEST(!iThirdMute.Muted());
    iMuteCollection.Unmute();  // expected to be idempotent op
    TEST(!iFirstMute.Muted());  TEST(!iSecondMute.Muted());  TEST(!iThirdMute.Muted());
}

// SuiteMuteManager
SuiteMuteManager::SuiteMuteManager()
    : Suite("mute manager")
    , iFirstMute()
    , iSecondMute()
    , iThirdMute()
    , iFourthMute()
    , iMuteNull()
    , iMuteCounted(iSecondMute)
    , iMuteCollection()
    , iMuteManager()
{
    iMuteCollection.Add(iThirdMute);
    iMuteCollection.Add(iFourthMute);
    iMuteCollection.Add(iMuteNull);
}

void SuiteMuteManager::Test()
{
    TEST(!iFirstMute.Muted());  TEST(!iSecondMute.Muted());  TEST(!iThirdMute.Muted());  TEST(!iFourthMute.Muted());
    iMuteManager.Add("PLAIN", iFirstMute);
    iMuteManager.Add("REFCNT", iMuteCounted);
    iMuteManager.Add("COLL", iMuteCollection);
    TEST(!iFirstMute.Muted());  TEST(!iSecondMute.Muted());  TEST(!iThirdMute.Muted());  TEST(!iFourthMute.Muted());
    TEST_THROWS(iMuteManager.Find("ENOENT"), AssertionFailed);
    iMuteManager.Find("PLAIN").Mute();
    TEST(iFirstMute.Muted());  TEST(!iSecondMute.Muted());  TEST(!iThirdMute.Muted());  TEST(!iFourthMute.Muted());
    iMuteManager.Find("REFCNT").Mute();
    TEST(iFirstMute.Muted());  TEST(iSecondMute.Muted());  TEST(!iThirdMute.Muted());  TEST(!iFourthMute.Muted());
    iMuteManager.Find("COLL").Mute();
    TEST(iFirstMute.Muted());  TEST(iSecondMute.Muted());  TEST(iThirdMute.Muted());  TEST(iFourthMute.Muted());
    iMuteManager.Find("PLAIN").Unmute();
    iMuteManager.Find("REFCNT").Unmute();
    iMuteManager.Find("COLL").Unmute();
    TEST(!iFirstMute.Muted());  TEST(!iSecondMute.Muted());  TEST(!iThirdMute.Muted());  TEST(!iFourthMute.Muted());
}

//
// sequential execution of test suites
//

void TestMuteManager()
{
    Runner runner("Mute subsystem tests\n");
    // MuteNull not testable but obviously correct (from inspection)
    runner.Add(new SuiteMuteCounted());
    runner.Add(new SuiteMuteCollection());
    runner.Add(new SuiteMuteManager());
    runner.Run();
}
