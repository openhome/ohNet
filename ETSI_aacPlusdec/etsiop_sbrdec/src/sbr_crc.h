/*
   CRC check routines
 */

#ifndef __SBR_CRC_H
#define __SBR_CRC_H


#include "FFR_bitbuffer.h"


/* some useful crc polynoms:

crc5: x^5+x^4+x^2+x^1+1
crc6: x^6+x^5+x^3+x^2+x+1
crc7: x^7+x^6+x^2+1
crc8: x^8+x^2+x+x+1
*/

/* default SBR CRC */  /* G(x) = x^10 + x^9 + x^5 + x^4 + x + 1 */
#define SBR_CRC_POLY                  0x0233
#define SBR_CRC_MASK                  0x0200
#define SBR_CRC_START                 0x0000
#define SBR_CRC_RANGE                 0x03FF

typedef struct
{
  Word16 crcState;
  Word16 crcMask;
  Word16 crcPoly;
}
CRC_BUFFER;

typedef CRC_BUFFER *HANDLE_CRC;

Flag SbrCrcCheck (HANDLE_BIT_BUF hBitBuf, Word16 NrCrcBits);


#endif
