/*
   data stream element
 */

#ifndef DATASTREAM_H
#define DATASTREAM_H

#include "bitstream.h"
#include "FFR_bitbuffer.h"

enum
{
  MaximumElementLength = 512
};

typedef struct
{
  Word16 ElementInstanceTag;
  Flag DataByteAlignFlag;
  Word16 Count;
  Word8 DataStreamByte[MaximumElementLength];
} CDataStreamElement;

void CDataStreamElementOpen(CDataStreamElement **pDataStreamElement);
void CDataStreamElement_Read(HANDLE_BIT_BUF bs,CDataStreamElement *pDataStreamElement,Word32 *pByteAlignBits);

#endif /* #ifndef DATASTREAM_H */


