/*
   frequency scale calculation
 */
#include <math.h> 
#include <string.h>
#include <assert.h>
#include "ffr.h"
#include "sbr_rom.h"
#include "sbr_const.h"
#include "env_extr.h"
#include "freq_sca.h"
#include "intrinsics.h"
#include "count.h"


#define MAX_OCTAVE         29
#define MAX_SECOND_REGION  50


static Word16  numberOfBands(Word16 bpo_div16, Word16 start, Word16 stop, Word16 warpFlag);
static void CalcBands(Word16 * diff, Word16 start, Word16 stop, Word16 num_bands);
static Word16 modifyBands(Word16 max_band, Word16 * diff, Word16 length);
static void cumSum(Word16 start_value, Word16 *diff, Word16 length, Word16 *start_adress);


/*!
  \brief     Retrieve QMF-band where the SBR range starts

  \return  Number of start band
*/
static Word16
getStartBand(Word32 fs,         /*!< Output sampling frequency */
             Word16 startFreq)  /*!< Index to table of possible start bands */
{
  Word16 band;

  test();
  switch(fs) {
    case 44100:
      test();
      logic16(); logic16(); /* Word8 read access */
      band = sbr_start_freq_44[startFreq];                      move16();
      break;
    case 48000:
      test();test();
      logic16(); logic16(); /* Word8 read access */
      band = sbr_start_freq_48[startFreq];                      move16();
      break;
    case 32000:
      test();test();test();
      logic16(); logic16(); /* Word8 read access */
      band = sbr_start_freq_32[startFreq];                      move16();
      break;
    case 24000:
      test();test();test();test();
      logic16(); logic16(); /* Word8 read access */
      band = sbr_start_freq_24[startFreq];                      move16();
      break;
    case 22050:
      test();test();test();test();test();
      logic16(); logic16(); /* Word8 read access */
      band = sbr_start_freq_22[startFreq];                      move16();
      break;
    case 16000:
      test();test();test();test();test();test();
      logic16(); logic16(); /* Word8 read access */
      band = sbr_start_freq_16[startFreq];                      move16();
      break;
    default:
      test();test();test();test();test();test();
      band = -1;                                                move16();
  }

  return band;
}


