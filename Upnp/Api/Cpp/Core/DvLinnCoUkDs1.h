#ifndef HEADER_DVLINNCOUKDS1
#define HEADER_DVLINNCOUKDS1

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
 * Base Device for linn.co.uk:Ds:1
 */
class DvServiceLinnCoUkDs1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkDs1() {}
    void SetPropertySupportedProtocols(const Brx& aValue);
    void GetPropertySupportedProtocols(Brhz& aValue);
    void SetPropertyTrackDuration(TUint aValue);
    void GetPropertyTrackDuration(TUint& aValue);
    void SetPropertyTrackBitRate(TUint aValue);
    void GetPropertyTrackBitRate(TUint& aValue);
    void SetPropertyTrackLossless(TBool aValue);
    void GetPropertyTrackLossless(TBool& aValue);
    void SetPropertyTrackBitDepth(TUint aValue);
    void GetPropertyTrackBitDepth(TUint& aValue);
    void SetPropertyTrackSampleRate(TUint aValue);
    void GetPropertyTrackSampleRate(TUint& aValue);
    void SetPropertyTrackCodecName(const Brx& aValue);
    void GetPropertyTrackCodecName(Brhz& aValue);
    void SetPropertyTrackId(TUint aValue);
    void GetPropertyTrackId(TUint& aValue);
    void SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
protected:
    DvServiceLinnCoUkDs1(DvDevice& aDevice);
    void EnableActionPlay();
    void EnableActionPause();
    void EnableActionStop();
    void EnableActionSeekSecondAbsolute();
    void EnableActionSeekSecondRelative();
    void EnableActionSeekTrackId();
    void EnableActionSeekTrackAbsolute();
    void EnableActionSeekTrackRelative();
    void EnableActionState();
    void EnableActionProtocolInfo();
private:
    virtual void Play(IInvocationResponse& aResponse, TUint aVersion);
    virtual void Pause(IInvocationResponse& aResponse, TUint aVersion);
    virtual void Stop(IInvocationResponse& aResponse, TUint aVersion);
    virtual void SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond);
    virtual void SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond);
    virtual void SeekTrackId(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrackId);
    virtual void SeekTrackAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaTrack);
    virtual void SeekTrackRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaTrack);
    virtual void State(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaTransportState, IInvocationResponseUint& aaTrackDuration, IInvocationResponseUint& aaTrackBitRate, IInvocationResponseBool& aaTrackLossless, IInvocationResponseUint& aaTrackBitDepth, IInvocationResponseUint& aaTrackSampleRate, IInvocationResponseString& aaTrackCodecName, IInvocationResponseUint& aaTrackId);
    virtual void ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSupportedProtocols);
private:
    DvServiceLinnCoUkDs1();
    void DoPlay(IDvInvocation& aInvocation, TUint aVersion);
    void DoPause(IDvInvocation& aInvocation, TUint aVersion);
    void DoStop(IDvInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondAbsolute(IDvInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondRelative(IDvInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackId(IDvInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackAbsolute(IDvInvocation& aInvocation, TUint aVersion);
    void DoSeekTrackRelative(IDvInvocation& aInvocation, TUint aVersion);
    void DoState(IDvInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertySupportedProtocols;
    PropertyUint* iPropertyTrackDuration;
    PropertyUint* iPropertyTrackBitRate;
    PropertyBool* iPropertyTrackLossless;
    PropertyUint* iPropertyTrackBitDepth;
    PropertyUint* iPropertyTrackSampleRate;
    PropertyString* iPropertyTrackCodecName;
    PropertyUint* iPropertyTrackId;
    PropertyString* iPropertyTransportState;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDS1

