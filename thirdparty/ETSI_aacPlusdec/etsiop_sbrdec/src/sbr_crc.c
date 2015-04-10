/*
   CRC check routines
 */

#include <assert.h>
#include "sbr_crc.h"
#include "FFR_bitbuffer.h"
#include "sbr_const.h"
#include "sbr_const.h"
#include "ffr.h"
#include "count.h"


const Word16 MAXCRCSTEP = 16;


/*!
  \brief     crc calculation
*/
static Word32
calcCRC (HANDLE_CRC hCrcBuf, Word32 bValue, Word16 nBits)
{
  Word16 i;
  Word32 bMask = L_shl(1L, sub(nBits, 1));/* counting operation */

  for (i = 0; i < nBits; i++) {
    Word16 flag, flag1;

    flag  = (hCrcBuf->crcState & hCrcBuf->crcMask) ? 1 : 0;                 logic16(); test(); move16();
    flag1 = (bMask & bValue) ? 1 : 0;                                       logic16(); test(); move16();

    flag ^= flag1;                                                          logic16();

    hCrcBuf->crcState = extract_l(L_shl(hCrcBuf->crcState, 1));             move16();

    test();
    if (flag) {
      hCrcBuf->crcState ^= hCrcBuf->crcPoly;                                logic16(); move16();
    }
    bMask = L_shr(bMask,1);
  }

  return (hCrcBuf->crcState);
}


/*!
  \brief     crc 
*/
static Word32
getCrc (HANDLE_BIT_BUF hBitBuf, Word16 NrBits)
{
  Word16 i;
  CRC_BUFFER CrcBuf;
  Word16 CrcStep, CrcNrBitsRest;
  Word32 bValue;

  CrcBuf.crcState = SBR_CRC_START;                                          move16();
  CrcBuf.crcPoly  = SBR_CRC_POLY;                                           move16();
  CrcBuf.crcMask  = SBR_CRC_MASK;                                           move16();

  CrcStep       = extract_l(ffr_divideWord32(NrBits, MAXCRCSTEP));
  CrcNrBitsRest = sub(NrBits, shl(CrcStep, 4)); /* log2(MAXCRCSTEP) == 4 */

  assert(MAXCRCSTEP == (1 << 4));

  for (i = 0; i < CrcStep; i++) {
    bValue = ReadBits (hBitBuf, MAXCRCSTEP);
    calcCRC (&CrcBuf, bValue, MAXCRCSTEP);
  }

  bValue = ReadBits (hBitBuf, CrcNrBitsRest);
  calcCRC (&CrcBuf, bValue, CrcNrBitsRest);

                                                                            logic16();
  return (CrcBuf.crcState & SBR_CRC_RANGE);

}


/*!
  \brief   crc interface
  \return  1: CRC OK, 0: CRC check failure
*/
Flag
SbrCrcCheck (HANDLE_BIT_BUF hBitBuf,    /*!< handle to bit-buffer  */
             Word16 NrBits)             /*!< max. CRC length       */
{
  Flag crcResult;
  struct BIT_BUF BitBufferCRC;
  Word16 NrCrcBits;
  Word32 crcCheckResult;
  Word16 NrBitsAvailable;
  Word32 crcCheckSum;

  crcResult = 1;                                                            move16();

  crcCheckSum = ReadBits (hBitBuf, SI_SBR_CRC_BITS);

  CopyBitBuf (hBitBuf, &BitBufferCRC);

  NrBitsAvailable = GetNrBitsAvailable(&BitBufferCRC);  move16();

                                                                            test();
  if (NrBitsAvailable <= 0){
    return 0;
  }

  NrCrcBits = S_min (NrBits, NrBitsAvailable);

  crcCheckResult = getCrc (&BitBufferCRC, NrCrcBits);


                                                                            test();
  if (L_sub(crcCheckResult,crcCheckSum) != 0) {
    crcResult = 0;                                                          move16();
  }

  return (crcResult);
}
