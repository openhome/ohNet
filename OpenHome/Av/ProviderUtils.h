#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
namespace Net {
    class IDvInvocationResponseString;
} // namespace Net
namespace Av {

class WriterInvocationResponseString : public IWriter, private INonCopyable
{
public:
    WriterInvocationResponseString(Net::IDvInvocationResponseString& aIrs);
    ~WriterInvocationResponseString();
public: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
private:
    Net::IDvInvocationResponseString& iIrs;
};

} // namespace Av
} // namespace OpenHome

