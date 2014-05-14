#include <OpenHome/Os.h>

uint16_t SwapEndian16(uint16_t x)
{
    return ((x & 0xff00) >> 8)
        |  ((x & 0x00ff) << 8);
}

uint32_t SwapEndian32(uint32_t x)
{
    return ((x & 0xff000000) >> 24)
        |  ((x & 0x00ff0000) >> 8 )
        |  ((x & 0x0000ff00) << 8 )
        |  ((x & 0x000000ff) << 24);
}

