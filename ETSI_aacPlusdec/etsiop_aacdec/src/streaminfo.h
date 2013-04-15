/*
   current bitstream parameters
 */

#ifndef STREAMINFO_H
#define STREAMINFO_H


typedef struct
{
  Word16  SamplingRateIndex;
  Word32 SamplingRate;
  Word16 Profile;
  Word16 ChannelConfig;
  Word16 Channels;
  Word32 BitRate;
  Word16 SamplesPerFrame;
} CStreamInfo;

/* Initialize stream info */
void CStreamInfoOpen(CStreamInfo **pStreamInfo);


#endif /* #ifndef STREAMINFO_H */
