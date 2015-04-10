/*
   aacPlus-specific Payload Extraction
 */
#ifndef AACPLUSCHECK_H
#define AACPLUSCHECK_H

#include "FFR_bitbuffer.h"

Flag aacPlusCheckForPayload(HANDLE_BIT_BUF bs,
                            SBRBITSTREAM *streamSBR,
                            Word16 prev_element
                            );

Word8 aacPlusGetPayload(HANDLE_BIT_BUF bs,
                        SBR_ELEMENT_STREAM *streamSBR);


#endif
