/*
   perceptual noise substitution tool
 */

#include <math.h>
#include <assert.h>
#include "ffr.h"
#include "aac_rom.h"
#include "channelinfo.h"
#include "block.h"
#include "pns.h"
#include "FFR_bitbuffer.h"
#include "count.h"


#define NOISE_OFFSET 90           /* cf. ISO 14496-3 p. 175 */

const Word16 pns_group_fac = (Word16) 4; /* log2(MaximumScaleFactorBandsShort) */


void GenerateRandomVector (Word32 scale,
                           Word16 shift,
                           Word32 spec[],
                           Word16 bandOffsetStart,
                           Word16 bandOffsetEnd,
                           Word16 *random_state);

/*!
  \brief Reset InterChannel data

  The function initializes the InterChannel data
*/
void CPns_InitInterChannelData(CAacDecoderChannelInfo *pAacDecoderChannelInfo) 
{
  CPnsInterChannelData *pInterChannelData = pAacDecoderChannelInfo->pPnsInterChannelData;
  Word16 i;
  move16();
  for (i = 0; i < PNS_BAND_FLAGS_SIZE; i++) {
    pInterChannelData->correlated[i] = 0;                                   move16();
  }
}


/*!
  \brief Reset PNS data
*/
void CPns_InitPns(CAacDecoderChannelInfo *pAacDecoderChannelInfo) 
{
  CPnsData *pPnsData = &pAacDecoderChannelInfo->PnsData;
  Word16 i;
  move16();

  assert((1 << 4) == MaximumScaleFactorBandsShort); /* needed for pns_group_fac */

  for (i = 0; i < PNS_BAND_FLAGS_SIZE; i++) {
    pPnsData->pnsUsed[i] = 0;                                               move16();
  }

  pPnsData->PnsActive = 0;                                                  move16();
  pPnsData->CurrentEnergy = 0;                                              move16();
}


/*!
  \brief Indicates if PNS is used

  \return  PNS used
*/
Word16 CPns_IsPnsUsed (CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                       const Word16 group,
                       const Word16 band)
{
  CPnsData *pPnsData = &pAacDecoderChannelInfo->PnsData;
  Word16 pns_band = add(shl(group, pns_group_fac), band);
                                                                            move16();

                                                                            logic16(); logic16();
  return (shr(pPnsData->pnsUsed[shr(pns_band, PNS_BAND_FLAGS_SHIFT)], (pns_band & PNS_BAND_FLAGS_MASK)) & (Word16)1);
}

/*!
  \brief Set correlation
*/
void CPns_SetCorrelation(CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                         const Word16 group,
                         const Word16 band)
{
  CPnsInterChannelData *pInterChannelData = pAacDecoderChannelInfo->pPnsInterChannelData;
  Word16 pns_band = add(shl(group, pns_group_fac), band);
                                                                            move16();

                                                                            logic16(); logic16(); move16();
  pInterChannelData->correlated[shr(pns_band, PNS_BAND_FLAGS_SHIFT)] |= shl((Word16)1, (pns_band & PNS_BAND_FLAGS_MASK));
}

/*!
  \brief Indicates if correlation is used

  \return  PNS used
*/
Word16 CPns_IsCorrelated(CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                         const Word16 group,
                         const Word16 band)
{
  CPnsInterChannelData *pInterChannelData = pAacDecoderChannelInfo->pPnsInterChannelData;
  Word16 pns_band = add(shl(group, pns_group_fac), band);
                                                                            move16();

                                                                            logic16(); logic16();
  return (shr(pInterChannelData->correlated[shr(pns_band, PNS_BAND_FLAGS_SHIFT)], (pns_band & PNS_BAND_FLAGS_MASK)) & (Word16)1);
}

