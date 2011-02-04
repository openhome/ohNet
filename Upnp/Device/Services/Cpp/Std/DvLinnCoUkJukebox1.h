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
 * Provider for the linn.co.uk:Jukebox:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkJukebox1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkJukebox1Cpp() {}
    /**
     * Set the value of the CurrentPreset property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyCurrentPreset(uint32_t aValue);
    /**
     * Get a copy of the value of the CurrentPreset property
     */
    void GetPropertyCurrentPreset(uint32_t& aValue);
    /**
     * Set the value of the PresetPrefix property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyPresetPrefix(const std::string& aValue);
    /**
     * Get a copy of the value of the PresetPrefix property
     */
    void GetPropertyPresetPrefix(std::string& aValue);
    /**
     * Set the value of the AlbumArtFileName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyAlbumArtFileName(const std::string& aValue);
    /**
     * Get a copy of the value of the AlbumArtFileName property
     */
    void GetPropertyAlbumArtFileName(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkJukebox1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action SetPresetPrefix is supported.
     * The action's availability will be published in the device's service.xml.
     * SetPresetPrefix must be overridden if this is called.
     */
    void EnableActionSetPresetPrefix();
    /**
     * Signal that the action PresetPrefix is supported.
     * The action's availability will be published in the device's service.xml.
     * PresetPrefix must be overridden if this is called.
     */
    void EnableActionPresetPrefix();
    /**
     * Signal that the action SetAlbumArtFileName is supported.
     * The action's availability will be published in the device's service.xml.
     * SetAlbumArtFileName must be overridden if this is called.
     */
    void EnableActionSetAlbumArtFileName();
    /**
     * Signal that the action AlbumArtFileName is supported.
     * The action's availability will be published in the device's service.xml.
     * AlbumArtFileName must be overridden if this is called.
     */
    void EnableActionAlbumArtFileName();
    /**
     * Signal that the action SetCurrentPreset is supported.
     * The action's availability will be published in the device's service.xml.
     * SetCurrentPreset must be overridden if this is called.
     */
    void EnableActionSetCurrentPreset();
    /**
     * Signal that the action CurrentPreset is supported.
     * The action's availability will be published in the device's service.xml.
     * CurrentPreset must be overridden if this is called.
     */
    void EnableActionCurrentPreset();
    /**
     * Signal that the action PresetMetaData is supported.
     * The action's availability will be published in the device's service.xml.
     * PresetMetaData must be overridden if this is called.
     */
    void EnableActionPresetMetaData();
    /**
     * Signal that the action LoadManifest is supported.
     * The action's availability will be published in the device's service.xml.
     * LoadManifest must be overridden if this is called.
     */
    void EnableActionLoadManifest();
private:
    /**
     * SetPresetPrefix action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetPrefix action for the owning device.
     * Must be implemented iff EnableActionSetPresetPrefix was called.
     */
    virtual void SetPresetPrefix(uint32_t aVersion, const std::string& aaUri);
    /**
     * PresetPrefix action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetPrefix action for the owning device.
     * Must be implemented iff EnableActionPresetPrefix was called.
     */
    virtual void PresetPrefix(uint32_t aVersion, std::string& aaUri);
    /**
     * SetAlbumArtFileName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetAlbumArtFileName action for the owning device.
     * Must be implemented iff EnableActionSetAlbumArtFileName was called.
     */
    virtual void SetAlbumArtFileName(uint32_t aVersion, const std::string& aaName);
    /**
     * AlbumArtFileName action.
     *
     * Will be called when the device stack receives an invocation of the
     * AlbumArtFileName action for the owning device.
     * Must be implemented iff EnableActionAlbumArtFileName was called.
     */
    virtual void AlbumArtFileName(uint32_t aVersion, std::string& aaName);
    /**
     * SetCurrentPreset action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetCurrentPreset action for the owning device.
     * Must be implemented iff EnableActionSetCurrentPreset was called.
     */
    virtual void SetCurrentPreset(uint32_t aVersion, uint32_t aaPreset);
    /**
     * CurrentPreset action.
     *
     * Will be called when the device stack receives an invocation of the
     * CurrentPreset action for the owning device.
     * Must be implemented iff EnableActionCurrentPreset was called.
     */
    virtual void CurrentPreset(uint32_t aVersion, uint32_t& aaPreset);
    /**
     * PresetMetaData action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetMetaData action for the owning device.
     * Must be implemented iff EnableActionPresetMetaData was called.
     */
    virtual void PresetMetaData(uint32_t aVersion, uint32_t aaPreset, std::string& aaMetaData);
    /**
     * LoadManifest action.
     *
     * Will be called when the device stack receives an invocation of the
     * LoadManifest action for the owning device.
     * Must be implemented iff EnableActionLoadManifest was called.
     */
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

