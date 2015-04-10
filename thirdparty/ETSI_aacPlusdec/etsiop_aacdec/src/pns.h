/*
   perceptual noise substitution tool
 */

#ifndef PNS_H
#define PNS_H

#include "ffr.h"
#include "channelinfo.h"


#define PNS_BAND_FLAGS_SIZE              16  /* (short-window) max. scalefactors * max. groups / sizeof(char) = 16 * 8 / 8 */
#define PNS_BAND_FLAGS_MASK              ((Word16)(( ((Word16)1) << PNS_BAND_FLAGS_SHIFT) - 1))
#define PNS_BAND_FLAGS_SHIFT             3

#define PNS_SCALE_MANT_TAB_SIZE          4
#define PNS_SCALE_MANT_TAB_MASK          (PNS_SCALE_MANT_TAB_SIZE - 1)
#define PNS_SCALE_MANT_TAB_SCALING       -4

#define PNS_SCALEFACTOR_SCALING          2

#define PNS_SPEC_SCALE                   3

typedef struct {
  UWord16 correlated[PNS_BAND_FLAGS_SIZE];
  Word16 randomState[PNS_BAND_FLAGS_SIZE * 8];
} CPnsInterChannelData;

typedef struct {
  Word16 current_seed;
  Word16 pns_frame_number;
} CPnsStaticInterChannelData;

typedef struct {
  UWord16 pnsUsed[PNS_BAND_FLAGS_SIZE];
  Word16 CurrentEnergy;
  UWord8 PnsActive;
} CPnsData;


#endif /* #ifndef PNS_H */
