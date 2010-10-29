#ifndef HEADER_DVZAPPORGTESTWIDGET1
#define HEADER_DVZAPPORGTESTWIDGET1

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
 * Base Device for zapp.org:TestWidget:1
 */
class DvServiceZappOrgTestWidget1 : public DvService
{
public:
    virtual ~DvServiceZappOrgTestWidget1() {}
    TBool SetPropertyReadWriteRegister0(TUint aValue);
    void GetPropertyReadWriteRegister0(TUint& aValue);
    TBool SetPropertyReadWriteRegister1(TUint aValue);
    void GetPropertyReadWriteRegister1(TUint& aValue);
    TBool SetPropertyReadWriteRegister2(TUint aValue);
    void GetPropertyReadWriteRegister2(TUint& aValue);
    TBool SetPropertyReadWriteRegister3(TUint aValue);
    void GetPropertyReadWriteRegister3(TUint& aValue);
    TBool SetPropertyReadOnlyRegister4(TUint aValue);
    void GetPropertyReadOnlyRegister4(TUint& aValue);
    TBool SetPropertyReadOnlyRegister5(TUint aValue);
    void GetPropertyReadOnlyRegister5(TUint& aValue);
    TBool SetPropertyReadOnlyRegister6(TUint aValue);
    void GetPropertyReadOnlyRegister6(TUint& aValue);
    TBool SetPropertyReadOnlyRegister7(TUint aValue);
    void GetPropertyReadOnlyRegister7(TUint& aValue);
protected:
    DvServiceZappOrgTestWidget1(DvDevice& aDevice);
    void EnableActionSetReadWriteRegister();
private:
    virtual void SetReadWriteRegister(IInvocationResponse& aResponse, TUint aVersion, TUint aRegisterIndex, TUint aRegisterValue);
private:
    DvServiceZappOrgTestWidget1();
    void DoSetReadWriteRegister(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyReadWriteRegister0;
    PropertyUint* iPropertyReadWriteRegister1;
    PropertyUint* iPropertyReadWriteRegister2;
    PropertyUint* iPropertyReadWriteRegister3;
    PropertyUint* iPropertyReadOnlyRegister4;
    PropertyUint* iPropertyReadOnlyRegister5;
    PropertyUint* iPropertyReadOnlyRegister6;
    PropertyUint* iPropertyReadOnlyRegister7;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTWIDGET1

