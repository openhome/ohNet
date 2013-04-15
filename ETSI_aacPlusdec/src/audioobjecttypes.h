/*
   audio object types
 */

#ifndef __AUDIOOBJECTTYPES_H__
#define __AUDIOOBJECTTYPES_H__

typedef enum _AUDIO_OBJECT_TYPE
{
  AOT_NULL_OBJECT      = 0, 
  AOT_AAC_MAIN         = 1,
  AOT_AAC_LC           = 2,
  AOT_AAC_SSR          = 3,
  AOT_AAC_LTP          = 4,
  AOT_SBR              = 5,
  AOT_AAC_SCAL         = 6,
  AOT_TWIN_VQ          = 7,
  AOT_CELP             = 8,
  AOT_HVXC             = 9,
  AOT_RSVD_10          = 10, /* (reserved)                                */
  AOT_RSVD_11          = 11, /* (reserved)                                */
  /* not supported */
  AOT_TTSI         = 12, /* TTSI Object                               */
  AOT_MAIN_SYNTH       = 13, /* Main Synthetic Object                     */
  AOT_WAV_TAB_SYNTH    = 14, /* Wavetable Synthesis Object                */
  AOT_GEN_MIDI         = 15, /* General MIDI Object                       */
  AOT_ALG_SYNTH_AUD_FX = 16, /* Algorithmic Synthesis and Audio FX Object */
  AOT_ER_AAC_LC        = 17, /* Error Resilient(ER) AAC LC Object         */
  AOT_RSVD_18          = 18, /* (reserved)                                */
  AOT_ER_AAC_LTP       = 19, /* Error Resilient(ER) AAC LTP Object        */
  AOT_ER_AAC_SCAL      = 20, /* Error Resilient(ER) AAC Scalable Object   */
  AOT_ER_TWIN_VQ       = 21, /* Error Resilient(ER) TwinVQ Object         */
  AOT_ER_BSAC          = 22, /* Error Resilient(ER) BSAC Object           */
  AOT_ER_AAC_LD        = 23, /* Error Resilient(ER) AAC LD Object         */
  AOT_ER_CELP          = 24, /* Error Resilient(ER) CELP Object           */
  AOT_ER_HVXC          = 25, /* Error Resilient(ER) HVXC Object           */
  AOT_ER_HILN          = 26, /* Error Resilient(ER) HILN Object           */
  AOT_ER_PARA          = 27, /* Error Resilient(ER) Parametric Object     */
  AOT_RSVD_28          = 28, /* (reserved)                                */
  AOT_RSVD_29          = 29, /* (reserved)                                */
  AOT_RSVD_30          = 30, /* (reserved)                                */
  AOT_RSVD_31          = 31  /* (reserved)                                */

} AUDIO_OBJECT_TYPE;

#endif
