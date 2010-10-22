#ifndef HEADER_DVLINNCOUKMULTIPUSSENDER1
#define HEADER_DVLINNCOUKMULTIPUSSENDER1

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
 * Base Device for linn.co.uk:MultipusSender:1
 */
class DvServiceLinnCoUkMultipusSender1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkMultipusSender1() {}
    void SetPropertyEnabled(TBool aValue);
    void GetPropertyEnabled(TBool& aValue);
    void SetPropertyChannel(TUint aValue);
    void GetPropertyChannel(TUint& aValue);
    void SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    void SetPropertyAudio(TBool aValue);
    void GetPropertyAudio(TBool& aValue);
    void SetPropertyStatus(const Brx& aValue);
    void GetPropertyStatus(Brhz& aValue);
    void SetPropertyInfoAvailable(TBool aValue);
    void GetPropertyInfoAvailable(TBool& aValue);
    void SetPropertyTimeAvailable(TBool aValue);
    void GetPropertyTimeAvailable(TBool& aValue);
protected:
    DvServiceLinnCoUkMultipusSender1(DvDevice& aDevice);
    void EnableActionEnabled();
    void EnableActionSetEnabled();
    void EnableActionChannel();
    void EnableActionSetChannel();
    void EnableActionMetadata();
    void EnableActionAudio();
    void EnableActionStatus();
    void EnableActionInfoAvailable();
    void EnableActionTimeAvailable();
private:
    virtual void Enabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    virtual void SetEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aValue);
    virtual void Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
    virtual void SetChannel(IInvocationResponse& aResponse, TUint aVersion, TUint aValue);
    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    virtual void Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void InfoAvailable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    virtual void TimeAvailable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
private:
    DvServiceLinnCoUkMultipusSender1();
    void DoEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoChannel(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetChannel(IDvInvocation& aInvocation, TUint aVersion);
    void DoMetadata(IDvInvocation& aInvocation, TUint aVersion);
    void DoAudio(IDvInvocation& aInvocation, TUint aVersion);
    void DoStatus(IDvInvocation& aInvocation, TUint aVersion);
    void DoInfoAvailable(IDvInvocation& aInvocation, TUint aVersion);
    void DoTimeAvailable(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyBool* iPropertyEnabled;
    PropertyUint* iPropertyChannel;
    PropertyString* iPropertyMetadata;
    PropertyBool* iPropertyAudio;
    PropertyString* iPropertyStatus;
    PropertyBool* iPropertyInfoAvailable;
    PropertyBool* iPropertyTimeAvailable;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKMULTIPUSSENDER1

