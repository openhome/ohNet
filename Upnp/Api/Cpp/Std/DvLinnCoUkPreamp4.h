#ifndef HEADER_DVLINNCOUKPREAMP4CPP
#define HEADER_DVLINNCOUKPREAMP4CPP

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
 * Base Device for linn.co.uk:Preamp:4
 */
class DvServiceLinnCoUkPreamp4Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkPreamp4Cpp() {}
    void SetPropertyVolume(uint32_t aValue);
    void GetPropertyVolume(uint32_t& aValue);
    void SetPropertyMute(bool aValue);
    void GetPropertyMute(bool& aValue);
    void SetPropertyBalance(int32_t aValue);
    void GetPropertyBalance(int32_t& aValue);
    void SetPropertyVolumeLimit(uint32_t aValue);
    void GetPropertyVolumeLimit(uint32_t& aValue);
    void SetPropertyStartupVolume(uint32_t aValue);
    void GetPropertyStartupVolume(uint32_t& aValue);
    void SetPropertyStartupVolumeEnabled(bool aValue);
    void GetPropertyStartupVolumeEnabled(bool& aValue);
protected:
    DvServiceLinnCoUkPreamp4Cpp(DvDeviceStd& aDevice);
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
    virtual void VolumeInc(uint32_t aVersion);
    virtual void VolumeDec(uint32_t aVersion);
    virtual void SetVolume(uint32_t aVersion, uint32_t aaVolume);
    virtual void Volume(uint32_t aVersion, uint32_t& aaVolume);
    virtual void SetMute(uint32_t aVersion, bool aaMute);
    virtual void Mute(uint32_t aVersion, bool& aaMute);
    virtual void SetBalance(uint32_t aVersion, int32_t aaBalance);
    virtual void Balance(uint32_t aVersion, int32_t& aaBalance);
    virtual void SetVolumeLimit(uint32_t aVersion, uint32_t aaVolumeLimit);
    virtual void VolumeLimit(uint32_t aVersion, uint32_t& aaVolumeLimit);
    virtual void SetStartupVolume(uint32_t aVersion, uint32_t aaStartupVolume);
    virtual void StartupVolume(uint32_t aVersion, uint32_t& aaStartupVolume);
    virtual void SetStartupVolumeEnabled(uint32_t aVersion, bool aaStartupVolumeEnabled);
    virtual void StartupVolumeEnabled(uint32_t aVersion, bool& aaStartupVolumeEnabled);
private:
    DvServiceLinnCoUkPreamp4Cpp();
    void DoVolumeInc(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeDec(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolume(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoVolume(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetMute(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoMute(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetBalance(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoBalance(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolumeLimit(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeLimit(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupVolume(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStartupVolume(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupVolumeEnabled(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStartupVolumeEnabled(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyVolume;
    PropertyBool* iPropertyMute;
    PropertyInt* iPropertyBalance;
    PropertyUint* iPropertyVolumeLimit;
    PropertyUint* iPropertyStartupVolume;
    PropertyBool* iPropertyStartupVolumeEnabled;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPREAMP4CPP

