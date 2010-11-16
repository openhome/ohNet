#ifndef HEADER_DVAVOPENHOMEORGSENDER1
#define HEADER_DVAVOPENHOMEORGSENDER1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for av.openhome.org:Sender:1
 */
class DvProviderAvOpenhomeOrgSender1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgSender1() {}
    TBool SetPropertyPresentationUrl(const Brx& aValue);
    void GetPropertyPresentationUrl(Brhz& aValue);
    TBool SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    TBool SetPropertyAudio(TBool aValue);
    void GetPropertyAudio(TBool& aValue);
    TBool SetPropertyStatus(const Brx& aValue);
    void GetPropertyStatus(Brhz& aValue);
    TBool SetPropertyAttributes(const Brx& aValue);
    void GetPropertyAttributes(Brhz& aValue);
protected:
    DvProviderAvOpenhomeOrgSender1(DvDevice& aDevice);
    void EnableActionPresentationUrl();
    void EnableActionMetadata();
    void EnableActionAudio();
    void EnableActionStatus();
    void EnableActionAttributes();
private:
    virtual void PresentationUrl(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    virtual void Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
private:
    DvProviderAvOpenhomeOrgSender1();
    void DoPresentationUrl(IDvInvocation& aInvocation, TUint aVersion);
    void DoMetadata(IDvInvocation& aInvocation, TUint aVersion);
    void DoAudio(IDvInvocation& aInvocation, TUint aVersion);
    void DoStatus(IDvInvocation& aInvocation, TUint aVersion);
    void DoAttributes(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyPresentationUrl;
    PropertyString* iPropertyMetadata;
    PropertyBool* iPropertyAudio;
    PropertyString* iPropertyStatus;
    PropertyString* iPropertyAttributes;
};

} // namespace Zapp

#endif // HEADER_DVAVOPENHOMEORGSENDER1

