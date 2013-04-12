/*
   pulse data tool
 */

#include "block.h"
#include "FFR_bitbuffer.h"
#include "count.h"

/*!
  \brief Read pulse data from bitstream

  The function reads the elements for pulse data from
  the bitstream.

  \return  none
*/
void CPulseData_Read(HANDLE_BIT_BUF bs,     /*!< pointer to bitstream */
                     CPulseData *PulseData) /*!< pointer to pulse data side info */
{
  int i;

                                                                            move16(); test();
 if ((PulseData->PulseDataPresent = (Flag) ReadBits(bs,1)))
  {
    PulseData->NumberPulse         = (Word16) ReadBits(bs,2);
    PulseData->PulseStartBand      = (Word16) ReadBits(bs,6);

    move16(); /*PulseData->NumberPulse*/
    for (i=0; i<=PulseData->NumberPulse; i++)
    {
      PulseData->PulseOffset[i] = (Word16) ReadBits(bs,5);
      PulseData->PulseAmp[i]    = (Word16) ReadBits(bs,4);
    }
  }
}

/*!
  \brief Apply pulse data to spectral lines

  The function applies the pulse data to the
  specified spectral lines.

  \return  none
*/
void CPulseData_Apply(CPulseData *PulseData,                 /*!< pointer to pulse data side info */
                      const Word16 *pScaleFactorBandOffsets, /*!< pointer to scalefactor band offsets */
                      Word16       *coef)                    /*!< pointer to spectrum */
{
  Word16 i, k;

                                                                            test();
  if (PulseData->PulseDataPresent)
  {
    k = pScaleFactorBandOffsets[PulseData->PulseStartBand];                 move16();
  
    move16(); /*PulseData->NumberPulse*/
    for (i=0; i<=PulseData->NumberPulse; i++)
    {
      k = add(k, PulseData->PulseOffset[i]);
      test();
      if (coef [k] > 0) coef[k] = add(coef[k], PulseData->PulseAmp[i]);
      else              coef[k] = sub(coef[k], PulseData->PulseAmp[i]);
    }
  }
}
