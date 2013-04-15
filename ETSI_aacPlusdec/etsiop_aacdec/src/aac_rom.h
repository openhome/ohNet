/*
   definition of constant tables
 */

#ifndef AAC_ROM_H
#define AAC_ROM_H

#include "defines.h"
#include "typedef.h"


#define AAC_NF_NO_RANDOM_VAL  512   /*!< Size of random number array for noise floor */

extern const Word16 OnlyLongWindowSine[1024];
extern const Word16 OnlyShortWindowSine[128];
extern const Word16 OnlyLongWindowKBD[1024];
extern const Word16 OnlyShortWindowKBD[128];

extern const Word32  InverseQuantTable[POW_TAB_SIZE+1];
extern const Word32  specExpMantTableComb[4][14];
extern const Word8   specExpTableComb[4][14];

extern const Word16 trigData[513];

extern const SamplingRateInfo SamplingRateInfoTable[16];

extern const CodeBookDescription HuffmanCodeBooks[13];


extern const Word8 tns_max_bands_tbl[12][4];
extern const Word16 tnsCoeff3[8];
extern const Word16 tnsCoeff4[16];
extern const Word16  sgn_mask[3];
extern const Word16  neg_mask[3];


#endif /* #ifndef AAC_ROM_H */
