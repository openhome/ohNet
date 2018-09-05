#ifndef HEADER_TESTBASICDV
#define HEADER_TESTBASICDV

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestBasic1.h>

namespace OpenHome {
namespace Net {

class ProviderTestBasic : public DvProviderOpenhomeOrgTestBasic1
{
public:
    ProviderTestBasic(DvDevice& aDevice);
private:
    void Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult);
    void EchoAllowedRangeUint(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult);
    void Decrement(IDvInvocation& aInvocation, TInt aValue, IDvInvocationResponseInt& aResult);
    void Toggle(IDvInvocation& aInvocation, TBool aValue, IDvInvocationResponseBool& aResult);
    void EchoString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult);
    void EchoAllowedValueString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult);
    void EchoBinary(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseBinary& aResult);
    void SetUint(IDvInvocation& aInvocation, TUint aValueUint);
    void GetUint(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint);
    void SetInt(IDvInvocation& aInvocation, TInt aValueInt);
    void GetInt(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValueInt);
    void SetBool(IDvInvocation& aInvocation, TBool aValueBool);
    void GetBool(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValueBool);
    void SetMultiple(IDvInvocation& aInvocation, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void GetMultiple(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint, IDvInvocationResponseInt& aValueInt, IDvInvocationResponseBool& aValueBool);
    void SetString(IDvInvocation& aInvocation, const Brx& aValueStr);
    void GetString(IDvInvocation& aInvocation, IDvInvocationResponseString& aValueStr);
    void SetBinary(IDvInvocation& aInvocation, const Brx& aValueBin);
    void GetBinary(IDvInvocation& aInvocation, IDvInvocationResponseBinary& aValueBin);
    void ReportError(IDvInvocation& aInvocation);
    void WriteFile(IDvInvocation& aInvocation, const Brx& aData, const Brx& aFileFullName);
    void Shutdown(IDvInvocation& aInvocation);
};

class DeviceBasic
{
public:
    DeviceBasic(DvStack& aDvStack);
    ~DeviceBasic();
    const Brx& Udn() const;
    DvDevice& Device();
private:
    DvDeviceStandard* iDevice;
    ProviderTestBasic* iTestBasic;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TESTBASICDV
