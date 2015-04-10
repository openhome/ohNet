/*
   QMF filtering
*/

#include <assert.h>

#include <string.h>

#include "qmf_dec.h"
#include "dsp_fft32x32s.h"
#include "sbr_ram.h"
#include "sbr_rom.h"

#include "typedef.h"
#include "basic_op.h"
#include "oper_32b.h"
#include "count.h"

/*
 * Low-Power SBR functions
 */

static void dct3 (Word32 *data, 
                  Word32 *tmp, 
                  Word32 L,
                  HANDLE_SBR_QMF_FILTER_BANK qmfBank)
{
  Word16 i;
  Word32 xr, tmp2;
  Word16 cosphi,sinphi;
  Word16 p1, p2, p3, p4;

  Word32 M = L >> 1;    /* this is a constant: NO_ANALYSIS_CHANNELS/2 */
  Word32 N = L >> 2;    /* this is a constant: NO_ANALYSIS_CHANNELS/4 */
  int  a1,a2,a3,a4,a5,a6;

  for (i=1; i<M; i++) {

    sinphi = qmfBank->ralt_sin_twiddle[i];   move16(); /* sin((PI/(2*L))*(double)i); */
    cosphi = qmfBank->ralt_sin_twiddle[L-i]; move16(); /* cos((PI/(2*L))*(double)i); */
    
    tmp[2*i] =   L_add( fixmuldiv2_32x16b(data[i], cosphi),   fixmuldiv2_32x16b(data[L-i], sinphi) ); move32();
    tmp[2*i+1] = L_sub( fixmuldiv2_32x16b(data[L-i], cosphi), fixmuldiv2_32x16b(data[i], sinphi) );   move32();
  }

  xr     = fixmuldiv2_32x16b(data[M] , qmfBank->ralt_sin_twiddle[M]);/* cos((PI/(2*L))*M); */
  tmp2   = L_shr(data[0],1);

  tmp[0] = L_add( tmp2, xr );                                    move32();
  tmp[1] = L_sub( tmp2, xr );                                    move32();

  p1 = 4; move16();       /* initialize counter  4*i */
  p2 = L-4; move16();     /* initialize counter  L-4*i */
  p3 = (M-1)*2; move16(); /* initialize counter  (M-i)*2 */
  p4 = 2; move16();       /* initialize counter  2*i */
  for (i=1; i<N; i++) {

    sinphi = qmfBank->ralt_sin_twiddle[p1];  move16(); /*sin((2.0*PI/(L))*(double)i);*/
    cosphi = qmfBank->ralt_sin_twiddle[p2];  move16(); /*cos((2.0*PI/(L))*(double)i);*/
    
    a2 = L_add(tmp[p4+1], tmp[p3+1]);
    a3 = L_sub(tmp[p3],   tmp[p4]);
    
    a5 = L_add(fixmuldiv2_32x16b(a2 , cosphi), fixmuldiv2_32x16b(a3 , sinphi) );
    a6 = L_sub(fixmuldiv2_32x16b(a3 , cosphi), fixmuldiv2_32x16b(a2 , sinphi) );
    
    a1 = L_shr( L_add(tmp[p4],   tmp[p3]),   1 );
    a4 = L_shr( L_sub(tmp[p4+1], tmp[p3+1]), 1 );
    
    tmp[p4] = L_sub(a1,a5);                                      move32();
    tmp[p3] = L_add(a1,a5);                                      move32();
    
    tmp[p4+1] = L_sub(a4,a6);                                    move32();
    tmp[p3+1] = L_negate(L_add(a6,a4));                          move32();
    
    p1 += 4;
    p2 -= 4;
    p3 -= 2;
    p4 += 2;
  }

  
  DSP_fft32x32s (M, tmp); 
    
  p1 = 0; move16();       /* initialize counter  2*i */
  p2 = L-1; move16();     /* initialize counter  L-1-i */
  for (i = 0; i < M; i++) {
    data[p1]   = tmp[i];                                        move32();
    data[p1+1] = tmp[p2];                                       move32();
    p1 += 2;
    p2 -= 1;
  }
  
}


/*!
 *
 * \brief Perform dct type 2
 * The dct 2 is calculated by a real inverse fft, with 
 * some pre twiddeling after the  fft, as discribed by Takuya OOURA.
 * The real inverse fft is calculated by a inverse complex fft, as described
 * in numerical recipes in C, Cambridge University press
 * the auxiliary function is built by reversing the odd samples
 *
 * Scaling 1 shift in pre twiddeling, 
 *         5 in cfft
 */
