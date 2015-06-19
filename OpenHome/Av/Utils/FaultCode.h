#ifndef HEADER_FAULT_CODE
#define HEADER_FAULT_CODE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

namespace OpenHome {
namespace Av {

class FaultCode
{
public:
    static const FaultCode kSourceNotFound;
    static const FaultCode kActionNotImplemented;
public:
    TUint Code() const;
    const Brx& Description() const;
    static void Report(Net::IDvInvocation& aInvocation, const FaultCode& aFault); // throws
protected:
    FaultCode(TUint aCode, const TChar* aDescription);
private:
    TUint iCode;
    Brn iDescription;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_FAULT_CODE
