/*
   memory layout
 */

#ifndef AAC_RAM_H
#define AAC_RAM_H


#include "channel.h"
#include"stereo.h"
#include "conceal.h"
#include "datastream.h"
#include "pns.h"


#define MAX_SYNCHS        10
#define SAMPL_FREQS       12


extern CStreamInfo StreamInfo;
extern CAacDecoderStaticChannelInfo AacDecoderStaticChannelInfo[Channels];

extern Word16 OverlapBuffer[Channels*OverlapBufferSize];
extern CPnsStaticInterChannelData PnsStaticInterChannelData;

extern CConcealmentInfo ConcealmentInfoInstance;

extern Word32 WorkBufferCore[MaximumBinsLong*Channels];
extern CAacDecoderChannelInfo *pAacDecoderChannelInfoInit[Channels];
extern CAacDecoderChannelInfo *pAacDecoderChannelInfoInitEnh[Channels];
extern CAacDecoderDynamicData *pAacDecoderDynamicDataInit[Channels];
extern CAacDecoderDynamicData *pAacDecoderDynamicDataInitEnh[Channels];
extern CAacDecoderDynamicCommonData *pAacDecoderDynamicCommonDataInit;

extern CDataStreamElement DataStreamElement;


#endif /* #ifndef AAC_RAM_H */
