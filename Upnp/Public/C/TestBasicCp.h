#ifndef HEADER_TESTBASICCPC
#define HEADER_TESTBASICCPC

#include <ZappTypes.h>
#include <C/CpDevice.h>

namespace Zapp {

class TestBasicCpC
{
    static const TUint kTestIterations = 10;
public:
    static void TestActions(CpDeviceC aDevice);
    static void TestSubscriptions(CpDeviceC aDevice);
};

} // namespace Zapp

#endif // HEADER_TESTBASICCPC
