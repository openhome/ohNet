/*  
   this module declares all static and dynamic memory spaces
 */

#include "sbrdecoder.h"
#include "sbr_ram.h"
#include "aac_ram.h"
#include "ffr.h"

extern Word32 WorkBufferCore[];

/*! Filter states for QMF-analysis. <br>
  Dimension: #MAXNRSBRCHANNELS * #QMF_FILTER_STATE_ANA_SIZE */

Word16 sbr_CodecQmfStatesAnalysis[MAXNRSBRCHANNELS * QMF_FILTER_STATE_ANA_SIZE];

/*! Filter states for QMF-synthesis.  <br>
  Dimension: #MAXNRSBRCHANNELS * #QMF_FILTER_STATE_SYN_SIZE */


Word16 sbr_QmfStatesSynthesis[MAXNRSBRCHANNELS * QMF_FILTER_STATE_SYN_SIZE];

/*! Filter states (real part) for LPC used in the LPP-transposer */
Word32 sbr_LpcFilterStatesReal[MAXNRSBRCHANNELS][LPC_ORDER][NO_ANALYSIS_CHANNELS];

#ifndef LP_SBR_ONLY
/*! Filter states (imaginary part) for LPC used in the LPP-transposer */
Word32 sbr_LpcFilterStatesImag[MAXNRSBRCHANNELS][LPC_ORDER][NO_ANALYSIS_CHANNELS];
#endif

/*! Transposer settings derived from the SBR-header */
TRANSPOSER_SETTINGS sbr_TransposerSettings;

/*! Gains (matissas) of last envelope, needed for smoothing.  <br>
  Dimension: #MAXNRSBRCHANNELS x #MAX_FREQ_COEFFS */
Word16 sbr_GainSmooth_m[MAXNRSBRCHANNELS][MAX_FREQ_COEFFS];

/*! Noise levels of last envelope, needed for smoothing.  <br>
  Dimension: #MAXNRSBRCHANNELS x #MAX_FREQ_COEFFS */
Word16 sbr_NoiseSmooth_m[MAXNRSBRCHANNELS][MAX_FREQ_COEFFS];

/*! Gains (exponents) of last envelope, needed for smoothing.  <br>
  Dimension: #MAXNRSBRCHANNELS x #MAX_FREQ_COEFFS */
Word16 sbr_GainSmooth_e[MAXNRSBRCHANNELS][MAX_FREQ_COEFFS];

/*! Frequency tables derived from the SBR-header */
FREQ_BAND_DATA FreqBandData;

/*! Delayed spectral data needed for the dynamic framing of SBR */
#ifdef LP_SBR_ONLY
Word32 sbr_OverlapBuffer[MAXNRSBRCHANNELS][MAX_OV_COLS * NO_SYNTHESIS_CHANNELS];
#else
Word32 sbr_OverlapBuffer[MAXNRSBRCHANNELS][2 * MAX_OV_COLS * NO_SYNTHESIS_CHANNELS];
#endif

/*! Some data from the previous frame needed for delta-coding over time
  and for concealment. */
SBR_PREV_FRAME_DATA PrevFrameData[MAXNRSBRCHANNELS];


/*!
  \name DynamicSbrData
*/

#ifdef LP_SBR_ONLY
Word32* WorkBuffer1 = WorkBufferCore;
#else
/* The work buffer #WorkBufferCore of the aac-core
  will be reused as #WorkBuffer2 in the SBR part. Minimum size of
  #WorkBufferCore must be #MAX_COLS * #NO_SYNTHESIS_CHANNELS.
  #WorkBuffer2 is the second half of the SBR work buffer. */
Word32 *WorkBuffer2 = WorkBufferCore;
Word32 WorkBuffer1[MAX_COLS*NO_SYNTHESIS_CHANNELS];
#endif

