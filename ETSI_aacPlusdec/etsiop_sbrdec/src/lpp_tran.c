/*
   transposer
*/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lpp_tran.h"
#include "sbr_ram.h"
#include "sbr_rom.h"
#include "intrinsics.h"
#include "ffr.h"
#include "count.h"

#define neg32(x) L_sub(0,x)


typedef struct {
  Word32  r11r;
  Word32  r22r;
  Word32  r01r;
  Word32  r02r;
  Word32  r12r;
#ifndef LP_SBR_ONLY
  Word32  r01i;
  Word32  r02i;
  Word32  r12i;
#endif
  Word32  det;
} ACORR_COEFS;



#define LPC_SCALE_FACTOR 2

/*
  If the accumulator does not provide enough overflow bits,
  products have to be shifted down in the autocorrelation below.
*/
#define SHIFT 5


/*!
 * \brief Calculate second order autocorrelation using 2 accumulators
 */
static void 
autoCorrelation2ndLP(ACORR_COEFS *ac,  /*!< Pointer to autocorrelation coeffs */ 
                     Word32 *realBuf,     /*!< Pointer to real part of spectrum */
                     Word16 len           /*!< Number of qmf slots */
                     )                   
{

  const Word16 preScale = 2;
  Word16 j;
  Word16 mScale_r11r,mScale_r22r,mScale_r01r,mScale_r12r,mScale_r02r;
  Word16 mScale;
  Word32 temp;

  Word32 accu1, accu2;
  Word16 real1;
  Word16 real2;

  /*
    r11r,r22r
  */

  accu1 = 0;                                                                                        move32();
  sub(len,1);
  for ( j = 0; j < len - 1; j++ ) {
    real1 = shr(extract_h(realBuf[j-1]), preScale);
    accu1 = L_mac(accu1, real1, real1); 
  }

  real1 = shr(extract_h(realBuf[-2] ), preScale);
  accu2 = L_mac(accu1, real1, real1); 

  real1 = shr(extract_h(realBuf[j-1]), preScale);
  accu1 = L_mac(accu1, real1, real1); 

                                                                                                    test();
  if ((temp = L_shr(accu1, 8)))
    mScale_r11r = sub(ffr_norm32(temp), 8);
  else
  {
    mScale_r11r = INT_BITS - 9;                                                                   move16();
  }

                                                                                                    test();
  if ((temp = L_shr(accu2,8)))
    mScale_r22r = sub(ffr_norm32(temp), 8);
  else
  {
    mScale_r22r = INT_BITS - 9;                                                                     move16();
  }

  ac->r11r = L_shl(accu1, mScale_r11r);                                                             move32();  
  ac->r22r = L_shl(accu2, mScale_r22r);                                                             move32();  

  mScale = S_min(mScale_r11r, mScale_r22r);

  /*
    r01r,r12r
  */
  accu1 = 0;                                                                                        move32();
  sub(len,1);
  for ( j = 0; j < len - 1; j++ ) {
    real1 = shr(extract_h(realBuf[j]), preScale);
    real2 = shr(extract_h(realBuf[j-1]), preScale);
    accu1 = L_mac( accu1, real1, real2);
  }

  real1 = shr(extract_h(realBuf[-1]), preScale);
  real2 = shr(extract_h(realBuf[-2]), preScale);
  accu2 = L_mac( accu1, real1, real2);

  real1 = shr(extract_h(realBuf[j]), preScale);

  real2 = shr(extract_h(realBuf[j-1]), preScale);
  accu1 = L_mac( accu1, real1, real2);
  
                                                                                                    test();
  if ((temp = L_shr(accu1, 8)))
    mScale_r01r = sub(ffr_norm32(temp), 8);
  else
  {
    mScale_r01r = INT_BITS - 9;                                                                   move16();
  }

                                                                                                    test();
  if ((temp = L_shr(accu2, 8)))
    mScale_r12r = sub(ffr_norm32(temp), 8);
  else
  {
    mScale_r12r = INT_BITS - 9;                                                                     move16();
  }

  ac->r01r = L_shl(accu1, mScale_r01r);                                                             move32();  
  ac->r12r = L_shl(accu2, mScale_r12r);                                                             move32();  
  mScale = S_min(mScale, S_min(mScale_r01r,mScale_r12r));


  /* 
    r02r
  */
  accu1 = 0;                                                                                        move32();
  
  for ( j = 0; j < len; j++ ){
    real1 = shr(extract_h(realBuf[j]), preScale);
    real2 = shr(extract_h(realBuf[j-2]), preScale);
    accu1 = L_mac(accu1, real1, real2);
  }

                                                                                                    test();
  if ((temp = L_shr(accu1, 8)))
    mScale_r02r = sub(ffr_norm32(temp), 8);
  else
  {
    mScale_r02r = INT_BITS - 9;                                                                     move16();
  }
 
  ac->r02r = L_shl(accu1, mScale_r02r);                                                             move32();
  mScale = S_min(mScale, mScale_r02r);
 
  
  /* Scale to common scale factor */

  ac->r11r = L_shr(ac->r11r, sub(mScale_r11r, mScale));                                             move32();
  ac->r22r = L_shr(ac->r22r, sub(mScale_r22r, mScale));                                             move32();
  ac->r01r = L_shr(ac->r01r, sub(mScale_r01r, mScale));                                             move32();
  ac->r12r = L_shr(ac->r12r, sub(mScale_r12r, mScale));                                             move32();
  ac->r02r = L_shr(ac->r02r, sub(mScale_r02r, mScale));                                             move32();

  ac->det = L_sub( fixmul_32x16t(ac->r22r, ac->r11r), fixmul_32x16t(ac->r12r, ac->r12r) );          move32();

}

