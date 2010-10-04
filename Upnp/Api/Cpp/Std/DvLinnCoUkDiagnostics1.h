#ifndef HEADER_DVLINNCOUKDIAGNOSTICS1CPP
#define HEADER_DVLINNCOUKDIAGNOSTICS1CPP

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
 * Base Device for linn.co.uk:Diagnostics:1
 */
class DvServiceLinnCoUkDiagnostics1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkDiagnostics1Cpp() {}
    void SetPropertyaStateVariable(uint32_t aValue);
    void GetPropertyaStateVariable(uint32_t& aValue);
protected:
    DvServiceLinnCoUkDiagnostics1Cpp(DvDeviceStd& aDevice);
    void EnableActionEcho();
    void EnableActionElfFile();
    void EnableActionElfFingerprint();
    void EnableActionCrashDataStatus();
    void EnableActionCrashDataFetch();
    void EnableActionCrashDataClear();
    void EnableActionSysLog();
    void EnableActionDiagnostic();
    void EnableActionStateVariable();
    void EnableActionSetStateVariable();
    void EnableActionStateVariablePeriod();
    void EnableActionSetStateVariablePeriod();
    void EnableActionReboot();
private:
    virtual void Echo(uint32_t aVersion, const std::string& aaIn, std::string& aaOut);
    virtual void ElfFile(uint32_t aVersion, std::string& aaElfFile);
    virtual void ElfFingerprint(uint32_t aVersion, std::string& aaElfFileFingerprint);
    virtual void CrashDataStatus(uint32_t aVersion, std::string& aaCrashDataStatus);
    virtual void CrashDataFetch(uint32_t aVersion, std::string& aaCrashData);
    virtual void CrashDataClear(uint32_t aVersion);
    virtual void SysLog(uint32_t aVersion, std::string& aaSysLog);
    virtual void Diagnostic(uint32_t aVersion, const std::string& aaDiagnosticType, std::string& aaDiagnosticInfo);
    virtual void StateVariable(uint32_t aVersion, uint32_t& aaStateVariable);
    virtual void SetStateVariable(uint32_t aVersion, uint32_t aaStateVariable);
    virtual void StateVariablePeriod(uint32_t aVersion, uint32_t& aaPeriod);
    virtual void SetStateVariablePeriod(uint32_t aVersion, uint32_t aaPeriod);
    virtual void Reboot(uint32_t aVersion, uint32_t aaDelay);
private:
    DvServiceLinnCoUkDiagnostics1Cpp();
    void DoEcho(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoElfFile(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoElfFingerprint(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoCrashDataStatus(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoCrashDataFetch(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoCrashDataClear(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSysLog(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDiagnostic(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStateVariable(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStateVariable(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStateVariablePeriod(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStateVariablePeriod(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoReboot(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyaStateVariable;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDIAGNOSTICS1CPP

