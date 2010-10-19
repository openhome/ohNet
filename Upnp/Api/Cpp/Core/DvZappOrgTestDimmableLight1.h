#ifndef HEADER_DVZAPPORGTESTDIMMABLELIGHT1
#define HEADER_DVZAPPORGTESTDIMMABLELIGHT1

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
 * Base Device for zapp.org:TestDimmableLight:1
 */
class DvServiceZappOrgTestDimmableLight1 : public DvService
{
public:
    virtual ~DvServiceZappOrgTestDimmableLight1() {}
    void SetPropertyA_ARG_Level(TUint aValue);
    void GetPropertyA_ARG_Level(TUint& aValue);
protected:
    DvServiceZappOrgTestDimmableLight1(DvDevice& aDevice);
    void EnableActionGetLevel();
    void EnableActionSetLevel();
private:
    virtual void GetLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aLevel);
    virtual void SetLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aLevel);
private:
    DvServiceZappOrgTestDimmableLight1();
    void DoGetLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetLevel(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyA_ARG_Level;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTDIMMABLELIGHT1