static void
dct2 (Word32 *data,                      /*!< pointer to data (inplace) */
      Word32 *tmp,                       /*!< temp buffer of lenght L */
      Word32 L,                          /*!< length */
      HANDLE_SBR_QMF_FILTER_BANK qmfBank /*!< Handle of qmfBank  */
      )
{
  Word16 cosphi,sinphi;
  Word16 i;
  Word32 M = L >> 1; /* this is a constant: NO_ANALYSIS_CHANNELS/2 */
  Word32 N = L >> 2; /* this is a constant: NO_ANALYSIS_CHANNELS/4 */
  Word32  a1,a2,a3,a4,a5,a6;
  Word16 p1, p2, p3, p4;

  for (i = 0; i < M; i++) {
    tmp[i] = data[2 * i];                                        move32();
    tmp[L - 1 - i] = data[2 * i + 1];                            move32();
  }

  DSP_fft32x32s (M, tmp);
  
  p1 = 4; move16();       /* initialize counter  4*i */
  p2 = L-4; move16();     /* initialize counter  L-4*i */
  p3 = (M-1)*2; move16(); /* initialize counter  (M-i)*2 */
  p4 = 2; move16();       /* initialize counter  2*i */
  for (i=1; i <N; i++) {

    sinphi = qmfBank->ralt_sin_twiddle[p1]; move16(); /*sin((2.0*PI/(L))*(double)i);*/
    cosphi = qmfBank->ralt_sin_twiddle[p2]; move16(); /*cos((2.0*PI/(L))*(double)i);*/
    
    a2 = L_add(tmp[p4+1], tmp[p3+1]);
    a3 = L_sub(tmp[p3],   tmp[p4]);
    
    a5 = L_add( fixmuldiv2_32x16b(a2 , cosphi), fixmuldiv2_32x16b(a3 , sinphi) );
    a6 = L_sub( fixmuldiv2_32x16b(a3 , cosphi), fixmuldiv2_32x16b(a2 , sinphi) );
    
    a1 = L_shr( L_add(tmp[p4],   tmp[p3]),   1 );
    a4 = L_shr( L_sub(tmp[p4+1], tmp[p3+1]), 1 );
    
    tmp[p4] = L_add(a1,a5);                                     move32();
    tmp[p3] = L_sub(a1,a5);                                     move32();
    
    tmp[p4+1] = L_negate( L_add(a4,a6) );                       move32();
    tmp[p3+1] = L_sub(a4,a6);                                   move32();

    p1 += 4;
    p2 -= 4;
    p3 -= 2;
    p4 += 2;
  }

  p1 = 2; move16();       /* initialize counter  2*i */
  p2 = L-1; move16();     /* initialize counter  L-i */
  for (i=1; i <M; i++) {
  
    cosphi = qmfBank->ralt_sin_twiddle[p2]; /* cos((PI/(2*L))*(double)i); */
    sinphi = qmfBank->ralt_sin_twiddle[i];   /* sin((PI/(2*L))*(double)i); */
    
    data[i]     = L_sub( fixmuldiv2_32x16b( tmp[p1],   cosphi), fixmuldiv2_32x16b(tmp[p1+1], sinphi) ); move32();
    data[p2] = L_add( fixmuldiv2_32x16b( tmp[p1+1], cosphi), fixmuldiv2_32x16b(tmp[p1],   sinphi) ); move32();
    p1 += 2;
    p2 -= 1;
  }
  
  data[0]  = L_add( L_shr(tmp[0],1), L_shr(tmp[1],1) );          move32();
  data[M] =  fixmuldiv2_32x16b(L_sub(tmp[0],tmp[1]) , qmfBank->ralt_sin_twiddle[M]); move32();
  
}


/*!
 *
 * \brief Perform real-valued forward modulation of the time domain
 *        data of timeIn and stores the real part of the subband
 *        samples in rSubband
 *
 */
static void
forwardModulationLP (const Word32 *timeIn,              /*!< Time Signal */
                     Word32 *rSubband,                  /*!< Real Output */
                     HANDLE_SBR_QMF_FILTER_BANK qmfBank /*!< Handle of qmfBank */
                     )
{
  Word16 i;
  const int L = NO_ANALYSIS_CHANNELS;
  const int M = L/2;
  Word32 accu;

  rSubband[0] = L_shr(timeIn[M-1],1);                            move32();
  
  for (i = 1; i < M; i++) {
    accu = L_add( L_shr(timeIn[M - 1 + i],1) , L_shr(timeIn[M - 1 - i],1) );
    rSubband[i] = accu;                                          move32();
  }
  
  for (i = M; i < L; i++) {
    accu = L_sub( L_shr(timeIn[M - 1 + i],1) , L_shr(timeIn[5 * M - 1 - i],1) );
    rSubband[i] = accu;                                          move32();
  }

  dct3 (rSubband, qmfBank->dctTempBuffer, L, qmfBank);
}


#if 0
/*!
 *
 * \brief Cosine modulation of the time domain data of a subband. Performed in-place
 *
 */
static void
butterfly( Word32 re, Word32 im, Word16 wre, Word16 wim, Word32 *xr, Word32 *xi )
{
  Word16 reh, rel, imh, iml;
  Word32 rH;
  
  splitWord32(re, &rel, &reh);
  splitWord32(im, &iml, &imh);

  rH = L_mult(imh, wim);
  rH = L_mac(rH, reh, wre);
  rH = L_mac(rH, mult(iml,wim), 1);
  rH = L_mac(rH, mult(rel,wre), 1);
  *xi = rH;                                             move32();
  
  rH = L_mult(imh, wre);
  rH = L_msu(rH, reh, wim);
  rH = L_mac(rH, mult(iml,wre), 1);
  rH = L_msu(rH, mult(rel,wim), 1);
  *xr = rH;                                             move32();
}
#endif

