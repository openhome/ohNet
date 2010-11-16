#ifndef HEADER_DVLINNCOUKJUKEBOX1CPP
#define HEADER_DVLINNCOUKJUKEBOX1CPP

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
 * Base Device for linn.co.uk:Jukebox:1
 */
class DvProviderLinnCoUkJukebox1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkJukebox1Cpp() {}
    bool SetPropertyCurrentPreset(uint32_t aValue);
    void GetPropertyCurrentPreset(uint32_t& aValue);
    bool SetPropertyPresetPrefix(const std::string& aValue);
    void GetPropertyPresetPrefix(std::string& aValue);
    bool SetPropertyAlbumArtFileName(const std::string& aValue);
    void GetPropertyAlbumArtFileName(std::string& aValue);
protected:
    DvProviderLinnCoUkJukebox1Cpp(DvDeviceStd& aDevice);
    void EnableActionSetPresetPrefix();
    void EnableActionPresetPrefix();
    void EnableActionSetAlbumArtFileName();
    void EnableActionAlbumArtFileName();
    void EnableActionSetCurrentPreset();
    void EnableActionCurrentPreset();
    void EnableActionPresetMetaData();
    void EnableActionLoadManifest();
private:
    virtual void SetPresetPrefix(uint32_t aVersion, const std::string& aaUri);
    virtual void PresetPrefix(uint32_t aVersion, std::string& aaUri);
    virtual void SetAlbumArtFileName(uint32_t aVersion, const std::string& aaName);
    virtual void AlbumArtFileName(uint32_t aVersion, std::string& aaName);
    virtual void SetCurrentPreset(uint32_t aVersion, uint32_t aaPreset);
    virtual void CurrentPreset(uint32_t aVersion, uint32_t& aaPreset);
    virtual void PresetMetaData(uint32_t aVersion, uint32_t aaPreset, std::string& aaMetaData);
    virtual void LoadManifest(uint32_t aVersion, uint32_t& aaTotalPresets);
private:
    DvProviderLinnCoUkJukebox1Cpp();
    void DoSetPresetPrefix(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPresetPrefix(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetAlbumArtFileName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoAlbumArtFileName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetCurrentPreset(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCurrentPreset(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPresetMetaData(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoLoadManifest(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyCurrentPreset;
    PropertyString* iPropertyPresetPrefix;
    PropertyString* iPropertyAlbumArtFileName;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKJUKEBOX1CPP

