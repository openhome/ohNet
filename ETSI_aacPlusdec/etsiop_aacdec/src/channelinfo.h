/*
   individual channel stream info
 */

#ifndef CHANNELINFO_H
#define CHANNELINFO_H

#include "defines.h"
#include "overlapadd.h"
#include "pulsedata.h"
#include "streaminfo.h"
#include "pns.h"
#include "FFR_bitbuffer.h"



#define MAX_WINDOWS   8
#define MAX_SFB_LONG  64
#define MAX_SFB_SHORT 16
#define MAX_QUANTIZED_VALUE 8191

enum
{
  OnlyLongSequence = 0,
  LongStartSequence,
  EightShortSequence,
  LongStopSequence,

  ProfileMain = 0,
  ProfileLowComplexity,
  ProfileSSR,
  ProfileReserved
};

typedef struct
{
  Word16 CommonWindow;
  Word16 ElementInstanceTag;
  Word16 GlobalGain;
} CRawDataInfo;

typedef struct
{
  Word16 Valid;

  Word16 IcsReservedBit;
  Word16 WindowShape;
  Word16 WindowSequence;
  Word16 MaxSfBands;
  Word16 ScaleFactorGrouping;

  Word16 TotalSfBands;
  Word16 SamplingRateIndex;
  Word16 Profile;

  Word16 WindowGroups;
  Word16 WindowGroupLength[8];
} CIcsInfo;

enum
{
  JointStereoMaximumGroups = 8,
  JointStereoMaximumBands = 64
};

typedef struct
{
  Word16 MsMaskPresent; 
  Flag MsUsed[JointStereoMaximumBands]; /*!< every byte contains flags for up to 8 groups */
} CJointStereoData;

typedef struct
{
  Word16 StartBand;
  Word16 StopBand;

  Word16 Direction;
  Word16 Resolution;

  Word16 Order;
  Word16 Coeff[MaximumOrder];
} CFilter;

typedef struct
{
  Flag TnsDataPresent;
  Word16 NumberOfFilters[MaximumWindows];
  CFilter Filter[MaximumWindows][MaximumFilters];
} CTnsData;

typedef struct
{
  const Word16 *pLongWindow[2];
  const Word16 *pShortWindow[2];

  COverlapAddData OverlapAddData;

} CAacDecoderStaticChannelInfo;

typedef struct
{
  Word16 aSpecScale[MAX_WINDOWS];
  Word16 aSfbScale[MAX_WINDOWS * MAX_SFB_SHORT];
  Word16 aScaleFactor[MAX_WINDOWS * MAX_SFB_SHORT];
  Word8  aCodeBook[MAX_WINDOWS * MAX_SFB_SHORT];
} CAacDecoderDynamicData;

typedef struct
{
  CJointStereoData JointStereoData; /*! Common MS-mask for a channel-pair */
  CPnsInterChannelData PnsInterChannelData;
} CAacDecoderDynamicCommonData;

typedef struct
{
  Word16 *pSpecScale;
  Word16 *pSfbScale;
  Word16 *pScaleFactor;
  Word8  *pCodeBook;
  Word32 *pSpectralCoefficient;

  CIcsInfo IcsInfo;
  CTnsData TnsData;
  CPulseData PulseData;
  CRawDataInfo RawDataInfo;
  CJointStereoData * pJointStereoData;

  CPnsData PnsData;
  CPnsInterChannelData       *pPnsInterChannelData;
  CPnsStaticInterChannelData *pPnsStaticInterChannelData;
} CAacDecoderChannelInfo;

Word16 IcsRead(HANDLE_BIT_BUF bs,CIcsInfo *pIcsInfo);
void IcsReset(CIcsInfo *pIcsInfo, CStreamInfo *pStreamInfo);

Word16 IsValid(CIcsInfo *pIcsInfo);
Word16 IsLongBlock(CIcsInfo *pIcsInfo);
Word16 IsShortBlock(CIcsInfo *pIcsInfo);
Word16 IsMainProfile(CIcsInfo *pIcsInfo);
Word16 GetProfile(CIcsInfo *pIcsInfo);
Word16 GetWindowShape(CIcsInfo *pIcsInfo);
Word16 GetWindowSequence(CIcsInfo *pIcsInfo);
Word16  GetWindowsPerFrame(CIcsInfo *pIcsInfo);
Word16 GetWindowGroups(CIcsInfo *pIcsInfo);
Word16 GetWindowGroupLength(CIcsInfo *pIcsInfo, Word16 index);
Word16 *GetWindowGroupLengthTable(CIcsInfo *pIcsInfo);
Word16 GetScaleFactorBandsTransmitted(CIcsInfo *pIcsInfo);
Word16 GetScaleFactorBandsTotal(CIcsInfo *pIcsInfo);
const Word16 *GetScaleFactorBandOffsets(CIcsInfo *pIcsInfo);
Word32 SamplingRateFromIndex(Word16 index);
Word16 GetFreqLine (CIcsInfo *pIcsInfo, Word8 sfb);
Word32 GetSamplingFrequency(CIcsInfo *pIcsInfo);
Word16 GetMaximumTnsBands(CIcsInfo *pIcsInfo);


#endif /* #ifndef CHANNELINFO_H */