/*!
  \brief     Generates master frequency tables

  \return  errorCode, 0 if successful
*/
Word16
sbrdecUpdateFreqScale(Word16 * v_k_master,    /*!< Master table to be created */
                      Word16 *numMaster,      /*!< Number of entries in master table */
                      SBR_HEADER_DATA * hHeaderData) /*!< Control data from bitstream */
{
  Word16          i;
  Word32          fs = hHeaderData->outSampleRate;
  Word16          bpo_div16;    /* bands_per_octave divided by 16 */
  Word16          k0, k2, k1;
  Word16          k2_achived;
  Word16          k2_diff;
  Word16          incr;
  Word16          dk;
  Word16          num_bands0;
  Word16          num_bands1;
  Word16          diff_tot[MAX_OCTAVE + MAX_SECOND_REGION];
  Word16          *diff0 = &diff_tot[0];
  Word16          *diff1 = &diff_tot[MAX_OCTAVE];

  move16(); /* init fs */
  move16(); /* init diff0 */
  move16(); /* init diff1 */

  k1 = 0;                                                       move16();
  incr = 0;                                                     move16();
  dk = 0;                                                       move16();
  
  /*
    Determine start band
  */
  k0 = getStartBand(fs, hHeaderData->startFreq);


  /*
    Determine stop band
  */
  test();
  if(sub(hHeaderData->stopFreq,14) < 0) {
    switch(fs) {
    case 44100:
      test();
      k1 = 23;  /* int(1024000/fs + 0.5) */                     move16();
      break;
    case 48000:
      test();test();
      k1 = 21;  /* int(1024000/fs + 0.5) */                     move16();
      break;
    case 32000:
    case 24000:
      test();test();test();test();
      k1 = 32;                                                  move16();
      break;
    case 22050:
      test();test();test();test();test();
      k1 = 35;  /* int(768000/fs + 0.5) */                      move16();
      break;
    case 16000:
      test();test();test();test();test();test();
      k1 = 48;  /* int(768000/fs + 0.5) */                      move16();
      break;
    default:
      return -1;
    }

    /*
      Choose a stop band between k1 and 64 depending on stopFreq (0..13),
      based on a logarithmic scale.
      The vectors diff0 and diff1 are used temporarily here.
    */
    CalcBands( diff0, k1, 64, 13 );
    shellsort( diff0, 13 );
    cumSum(k1, diff0, 13, diff1);
    k2 = diff1[hHeaderData->stopFreq];                          move16();
  }
  else {
    test();
    if(sub(hHeaderData->stopFreq,14) == 0)
      k2=shl(k0,1); /* 2*k0 */
    else
      k2=add(shl(k0,1), k0); /* 3*k0 */
  }
  
  /* Limit to Nyquist */
  test();
  if (sub(k2, NO_SYNTHESIS_CHANNELS) > 0) {
    k2 = NO_SYNTHESIS_CHANNELS;                                 move16();
  }
  

  /* Range checks */
  test(); test();
  if ( (sub(sub(k2,k0), MAX_FREQ_COEFFS) > 0) || (sub(k2,k0) <= 0) ) {
    return -1;
  }

  test(); test();
  if ((L_sub(fs,44100)==0) && ( sub(sub(k2,k0), MAX_FREQ_COEFFS_FS44100)>0 )) {
    return -1;
  }
  test(); test();
  if ((L_sub(fs,48000)>=0) && ( sub(sub(k2,k0), MAX_FREQ_COEFFS_FS48000)>0 )) {
    return -1;
  }

  test();
  if(hHeaderData->freqScale>0) { /* Bark */

    test();
    if(sub(hHeaderData->freqScale,1)==0) {
      bpo_div16 = 0x6000;                          move16();
    }
    else {
      test();
      if(sub(hHeaderData->freqScale,2)==0) {
        bpo_div16 = 0x5000;                        move16();
      }
      else {
        bpo_div16 = 0x4000;                        move16();
      }
    }


    test();
    if( L_sub(L_mult(1000,k2), L_mult(2245, k0)) > 0 ) { /* Two or more regions */
      Word16 num_bands0m1;
      k1 = shl(k0, 1);
          
      num_bands0 = numberOfBands(bpo_div16, k0, k1, 0);
      num_bands1 = numberOfBands(bpo_div16, k1, k2, hHeaderData->alterScale );
      num_bands0m1 = sub(num_bands0,1);
      test();
      if ( num_bands0m1 < 0 ) {
        return -1;
      }
      test();
      if ( sub(num_bands1,1) < 0 ) {
        return -1;
      }
          
      CalcBands(diff0, k0, k1, num_bands0);
      shellsort( diff0, num_bands0);

      test();
      if (diff0[0] == 0) {
        return -1;
      }

      cumSum(k0, diff0, num_bands0, v_k_master);
          
      CalcBands(diff1, k1, k2, num_bands1);     
      shellsort( diff1, num_bands1);                          
      test();
      if(sub(diff0[num_bands0m1], diff1[0]) > 0) {
        Word16 err = modifyBands(diff0[num_bands0m1], diff1, num_bands1);
        test();
        if (err)
          return -1;
      }
          
      /* Add 2nd region */
      cumSum(k1, diff1, num_bands1, &v_k_master[num_bands0]);
      *numMaster = add(num_bands0, num_bands1);     /* Output nr of bands */  move16();
          
    }
    else { /* Only one region */
      k1=k2;                                                    move16();
          
      num_bands0 = numberOfBands(bpo_div16, k0, k1, 0);
      test();
      if ( sub(num_bands0,1) < 0) {
        return -1;
      }
      CalcBands(diff0, k0, k1, num_bands0);
      shellsort(diff0, num_bands0);
      test();
      if (diff0[0] == 0) {
        return -1;
      }

      cumSum(k0, diff0, num_bands0, v_k_master);
      *numMaster = num_bands0;        /* Output nr of bands */  move16();
          
    }
  }
  else { /* Linear mode */
    test();
    if (hHeaderData->alterScale==0) {
      dk = 1;                                                 move16();
      /* FLOOR to get to few number of bands (next lower even number) */
      num_bands0 = sub(k2, k0) & 254;                         logic16();
    } else {
      dk = 2;                                                 move16();
      num_bands0 = ( add(shr(sub(k2,k0),1),1) ) & 254; /* ROUND to the closest fit */ logic16();
    }

    test();
    if (sub(num_bands0,1) < 0) {
      return -1;
      /* We must return already here because 'i' can become negative below. */
    }

    k2_achived = add(k0, num_bands0);
    test();
    if (sub(dk,2) == 0) {
      k2_achived = add(k2_achived, num_bands0);
    }
    k2_diff = sub(k2, k2_achived);

    for (i=0; i<num_bands0; i++) {
      diff_tot[i] = dk;                                       move16();
    }

    /* If linear scale wasn't achieved */
    /* and we got too wide SBR area */
    test();
    if (k2_diff < 0) {
      incr = 1;                                             move16();
      i = 0;                                                move16();
    }

    /* If linear scale wasn't achieved */
    /* and we got too small SBR area */
    test();
    if (k2_diff > 0) {
      incr = -1;                                            move16();
      i = sub(num_bands0,1);
    }

    /* Adjust diff vector to get spec. SBR range */
                                                                test();
    while (k2_diff != 0) {
      diff_tot[i] = sub(diff_tot[i], incr);
      i += incr;
      k2_diff = add(k2_diff, incr);
      /* end of while */                                        test();
    }

    cumSum(k0, diff_tot, num_bands0, v_k_master);/* cumsum */
    *numMaster = num_bands0;  /* Output nr of bands */          move16();
  }

  test();
  if (sub(*numMaster,1) < 0) {
    return -1;
  }



  return 0;
}


