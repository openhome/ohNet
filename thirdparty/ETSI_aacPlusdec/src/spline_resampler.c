/*
   Spline-Interpolation-Resampler
 */
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "spline_resampler.h"
#include "ffr.h"
#include "intrinsics.h"
#include "count.h"

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

static const Word16 __2_3 =  0x5555;  /* 2.0f/3.0f */
static const Word16 __1_6 =  0x1555;  /* 1.0f/6.0f */


static const Word32 a_22_16 = 0x13333333; /* 0.3f / 2 */
static const Word32 b_22_16 = 0x53333333; /* 1.3f / 2 */

static const Word32 a_24_16 = 0x0f5c28f6; /* 0.24f / 2 */
static const Word32 b_24_16 = 0x4f5c28f6; /* 1.24f / 2 */


static const Word32 a_22_8 = 0x03d70a3d;  /* 0.06f / 2 */
static const Word32 b_22_8 = 0x43d70a3d;  /* 1.06f / 2 */

static const Word32 a_24_8 = 0x03333333;  /* 0.05f / 2 */
static const Word32 b_24_8 = 0x43333333;  /* 1.05f / 2 */


struct SPLINE_RESAMPLER { 
  
  Word16 remainder;
  Word16 quotient;

  Word16 distance[2];

  Word16 L;
  Word16 M;

  Word32 invL;

  Word16 oldSamples[MAX_ORDER][2];
  Word16 position[2];

  Word32 iirFilterCoeff_b;
  Word32 iirFilterCoeff_a;

  Word16 oldSampleFilter[2];

} splineResamplerInstance;


static Word16
calcCoeff1(Word16 a, Word16 a_2, Word16 a_3)
{
  return add(sub(__1_6, mult(a_3,__1_6)), shr(sub(a_2,a), 1));
}


static Word16
calcCoeff2(Word16 a_2, Word16 a_3)
{
  return add (sub(shr(a_3,1), a_2), __2_3);
}


static Word16
calcCoeff3(Word16 a, Word16 a_2, Word16 a_3)
{
  return add(sub(add(shr(a,1), shr(a_2,1)), shr(a_3,1)),__1_6);
}


static Word16
calcCoeff4(Word16 a_3)
{
  return mult(a_3,__1_6);
}




/************************************************************************/
/*!
   \brief   Create spline resampler

*/
/************************************************************************/
int
CreateSplineResampler(HANDLE_SPLINE_RESAMPLER* hr,/*!< Handle of resampler */ 
                      Word16 Fin,                 /*!< Input sample rate */ 
                      Word16 Fout                 /*!< Output sample rate */ 
                      )
{
  Word16 i;

  *hr = &splineResamplerInstance;

  (*hr)->L = Fout;                                              move16();
  (*hr)->M = Fin;                                               move16();

  (*hr)->distance[0]  = 0;                                      move16();
  (*hr)->distance[1]  = 0;                                      move16();

  (*hr)->remainder = (Fin % Fout); /* note: this is an integer representation */ move16();
  (*hr)->quotient  = (Fin / Fout); /* note: this is an integer representation */ move16();

  (*hr)->position[0]  = 0;                                      move16();
  (*hr)->position[1]  = 0;                                      move16();

  for (i=0; i<MAX_ORDER; i++) {
    (*hr)->oldSamples[i][0] = 0;                                move16();
    (*hr)->oldSamples[i][1] = 0;                                move16();
  }

  test();
  switch(Fin){

  case 22050:
    test(); move32(); move32(); move32();
    switch(Fout){
    case 16000:
      (*hr)->iirFilterCoeff_a = a_22_16;
      (*hr)->iirFilterCoeff_b = b_22_16;
      (*hr)->invL             = 0x20c4a;  /* 1.0f/16000 */
      break;
    case 8000:
      (*hr)->iirFilterCoeff_a = a_22_8;
      (*hr)->iirFilterCoeff_b = b_22_8;
      (*hr)->invL             = 0x41893;  /* 1.0f/8000 */
      break;
    }
    break;

  case 24000:
    test(); move32(); move32(); move32();
    switch(Fout){
    case 16000:
      (*hr)->iirFilterCoeff_a = a_24_16;
      (*hr)->iirFilterCoeff_b = b_24_16;
      (*hr)->invL             = 0x20c4a;  /* 1.0f/16000 */
      break;
    case 8000:
      (*hr)->iirFilterCoeff_a = a_24_8;
      (*hr)->iirFilterCoeff_b = b_24_8;
      (*hr)->invL             = 0x41893;  /* 1.0f/8000 */
      break;
    }
    break;

  default:
    return 1;
  }

  return 0;
}

