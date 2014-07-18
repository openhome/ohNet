#ifndef HEADER_ARCH
#define HEADER_ARCH

#include <OpenHome/Types.h>
#include <OpenHome/OsWrapper.h>

namespace OpenHome {

class Arch
{
public:
#ifdef DEFINE_LITTLE_ENDIAN
    inline static TUint16 BigEndian2(TUint16 x) {return (TUint16)(SwapEndian16(x));}
    inline static TUint32 BigEndian4(TUint32 x) {return (TUint32)(SwapEndian32(x));}
    inline static TUint64 BigEndian8(TUint64 x)
        { return (TUint64(BigEndian4(TUint32(x))) << 32) | BigEndian4(TUint32(x>>32)); }
    inline static TUint16 LittleEndian2(TUint16 x) {return x;}
    inline static TUint32 LittleEndian4(TUint32 x) {return x;}
    inline static TUint64 LittleEndian8(TUint64 x) {return x;}
#elif defined DEFINE_BIG_ENDIAN
    inline static TUint16 BigEndian2(TUint16 x) {return x;}
    inline static TUint32 BigEndian4(TUint32 x) {return x;}
    inline static TUint64 BigEndian8(TUint64 x) {return x;}
    inline static TUint16 LittleEndian2(TUint16 x) {return (SwapEndian16(x)); }
    inline static TUint32 LittleEndian4(TUint32 x) {return (SwapEndian32(x)); }
    inline static TUint64 LittleEndian8(TUint64 x)
        { return (TUint64(LittleEndian4(TUint32(x))) << 32) | LittleEndian4(TUint32(x>>32)); }
#else
#error ENDIANNESS not defined
#endif //DEFINE_LITTLE_ENDIAN
};

} // namespace OpenHome

#endif  // HEADER_ARCH

