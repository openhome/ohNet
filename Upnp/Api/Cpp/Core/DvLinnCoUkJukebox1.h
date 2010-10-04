#ifndef HEADER_DVLINNCOUKJUKEBOX1
#define HEADER_DVLINNCOUKJUKEBOX1

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
 * Base Device for linn.co.uk:Jukebox:1
 */
class DvServiceLinnCoUkJukebox1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkJukebox1() {}
    void SetPropertyCurrentPreset(TUint aValue);
    void GetPropertyCurrentPreset(TUint& aValue);
    void SetPropertyPresetPrefix(const Brx& aValue);
    void GetPropertyPresetPrefix(Brhz& aValue);
    void SetPropertyAlbumArtFileName(const Brx& aValue);
    void GetPropertyAlbumArtFileName(Brhz& aValue);
protected:
    DvServiceLinnCoUkJukebox1(DvDevice& aDevice);
    void EnableActionSetPresetPrefix();
    void EnableActionPresetPrefix();
    void EnableActionSetAlbumArtFileName();
    void EnableActionAlbumArtFileName();
    void EnableActionSetCurrentPreset();
    void EnableActionCurrentPreset();
    void EnableActionPresetMetaData();
    void EnableActionLoadManifest();
private:
    virtual void SetPresetPrefix(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri);
    virtual void PresetPrefix(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri);
    virtual void SetAlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName);
    virtual void AlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName);
    virtual void SetCurrentPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset);
    virtual void CurrentPreset(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPreset);
    virtual void PresetMetaData(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset, IInvocationResponseString& aaMetaData);
    virtual void LoadManifest(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTotalPresets);
private:
    DvServiceLinnCoUkJukebox1();
    void DoSetPresetPrefix(IDvInvocation& aInvocation, TUint aVersion);
    void DoPresetPrefix(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetAlbumArtFileName(IDvInvocation& aInvocation, TUint aVersion);
    void DoAlbumArtFileName(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetCurrentPreset(IDvInvocation& aInvocation, TUint aVersion);
    void DoCurrentPreset(IDvInvocation& aInvocation, TUint aVersion);
    void DoPresetMetaData(IDvInvocation& aInvocation, TUint aVersion);
    void DoLoadManifest(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyCurrentPreset;
    PropertyString* iPropertyPresetPrefix;
    PropertyString* iPropertyAlbumArtFileName;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKJUKEBOX1

