/*
   Bit Buffer Management
 */

#include <stdio.h>
#include <assert.h>

#include "FFR_bitbuffer.h"
#include "count.h"



static void updateBitBufWordPtr(HANDLE_BIT_BUF hBitBuf,
                                UWord8 **pBitBufWord,
                                Word16   cnt)
{
  *pBitBufWord += cnt;                                                                  add(1,1); /* counting operation */ move16();

                                                                                        test(); sub(1,1);
  if(*pBitBufWord > hBitBuf->pBitBufEnd) {
    *pBitBufWord -= (hBitBuf->pBitBufEnd - hBitBuf->pBitBufBase + 1);                   sub(1,1); add(1,1); sub(1,1); /* counting operation */ move16();
  }
                                                                                        test(); sub(1,1);
  if(*pBitBufWord < hBitBuf->pBitBufBase) {
    *pBitBufWord += (hBitBuf->pBitBufEnd - hBitBuf->pBitBufBase + 1);                   sub(1,1); add(1,1); add(1,1); /* counting operation */ move16();
  }
}

HANDLE_BIT_BUF CreateBitBuffer(HANDLE_BIT_BUF hBitBuf,
                               UWord8 *pBitBufBase,
                               Word16  bitBufSize)
{
  assert(bitBufSize*8 <= 32768);

  hBitBuf->pBitBufBase = pBitBufBase;                                                   move16();
  hBitBuf->pBitBufEnd  = pBitBufBase + bitBufSize - 1;                                  add(1,1); sub(1,1); /* counting operations */ move16();

  hBitBuf->pReadNext   = pBitBufBase;                                                   move16();
  hBitBuf->pWriteNext  = pBitBufBase;                                                   move16();

  hBitBuf->wBitPos     = 7;                                                             move16();
  hBitBuf->rBitPos     = 7;                                                             move16();

  hBitBuf->cntBits     = 0;                                                             move16();
  hBitBuf->size        = shl(bitBufSize, 3);                                            move16();
  hBitBuf->isValid     = 1;                                                             move16();

  return hBitBuf;
}


HANDLE_BIT_BUF CreateInitializedBitBuffer(HANDLE_BIT_BUF hBitBuf,
                                          UWord8 *pBitBufBase,
                                          Word16  bitBufSize)
{
  hBitBuf->pBitBufBase = pBitBufBase;                                                   move16();
  hBitBuf->pBitBufEnd  = pBitBufBase + bitBufSize - 1;                                  add(1,1); sub(1,1); /* counting operations */ move16();

  hBitBuf->pReadNext   = pBitBufBase;                                                   move16();
  hBitBuf->pWriteNext  = pBitBufBase;                                                   move16();

  hBitBuf->wBitPos     = 7;                                                             move16();
  hBitBuf->rBitPos     = 7;                                                             move16();

  hBitBuf->cntBits     = shl(bitBufSize, 3);                                            move16();
  hBitBuf->size        = shl(bitBufSize, 3);                                            move16();

  return (hBitBuf);
}


void DeleteBitBuffer(HANDLE_BIT_BUF *hBitBuf)
{
  (*hBitBuf)->isValid = 0;                                                              move16();
  *hBitBuf = NULL;                                                                      move16();
}


void ResetBitBuf(HANDLE_BIT_BUF hBitBuf,
                 UWord8 *pBitBufBase,
                 Word16  bitBufSize)
{
  hBitBuf->pBitBufBase = pBitBufBase;                                                   move16();
  hBitBuf->pBitBufEnd  = pBitBufBase + bitBufSize - 1;                                  add(1,1); sub(1,1); /* counting operations */ move16();

  hBitBuf->pReadNext   = pBitBufBase;                                                   move16();
  hBitBuf->pWriteNext  = pBitBufBase;                                                   move16();

  hBitBuf->rBitPos     = 7;                                                             move16();
  hBitBuf->wBitPos     = 7;                                                             move16();

  hBitBuf->cntBits     = 0;                                                             move16();
}


void CopyBitBuf(HANDLE_BIT_BUF hBitBufSrc,
                HANDLE_BIT_BUF hBitBufDst)
{
  *hBitBufDst = *hBitBufSrc;                                                            move16();
}


void CopyBitBufAll(HANDLE_BIT_BUF hBitBufSrc,
                   HANDLE_BIT_BUF hBitBufDst)
{
  Word16 i;
  Word16 bytesToGoSrc = (hBitBufSrc->pBitBufEnd - hBitBufSrc->pBitBufBase);             sub(1,1); /* counting operations */

  assert (bytesToGoSrc == (hBitBufDst->pBitBufEnd-hBitBufDst->pBitBufBase));

  for ( i = 0; i <= bytesToGoSrc; i++ ) {
    hBitBufDst->pBitBufBase[i] = hBitBufSrc->pBitBufBase[i];                            move16();
  }

  hBitBufDst->pReadNext  = hBitBufDst->pBitBufBase + (hBitBufSrc->pReadNext - hBitBufSrc->pBitBufBase);   add(1,1); sub(1,1); /* counting operations */ move16();
  hBitBufDst->pWriteNext = hBitBufDst->pBitBufBase + (hBitBufSrc->pWriteNext - hBitBufSrc->pBitBufBase);  add(1,1); sub(1,1); /* counting operations */ move16();

  hBitBufDst->rBitPos    = hBitBufSrc->rBitPos;                                         move16();
  hBitBufDst->wBitPos    = hBitBufSrc->wBitPos;                                         move16();

  hBitBufDst->cntBits    = hBitBufSrc->cntBits;                                         move16();
  hBitBufDst->isValid    = hBitBufSrc->isValid;                                         move16();
}


