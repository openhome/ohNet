#ifndef HEADER_DVLINNCOUKDS1CPP
#define HEADER_DVLINNCOUKDS1CPP

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
 * Base Device for linn.co.uk:Ds:1
 */
class DvServiceLinnCoUkDs1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkDs1Cpp() {}
    void SetPropertySupportedProtocols(const std::string& aValue);
    void GetPropertySupportedProtocols(std::string& aValue);
    void SetPropertyTrackDuration(uint32_t aValue);
    void GetPropertyTrackDuration(uint32_t& aValue);
    void SetPropertyTrackBitRate(uint32_t aValue);
    void GetPropertyTrackBitRate(uint32_t& aValue);
    void SetPropertyTrackLossless(bool aValue);
    void GetPropertyTrackLossless(bool& aValue);
    void SetPropertyTrackBitDepth(uint32_t aValue);
    void GetPropertyTrackBitDepth(uint32_t& aValue);
    void SetPropertyTrackSampleRate(uint32_t aValue);
    void GetPropertyTrackSampleRate(uint32_t& aValue);
    void SetPropertyTrackCodecName(const std::string& aValue);
    void GetPropertyTrackCodecName(std::string& aValue);
    void SetPropertyTrackId(uint32_t aValue);
    void GetPropertyTrackId(uint32_t& aValue);
    void SetPropertyTransportState(const std::string& aValue);
    void GetPropertyTransportState(std::string& aValue);
protected:
    DvServiceLinnCoUkDs1Cpp(DvDeviceStd& aDevice);
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
    virtual void Play(uint32_t aVersion);
    virtual void Pause(uint32_t aVersion);
    virtual void Stop(uint32_t aVersion);
    virtual void SeekSecondAbsolute(uint32_t aVersion, uint32_t aaSecond);
    virtual void SeekSecondRelative(uint32_t aVersion, int32_t aaSecond);
    virtual void SeekTrackId(uint32_t aVersion, uint32_t aaTrackId);
    virtual void SeekTrackAbsolute(uint32_t aVersion, uint32_t aaTrack);
    virtual void SeekTrackRelative(uint32_t aVersion, int32_t aaTrack);
    virtual void State(uint32_t aVersion, std::string& aaTransportState, uint32_t& aaTrackDuration, uint32_t& aaTrackBitRate, bool& aaTrackLossless, uint32_t& aaTrackBitDepth, uint32_t& aaTrackSampleRate, std::string& aaTrackCodecName, uint32_t& aaTrackId);
    virtual void ProtocolInfo(uint32_t aVersion, std::string& aaSupportedProtocols);
private:
    DvServiceLinnCoUkDs1Cpp();
    void DoPlay(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPause(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStop(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondAbsolute(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondRelative(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSeekTrackId(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSeekTrackAbsolute(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSeekTrackRelative(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoState(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoProtocolInfo(IDvInvocation& aInvocation, uint32_t aVersion);
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

#endif // HEADER_DVLINNCOUKDS1CPP

