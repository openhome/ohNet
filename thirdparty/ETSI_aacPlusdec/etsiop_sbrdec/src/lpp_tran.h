/*
   transposer
*/

#ifndef _LPP_TRANS_H
#define _LPP_TRANS_H



#include "ffr.h"
#include "sbr_scale.h"
#include "sbrdecsettings.h"


#define MAX_NUM_PATCHES 6
#define GUARDBANDS      0              /*!< number of guardbands between every patch */
#define SHIFT_START_SB  1              /*!< lowest subband of source range */

typedef enum
{
  INVF_OFF = 0,
  INVF_LOW_LEVEL,
  INVF_MID_LEVEL,
  INVF_HIGH_LEVEL,
  INVF_SWITCHED /* not a real choice but used here to control behaviour */
}
INVF_MODE;



/** parameter set for one single patch */
typedef struct {
  Word16  sourceStartBand;   /*!< first band in lowbands where to take the samples from */ 
  Word16  sourceStopBand;    /*!< first band in lowbands which is not included in the patch anymore */
  Word16  guardStartBand;    /*!< first band in highbands to be filled with zeros in order to
                      reduce interferences between patches */
  Word16  targetStartBand;   /*!< first band in highbands to be filled with whitened lowband signal */
  Word16  targetBandOffs;    /*!< difference between 'startTargetBand' and 'startSourceBand' */
  Word16  numBandsInPatch;   /*!< number of consecutive bands in this one patch */
} PATCH_PARAM;


/*! The transposer settings are calculated on a header reset and are shared by both channels. */
typedef struct {
  Word16  nCols;                       /*!< number subsamples of a codec frame */
  Word16  noOfPatches;                 /*!< number of patches */
  Word16  lbStartPatching;             /*!< first band of lowbands that will be patched */
  Word16  lbStopPatching;              /*!< first band that won't be patched anymore*/
  Word16  bwBorders[MAX_NUM_NOISE_VALUES];
  PATCH_PARAM    patchParam[MAX_NUM_PATCHES]; /*!< new parameter set for patching */
} TRANSPOSER_SETTINGS;


typedef struct
{
  TRANSPOSER_SETTINGS *pSettings;
  Word32    bwVectorOld[MAX_NUM_PATCHES];    /*!< pole moving factors of past frame */
  Word32   *lpcFilterStatesReal[LPC_ORDER];  /*!< pointer array to save filter states */
#ifndef LP_SBR_ONLY
  Word32   *lpcFilterStatesImag[LPC_ORDER];  /*!< pointer array to save filter states */
#endif
} 
SBR_LPP_TRANS;

typedef SBR_LPP_TRANS *HANDLE_SBR_LPP_TRANS;


void lppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans,
                    SBR_SCALE_FACTOR  *sbrScaleFactor,
                    Word32 **qmfBufferReal,
#ifndef LP_SBR_ONLY
                    Word32 **qmfBufferImag,
#endif
                    Word16 *degreeAlias,
                    Word16 timeStep,            
                    Word16 firstSlotOffset,     
                    Word16 lastSlotOffset,     
                    Word16 nInvfBands,
                    Word16 maxQmfSubbandAac,
                    INVF_MODE *sbr_invf_mode,    
                    INVF_MODE *sbr_invf_mode_prev,
                    Flag bUseLP

                    );


Word16
createLppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans,
                     Word16 highBandStartSb,
                     Word16 *v_k_master,
                     Word16 numMaster,
                     Word16 usb,
                     Word16 nCols,
                     Word16* noiseBandTable,
                     Word16 noNoiseBands,
                     Word32 fs,
                     Word16  chan);
  

Word16
resetLppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans,
                    Word16 highBandStartSb,
                    Word16 *v_k_master,
                    Word16 numMaster,
                    Word16* noiseBandTable,
                    Word16 noNoiseBands,
                    Word16 usb,
                    Word32 fs);



#endif /* _LPP_TRANS_H */

