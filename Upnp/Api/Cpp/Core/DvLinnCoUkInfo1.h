#ifndef HEADER_DVLINNCOUKINFO1
#define HEADER_DVLINNCOUKINFO1

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
 * Base Device for linn.co.uk:Info:1
 */
class DvServiceLinnCoUkInfo1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkInfo1() {}
    TBool SetPropertyTrackCount(TUint aValue);
    void GetPropertyTrackCount(TUint& aValue);
    TBool SetPropertyDetailsCount(TUint aValue);
    void GetPropertyDetailsCount(TUint& aValue);
    TBool SetPropertyMetatextCount(TUint aValue);
    void GetPropertyMetatextCount(TUint& aValue);
    TBool SetPropertyUri(const Brx& aValue);
    void GetPropertyUri(Brhz& aValue);
    TBool SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    TBool SetPropertyDuration(TUint aValue);
    void GetPropertyDuration(TUint& aValue);
    TBool SetPropertyBitRate(TUint aValue);
    void GetPropertyBitRate(TUint& aValue);
    TBool SetPropertyBitDepth(TUint aValue);
    void GetPropertyBitDepth(TUint& aValue);
    TBool SetPropertySampleRate(TUint aValue);
    void GetPropertySampleRate(TUint& aValue);
    TBool SetPropertyLossless(TBool aValue);
    void GetPropertyLossless(TBool& aValue);
    TBool SetPropertyCodecName(const Brx& aValue);
    void GetPropertyCodecName(Brhz& aValue);
    TBool SetPropertyMetatext(const Brx& aValue);
    void GetPropertyMetatext(Brhz& aValue);
protected:
    DvServiceLinnCoUkInfo1(DvDevice& aDevice);
    void EnableActionCounters();
    void EnableActionTrack();
    void EnableActionDetails();
    void EnableActionMetatext();
private:
    virtual void Counters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDetailsCount, IInvocationResponseUint& aaMetatextCount);
    virtual void Track(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata);
    virtual void Details(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaBitRate, IInvocationResponseUint& aaBitDepth, IInvocationResponseUint& aaSampleRate, IInvocationResponseBool& aaLossless, IInvocationResponseString& aaCodecName);
    virtual void Metatext(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMetatext);
private:
    DvServiceLinnCoUkInfo1();
    void DoCounters(IDvInvocation& aInvocation, TUint aVersion);
    void DoTrack(IDvInvocation& aInvocation, TUint aVersion);
    void DoDetails(IDvInvocation& aInvocation, TUint aVersion);
    void DoMetatext(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDetailsCount;
    PropertyUint* iPropertyMetatextCount;
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertyBitRate;
    PropertyUint* iPropertyBitDepth;
    PropertyUint* iPropertySampleRate;
    PropertyBool* iPropertyLossless;
    PropertyString* iPropertyCodecName;
    PropertyString* iPropertyMetatext;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKINFO1

