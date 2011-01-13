#ifndef HEADER_DVLINNCOUKJUKEBOX1
#define HEADER_DVLINNCOUKJUKEBOX1

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
 * Provider for the linn.co.uk:Jukebox:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkJukebox1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkJukebox1() {}
    /**
     * Set the value of the CurrentPreset property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyCurrentPreset(TUint aValue);
    /**
     * Get a copy of the value of the CurrentPreset property
     */
    void GetPropertyCurrentPreset(TUint& aValue);
    /**
     * Set the value of the PresetPrefix property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyPresetPrefix(const Brx& aValue);
    /**
     * Get a copy of the value of the PresetPrefix property
     */
    void GetPropertyPresetPrefix(Brhz& aValue);
    /**
     * Set the value of the AlbumArtFileName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAlbumArtFileName(const Brx& aValue);
    /**
     * Get a copy of the value of the AlbumArtFileName property
     */
    void GetPropertyAlbumArtFileName(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkJukebox1(DvDevice& aDevice);
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
    virtual void SetPresetPrefix(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri);
    /**
     * PresetPrefix action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetPrefix action for the owning device.
     * Must be implemented iff EnableActionPresetPrefix was called.
     */
    virtual void PresetPrefix(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri);
    /**
     * SetAlbumArtFileName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetAlbumArtFileName action for the owning device.
     * Must be implemented iff EnableActionSetAlbumArtFileName was called.
     */
    virtual void SetAlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName);
    /**
     * AlbumArtFileName action.
     *
     * Will be called when the device stack receives an invocation of the
     * AlbumArtFileName action for the owning device.
     * Must be implemented iff EnableActionAlbumArtFileName was called.
     */
    virtual void AlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName);
    /**
     * SetCurrentPreset action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetCurrentPreset action for the owning device.
     * Must be implemented iff EnableActionSetCurrentPreset was called.
     */
    virtual void SetCurrentPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset);
    /**
     * CurrentPreset action.
     *
     * Will be called when the device stack receives an invocation of the
     * CurrentPreset action for the owning device.
     * Must be implemented iff EnableActionCurrentPreset was called.
     */
    virtual void CurrentPreset(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPreset);
    /**
     * PresetMetaData action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetMetaData action for the owning device.
     * Must be implemented iff EnableActionPresetMetaData was called.
     */
    virtual void PresetMetaData(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset, IInvocationResponseString& aaMetaData);
    /**
     * LoadManifest action.
     *
     * Will be called when the device stack receives an invocation of the
     * LoadManifest action for the owning device.
     * Must be implemented iff EnableActionLoadManifest was called.
     */
    virtual void LoadManifest(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTotalPresets);
private:
    DvProviderLinnCoUkJukebox1();
    void DoSetPresetPrefix(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetPrefix(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetAlbumArtFileName(IDviInvocation& aInvocation, TUint aVersion);
    void DoAlbumArtFileName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetCurrentPreset(IDviInvocation& aInvocation, TUint aVersion);
    void DoCurrentPreset(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetMetaData(IDviInvocation& aInvocation, TUint aVersion);
    void DoLoadManifest(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyCurrentPreset;
    PropertyString* iPropertyPresetPrefix;
    PropertyString* iPropertyAlbumArtFileName;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKJUKEBOX1