/*!
  \brief     Calculate frequency ratio of one SBR band

 \return    num_band-th root of k_start/k_stop
*/
static Word16 calcFactorPerBand(Word16 k_start, Word16 k_stop, Word16 num_bands)
{
  Word32 bandfactor;
  Word32 step;
  Word16 direction;
  Word32 start;
  Word32 stop;
  Word32 temp;
  Word16 j, i;


  bandfactor = 0x3f000000L; /* Start value */                   move32();
  step = 0x20000000L;      /* Initial increment for factor */   move32();
  direction = 1;                                                move16();
  start = L_shl(L_deposit_l(k_start), INT_BITS-8);
  stop =  L_shl(L_deposit_l(k_stop),  INT_BITS-8);

  i = 0;                                                        move16();
  test();
  while ( step > 0) {                                           test();
    i = add(i, 1);
    temp = stop;                                                move32();

    /* Calculate temp^num_bands: */
    assert(num_bands > 0);
    for (j=0; j<num_bands; j++)
      temp = L_mult(extract_h(temp), extract_h(bandfactor));

    test();
    if (L_sub(temp,start) < 0) { /* Factor too strong, make it weaker */
      test();
      if (direction == 0)
        step = L_shr(step, 1);
      direction = 1;                                            move16();
      bandfactor = L_add(bandfactor, step);

    }
    else {  /* Factor is too weak: make it stronger */
      test();
      if (direction == 1)
        step = L_shr(step, 1);
      direction = 0;                                            move16();
      bandfactor = L_sub(bandfactor, step);
    }

    test();
    if (sub(i,100) > 0) {
      step = 0;                                                 move32();
    }
  }
  return extract_h(bandfactor);
}


/*!
  \brief     Calculate number of SBR bands between start and stop band

  \return    number of bands
*/
static Word16
numberOfBands(Word16 bpo_div16, /*!< Input: number of bands per octave divided by 16 */
              Word16 start,     /*!< First QMF band of SBR frequency range */
              Word16 stop,      /*!< Last QMF band of SBR frequency range + 1 */
              Word16 warpFlag)  /*!< Stretching flag */
{
  Word16  num_bands_div128;
  Word16  num_bands;

  num_bands_div128 = mult(ffr_getNumOctavesDiv8(start,stop), bpo_div16);

  test();
  if (warpFlag) {
    /* Apply the warp factor of 1.3 to get wider bands.  We use a value
       of 32768/25200 instead of the exact value to avoid critical cases
       of rounding.
    */
    num_bands_div128 = mult(num_bands_div128, 0x6270);
  }

  /* add scaled 1 for rounding to even numbers: */
  num_bands_div128 = add(num_bands_div128, 0x0100);
  /* scale back to right aligned integer and double the value: */
  num_bands = shl(shr(num_bands_div128, SHORT_BITS-7), 1);
 
  return(num_bands);
}


/*!
  \brief     Calculate width of SBR bands
*/
static void
CalcBands(Word16 * diff,    /*!< Vector of widths to be calculated */
          Word16 start,     /*!< Lower end of subband range */
          Word16 stop,      /*!< Upper end of subband range */
          Word16 num_bands) /*!< Desired number of bands */
{
  Word16 i;
  Word16 previous;
  Word16 current;
  Word32 temp, exact;
  Word16 bandfactor = calcFactorPerBand(start, stop, num_bands);


  previous = stop; /* Start with highest QMF channel */
  exact = L_shl(L_deposit_l(stop), INT_BITS-8); /* Shift left to gain some accuracy */

  for(i=sub(num_bands,1); i>=0; i--) {
    /* Calculate border of next lower sbr band */
    exact = L_mult(extract_h(exact), bandfactor);

    /* Add scaled 0.5 for rounding: */
    temp = L_add(exact, 0x00800000);

    /* scale back to right alinged integer: */
    current = extract_l(L_shr(temp, (INT_BITS-8)));

    /* Save width of band i */
    diff[i] = sub(previous, current);
    previous = current;                                         move16();
  }
}


