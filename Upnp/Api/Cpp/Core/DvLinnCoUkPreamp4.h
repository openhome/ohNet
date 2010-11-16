#ifndef HEADER_DVLINNCOUKPREAMP4
#define HEADER_DVLINNCOUKPREAMP4

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
 * Base Device for linn.co.uk:Preamp:4
 */
class DvProviderLinnCoUkPreamp4 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPreamp4() {}
    TBool SetPropertyVolume(TUint aValue);
    void GetPropertyVolume(TUint& aValue);
    TBool SetPropertyMute(TBool aValue);
    void GetPropertyMute(TBool& aValue);
    TBool SetPropertyBalance(TInt aValue);
    void GetPropertyBalance(TInt& aValue);
    TBool SetPropertyVolumeLimit(TUint aValue);
    void GetPropertyVolumeLimit(TUint& aValue);
    TBool SetPropertyStartupVolume(TUint aValue);
    void GetPropertyStartupVolume(TUint& aValue);
    TBool SetPropertyStartupVolumeEnabled(TBool aValue);
    void GetPropertyStartupVolumeEnabled(TBool& aValue);
protected:
    DvProviderLinnCoUkPreamp4(DvDevice& aDevice);
    void EnableActionVolumeInc();
    void EnableActionVolumeDec();
    void EnableActionSetVolume();
    void EnableActionVolume();
    void EnableActionSetMute();
    void EnableActionMute();
    void EnableActionSetBalance();
    void EnableActionBalance();
    void EnableActionSetVolumeLimit();
    void EnableActionVolumeLimit();
    void EnableActionSetStartupVolume();
    void EnableActionStartupVolume();
    void EnableActionSetStartupVolumeEnabled();
    void EnableActionStartupVolumeEnabled();
private:
    virtual void VolumeInc(IInvocationResponse& aResponse, TUint aVersion);
    virtual void VolumeDec(IInvocationResponse& aResponse, TUint aVersion);
    virtual void SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolume);
    virtual void Volume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolume);
    virtual void SetMute(IInvocationResponse& aResponse, TUint aVersion, TBool aaMute);
    virtual void Mute(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaMute);
    virtual void SetBalance(IInvocationResponse& aResponse, TUint aVersion, TInt aaBalance);
    virtual void Balance(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aaBalance);
    virtual void SetVolumeLimit(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolumeLimit);
    virtual void VolumeLimit(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolumeLimit);
    virtual void SetStartupVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaStartupVolume);
    virtual void StartupVolume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStartupVolume);
    virtual void SetStartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupVolumeEnabled);
    virtual void StartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupVolumeEnabled);
private:
    DvProviderLinnCoUkPreamp4();
    void DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBalance(IDviInvocation& aInvocation, TUint aVersion);
    void DoBalance(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeLimit(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyVolume;
    PropertyBool* iPropertyMute;
    PropertyInt* iPropertyBalance;
    PropertyUint* iPropertyVolumeLimit;
    PropertyUint* iPropertyStartupVolume;
    PropertyBool* iPropertyStartupVolumeEnabled;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPREAMP4

