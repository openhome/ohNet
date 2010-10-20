#ifndef HEADER_DVZAPPORGTESTWIDGET1CPP
#define HEADER_DVZAPPORGTESTWIDGET1CPP

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
 * Base Device for zapp.org:TestWidget:1
 */
class DvServiceZappOrgTestWidget1Cpp : public DvService
{
public:
    virtual ~DvServiceZappOrgTestWidget1Cpp() {}
    void SetPropertyReadWriteRegister0(uint32_t aValue);
    void GetPropertyReadWriteRegister0(uint32_t& aValue);
    void SetPropertyReadWriteRegister1(uint32_t aValue);
    void GetPropertyReadWriteRegister1(uint32_t& aValue);
    void SetPropertyReadWriteRegister2(uint32_t aValue);
    void GetPropertyReadWriteRegister2(uint32_t& aValue);
    void SetPropertyReadWriteRegister3(uint32_t aValue);
    void GetPropertyReadWriteRegister3(uint32_t& aValue);
    void SetPropertyReadOnlyRegister4(uint32_t aValue);
    void GetPropertyReadOnlyRegister4(uint32_t& aValue);
    void SetPropertyReadOnlyRegister5(uint32_t aValue);
    void GetPropertyReadOnlyRegister5(uint32_t& aValue);
    void SetPropertyReadOnlyRegister6(uint32_t aValue);
    void GetPropertyReadOnlyRegister6(uint32_t& aValue);
    void SetPropertyReadOnlyRegister7(uint32_t aValue);
    void GetPropertyReadOnlyRegister7(uint32_t& aValue);
protected:
    DvServiceZappOrgTestWidget1Cpp(DvDeviceStd& aDevice);
    void EnableActionSetReadWriteRegister();
private:
    virtual void SetReadWriteRegister(uint32_t aVersion, uint32_t aRegisterIndex, uint32_t aRegisterValue);
private:
    DvServiceZappOrgTestWidget1Cpp();
    void DoSetReadWriteRegister(IDvInvocation& aInvocation, uint32_t aVersion);
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

#endif // HEADER_DVZAPPORGTESTWIDGET1CPP