#ifndef LP_SBR_ONLY
static void 
autoCorrelation2nd (ACORR_COEFS *ac, /*!< Pointer to autocorrelation coeffs */ 
                    Word32 *realBuf,    /*!< Pointer to to real part of spectrum */
                    Word32 *imagBuf,    /*!< Pointer to imag part of spectrum */
                    Word16 len)         /*!< Number of qmf slots */
{
  static const Word16 preScale = 2 ;  
  Word32 x11r = 0, x01r = 0, x01i = 0 ;
  Word32 maximumValue = 0 ; 
  Word32 v = 0 ;
                                                                                                    move32(); move16(); move32();
                                                                                                    move32(); move32(); move32();
  {
    Word16 realPrev = shr(extract_h(realBuf[-1]), preScale);
    Word16 imagPrev = shr(extract_h(imagBuf[-1]), preScale);

    Word16 realPart = shr(extract_h(realBuf[0]), preScale);
    Word16 imagPart = shr(extract_h(imagBuf[0]), preScale);

    x01r = L_mac(x01r, realPart, realPrev);
    x01r = L_mac(x01r, imagPart, imagPrev);

    x01i = L_mult(imagPart, realPrev);
    x01i = L_msu(x01i, realPart, imagPrev);

    x11r = L_mac(x11r, realPrev, realPrev);
    x11r = L_mac(x11r, imagPrev, imagPrev);

    {
      Word16 n;
      Word32 *r = &realBuf[1]; 
      Word32 *i = &imagBuf[1]; 

      for (n = shr(sub(len, 2),1); n ; n--)
      {
        realPrev = realPart ;                                                                       move32();
        imagPrev = imagPart ;                                                                       move32();

        realPart = shr(extract_h(*r++), preScale);
        imagPart = shr(extract_h(*i++), preScale);

        x01r = L_mac(x01r, realPart, realPrev);
        x01r = L_mac(x01r, imagPart, imagPrev);

        x01i = L_mac(x01i, imagPart, realPrev);
        x01i = L_msu(x01i, realPart, imagPrev);

        x11r = L_mac(x11r, realPrev, realPrev);
        x11r = L_mac(x11r, imagPrev, imagPrev);

        realPrev = realPart ;                                                                       move32();
        imagPrev = imagPart ;                                                                       move32();

        realPart = shr(extract_h(*r++), preScale);
        imagPart = shr(extract_h(*i++), preScale);

        x01r = L_mac(x01r, realPart, realPrev);
        x01r = L_mac(x01r, imagPart, imagPrev);

        x01i = L_mac(x01i, imagPart, realPrev);
        x01i = L_msu(x01i, realPart, imagPrev);

        x11r = L_mac(x11r, realPrev, realPrev);
        x11r = L_mac(x11r, imagPrev, imagPrev);
      }

      test(); logic16();
      if (len & 0x01)
      {
        realPrev = realPart ;                                                                       move32();
        imagPrev = imagPart ;                                                                       move32();

        realPart = shr(extract_h(*r), preScale);
        imagPart = shr(extract_h(*i), preScale);

        x01r = L_mac(x01r, realPart, realPrev);
        x01r = L_mac(x01r, imagPart, imagPrev);

        x01i = L_mac(x01i, imagPart, realPrev);
        x01i = L_msu(x01i, realPart, imagPrev);

        x11r = L_mac(x11r, realPrev, realPrev);
        x11r = L_mac(x11r, imagPrev, imagPrev);
      }
    }
  }

  /* r11r, r22r */

  {
    Word32 x22r = x11r ;  
    Word16 realPart = shr(extract_h(realBuf[-2]), preScale);
    Word16 imagPart = shr(extract_h(imagBuf[-2]), preScale);
                                                                                                    move32();
    x22r = L_mac(x22r, realPart, realPart);
    x22r = L_mac(x22r, imagPart, imagPart);

    realPart = shr(extract_h(realBuf[len-2]), preScale);
    imagPart = shr(extract_h(imagBuf[len-2]), preScale);

    x11r = L_mac(x11r, realPart, realPart);
    x11r = L_mac(x11r, imagPart, imagPart);

    ac->r11r = x11r ;                                                                               move32();
    ac->r22r = x22r ;                                                                               move32(); 

                                                                                                    test();
    if (L_sub(x11r,maximumValue) > 0) {
      maximumValue = x11r ; move32();
    }
    
                                                                                                    test();
    if (L_sub(x22r,maximumValue) > 0) {
      maximumValue = x22r ; move32();
    }
  }

  /* r01r, r12r */

  {
    Word32 x12r = x01r ;                                                                            move32();

    x12r = L_mac(x12r, shr(extract_h(realBuf[-1]), preScale), shr(extract_h(realBuf[-2]), preScale));
    x12r = L_mac(x12r, shr(extract_h(imagBuf[-1]), preScale), shr(extract_h(imagBuf[-2]), preScale));
    x01r = L_mac(x01r, shr(extract_h(realBuf[len-1]), preScale), shr(extract_h(realBuf[len-2]), preScale));
    x01r = L_mac(x01r, shr(extract_h(imagBuf[len-1]), preScale), shr(extract_h(imagBuf[len-2]), preScale)) ;

    ac->r01r = x01r ;                                                                               move32();
    ac->r12r = x12r ;                                                                               move32();

    {
      Word32 tmp = L_abs (x01r) ;
                                                                                                    test();
      if (L_sub(tmp,maximumValue) > 0) 
      {
        maximumValue = tmp ;                                                                        move32();
      }
      tmp = L_abs (x12r) ;
                                                                                                    test();
      if (L_sub(tmp,maximumValue) > 0)
      {
        maximumValue = tmp ;                                                                        move32();
      }
    }
  }

  /* r01i, r12i */

  {
    Word32 x12i = x01i ;                                                                            move32();

    x12i = L_mac(x12i, shr(extract_h(imagBuf[-1]), preScale), shr(extract_h(realBuf[-2]), preScale));
    x12i = L_msu(x12i, shr(extract_h(realBuf[-1]), preScale), shr(extract_h(imagBuf[-2]), preScale));
    x01i = L_mac(x01i, shr(extract_h(imagBuf[len-1]), preScale), shr(extract_h(realBuf[len-2]), preScale));
    x01i = L_msu(x01i, shr(extract_h(realBuf[len-1]), preScale), shr(extract_h(imagBuf[len-2]), preScale));

    ac->r01i = x01i ;                                                                               move32();
    ac->r12i = x12i ;                                                                               move32();

    {
      Word32 tmp = L_abs (x01i) ;
                                                                                                    test();
      if (L_sub(tmp,maximumValue) > 0)
      {
        maximumValue = tmp ;                                                                        move32();
      }
      tmp = L_abs (x12i) ;
                                                                                                    test();
      if (L_sub(tmp,maximumValue) > 0) 
      {
        maximumValue = tmp ;                                                                        move32();
      }
    }
  }

  /* r02r, r02i */

  {
    Word16 n, len_2, p;
    Word32 x02r = 0x00, x02i = 0x00 ;                                                               move32(); move32();

    len_2 = shr(len,2);
    p = 0; move16();
    for (n = 0 ; n < len_2 ; n++)
    {
      /* realBuf[4*n], realBuf[4*n-2], imagBuf[4*n], imagBuf[4*n-2] */
      Word16 r,r2,i,i2;
      r = shr(extract_h(realBuf[p]), preScale); 
      r2 = shr(extract_h(realBuf[p-2]), preScale);
      i = shr(extract_h(imagBuf[p]), preScale);
      i2 = shr(extract_h(imagBuf[p-2]), preScale);

      x02r = L_mac(x02r, r, r2);
      x02r = L_mac(x02r, i, i2);
      x02i = L_mac(x02i, i, r2);
      x02i = L_msu(x02i, r, i2);

      /* realBuf[4*n+1], realBuf[4*n-1], imagBuf[4*n+1], imagBuf[4*n-1] */
      r = shr(extract_h(realBuf[p+1]), preScale); 
      r2 = shr(extract_h(realBuf[p-1]), preScale);
      i = shr(extract_h(imagBuf[p+1]), preScale); 
      i2 = shr(extract_h(imagBuf[p-1]), preScale);

      x02r = L_mac(x02r, r, r2);
      x02r = L_mac(x02r, i, i2);
      x02i = L_mac(x02i, i, r2);
      x02i = L_msu(x02i, r, i2);

      /* realBuf[4*n+2], realBuf[4*n], imagBuf[4*n+2], imagBuf[4*n] */
      r = shr(extract_h(realBuf[p+2]), preScale); 
      r2 = shr(extract_h(realBuf[p]), preScale);
      i = shr(extract_h(imagBuf[p+2]), preScale); 
      i2 = shr(extract_h(imagBuf[p]), preScale);

      x02r = L_mac(x02r, r, r2);
      x02r = L_mac(x02r, i, i2);
      x02i = L_mac(x02i, i, r2);
      x02i = L_msu(x02i,  r, i2);

      /* realBuf[4*n+3], realBuf[4*n+1], imagBuf[4*n+3], imagBuf[4*n+1] */
      r = shr(extract_h(realBuf[p+3]), preScale); 
      r2 = shr(extract_h(realBuf[p+1]), preScale);
      i = shr(extract_h(imagBuf[p+3]), preScale); 
      i2 = shr(extract_h(imagBuf[p+1]), preScale);

      x02r = L_mac(x02r, r, r2);
      x02r = L_mac(x02r, i, i2);
      x02i = L_mac(x02i, i, r2);
      x02i = L_msu(x02i, r, i2);
      p+=4;
    }

    for (n=shl(len_2,2); n < len ; n++)
    {
      Word16 r,r2,i,i2;
      r = shr(extract_h(realBuf[n]), preScale); 
      r2 = shr(extract_h(realBuf[n-2]), preScale);
      i = shr(extract_h(imagBuf[n]), preScale); 
      i2 = shr(extract_h(imagBuf[n-2]), preScale);

      x02r = L_mac(x02r, r, r2);
      x02r = L_mac(x02r, i, i2);
      x02i = L_mac(x02i, i, r2);
      x02i = L_msu(x02i, r, i2);
    }

    ac->r02r = x02r;                                                                               move32();
    ac->r02i = x02i;                                                                               move32();

    {
      Word32 tmp = L_abs (x02r) ;
                                                                                                    test();
      if (L_sub(tmp,maximumValue) > 0) 
      {
        maximumValue = tmp ;                                                                        move32();
      }
      tmp = L_abs (x02i ) ;
                                                                                                    test();
      if (L_sub(tmp,maximumValue) > 0) 
        
      {
        maximumValue = tmp ;                                                                        move32();
      }
    }
  }
                                                                                                    test();
  if (maximumValue)
  {
    Word16 scaleValue = ffr_norm32 (maximumValue);
    Word32 tmp;
                                                                                                    test();
    if (scaleValue)
    {
      ac->r11r = L_shl(ac->r11r, scaleValue) ;                                                      move32();
      ac->r22r = L_shl(ac->r22r, scaleValue) ;                                                      move32();
      ac->r01r = L_shl(ac->r01r, scaleValue) ;                                                      move32();
      ac->r12r = L_shl(ac->r12r, scaleValue) ;                                                      move32();
      ac->r01i = L_shl(ac->r01i, scaleValue) ;                                                      move32();
      ac->r12i = L_shl(ac->r12i, scaleValue) ;                                                      move32();
      ac->r02r = L_shl(ac->r02r, scaleValue) ;                                                      move32(); 
      ac->r02i = L_shl(ac->r02i, scaleValue) ;                                                      move32();
    }

    tmp = fixmuldiv2(ac->r12r,ac->r12r);
    fixmadd(&tmp,ac->r12i,ac->r12i);
    v = L_shl(L_sub(fixmuldiv2(ac->r11r,ac->r22r), tmp), 1) ;
  }

  ac->det = v ;                                                                                     move32();
}
#endif