/*!
  \brief     Calculate cumulated sum vector from delta vector
*/
static void 
cumSum(Word16 start_value, Word16* diff, Word16 length, Word16 *start_adress)
{
  Word16 i;
  start_adress[0]=start_value;                                  move16();

  assert(length > 0);
  for(i=1; i<=length; i++)
    start_adress[i] = add(start_adress[i-1], diff[i-1]);        move16();
}


/*!
  \brief     Adapt width of frequency bands in the second region
*/
static Word16
modifyBands(Word16 max_band_previous, Word16 * diff, Word16 length)
{
  Word16 change = sub(max_band_previous, diff[0]);
  Word16 change_max = shr(sub(diff[sub(length,1)], diff[0]), 1);
  /* Limit the change so that the last band cannot get narrower than the first one */
  test();
  if ( sub(change, change_max) > 0 ) {
    change = change_max;                                        move16();
  }

  diff[0] = add(diff[0], change);                               move16();
  diff[sub(length,1)] = sub(diff[sub(length,1)], change);       move16();
  shellsort(diff, length);
  
  return 0;
}


/*!
  \brief   Update high resolution frequency band table
*/
void
sbrdecUpdateHiRes(Word16 * h_hires,
                  Word16 * num_hires,
                  Word16 * v_k_master,
                  Word16 num_bands,
                  Word16 xover_band)
{
  Word16 i;
  
  *num_hires = sub(num_bands, xover_band);                      move16();
  
  for(i=xover_band; i<=num_bands; i++) {
    h_hires[sub(i, xover_band)] = v_k_master[i];                move16();
  } 
}


/*!
  \brief  Build low resolution table out of high resolution table
*/
void                    
sbrdecUpdateLoRes(Word16 * h_lores,
                  Word16 * num_lores,
                  Word16 * h_hires,
                  Word16 num_hires)
{
  Word16 i, j;
  
  logic16(); test();
  if( (num_hires & 1) == 0) {
    /* If even number of hires bands */
    *num_lores = shr(num_hires, 1);                             move16();
    /* Use every second lores=hires[0,2,4...] */
    j = 0;                                                      move16();
    for(i=0; i<=*num_lores; i++, j+=2) {
      h_lores[i] = h_hires[j];  /* h_hires[2*i] */              move16();
    }
  }
  else {
    /* Odd number of hires, which means xover is odd */
    *num_lores = shr(add(num_hires, 1), 1);                     move16();
    /* Use lores=hires[0,1,3,5 ...] */
    h_lores[0] = h_hires[0];                                    move16();

    assert(*num_lores > 0);
    j = 1;                                                      move16();
    for(i=1; i<=*num_lores; i++, j+=2) {
      h_lores[i] = h_hires[j]; /* h_hires[2*i-1] */             move16();
    }
  }
}


/*!
  \brief   Derive a low-resolution frequency-table from the master frequency table
*/
void 
sbrdecDownSampleLoRes(Word16 *v_result,
                      Word16 num_result,
                      Word16 *freqBandTableRef,
                      Word16 num_Ref)
{
  Word16 step;
  Word16 i,j;
  Word16 org_length,result_length;
  Word16 v_index[MAX_FREQ_COEFFS/2];
  
  /* init */
  org_length = num_Ref;                                         move16();
  result_length = num_result;                                   move16();
  
  v_index[0] = 0;   /* Always use left border */                move16();
  i=0;                                                          move16();
  while(org_length > 0) {                                       test();
    /* Create downsample vector */
    i += 1;
    step = (Word16) ffr_divideWord32(org_length, result_length);
    org_length = sub(org_length, step);
    result_length = sub(result_length, 1);
    v_index[i] = add(v_index[i-1], step);                  move16();
  }
  
  for(j=0;j<=i;j++) {
    /* Use downsample vector to index LoResolution vector */
    v_result[j]=freqBandTableRef[v_index[j]];                   move16();
  }
  
}


