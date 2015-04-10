/*
   bitstream routines
 */

#include "aac_ram.h"
#include "FFR_bitbuffer.h"
#include "count.h"




/*!
  \brief Rewinds bitstream pointers

  \return  none
*/
void PushBack(HANDLE_BIT_BUF hBitBuf, /*!< pointer to current data in bitstream */
              Word16 nBits)           /*!< number of bits */
{
  WindBitBufferBidirectional(hBitBuf,negate(nBits));
}


/*!
  \brief Get byte alignement

  \return  none
*/
void ByteAlign(HANDLE_BIT_BUF hBitBuf, /*!< pointer to current data in bitstream */
               Word32 *pByteAlignBits) /*!< pointer to last state of cntBits */
{

  Word16 alignment;
  alignment = extract_l(L_sub(*pByteAlignBits, hBitBuf->cntBits)) & 0x07;                                    logic16(); 
                                                                                                  test();
  if (alignment)
    ReadBits(hBitBuf,sub(8,alignment));

  *pByteAlignBits = hBitBuf->cntBits;                                                              move32();
}