#ifndef LP_SBR_ONLY
static void cosMod (Word32 *subband, HANDLE_SBR_QMF_FILTER_BANK qmfBank)
{
  Word32 im2 ;
  Word16 wim, wre ;

  Word16 i, k, M2, M_2, p1, p2;
  Word16 M = shr(qmfBank->no_channels, 1);
  const Word16 *pCos = &qmfBank->cos_twiddle[0];
  const Word16 *pSin = &qmfBank->sin_twiddle[0];
  move16(); move16();

  M_2 = shr(M,1);         /* M/2 */

  k  = sub(M,1);          /* initialize counter  k=M-i-1 */
  p1 = shl(k,1);          /* initialize counter    2*k */
  p2 = 0; move16();       /* initialize counter    2*i */
  for (i = 0; i < M_2 ; i += 2)
  { 
    im2 = subband [p2 + 1] ;                                    move32();
    
    butterfly(subband [p2], subband [p1 + 1], pCos [i], pSin [i], &subband [p2 + 1], &subband [p2]);
    
    butterfly(subband [p1], im2, pCos [k], pSin [k], &subband [p1 + 1], &subband [p1]);
    
    im2 = subband [p2 + 3] ;                                    move32();
    
    butterfly(subband [p2+2], subband [p1 - 1], pCos [i + 1], pSin [i + 1], &subband [p2 + 3], &subband [p2+2]);
    
    butterfly(subband [p1 - 2], im2, pCos [k - 1], pSin [k - 1], &subband [p1 - 1], &subband [p1 - 2]);
    
    k  -= 2;
    p1 -= 4;
    p2 += 4;
  }
  
  DSP_fft32x32s (M, subband) ;
  
  M2 = sub(add(M, M), 2);               /* M2 = 2 * M - 2 */
  im2 = subband [M2 + 1];                                        move32();
  
  subband [M2 + 1]      = L_negate(subband [1]) ;                move32();

  wim = qmfBank->alt_sin_twiddle[1] ;                            move16();
  wre = qmfBank->alt_sin_twiddle[M - 1] ;                        move16();

  butterfly(im2, subband [M2], wre, wim, &subband [1], &subband [M2]);

  k  = sub(M,2);          /* initialize counter  k=M-i-1 */
  p1 = shl(k,1);          /* initialize counter    2*k */
  p2 = 2; move16();       /* initialize counter    2*i */
  for (i = 1 ; i < M_2 ; i++)
  { 
    im2 = subband [p1 + 1];                                     move32();
    
    butterfly(subband [p2 + 1], subband [p2], wim, wre, &subband [p1 + 1], &subband [p2]);
    
    wim = qmfBank->alt_sin_twiddle [i + 1] ;                     move16();
    wre = qmfBank->alt_sin_twiddle [k] ;                         move16();
    
    butterfly(im2, subband [2*k], wre, wim, &subband [2*i + 1], &subband [2*k]);

    k--;
    p1 -= 2;
    p2 += 2;
  }
}



/*!
 *
 * \brief Sine modulation of the time domain data of a subband. Performed in-place
 *
 */
static void sinMod (Word32 *subband, HANDLE_SBR_QMF_FILTER_BANK qmfBank)
{
  Word32 im2 ;
  Word16 wre, wim ;

  Word16 i, k, M2, M_2, p1, p2;
  Word16 M = shr(qmfBank->no_channels, 1);
  const Word16 *pCos = &qmfBank->cos_twiddle[0];
  const Word16 *pSin = &qmfBank->sin_twiddle[0];
  move16(); move16();

  M_2 = shr(M,1);         /* M/2 */

  k  = sub(M,1);          /* initialize counter  k=M-i-1 */
  p1 = shl(k,1);          /* initialize counter    2*k */
  p2 = 0; move16();       /* initialize counter    2*i */
  for (i = 0; i < M_2 ; i += 2)
  { 
    im2 = subband [p2 + 1] ;                                    move32();
    
    butterfly(subband [p2], subband [p1 + 1], pSin [i], pCos [i], &subband [p2], &subband [p2 + 1]);
    
    butterfly(subband [p1], im2, pSin [k], pCos [k], &subband [p1], &subband [p1 + 1]);
    
    
    im2 = subband [p2 + 3] ;                                    move32();

    butterfly(subband [p2+2], subband [p1 - 1], pSin [i + 1], pCos [i + 1], &subband [p2+2], &subband [p2+3]);
    
    butterfly(subband [p1 - 2], im2, pSin [k - 1], pCos [k - 1], &subband [p1 - 2], &subband [p1 - 1]);
    
    k  -= 2;
    p1 -= 4;
    p2 += 4;
  }
  
  DSP_fft32x32s (M, subband) ;
    
  M2 = sub(add(M, M), 2);               /* M2 = 2 * M - 2 */
  im2 = subband [M2 + 1];                                        move32();
  
  subband [M2 + 1] = L_negate(subband [0]) ;                     move32();
  subband [0]      = subband[1] ;                                move32();
  
  wim = negate(qmfBank->alt_sin_twiddle [1]) ;
  wre = negate(qmfBank->alt_sin_twiddle [M - 1]) ;

  butterfly(im2, subband [M2], wre, wim, &subband [M2], &subband [1]);

  k  = sub(M,2);          /* initialize counter  k=M-i-1 */
  p1 = shl(k,1);          /* initialize counter    2*k */
  p2 = 2; move16();       /* initialize counter    2*i */
  for (i = 1 ; i < M_2 ; i++)
  {
    im2 = subband [p1 + 1] ;                                    move32();
    
    butterfly(subband [p2 + 1], subband [p2], wim, wre, &subband [p2], &subband [p1 + 1]);
    
    wim = negate(qmfBank->alt_sin_twiddle [i + 1]) ;
    wre = negate(qmfBank->alt_sin_twiddle [k]) ;
    
    butterfly(im2, subband [p1], wre, wim, &subband [p1], &subband [p2 + 1]);

    k--;
    p1 -= 2;
    p2 += 2;
  }
}

/*!
 *
 * \brief Perform complex-valued forward modulation of the time domain
 *                data of timeIn and stores the real part of the subband
 *                samples in rSubband, and the imaginary part in iSubband
 *
 */
