#ifndef HEADER_DVLINNCOUKCOMPONENT1CPP
#define HEADER_DVLINNCOUKCOMPONENT1CPP

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
 * Base Device for linn.co.uk:Component:1
 */
class DvProviderLinnCoUkComponent1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkComponent1Cpp() {}
    bool SetPropertyAmplifierEnabled(bool aValue);
    void GetPropertyAmplifierEnabled(bool& aValue);
    bool SetPropertyAmplifierAttenuation(const std::string& aValue);
    void GetPropertyAmplifierAttenuation(std::string& aValue);
    bool SetPropertyVolumeControlEnabled(bool aValue);
    void GetPropertyVolumeControlEnabled(bool& aValue);
    bool SetPropertyDigitalAudioOutputRaw(bool aValue);
    void GetPropertyDigitalAudioOutputRaw(bool& aValue);
protected:
    DvProviderLinnCoUkComponent1Cpp(DvDeviceStd& aDevice);
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
    DvProviderLinnCoUkComponent1Cpp();
    void DoAmplifierEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetAmplifierEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoAmplifierAttenuation(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetAmplifierAttenuation(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolumeControlEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeControlEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDigitalAudioOutputRaw(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDigitalAudioOutputRaw(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoAmplifierOverTemperature(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoEthernetLinkConnected(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoLocate(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyBool* iPropertyAmplifierEnabled;
    PropertyString* iPropertyAmplifierAttenuation;
    PropertyBool* iPropertyVolumeControlEnabled;
    PropertyBool* iPropertyDigitalAudioOutputRaw;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCOMPONENT1CPP

