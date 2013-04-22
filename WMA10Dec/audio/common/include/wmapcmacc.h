//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __WMAPCMACC_H__
#define __WMAPCMACC_H__

#include "wmatypes.h"
#include "pcmfmt.h"

typedef enum {
    PCMAccFlt,
    PCMAcc16,
    PCMAcc24,
    PCMAcc2432,
    PCMAcc32,
    PCMAcc8,
    PCMAccGeneric
} WMAPCMType;

#pragma pack (push)
#pragma pack () // default
typedef struct _WMAPCMAcc {
    WMAPCMType type;
    PCMFormat fmt;
} WMAPCMAcc;
#pragma pack (pop)

#ifdef __cplusplus
extern "C" {
#endif
void WMAPCMAccSetFormat(WMAPCMAcc* pAcc, PCMFormat* pFormat);
float WMAPCMAccGetPCMGeneric(WMA_U32 vb, WMA_U32 cb, WMA_U8* pb); // vb: valid bytes; cb: container bytes
double WMAPCMAccGetPCMGenericD(WMA_U32 vb, WMA_U32 cb, WMA_U8* pb);
void WMAPCMAccPutPCMGeneric(WMA_U32 vb, WMA_U32 cb, WMA_U8* pb, float fltVal);
void WMAPCMAccPutPCMGenericD(WMA_U32 vb, WMA_U32 cb, WMA_U8* pb, double dblVal);
void WMAPCMAccGetPCMMulti(WMAPCMAcc* pAcc, WMA_U8* pb, float* pflt, WMA_U32 count);
void WMAPCMAccGetPCMMultiD(WMAPCMAcc* pAcc, WMA_U8* pb, double* pdbl, WMA_U32 count);
void WMAPCMAccPutPCMMulti(WMAPCMAcc* pAcc, WMA_U8* pb, float* pflt, WMA_U32 count, WMA_Bool fClip);
void WMAPCMAccPutPCMMultiD(WMAPCMAcc* pAcc, WMA_U8* pb, double* pdbl, WMA_U32 count, WMA_Bool fClip);
#ifdef __cplusplus
}
#endif

// built-in float-to-int conversion with /QIfist gives somewhat faster code
#ifdef USE_ROUND_MACROS
// ROUNDF from wmaudio\x86\macros.h
__inline int f2i32(float fSrc) {
    __int64 intval;
    _asm {
        fld         fSrc
        fistp       dword ptr [intval]
        mov         eax,dword ptr [intval]
    }
}

// ROUNDD from wmaudio\x86\macros.h
__inline int d2i32(double f) {
    _asm {
        fld         f
        fistp       dword ptr [f]
        mov         eax,dword ptr [f]
    }
}

#define FLOAT2I32(f,i) (i) = f2i32(f)
#define DOUBLE2I32(d,i) (i) = d2i32(d)
#else
#define FLOAT2I32(f,i) (i) = (WMA_I32)(f)
#define DOUBLE2I32(d,i) (i) = (WMA_I32)(d)
#endif