/*!
 *
 * \brief Get bandwidth expansion factor from filtering level
 */
static Word32
mapInvfMode (INVF_MODE mode, 
             INVF_MODE prevMode)
{
  
  switch (mode) {
  case INVF_LOW_LEVEL:
                                                                                                    test();
    test();
    if(sub(prevMode,INVF_OFF) == 0)
      return 0x4ccccccd;
    else
      return 0x60000000;
      
  case INVF_MID_LEVEL:
    test(); test(); 
    return 0x73333333;

  case INVF_HIGH_LEVEL:
    test(); test(); test(); 
    return 0x7d70a3d7;
      
  default:
    test(); test(); test(); 
                                                                                                    test();
    if(sub(prevMode,INVF_LOW_LEVEL) == 0)
      return 0x4ccccccd;
    else
      return 0x0;
  }
}


/*!
 *
 * \brief Perform inverse filtering level emphasis
 *        
 */
static void
inverseFilteringLevelEmphasis(HANDLE_SBR_LPP_TRANS hLppTrans,/*!< Handle of lpp transposer  */
                              Word16     nInvfBands,         /*!< Number of bands for inverse filtering */
                              INVF_MODE *sbr_invf_mode,      /*!< Current inverse filtering modes */
                              INVF_MODE *sbr_invf_mode_prev, /*!< Previous inverse filtering modes */
                              Word32  * bwVector                /*!< Resulting filtering levels */
                              )
{
  Word16 i;
  Word32 accu;
  Word16 w1, w2;

  for(i = 0; i < nInvfBands; i++) {
    bwVector[i] = mapInvfMode (sbr_invf_mode[i],
                               sbr_invf_mode_prev[i]);           move32();

                                                                 test();
    if(L_sub(bwVector[i],hLppTrans->bwVectorOld[i]) < 0) {
      w1 = 0x6000;                                               move16();
      w2 = 0x2000;                                               move16();
    }
    else {
      w1 = 0x7400;                                               move16();
      w2 = 0x0c00;                                               move16();
    }
    accu = L_add(fixmul_32x16b(bwVector[i], w1), fixmul_32x16b(hLppTrans->bwVectorOld[i], w2));

    test();
    if ( L_sub(accu, 0x02000000) < 0)
    {
      accu = 0;                                                  move32();
    }

    test();
    if ( L_sub(accu,0x7f800000) >= 0)
    {
      accu = 0x7f800000;                                         move32();
    }
    bwVector[i] = accu;                                          move32();

  }


}