/************************************************************************/
/*!
   \brief   Copy resampler state
   needed if switching form mono to stereo     

*/
/************************************************************************/
 
void CopyResamplerState(HANDLE_SPLINE_RESAMPLER hr /*!< Handle of resampler */
                        )
{
  hr->distance[1] = hr->distance[0];                            move16();
  hr->position[1] = hr->position[0];                            move16();
}

/************************************************************************/
/*!
   \brief   Spline resampling
   Resampling is done on ioBuffer, which is not interleaved in
   case of more than one channel

*/
/************************************************************************/
void SplineResample(HANDLE_SPLINE_RESAMPLER hr,   /*!< Handle of resampler */
                    Word16* ioBuffer,             /*!< Input/output buffer */
                    Word16 inSamples,             /*!< Number of input samples */
                    Word16* outSamples,           /*!< Number of output samples */
                    Word16 ch                     /*!< Channel index */
                    ) 
{
  Word16 i, k, samplesOut, outIndex = 0;
  Word16 inIndex = 0;
  Word16 numTmpOutSamples = 0;

  Word16 alpha, alpha_2, alpha_3, coeff;
  Word32 tmp, tmp_2, accu;

  Word16 tmpOutSamples[MAX_ORDER+1];
  Word16 *pos;

  move16(); move16(); move16();


  /* special treatment for the first output samples: may need oldSamples */
  test();
  while ( sub(hr->position[ch],3) < 0 ){ 

    tmp     = hr->invL * hr->distance[ch];                      fixmul_32x16b(0,0); /* Note: this is a fract by int multiplication, counting operations */
    alpha   = extract_h(tmp);
    tmp_2   = fixmul_32x16b(tmp, alpha);
    alpha_2 = extract_h(tmp_2);
    alpha_3 = extract_h(fixmul_32x16b(tmp, alpha_2));


    /*
      in the following mac operations, we shift up the 16 bit input values 1 
      bit less to the right than possible to avoid overflows and allow clipping later 
    */

    coeff = calcCoeff1(alpha, alpha_2, alpha_3);

    test();
    if (hr->position[ch] >= 3) {

       accu = L_shr(L_mult(coeff, ioBuffer[hr->position[ch] - 3]),1);

    }
    else {

      accu =L_shr(L_mult(coeff, hr->oldSamples[hr->position[ch]][ch]),1);
    }
    

    coeff = calcCoeff2(alpha_2, alpha_3);

    test();
    if (hr->position[ch] >= 2) {

      accu = L_add (accu, L_shr(L_mult(coeff, ioBuffer[hr->position[ch] - 2]),1) );
    }
    else {

      accu = L_add (accu, L_shr(L_mult(coeff, hr->oldSamples[hr->position[ch] + 1][ch]),1) );
    }

    
    coeff = calcCoeff3(alpha, alpha_2, alpha_3);

    test();
    if (hr->position[ch] >= 1) {

      accu = L_add (accu, L_shr(L_mult(coeff, ioBuffer[hr->position[ch] - 1]),1) );
    }
    else {

      accu = L_add (accu, L_shr(L_mult(coeff, hr->oldSamples[hr->position[ch] + 2][ch]),1) );
    }
    

    coeff = calcCoeff4(alpha_3);

    accu = L_add (accu, L_shr(L_mult(coeff, ioBuffer[hr->position[ch]]),1) );

    tmpOutSamples[numTmpOutSamples++] = etsiopround( L_shl(accu,1) );  move16();

    /* Update variables */
    hr->position[ch] += hr->quotient;
    hr->distance[ch] += hr->remainder;

    test();
    if ( sub(hr->distance[ch], hr->L) >= 0 ) {
      hr->distance[ch] -= hr->L;
      hr->position[ch] += 1;
    }

  }
  
  inIndex =  hr->position[ch] - 3;

  assert (inIndex >=0);

  
  /* now we have to work up input buffer samples such long that we can start writing the output samples ... */
  test();
  while(numTmpOutSamples) 
  {
    tmp     = hr->invL * hr->distance[ch];                      fixmul_32x16b(0,0); /* Note: this is a fract by int multiplication, counting operations */
    alpha   = extract_h(tmp);
    tmp_2   = fixmul_32x16b(tmp, alpha);
    alpha_2 = extract_h(tmp_2);
    alpha_3 = extract_h(fixmul_32x16b(tmp, alpha_2));

    pos = &ioBuffer[inIndex];


    /*
      in the following mac operations, we shift up the 16 bit input values 1 
      bit less to the right than possible to avoid overflows and allow clipping later 
    */

    coeff = calcCoeff1(alpha, alpha_2, alpha_3);
    accu  = L_mult(coeff, shr(*pos++,1));

    coeff = calcCoeff2(alpha_2, alpha_3);
    accu  = L_mac(accu, coeff, shr(*pos++,1));
  
    coeff = calcCoeff3(alpha, alpha_2, alpha_3);
    accu  = L_mac(accu, coeff, shr(*pos++,1));
  
    coeff = calcCoeff4(alpha_3);
    accu  = L_mac(accu, coeff, shr(*pos++,1));

    tmpOutSamples[numTmpOutSamples++] = etsiopround( L_shl(accu,1) );  move16();

    assert (numTmpOutSamples <= MAX_ORDER+1);


    /* Update variables */
    inIndex          += hr->quotient;
    hr->distance[ch] += hr->remainder;

    test();
    if( sub(hr->distance[ch], hr->L) >= 0 ) {
      hr->distance[ch] -= hr->L;
      inIndex          += 1;
    }

    /* write as many output samples as possible */
    samplesOut = min( sub(inIndex,outIndex), numTmpOutSamples );

    for ( i=0; i<samplesOut; i++ ) {
      ioBuffer[outIndex++] = tmpOutSamples[i];                  move16();
    }

    for ( k=0; k<numTmpOutSamples-samplesOut; k++) {
      tmpOutSamples[k] = tmpOutSamples[samplesOut+k];           move16();
    }

    numTmpOutSamples = sub (numTmpOutSamples, samplesOut);

  }


  /* now we can work directly on the i/o buffer */
  test();
  while( sub( add(inIndex,3), inSamples) < 0 ) 
  {
    tmp     = hr->invL * hr->distance[ch];                      fixmul_32x16b(0,0); /* Note: this is a fract by int multiplication, counting operations */
    alpha   = extract_h(tmp);
    tmp_2   = fixmul_32x16b(tmp, alpha);
    alpha_2 = extract_h(tmp_2);
    alpha_3 = extract_h(fixmul_32x16b(tmp, alpha_2));
  
    pos = &ioBuffer[inIndex];

    coeff = calcCoeff1(alpha, alpha_2, alpha_3);
    accu  = L_mult(coeff, shr(*pos++,1));

    coeff = calcCoeff2(alpha_2, alpha_3);
    accu  = L_mac(accu, coeff, shr(*pos++,1));
  
    coeff = calcCoeff3(alpha, alpha_2, alpha_3);
    accu  = L_mac(accu, coeff, shr(*pos++,1));
  
    coeff = calcCoeff4(alpha_3);
    accu  = L_mac(accu, coeff, shr(*pos++,1));

    /* Update variables */
    inIndex          += hr->quotient;
    hr->distance[ch] += hr->remainder;

    test();
    if( sub(hr->distance[ch], hr->L) >= 0 ) {
      hr->distance[ch] -= hr->L;
      inIndex      += 1;
    }

    assert(outIndex < inIndex); /* make sure that we can work inplace */

    ioBuffer[outIndex++] = etsiopround( L_shl(accu,1) );        move16();

    assert(outIndex <= inSamples);
  }

  *outSamples = outIndex;                                       move16();

  hr->position[ch] = inIndex - (inSamples-3);

  test();
  if (hr->position[ch] < 0) {
    assert (hr->position[ch] >= 0);
  }

  
  /* update buffers */
  test();
  if ( sub(inSamples, 3) > 0 ) {

    for (i=0; i<3; i++) {
      hr->oldSamples[i][ch] = ioBuffer[inSamples-3+i];          move16();
    }
  }


  /* 
    Do the IIR filtering 
    iirFilterCoeff_a and iirFilterCoeff_b are scaled by 0.5
  */
  
  ioBuffer[0] = etsiopround( L_shl(L_sub(fixmul_32x16b(hr->iirFilterCoeff_b, ioBuffer[0]), fixmul_32x16b(hr->iirFilterCoeff_a, hr->oldSampleFilter[ch])),1) ); move16();

  for(i=1; i < outIndex; i++){
    ioBuffer[i] = etsiopround( L_shl(L_sub(fixmul_32x16b(hr->iirFilterCoeff_b, ioBuffer[i]), fixmul_32x16b(hr->iirFilterCoeff_a, ioBuffer[i - 1])),1) ); move16();
  }

  hr->oldSampleFilter[ch] = ioBuffer[outIndex - 1];             move16();

}
