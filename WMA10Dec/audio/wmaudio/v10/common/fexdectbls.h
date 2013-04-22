//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#pragma once

#include "msaudio.h"
#include "fex.h"

extern const U16 g_fexHuffScaleDec[308];
extern const U16 g_fexHuffScaleDecPred[216];

extern const I32 g_fexHuffScaleMinSym;
extern const I32 g_fexHuffScaleMaxSym;
extern const I32 g_fexHuffScaleMinBits;
extern const I32 g_fexHuffScaleMaxBits;

extern const I32 g_fexHuffScalePredMinSym;
extern const I32 g_fexHuffScalePredMaxSym;
extern const I32 g_fexHuffScalePredMinBits;
extern const I32 g_fexHuffScalePredMaxBits;
extern const I32 g_fexHuffScalePredOffset;

#ifdef BUILD_WMAPROLBRV2
extern const U16 g_fexScFacLevelDecTableIntra_1dB[220];
extern const U16 g_fexScFacLevelDecTableInter_1dB[68];
extern const U16 g_fexScFacLevelDecTableCh_1dB[68];
extern const U16 g_fexScFacLevelDecTableRecon_1dB[68];

extern const U16 g_fexScFacRunLevelDecTableIntra_3dB[124];
extern const U16 g_fexScFacRunLevelDecTableInter_3dB[112];
extern const U16 g_fexScFacRunLevelDecTableIntpl_3dB[188];
extern const U16 g_fexScFacRunLevelDecTableCh_3dB[56];
extern const U16 g_fexScFacRunLevelDecTableRecon_3dB[68];
extern const U8 g_fexScFacLevelIntpl_3dB[117];
extern const U8 g_fexScFacRunIntpl_3dB[117];
extern const U8 g_fexScFacLevelInter_3dB[57];
extern const U8 g_fexScFacRunInter_3dB[57];
extern const U8 g_fexScFacLevelIntra_3dB[62];
extern const U8 g_fexScFacRunIntra_3dB[62];
extern const U8 g_fexScFacLevelCh_3dB[29];
extern const U8 g_fexScFacRunCh_3dB[29];
extern const U8 g_fexScFacLevelRecon_3dB[32];
extern const U8 g_fexScFacRunRecon_3dB[32];

extern const I16 g_fexScaleIntpl;

extern const I16 g_fexScaleMaxLevel_1dB;
extern const I16 g_fexScaleMinLevelIntra_1dB;
extern const I16 g_fexScaleMaxLevelIntra_1dB;
extern const I16 g_fexScaleMinLevelInter_1dB;
extern const I16 g_fexScaleMaxLevelInter_1dB;
extern const I16 g_fexScaleMinLevelCh_1dB;
extern const I16 g_fexScaleMaxLevelCh_1dB;
extern const I16 g_fexScaleMinLevelRecon_1dB;
extern const I16 g_fexScaleMaxLevelRecon_1dB;

extern const I16 g_fexScaleMaxLevel_3dB;
extern const I16 g_fexScaleRunLevelVLCAtLevelIntpl_3dB[7];
extern const I16 g_fexScaleRunLevelMaxLevelIntpl_3dB;
extern const I16 g_fexScaleRunLevelVLCAtLevelInter_3dB[9];
extern const I16 g_fexScaleRunLevelMaxLevelInter_3dB;
extern const I16 g_fexScaleRunLevelVLCAtLevelIntra_3dB[12];
extern const I16 g_fexScaleRunLevelMaxLevelIntra_3dB;
extern const I16 g_fexScaleRunLevelVLCAtLevelCh_3dB[7];
extern const I16 g_fexScaleRunLevelMaxLevelCh_3dB;
extern const I16 g_fexScaleRunLevelVLCAtLevelRecon_3dB[7];
extern const I16 g_fexScaleRunLevelMaxLevelRecon_3dB;

extern const FexMvCodebook g_rgMvCodebook[14];
extern const I32   g_cNumMvCodebooks;

extern const I32   g_rgrgcNumScMvBands_8_0[13][2];
extern const I32   g_rgrgcNumScMvBands_8_1[8][2];
extern const I32   g_rgrgcNumScMvBands_8_2[8][2];
extern const I32   g_rgrgcNumScMvBands_8_3[7][2];
extern const I32   g_rgcNumEntriesScMvBands_8[4];
extern const I32   g_rgcBitsScMvBands_8[4];

extern const I32   g_rgrgcNumScMvBands_16_0[29][2];
extern const I32   g_rgrgcNumScMvBands_16_1[16][2];
extern const I32   g_rgrgcNumScMvBands_16_2[32][2];
extern const I32   g_rgrgcNumScMvBands_16_3[59][2];
extern const I32   g_rgcNumEntriesScMvBands_16[4];
extern const I32   g_rgcBitsScMvBands_16[4];
#ifdef BUILD_WMAPROLBRV3
extern const I16   g_bpeakShiftRange;
extern const I16   g_bpeakMaxLevel;
extern const I16   g_bpeakMinMaskDelta;
extern const I16   g_bpeakMaxMaskDelta;
extern const U16   g_bpeakCoefShiftHuffDec[24];
extern const U16   g_bpeakCoefLevelHuffDec[8];
extern const U16   g_bpeakMaskDeltaHuffDec[32];
extern const U16   g_bpeakShapeCB1HuffDec[8];
extern const U16   g_bpeakShapeCB2HuffDec[12];
#endif

#endif