/*!
 *
 * \brief Perform transposition by patching of subband samples.
 *        
 */
void lppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans,    /*!< Handle of lpp transposer  */
                    SBR_SCALE_FACTOR  *sbrScaleFactor, /*!< Scaling factors */
                    Word32 **qmfBufferReal,            /*!< Pointer to pointer to real part of subband samples (source) */                
#ifndef LP_SBR_ONLY
                    Word32 **qmfBufferImag,            /*!< Pointer to pointer to imaginary part of subband samples (source) */
#endif
                    Word16 *degreeAlias,               /*!< Vector for results of aliasing estimation */ 
                    Word16 timeStep,                   /*!< Time step of envelope */
                    Word16 firstSlotOffs,              /*!< Start position in time */
                    Word16 lastSlotOffs,               /*!< Number of overlap-slots into next frame */
                    Word16 nInvfBands,                 /*!< Number of bands for inverse filtering */
                    Word16 maxQmfSubbandAac,           /*!< Actual start frequency for SBR */
                    INVF_MODE *sbr_invf_mode,          /*!< Current inverse filtering modes */
                    INVF_MODE *sbr_invf_mode_prev,     /*!< Previous inverse filtering modes */
                    Flag bUseLP
                    )
{
  Word32    bwIndex[MAX_NUM_PATCHES]; 
  Word32    bwVector[MAX_NUM_PATCHES];       /*!< pole moving factors */

  Word32    i;
  Word16    j;
  Word16    lb=0, hb=0, loBand, hiBand;
  PATCH_PARAM *patchParam = hLppTrans->pSettings->patchParam;
  Word16    patch;

  Word16  alphar[LPC_ORDER], a0r, a1r;
#ifndef LP_SBR_ONLY
  Word16  alphai[LPC_ORDER], a0i, a1i;
#endif
  Word16  bw = 0; 

  Word16  autoCorrLength;
  Word16  k1, k1_below=0, k1_below2=0;

  ACORR_COEFS ac;
  Word32    startSample;
  Word32    stopSample;
  Word32    stopSampleClear;

  Word16 comLowBandScale; 
  Word16 ovLowBandShift;
  Word16 lowBandShift; 
  Word16 targetStopBand;

  ac.r11r=0;
  ac.r22r=0;
  ac.r01r=0;
  ac.r02r=0;
  ac.r12r=0;
  ac.det=0;                                                                                                    move16(); move16(); move16(); move16();

  startSample = L_shr(L_mult(firstSlotOffs, timeStep), 1);
  stopSample  = L_add(hLppTrans->pSettings->nCols, L_shr(L_mult(lastSlotOffs, timeStep), 1)) ;

  
  inverseFilteringLevelEmphasis(hLppTrans, nInvfBands, sbr_invf_mode, sbr_invf_mode_prev, bwVector);



  
  /*
    Clean some bands for the current frame, and in case of a FIX frame border
    also within the overlap buffer
  */
  stopSampleClear = stopSample;                                                                     move32();

  /* 1. Clean the guard zones */
  move16(); /* hLppTrans->pSettings->noOfPatches */
  for ( patch = 0; patch < hLppTrans->pSettings->noOfPatches; patch++ ) {
    for (i = startSample; i < stopSampleClear; i++) {
      add(patchParam[patch].guardStartBand,GUARDBANDS);
      for(j=patchParam[patch].guardStartBand; j<patchParam[patch].guardStartBand+GUARDBANDS; j++){
        qmfBufferReal[i][j] = 0;                                                                    move32();
#ifndef LP_SBR_ONLY
        if (!bUseLP) {
          qmfBufferImag[i][j] = 0;                                                                  move32();
        }
#endif
      }
    }
  }

  /* 2.  Set upper subbands to zero:
     This is required in case that the patches do not cover the complete highband
     (because the last patch would be too short).
     Possible optimization: Clearing bands up to usb would be sufficient here. */
  targetStopBand = add(patchParam[sub(hLppTrans->pSettings->noOfPatches,1)].targetStartBand,
    patchParam[hLppTrans->pSettings->noOfPatches-1].numBandsInPatch);
  for (i = startSample; i < stopSampleClear; i++) {
    for (j=targetStopBand; j<NO_SYNTHESIS_CHANNELS; j++) {
      qmfBufferReal[i][j] = 0;                                                                      move32();
#ifndef LP_SBR_ONLY
      if (!bUseLP) {
        qmfBufferImag[i][j] = 0;                                                                    move32();
      }
#endif
    }
  }

  autoCorrLength = add(hLppTrans->pSettings->nCols, 6);

  /* init bwIndex for each patch */
  move16();
  for ( patch=0; patch<hLppTrans->pSettings->noOfPatches; patch++ )
  {
    bwIndex[patch] = 0;                                                                             move32();
  }

  /*
    Calc common low band scale factor
  */
  comLowBandScale = S_min(sbrScaleFactor->ov_lb_scale,sbrScaleFactor->lb_scale);
  
  ovLowBandShift =  sub(sbrScaleFactor->ov_lb_scale, comLowBandScale);
  lowBandShift   =  sub(sbrScaleFactor->lb_scale, comLowBandScale);



                                                                                                    test();
  if (bUseLP) {
    lb = S_max(1, sub(hLppTrans->pSettings->lbStartPatching, 2));
    hb = shr(shl(patchParam[0].targetStartBand,8),8);
  }
#ifndef LP_SBR_ONLY
  else {
    lb = hLppTrans->pSettings->lbStartPatching;                                                     move16();
    hb = hLppTrans->pSettings->lbStopPatching;                                                      move16();
  }
#endif

  for ( loBand = lb; loBand < hb; loBand++ ) {
    Word32 lowBandReal[MAX_COLS+MAX_OV_COLS+LPC_ORDER];
#ifndef LP_SBR_ONLY
    Word32 lowBandImag[MAX_COLS+MAX_OV_COLS+LPC_ORDER];
#endif
    Word32 lowBandPtr =0; 
    Flag resetLPCCoeffs=0;  
    
                                                                                                    move16(); move32();

    for(i=0;i<LPC_ORDER;i++){
      lowBandReal[lowBandPtr] = L_shr(hLppTrans->lpcFilterStatesReal[i][loBand], ovLowBandShift);   move32();
#ifndef LP_SBR_ONLY
                                                                                                    test();
      if (!bUseLP) {
        lowBandImag[lowBandPtr] = L_shr(hLppTrans->lpcFilterStatesImag[i][loBand], ovLowBandShift); move32();
      }
#endif
      lowBandPtr++;
    }
   

    /*
      Take old slope length qmf slot source values out of (overlap)qmf buffer
    */   

    for(i=0;i< 6;i++){   
      
      lowBandReal[lowBandPtr] = L_shr(qmfBufferReal[i][loBand],  ovLowBandShift);                   move32();
#ifndef LP_SBR_ONLY
                                                                                                    test();
      if (!bUseLP) {
        lowBandImag[lowBandPtr] = L_shr(qmfBufferImag[i][loBand],  ovLowBandShift);                 move32();
      }
#endif
      lowBandPtr++;
    }

    /*
      Take actual nCols qmf slot source values out of qmf buffer
    */   
    assert(hLppTrans->pSettings->nCols >= 18);
    add(hLppTrans->pSettings->nCols,6);
    for(i=6;i<hLppTrans->pSettings->nCols+6;i++){
      
      lowBandReal[lowBandPtr] = L_shr(qmfBufferReal[i][loBand], lowBandShift);                      move32();
#ifndef LP_SBR_ONLY
                                                                                                    test();
      if (!bUseLP) {
        lowBandImag[lowBandPtr] = L_shr(qmfBufferImag[i][loBand], lowBandShift);                    move32();
      }
#endif
      lowBandPtr++;
    }


                                                                                                    test();
    if (bUseLP) {
      autoCorrelation2ndLP(&ac,
                           &lowBandReal[LPC_ORDER],
                           autoCorrLength);
    }
#ifndef LP_SBR_ONLY
    else {
      autoCorrelation2nd(&ac,
                         &lowBandReal[LPC_ORDER],
                         &lowBandImag[LPC_ORDER],
                         autoCorrLength);
    }
#endif 

    alphar[1] = 0;                                                                                  move16();
#ifndef LP_SBR_ONLY
    alphai[1] = 0;                                                                                  move16();
#endif

                                                                                                    test();
    if (ac.det != 0) {
      Word32 tmp_r=0, absTmp_r, absDet;
#ifndef LP_SBR_ONLY
      Word32 tmp_i, absTmp_i;
#endif

      absDet = L_abs(ac.det);

                                                                                                    test();
      if (bUseLP) {
        tmp_r = L_shr(L_sub(fixmul(ac.r01r, ac.r12r), fixmul(ac.r02r, ac.r11r)), LPC_SCALE_FACTOR);
      }
#ifndef LP_SBR_ONLY
      else {
        tmp_r = L_shr(L_sub(L_sub(fixmul(ac.r01r, ac.r12r), fixmul(ac.r01i, ac.r12i)), fixmul(ac.r02r, ac.r11r)), LPC_SCALE_FACTOR);
        tmp_i = L_shr(L_sub(L_add(fixmul(ac.r01i, ac.r12r), fixmul(ac.r01r, ac.r12i)), fixmul(ac.r02i, ac.r11r)), LPC_SCALE_FACTOR);
        
        absTmp_i = L_abs(tmp_i);
      }
#endif
      absTmp_r = L_abs(tmp_r);

      /*  
        Quick check: is first filter coeff >= 1(4)
      */
                                                                                                    test();
      if(L_sub(absTmp_r,absDet) >= 0)
      {
        resetLPCCoeffs=1; move16();
      }
      else {
        alphar[1] = extract_l(ffr_divide16(tmp_r, ac.det));
      }

#ifndef LP_SBR_ONLY
                                                                                                    test();
      if (!bUseLP) {
        
        /*
          Quick check: is second filter coeff >= 1(4)
        */
                                                                                                    test();
        if(L_sub(absTmp_i,absDet) >= 0)
        {
          resetLPCCoeffs=1;  move16();
        }
        else {
          alphai[1] = extract_l(ffr_divide16(tmp_i, ac.det));
        }
      }
#endif
    }

    alphar[0] = 0;                                                                                  move16();
#ifndef LP_SBR_ONLY
    alphai[0] = 0;                                                                                  move16();
#endif

                                                                                                    test();
    if ( ac.r11r != 0 ) {

      /* ac.r11r is always >=0 */
      Word32 tmp_r=0,absTmp_r;

#ifndef LP_SBR_ONLY
      Word32 tmp_i,absTmp_i;
#endif


                                                                                                    test();
      if (bUseLP) {
        tmp_r = L_add(L_shr(ac.r01r, LPC_SCALE_FACTOR), fixmul_32x16b(ac.r12r, alphar[1]));
      }
#ifndef LP_SBR_ONLY
      else {
        tmp_r = L_add(L_add(L_shr(ac.r01r, LPC_SCALE_FACTOR), fixmul_32x16b(ac.r12r, alphar[1])), fixmul_32x16b(ac.r12i, alphai[1]));
        tmp_i = L_sub(L_add(L_shr(ac.r01i, LPC_SCALE_FACTOR), fixmul_32x16b(ac.r12r, alphai[1])), fixmul_32x16b(ac.r12i, alphar[1]));     
        absTmp_i = L_abs(tmp_i);
      }
#endif

      absTmp_r = L_abs(tmp_r);

      /*  
        Quick check: is first filter coeff >= 1(4)
      */
      
                                                                                                    test();
      if(L_sub(absTmp_r,ac.r11r) >= 0)
      {
        resetLPCCoeffs=1; move16();
      }
      else {
        alphar[0] = extract_l(ffr_divide16(neg32(tmp_r), ac.r11r));
      }
     
#ifndef LP_SBR_ONLY
                                                                                                    test();
      if (!bUseLP) {
        /*  
            Quick check: is second filter coeff >= 1(4)
        */
                                                                                                    test();
        if(L_sub(absTmp_i,ac.r11r) >= 0)
        {
          resetLPCCoeffs=1; move16();
        }
        else {
          alphai[0] = extract_l(ffr_divide16(neg32(tmp_i), ac.r11r));
        }
      }
#endif
    }


#ifndef LP_SBR_ONLY
                                                                                                    test();
    if (!bUseLP) {
      /* Now check the quadratic criteria */

                                                                                                    test();
      if(L_sub(L_add(L_shr(L_mult(alphar[0], alphar[0]), 1), L_shr(L_mult(alphai[0], alphai[0]), 1)), 0x40000000L) >= 0)
      {
        resetLPCCoeffs=1; move16();
      }
                                                                                                    test();
      if(L_sub(L_add(L_shr(L_mult(alphar[1], alphar[1]), 1), L_shr(L_mult(alphai[1], alphai[1]), 1)),0x40000000L) >= 0)
      {
        resetLPCCoeffs=1; move16();
      }
    }
#endif

                                                                                                    test();
    if(resetLPCCoeffs){
      alphar[0] = 0;                                                                                move16();
      alphar[1] = 0;                                                                                move16();
#ifndef LP_SBR_ONLY
      alphai[0] = 0;                                                                                move16();
      alphai[1] = 0;                                                                                move16();
#endif
    }

                                                                                                    test();
    if (bUseLP) {

      /* Aliasing detection */
                                                                                                    test();
      if(ac.r11r == 0) {
        k1 = 0;                                                                                     move16();
      }
      else {
                                                                                                    test();
        if ( L_sub(L_abs(ac.r01r),L_abs(ac.r11r)) >= 0) {
                                                                                                    test();
          if ( fixmul(ac.r01r, ac.r11r) < 0)
          {
            k1 = 0x7fff;                                                                            move16();
          }
          else
          {
            k1 = (Word16)0x8000;                                                                            move16();
          }
        }
        else {
          k1 = negate(extract_l(ffr_divide16(ac.r01r, ac.r11r)));
        }
      }

                                                                                                    test();
      if(sub(loBand,1) > 0){
        /* Check if the gain should be locked */
        Word16 deg = sub(0x7fff, mult(k1_below, k1_below));
        degreeAlias[loBand] = 0;                                                                    move16();
                                                                                                    test(); test(); logic16();
        if (((loBand & 1) == 0) && (k1 < 0)){
                                                                                                    test();
          if (k1_below < 0) {         /* 2-Ch Aliasing Detection */
            degreeAlias[loBand] = 0x7fff;                                                      move16();
                                                                                                    test();
            if ( k1_below2 > 0 ) {    /* 3-Ch Aliasing Detection */
              degreeAlias[loBand-1] = deg;                                                          move16();
            }
          }
          else {
                                                                                                    test();
              if ( k1_below2 > 0 ) { /* 3-Ch Aliasing Detection */
              degreeAlias[loBand] = deg;                                                            move16();
            }
          }
        }
                                                                                                    test(); test(); logic16();
        if (((loBand & 1) != 0) && (k1 > 0)){
                                                                                                    test();
          if (k1_below > 0) {         /* 2-CH Aliasing Detection */
            degreeAlias[loBand] = 0x7fff;                                                      move16();
                                                                                                    test();
            if ( k1_below2 < 0 ) {    /* 3-CH Aliasing Detection */
              degreeAlias[loBand-1] = deg;                                                          move16();
            }
          }
          else{ 
                                                                                                    test();
              if ( k1_below2 < 0 ) { /* 3-CH Aliasing Detection */
              degreeAlias[loBand] = deg;                                                            move16();
            }
          }
        }
      }
      /* remember k1 values of the 2 QMF channels below the current channel */
      k1_below2 = k1_below;                                                                         move16();
      k1_below = k1;                                                                                move16();
    }

    patch = 0;                                                                                      move16();
    test();
    while ( sub(patch,hLppTrans->pSettings->noOfPatches) < 0) { /* Loop over every patch */
                                                                                                    test();
      
      hiBand = shr(shl(add(loBand, patchParam[patch].targetBandOffs),8),8);
                                                                                                    test(); test(); 
      if ( sub(loBand,patchParam[patch].sourceStartBand) < 0 || sub(loBand,patchParam[patch].sourceStopBand) >= 0) {
        /* Lowband not in current patch - proceed */
        patch++;
        continue;
      }
      assert( hiBand < NO_SYNTHESIS_CHANNELS );

      /* check if target area is covered by core */
                                                                                                    test();
      if (sub(hiBand,maxQmfSubbandAac) < 0) {
        patch++;
        continue;
      }

      /* bwIndex[patch] is already initialized with value from previous band inside this patch */
                                                                                                    test();
      while (sub(hiBand,hLppTrans->pSettings->bwBorders[bwIndex[patch]]) >= 0)
      {
        bwIndex[patch] = L_add(bwIndex[patch], 1); move32();
        /* end of while */ test();
      }


      /* 
        Filter Step 2: add the left slope with the current filter to the buffer
                       pure source values are already in there
      */
      bw = extract_h(bwVector[bwIndex[patch]] );
      a0r = mult(bw, alphar[0]); /* Apply current bandwidth expansion factor */
#ifndef LP_SBR_ONLY
                                                                                                    test();
      if (!bUseLP) {
        a0i = mult(bw, alphai[0]);
      }
#endif
      bw =  mult(bw, bw);
      a1r = mult(bw, alphar[1]);
#ifndef LP_SBR_ONLY
                                                                                                    test();
      if (!bUseLP) {
        a1i = mult(bw, alphai[1]);
      }
#endif


      
      /* 
        Filter Step 3: insert the middle part which won't be windowed
      */
                                                                                                    test();
      if ( bw > 0 ) {

                                                                                                    test();
        if (bUseLP) {

          for(i = startSample; i < stopSample; i++ ) {
            qmfBufferReal[i][hiBand] = L_shr(lowBandReal[LPC_ORDER+i], LPC_SCALE_FACTOR);   move32();
            qmfBufferReal[i][hiBand] = L_add(L_add(qmfBufferReal[i][hiBand],
                                                   fixmul_32x16b(lowBandReal[LPC_ORDER+i-1], a0r)),
                                             fixmul_32x16b(lowBandReal[LPC_ORDER+i-2], a1r));       move32();
          }

        }
#ifndef LP_SBR_ONLY
        else {

          assert(stopSample - startSample >= 12);
          for(i = startSample; i < stopSample; i++ ) {
            Word32 accu;
            
            Word32 lowBandReal_i   = L_shr(lowBandReal[LPC_ORDER+i], LPC_SCALE_FACTOR);
            accu = L_sub(L_add(L_sub(fixmul_32x16b(lowBandReal[LPC_ORDER+i-1], a0r), 
                                     fixmul_32x16b(lowBandImag[LPC_ORDER+i-1], a0i)),
                               fixmul_32x16b(lowBandReal[LPC_ORDER+i-2], a1r)),
                         fixmul_32x16b(lowBandImag[LPC_ORDER+i-2], a1i));

            qmfBufferReal[i][hiBand] = L_add(lowBandReal_i, accu);
          }
          
          assert(stopSample - startSample >= 12);
          for(i = startSample; i < stopSample; i++ ) {
            Word32 accu;
            
            Word32 lowBandImag_i   = L_shr(lowBandImag[LPC_ORDER+i], LPC_SCALE_FACTOR);
            accu = L_add(L_add(L_add(fixmul_32x16b(lowBandReal[LPC_ORDER+i-1], a0i),
                                     fixmul_32x16b(lowBandImag[LPC_ORDER+i-1], a0r)),
                               fixmul_32x16b(lowBandReal[LPC_ORDER+i-2], a1i)),
                         fixmul_32x16b(lowBandImag[LPC_ORDER+i-2], a1r));

            qmfBufferImag[i][hiBand] = L_add(lowBandImag_i, accu);                                  move32();
          }
        }
#endif

      }
      else {
        assert(stopSample - startSample >= 12);
        for(i = startSample; i < stopSample; i++ ) {
          qmfBufferReal[i][hiBand] = L_shr(lowBandReal[LPC_ORDER+i], LPC_SCALE_FACTOR);    move32();
#ifndef LP_SBR_ONLY
          test();
          if (!bUseLP) {
            qmfBufferImag[i][hiBand] = L_shr(lowBandImag[LPC_ORDER+i], LPC_SCALE_FACTOR);   move32();
          }
#endif
        }
      }


      patch++;

    }  /* Patch */


  }  /* loBand (band) */

  
                                                                                                    test();
  if (bUseLP) {
    move16(); /* hLppTrans->pSettings->lbStopPatching */
    for ( loBand = hLppTrans->pSettings->lbStartPatching; loBand <  hLppTrans->pSettings->lbStopPatching; loBand++ ) {
      patch = 0;                                                                                    move16();
      while ( sub(patch,hLppTrans->pSettings->noOfPatches) < 0) {
                                                                                                    test();
        hiBand = shr(shl(add(loBand, patchParam[patch].targetBandOffs),8),8);
        
                                                                                                    test(); test(); test(); 
        if ( sub(loBand,patchParam[patch].sourceStartBand) < 0
             || sub(loBand,patchParam[patch].sourceStopBand) >= 0
             || sub(hiBand,NO_SYNTHESIS_CHANNELS) >= 0              /* Highband out of range (biterror) */
             ) {
          /* Lowband not in current patch or highband out of range (might be caused by biterrors)- proceed */
          patch++;
          continue;
        }
        
                                                                                                    test();
        if(sub(hiBand,patchParam[patch].targetStartBand) != 0)
        {
          degreeAlias[hiBand] = degreeAlias[loBand];                                                move16();
        }

        patch++;
      }
    }

  }


  for (i = 0; i < nInvfBands; i++ ) {
    hLppTrans->bwVectorOld[i] = bwVector[i];                                                        move32();
  }
  
  /*
    set high band scale factor
  */
  sbrScaleFactor->hb_scale = sub(comLowBandScale, LPC_SCALE_FACTOR);                        move16();
 
}


