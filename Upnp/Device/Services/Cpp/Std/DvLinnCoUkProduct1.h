#ifndef HEADER_DVLINNCOUKPRODUCT1CPP
#define HEADER_DVLINNCOUKPRODUCT1CPP

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
 * Provider for the linn.co.uk:Product:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkProduct1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct1Cpp() {}
    /**
     * Set the value of the Room property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyRoom(const std::string& aValue);
    /**
     * Get a copy of the value of the Room property
     */
    void GetPropertyRoom(std::string& aValue);
    /**
     * Set the value of the Standby property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyStandby(bool aValue);
    /**
     * Get a copy of the value of the Standby property
     */
    void GetPropertyStandby(bool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkProduct1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Room is supported.
     * The action's availability will be published in the device's service.xml.
     * Room must be overridden if this is called.
     */
    void EnableActionRoom();
    /**
     * Signal that the action SetRoom is supported.
     * The action's availability will be published in the device's service.xml.
     * SetRoom must be overridden if this is called.
     */
    void EnableActionSetRoom();
    /**
     * Signal that the action Standby is supported.
     * The action's availability will be published in the device's service.xml.
     * Standby must be overridden if this is called.
     */
    void EnableActionStandby();
    /**
     * Signal that the action SetStandby is supported.
     * The action's availability will be published in the device's service.xml.
     * SetStandby must be overridden if this is called.
     */
    void EnableActionSetStandby();
private:
    /**
     * Room action.
     *
     * Will be called when the device stack receives an invocation of the
     * Room action for the owning device.
     * Must be implemented iff EnableActionRoom was called.
     */
    virtual void Room(uint32_t aVersion, std::string& aaRoom);
    /**
     * SetRoom action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRoom action for the owning device.
     * Must be implemented iff EnableActionSetRoom was called.
     */
    virtual void SetRoom(uint32_t aVersion, const std::string& aaRoom);
    /**
     * Standby action.
     *
     * Will be called when the device stack receives an invocation of the
     * Standby action for the owning device.
     * Must be implemented iff EnableActionStandby was called.
     */
    virtual void Standby(uint32_t aVersion, bool& aaStandby);
    /**
     * SetStandby action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStandby action for the owning device.
     * Must be implemented iff EnableActionSetStandby was called.
     */
    virtual void SetStandby(uint32_t aVersion, bool aaStandby);
private:
    DvProviderLinnCoUkProduct1Cpp();
    void DoRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStandby(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyRoom;
    PropertyBool* iPropertyStandby;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT1CPP

