/*
   channel info
 */

#ifndef CHANNEL_H
#define CHANNEL_H

#include "block.h"
#include "FFR_bitbuffer.h"


enum
{
  ID_SCE = 0,
  ID_CPE,
  ID_CCE,
  ID_LFE,
  ID_DSE,
  ID_PCE,
  ID_FIL,
  ID_END
};

enum
{
  L = 0,
  R = 1,
  Channels = 2
};

Word16 ReadICS(HANDLE_BIT_BUF bs,
               CAacDecoderChannelInfo *pAacDecoderChannelInfo);

Word16 CSingleChannelElement_Read(HANDLE_BIT_BUF bs,
                               CAacDecoderChannelInfo *pAacDecoderChannelInfo[Channels],
                               CStreamInfo *pStreamInfo,
                               Word16 *pElementInstanceTag);

Word16 CChannelPairElement_Read(HANDLE_BIT_BUF bs,
                             CAacDecoderChannelInfo *pAacDecoderChannelInfo[Channels],
                             CStreamInfo *pStreamInfo,
                             Word16 *pElementInstanceTag);

void CSingleChannelElement_Decode(CAacDecoderChannelInfo *pAacDecoderChannelInfo[Channels]);

void CChannelPairElement_Decode(CAacDecoderChannelInfo *pAacDecoderChannelInfo[Channels]);

void MapMidSideMaskToPnsCorrelation(CAacDecoderChannelInfo *pAacDecoderChannelInfo[Channels]);

#endif /* #ifndef CHANNEL_H */