Word16 GetBitsAvail(HANDLE_BIT_BUF hBitBuf)
{
  return hBitBuf->cntBits;
}

Word32 ReadBits(HANDLE_BIT_BUF hBitBuf,
                Word16 noBitsToRead)
{
  UWord32 returnValue;

  /* return value is of type Word32, it can hold up to 32 bits 
     this optimized code can read upto 25 Bits a time */
  assert(noBitsToRead <= 25);

  hBitBuf->cntBits = sub(hBitBuf->cntBits, noBitsToRead);                               move16();
  hBitBuf->rBitPos = sub(hBitBuf->rBitPos, noBitsToRead);                               move16();

  logic16(); logic16(); /* 8-bit aligned read access: *pReadNext */
  returnValue = (UWord32)*hBitBuf->pReadNext;                                           move32();

                                                                                        test() ;
  while (hBitBuf->rBitPos < 0) {
    hBitBuf->rBitPos = add(hBitBuf->rBitPos, 8);                                        move16();
    hBitBuf->pReadNext++;                                                               add(1,1); /* counting operation */ move16();

                                                                                        test(); sub(1,1);
    if(hBitBuf->pReadNext > hBitBuf->pBitBufEnd) {
      hBitBuf->pReadNext = hBitBuf->pBitBufBase;                                        move16();
    }

    returnValue <<= 8;                                                                  shr(1,1); /* counting operation */

    logic16(); logic16(); /* 8-bit aligned read access: *pReadNext */
    returnValue  |= (UWord32)*hBitBuf->pReadNext;                                       logic32();
    /* end of while */                                                                  test();

  }

                                                                                        L_shl(1,1); shr(1,1); /* counting operations */
  returnValue = returnValue << sub(sub(31, noBitsToRead), hBitBuf->rBitPos) >> sub(32, noBitsToRead);

  return returnValue;
}

Word16 WriteBits(HANDLE_BIT_BUF hBitBuf,
                 Word32 writeValue,
                 Word16 noBitsToWrite)
{
  Word16 bitsToWrite, bitsWritten;

  bitsWritten = noBitsToWrite;                                                          move16();

  assert(noBitsToWrite <= (Word16)sizeof(Word32)*8);

  hBitBuf->cntBits = add(hBitBuf->cntBits, noBitsToWrite);                              move16();


                                                                                        test();
  while(noBitsToWrite){
    Word16 bits_to_shift;
    UWord8 tmp, msk;

    bitsToWrite = S_min (add(hBitBuf->wBitPos, 1), noBitsToWrite);

    bits_to_shift = sub(add(hBitBuf->wBitPos, 1), bitsToWrite);
    logic32(); /* cast (Word8) is equivalent to a mask */
    tmp = (Word8)((UWord32)writeValue << sub(32, noBitsToWrite) >> sub(32, bitsToWrite) 
                             << bits_to_shift);            L_shl(1,1); L_shr(1,1); L_shl(1,1); /* counting operations */
    msk = ~( ((1 << bitsToWrite) - 1) 
             << bits_to_shift );                           L_shl(1,1); L_shl(1,1); /* counting operations */

    *hBitBuf->pWriteNext &= msk;                                                        logic16(); move16();
    *hBitBuf->pWriteNext |= tmp;                                                        logic16(); move16();

    hBitBuf->wBitPos      = sub(hBitBuf->wBitPos, bitsToWrite);                         move16();
    noBitsToWrite         = sub(noBitsToWrite, bitsToWrite);

                                                                                        test();
    if (hBitBuf->wBitPos < 0) {
      hBitBuf->wBitPos   = add(hBitBuf->wBitPos, 8);                                    move16();
      hBitBuf->pWriteNext++;                                                            add(1,1); /* counting operation */ move16();

                                                                                        test(); sub(1,1);
      if(hBitBuf->pWriteNext > hBitBuf->pBitBufEnd) {
        hBitBuf->pWriteNext = hBitBuf->pBitBufBase;                                     move16();
      }
    }
    /* end of while */                                                                      test();
  }

  return bitsWritten;
}


void WindBitBufferBidirectional(HANDLE_BIT_BUF hBitBuf,
                                Word16 offset)        
{
  /* Nothing to do, if number of wind bits are zero */
                                                                                       test();
  if (offset != 0) {
    Word16 bOffset;
    
    hBitBuf->rBitPos  = sub(hBitBuf->rBitPos, offset);                                  move16();
    bOffset           = shr(hBitBuf->rBitPos, 3);
    hBitBuf->rBitPos  = sub(hBitBuf->rBitPos, shl(bOffset, 3));                         move16();

                                                                                        test();
    if (bOffset) {
      updateBitBufWordPtr (hBitBuf, &hBitBuf->pReadNext, negate(bOffset));
    }
    hBitBuf->cntBits  = sub(hBitBuf->cntBits, offset);                                  move16();
  }
}