/*!
  \brief   Sorting routine
*/
void shellsort(Word16 *in, Word16 n)
{

  Word16 i, j;
  Word16 inc;
  Word16 v, w;

  inc = 1;                                                      move16();

  do {
    inc = add(add(shl(inc,1),inc), 1);
                                                                test();
  } while (sub(inc,n) <= 0);

  do {
    inc = extract_l(ffr_divideWord32(inc, 3));
    for (i = inc; i < n; i++) {
      v = in[i];                                                move16();
      j = i;                                                    move16();
                                                                test(); move16();
      while (sub((w=in[sub(j,inc)]), v) > 0) {
        in[j] = w;                                              move16();
        j = sub(j, inc);
        test();
        if (sub(j, inc) < 0) break;
        /* end of while */                                      test(); move16();
      }
      in[j] = v;                                                move16();
    }
                                                                test();
  } while (sub(inc,1) > 0);

}



/*!
  \brief   Reset frequency band tables
  \return  errorCode, 0 if successful
*/
Word16
resetFreqBandTables(HANDLE_SBR_HEADER_DATA hHeaderData)
{
  Word16 err;
  Word16 k2,kx;
  Word16 intTemp;
  Word16 nBandsLo, nBandsHi, lsb, usb;
  HANDLE_FREQ_BAND_DATA hFreq = hHeaderData->hFreqBandData;

  /* Calculate master frequency function */
  err = sbrdecUpdateFreqScale(hFreq->v_k_master,
                              &hFreq->numMaster,
                              hHeaderData);

  test(); test();
  if ( err || (sub(hHeaderData->xover_band, hFreq->numMaster) > 0) ) {
    return -1;
  }

  /* Derive Hiresolution from master frequency function */
  sbrdecUpdateHiRes(hFreq->freqBandTable[HI], &nBandsHi, hFreq->v_k_master, hFreq->numMaster, hHeaderData->xover_band );
  /* Derive Loresolution from Hiresolution */
  sbrdecUpdateLoRes(hFreq->freqBandTable[LO], &nBandsLo, hFreq->freqBandTable[HI], nBandsHi);


  hFreq->nSfb[LO] = nBandsLo;                                   move16();
  hFreq->nSfb[HI] = nBandsHi;                                   move16();

  /* Check index to freqBandTable[LOW_RES] */
  test(); test();
  if ( (nBandsLo <= 0) || (sub(nBandsLo, shr(MAX_FREQ_COEFFS,1)) > 0) ) {
    return -1;
  }

  lsb = hFreq->freqBandTable[LOW_RES][0];                       move16();
  usb = hFreq->freqBandTable[LOW_RES][nBandsLo];                move16();

  /* Additional check for lsb */
  test(); test();
  if ( (sub(lsb, NO_ANALYSIS_CHANNELS) > 0) || (sub(lsb, usb) >= 0) )
  {
    return -1;
  }


  /* Calculate number of noise bands */

  k2 = hFreq->freqBandTable[HI][nBandsHi];                      move16();
  kx = hFreq->freqBandTable[HI][0];                             move16();

  test();
  if (hHeaderData->noise_bands == 0)
  {
    hFreq->nNfb = 1;                                            move16();
  }
  else /* Calculate no of noise bands 1,2 or 3 bands/octave */
  {
    /* Fetch number of octaves divided by 32 */
    intTemp = shr(ffr_getNumOctavesDiv8(kx,k2), 2);

    /* Integer-Multiplication with number of bands: */
    /* Add scaled 0.5 for rounding: */
    /*intTemp =  0x0200 + intTemp * hHeaderData->noise_bands; */
    intTemp = shr(extract_l(L_mac(0x00000200<<1,intTemp, hHeaderData->noise_bands)),1);

    /* Convert to right-aligned integer: */
    intTemp = shr(intTemp, SHORT_BITS-1/*sign*/-5/* rescale */);

    /* Compare with float calculation */
    assert( intTemp ==  (Word32)((hHeaderData->noise_bands * log( (float)k2/kx) / (float)(log(2.0)))+0.5) );
    test();
    if( intTemp==0) {
      intTemp=1;                                                move16();
    }

    hFreq->nNfb = intTemp;                                      move16();
  }

  hFreq->nInvfBands = hFreq->nNfb;                              move16();

  test();
  if( sub(hFreq->nNfb, MAX_NOISE_COEFFS) > 0 ) {
    return -1;
  }

  /* Get noise bands */
  sbrdecDownSampleLoRes(hFreq->freqBandTableNoise, 
                        hFreq->nNfb,
                        hFreq->freqBandTable[LO],
                        nBandsLo);




  hFreq->lowSubband  = lsb;                                     move16();
  hFreq->highSubband = usb;                                     move16();

  return 0;
}
