#ifndef HEADER_DVLINNCOUKDEBUG2CPP
#define HEADER_DVLINNCOUKDEBUG2CPP

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
 * Base Device for linn.co.uk:Debug:2
 */
class DvServiceLinnCoUkDebug2Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkDebug2Cpp() {}
protected:
    DvServiceLinnCoUkDebug2Cpp(DvDeviceStd& aDevice);
    void EnableActionSetDebugLevel();
    void EnableActionDebugLevel();
    void EnableActionMemWrite();
private:
    virtual void SetDebugLevel(uint32_t aVersion, uint32_t aaDebugLevel);
    virtual void DebugLevel(uint32_t aVersion, uint32_t& aaDebugLevel);
    virtual void MemWrite(uint32_t aVersion, uint32_t aaMemAddress, const std::string& aaMemData);
private:
    DvServiceLinnCoUkDebug2Cpp();
    void DoSetDebugLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDebugLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoMemWrite(IDvInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDEBUG2CPP

