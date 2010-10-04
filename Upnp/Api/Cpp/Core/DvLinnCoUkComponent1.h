#ifndef HEADER_DVLINNCOUKCOMPONENT1
#define HEADER_DVLINNCOUKCOMPONENT1

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
 * Base Device for linn.co.uk:Component:1
 */
class DvServiceLinnCoUkComponent1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkComponent1() {}
    void SetPropertyAmplifierEnabled(TBool aValue);
    void GetPropertyAmplifierEnabled(TBool& aValue);
    void SetPropertyAmplifierAttenuation(const Brx& aValue);
    void GetPropertyAmplifierAttenuation(Brhz& aValue);
    void SetPropertyVolumeControlEnabled(TBool aValue);
    void GetPropertyVolumeControlEnabled(TBool& aValue);
    void SetPropertyDigitalAudioOutputRaw(TBool aValue);
    void GetPropertyDigitalAudioOutputRaw(TBool& aValue);
protected:
    DvServiceLinnCoUkComponent1(DvDevice& aDevice);
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
    virtual void AmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    virtual void SetAmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    virtual void AmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaAttenuation);
    virtual void SetAmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaAttenuation);
    virtual void SetVolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    virtual void VolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    virtual void SetDigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, TBool aaRaw);
    virtual void DigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRaw);
    virtual void AmplifierOverTemperature(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOverTemperature);
    virtual void EthernetLinkConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaLinkConnected);
    virtual void Locate(IInvocationResponse& aResponse, TUint aVersion);
private:
    DvServiceLinnCoUkComponent1();
    void DoAmplifierEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetAmplifierEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoAmplifierAttenuation(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetAmplifierAttenuation(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeControlEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoVolumeControlEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDigitalAudioOutputRaw(IDvInvocation& aInvocation, TUint aVersion);
    void DoDigitalAudioOutputRaw(IDvInvocation& aInvocation, TUint aVersion);
    void DoAmplifierOverTemperature(IDvInvocation& aInvocation, TUint aVersion);
    void DoEthernetLinkConnected(IDvInvocation& aInvocation, TUint aVersion);
    void DoLocate(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyBool* iPropertyAmplifierEnabled;
    PropertyString* iPropertyAmplifierAttenuation;
    PropertyBool* iPropertyVolumeControlEnabled;
    PropertyBool* iPropertyDigitalAudioOutputRaw;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCOMPONENT1

