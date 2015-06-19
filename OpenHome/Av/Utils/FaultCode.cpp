#include <OpenHome/Av/Utils/FaultCode.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

class FaultCodeMaker : public FaultCode
{
public:
    FaultCodeMaker(TUint aCode, const TChar* aReason);
};

FaultCodeMaker::FaultCodeMaker(TUint aCode, const TChar* aReason)
    : FaultCode(aCode, aReason)
{
}


const FaultCode FaultCode::kSourceNotFound = FaultCodeMaker(801, "Source not found");
const FaultCode FaultCode::kActionNotImplemented = FaultCodeMaker(899, "Wip - action not (yet) implemented");

TUint FaultCode::Code() const
{
    return iCode;
}

const Brx& FaultCode::Description() const
{
    return iDescription;
}

void FaultCode::Report(Net::IDvInvocation& aInvocation, const FaultCode& aFault)
{ // static
    aInvocation.Error(aFault.Code(), aFault.Description());
}

FaultCode::FaultCode(TUint aCode, const TChar* aDescription)
    : iCode(aCode)
    , iDescription(aDescription)
{
}
