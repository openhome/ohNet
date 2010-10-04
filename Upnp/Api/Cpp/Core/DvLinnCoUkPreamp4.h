#ifndef HEADER_DVLINNCOUKPREAMP4
#define HEADER_DVLINNCOUKPREAMP4

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
 * Base Device for linn.co.uk:Preamp:4
 */
class DvServiceLinnCoUkPreamp4 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkPreamp4() {}
    void SetPropertyVolume(TUint aValue);
    void GetPropertyVolume(TUint& aValue);
    void SetPropertyMute(TBool aValue);
    void GetPropertyMute(TBool& aValue);
    void SetPropertyBalance(TInt aValue);
    void GetPropertyBalance(TInt& aValue);
    void SetPropertyVolumeLimit(TUint aValue);
    void GetPropertyVolumeLimit(TUint& aValue);
    void SetPropertyStartupVolume(TUint aValue);
    void GetPropertyStartupVolume(TUint& aValue);
    void SetPropertyStartupVolumeEnabled(TBool aValue);
    void GetPropertyStartupVolumeEnabled(TBool& aValue);
protected:
    DvServiceLinnCoUkPreamp4(DvDevice& aDevice);
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
    DvServiceLinnCoUkPreamp4();
    void DoVolumeInc(IDvInvocation& aInvocation, TUint aVersion);
    void DoVolumeDec(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetVolume(IDvInvocation& aInvocation, TUint aVersion);
    void DoVolume(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetMute(IDvInvocation& aInvocation, TUint aVersion);
    void DoMute(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetBalance(IDvInvocation& aInvocation, TUint aVersion);
    void DoBalance(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeLimit(IDvInvocation& aInvocation, TUint aVersion);
    void DoVolumeLimit(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStartupVolume(IDvInvocation& aInvocation, TUint aVersion);
    void DoStartupVolume(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStartupVolumeEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoStartupVolumeEnabled(IDvInvocation& aInvocation, TUint aVersion);
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

