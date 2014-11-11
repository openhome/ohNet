#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Net/Private/ShellCommandRun.h>

using namespace OpenHome;
using namespace OpenHome::Net;

#define SIMPLE_TEST_DECLARATION(x)  \
    extern void x();                \
    static void Shell##x(CpStack&, DvStack&, const std::vector<Brn>&) { x(); } \

#define ENV_TEST_DECLARATION(x) \
    extern void x(Environment&);            \
    static void Shell##x(CpStack&, DvStack& aDvStack, const std::vector<Brn>&) { x(aDvStack.Env()); } \

#define CP_DV_TEST_DECLARATION(x) \
    extern void x(CpStack&, DvStack&);            \
    static void Shell##x(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>&) { x(aCpStack, aDvStack); } \

namespace OpenHome {
namespace Net {
    class InitialisationParams;
}

namespace Media {

static const TUint kTestShellTimeout = 60; // initial timeout for TestShell. This is increased  by testharness once running.

void ExecuteTestShell(Net::InitialisationParams* aInitParams, std::vector<ShellTest>& aTests);

} // namespace Media
} // namespace OpenHome
