/*
   Spline resampler structs and prototypes
 */
#ifndef __SPLINE_RESAMPLER_H_
#define __SPLINE_RESAMPLER_H_

#include "typedef.h"


#define MAX_ORDER 3

typedef struct SPLINE_RESAMPLER *HANDLE_SPLINE_RESAMPLER;

int CreateSplineResampler(HANDLE_SPLINE_RESAMPLER* hr, Word16 Fin, Word16 Fout);
void SplineResample(HANDLE_SPLINE_RESAMPLER hr, Word16* Buffer, Word16 inSamples, Word16* outSamples, Word16 channel);
void CopyResamplerState(HANDLE_SPLINE_RESAMPLER hr);

#endif
