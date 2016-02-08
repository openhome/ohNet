#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/MuteManager.h>

#include <memory>

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
    std::unique_ptr<IMute> iMuteCounted;
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
{
    iMuteCounted.reset(new MuteCounted(iMute));
}

void SuiteMuteCounted::Test()
{
    TEST(!iMute.Muted());
    TEST_THROWS(iMuteCounted->Unmute(), AssertionFailed);
    iMuteCounted->Mute();
    TEST(iMute.Muted());
    iMuteCounted->Mute();
    TEST(iMute.Muted());
    iMuteCounted->Unmute();
    TEST(iMute.Muted());
    iMuteCounted->Unmute();
    TEST(!iMute.Muted());
    TEST_THROWS(iMuteCounted->Unmute(), AssertionFailed);
}



void TestMuteManager()
{
    Runner runner("Mute subsystem tests\n");
    runner.Add(new SuiteMuteCounted());
    runner.Run();
}