static void 
forwardModulation (const Word32 *timeIn, Word32 *rSubband, Word32 *iSubband,
                   HANDLE_SBR_QMF_FILTER_BANK qmfBank)
{
  Word16 i;
  Word16 j = 2 * NO_ANALYSIS_CHANNELS - 1;                       move16();
  
  for (i = 0; i < NO_ANALYSIS_CHANNELS; i++, j--)
  {
    rSubband[i] = L_sub(timeIn [j], timeIn [i]) ;                move32();
    iSubband[i] = L_add(timeIn [j], timeIn [i]) ;                move32();
  }

  cosMod (rSubband, qmfBank) ;
  sinMod (iSubband, qmfBank) ;

  move16(); /* qmfBank->usb */
  for (i = qmfBank->lsb; i < qmfBank->usb; i++)
  {
    Word16 reh, rel, imh, iml;
    Word16 cosh, sinh;
    Word32 acc;
    cosh = qmfBank->t_cos[i];
    sinh = qmfBank->t_sin[i];
    L_Extract(rSubband[i], &reh, &rel);
    L_Extract(iSubband[i], &imh, &iml);
    
    acc = L_mult(reh, cosh);
    acc = L_mac(acc, imh, sinh);
    acc = L_mac(acc, mult(rel, cosh), 1);
    acc = L_mac(acc, mult(iml, sinh), 1);
    rSubband[i] = acc;                                           move32();
    acc = L_mult(imh, cosh);
    acc = L_msu(acc, reh, sinh);
    acc = L_mac(acc, mult(iml, cosh), 1);
    acc = L_msu(acc, mult(rel, sinh), 1);
    iSubband[i] = acc;                                           move32();
  }
}
#endif

static void 
AnalysisPolyphaseFiltering (Word32 *analysisBuffer,
                            Word16 *filterStates,
                            const Word16 *pFilter
                            )
{
  Word16 k, p;
  const Word16 *pFilterR = &pFilter[QMF_FILTER_STATE_ANA_SIZE - 2 * NO_POLY];
  move16();
  pFilter += NO_POLY;
  
  for (k = 0; k < NO_ANALYSIS_CHANNELS; k++) {
    Word16 *fp1, *fp2;
    Word32 accu1 = 0;
    Word32 accu2 = 0;                                            move32(); move32();
    
    fp1 = &filterStates[k];                                      move16();
    fp2 = fp1 + NO_ANALYSIS_CHANNELS;                            move16();
    
    for (p = 0; p < NO_POLY * 2; p += 2) {
      accu1 = L_mac(accu1, *fp1, *pFilter++);
      accu2 = L_mac(accu2, *fp2, *--pFilterR);
      fp1 += (2 * NO_ANALYSIS_CHANNELS);
      fp2 += (2 * NO_ANALYSIS_CHANNELS);
    }
    pFilter  += NO_POLY;
    pFilterR -= NO_POLY;
    
    analysisBuffer[k]                        = L_shr(accu1, 7);  move32();
    analysisBuffer[NO_ANALYSIS_CHANNELS + k] = L_shr(accu2, 7);  move32();
  }
}

static void 
SynthesisPolyphaseFiltering(Word16 *pFilterStates,              /*!< Pointer to filter states */
                            const Word16 *pFilter,              /*!< Pointer to filter coefficients */
                            Word32 *pReal,                      /*!< Low and High band slot, real */
                            Word32 *pImag,                      /*!< Low and High band slot, imag */
                            Word16 *pTimeOut,                   /*!< Pointer to output */
                            Word16 outScalefactor,              /*!< scalefactor to output */
                            Word16 no_synthesis_channels,
                            Word16 qmf_filter_state_syn_size)
{
  Word16 j, p;
  Word16 outScalefactorm1, offset1, offset2, offset3, offset4, step;
  const Word16 *pFilterR = &sbr_qmf_64_640[QMF_FILTER_STATE_ANA_SIZE + NO_POLY];               move16();

  outScalefactorm1 = sub(outScalefactor,1);
  
  offset2 = shl(no_synthesis_channels,1);
  step    = shl(offset2,1);
  offset1 = sub(qmf_filter_state_syn_size,offset2);
  offset3 = add(no_synthesis_channels,offset2);
  offset2 = sub(no_synthesis_channels,1);
  offset4 = sub(qmf_filter_state_syn_size,no_synthesis_channels);

  /* offset1: qmf_filter_state_syn_size-2*no_synthesis_channels */
  /* offset2: no_synthesis_channels -1 */
  /* offset3: 2*no_synthesis_channels + no_synthesis_channels */
  /* offset4: qmf_filter_state_syn_size-  no_synthesis_channels */
  /* step:    2 * 2*no_synthesis_channels */

  for (j = 0; j < no_synthesis_channels; j++){
    Word32 accu;
    Word16 *pFilterStat16i;
    Word16 *pFilterStat16r;

    accu = 0;                                                                                  move32();

    pFilterStates[offset1 + j] = etsiopround(L_shl(pImag[offset2 - j], outScalefactorm1));   move16();
    pFilterStates[offset4 + j] = etsiopround(L_shl(pReal[offset2 - j], outScalefactorm1));   move16();

    pFilterStat16i = &pFilterStates[j];                                                        move16();
    pFilterStat16r = &pFilterStates[offset3 + j];      move16();

    test();
    if(sub(no_synthesis_channels,NO_SYNTHESIS_CHANNELS_DOWN_SAMPLED) == 0){
      pFilterR -= NO_POLY;
      pFilter  += NO_POLY;
    }

    for (p = 0; p < NO_POLY; p++) {
      accu = L_mac(accu, *pFilterStat16i, *pFilter++);
      accu = L_mac(accu, *pFilterStat16r, *--pFilterR);

      pFilterStat16i += step;
      pFilterStat16r += step;
    }

    pTimeOut[offset2 - j] = etsiopround(accu);                               move16();
  }

  /* the memmove here is not instrumented since on a DSP this would be done by modulo addressing */
  memmove(pFilterStates,pFilterStates+2*no_synthesis_channels,
          (qmf_filter_state_syn_size - 2*no_synthesis_channels) * sizeof(Word16));
}

