#ifndef HEADER_DVLINNCOUKVOLKANO1
#define HEADER_DVLINNCOUKVOLKANO1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Volkano:1
 */
class DvServiceLinnCoUkVolkano1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkVolkano1() {}
protected:
    DvServiceLinnCoUkVolkano1(DvDevice& aDevice);
    void EnableActionReboot();
    void EnableActionBootMode();
    void EnableActionSetBootMode();
    void EnableActionBspType();
    void EnableActionUglyName();
    void EnableActionMacAddress();
    void EnableActionProductId();
    void EnableActionBoardId();
    void EnableActionBoardType();
    void EnableActionMaxBoards();
    void EnableActionSoftwareVersion();
private:
    virtual void Reboot(IInvocationResponse& aResponse, TUint aVersion);
    virtual void BootMode(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMode);
    virtual void SetBootMode(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaMode);
    virtual void BspType(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaBspType);
    virtual void UglyName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUglyName);
    virtual void MacAddress(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMacAddress);
    virtual void ProductId(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaProductNumber);
    virtual void BoardId(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber);
    virtual void BoardType(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber);
    virtual void MaxBoards(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaMaxBoards);
    virtual void SoftwareVersion(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSoftwareVersion);
private:
    DvServiceLinnCoUkVolkano1();
    void DoReboot(IDvInvocation& aInvocation, TUint aVersion);
    void DoBootMode(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetBootMode(IDvInvocation& aInvocation, TUint aVersion);
    void DoBspType(IDvInvocation& aInvocation, TUint aVersion);
    void DoUglyName(IDvInvocation& aInvocation, TUint aVersion);
    void DoMacAddress(IDvInvocation& aInvocation, TUint aVersion);
    void DoProductId(IDvInvocation& aInvocation, TUint aVersion);
    void DoBoardId(IDvInvocation& aInvocation, TUint aVersion);
    void DoBoardType(IDvInvocation& aInvocation, TUint aVersion);
    void DoMaxBoards(IDvInvocation& aInvocation, TUint aVersion);
    void DoSoftwareVersion(IDvInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKVOLKANO1

