#ifndef HEADER_DVLINNCOUKRADIO1CPP
#define HEADER_DVLINNCOUKRADIO1CPP

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
 * Base Device for linn.co.uk:Radio:1
 */
class DvServiceLinnCoUkRadio1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkRadio1Cpp() {}
    void SetPropertyChannelUri(const std::string& aValue);
    void GetPropertyChannelUri(std::string& aValue);
    void SetPropertyChannelMetadata(const std::string& aValue);
    void GetPropertyChannelMetadata(std::string& aValue);
    void SetPropertyTransportState(const std::string& aValue);
    void GetPropertyTransportState(std::string& aValue);
    void SetPropertyProtocolInfo(const std::string& aValue);
    void GetPropertyProtocolInfo(std::string& aValue);
    void SetPropertyId(uint32_t aValue);
    void GetPropertyId(uint32_t& aValue);
    void SetPropertyIdArray(const std::string& aValue);
    void GetPropertyIdArray(std::string& aValue);
    void SetPropertyIdsMax(uint32_t aValue);
    void GetPropertyIdsMax(uint32_t& aValue);
protected:
    DvServiceLinnCoUkRadio1Cpp(DvDeviceStd& aDevice);
    void EnableActionPlay();
    void EnableActionPause();
    void EnableActionStop();
    void EnableActionSeekSecondAbsolute();
    void EnableActionSeekSecondRelative();
    void EnableActionChannel();
    void EnableActionSetChannel();
    void EnableActionProtocolInfo();
    void EnableActionTransportState();
    void EnableActionId();
    void EnableActionSetId();
    void EnableActionRead();
    void EnableActionReadList();
    void EnableActionIdArray();
    void EnableActionIdArrayChanged();
    void EnableActionIdsMax();
private:
    virtual void Play(uint32_t aVersion);
    virtual void Pause(uint32_t aVersion);
    virtual void Stop(uint32_t aVersion);
    virtual void SeekSecondAbsolute(uint32_t aVersion, uint32_t aaSecond);
    virtual void SeekSecondRelative(uint32_t aVersion, int32_t aaSecond);
    virtual void Channel(uint32_t aVersion, std::string& aaUri, std::string& aaMetadata);
    virtual void SetChannel(uint32_t aVersion, const std::string& aaUri, const std::string& aaMetadata);
    virtual void ProtocolInfo(uint32_t aVersion, std::string& aaInfo);
    virtual void TransportState(uint32_t aVersion, std::string& aaState);
    virtual void Id(uint32_t aVersion, uint32_t& aaId);
    virtual void SetId(uint32_t aVersion, uint32_t aaId, const std::string& aaUri);
    virtual void Read(uint32_t aVersion, uint32_t aaId, std::string& aaMetadata);
    virtual void ReadList(uint32_t aVersion, const std::string& aaIdList, std::string& aaMetadataList);
    virtual void IdArray(uint32_t aVersion, uint32_t& aaIdArrayToken, std::string& aaIdArray);
    virtual void IdArrayChanged(uint32_t aVersion, uint32_t aaIdArrayToken, bool& aaIdArrayChanged);
    virtual void IdsMax(uint32_t aVersion, uint32_t& aaIdsMax);
private:
    DvServiceLinnCoUkRadio1Cpp();
    void DoPlay(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPause(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStop(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondAbsolute(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondRelative(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoChannel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetChannel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoProtocolInfo(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoTransportState(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoId(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetId(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoRead(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoReadList(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoIdArray(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoIdArrayChanged(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoIdsMax(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyChannelUri;
    PropertyString* iPropertyChannelMetadata;
    PropertyString* iPropertyTransportState;
    PropertyString* iPropertyProtocolInfo;
    PropertyUint* iPropertyId;
    PropertyBinary* iPropertyIdArray;
    PropertyUint* iPropertyIdsMax;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKRADIO1CPP

