/*
   global defines
 */

#ifndef __DEFINES_H
#define __DEFINES_H

#include "typedef.h"

/* TNS */
enum
{
  MaximumWindows = 8,
  MaximumBands = 49,
  MaximumOrder = 31,
  MaximumFilters = 3
};

typedef struct
{
  Word32        SamplingFrequency;
  Word16         NumberOfScaleFactorBands_Long;
  const Word16 *ScaleFactorBands_Long;
  Word16         NumberOfScaleFactorBands_Short;
  const Word16 *ScaleFactorBands_Short;
} SamplingRateInfo;

/* code books related */


enum
{
  MaximumBinsLong = 1024,
  MaximumBinsShort = 128,
  MaximumScaleFactorBandsLong = 64,
  MaximumScaleFactorBandsShort = 16,
  MaximumGroups = MaximumWindows,

  ZERO_HCB = 0,
  ESCBOOK  = 11,
  NSPECBOOKS = ESCBOOK + 1,
  BOOKSCL    = NSPECBOOKS,
  NOISE_HCB = 13,
  INTENSITY_HCB2 = 14,
  INTENSITY_HCB  = 15,

  LD_MANT=         12,
  MANT_SIZE=       4096,
  LD_POW_TAB=      8,
  POW_TAB_SIZE=    256,
  LD_DELTA=        4,
  DELTA_SIZE=      16,
  TNS_SCALE=        2,

  HuffmanBits = 2,
  HuffmanEntries = (1 << HuffmanBits)
};

typedef struct tagCodeBookDescription
{
  Word16 Dimension;
  Word16 numBits;
  Word16 Offset;
  const Word16 (*CodeBook)[HuffmanEntries];
} CodeBookDescription;

enum {
  Size01 = (MaximumBinsLong/16),
  Size02 = ( 2*Size01),
  Size03 = ( 3*Size01),
  Size04 = ( 4*Size01),
  Size05 = ( 5*Size01),
  Size06 = ( 6*Size01),
  Size07 = ( 7*Size01),
  Size08 = ( 8*Size01),
  Size09 = ( 9*Size01),
  Size10 = (10*Size01),
  Size11 = (11*Size01),
  Size12 = (12*Size01),
  Size13 = (13*Size01),
  Size14 = (14*Size01),
  Size15 = (15*Size01),
  Size16 = (16*Size01)
};

#endif