//
// These macros map all integer ranges, regardless of integer bit
// depth, to -2^31 .. +2^31-1 float (-2147483648.0 .. +2147483647.0).
//#define GETPCM8(pb,fltVal)   (fltVal) = (float)((((WMA_I32)(*((WMA_U8*)(pb)))) ^ 0x80) << 24) // ^ 0x80 because 8-bit is unsigned
//#define PUTPCM8(pb,fltVal)   { WMA_I32 i; FLOAT2I32(fltVal,i); (pb)[0] = (((WMA_U8)(i >> 24))  ^ 0x80)
//#define PUTPCM24(pb,fltVal)  { WMA_I32 i; FLOAT2I32(fltVal,i); (pb)[0] = (WMA_U8)(i >>  8); (pb)[1] = (WMA_U8)(i >> 16); (pb)[2] = (WMA_U8)(i >> 24); }
//#if _X86_
//#define GETPCM16(pb,fltVal) (fltVal) = (float)(*((WMA_I16*)(pb)))
//#define GETPCM24(pb,fltVal) (fltVal) = (float)(((WMA_I32*)(pb)) << 8)
//#define GETPCM32(pb,fltVal) (fltVal) = (float)((WMA_I32*)(pb))
//#define PUTPCM16(pb,fltVal) { WMA_I32 i; FLOAT2I32(fltVal,i); (*((WMA_I16*)(pb))) = (WMA_I16)(i >> 16); }
//#define PUTPCM32(pb,fltVal) { WMA_I32 i; FLOAT2I32(fltVal,i); (*((WMA_I32*)(pb))) = i; }
//#else
//#define GETPCM16(pb,fltVal) (fltVal) = (float)((((WMA_I32)((pb)[0])) << 16) | (((WMA_I32)((pb)[1])) << 24))
//#define GETPCM24(pb,fltVal) (fltVal) = (float)((((WMA_I32)((pb)[0])) <<  8) | (((WMA_I32)((pb)[1])) << 16) | (((WMA_I32)((pb)[2])) << 24))
//#define GETPCM32(pb,fltVal) (fltVal) = (float)((((WMA_I32)((pb)[0])) <<  0) | (((WMA_I32)((pb)[1])) <<  8) | (((WMA_I32)((pb)[2])) << 16) | (((WMA_I32)((pb)[2])) << 24))
//#define PUTPCM16(pb,fltVal) { WMA_I32 i; FLOAT2I32(fltVal,i); (pb)[0] = (WMA_U8)(i >> 16); (pb)[1] = (WMA_U8)(i >> 24);  }
//#define PUTPCM32(pb,fltVal) { WMA_I32 i; FLOAT2I32(fltVal,i); (pb)[0] = (WMA_U8)(i >>  0); (pb)[1] = (WMA_U8)(i >>  8); (pb)[2] = (WMA_U8)(i >> 16); (pb)[3] = (WMA_U8)(i >> 24); }
//#endif
//
// Audio engine maps everything to -1.0 .. +1.0.
// For intin-intout or fltin-fltout the range choice is arbitrary.
// But the intin-fltout neeeds to be supported properly.

#define I08MAXGETFLT 128.0f
#define I16MAXGETFLT 32768.0f
#define I24MAXGETFLT 8388608.0f
#define I32MAXGETFLT 2147483648.0f
#define I08MAXPUTFLT 127.0f
#define I16MAXPUTFLT 32767.0f
#define I24MAXPUTFLT 8388607.0f
#define I32MAXPUTFLT 2147483647.0f

#define I08MAXGETDBL 128.0
#define I16MAXGETDBL 32768.0
#define I24MAXGETDBL 8388608.0
#define I32MAXGETDBL 2147483648.0
#define I08MAXPUTDBL 127.0
#define I16MAXPUTDBL 32767.0
#define I24MAXPUTDBL 8388607.0
#define I32MAXPUTDBL 2147483647.0

//#define SOFT_CLIP
#ifdef SOFT_CLIP
#define _USE_MATH_DEFINES 
#include <math.h>
#define CLIP_START 0.5f
#define ATAN_COEF ((1.0f - CLIP_START) * 2.0f / M_PI)
#define CLIP_FN(f) ((float)(CLIP_START + ATAN_COEF * atan((f - CLIP_START) / ATAN_COEF)))
#define CLIPF(f) { if (f > CLIP_START) f = CLIP_FN(f); else if (f < -CLIP_START) f = -CLIP_FN(-f); }
#define CLIPD CLIPF
#else
#define CLIPF(f) { if (f > 1.0f) f = 1.0f; else if (f < -1.0f) f = -1.0f; }
#define CLIPD(f) { if (f > 1.0 ) f = 1.0 ; else if (f < -1.0 ) f = -1.0 ; }
#endif

#define GETPCMFLT(pb,fltVal) (fltVal) = *((float*)(pb))
#define PUTPCMFLT(pb,fltVal) *((float*)(pb)) = (fltVal)
#define GETPCM8(pb,fltVal) (fltVal) = ((float)(*((signed char*)(pb)) ^ (signed char)0x80)) / I08MAXGETFLT
#define PUTPCM8(pb,fltVal)   { WMA_I32 i; float f = (fltVal) * I08MAXPUTFLT; FLOAT2I32(f,i); (pb)[0] = (WMA_U8)(i ^ 0x80); }
#define PUTPCM24(pb,fltVal)  { WMA_I32 i; float f = (fltVal) * I24MAXPUTFLT; FLOAT2I32(f,i); (pb)[0] = (WMA_U8)(i); (pb)[1] = (WMA_U8)(i >> 8); (pb)[2] = (WMA_U8)(i >> 16); }
#define PUTPCM8CLIP(pb,fltVal)   { WMA_I32 i; float f = (fltVal); CLIPF(f); f *= I08MAXPUTFLT; FLOAT2I32(f,i); (pb)[0] = (WMA_U8)(i ^ 0x80); }
#define PUTPCM24CLIP(pb,fltVal)  { WMA_I32 i; float f = (fltVal); CLIPF(f); f *= I24MAXPUTFLT; FLOAT2I32(f,i); (pb)[0] = (WMA_U8)(i); (pb)[1] = (WMA_U8)(i >> 8); (pb)[2] = (WMA_U8)(i >> 16); }

#define GETPCMFLTD(pb,dblVal) (dblVal) = (double)(*((float*)(pb)))
#define PUTPCMFLTD(pb,dblVal) *((float*)(pb)) = (float)(dblVal)
#define GETPCM8D(pb,dblVal) (dblVal) = ((double)(*((signed char*)(pb)) ^ (signed char)0x80)) / I08MAXGETDBL
#define PUTPCM8D(pb,dblVal)   { WMA_I32 i; double f = (dblVal) * I08MAXPUTDBL; DOUBLE2I32(f,i); (pb)[0] = (WMA_U8)(i ^ 0x80); }
#define PUTPCM24D(pb,dblVal)  { WMA_I32 i; double f = (dblVal) * I24MAXPUTDBL; DOUBLE2I32(f,i); (pb)[0] = (WMA_U8)(i); (pb)[1] = (WMA_U8)(i >> 8); (pb)[2] = (WMA_U8)(i >> 16); }
#define PUTPCM8CLIPD(pb,dblVal)   { WMA_I32 i; double f = (dblVal); CLIPD(f); f *= I08MAXPUTDBL; DOUBLE2I32(f,i); (pb)[0] = (WMA_U8)(i ^ 0x80); }
#define PUTPCM24CLIPD(pb,dblVal)  { WMA_I32 i; double f = (dblVal); CLIPD(f); f *= I24MAXPUTDBL; DOUBLE2I32(f,i); (pb)[0] = (WMA_U8)(i); (pb)[1] = (WMA_U8)(i >> 8); (pb)[2] = (WMA_U8)(i >> 16); }

#if _X86_
#define GETPCM16(pb,fltVal) (fltVal) = ((float)(*((WMA_I16*)(pb)))) / I16MAXGETFLT
#define GETPCM24(pb,fltVal) (fltVal) = ((float)((*((WMA_I32*)(pb))) << 8)) / I32MAXGETFLT
#define GETPCM32(pb,fltVal) (fltVal) = ((float)(*((WMA_I32*)(pb)))) / I32MAXGETFLT
#define PUTPCM16(pb,fltVal) { WMA_I32 i; float f = (fltVal) * I16MAXPUTFLT; FLOAT2I32(f,i); (*((WMA_I16*)(pb))) = (WMA_I16)i; }
#define PUTPCM32(pb,fltVal) { WMA_I32 i; float f = (fltVal) * I32MAXPUTFLT; FLOAT2I32(f,i); (*((WMA_I32*)(pb))) = i; }
#define PUTPCM16CLIP(pb,fltVal) { WMA_I32 i; float f = (fltVal); CLIPF(f); f *= I16MAXPUTFLT; FLOAT2I32(f,i); (*((WMA_I16*)(pb))) = (WMA_I16)i; }
#define PUTPCM32CLIP(pb,fltVal) { WMA_I32 i; float f = (fltVal); CLIPF(f); f *= I32MAXPUTFLT; FLOAT2I32(f,i); (*((WMA_I32*)(pb))) = i; }
#define GETPCM16D(pb,dblVal) (dblVal) = ((double)(*((WMA_I16*)(pb)))) / I16MAXGETDBL
#define GETPCM24D(pb,dblVal) (dblVal) = ((double)((*((WMA_I32*)(pb))) << 8)) / I32MAXGETDBL
#define GETPCM32D(pb,dblVal) (dblVal) = ((double)(*((WMA_I32*)(pb)))) / I32MAXGETDBL
#define PUTPCM16D(pb,dblVal) { WMA_I32 i; double f = (dblVal) * I16MAXPUTDBL; DOUBLE2I32(f,i); (*((WMA_I16*)(pb))) = (WMA_I16)i; }
#define PUTPCM32D(pb,dblVal) { WMA_I32 i; double f = (dblVal) * I32MAXPUTDBL; DOUBLE2I32(f,i); (*((WMA_I32*)(pb))) = i; }
#define PUTPCM16CLIPD(pb,dblVal) { WMA_I32 i; double f = (dblVal); CLIPD(f); f *= I16MAXPUTDBL; DOUBLE2I32(f,i); (*((WMA_I16*)(pb))) = (WMA_I16)i; }
#define PUTPCM32CLIPD(pb,dblVal) { WMA_I32 i; double f = (dblVal); CLIPD(f); f *= I32MAXPUTDBL; DOUBLE2I32(f,i); (*((WMA_I32*)(pb))) = i; }
#else
#define GETPCM16(pb,fltVal) (fltVal) = ((float)((((WMA_I32)((pb)[0])) <<  0) | (((WMA_I32)(((signed char*)(pb))[1])) <<  8))) / I16MAXGETFLT
#define GETPCM24(pb,fltVal) (fltVal) = ((float)((((WMA_I32)((pb)[0])) <<  0) | (((WMA_I32)((pb)[1])) <<  8) | (((WMA_I32)(((signed char*)(pb))[2])) << 16))) / I24MAXGETFLT
#define GETPCM32(pb,fltVal) (fltVal) = ((float)((((WMA_I32)((pb)[0])) <<  0) | (((WMA_I32)((pb)[1])) <<  8) | (((WMA_I32)((pb)[2])) << 16) | (((WMA_I32)(((signed char*)(pb))[2])) << 24))) / I32MAXGETFLT
#define PUTPCM16(pb,fltVal) { WMA_I32 i; float f = (fltVal) * I16MAXPUTFLT; FLOAT2I32(f,i); (pb)[0] = (WMA_U8)(i >> 0); (pb)[1] = (WMA_U8)(i >> 8);  }
#define PUTPCM32(pb,fltVal) { WMA_I32 i; float f = (fltVal) * I32MAXPUTFLT; FLOAT2I32(f,i); (pb)[0] = (WMA_U8)(i >> 0); (pb)[1] = (WMA_U8)(i >> 8); (pb)[2] = (WMA_U8)(i >> 16); (pb)[3] = (WMA_U8)(i >> 24); }
#define PUTPCM16CLIP(pb,fltVal) { WMA_I32 i; float f = (fltVal); CLIPF(f); f *= I16MAXPUTFLT; FLOAT2I32(f,i); (pb)[0] = (WMA_U8)(i >> 0); (pb)[1] = (WMA_U8)(i >> 8);  }
#define PUTPCM32CLIP(pb,fltVal) { WMA_I32 i; float f = (fltVal); CLIPF(f); f *= I32MAXPUTFLT; FLOAT2I32(f,i); (pb)[0] = (WMA_U8)(i >> 0); (pb)[1] = (WMA_U8)(i >> 8); (pb)[2] = (WMA_U8)(i >> 16); (pb)[3] = (WMA_U8)(i >> 24); }
#define GETPCM16D(pb,dblVal) (dblVal) = ((double)((((WMA_I32)((pb)[0])) <<  0) | (((WMA_I32)(((signed char*)(pb))[1])) <<  8))) / I16MAXGETDBL
#define GETPCM24D(pb,dblVal) (dblVal) = ((double)((((WMA_I32)((pb)[0])) <<  0) | (((WMA_I32)((pb)[1])) <<  8) | (((WMA_I32)(((signed char*)(pb))[2])) << 16))) / I24MAXGETDBL
#define GETPCM32D(pb,dblVal) (dblVal) = ((double)((((WMA_I32)((pb)[0])) <<  0) | (((WMA_I32)((pb)[1])) <<  8) | (((WMA_I32)((pb)[2])) << 16) | (((WMA_I32)(((signed char*)(pb))[2])) << 24))) / I32MAXGETDBL
#define PUTPCM16D(pb,dblVal) { WMA_I32 i; double f = (dblVal) * I16MAXPUTDBL; DOUBLE2I32(f,i); (pb)[0] = (WMA_U8)(i >> 0); (pb)[1] = (WMA_U8)(i >> 8);  }
#define PUTPCM32D(pb,dblVal) { WMA_I32 i; double f = (dblVal) * I32MAXPUTDBL; DOUBLE2I32(f,i); (pb)[0] = (WMA_U8)(i >> 0); (pb)[1] = (WMA_U8)(i >> 8); (pb)[2] = (WMA_U8)(i >> 16); (pb)[3] = (WMA_U8)(i >> 24); }
#define PUTPCM16CLIPD(pb,dblVal) { WMA_I32 i; double f = (dblVal); CLIPD(f); f *= I16MAXPUTDBL; DOUBLE2I32(f,i); (pb)[0] = (WMA_U8)(i >> 0); (pb)[1] = (WMA_U8)(i >> 8);  }
#define PUTPCM32CLIPD(pb,dblVal) { WMA_I32 i; double f = (dblVal); CLIPD(f); f *= I32MAXPUTDBL; DOUBLE2I32(f,i); (pb)[0] = (WMA_U8)(i >> 0); (pb)[1] = (WMA_U8)(i >> 8); (pb)[2] = (WMA_U8)(i >> 16); (pb)[3] = (WMA_U8)(i >> 24); }
#endif

#define GETPCM(acc,pb,fltVal) { \
    switch(acc.type) { \
    case PCMAccFlt: GETPCMFLT (pb,fltVal); break; \
    case PCMAcc16:  GETPCM16  (pb,fltVal); break; \
    case PCMAcc24:  GETPCM24  (pb,fltVal); break; \
    case PCMAcc2432:GETPCM24(1+pb,fltVal); break; \
    case PCMAcc32:  GETPCM32  (pb,fltVal); break; \
    case PCMAcc8:   GETPCM8   (pb,fltVal); break; \
    case PCMAccGeneric: fltVal = WMAPCMAccGetPCMGeneric((acc.fmt.nValidBitsPerSample + 7) / 8, acc.fmt.cbPCMContainerSize, pb); break; \
    default: assert(0); \
    } \
}

#define GETPCMD(acc,pb,dblVal) { \
    switch(acc.type) { \
    case PCMAccFlt: GETPCMFLTD (pb,dblVal); break; \
    case PCMAcc16:  GETPCM16D  (pb,dblVal); break; \
    case PCMAcc24:  GETPCM24D  (pb,dblVal); break; \
    case PCMAcc2432:GETPCM24D(1+pb,dblVal); break; \
    case PCMAcc32:  GETPCM32D  (pb,dblVal); break; \
    case PCMAcc8:   GETPCM8D   (pb,dblVal); break; \
    case PCMAccGeneric: dblVal = WMAPCMAccGetPCMGenericD((acc.fmt.nValidBitsPerSample + 7) / 8, acc.fmt.cbPCMContainerSize, pb); break; \
    default: assert(0); \
    } \
}

#define PUTPCM(acc,pb,fltVal) { \
   switch(acc.type) { \
   case PCMAccFlt: PUTPCMFLT (pb,fltVal); break; \
   case PCMAcc16:  PUTPCM16  (pb,fltVal); break; \
   case PCMAcc24:  PUTPCM24  (pb,fltVal); break; \
   case PCMAcc2432:PUTPCM24(1+pb,fltVal); break; \
   case PCMAcc32:  PUTPCM32  (pb,fltVal); break; \
   case PCMAcc8:   PUTPCM8   (pb,fltVal); break; \
   case PCMAccGeneric: WMAPCMAccPutPCMGeneric((acc.fmt.nValidBitsPerSample + 7) / 8, acc.fmt.cbPCMContainerSize, pb,fltVal); break; \
   default: assert(0); \
   } \
}

#define PUTPCMCLIP(acc,pb,fltVal) { \
   switch(acc.type) { \
   case PCMAccFlt: PUTPCMFLT (pb,fltVal); break; \
   case PCMAcc16:  PUTPCM16CLIP  (pb,fltVal); break; \
   case PCMAcc24:  PUTPCM24CLIP  (pb,fltVal); break; \
   case PCMAcc2432:PUTPCM24CLIP(1+pb,fltVal); break; \
   case PCMAcc32:  PUTPCM32CLIP  (pb,fltVal); break; \
   case PCMAcc8:   PUTPCM8CLIP   (pb,fltVal); break; \
   case PCMAccGeneric: WMAPCMAccPutPCMGeneric((acc.fmt.nValidBitsPerSample + 7) / 8, acc.fmt.cbPCMContainerSize, pb,fltVal); break; \
   default: assert(0); \
   } \
}

#define PUTPCMD(acc,pb,dblVal) { \
   switch(acc.type) { \
   case PCMAccFlt: PUTPCMFLTD (pb,dblVal); break; \
   case PCMAcc16:  PUTPCM16D  (pb,dblVal); break; \
   case PCMAcc24:  PUTPCM24D  (pb,dblVal); break; \
   case PCMAcc2432:PUTPCM24D(1+pb,dblVal); break; \
   case PCMAcc32:  PUTPCM32D  (pb,dblVal); break; \
   case PCMAcc8:   PUTPCM8D   (pb,dblVal); break; \
   case PCMAccGeneric: WMAPCMAccPutPCMGenericD((acc.fmt.nValidBitsPerSample + 7) / 8, acc.fmt.cbPCMContainerSize, pb,dblVal); break; \
   default: assert(0); \
   } \
}

#define PUTPCMCLIPD(acc,pb,dblVal) { \
   switch(acc.type) { \
   case PCMAccFlt: PUTPCMFLTD (pb,dblVal); break; \
   case PCMAcc16:  PUTPCM16CLIPD  (pb,dblVal); break; \
   case PCMAcc24:  PUTPCM24CLIPD  (pb,dblVal); break; \
   case PCMAcc2432:PUTPCM24CLIPD(1+pb,dblVal); break; \
   case PCMAcc32:  PUTPCM32CLIPD  (pb,dblVal); break; \
   case PCMAcc8:   PUTPCM8CLIPD   (pb,dblVal); break; \
   case PCMAccGeneric: WMAPCMAccPutPCMGenericD((acc.fmt.nValidBitsPerSample + 7) / 8, acc.fmt.cbPCMContainerSize, pb,dblVal); break; \
   default: assert(0); \
   } \
}

#endif//__WMAPCMACC_H__