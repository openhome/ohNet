#ifndef HEADER_DVLINNCOUKCOMPONENT1CPP
#define HEADER_DVLINNCOUKCOMPONENT1CPP

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
 * Base Device for linn.co.uk:Component:1
 */
class DvServiceLinnCoUkComponent1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkComponent1Cpp() {}
    void SetPropertyAmplifierEnabled(bool aValue);
    void GetPropertyAmplifierEnabled(bool& aValue);
    void SetPropertyAmplifierAttenuation(const std::string& aValue);
    void GetPropertyAmplifierAttenuation(std::string& aValue);
    void SetPropertyVolumeControlEnabled(bool aValue);
    void GetPropertyVolumeControlEnabled(bool& aValue);
    void SetPropertyDigitalAudioOutputRaw(bool aValue);
    void GetPropertyDigitalAudioOutputRaw(bool& aValue);
protected:
    DvServiceLinnCoUkComponent1Cpp(DvDeviceStd& aDevice);
    void EnableActionAmplifierEnabled();
    void EnableActionSetAmplifierEnabled();
    void EnableActionAmplifierAttenuation();
    void EnableActionSetAmplifierAttenuation();
    void EnableActionSetVolumeControlEnabled();
    void EnableActionVolumeControlEnabled();
    void EnableActionSetDigitalAudioOutputRaw();
    void EnableActionDigitalAudioOutputRaw();
    void EnableActionAmplifierOverTemperature();
    void EnableActionEthernetLinkConnected();
    void EnableActionLocate();
private:
    virtual void AmplifierEnabled(uint32_t aVersion, bool& aaEnabled);
    virtual void SetAmplifierEnabled(uint32_t aVersion, bool aaEnabled);
    virtual void AmplifierAttenuation(uint32_t aVersion, std::string& aaAttenuation);
    virtual void SetAmplifierAttenuation(uint32_t aVersion, const std::string& aaAttenuation);
    virtual void SetVolumeControlEnabled(uint32_t aVersion, bool aaEnabled);
    virtual void VolumeControlEnabled(uint32_t aVersion, bool& aaEnabled);
    virtual void SetDigitalAudioOutputRaw(uint32_t aVersion, bool aaRaw);
    virtual void DigitalAudioOutputRaw(uint32_t aVersion, bool& aaRaw);
    virtual void AmplifierOverTemperature(uint32_t aVersion, bool& aaOverTemperature);
    virtual void EthernetLinkConnected(uint32_t aVersion, bool& aaLinkConnected);
    virtual void Locate(uint32_t aVersion);
private:
    DvServiceLinnCoUkComponent1Cpp();
    void DoAmplifierEnabled(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetAmplifierEnabled(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoAmplifierAttenuation(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetAmplifierAttenuation(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolumeControlEnabled(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeControlEnabled(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetDigitalAudioOutputRaw(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDigitalAudioOutputRaw(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoAmplifierOverTemperature(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoEthernetLinkConnected(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoLocate(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyBool* iPropertyAmplifierEnabled;
    PropertyString* iPropertyAmplifierAttenuation;
    PropertyBool* iPropertyVolumeControlEnabled;
    PropertyBool* iPropertyDigitalAudioOutputRaw;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCOMPONENT1CPP

