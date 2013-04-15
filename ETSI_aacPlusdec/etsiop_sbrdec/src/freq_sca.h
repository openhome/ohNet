/*
   frequency scale prototypes
 */
#ifndef __FREQ_SCA_H
#define __FREQ_SCA_H

#include "env_extr.h"



Word16
sbrdecUpdateFreqScale(Word16 * v_k_master,
                      Word16 *numMaster,
                      SBR_HEADER_DATA * headerData);

void sbrdecUpdateHiRes(Word16 * v_hires, Word16 *num_hires, Word16 * v_k_master, Word16 num_bands, Word16 xover_band);
void sbrdecUpdateLoRes(Word16 * v_lores, Word16 *num_lores, Word16 * v_hires, Word16 num_hires);

  
void sbrdecDownSampleLoRes(Word16 *v_result, Word16 num_result, 
                           Word16 *freqBandTableRef, Word16 num_Ref);

void shellsort(Word16 *in, Word16 n);

Word16
resetFreqBandTables(HANDLE_SBR_HEADER_DATA hHeaderData);


#endif
