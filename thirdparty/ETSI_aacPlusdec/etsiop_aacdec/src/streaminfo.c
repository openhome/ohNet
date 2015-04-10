/*
   current bitstream parameters
 */

#include "aac_ram.h"
#include "streaminfo.h"
#include "count.h"

/*  Stream Configuration and Information.  */
void CStreamInfoOpen(CStreamInfo **pStreamInfo)
{
  /* initialize CStreamInfo */
  pStreamInfo[0] = &StreamInfo;                                             move16();

  pStreamInfo[0]->SamplingRateIndex = 0;                                    move16();
  pStreamInfo[0]->SamplingRate      = 0;                                    move32();
  pStreamInfo[0]->Profile           = 0;                                    move16();
  pStreamInfo[0]->BitRate           = 0;                                    move32();
  pStreamInfo[0]->ChannelConfig     = 0;                                    move16();
  pStreamInfo[0]->Channels          = 1;                                    move16();
  pStreamInfo[0]->SamplesPerFrame   = 1024;                                 move32();
}