/*!
 *
 * \brief Perform complex-valued subband filtering of the time domain
 *                data of timeIn and stores the real part of the subband
 *                samples in rAnalysis, and the imaginary part in iAnalysis
 *
 */

void
cplxAnalysisQmfFiltering (const Word16 *timeIn,                 /*!< Time signal */
                          SBR_SCALE_FACTOR  *sbrScaleFactor,    /*!< Scaling factors */
                          Word32 **qmfReal,                     /*!< Pointer to real subband slots */
#ifndef LP_SBR_ONLY
                          Word32 **qmfImag,                     /*!< Pointer to imag subband slots */
#endif
                          HANDLE_SBR_QMF_FILTER_BANK qmfBank,   /*!< Handle of Qmf Analysis Bank */
                          Flag bUseLP
                          )
{
  Word32 analysisBuffer [2 * NO_ANALYSIS_CHANNELS] ;
  Word16 i, k;

  sbrScaleFactor->st_lb_scale = 0 ;                              move16();

                                                          test();move16();
  if (bUseLP)
    sbrScaleFactor->lb_scale = -10 ;
  else
    sbrScaleFactor->lb_scale = -8 ; 


  for (i = 0; i < qmfBank->no_col; i++)
  {
    /* feed time signal into oldest NO_ANALYSIS_CHANNELS states */
    Word16 *src, *dst;
    Word16 *filterStates = qmfBank->FilterStatesAna +
      (QMF_FILTER_STATE_ANA_SIZE - NO_ANALYSIS_CHANNELS);        move16();
    
    for ( k = 0; k < NO_ANALYSIS_CHANNELS; k++ ) {
      filterStates [k] = timeIn [k] ;                            move16();
    }
    
    AnalysisPolyphaseFiltering (analysisBuffer, qmfBank->FilterStatesAna, qmfBank->p_filter_ana) ;

    test();
    if (bUseLP) {
      forwardModulationLP (analysisBuffer, 
                       qmfReal [i],
                       qmfBank) ;
    }
#ifndef LP_SBR_ONLY
    else {
      forwardModulation (analysisBuffer, 
                         qmfReal [i],
                         qmfImag [i],
                         qmfBank) ;
    }
#endif
    
    /* shift filter states */
    
    src = qmfBank->FilterStatesAna + NO_ANALYSIS_CHANNELS;       move16();
    dst = qmfBank->FilterStatesAna;                              move16();

    for(k = 0; k < QMF_FILTER_STATE_ANA_SIZE - NO_ANALYSIS_CHANNELS; ++k) 
    {
      *dst++ = *src++;                                           move16();
    }
    
    timeIn += NO_ANALYSIS_CHANNELS ;
  }
}

static void
inverseModulationLP (Word32 *qmfReal,                     /*!< Pointer to qmf real subband slot (input/output) */
                     Word32 *qmfReal2,                    /*!< Pointer to qmf real subband slot (output)*/
                     const Word16 scaleFactorLowBand,     /*!< Scalefactor for Low band */
                     const Word16 scaleFactorHighBand,    /*!< Scalefactor for High band */
                     HANDLE_SBR_QMF_FILTER_BANK synQmf    /*!< Handle of Qmf Synthesis Bank  */
                   )
{
  Word16 i;
  const Word16 L = synQmf->no_channels;
  const Word16 M = shr(L,1);
  Word32 timeOut[2*NO_SYNTHESIS_CHANNELS];

  move16(); /* init L */
  

  /* Move input to output vector with offset */
  move16(); /* synQmf->lsb */
  for (i = 0; i < synQmf->lsb; i++) {
    timeOut[i + M] = L_shl(qmfReal[i],scaleFactorLowBand);      move32();
  }

  move16(); /* synQmf->usb */
  for (i = synQmf->lsb; i < synQmf->usb; i++) {
    timeOut[i + M] = L_shl(qmfReal[i],scaleFactorHighBand);     move32();
  }

  for (i = synQmf->usb; i < L; i++) {
    timeOut[i + M] = 0;                                         move32();
  }

  /* Dct type-2 transform */
  dct2(timeOut+M, synQmf->dctTempBuffer, L, synQmf);

  /* Expand output */
  timeOut[3 * M] = 0;                                           move32();          

  for (i = 1; i < M; i++) {
    timeOut[i + 3 * M] = L_negate(timeOut[3 * M - i]);          move32();
  }

  for (i = 0; i < M; i++) {
    timeOut[i] = timeOut[L - i];                                move32();
  }

  /* timeOut buffer should be replaced by qmfReal and qmfReal2 buffer */
  for (i = 0; i < L; i++) {
    qmfReal[i] = timeOut[i];                                    move32();
  }

  for (i = 0; i < L; i++) {
    qmfReal2[i] = timeOut[L+i];                                 move32();
  }

}


