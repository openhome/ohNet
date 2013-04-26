//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************


#ifndef _ENTROPYDEC_H
#define _ENTROPYDEC_H

#include "msaudiodec.h"

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

    WMARESULT prvEntropyDecodePostProcXform (CAudioObjectDecoder* paudec);
    WMARESULT prvEntropyDecodeChannelXform (CAudioObjectDecoder* paudec);
    WMARESULT prvDecodeQuantStepV3 (CAudioObjectDecoder* paudec);
    WMARESULT prvDecodeQuantStepModifiers (CAudioObjectDecoder* paudec);
    WMARESULT prvDecodeMaskHeaderV3_Channel (CAudioObjectDecoder* paudec,
        Int iCh);
    WMARESULT prvEscapeDecodeRunV3(Int *pcRunOfZeros, Int cMaxRun,
        CWMAInputBitStream *pibstrm);
    WMARESULT prvDecodeQuantStepV2 (CAudioObjectDecoder* paudec);
    Void    prvSetDecTable  (CAudioObjectDecoder* paudec,  PerChannelInfo* ppcinfo, I16 iSet);
    Void    prvGetBandWeightLowRate (CAudioObjectDecoder* paudec);
    Void prvInitDecodeTileHdr(CAudioObjectDecoder *paudec, ConfigFrame iFrame);
    I32 prvDecodeTileHdr(CAudioObjectDecoder* paudec, ConfigFrame iFrame);

#ifdef __cplusplus
}
#endif

#endif //_ENTROPYDEC_H

