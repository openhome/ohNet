/*
   data stream element
 */

#include "datastream.h"
#include "FFR_bitbuffer.h"
#include "aac_ram.h"
#include "count.h"

void CDataStreamElementOpen(CDataStreamElement **pDataStreamElement)
{
  pDataStreamElement[0] = &DataStreamElement;                  move16();
}


void CDataStreamElement_Read(HANDLE_BIT_BUF bs,
                             CDataStreamElement *pDataStreamElement,
                             Word32 *pByteAlignBits)
{
  Word16 i;

  pDataStreamElement->ElementInstanceTag = (Word16) ReadBits(bs,4);
  pDataStreamElement->DataByteAlignFlag = ReadBits(bs,1);          move16();
  pDataStreamElement->Count = (Word16)ReadBits(bs,8);

  test();
  if (sub(pDataStreamElement->Count, 255) == 0)
  {
    pDataStreamElement->Count = add(pDataStreamElement->Count, (Word16)ReadBits(bs,8)); move16(); /* EscCount */
  }

  test();
  if (pDataStreamElement->DataByteAlignFlag)
  {
    ByteAlign(bs,pByteAlignBits);
  }

  move16(); /*pDataStreamElement->Count*/
  for (i=0; i < pDataStreamElement->Count; i++)
  {
    pDataStreamElement->DataStreamByte[i] = (Word8)ReadBits(bs,8); move16();logic16(); logic16(); logic16();
  }
}

