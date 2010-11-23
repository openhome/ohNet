#ifndef HEADER_DVLINNCOUKVOLKANO1
#define HEADER_DVLINNCOUKVOLKANO1

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
 * Provider for the linn.co.uk:Volkano:1 UPnP service
 */
class DvProviderLinnCoUkVolkano1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkVolkano1() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkVolkano1(DvDevice& aDevice);
    /**
     * Signal that the action Reboot is supported.
     * The action's availability will be published in the device's service.xml.
     * DoReboot must be overridden if this is called.
     */
    void EnableActionReboot();
    /**
     * Signal that the action BootMode is supported.
     * The action's availability will be published in the device's service.xml.
     * DoBootMode must be overridden if this is called.
     */
    void EnableActionBootMode();
    /**
     * Signal that the action SetBootMode is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetBootMode must be overridden if this is called.
     */
    void EnableActionSetBootMode();
    /**
     * Signal that the action BspType is supported.
     * The action's availability will be published in the device's service.xml.
     * DoBspType must be overridden if this is called.
     */
    void EnableActionBspType();
    /**
     * Signal that the action UglyName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoUglyName must be overridden if this is called.
     */
    void EnableActionUglyName();
    /**
     * Signal that the action MacAddress is supported.
     * The action's availability will be published in the device's service.xml.
     * DoMacAddress must be overridden if this is called.
     */
    void EnableActionMacAddress();
    /**
     * Signal that the action ProductId is supported.
     * The action's availability will be published in the device's service.xml.
     * DoProductId must be overridden if this is called.
     */
    void EnableActionProductId();
    /**
     * Signal that the action BoardId is supported.
     * The action's availability will be published in the device's service.xml.
     * DoBoardId must be overridden if this is called.
     */
    void EnableActionBoardId();
    /**
     * Signal that the action BoardType is supported.
     * The action's availability will be published in the device's service.xml.
     * DoBoardType must be overridden if this is called.
     */
    void EnableActionBoardType();
    /**
     * Signal that the action MaxBoards is supported.
     * The action's availability will be published in the device's service.xml.
     * DoMaxBoards must be overridden if this is called.
     */
    void EnableActionMaxBoards();
    /**
     * Signal that the action SoftwareVersion is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSoftwareVersion must be overridden if this is called.
     */
    void EnableActionSoftwareVersion();
private:
    /**
     * Reboot action.
     *
     * Will be called when the device stack receives an invocation of the
     * Reboot action for the owning device.
     * Must be implemented iff EnableActionReboot was called.
     */
    virtual void Reboot(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * BootMode action.
     *
     * Will be called when the device stack receives an invocation of the
     * BootMode action for the owning device.
     * Must be implemented iff EnableActionBootMode was called.
     */
    virtual void BootMode(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMode);
    /**
     * SetBootMode action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBootMode action for the owning device.
     * Must be implemented iff EnableActionSetBootMode was called.
     */
    virtual void SetBootMode(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaMode);
    /**
     * BspType action.
     *
     * Will be called when the device stack receives an invocation of the
     * BspType action for the owning device.
     * Must be implemented iff EnableActionBspType was called.
     */
    virtual void BspType(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaBspType);
    /**
     * UglyName action.
     *
     * Will be called when the device stack receives an invocation of the
     * UglyName action for the owning device.
     * Must be implemented iff EnableActionUglyName was called.
     */
    virtual void UglyName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUglyName);
    /**
     * MacAddress action.
     *
     * Will be called when the device stack receives an invocation of the
     * MacAddress action for the owning device.
     * Must be implemented iff EnableActionMacAddress was called.
     */
    virtual void MacAddress(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMacAddress);
    /**
     * ProductId action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProductId action for the owning device.
     * Must be implemented iff EnableActionProductId was called.
     */
    virtual void ProductId(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaProductNumber);
    /**
     * BoardId action.
     *
     * Will be called when the device stack receives an invocation of the
     * BoardId action for the owning device.
     * Must be implemented iff EnableActionBoardId was called.
     */
    virtual void BoardId(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber);
    /**
     * BoardType action.
     *
     * Will be called when the device stack receives an invocation of the
     * BoardType action for the owning device.
     * Must be implemented iff EnableActionBoardType was called.
     */
    virtual void BoardType(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, IInvocationResponseString& aaBoardNumber);
    /**
     * MaxBoards action.
     *
     * Will be called when the device stack receives an invocation of the
     * MaxBoards action for the owning device.
     * Must be implemented iff EnableActionMaxBoards was called.
     */
    virtual void MaxBoards(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaMaxBoards);
    /**
     * SoftwareVersion action.
     *
     * Will be called when the device stack receives an invocation of the
     * SoftwareVersion action for the owning device.
     * Must be implemented iff EnableActionSoftwareVersion was called.
     */
    virtual void SoftwareVersion(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSoftwareVersion);
private:
    DvProviderLinnCoUkVolkano1();
    void DoReboot(IDviInvocation& aInvocation, TUint aVersion);
    void DoBootMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBootMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoBspType(IDviInvocation& aInvocation, TUint aVersion);
    void DoUglyName(IDviInvocation& aInvocation, TUint aVersion);
    void DoMacAddress(IDviInvocation& aInvocation, TUint aVersion);
    void DoProductId(IDviInvocation& aInvocation, TUint aVersion);
    void DoBoardId(IDviInvocation& aInvocation, TUint aVersion);
    void DoBoardType(IDviInvocation& aInvocation, TUint aVersion);
    void DoMaxBoards(IDviInvocation& aInvocation, TUint aVersion);
    void DoSoftwareVersion(IDviInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKVOLKANO1

