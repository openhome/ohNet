//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
//+-------------------------------------------------------------------------
//
//  Microsoft Windows Media
//
//  Copyright (C) Microsoft Corporation, 1999 - 1999
//
//  File:       tables_rc.h
//
//--------------------------------------------------------------------------

#ifndef _DECTABLES_H_
#define _DECTABLES_H_

#include "macros.h"
#include "constants.h"

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif


#ifdef USE_SIN_COS_TABLES
extern const Int g_SinTableForReconstruction[(8192+4096+2048+1024+512+256+128+64)];
#endif

//for high rates only
extern const U32    g_rgiBarkFreqV2	[];

extern const U16    g_rgiHuffDecTblMsk[];

extern const U16    g_rgiHuffDecTbl16smOb[];
extern const U16    gRun16smOb[];   //can be a byte
extern const U16    gLevel16smOb[]; //can be a byte

extern const U16    g_rgiHuffDecTbl16ssOb[];
extern const U16    gRun16ssOb[];   //can be a byte
extern const U16    gLevel16ssOb[]; //can be a byte

// next five are V3 (WMA Pro) related new tables
extern const U16    g_rgunHuffDecTblMaskVLCV3[];
extern const U16    g_rgunHuffDecTblMaskRLCV3[];
extern const U16    g_rgunLevelMaskV3[];
extern const U16    g_rgunRunMaskV3[];
extern const U32    g_rgiBarkFreqV3	[];

//For FFT & adaptToSubFrameConfig
typedef struct {
    BP1Type sin_PIby4cSB;		// sin( pi/(4*cSB) ) * nF2BP1 for DCT and inverseTransform
    BP1Type cos_PIby4cSB;		// cos( pi/(4*cSB) ) * nF2BP1 for DCT and inverseTransform
	BP1Type sin_3PIby4cSB;		// sin( 3*pi/(4*cSB) ) * nF2BP1 for DCT
	BP1Type cos_3PIby4cSB;		// cos( 3*pi/(4*cSB) ) * nF2BP1 for DCT
	BP1Type sin_PIbycSB;		// sin( pi/cSB ) * nF2BP1 for DCT
	BP1Type cos_PIbycSB;		// cos( pi/cSB ) * nF2BP1 for DCT
	BP1Type sin_2PIbycSB;		// sin( pi/(cSB/2) ) * nF2BP1 for FFT
	BP1Type cos_2PIbycSB;		// cos( pi/(cSB/2) ) * nF2BP1 for FFT
	BP1Type sin_PIby2cSB;		// sin( pi/(2*cSB) ) * nF2BP1 for inverseTransform
	BP1Type cos_PIby2cSB;		// cos( pi/(2*cSB) ) * nF2BP1 for inverseTransform
	BP1Type two_sin_PIbycSB;	// 2 * sin( pi/cSB ) * nF2BP1 for DCT
#ifdef ENABLE_LPC
    BP2Type sin_4PIbycSB;       // sin( 4*pi/cSB ) * nF2BP2 for LPC
    BP2Type cos_4PIbycSB;       // sin( 4*pi/cSB ) * nF2BP2 for LPC
#endif
}SinCosTable;

#define SINCOSTABLE_ENTRIES 65
extern const SinCosTable * const rgSinCosTables[SINCOSTABLE_ENTRIES];

#ifdef UNDER_CE
extern const BP2Type g_bp2SinLUT128[];
extern const BP2Type g_bp2SinLUT256[];
#endif

#if defined(BUILD_INTEGER)
	typedef I32 MaskPowerType;
#	define MASK_POWER_FRAC_BITS 28
#	define MASK_POWER_SCALE (1<<MASK_POWER_FRAC_BITS)
#	define MASK_POWER_FROM_FLOAT(flt) ((MaskPowerType)((flt)*MASK_POWER_SCALE))
#	define FLOAT_FROM_MASK_POWER(typ) ((typ)/((Float)MASK_POWER_SCALE))

	typedef I32 DBPowerType;
#	define DBPOWER_FRAC_BITS QUANTSTEP_FRACT_BITS
#	define DBPOWER_FROM_FLOAT(flt) ((DBPowerType)((flt)*(1<<DBPOWER_FRAC_BITS)))
#	define FLOAT_FROM_DBPOWER(typ) ((typ)*(((Float)1.0)/(1<<DBPOWER_FRAC_BITS)))
#else
	typedef Float MaskPowerType;
#	define MASK_POWER_FRAC_BITS 0
#	define MASK_POWER_SCALE 1
#	define MASK_POWER_FROM_FLOAT(flt) ((MaskPowerType)(flt))
#	define FLOAT_FROM_MASK_POWER(typ) ((Float)(typ))

	typedef Float DBPowerType;
#	define DBPOWER_FROM_FLOAT(flt) ((DBPowerType)(flt))
#	define FLOAT_FROM_DBPower(typ) ((Float)(typ))
#endif

#if defined(SKIMP_ON_ROM)
#	define MASK_MINUS_POWER_TABLE_SIZE 40
#   define MASK_PLUS_POWER_TABLE_SIZE 50
#else
#	define MASK_MINUS_POWER_TABLE_SIZE 72
#   define MASK_PLUS_POWER_TABLE_SIZE 62
#endif
extern const MaskPowerType rgiMaskMinusPower10[MASK_MINUS_POWER_TABLE_SIZE];
extern const MaskPowerType rgiMaskPlusPower10[MASK_PLUS_POWER_TABLE_SIZE];


#define DBPOWER_TABLE_SIZE   128
#define DBPOWER_TABLE_SIZEV3 192
#define INTEGER_DBPOWER_TABLE_SIZEV3 (187)
#define DBPOWER_TABLE_OFFSET  18
extern const DBPowerType rgDBPower10[DBPOWER_TABLE_SIZE];

// next two are WMA Pro tables
extern const QuantStepType g_rgfltDBPower10V3[DBPOWER_TABLE_SIZEV3];
extern const Int g_rgiLog2DBPower10V3[DBPOWER_TABLE_SIZEV3];

#ifdef BUILD_INT_FLOAT
extern const Float rgfltDBPowerExponentScale[((DBPOWER_TABLE_OFFSET+DBPOWER_TABLE_SIZE)>>3)+1];
#endif

#ifdef ENABLE_ALL_ENCOPT
//for all other rates
extern const U16    g_rgiHuffDecTbl44smOb[];
extern const U16    gRun44smOb[];   //can be a byte
extern const U16    gLevel44smOb[];

extern const U16    g_rgiHuffDecTbl44ssOb[];
extern const U16    gRun44ssOb[];
extern const U16    gLevel44ssOb[]; //can be a byte

extern const U16    g_rgiHuffDecTbl44smQb[];
extern const U16    gRun44smQb[];
extern const U16    gLevel44smQb[];  //can be a byte

extern const U16    g_rgiHuffDecTbl44ssQb[];
extern const U16    gRun44ssQb[];
extern const U16    gLevel44ssQb[];  //can be a byte

extern const U16    g_rgiHuffDecTblNoisePower[];

extern const float  g_rgfltLsfReconLevel [LPCORDER] [16];

#if defined(BUILD_INTEGER_LPC)

#   define INVQUADROOT_FRACTION_TABLE_LOG2_SIZE 8
#   define INVQUADROOT_FRACTION_TABLE_SIZE (1<<INVQUADROOT_FRACTION_TABLE_LOG2_SIZE)

    extern ROPI_CONST UInt g_InvQuadRootFraction[1+INVQUADROOT_FRACTION_TABLE_SIZE];
    extern ROPI_CONST UInt g_InvQuadRootExponent[BITS_LP_SPEC_POWER+1];

#endif // BUILD_INTEGER_LPC
#endif // ENABLE_ALL_ENCOPT

#if defined(BUILD_INTEGER)

#   define INVERSE_FRACTION_TABLE_LOG2_SIZE 8
#   define INVERSE_FRACTION_TABLE_SIZE (1<<INVERSE_FRACTION_TABLE_LOG2_SIZE)
    extern ROPI_CONST UInt g_InverseFraction[1+INVERSE_FRACTION_TABLE_SIZE];

#   define SQRT_FRACTION_TABLE_LOG2_SIZE 8
#   define SQRT_FRACTION_TABLE_SIZE (1<<SQRT_FRACTION_TABLE_LOG2_SIZE)
    extern ROPI_CONST UInt g_SqrtFraction[1+SQRT_FRACTION_TABLE_SIZE];

#endif // BUILD_INTEGER

#define PWRTORMS_ZEROPT     60
#define PWRTORMS_SIZE       (PWRTORMS_ZEROPT*2 + 1)
extern const UInt           g_rgfiPwrToRMS[];

// next two are for V3 (WMA Pro)
#define MAX_PREDEF_MATRIX_CHANNELS 6
extern  ChXFormType   g_rgfltMultiXIDCT[];

#ifdef __cplusplus
}
#endif

#if defined(BUILD_INTEGER) || defined(FLOAT_INT_CHXFORM)
AVRT_DATA extern const ChXFormMType g_fltRotationCos[MAX_ROTATION_ANGLES];
AVRT_DATA extern const ChXFormMType g_fltRotationSin[MAX_ROTATION_ANGLES];
#endif


// from wmavechuffdtbls.h, only for WMA Pro
extern const U32 g_wmaVec4MaxSum;
extern const U32 g_wmaVec4NSyms;
extern const U32 g_wmaVec2MaxSum;
extern const U32 g_wmaVec2NSyms;
extern const U32 g_wmaVec1MaxSum;
extern const U32 g_wmaVec1NSyms;
#define WMA_MAX_RL_LEVEL_SS (52)

#define WMA_MAX_RL_LEVEL_SM (28)

extern const U16 g_wmaHuffDecTbls_0_0[240];
extern const U16 g_wmaHuffDecTbls_1_0[272];
extern const U16 g_wmaHuffDecTbls_2_0[204];
extern const U16 g_wmaHuffDecTbls_3_SS[474];
extern const U16 g_wmaHuffDecTbls_3_SM[532];

extern const U16 g_wmaRunLevelToRun_SS[242];
extern const U16 g_wmaRunLevelToLevel_SS[242];
extern const U16 g_wmaRunLevelToRun_SM[270];
extern const U16 g_wmaRunLevelToLevel_SM[270];
extern const U16 g_wmaSymToVec4[126];
extern const U8 g_wmaSymToVec2[136];
// end of WMA Pro tables

#ifdef DEFINE_ARITH_CODER
#include "wmaactbls.h"
//lossless arithmetic coding
const extern I32 i32ResQPMF[]; 
#endif // DEFINE_ARITH_CODER

#ifdef USE_V4ENTCODING
#include "enttblsdecv4.h"
#endif

#if defined(BUILD_WMAPROLBRV2)
#include "chexdectblspro.h"
extern const Float g_fMinLMRMStep;
extern const Int   g_iMinLMScale;
extern const Int   g_iMaxLMScale;
extern const Int   g_iNumLMScale;
extern const I16 g_rgiMinRMScale[251];
extern const I16 g_rgiMaxRMScale[251];
#endif

#endif // _DECTABLES_H_

