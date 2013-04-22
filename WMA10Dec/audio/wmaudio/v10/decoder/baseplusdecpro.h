//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __BASEPLUSDECPRO_H_
#define __BASEPLUSDECPRO_H_

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPROLBRV2)

#ifdef __cplusplus
extern "C" 
{  // only need to export C interface if
   // used by C++ source code
#endif

typedef struct DecoderRunLevelTables
{
    const U16   *piIndexToRun;
    const U16   *piIndexToLevel;
    const U16   *piRunLevelTableDec;
}DecoderRunLevelTables;

WMARESULT bpdecInit(CAudioObjectDecoder* paudec);
WMARESULT bpdecDecodeTile(CAudioObjectDecoder* paudec, U32 uVal);
WMARESULT prvBasePlusDecodeRLCCoefQ (CAudioObject*  pau, 
                                  CAudioObjectDecoder* paudec,
                                  PerChannelInfo* ppcinfo);
WMARESULT prvGetNextBPRunDECVecTableIndex(Void*           pobjin, 
                                          PerChannelInfo* ppcinfo);
WMARESULT prvGetNextBPRunDECVecNonRLV4(Void*           pobjin, 
                                       PerChannelInfo* ppcinfo);

WMARESULT prvBasePlusDecodeTileQuantStepSize(CAudioObjectDecoder* paudec,
                                       Int* pcBPTileQuant);
WMARESULT prvBasePlusDecodeChannelQuantStepSize(CAudioObjectDecoder* paudec);
WMARESULT prvBasePlusEntropyDecodeChannelXform (CAudioObjectDecoder* paudec);
WMARESULT prvBasePlusDecodeTileScaleFactors(CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSFBandTableIndex(CAudioObjectDecoder* paudec);
WMARESULT prvBasePlusDecodeFirstTileHeaderExclusiveMode(CAudioObjectDecoder* paudec);
WMARESULT prvBasePlusDecodeScaleFactorRunLevel  (CAudioObjectDecoder* paudec, 
                                  PerChannelInfo* ppcinfo,
                                  Int iBandLim,
                                  PerChannelInfo* ppcinfoPred,
                                  const U16     *rgiRunEntry,
                                  const U16     *rgiLevelEntry,
                                  const U16     *rgunHuffDecTblMaskRLCV3);
WMARESULT prvGetNextSFRunDEC(Void* pobjin, 
                             PerChannelInfo *ppcinfo,
                             const U16      *rgiRunEntry,
                             const U16      *rgiLevelEntry,
                             const U16      *rgunHuffDecTblMaskRLCV3,
                             const U16      ESC_RUNBITS,
                             const U16      ESC_LEVBITS);

WMARESULT prvBasePlusDecodeCoefQPredictor (CAudioObjectDecoder* paudec, 
                                           PerChannelInfo* ppcinfo);
WMARESULT prvBasePlusInverseCoefQPrediction(CAudioObject*  pau, 
                                        CAudioObjectDecoder* paudec,
                                        PerChannelInfo* ppcinfo);

WMARESULT prvBasePlusDecodeInterleaveModeParams(CAudioObjectDecoder* paudec, PerChannelInfo *ppcinfo);
WMARESULT prvBasePlusDecodeRLCCoefQAndDeinterleaveCoefQ(CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo);

WMARESULT prvDecodeCfpdModeParams (CAudioObjectDecoder* paudec, 
                                           PerChannelInfo* ppcinfo);

WMARESULT prvBasePlusDecoderPrepareRefSubFrmPerTile (CAudioObject * pau);

WMARESULT prvBasePlusDecodePDFShiftModeParams (CAudioObjectDecoder* paudec, 
                                   PerChannelInfo* ppcinfo);

WMARESULT prvBasePlusInversePDFShiftRLCCoefQ(CAudioObjectDecoder *paudec, PerChannelInfo* ppcinfo);

WMARESULT prvDecodeBasePlusOverlayMode(CAudioObjectDecoder *paudec);
WMARESULT prvBasePlusDecodeTileExclusiveMode(CAudioObjectDecoder *paudec);
WMARESULT prvBasePlusDecodeFirstTileHeaderOverlayMode(CAudioObjectDecoder* paudec);

WMARESULT plusDecodeBasePlusSuperFrameHeader(CAudioObjectDecoder *paudec);
WMARESULT prvBasePlusCopyChannelXFormToBase (CAudioObjectDecoder *paudec);
WMARESULT prvBasePlusDecodeWeightFactorOverlayMode(CAudioObjectDecoder *paudec);
WMARESULT prvBasePlusReset(CAudioObjectDecoder *paudec);

WMARESULT prvBasePlusDecodeRLCCoefQ_ExplicitStartPos (CAudioObject* pau, 
                                  CAudioObjectDecoder* pcaller, 
                                  PerChannelInfo* ppcinfo);

#ifdef __cplusplus
}
#endif

#endif // BUILD_WMAPRO  && BUILD_WMAPROLBRV2

#endif // __BASEPLUSDECPRO_H_
