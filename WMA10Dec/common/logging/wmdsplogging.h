
//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************/

#ifndef __WMDSPLOGGING_H__
#define __WMDSPLOGGING_H__
#include <stdarg.h>

#define WMDSPLogTtlPinMax 8

typedef enum _WMDSPLogComp {
    //
    // Audio
    //
    
    // codec
    WMDSPLogComp_WMAEnc    = 1,
    WMDSPLogComp_WMADec    = 2,
    WMDSPLogComp_WMAVEnc   = 3,
    WMDSPLogComp_WMAVDec   = 4,
    WMDSPLogComp_WMARTVEnc = 5,
    WMDSPLogComp_WMARTVDec = 6,
    WMDSPLogComp_Mpg2ADec  = 7,
    WMDSPLogComp_AC3Enc    = 8,
    WMDSPLogComp_TrueHDDec = 9,
    
    // dsp
    WMDSPLogComp_Eq       = 31,
    WMDSPLogComp_Norm     = 32,
    WMDSPLogComp_TimeComp = 33,
    WMDSPLogComp_Mixer    = 34,
    WMDSPLogComp_HDCDDec  = 35,
    WMDSPLogComp_Resample = 36,
    WMDSPLogComp_SA       = 37,
    WMDSPLogComp_VRHeadphone = 38,
    WMDSPLogComp_SpkrFill = 39,
    WMDSPLogComp_WmaSpdTx = 40,
    WMDSPLogComp_LFXAPO   = 41,
    WMDSPLogComp_TCAPO    = 42,
    WMDSPLogComp_AudMorph = 43,
    WMDSPLogComp_AEC      = 44,
    WMDSPLogComp_AACDec   = 45,
    WMDSPLogComp_GFXAPO   = 46,
    WMDSPLogComp_RCDSA    = 47,
    WMDSPLogComp_MSVeranceWMDet = 48,

    //
    // Video
    //
    // codec
    WMDSPLogComp_WMVEnc   = 101,
    WMDSPLogComp_WMVDec   = 102,
    WMDSPLogComp_Mpg4Dec  = 103,
    WMDSPLogComp_Mpg2VDec = 104,
    WMDSPLogComp_Mpg2Enc  = 105,
    WMDSPLogComp_H264Dec  = 106,

    // dsp
    WMDSPLogComp_Resize      = 131,
    WMDSPLogComp_FrameInterp = 132,
    WMDSPLogComp_ColorConv   = 133,
    WMDSPLogComp_SMPTEWipe   = 134

} WMDSPLogComp; // component

typedef enum _WMDSPLogCat {
    WMDSPLogCat_Unknown   = 0x00000000,
    WMDSPLogCat_Format    = 0x00000001,
    WMDSPLogCat_State     = 0x00000002,
    WMDSPLogCat_Buffer    = 0x00000003,
    WMDSPLogCat_Timestamp = 0x00000004,
    WMDSPLogCat_Perf      = 0x00000005,
    WMDSPLogCat_Init      = 0x00000006,
    WMDSPLogNumCategories
} WMDSPLogCat; // event category

typedef enum _WMDSPLogLevel {
    WMDSPLogLevel_Assert           = 0, // code bug
    WMDSPLogLevel_Error            = 1, // unexpected error
    WMDSPLogLevel_NormalError      = 2, // expected error
    WMDSPLogLevel_UnusualEvent     = 3,
    WMDSPLogLevel_OccasionalEvent  = 4,
    WMDSPLogLevel_PeriodicEvent    = 5,
    WMDSPLogLevel_FrequentEvent    = 6,
    WMDSPLogNumLevels
} WMDSPLogLevel;

typedef enum _WMDSPDumpCat {
    WMDSPDumpCat_Input  = 0,
    WMDSPDumpCat_Output = 1,
    WMDSPDumpCat_Custom1,
    WMDSPDumpCat_Custom2,
    WMDSPDumpNumCategories
} WMDSPDumpCat;

typedef void* WMDSPLogInst;

#define WMDSPCALLERINFO __FILE__,__LINE__

#ifdef WMDSPLOGGING_ENABLED


#define WMDSPLOGMSG WMDSPLogMsg
#define WMDSPDUMP WMDSPDump
#define WMDSPDUMPRESET WMDSPDumpReset
#define WMDSPDUMPRESETALL WMDSPDumpResetAll

#ifdef __cplusplus
extern "C" {
#endif
WMDSPLogInst WMDSPLogInit(WMDSPLogComp comp);
void WMDSPLogClose(WMDSPLogInst inst);
void WMDSPLogMsg(const char* file, int line, WMDSPLogInst inst, WMDSPLogCat cat, WMDSPLogLevel, const char* strr, ...);
void WMDSPLogMsgVa(const char* file, int line, WMDSPLogInst inst, WMDSPLogCat cat, WMDSPLogLevel, const char* strr, va_list ap);

void WMDSPDump(WMDSPLogInst inst, WMDSPDumpCat cat, int iPin, const char* szPin, const unsigned char* pb, int cb);
void WMDSPDumpReset(WMDSPLogInst inst, WMDSPDumpCat cat);
void WMDSPDumpResetAll(WMDSPLogInst inst);
#ifdef __cplusplus
}
#endif

#define WMDSPLOGDECLARE void* m_WMDSPLogInst;

#ifdef __cplusplus
#define WMDSPLOGINIT(comp) m_WMDSPLogInst = WMDSPLogInit(comp);
#define WMDSPLOGINIT_NOLOGGING m_WMDSPLogInst = NULL;
#define WMDSPLOGCOPYINST(inst) m_WMDSPLogInst = inst;
#define WMDSPLOGCLOSE if (m_WMDSPLogInst) { WMDSPLogClose(m_WMDSPLogInst); m_WMDSPLogInst = NULL; }
#define WMDSPLOGINST m_WMDSPLogInst
#else
#define WMDSPLOGINIT(x,comp) x->m_WMDSPLogInst = WMDSPLogInit(comp);
#define WMDSPLOGINIT_NOLOGGING(x) x->m_WMDSPLogInst = NULL;
#define WMDSPLOGCOPYINST(x, inst) x->m_WMDSPLogInst = inst;
#define WMDSPLOGCLOSE(x) if (x->m_WMDSPLogInst) { WMDSPLogClose(x->m_WMDSPLogInst); x->m_WMDSPLogInst = NULL; }
#define WMDSPLOGINST(x) (x->m_WMDSPLogInst)
#endif


#else//WMDSPLOGGING_ENABLED


#define WMDSPLOGDECLARE
#define WMDSPLOGMSG


#ifdef __cplusplus
#define WMDSPLOGINIT
#define WMDSPLOGINIT_NOLOGGING
#define WMDSPLOGCOPYINST(inst)
#define WMDSPLOGCLOSE
#define WMDSPLOGINST 0
#else
#define WMDSPLOGINIT(x,comp) 
#define WMDSPLOGINIT_NOLOGGING(x) 
#define WMDSPLOGCOPYINST(x, inst)
#define WMDSPLOGCLOSE(x) 
#define WMDSPLOGINST(x) 0
#endif 

#define WMDSPDUMP
#define WMDSPDUMPRESET
#define WMDSPDUMPRESETALL

#endif//WMDSPLOGGING_ENABLED

#endif//__WMDSPLOGGING_H__