/*
   pulse data tool
 */

#ifndef PULSEDATA_H
#define PULSEDATA_H

#include "bitstream.h"
#include "FFR_bitbuffer.h"


enum
{
  MaximumLines = 4
};

typedef struct
{
  Flag  PulseDataPresent;
  Word16 NumberPulse;
  Word16 PulseStartBand;
  Word16 PulseOffset[MaximumLines];
  Word16 PulseAmp[MaximumLines];
} CPulseData;

void CPulseData_Read(HANDLE_BIT_BUF bs,
                     CPulseData *PulseData);

void CPulseData_Apply(CPulseData *PulseData,
                      const Word16 *pScaleFactorBandOffsets,
                      Word16 *coef);


#endif /* #ifndef PULSEDATA_H */
