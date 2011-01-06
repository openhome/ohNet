#ifndef HEADER_DVLINNCOUKDIAGNOSTICS1CPP
#define HEADER_DVLINNCOUKDIAGNOSTICS1CPP

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
 * Provider for the linn.co.uk:Diagnostics:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkDiagnostics1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDiagnostics1Cpp() {}
    /**
     * Set the value of the aStateVariable property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyaStateVariable(uint32_t aValue);
    /**
     * Get a copy of the value of the aStateVariable property
     */
    void GetPropertyaStateVariable(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkDiagnostics1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Echo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoEcho must be overridden if this is called.
     */
    void EnableActionEcho();
    /**
     * Signal that the action ElfFile is supported.
     * The action's availability will be published in the device's service.xml.
     * DoElfFile must be overridden if this is called.
     */
    void EnableActionElfFile();
    /**
     * Signal that the action ElfFingerprint is supported.
     * The action's availability will be published in the device's service.xml.
     * DoElfFingerprint must be overridden if this is called.
     */
    void EnableActionElfFingerprint();
    /**
     * Signal that the action CrashDataStatus is supported.
     * The action's availability will be published in the device's service.xml.
     * DoCrashDataStatus must be overridden if this is called.
     */
    void EnableActionCrashDataStatus();
    /**
     * Signal that the action CrashDataFetch is supported.
     * The action's availability will be published in the device's service.xml.
     * DoCrashDataFetch must be overridden if this is called.
     */
    void EnableActionCrashDataFetch();
    /**
     * Signal that the action CrashDataClear is supported.
     * The action's availability will be published in the device's service.xml.
     * DoCrashDataClear must be overridden if this is called.
     */
    void EnableActionCrashDataClear();
    /**
     * Signal that the action SysLog is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSysLog must be overridden if this is called.
     */
    void EnableActionSysLog();
    /**
     * Signal that the action Diagnostic is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDiagnostic must be overridden if this is called.
     */
    void EnableActionDiagnostic();
    /**
     * Signal that the action StateVariable is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStateVariable must be overridden if this is called.
     */
    void EnableActionStateVariable();
    /**
     * Signal that the action SetStateVariable is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStateVariable must be overridden if this is called.
     */
    void EnableActionSetStateVariable();
    /**
     * Signal that the action StateVariablePeriod is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStateVariablePeriod must be overridden if this is called.
     */
    void EnableActionStateVariablePeriod();
    /**
     * Signal that the action SetStateVariablePeriod is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStateVariablePeriod must be overridden if this is called.
     */
    void EnableActionSetStateVariablePeriod();
    /**
     * Signal that the action Reboot is supported.
     * The action's availability will be published in the device's service.xml.
     * DoReboot must be overridden if this is called.
     */
    void EnableActionReboot();
private:
    /**
     * Echo action.
     *
     * Will be called when the device stack receives an invocation of the
     * Echo action for the owning device.
     * Must be implemented iff EnableActionEcho was called.
     */
    virtual void Echo(uint32_t aVersion, const std::string& aaIn, std::string& aaOut);
    /**
     * ElfFile action.
     *
     * Will be called when the device stack receives an invocation of the
     * ElfFile action for the owning device.
     * Must be implemented iff EnableActionElfFile was called.
     */
    virtual void ElfFile(uint32_t aVersion, std::string& aaElfFile);
    /**
     * ElfFingerprint action.
     *
     * Will be called when the device stack receives an invocation of the
     * ElfFingerprint action for the owning device.
     * Must be implemented iff EnableActionElfFingerprint was called.
     */
    virtual void ElfFingerprint(uint32_t aVersion, std::string& aaElfFileFingerprint);
    /**
     * CrashDataStatus action.
     *
     * Will be called when the device stack receives an invocation of the
     * CrashDataStatus action for the owning device.
     * Must be implemented iff EnableActionCrashDataStatus was called.
     */
    virtual void CrashDataStatus(uint32_t aVersion, std::string& aaCrashDataStatus);
    /**
     * CrashDataFetch action.
     *
     * Will be called when the device stack receives an invocation of the
     * CrashDataFetch action for the owning device.
     * Must be implemented iff EnableActionCrashDataFetch was called.
     */
    virtual void CrashDataFetch(uint32_t aVersion, std::string& aaCrashData);
    /**
     * CrashDataClear action.
     *
     * Will be called when the device stack receives an invocation of the
     * CrashDataClear action for the owning device.
     * Must be implemented iff EnableActionCrashDataClear was called.
     */
    virtual void CrashDataClear(uint32_t aVersion);
    /**
     * SysLog action.
     *
     * Will be called when the device stack receives an invocation of the
     * SysLog action for the owning device.
     * Must be implemented iff EnableActionSysLog was called.
     */
    virtual void SysLog(uint32_t aVersion, std::string& aaSysLog);
    /**
     * Diagnostic action.
     *
     * Will be called when the device stack receives an invocation of the
     * Diagnostic action for the owning device.
     * Must be implemented iff EnableActionDiagnostic was called.
     */
    virtual void Diagnostic(uint32_t aVersion, const std::string& aaDiagnosticType, std::string& aaDiagnosticInfo);
    /**
     * StateVariable action.
     *
     * Will be called when the device stack receives an invocation of the
     * StateVariable action for the owning device.
     * Must be implemented iff EnableActionStateVariable was called.
     */
    virtual void StateVariable(uint32_t aVersion, uint32_t& aaStateVariable);
    /**
     * SetStateVariable action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStateVariable action for the owning device.
     * Must be implemented iff EnableActionSetStateVariable was called.
     */
    virtual void SetStateVariable(uint32_t aVersion, uint32_t aaStateVariable);
    /**
     * StateVariablePeriod action.
     *
     * Will be called when the device stack receives an invocation of the
     * StateVariablePeriod action for the owning device.
     * Must be implemented iff EnableActionStateVariablePeriod was called.
     */
    virtual void StateVariablePeriod(uint32_t aVersion, uint32_t& aaPeriod);
    /**
     * SetStateVariablePeriod action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStateVariablePeriod action for the owning device.
     * Must be implemented iff EnableActionSetStateVariablePeriod was called.
     */
    virtual void SetStateVariablePeriod(uint32_t aVersion, uint32_t aaPeriod);
    /**
     * Reboot action.
     *
     * Will be called when the device stack receives an invocation of the
     * Reboot action for the owning device.
     * Must be implemented iff EnableActionReboot was called.
     */
    virtual void Reboot(uint32_t aVersion, uint32_t aaDelay);
private:
    DvProviderLinnCoUkDiagnostics1Cpp();
    void DoEcho(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoElfFile(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoElfFingerprint(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCrashDataStatus(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCrashDataFetch(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCrashDataClear(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSysLog(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDiagnostic(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStateVariable(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStateVariable(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStateVariablePeriod(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStateVariablePeriod(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoReboot(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyaStateVariable;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDIAGNOSTICS1CPP

