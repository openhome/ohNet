#ifndef HEADER_DVLINNCOUKVOLKANO1
#define HEADER_DVLINNCOUKVOLKANO1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Volkano:1
 */
class DvProviderLinnCoUkVolkano1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkVolkano1() {}
protected:
    DvProviderLinnCoUkVolkano1(DvDevice& aDevice);
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
    DvProviderLinnCoUkVolkano1();
    void DoReboot(IDviInvocation& aInvocation, TUint aVersion);
    void DoBootMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBootMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoBspType(IDviInvocation& aInvocation, TUint aVersion);
    void DoUglyName(IDviInvocation& aInvocation, TUint aVersion);
    void DoMacAddress(IDviInvocation& aInvocation, TUint aVersion);
    void DoProductId(IDviInvocation& aInvocation, TUint aVersion);
    void DoBoardId(IDviInvocation& aInvocation, TUint aVersion);
    void DoBoardType(IDviInvocation& aInvocation, TUint aVersion);
    void DoMaxBoards(IDviInvocation& aInvocation, TUint aVersion);
    void DoSoftwareVersion(IDviInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKVOLKANO1

