#ifndef HEADER_DVLINNCOUKDEBUG2CPP
#define HEADER_DVLINNCOUKDEBUG2CPP

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
 * Provider for the linn.co.uk:Debug:2 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkDebug2Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDebug2Cpp() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkDebug2Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action SetDebugLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDebugLevel must be overridden if this is called.
     */
    void EnableActionSetDebugLevel();
    /**
     * Signal that the action DebugLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDebugLevel must be overridden if this is called.
     */
    void EnableActionDebugLevel();
    /**
     * Signal that the action MemWrite is supported.
     * The action's availability will be published in the device's service.xml.
     * DoMemWrite must be overridden if this is called.
     */
    void EnableActionMemWrite();
private:
    /**
     * SetDebugLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDebugLevel action for the owning device.
     * Must be implemented iff EnableActionSetDebugLevel was called.
     */
    virtual void SetDebugLevel(uint32_t aVersion, uint32_t aaDebugLevel);
    /**
     * DebugLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * DebugLevel action for the owning device.
     * Must be implemented iff EnableActionDebugLevel was called.
     */
    virtual void DebugLevel(uint32_t aVersion, uint32_t& aaDebugLevel);
    /**
     * MemWrite action.
     *
     * Will be called when the device stack receives an invocation of the
     * MemWrite action for the owning device.
     * Must be implemented iff EnableActionMemWrite was called.
     */
    virtual void MemWrite(uint32_t aVersion, uint32_t aaMemAddress, const std::string& aaMemData);
private:
    DvProviderLinnCoUkDebug2Cpp();
    void DoSetDebugLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDebugLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoMemWrite(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDEBUG2CPP

