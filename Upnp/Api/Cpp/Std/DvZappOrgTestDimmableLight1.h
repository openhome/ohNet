#ifndef HEADER_DVZAPPORGTESTDIMMABLELIGHT1CPP
#define HEADER_DVZAPPORGTESTDIMMABLELIGHT1CPP

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
 * Base Device for zapp.org:TestDimmableLight:1
 */
class DvServiceZappOrgTestDimmableLight1Cpp : public DvService
{
public:
    virtual ~DvServiceZappOrgTestDimmableLight1Cpp() {}
    void SetPropertyA_ARG_Level(uint32_t aValue);
    void GetPropertyA_ARG_Level(uint32_t& aValue);
protected:
    DvServiceZappOrgTestDimmableLight1Cpp(DvDeviceStd& aDevice);
    void EnableActionGetLevel();
    void EnableActionSetLevel();
private:
    virtual void GetLevel(uint32_t aVersion, uint32_t& aLevel);
    virtual void SetLevel(uint32_t aVersion, uint32_t aLevel);
private:
    DvServiceZappOrgTestDimmableLight1Cpp();
    void DoGetLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetLevel(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyA_ARG_Level;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTDIMMABLELIGHT1CPP

