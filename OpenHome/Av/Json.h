#ifndef HEADER_JSON
#define HEADER_JSON

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
    class IWriter;
namespace Av{

class JsonStringSanitiser : public IWriter, public INonCopyable
{
public:
    JsonStringSanitiser(IWriter& aWriter);
public: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
private:
    void WriteSanitised(TByte aByte);
private:
    IWriter& iWriter;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_JSON
