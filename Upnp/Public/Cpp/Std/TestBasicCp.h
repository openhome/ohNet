#ifndef HEADER_TESTBASICCP
#define HEADER_TESTBASICCP

namespace Zapp {

class CpDevice;

class TestBasicCp
{
    static const TUint kTestIterations = 10;
public:
    static void TestActions(CpDeviceCpp& aDevice);
    static void TestSubscriptions(CpDeviceCpp& aDevice);
};

} // namespace Zapp

#endif // HEADER_TESTBASICCP
