/*
   temporal noise shaping tool 
 */

#ifndef TNS_H
#define TNS_H

#include "channelinfo.h"
#include "FFR_bitbuffer.h"


Flag TnsPresent(CTnsData *pTnsData);

void CTns_Apply (CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                 Word16 maxSfb);

Word16 CTns_Read(HANDLE_BIT_BUF bs,
                 CAacDecoderChannelInfo *pAacDecoderChannelInfo);


#endif /* #ifndef TNS_H */