/*!
 *
 * \brief Initialize one low power transposer instance
 *        
 *
 */
Word16
createLppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans, /*!< Handle of low power transposer  */
                     Word16 highBandStartSb,  /*!< ? */
                     Word16 *v_k_master,      /*!< Master table */
                     Word16 numMaster,        /*!< Valid entries in master table */
                     Word16 usb,              /*!< Highband area stop subband */
                     Word16 nCols,            /*!< Number of colums (codec qmf bank) */
                     Word16* noiseBandTable,  /*!< Mapping of SBR noise bands to QMF bands */
                     Word16 noNoiseBands,     /*!< Number of noise bands */
                     Word32 fs,               /*!< Sample Frequency */
                     Word16 chan              /*!< Channel number */
                     )
{
  Word16 i, loBand;

  HANDLE_SBR_LPP_TRANS hs = hLppTrans;                                                              move32();

  hs->pSettings = &sbr_TransposerSettings;                                                          move32();


  /*
    Set pointer to filter states
  */
  hs->lpcFilterStatesReal[0] = sbr_LpcFilterStatesReal[chan][0];                                    move32();
  hs->lpcFilterStatesReal[1] = sbr_LpcFilterStatesReal[chan][1];                                    move32();

#ifndef LP_SBR_ONLY
  hs->lpcFilterStatesImag[0] = sbr_LpcFilterStatesImag[chan][0];                                    move32();
  hs->lpcFilterStatesImag[1] = sbr_LpcFilterStatesImag[chan][1];                                    move32();
#endif
  
  /* Init LPC filter states */
  for(i=0; i<LPC_ORDER; i++){
    for (loBand=0; loBand < NO_ANALYSIS_CHANNELS; loBand++) {
      hs->lpcFilterStatesReal[i][loBand] = 0;                                                       move32();
#ifndef LP_SBR_ONLY
      hs->lpcFilterStatesImag[i][loBand] = 0;                                                       move32();
#endif
    }
  }

                                                                                                    test();
  if (chan==0) {
    /* Init common data only once */
    hs->pSettings->nCols = nCols;                                                                   move16();

    return resetLppTransposer (hs,
                               highBandStartSb,
                               v_k_master,
                               numMaster,
                               noiseBandTable,
                               noNoiseBands,
                               usb,
                               fs);
  }
  return 0;
}


