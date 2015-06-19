#ifndef HEADER_FORM_URL
#define HEADER_FORM_URL

#include <OpenHome/Buffer.h>

namespace OpenHome {
    class IWriter;
namespace Av {

class FormUrl
{
public:
    static void Encode(IWriter& aWriter, const Brx& aValue);
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_FORM_URL