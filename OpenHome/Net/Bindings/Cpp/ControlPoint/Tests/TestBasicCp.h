#ifndef HEADER_TESTBASICCP
#define HEADER_TESTBASICCP

namespace OpenHome {
namespace Net {

class CpDevice;

class TestBasicCp
{
    static const TUint kTestIterations = 10;
public:
    static void TestActions(CpDeviceCpp& aDevice);
    static void TestThrowsWhenDisabled(CpDeviceCpp& aDevice);
    static void TestThrowsCustomError(CpDeviceCpp& aDevice);
    static void TestSubscriptions(CpDeviceCpp& aDevice);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TESTBASICCP