#ifndef LP_SBR_ONLY
/*!
 *
 * \brief Perform complex-valued inverse modulation of the subband
 *                samples stored in rSubband (real part) and iSubband (imaginary
 *                part) and stores the result in timeOut
 *
 */
static void
inverseModulation (Word32 *qmfReal,                       /*!< Pointer to qmf real subband slot */
                   Word32 *qmfImag,                       /*!< Pointer to qmf imag subband slot */
                   Word16 scaleFactorLowBand,             /*!< Scalefactor for Low band */
                   Word16 scaleFactorHighBand,            /*!< Scalefactor for High band */
                   HANDLE_SBR_QMF_FILTER_BANK synQmf      /*!< Handle of Qmf Synthesis Bank  */
                   )
{
  Word16 i, j;
  Word16 M;
  Word16 scaleFactorLowBandm8 = sub(scaleFactorLowBand, 8);
  Word16 scaleFactorHighBandm8 = sub(scaleFactorHighBand, 8);
  Word16 no_synthesis_channels = synQmf->no_channels; move16();

  M = shr(no_synthesis_channels,1);
    
  /* Low band area */
  move16(); /* synQmf->lsb */
  for (i = 0; i < synQmf->lsb ; i++)  
  {
    qmfReal[i] = L_negate(L_shl(qmfReal[i], scaleFactorLowBandm8)) ;  move32();
    qmfImag[i] = L_negate(L_shl(qmfImag[i], scaleFactorLowBandm8)) ;  move32();
  }
  
  /* High band area */
  move16(); /* synQmf->usb */
  for (i = synQmf->lsb; i < synQmf->usb; i++)
  {
    qmfReal[i] = L_negate(L_shl(qmfReal[i], scaleFactorHighBandm8)) ; move32();
    qmfImag[i] = L_negate(L_shl(qmfImag[i], scaleFactorHighBandm8)) ; move32();
  }
  
  cosMod (qmfReal, synQmf) ;
  sinMod (qmfImag, synQmf) ;

  j = sub(no_synthesis_channels,1);
  for (i = 0 ; i < M ; i++, j--)
  { 
    Word32 r1, r2, i1, i2;
    r1 = qmfReal[i] ;
    i2 = L_negate( qmfImag[j] ) ;
    r2 = qmfReal[j] ;
    i1 = L_negate( qmfImag[i] ) ;
    
    qmfReal[i] = L_add(r1, i1);                                         move32();
    qmfImag[j] = L_sub(i1, r1);                                         move32();
    qmfReal[j] = L_add(r2, i2);                                         move32();
    qmfImag[i] = L_sub(i2, r2);                                         move32();
  }
}
#endif

/*!
 *
 *
 * \brief Perform complex-valued subband synthesis of the
 *                low band and the high band and store the
 *                time domain data in timeOut
 *
 */
