/*
   individual channel stream info
 */

#include "aac_rom.h"
#include "streaminfo.h"
#include "FFR_bitbuffer.h"
#include "intrinsics.h"
#include "channelinfo.h"
#include "count.h"



Word16 IsValid(CIcsInfo *pIcsInfo)
{
  return pIcsInfo->Valid;
}

Word16 IsLongBlock(CIcsInfo *pIcsInfo)
{
  Word16 temp;
  temp = sub(pIcsInfo->WindowSequence,EightShortSequence);

  return (temp != 0);                                  
}

Word16 IsShortBlock(CIcsInfo *pIcsInfo)
{
  Word16 temp;
  temp = sub(pIcsInfo->WindowSequence,EightShortSequence);

  return (temp == 0);                                  
}

Word16 IsMainProfile(CIcsInfo *pIcsInfo)
{
  Word16 temp;
  temp = sub(pIcsInfo->Profile,ProfileMain);

  return (temp == 0);                                  
}

Word16 GetProfile(CIcsInfo *pIcsInfo)
{
  return pIcsInfo->Profile;
}

Word16 GetWindowShape(CIcsInfo *pIcsInfo)
{
  return pIcsInfo->WindowShape;
}

Word16 GetWindowSequence(CIcsInfo *pIcsInfo)
{
  return pIcsInfo->WindowSequence;
}

Word16 GetWindowsPerFrame(CIcsInfo *pIcsInfo)
{
  Word16 temp;
  temp = sub(pIcsInfo->WindowSequence,EightShortSequence);
                                                                                                   test();
  if ( temp == 0 )
    return 8;
  else
    return 1;
}

Word16 GetWindowGroups(CIcsInfo *pIcsInfo)
{
  return pIcsInfo->WindowGroups;
}

Word16 GetWindowGroupLength(CIcsInfo *pIcsInfo, Word16 index)
{
  return pIcsInfo->WindowGroupLength[index];
}

Word16 *GetWindowGroupLengthTable(CIcsInfo *pIcsInfo)
{
  return pIcsInfo->WindowGroupLength;
}

Word16 GetScaleFactorBandsTransmitted(CIcsInfo *pIcsInfo)
{
  return pIcsInfo->MaxSfBands;
}

Word16 GetScaleFactorBandsTotal(CIcsInfo *pIcsInfo)
{
  return pIcsInfo->TotalSfBands;
}

Word32 SamplingRateFromIndex(Word16 index)
{
  return SamplingRateInfoTable[index].SamplingFrequency;
}

Word16 GetFreqLine (CIcsInfo *pIcsInfo, Word8 sfb)
{
  const Word32 samplingRateIndex = 7; /* 22050 kHz */
                                                                                                   test();
  if (IsLongBlock (pIcsInfo)) {
    return SamplingRateInfoTable[samplingRateIndex].ScaleFactorBands_Long[sfb];
  }
  else {
    return shl(SamplingRateInfoTable[samplingRateIndex].ScaleFactorBands_Short[sfb],3);
  }
}

Word32 GetSamplingFrequency(CIcsInfo *pIcsInfo)
{
  return SamplingRateFromIndex(pIcsInfo->SamplingRateIndex);
}

Word16 GetMaximumTnsBands(CIcsInfo *pIcsInfo)
{
  Word16 i;

  i = !IsLongBlock(pIcsInfo);                                                                      logic16();

  logic16(); logic16(); /* Word8 read access */
  return tns_max_bands_tbl[pIcsInfo->SamplingRateIndex][i];
}

const Word16 *GetScaleFactorBandOffsets(CIcsInfo *pIcsInfo)
{                                                                                                  test();
  if (IsLongBlock(pIcsInfo))
  {
    return SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].ScaleFactorBands_Long;
  }
  else
  {
    return SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].ScaleFactorBands_Short;
  }
}

void IcsReset(CIcsInfo *pIcsInfo, CStreamInfo *pStreamInfo)
{
  pIcsInfo->Valid = 0;                                                                             move16();
  pIcsInfo->TotalSfBands = 0;                                                                      move16();

  pIcsInfo->SamplingRateIndex = pStreamInfo->SamplingRateIndex;                                    move16();
  pIcsInfo->Profile = (Word8)pStreamInfo->Profile;                                                 move16();
}

Word16 IcsRead(HANDLE_BIT_BUF bs,
               CIcsInfo *pIcsInfo)
{
  Word16 i;
  Word16 mask;
  Word16  PredictorDataPresent;
  Word16 ErrorStatus = AAC_DEC_OK;                                                                 
                                                                                                   move16();

  pIcsInfo->IcsReservedBit = (Word16)ReadBits(bs,1);
  pIcsInfo->WindowSequence = (Word16)ReadBits(bs,2);
  pIcsInfo->WindowShape    = (Word16)ReadBits(bs,1);
                                                                                                   test();
  if (IsLongBlock(pIcsInfo))
  {
    pIcsInfo->TotalSfBands = SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].NumberOfScaleFactorBands_Long;                   move16();
    pIcsInfo->MaxSfBands = (Word16)ReadBits(bs,6);
                                                                                                                                 test();
    if ((PredictorDataPresent = (Word16)ReadBits(bs,1)))
    {
      return AAC_DEC_PREDICTION_NOT_SUPPORTED_IN_LC_AAC;
    }

    pIcsInfo->WindowGroups = 1;                                                                                                  move16();
    pIcsInfo->WindowGroupLength[0] = 1;                                                                                          move16();
  }
  else
  {
    pIcsInfo->TotalSfBands = SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].NumberOfScaleFactorBands_Short;                  move16();
    pIcsInfo->MaxSfBands = (Word16)ReadBits(bs,4);
    pIcsInfo->ScaleFactorGrouping = (Word16)ReadBits(bs,7);

    pIcsInfo->WindowGroups = 0 ;                                                                                                 move16();

    for (i=0; i < 7; i++)
    {
      mask = shl(1,sub(6,i));
      pIcsInfo->WindowGroupLength[i] = 1;                                                                                        move16();
                                                                                                                                 logic16(); test();
      if (pIcsInfo->ScaleFactorGrouping & mask)
      {
        pIcsInfo->WindowGroupLength[pIcsInfo->WindowGroups] =
          add(pIcsInfo->WindowGroupLength[pIcsInfo->WindowGroups],1);                                                            move16();
      }
      else
      {
        pIcsInfo->WindowGroups = add(pIcsInfo->WindowGroups,1);
      }
    }

    /* loop runs to i < 7 only */
    pIcsInfo->WindowGroupLength[7] = 1;                                                                                          move16();
    pIcsInfo->WindowGroups = add( pIcsInfo->WindowGroups, 1 );
  }

  pIcsInfo->Valid = 1;                                                                                                           move16();

  return ErrorStatus;
}

