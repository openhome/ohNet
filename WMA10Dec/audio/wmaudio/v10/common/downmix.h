
//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __DOWNMIX_H_
#define __DOWNMIX_H_

#ifdef __cplusplus
extern "C" {
#endif

WMARESULT WMADownmixMatrixToCoeff( const I32 *rgiDownMix,
                          I32 *rgiCoeff , Int *piNumCoeff,
                    const Int cNumInCh  , const Int cNumOutCh,
                    const U32 dwInChMask, const U32 dwOutChMask );

WMARESULT WMADownmixCoeffToMatrix( I32 *rgiDownMix,
                    const I32 *rgiCoeff , const Int iNumCoeff,
                    const Int cNumInCh  , const Int cNumOutCh,
                    const U32 dwInChMask, const U32 dwOutChMask );

#ifdef __cplusplus
}
#endif

#endif // downmix.h