void
cplxSynthesisQmfFiltering (Word32 **qmfReal,                   /*!< Low and High band, real */
#ifndef LP_SBR_ONLY
                           Word32 **qmfImag,                   /*!< Low and High band, imag */
#endif
                           Word32 splitSlot,                   /*!< split Slot of overlap and actual slots */
                           SBR_SCALE_FACTOR *sbrScaleFactor,   /*!< Scaling factors */
                           Word16 *timeOut,                    /*!< Pointer to output */
                           HANDLE_SBR_QMF_FILTER_BANK qmfBank, /*!< Handle of Qmf Synthesis Bank  */
#ifndef MONO_ONLY
                           HANDLE_PS_DEC hPS,                  /*!< Handle of parametric stereo decoder */
                           Flag active,                        /*!< parametricstereo activ flag */
#endif
                           Flag bUseLP
                           )
{
  Word16 i, j;
 
  Word16 codScalefactor;
  Word16 sbrScalefactor;
  Word16 outScalefactor;
  Word16 scaleFactorLowBand;
  Word16 scaleFactorHighBand;
  Word16 *filterStates = qmfBank->FilterStates;
  Word32 qmfReal2[NO_SYNTHESIS_CHANNELS];

  Word16 no_synthesis_channels = qmfBank->no_channels;
  Word16 p1;

#ifndef MONO_ONLY
  Word32 qmfRealTmp[NO_SYNTHESIS_CHANNELS];
  Word32 *qmfImagTmp = qmfReal2;
  Word8  env=0;

  move16(); /* init qmfImagTmp */
  move16(); /* init env */
#endif
  move16(); /* filterStates */
  move16(); /* no_synthesis_channels */

  /*
        scaling
  */
#ifndef MONO_ONLY
  test();
  if(active){
    codScalefactor = sbrScalefactor = sbrScaleFactor->ps_scale;                   move16(); move16();
  }
  else{
#endif
    codScalefactor = S_min(sbrScaleFactor->lb_scale, sbrScaleFactor->ov_lb_scale);
    sbrScalefactor = sbrScaleFactor->hb_scale ;                                   move16();

#ifndef MONO_ONLY
  }
#endif

  scaleFactorLowBand = sub(sbrScaleFactor->st_syn_scale, codScalefactor);

  scaleFactorHighBand = sub(sbrScaleFactor->st_syn_scale, sbrScalefactor);

  test();
  if (bUseLP)
    outScalefactor = negate(sub(sbrScaleFactor->st_syn_scale, 1)) ;
  else
    outScalefactor = negate(sub(sbrScaleFactor->st_syn_scale, 3)) ;

  p1 = 0; move16(); /* init counter:  i*no_synthesis_channels */
  move16(); /* qmfBank->no_col */
  for (i = 0 ; i < qmfBank->no_col ; i++)
  {
    Word16 scaleFactorLowBandSplit;
    Word32 *imagSlot;

    test(); move16();
    if (bUseLP)
      imagSlot = qmfReal2;
#ifndef LP_SBR_ONLY
    else
      imagSlot = qmfImag[i];
#endif

#ifndef MONO_ONLY
    test();
    if(active){
      test();
      if(sub(i,hPS->aEnvStartStop[env]) == 0){
        InitRotationEnvelope(hPS, env, qmfBank->usb);
        env++;
      }
      ApplyPsSlot(hPS,
                  &qmfReal[i],
                  &qmfImag[i],
                  qmfRealTmp,
                  qmfImagTmp,
                  sbrScaleFactor,
                  i,
                  qmfBank->lsb);
      scaleFactorLowBandSplit=scaleFactorLowBand;
    }
    else{
#endif
      test();
      if ( L_sub(L_deposit_l(i), splitSlot) < 0 )
        scaleFactorLowBandSplit = add(sub(scaleFactorLowBand, sbrScaleFactor->ov_lb_scale), codScalefactor);
      else
        scaleFactorLowBandSplit = add(sub(scaleFactorLowBand, sbrScaleFactor->lb_scale), codScalefactor);
#ifndef MONO_ONLY
    }
#endif



#ifndef  LP_SBR_ONLY
    test();
    if(!bUseLP) {

      test();
      if (sub(no_synthesis_channels,NO_SYNTHESIS_CHANNELS_DOWN_SAMPLED) == 0){

        for (j = 0; j < no_synthesis_channels; j++){
          Word32 temp;

          temp = qmfReal[i][j];                                  move32();
          qmfReal[i][j] = L_add( fixmul_32x16b(qmfReal[i][j], qmfBank->t_cos[j]) , fixmul_32x16b(imagSlot[j], qmfBank->t_sin[j]) );
          imagSlot[j]   = L_sub( fixmul_32x16b(imagSlot[j],   qmfBank->t_cos[j]) , fixmul_32x16b(temp,        qmfBank->t_sin[j]) );
        }
      }
    }
#endif


    test();
    if (bUseLP) {
      inverseModulationLP (qmfReal [i], imagSlot, sub(scaleFactorLowBandSplit,4), sub(scaleFactorHighBand,4), qmfBank) ;
    }
#ifndef LP_SBR_ONLY
    else {
      inverseModulation (qmfReal [i], imagSlot, scaleFactorLowBandSplit, scaleFactorHighBand, qmfBank) ;      
    }
#endif
    
    SynthesisPolyphaseFiltering(filterStates, qmfBank->p_filter, qmfReal[i],
                                imagSlot, 
                                &timeOut[p1], 
                                outScalefactor,
                                no_synthesis_channels,
                                qmfBank->qmf_filter_state_size);

#ifndef MONO_ONLY
    test();
    if(active){
      memcpy(qmfReal[i], qmfRealTmp, no_synthesis_channels*sizeof(Word32)); memop32(no_synthesis_channels);
      memcpy(qmfImag[i], qmfImagTmp, no_synthesis_channels*sizeof(Word32)); memop32(no_synthesis_channels);
    }
#endif
    p1 += no_synthesis_channels;
  }

}

/*!
 *
 * \brief Create QMF filter bank instance
 *
 * \return 0 if succesful
 *
 */
Word32
createCplxAnalysisQmfBank (HANDLE_SBR_QMF_FILTER_BANK h_sbrQmf, /*!< Returns handle */
                           SBR_SCALE_FACTOR  *sbrScaleFactor,   /*!< Scale factors */
                           Word16 noCols,                                                       /*!< Number of timeslots per frame */
                           Word16 usb,                                                  /*!< Upper end of lowband */
                           Word16 chan)                                                 /*!< Number of Instance */
{
  Word16 i;

  memset(h_sbrQmf, 0, sizeof(SBR_QMF_FILTER_BANK));                memop16(sizeof(SBR_QMF_FILTER_BANK)/sizeof(Word16));

  h_sbrQmf->p_filter_ana = sbr_qmf_64_640 + 2 * NO_POLY;           move16();

  h_sbrQmf->no_channels = NO_ANALYSIS_CHANNELS ;                   move16();
  h_sbrQmf->no_col = noCols ;                                      move16();       /* sbrFrameSize/no_channels */

  h_sbrQmf->lsb = 0 ;                                              move16();
  h_sbrQmf->usb = usb ;                                            move16();

  h_sbrQmf->ralt_sin_twiddle = (Word16*) sbr_ralt_sin_twiddle_L32; move16();

#ifndef LP_SBR_ONLY
  h_sbrQmf->cos_twiddle      = (Word16*) sbr_cos_twiddle_L32;      move16();
  h_sbrQmf->sin_twiddle      = (Word16*) sbr_sin_twiddle_L32;      move16();
  h_sbrQmf->alt_sin_twiddle  = (Word16*) sbr_alt_sin_twiddle_L32;  move16();

  h_sbrQmf->t_cos            = (Word16*) sbr_t_cos_L32 ;           move16();
  h_sbrQmf->t_sin            = (Word16*) sbr_t_sin_L32 ;           move16();
#endif

  test();
  h_sbrQmf->FilterStatesAna =
    &(sbr_CodecQmfStatesAnalysis[chan?QMF_FILTER_STATE_ANA_SIZE:0]); move16();
  for(i=0;i<QMF_FILTER_STATE_ANA_SIZE;i++) {
    h_sbrQmf->FilterStatesAna[i] = 0;                              move16();
  }
  
  sbrScaleFactor->st_lb_scale = 0 ;                                move32();

  return 0 ;
}


