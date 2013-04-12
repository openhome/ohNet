/*
   aacPlus-specific Payload Extraction
 */

#include "sbrdecoder.h"
#include "FFR_bitbuffer.h"
#include "aacpluscheck.h"

#include "count.h"




/*!
  \brief Check if valid SBR data is there as expected

  \return 1 if aacPlus payload has been detected, 0 otherwise
*/

Flag aacPlusCheckForPayload(HANDLE_BIT_BUF bs,        /*!< pointer to fill element data in bitstream */
                            SBRBITSTREAM *streamSBR,  /*!< pointer to SBR-bitstream */
                            Word16 prev_element       /*!< ID of syntactic element prior to the fill element */
                            )
{
  Flag ret;
  Word16 count;
  Word16 esc_count;

  ret       = 0;                                                                                    move16();
  esc_count = 0;                                                                                    move16();



  count = (Word16)ReadBits(bs,4);           /* bs_count: payload size in bytes */

                                                                                                    test();
  if (sub(count,15) == 0)
  {
    esc_count = (Word16)ReadBits(bs,8);     /* bs_esc_count */
    count = add(esc_count, 14);
  }

                                                                                                    test();
  if (count > 0)
  {
    Word8 extension_type;

    extension_type = (Word8) ReadBits(bs,4);    /* bs_extension_type */


                                                                                                    logic16(); logic16(); logic16(); logic16();
                                                                                                    test(); test(); test(); test(); test();
    if (((sub(extension_type,SBR_EXTENSION) == 0)
         || (sub(extension_type,SBR_EXTENSION_CRC) == 0)
         )
        && (sub(prev_element,SBR_ID_SCE) == 0  
            || sub(prev_element,SBR_ID_CPE) == 0)
        )
    {
      ret = 1;                                                                                      move16();

      streamSBR->sbrElement[streamSBR->nrElements].sizePayload = count;                             move16();
      streamSBR->sbrElement[streamSBR->nrElements].extensionType = extension_type;                  move16();
      streamSBR->sbrElement[streamSBR->nrElements].elementID = prev_element;                        move16();
    
      streamSBR->nrElements = add(streamSBR->nrElements, 1);                                        move16();
    }
    else {
      Word16 i;

      ReadBits(bs,4);       /* bs_fill_nibble: skip second half of first byte in fill element (4 bits have already been read) */

      for (i=1; i<count; i++)
        ReadBits(bs,8);     /* bs_fill_byte: skip all remaining bytes in fill element */
    }
  }
  return(ret);
}


/*!
  \brief Extraction of aacPlus-specific payload from fill element
*/
Word8 aacPlusGetPayload(HANDLE_BIT_BUF bs,             /*!< pointer to fill element data in bitstream */
                        SBR_ELEMENT_STREAM *streamSBR) /*!< pointer to SBR-bitstream */
{
  Word16 byteCount = streamSBR->sizePayload;

                                                                                                    test(); test();
  if (byteCount > 0 && sub(byteCount,MAXSBRBYTES) <= 0) {
    Word16 i;

    streamSBR->pData[0] = (Word8) ReadBits(bs,4);     /* bs_fill_nibble */                          move16(); logic16(); logic16(); logic16(); 

    /* assume that 6 logical operations are enough in 
       order to move the bitstream from bs to pData */
    logic16(); logic16(); logic16(); logic16(); logic16(); logic16(); 
    for (i=1; i<byteCount; i++) {
      streamSBR->pData[i] = (Word8) ReadBits(bs,8);   /* bs_sbr_data */                             move16();
    }
  }
  
  return 0;
}
