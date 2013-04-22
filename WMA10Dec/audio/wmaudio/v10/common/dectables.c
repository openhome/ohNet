//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "DecTables.h"

//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
// This file contains dummy arrays for build to happen with BUILD_WMASTD, BUILD_WMAPRO, 
// and BUILD_WMALSL.
//*@@@---@@@@******************************************************************

AVRT_DATA const U32 g_wmaVec4MaxSum = 6;
AVRT_DATA const U32 g_wmaVec4NSyms  = 126;
AVRT_DATA const U32 g_wmaVec2MaxSum = 16;
AVRT_DATA const U32 g_wmaVec2NSyms  = 136;
AVRT_DATA const U32 g_wmaVec1MaxSum = 100;
AVRT_DATA const U32 g_wmaVec1NSyms  = 100;

#if !defined (BUILD_WMASTD)
AVRT_DATA const U16 g_rgiHuffDecTblMsk[] ={0};
AVRT_DATA const U16 g_rgiHuffDecTblNoisePower[] = {0};
AVRT_DATA const U16 g_rgiHuffDecTbl16smOb[] = {0};
AVRT_DATA const U16 g_rgiHuffDecTbl44smOb[] = {0};
AVRT_DATA const U16 g_rgiHuffDecTbl16ssOb[] = {0};
AVRT_DATA const U16 g_rgiHuffDecTbl44ssOb[] = {0};
AVRT_DATA const U16 g_rgiHuffDecTbl44smQb[] = {0};
AVRT_DATA const U16 g_rgiHuffDecTbl44ssQb[] = {0};
AVRT_DATA const MaskPowerType rgiMaskMinusPower10[] = {0};
AVRT_DATA const MaskPowerType rgiMaskPlusPower10[] = {0};
AVRT_DATA const U32 g_rgiBarkFreqV2	[] = {0};
AVRT_DATA const U16 gRun16smOb[] =	{0};
AVRT_DATA const U16 gLevel16smOb[] =	{0};
AVRT_DATA const U16 gRun16ssOb[] =	{0};
AVRT_DATA const U16 gLevel16ssOb[] =	{0};

#if defined (ENABLE_ALL_ENCOPT)
AVRT_DATA const U16 gRun44smOb[] =	{0};
AVRT_DATA const U16 gLevel44smOb[] =	{0};
AVRT_DATA const U16 gRun44ssOb[] =	{0};
AVRT_DATA const U16 gLevel44ssOb[] =	{0};
AVRT_DATA const U16 gRun44smQb[] =	{0};
AVRT_DATA const U16 gLevel44smQb[] =	{0};
AVRT_DATA const U16 gRun44ssQb[] =	{0};
AVRT_DATA const U16 gLevel44ssQb[] =	{0};
AVRT_DATA const float g_rgfltLsfReconLevel [LPCORDER] [16] = {0};

#if defined(BUILD_INTEGER)
AVRT_DATA ROPI_CONST UInt g_InvQuadRootFraction[] = {0};
AVRT_DATA ROPI_CONST UInt g_InvQuadRootExponent[] = {0};
AVRT_DATA ROPI_CONST UInt g_InverseFraction[] = {0};
AVRT_DATA ROPI_CONST UInt g_SqrtFraction[] = {0};
#endif // BUILD_INTEGER
#endif // ENABLE_ALL_ENCOPT
#endif // !BUILD_WMASTD

#if !defined (BUILD_WMASTD) && !defined (BUILD_WMAPRO)
// i.e for pure lossless
AVRT_DATA const SinCosTable * const rgSinCosTables[] = {0};
AVRT_DATA const DBPowerType rgDBPower10[] = {0};
#if defined (BUILD_INT_FLOAT)
AVRT_DATA const Float rgfltDBPowerExponentScale[] = {0};
#endif // BUILD_INT_FLOAT
#endif // !BUILD_WMASTD && !BUILD_WMAPRO

#if !defined (BUILD_WMAPRO)
AVRT_DATA const U16 g_rgunHuffDecTblMaskVLCV3[] ={0};
AVRT_DATA const U16 g_rgunHuffDecTblMaskRLCV3[] ={0};
AVRT_DATA const QuantStepType g_rgfltDBPower10V3[] = {0};
AVRT_DATA const U16 g_wmaHuffDecTbls_0_0[] = {0};
AVRT_DATA const U16 g_wmaHuffDecTbls_1_0[] = {0};
AVRT_DATA const U16 g_wmaHuffDecTbls_2_0[] = {0};
AVRT_DATA const U16 g_wmaHuffDecTbls_3_SS[] = {0};
AVRT_DATA const U16 g_wmaHuffDecTbls_3_SM[] = {0};
AVRT_DATA const U16 g_wmaRunLevelToRun_SS[] = {0};
AVRT_DATA const U16 g_wmaRunLevelToLevel_SS[] = {0};
AVRT_DATA const U16 g_wmaRunLevelToRun_SM[] = {0};
AVRT_DATA const U16 g_wmaRunLevelToLevel_SM[] = {0};
AVRT_DATA const U16 g_wmaSymToVec4[] = {0};
AVRT_DATA const U8 g_wmaSymToVec2[] = {0};
AVRT_DATA const U32 g_rgiBarkFreqV3	[] = {0};
AVRT_DATA ChXFormType g_rgfltMultiXIDCT[] = {0};
AVRT_DATA const U16 g_rgunRunMaskV3[] =	{0};
AVRT_DATA const U16 g_rgunLevelMaskV3[] =	{0};
#if defined (BUILD_INTEGER)
AVRT_DATA const Int g_rgiLog2DBPower10V3[] = {0};
#endif // BUILD_INTEGER
#if defined(BUILD_INTEGER) || defined(FLOAT_INT_CHXFORM)
AVRT_DATA const ChXFormMType g_fltRotationCos[] = {0};
AVRT_DATA const ChXFormMType g_fltRotationSin[] = {0};
#endif // BUILD_INTEGER || FLOAT_INT_CHXFORM
#endif // !BUILD_WMAPRO
