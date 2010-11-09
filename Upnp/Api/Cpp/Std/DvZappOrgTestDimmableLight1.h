#ifndef HEADER_DVZAPPORGTESTDIMMABLELIGHT1CPP
#define HEADER_DVZAPPORGTESTDIMMABLELIGHT1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

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
class DvProviderZappOrgTestDimmableLight1Cpp : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestDimmableLight1Cpp() {}
    bool SetPropertyA_ARG_Level(uint32_t aValue);
    void GetPropertyA_ARG_Level(uint32_t& aValue);
protected:
    DvProviderZappOrgTestDimmableLight1Cpp(DvDeviceStd& aDevice);
    void EnableActionGetLevel();
    void EnableActionSetLevel();
private:
    virtual void GetLevel(uint32_t aVersion, uint32_t& aLevel);
    virtual void SetLevel(uint32_t aVersion, uint32_t aLevel);
private:
    DvProviderZappOrgTestDimmableLight1Cpp();
    void DoGetLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetLevel(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyA_ARG_Level;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTDIMMABLELIGHT1CPP

