#ifndef HEADER_DVLINNCOUKDIAGNOSTICS1
#define HEADER_DVLINNCOUKDIAGNOSTICS1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the linn.co.uk:Diagnostics:1 UPnP service
 */
class DvProviderLinnCoUkDiagnostics1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDiagnostics1() {}
    /**
     * Set the value of the aStateVariable property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyaStateVariable(TUint aValue);
    /**
     * Get a copy of the value of the aStateVariable property
     */
    void GetPropertyaStateVariable(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkDiagnostics1(DvDevice& aDevice);
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
    virtual void Echo(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIn, IInvocationResponseString& aaOut);
    /**
     * ElfFile action.
     *
     * Will be called when the device stack receives an invocation of the
     * ElfFile action for the owning device.
     * Must be implemented iff EnableActionElfFile was called.
     */
    virtual void ElfFile(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFile);
    /**
     * ElfFingerprint action.
     *
     * Will be called when the device stack receives an invocation of the
     * ElfFingerprint action for the owning device.
     * Must be implemented iff EnableActionElfFingerprint was called.
     */
    virtual void ElfFingerprint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFileFingerprint);
    /**
     * CrashDataStatus action.
     *
     * Will be called when the device stack receives an invocation of the
     * CrashDataStatus action for the owning device.
     * Must be implemented iff EnableActionCrashDataStatus was called.
     */
    virtual void CrashDataStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCrashDataStatus);
    /**
     * CrashDataFetch action.
     *
     * Will be called when the device stack receives an invocation of the
     * CrashDataFetch action for the owning device.
     * Must be implemented iff EnableActionCrashDataFetch was called.
     */
    virtual void CrashDataFetch(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaCrashData);
    /**
     * CrashDataClear action.
     *
     * Will be called when the device stack receives an invocation of the
     * CrashDataClear action for the owning device.
     * Must be implemented iff EnableActionCrashDataClear was called.
     */
    virtual void CrashDataClear(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * SysLog action.
     *
     * Will be called when the device stack receives an invocation of the
     * SysLog action for the owning device.
     * Must be implemented iff EnableActionSysLog was called.
     */
    virtual void SysLog(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaSysLog);
    /**
     * Diagnostic action.
     *
     * Will be called when the device stack receives an invocation of the
     * Diagnostic action for the owning device.
     * Must be implemented iff EnableActionDiagnostic was called.
     */
    virtual void Diagnostic(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaDiagnosticType, IInvocationResponseString& aaDiagnosticInfo);
    /**
     * StateVariable action.
     *
     * Will be called when the device stack receives an invocation of the
     * StateVariable action for the owning device.
     * Must be implemented iff EnableActionStateVariable was called.
     */
    virtual void StateVariable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStateVariable);
    /**
     * SetStateVariable action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStateVariable action for the owning device.
     * Must be implemented iff EnableActionSetStateVariable was called.
     */
    virtual void SetStateVariable(IInvocationResponse& aResponse, TUint aVersion, TUint aaStateVariable);
    /**
     * StateVariablePeriod action.
     *
     * Will be called when the device stack receives an invocation of the
     * StateVariablePeriod action for the owning device.
     * Must be implemented iff EnableActionStateVariablePeriod was called.
     */
    virtual void StateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPeriod);
    /**
     * SetStateVariablePeriod action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStateVariablePeriod action for the owning device.
     * Must be implemented iff EnableActionSetStateVariablePeriod was called.
     */
    virtual void SetStateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, TUint aaPeriod);
    /**
     * Reboot action.
     *
     * Will be called when the device stack receives an invocation of the
     * Reboot action for the owning device.
     * Must be implemented iff EnableActionReboot was called.
     */
    virtual void Reboot(IInvocationResponse& aResponse, TUint aVersion, TUint aaDelay);
private:
    DvProviderLinnCoUkDiagnostics1();
    void DoEcho(IDviInvocation& aInvocation, TUint aVersion);
    void DoElfFile(IDviInvocation& aInvocation, TUint aVersion);
    void DoElfFingerprint(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataStatus(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataFetch(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataClear(IDviInvocation& aInvocation, TUint aVersion);
    void DoSysLog(IDviInvocation& aInvocation, TUint aVersion);
    void DoDiagnostic(IDviInvocation& aInvocation, TUint aVersion);
    void DoStateVariable(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariable(IDviInvocation& aInvocation, TUint aVersion);
    void DoStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion);
    void DoReboot(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyaStateVariable;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDIAGNOSTICS1

