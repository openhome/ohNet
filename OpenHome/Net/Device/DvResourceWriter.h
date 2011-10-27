#ifndef HEADER_DVRESOURCEWRITER
#define HEADER_DVRESOURCEWRITER

#include <OpenHome/OsTypes.h>

namespace OpenHome {
namespace Net {

/**
 * Interface passed to implementors of DvDevice allowing them to serve UI files to Control Points
 * @ingroup Device
 */
class IResourceWriter
{
public:
    /**
     * Must be called before writing any file data
     *
     * @param[in] aTotalBytes  Size in bytes of the file.  Can be 0 if size is unknown.
     * @param[in] aMimeType    MIME type of the file.  May be NULL if this is unknown.
     */
    virtual void WriteResourceBegin(uint32_t aTotalBytes, const char* aMimeType=NULL) = 0;
    /**
     * Called to write a block of file data
     *
     * Will be called 0..n times after WriteResourceBegin and before WriteResourceEnd
     *
     * @param[in] aData        File data to write
     * @param[in] aBytes       Size in bytes of aData
     */
    virtual void WriteResource(const uint8_t* aData, uint32_t aBytes) = 0;
    /**
     * Called when serving of a file is complete
     *
     * Must only be called after a call to WriteResourceBegin.
     * An error writing the file can be inferred if WriteResource has not been called or
     * if aTotalBytes was non-zero in the WriteResourceBegin callback and the sum of aBytes
     * values in the WriteResource callbacks does not match aTotalBytes.
     */
    virtual void WriteResourceEnd() = 0;

    virtual ~IResourceWriter() {}
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVRESOURCEWRITER
