#ifndef HEADER_DVLINNCOUKCOMPONENT1
#define HEADER_DVLINNCOUKCOMPONENT1

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
 * Base Device for linn.co.uk:Component:1
 */
class DvProviderLinnCoUkComponent1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkComponent1() {}
    TBool SetPropertyAmplifierEnabled(TBool aValue);
    void GetPropertyAmplifierEnabled(TBool& aValue);
    TBool SetPropertyAmplifierAttenuation(const Brx& aValue);
    void GetPropertyAmplifierAttenuation(Brhz& aValue);
    TBool SetPropertyVolumeControlEnabled(TBool aValue);
    void GetPropertyVolumeControlEnabled(TBool& aValue);
    TBool SetPropertyDigitalAudioOutputRaw(TBool aValue);
    void GetPropertyDigitalAudioOutputRaw(TBool& aValue);
protected:
    DvProviderLinnCoUkComponent1(DvDevice& aDevice);
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
    DvProviderLinnCoUkComponent1();
    void DoAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion);
    void DoDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion);
    void DoAmplifierOverTemperature(IDviInvocation& aInvocation, TUint aVersion);
    void DoEthernetLinkConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoLocate(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyBool* iPropertyAmplifierEnabled;
    PropertyString* iPropertyAmplifierAttenuation;
    PropertyBool* iPropertyVolumeControlEnabled;
    PropertyBool* iPropertyDigitalAudioOutputRaw;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCOMPONENT1