/*!
 *
 * \brief Create QMF filter bank instance
 *
 * \return 0 if successful
 *
 */
Word32
createCplxSynthesisQmfBank (HANDLE_SBR_QMF_FILTER_BANK h_sbrQmf, /*!< Handle to return */
                            SBR_SCALE_FACTOR *sbrScaleFactor,    /*!< Scaling factors */
                            Word16 noCols,                       /*!< Number of timeslots per frame */
                            Word16 lsb,                          /*!< Lower end of SBR frequency range */
                            Word16 usb,                          /*!< Upper end of SBR frequency range */
                            Word16 chan,                         /*!< Number of instance */
                            Flag bDownSample
                            )
{
  Word16 L;
  Word16 i;
  Word16 qmfFilterStateSize;

  memset(h_sbrQmf, 0, sizeof(SBR_QMF_FILTER_BANK));                memop16(sizeof(SBR_QMF_FILTER_BANK)/sizeof(Word16));

  if(bDownSample){

    L = NO_SYNTHESIS_CHANNELS_DOWN_SAMPLED;                        move16();
    qmfFilterStateSize = QMF_FILTER_STATE_SYN_SIZE_DOWN_SAMPLED;   move16();
  }
  else{

    L = NO_SYNTHESIS_CHANNELS;                                     move16();
    qmfFilterStateSize = QMF_FILTER_STATE_SYN_SIZE;                move16();
  }

  h_sbrQmf->p_filter = sbr_qmf_64_640 + 2 * NO_POLY;               move16();

  h_sbrQmf->no_channels = L;                                       move16();
  h_sbrQmf->qmf_filter_state_size = qmfFilterStateSize;            move16();
  h_sbrQmf->no_col = noCols;                                       move16();

  h_sbrQmf->lsb = lsb;                                             move16();
  test();
  if(bDownSample){
    h_sbrQmf->usb = NO_SYNTHESIS_CHANNELS_DOWN_SAMPLED;            move16();
  }
  else{
    h_sbrQmf->usb = usb;                                           move16();
  }

  test();
  if(sub(L,32) == 0){
    h_sbrQmf->ralt_sin_twiddle = (Word16*) sbr_ralt_sin_twiddle_L32; move16();
  }
  else {
    h_sbrQmf->ralt_sin_twiddle = (Word16*) sbr_ralt_sin_twiddle_L64; move16();
  }

#ifndef LP_SBR_ONLY
  test();
  if(sub(L,32) == 0){
    h_sbrQmf->cos_twiddle = (Word16*)sbr_cos_twiddle_L32;          move16();
    h_sbrQmf->sin_twiddle = (Word16*)sbr_sin_twiddle_L32;          move16();
    h_sbrQmf->alt_sin_twiddle = (Word16*)sbr_alt_sin_twiddle_L32;  move16();
    h_sbrQmf->t_cos = (Word16*)sbr_cos_twiddle_ds_L32;             move16();
    h_sbrQmf->t_sin = (Word16*)sbr_sin_twiddle_ds_L32;             move16();
  }
 else {
   h_sbrQmf->cos_twiddle      = (Word16*)sbr_cos_twiddle_L64;      move16();
   h_sbrQmf->sin_twiddle      = (Word16*)sbr_sin_twiddle_L64;      move16();
   h_sbrQmf->alt_sin_twiddle  = (Word16*)sbr_alt_sin_twiddle_L64;  move16();
 }
#endif

  /* chan*qmfFilterStateSize is either 0 or qmfFilterStateSize I think... */
  test();
  h_sbrQmf->FilterStates =
    &sbr_QmfStatesSynthesis[chan?qmfFilterStateSize:0];     move16();

  for(i=0;i<qmfFilterStateSize;i++) {
    h_sbrQmf->FilterStates[i] = 0;                                 move16();
  }


/*
 * HQ-SBR:
 *
 * The scaling in forwardModulation() is caused by:
 *
 *       \li 1 R_SHIFT in forwardModulation()
 *       \li 1 R_SHIFT in cosMod() / sinMod()
 *       \li 4 R_SHIFT in cfft()
 *       \li 1 ommited gain of 2.0 of twiddle factors t_cos,t_sin
 *
 * The scaling in cplxSynthesisQmfFiltering() is caused by:
 *
 *       \li  1 R_SHIFT in cosMod() / sinMod()
 *       \li  1 R_SHIFT in inverseModulation()
 *       \li  5 R_SHIFT in cfft()
 *       \li -6 algorithmic division by 64 in synthesis filterbank
 */


/*
 * LP-SBR:
 *
 * The scaling in forwardModulation() is caused by:
 *
 *   \li 1 R_SHIFT in polyphase filter
 *   \li 1 R_SHIFT in forwardModulation()
 *   \li 5 R_SHIFT in dct3()
 *   \li 1 ommited gain of 2.0 in forwardModulation
 *
 * The scaling in cplxSynthesisQmfFiltering() is caused by:
 *
 *   \li  1 R_SHIFT in polyphase filter
 *   \li  6 R_SHIFT in dct2() and dct4()
 *   \li  1 ommited gain of 2.0 in inverseModulation()
 *   \li -6 division by 64 in synthesis filterbank
 */

  /* scale synthesis - scale analysis */
  sbrScaleFactor->st_syn_scale = -6;                          move16();
  return 0 ;
}
