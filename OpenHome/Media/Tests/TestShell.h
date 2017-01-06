#include <OpenHome/Types.h>
#include <OpenHome/Private/Shell.h>
#include <OpenHome/Private/ShellCommandRun.h>

#include <vector>

#define SIMPLE_TEST_DECLARATION(x)  \
    extern void x();                \
    static void Shell##x(Net::CpStack&, Net::DvStack&, const std::vector<Brn>&) { x(); } \

#define ENV_TEST_DECLARATION(x) \
    extern void x(Environment&);            \
    static void Shell##x(Net::CpStack&, Net::DvStack& aDvStack, const std::vector<Brn>&) { x(aDvStack.Env()); } \

#define CP_DV_TEST_DECLARATION(x) \
    extern void x(Net::CpStack&, Net::DvStack&);            \
    static void Shell##x(Net::CpStack& aCpStack, Net::DvStack& aDvStack, const std::vector<Brn>&) { x(aCpStack, aDvStack); } \

namespace OpenHome {
namespace Net {
    class InitialisationParams;
}
namespace Media {

static const TUint kTestShellTimeout = 60; // initial timeout for TestShell. This is increased  by testharness once running.

void ExecuteTestShell(Net::InitialisationParams* aInitParams, std::vector<ShellTest>& aTests);

} // namespace Media
} // namespace OpenHome
