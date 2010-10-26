#ifndef HEADER_DVMUSICOPENHOMEORGSENDER1
#define HEADER_DVMUSICOPENHOMEORGSENDER1

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
 * Base Device for music.openhome.org:Sender:1
 */
class DvServiceMusicOpenhomeOrgSender1 : public DvService
{
public:
    virtual ~DvServiceMusicOpenhomeOrgSender1() {}
    void SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    void SetPropertyAudio(TBool aValue);
    void GetPropertyAudio(TBool& aValue);
    void SetPropertyStatus(const Brx& aValue);
    void GetPropertyStatus(Brhz& aValue);
    void SetPropertyAttributes(const Brx& aValue);
    void GetPropertyAttributes(Brhz& aValue);
protected:
    DvServiceMusicOpenhomeOrgSender1(DvDevice& aDevice);
    void EnableActionMetadata();
    void EnableActionAudio();
    void EnableActionStatus();
    void EnableActionAttributes();
private:
    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    virtual void Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
private:
    DvServiceMusicOpenhomeOrgSender1();
    void DoMetadata(IDvInvocation& aInvocation, TUint aVersion);
    void DoAudio(IDvInvocation& aInvocation, TUint aVersion);
    void DoStatus(IDvInvocation& aInvocation, TUint aVersion);
    void DoAttributes(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyMetadata;
    PropertyBool* iPropertyAudio;
    PropertyString* iPropertyStatus;
    PropertyString* iPropertyAttributes;
};

} // namespace Zapp

#endif // HEADER_DVMUSICOPENHOMEORGSENDER1

