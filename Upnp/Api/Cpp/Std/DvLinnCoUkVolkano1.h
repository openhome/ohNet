#ifndef HEADER_DVLINNCOUKVOLKANO1CPP
#define HEADER_DVLINNCOUKVOLKANO1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Volkano:1
 */
class DvServiceLinnCoUkVolkano1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkVolkano1Cpp() {}
protected:
    DvServiceLinnCoUkVolkano1Cpp(DvDeviceStd& aDevice);
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
    DvServiceLinnCoUkVolkano1Cpp();
    void DoReboot(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoBootMode(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetBootMode(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoBspType(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoUglyName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoMacAddress(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoProductId(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoBoardId(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoBoardType(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoMaxBoards(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSoftwareVersion(IDvInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKVOLKANO1CPP