/*!
  \brief Read PNS information
*/
void CPns_Read (CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                HANDLE_BIT_BUF bs,
                const CodeBookDescription *hcb,
                Word16 global_gain,
                Word16 band,
                Word16 group)
{
  Word16 delta ;
  Word16 pns_band = add(shl(group, pns_group_fac), band);
  CPnsData *pPnsData = &pAacDecoderChannelInfo->PnsData;
                                                                            move16();

                                                                            test();
  if (pPnsData->PnsActive) {
    delta = sub(CBlock_DecodeHuffmanWord (bs, hcb->CodeBook), 60);
  } else {
    Word16 noiseStartValue = (Word16)ReadBits(bs,9);

    delta = sub(noiseStartValue, 256);
    pPnsData->PnsActive = 1;                                                move16();
    pPnsData->CurrentEnergy = sub(global_gain, NOISE_OFFSET);               move16();
  }

  pPnsData->CurrentEnergy = add(pPnsData->CurrentEnergy, delta);            move16();
  pAacDecoderChannelInfo->pScaleFactor[pns_band] = pPnsData->CurrentEnergy; move16();
 
                                                                            logic16(); logic16(); move16();
  pPnsData->pnsUsed[shr(pns_band, PNS_BAND_FLAGS_SHIFT)] |= shl((Word16)1, (pns_band & PNS_BAND_FLAGS_MASK));
}

/*!
  \brief Apply PNS
*/
void CPns_Apply (CAacDecoderChannelInfo *pAacDecoderChannelInfo[],
                 Word16 channel)
{
  const Word32 scale_mant_tab[PNS_SCALE_MANT_TAB_SIZE] = { 0x08000000,
                                                     0x09837f05,
                                                     0x0b504f33,
                                                     0x0d744fcc
  };

  CPnsData *pPnsData = &pAacDecoderChannelInfo[channel]->PnsData;
  CIcsInfo *pIcsInfo = &pAacDecoderChannelInfo[channel]->IcsInfo;
  move16(); move16();

                                                                            test();
  if (pPnsData->PnsActive) {
    const Word16 *BandOffsets = GetScaleFactorBandOffsets(pIcsInfo);
    Word16 window, group, groupwin, band;
    window = 0; move16();
    move16(); /*GetWindowGroups*/
    move16(); /*GetScaleFactorBandsTransmitted*/
    for (group = 0; group < GetWindowGroups(pIcsInfo); group++) {
      move16(); /*GetWindowGroupLength*/
      for (groupwin = 0; groupwin < GetWindowGroupLength(pIcsInfo, group); groupwin++, window++) {
        Word32 *spectrum = &pAacDecoderChannelInfo[channel]->pSpectralCoefficient[128*window]; move16();

        for (band = 0 ; band < GetScaleFactorBandsTransmitted(pIcsInfo); band++) {
                                                                            test();
          if (CPns_IsPnsUsed (pAacDecoderChannelInfo[channel], group, band)) {
            Word16 pns_band;
            Word32 scale_mant;
            Word16 scale_exp;

            pns_band = add(shl(group, pns_group_fac), band);

                                                                            move32(); logic32();
            scale_mant  = scale_mant_tab[pAacDecoderChannelInfo[channel]->pScaleFactor[pns_band] & PNS_SCALE_MANT_TAB_MASK];
            scale_exp   = add(sub(pAacDecoderChannelInfo[channel]->pSpecScale[window], shr(pAacDecoderChannelInfo[channel]->pScaleFactor[pns_band], PNS_SCALEFACTOR_SCALING)), PNS_SCALE_MANT_TAB_SCALING);

                                                                            test();
            if (scale_exp < 0) { /* extreme high-level noise ==> spectrum must be previously adjusted */
              Word16 i, band_adj;
              Word16 negate_scale_exp;
              negate_scale_exp = negate(scale_exp);
              move16(); /*GetScaleFactorBandsTransmitted*/
              for (band_adj = 0 ; band_adj < GetScaleFactorBandsTransmitted(pIcsInfo); band_adj++) {
                for (i = BandOffsets[band_adj]; i < BandOffsets[band_adj + 1]; i++) {
                  spectrum[i] = L_shr(spectrum[i], negate_scale_exp);      move32();
                }
              }
                                                                            move16();
              pAacDecoderChannelInfo[channel]->pSpecScale[window] = sub(pAacDecoderChannelInfo[channel]->pSpecScale[window], scale_exp);
              scale_exp = 0;                                                move16();
            }

                                                                            test();
            if (CPns_IsCorrelated(pAacDecoderChannelInfo[0], group, band)) {
                                                                            test();
              if (channel == 0) {
                /* store random state for right channel */
                                                                            move16();
                pAacDecoderChannelInfo[0]->pPnsInterChannelData->randomState[pns_band] = pAacDecoderChannelInfo[0]->pPnsStaticInterChannelData->current_seed;
                GenerateRandomVector(scale_mant,
                                     scale_exp,
                                     spectrum,
                                     BandOffsets[band],
                                     BandOffsets[band + 1],
                                     &(pAacDecoderChannelInfo[0]->pPnsStaticInterChannelData->current_seed));
              }
              else {
                /* use same random state as was used for left channel */
                GenerateRandomVector(scale_mant,
                                     scale_exp,
                                     spectrum,
                                     BandOffsets[band],
                                     BandOffsets[band + 1],
                                     &(pAacDecoderChannelInfo[0]->pPnsInterChannelData->randomState[pns_band]));
              }
            } else {
              GenerateRandomVector(scale_mant,
                                   scale_exp,
                                   spectrum,
                                   BandOffsets[band],
                                   BandOffsets[band + 1],
                                   &(pAacDecoderChannelInfo[0]->pPnsStaticInterChannelData->current_seed));
            }
          }
        }
      }
    }
                                                                            add(0,0); /* Counting following operation */ move16();
    pAacDecoderChannelInfo[0]->pPnsStaticInterChannelData->current_seed += pAacDecoderChannelInfo[0]->pPnsStaticInterChannelData->pns_frame_number;
  } 
                                                                            test();
  if (channel == 0) {
                                                                            add(0,0); /* Counting following operation */ move16();
    pAacDecoderChannelInfo[0]->pPnsStaticInterChannelData->pns_frame_number++;
  }
}

