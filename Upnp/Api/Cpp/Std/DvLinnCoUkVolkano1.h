#ifndef HEADER_DVLINNCOUKVOLKANO1CPP
#define HEADER_DVLINNCOUKVOLKANO1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

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
class DvProviderLinnCoUkVolkano1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkVolkano1Cpp() {}
protected:
    DvProviderLinnCoUkVolkano1Cpp(DvDeviceStd& aDevice);
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
    virtual void Reboot(uint32_t aVersion);
    virtual void BootMode(uint32_t aVersion, std::string& aaMode);
    virtual void SetBootMode(uint32_t aVersion, const std::string& aaMode);
    virtual void BspType(uint32_t aVersion, std::string& aaBspType);
    virtual void UglyName(uint32_t aVersion, std::string& aaUglyName);
    virtual void MacAddress(uint32_t aVersion, std::string& aaMacAddress);
    virtual void ProductId(uint32_t aVersion, std::string& aaProductNumber);
    virtual void BoardId(uint32_t aVersion, uint32_t aaIndex, std::string& aaBoardNumber);
    virtual void BoardType(uint32_t aVersion, uint32_t aaIndex, std::string& aaBoardNumber);
    virtual void MaxBoards(uint32_t aVersion, uint32_t& aaMaxBoards);
    virtual void SoftwareVersion(uint32_t aVersion, std::string& aaSoftwareVersion);
private:
    DvProviderLinnCoUkVolkano1Cpp();
    void DoReboot(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBootMode(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetBootMode(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBspType(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoUglyName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoMacAddress(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoProductId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBoardId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBoardType(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoMaxBoards(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSoftwareVersion(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKVOLKANO1CPP

