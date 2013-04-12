/*
   sbr constants
 */

#ifndef __SBR_CONST_H
#define __SBR_CONST_H


#define SBR_AMP_RES_1_5         0
#define SBR_AMP_RES_3_0         1
#define NOISE_FLOOR_OFFSET      6

#define LOW_RES                 0
#define HIGH_RES                1

#define LO                        0
#define HI                        1

#define TIME                      1
#define FREQ                      0

#define SI_SBR_PROTOCOL_VERSION_ID              0


#define SI_SBR_CRC_BITS               10


#define SBR_FREQ_SCALE_DEFAULT                  2
#define SBR_ALTER_SCALE_DEFAULT                 1
#define SBR_NOISE_BANDS_DEFAULT                 2

#define SBR_LIMITER_BANDS_DEFAULT               2
#define SBR_LIMITER_GAINS_DEFAULT               2
#define SBR_INTERPOL_FREQ_DEFAULT               1
#define SBR_SMOOTHING_LENGTH_DEFAULT            1  /* 0: on  1: off */



/* header */
#define SI_SBR_AMP_RES_BITS                     1
#define SI_SBR_START_FREQ_BITS                  4
#define SI_SBR_STOP_FREQ_BITS                   4
#define SI_SBR_XOVER_BAND_BITS                  3
#define SI_SBR_DATA_EXTRA_BITS                  1
#define SI_SBR_HEADER_EXTRA_1_BITS              1
#define SI_SBR_HEADER_EXTRA_2_BITS              1

#define SI_SBR_PSEUDO_STEREO_MODE_BITS          2

#define SI_SBR_FREQ_SCALE_BITS                  2
#define SI_SBR_ALTER_SCALE_BITS                 1
#define SI_SBR_NOISE_BANDS_BITS                 2

#define SI_SBR_LIMITER_BANDS_BITS               2
#define SI_SBR_LIMITER_GAINS_BITS               2
#define SI_SBR_INTERPOL_FREQ_BITS               1
#define SI_SBR_SMOOTHING_LENGTH_BITS            1
#define SI_SBR_RESERVED_HE2_BITS                1
#define SI_SBR_RESERVED_BITS_HDR                2
#define SI_SBR_RESERVED_BITS_DATA               4

/* data */
#define SI_SBR_SR_MODE_BITS                     1

#define SI_SBR_ENABLE_PSEUDOSTEREO_BITS         1

#define SI_SBR_COUPLING_BITS                    1

#define SI_SBR_INVF_MODE_BITS                   2
#define SI_SBR_XPOS_MODE_BITS                   2
#define SI_SBR_XPOS_CTRL_BITS                   3

#define SI_SBR_EXTENDED_DATA_BITS               1
#define SI_SBR_EXTENSION_SIZE_BITS              4
#define SI_SBR_EXTENSION_ESC_COUNT_BITS         8
#define SI_SBR_EXTENSION_ID_BITS                2

#define SI_SBR_DOMAIN_BITS                      1

#define SI_SBR_START_ENV_BITS_AMP_RES_3_0           6
#define SI_SBR_START_ENV_BITS_BALANCE_AMP_RES_3_0   5
#define SI_SBR_START_NOISE_BITS_AMP_RES_3_0         5
#define SI_SBR_START_NOISE_BITS_BALANCE_AMP_RES_3_0 5

#define SI_SBR_START_ENV_BITS_AMP_RES_1_5           7
#define SI_SBR_START_ENV_BITS_BALANCE_AMP_RES_1_5   6 

#define SI_SBR_ADDITIONAL_HARMONICS_BITS        1


/* Grid control */
#define SBR_CLA_BITS  2
#define SBR_ABS_BITS  2
#define SBR_RES_BITS  1
#define SBR_REL_BITS  2
#define SBR_ENV_BITS  2
#define SBR_NUM_BITS  2

#define FIXFIX  0
#define FIXVAR  1
#define VARFIX  2
#define VARVAR  3

#define    LEN_NIBBLE   (4)


#endif