void GenerateRandomVector (Word32 scale,
                           Word16 shift,
                           Word32 spec[],
                           Word16 bandOffsetStart,
                           Word16 bandOffsetEnd,
                           Word16 *random_seed)
{
  Word16 i;
  Word16 nrg_scale;
//  Word16 nrg_h, nrg_l;
//  Word16 scale_h, scale_l;
  Word32 nrg   = (Word32)0;                                                 move32();

  for (i = bandOffsetStart; i < bandOffsetEnd; i++) {
  //  Word16 spec_h, spec_l;

    *random_seed = (0x529 * *random_seed) + 0x3a7f;                         
    extract_l(0); L_add(0L,0L); L_shr(0L,0); L_mult(0,0); move16();

    /* to avoid overflows of the energy, we scale the spectrum down by PNS_SPEC_SCALE */
                                                                            move32();
    spec[i] = L_shl(*random_seed, (INT_BITS - SHORT_BITS - PNS_SPEC_SCALE));
#if 0

    L_Extract(spec[i], &spec_h, &spec_l);

    nrg = L_add(nrg, Mpy_32(spec_h, spec_l, spec_h, spec_l));
#else
    nrg += fixmul(spec[i], spec[i]);
#endif
  }

  /* normalize nrg to the range >= .25 */
  nrg_scale = norm_l(nrg);

                                                                            test();
  if (nrg_scale > 0) {
    nrg_scale &= ~1;                                                        logic16();
    nrg = L_shl(nrg, nrg_scale);
    shift = sub(shift, shr(nrg_scale, 1));
  }

  nrg = ffr_sqrt(nrg, (Word32) INT_BITS);

#if 0
  L_Extract(nrg, &nrg_h, &nrg_l);

  scale = Div_32(scale, nrg_h, nrg_l);
  L_Extract(scale, &scale_h, &scale_l);
#else
  scale = scale / nrg;
#endif
  for (i = bandOffsetStart; i < bandOffsetEnd; i++) {
#if 0
	  Word16 spec_h, spec_l;

	      L_Extract(spec[i], &spec_h, &spec_l);
	      spec[i] = L_shr(Mpy_32(spec_h, spec_l, scale_h, scale_l), shift);       move32();
#else
	      spec[i] = fixmul(spec[i], scale) << shift;
#endif
  }
}
