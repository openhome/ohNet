#ifndef HEADER_DVRESOURCEWRITER
#define HEADER_DVRESOURCEWRITER

#include <OsTypes.h>

namespace Zapp {

class IResourceWriter
{
public:
    virtual void WriteResourceBegin(uint32_t aTotalBytes, const char* aMimeType=NULL) = 0;
    virtual void WriteResource(const uint8_t* aData, uint32_t aBytes) = 0;
    virtual void WriteResourceEnd() = 0;
};

} // namespace Zapp

#endif // HEADER_DVRESOURCEWRITER
