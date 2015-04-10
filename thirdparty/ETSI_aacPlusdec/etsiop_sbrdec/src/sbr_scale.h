/*
   SBR scaling factors
 */

#ifndef __SBR_SCALE_H
#define __SBR_SCALE_H

#include "typedef.h"

typedef struct {
  Word16 lb_scale;        /*!< Scale of low band area           */         
  Word16 st_lb_scale;     /*!< Scale of analysis filter states  */
  Word16 ov_lb_scale;     /*!< Scale of lowband in overlap area */
  Word16 hb_scale;        /*!< Scale of high band area          */         
  Word16 ov_hb_scale;     /*!< Scale of adjusted overlap area   */
  Word16 st_syn_scale;    /*!< Scale of systhesis filter states */
#ifndef MONO_ONLY
  Word16 ps_scale;        /*!< Scale of all spectral data in case of PS */
#endif
}SBR_SCALE_FACTOR;


#endif