static Word16 findClosestEntry(Word16 goalSb, Word16 *v_k_master, Word16 numMaster, Word16 direction)
{
  Word16 index;

                                                                                                    test();
  if( sub(goalSb,v_k_master[0]) <= 0)
    return v_k_master[0];

                                                                                                    test();
  if( sub(goalSb,v_k_master[numMaster]) >= 0)
    return v_k_master[numMaster];

                                                                                                    test();
  if(direction) {
    index = 0;                                                                                      move16();
                                                                                                    test();
    while( sub(v_k_master[index],goalSb) < 0) {
      index++;
      test();
    }
  } else {
    index = numMaster;                                                                              move16();
                                                                                                    test();
    while( sub(v_k_master[index],goalSb) > 0) {
      index--;
      test();
    }
  }

  return v_k_master[index];
}


/*!
 *
 * \brief Reset memory for one lpp transposer instance
 *        
 *
 */
Word16
resetLppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans,  /*!< Handle of lpp transposer  */
                    Word16 highBandStartSb,   /*!< High band area: start subband */
                    Word16 *v_k_master,       /*!< Master table */
                    Word16 numMaster,         /*!< Valid entries in master table */
                    Word16* noiseBandTable,   /*!< Mapping of SBR noise bands to QMF bands */
                    Word16 noNoiseBands,      /*!< Number of noise bands */
                    Word16 usb,               /*!< High band area: stop subband */
                    Word32 fs                 /*!< SBR output sampling frequency */
                    )
{

  Word16    i, patch;
  Word16    targetStopBand;
  TRANSPOSER_SETTINGS *pSettings = hLppTrans->pSettings;  
  PATCH_PARAM  *patchParam = pSettings->patchParam;

  Word16 sourceStartBand;
  Word16 patchDistance;
  Word16 numBandsInPatch;
  
  Word16 lsb = v_k_master[0];        /* Start subband expressed in "non-critical" sampling terms*/ 
  Word16 xoverOffset = sub(highBandStartSb, lsb); /* Calculate distance in QMF bands between k0 and kx */

  Word16 goalSb;

                                                                                                    move16(); move16(); move16();

  /*
   * Plausibility check
   */

                                                                                                    test();
  if ( sub(lsb, SHIFT_START_SB+4) < 0 ) {
    return (1);
  }


  /*
   * Initialize the patching parameter
   */
  switch(fs){
  case 16000:
  case 22050:
  case 24000:
  case 32000:
    test();test();test();test();
    goalSb=64;                                                                                      move16();
    break;
  case 44100:
    test();test();test();test();test();
    goalSb=46;                                                                                      move16();
    break;
  case 48000:
    test();test();test();test();test();test();
    goalSb=43;                                                                                      move16();
    break;
  default:
    test();test();test();test();test();test();
    return(0);
  }

  goalSb = findClosestEntry(goalSb, v_k_master, numMaster, 1); move16();/* Adapt region to master-table */

                                                                                                    test();
  if ( sub(abs_s(sub(goalSb, usb)),4) < 0 ) {
    goalSb = usb;                                                                                   move16();
  }
  
 
  /* First patch */ 
  sourceStartBand = add(SHIFT_START_SB, xoverOffset);
  targetStopBand  = add(lsb, xoverOffset);

  /* Even (odd) numbered channel must be patched to even (odd) numbered channel */  
  patch = 0;                                                                                        move16();
                                                                                                    test();
  while(sub(targetStopBand,usb) < 0) {
    /* Too many patches?
       Allow MAX_NUM_PATCHES+1 patches here.
       we need to check later again, since patch might be the highest patch
       AND contain less than 3 bands => acutual number of patches will be reduced by 1.
    */
                                                                                                    test();
    if (sub(patch,MAX_NUM_PATCHES) > 0) {
      return -1;
    }

    patchParam[patch].guardStartBand = targetStopBand;                                              move16();
    targetStopBand = add(targetStopBand, GUARDBANDS);
    patchParam[patch].targetStartBand = targetStopBand;                                             move16();

    numBandsInPatch = sub(goalSb, targetStopBand);                   /* Get the desired range of the patch */

                                                                                                    test();
    if ( sub(numBandsInPatch,sub(lsb, sourceStartBand)) >= 0) {
      /* Desired number bands are not available -> patch whole source range */
      patchDistance   = sub(targetStopBand, sourceStartBand);        /* Get the targetOffset */
      patchDistance   = patchDistance & ~1;  /* Rounding off odd numbers and make all even */       logic16();
      numBandsInPatch = sub(lsb, sub(targetStopBand, patchDistance));  /* Update number of bands to be patched */
      numBandsInPatch = sub(findClosestEntry(add(targetStopBand, numBandsInPatch), v_k_master, numMaster, 0),
                        targetStopBand);  /* Adapt region to master-table */
    }

    /* Desired number bands are available -> get the minimal even patching distance */
    patchDistance   = sub(add(numBandsInPatch, targetStopBand), lsb);  /* Get minimal distance */
    patchDistance   = add(patchDistance, 1) & ~1; /* Rounding up odd numbers and make all even */   logic16();

                                                                                                    test();
    if (numBandsInPatch > 0) {
      patchParam[patch].sourceStartBand = sub(targetStopBand, patchDistance);                       move16();
      patchParam[patch].targetBandOffs  = patchDistance;                                            move16();
      patchParam[patch].numBandsInPatch = numBandsInPatch;                                          move16();
      patchParam[patch].sourceStopBand  = add(patchParam[patch].sourceStartBand, numBandsInPatch);  move16();

      targetStopBand = add(targetStopBand, patchParam[patch].numBandsInPatch);
      patch++;
    }

    /* All patches but first */
    sourceStartBand = SHIFT_START_SB;                                                               move16();

    /* Check if we are close to goalSb */
                                                                                                    test();
    if( sub(abs_s(sub(targetStopBand, goalSb)),3) < 0) {
      goalSb = usb;                                                                                 move16();
    }
    /* end of while */  test(); 
  }

  patch--;

  /* If highest patch contains less than three subband: skip it */
                                                                                                    test(); test(); 
  if ( (patch>0) && (sub(patchParam[patch].numBandsInPatch,3) < 0) ) {
    patch--;
    targetStopBand = add(patchParam[patch].targetStartBand, patchParam[patch].numBandsInPatch);
  } 

  /* now check if we don't have one too many */
                                                                                                    test();
  if (sub(patch,MAX_NUM_PATCHES) >= 0) {
    return -1;
  }

  pSettings->noOfPatches = add(patch, 1);  move16();

  /* Check lowest and highest source subband */
  pSettings->lbStartPatching = targetStopBand;                                                      move16();
  pSettings->lbStopPatching  = 0;                                                                   move16();
  move16(); /* pSettings->noOfPatches */
  for ( patch = 0; patch < pSettings->noOfPatches; patch++ ) {
    pSettings->lbStartPatching = S_min( pSettings->lbStartPatching,
                                      patchParam[patch].sourceStartBand );
    pSettings->lbStopPatching  = S_max( pSettings->lbStopPatching,
                                      patchParam[patch].sourceStopBand );
  }

  for(i = 0 ; i < noNoiseBands; i++){
    pSettings->bwBorders[i] = noiseBandTable[i+1];                                                  move16();
  }


  /* Init bwVector from previous frame */
  for (i = 0; i < MAX_NUM_PATCHES; i++ ) {
    hLppTrans->bwVectorOld[i] = 0;                                                                  move32();
  }

  return 0;
}


