//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
    /*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    MsAudioDec.h

Abstract:

    Header file for CAudioObjectDecoder.

Author:

    Wei-ge Chen (wchen) 14-July-1998

Revision History:


*************************************************************************/

#ifndef __MSAUDIODEC_H_
#define __MSAUDIODEC_H_

#include <math.h>
#include <limits.h>
#include "stdio.h"

#if defined(ENABLE_ARITHCODER)
    #include "arithcoder_c.h"
#endif //ENABLE_ARITHCODER

#include "msaudio.h"
#include "strmdec_wma.h"

#ifdef ENABLE_ARITHCODER
    #include "arithdecoder_c.h"
#endif //ENABLE_ARITHCODER

#ifdef _X86_
#undef _X86_
#define _X86_ 1
#endif
#include "wmaltrt.h"
//typedef struct LtRtDownmix LtRtDownmix;

#include "wmadec.h"
#ifdef WMA_COMPRESSION_TOOL
#include "wmacmpt.h"
#endif //WMA_COMPRESSION_TOOL
#ifdef BUILD_UES
#include "uesdec.h"
#endif

//
//ARM specific optimization
//
#ifdef WMA_TARGET_ARM
#include <arm_flags.h>
#endif //WMA_TARGET_ARM

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPROLBRV2)
#include "baseplusdecpro.h"
#endif



//#include "com_wmsglobal.h"
//#include "com_wmsdefines.h"
//#include "wmsdec.h"
typedef struct CSpeechObjectDecoder CSpeechObjectDecoder;
typedef enum {BEGIN_PACKET, SEEK_TO_NEXT_PACKET, BEGIN_FRAME, FRAME_HDR, BEGIN_SUBFRAME, DECODE_SUBFRAME,
    DECODE_STUFFINGBITS, DECODE_TRAILERBIT, END_SUBFRAME1, END_SUBFRAME2} DecodeStatus;
typedef enum {FHDR_DONE, FHDR_SIZE, FHDR_PREV, FHDR_CURR, FHDR_PPXFORM, FHDR_DRC_PARAM,
    FHDR_SILENCE, FHDR_SILENCE_LEAD_FLAG, FHDR_SILENCE_LEAD, FHDR_SILENCE_TRAIL_FLAG, 
    FHDR_SILENCE_TRAIL, FHDR_ADJUST_TIMESTAMP} FHdrDecodeStatus; 
typedef enum {SUBFRM_HDR, SUBFRM_COEFDEC_LOSSY, SUBFRM_COEFDEC_MLLM,
    SUBFRM_COEFDEC_PLLM, SUBFRM_REC_MLLM, SUBFRM_REC_LOSSY, SUBFRM_REC_PLLM,
    SUBFRM_SAVE_PREV, SUBFRM_DONE} SubFrmDecodeStatus;
typedef enum {HDR_SIZE, HDR_RAWPCM, HDR_SEEKABLE, HDR_INTERCH_DECORR, HDR_QUANT,
    HDR_V3_QUANT_MODIFIER, HDR_NOISE1, HDR_NOISE2, HDR_MSKUPD, HDR_BARK, HDR_DONE,
    HDR_V3_ESCAPE, HDR_V3_ESCAPE_SKIPDATA, HDR_V3_FREQEX_DATA, HDR_V3_LLM, HDR_V3_CHXFORM, HDR_INFO_SEEKABLE_BEGIN, 
    HDR_DO_ACFILTER, HDR_ENTROPY_CODING, HDR_INTERCH_DECORR_MCLMS, 
    HDR_ACFILTER_ORDER, HDR_ACFILTER_SCALING, HDR_ACFILTER, HDR_MCLMS_ORDER, HDR_MCLMS_SCALING, HDR_MCLMS_SEND,
    HDR_MCLMS_COEFF_BITS, HDR_MCLMS_COEFF_A,HDR_MCLMS_COEFF_B,
    HDR_CDLMS_SEND, HDR_V3_VECCODER_POSEXIST, HDR_V3_VECCODER_POS,
    HDR_V3_POWER, HDR_FILTERS_PARA, HDR_RES_MEM_SCALING, HDR_QSTEPSIZE_B4_PLLM, HDR_V3_RAWPCM_LLM, 
    HDR_V3_LPC_ORDER, HDR_V3_LPC_UNIFIED,
    HDR_PURE_IN_MLLM_SEEKABLE, HDR_PURE_IN_MLLM, HDR_PURE_IN_MLLM_FIRST_FRM, HDR_PURE_IN_MLLM_LAST_FRM, 
    HDR_MLLM_FILTER, HDR_V3_LPC_UNIFIED_SCALING, HDR_MLLM_QUANT_STEPSIZE, HDR_V3_LPC_UNIFIED_INTBITS,
    HDR_V3_LPC_COEF,
    HDR_V3_POWER_LLM, HDR_MLTCHL_MIX_SEQ, HDR_PADDED_ZEROS, HDR_PADDED_ZEROS_B, HDR_V2_POWER} HdrDecodeStatus; //and a lot more
typedef enum {HDRFLT_CLMS_AMOUNT, HDRFLT_CLMS_ORDERS, HDRFLT_CLMS_SCALINGS, HDRFLT_CLMS_COEFF}HdrDecodeFltParStatus;
typedef enum {HDRFLT_CLMS_COEFFS_SENT, HDRFLT_CLMS_COEFFS_SENTBITS, HDRFLT_CLMS_COEFFS_VALUE}HdrDecodeFltParCDLMSStatus;
typedef enum {VLC, FRAME_END, NORMAL, ESCAPE, TBL_INDEX, ESCAPE_LEVEL, ESCAPE_RUN} RunLevelStatus;
typedef enum {CHXFORM_BEGIN, CHXFORM_LEVEL, CHXFORM_CHGRP, CHXFORM_XFORM_ANGLES,
    CHXFORM_XFORM_SIGNS, CHXFORM_XFORMONOFF0, CHXFORM_XFORMONOFF1, CHXFORM_XFORMONOFF_DONE,
    CHXFORM_CONTINUED, CHXFORM_DONE} ChXformStatus;
typedef enum {PPXFORM_BEGIN, PPXFORM_ONOFF, PPXFORM_GENERIC, PPXFORM_COEF, PPXFORM_DONE} PPXformStatus;
//V3 LLM. Chao. Added.
typedef enum {CH_BEGIN, CH_LSP_LPCMODE, CH_TRANSIENT, CH_TRANSIENT_POS, CH_LSP_DIVISOR, CH_LSP_COEF, CH_LPC_COEF, CH_DIVISOR_WIDTH, CH_INIT_ARITHDECODER, CH_DIVISOR, CH_COEF, CH_DONE} LLMDecodeCoefStatus;
typedef enum {FIRST_PART, FIRST_PART_B, FIRST_PART_C, SECOND_PART} ColombDecodeStatus;
typedef enum {FIRSTSPL_SIGN_BIT, FIRSTSPL_OTHER_BITS} Decode1stSplStatus;

typedef enum {LargeValBitCnt, LargeVal8, LargeVal16, LargeVal24,
              LargeVal32_1, LargeVal32_2} LargeValDecodeStatus;

typedef enum {TABLE_INDEX,
              GET_VEC4, GET_VEC2, GET_VEC1, GET_ESC_VEC1, GET_SIGN4,
              GET_VEC4SMALL, GET_VEC2SMALL, GET_VEC1SMALL, DECODE_RLSMALL,
              FREQADAPTIDX_4D, FREQADAPTIDX_2D, FREQADAPTIDX_1D,
              FREQADAPTIDX_RL,
              DECODE_NONRL,
              DECODE_RL,
              DECODE_ESC_RLRUN,
              DECODE_ESC_RLLEVEL,
              DECODE_ESC_RLSIGN} VecDecodeStatus;


//#define _WMA_COUNT_CPU_CYCLES_IF_REGKEY_
#ifdef _WMA_COUNT_CPU_CYCLES_IF_REGKEY_

typedef enum{
    CCS_ibstrmAttach,
    CCS_audecDecode,
    CCS_audecGetPCM,
    CCS_audecDecodeInfo,
    CCS_audecDecodeData,
    CCS_NUM_FUNS
} CCSID;

typedef struct _CCSPerFunStruct {
    I64 iCurStartCycles;
    I64 iCurFrmCycles;
    I64 iTotalCycles;
    I64 iMaxFrmCycles;
    I32 iMaxPos;
    Bool fIn;
} CCSPerFunStruct;

typedef struct _CCSStruct {
    Bool fEnabled;
    Bool fDirty;
    I32 iFrmCount;
    I64 iMaxOverallFrmCycles;
    I32 iOverallMaxPos;
    WMAFormat Format;
    CCSPerFunStruct fns[CCS_NUM_FUNS];
} CCSStruct;

#endif

typedef struct WmaGetDataParam
{
    CBDATA  m_dwUser;
    Bool m_fTimeIsValid;
    I64  m_iTime;
} WmaGetDataParam;

typedef struct PerChannelInfoDEC
{
    // For V3 decoding.
    Bool               m_fVisited;
    Bool               m_fMaskHeaderDone;
} PerChannelInfoDEC;

typedef struct DecRunLevelVecState
{
  VecDecodeStatus getState;
  LargeValDecodeStatus getLargeState;
  Int vecIdx;
  Int curRun;
  Int trip;
  Int vec[4];
  Int sgn[4];
  Int symbol;
  Int cVecsInNonRLMode;
  Int iBark;
  Int iCoeff;
  Int iEscVal4d;
  Int iEscVal2d;
  Int iEscVal1d;
  Int iEscValRL;
  Int iLastSwitchPt[4];
  Int nTbls[4];
  Int iTblIdx[4];
  Int iVecType;
  RlcTblType rlctt;
  const U16 *huffDecTbl4d;
  const U16 *huffDecTbl2d;
  const U16 *huffDecTbl1d;
  const U16 *huffDecTblRL;
  const U16 *smallHuffDecTblRL;
  const U16 *uSymToVec4;
  const U8  *uSymToVec2;
  const U16 *smallSymLeafRunLevelToRun;
  const U16 *smallSymLeafRunLevelToLevel;
} DecRunLevelVecState;

typedef struct CAudioObjectDecoder 
{
    CAudioObject* pau;
    own PerChannelInfo* m_rgpcinfo; //this is just a pointer now
    own PerChannelInfoDEC* m_rgpcinfoDEC;
    
    //packetization stuff
    Bool  m_fPacketLoss;
    I16   m_cFrmInPacket;
    I16   m_cSeekableFrmInPacket; // for LLM. do we have seekable frm in this packet?
    Bool  m_bGotValidFilterInfo; // Have we decoded valid LMS filter info?
    U8*   m_pbSrcCurr;  //ptr to src of curr packet, only for non-strm mode
    U16   m_cbSrcCurrLength; //only for non-strm mode
    DecodeStatus       m_decsts;
    SubFrmDecodeStatus m_subfrmdecsts;
    HdrDecodeStatus    m_hdrdecsts;
    HdrDecodeFltParStatus m_hdrdecFilterParasts;
    HdrDecodeFltParCDLMSStatus m_hdrdecFilterParaCLMSsts;
    FHdrDecodeStatus   m_fhdrdecsts;
    RunLevelStatus     m_rlsts;
    I32                m_iSubfrmEscDataBits;

    Int                m_cBitSeekToNextPacket;
    U32                m_cBitsOverCurrPkt;

    // V3 LLM. Chao. Added.
    LLMDecodeCoefStatus m_LLMdecsts;    
    ColombDecodeStatus  m_Colombdecsts;
    Decode1stSplStatus  m_Dec1stSplsts;
    Bool               m_1stSplSignBit;

    // V3 stuff
    ChXformStatus      m_chxformsts;
    Int                m_cChannelsLeft;
    Bool               m_fDecodingSuperGroupXform;
    Int                m_cAngles;
    Int                m_cSigns;
    Int                m_iAngle;
    Int                m_iSign;
    __in_bound Int     m_cChannelGroup;
    own CChannelGroupInfo *m_rgChannelGrpInfo; 
    RunLevelStatus     m_maskrlsts;
    Bool               m_fTileAligned;
    Int                m_cBitQuantStepModifierIndex;
    Int                m_iQuantStepSign;
    Bool               m_fQuantStepEscaped;

    // WMA Voice related 
    U8  m_cbWMAV_Version;

    // V3 LLM. Chao. Added. more varibles to record decoder status for supporting decoder onhold/resume.
    I8                 m_iCurrPart;            //which part we are doing
    I16                m_iLMSCurrCoeff;
    I16                m_iCurrLPCCoef; //which lpc filter coefficient we are doing.

    // Common to V2, V3
    I16                m_iChannel;  //current channel we are doing
    I16                m_iBand;     //current band we are doing
    I16                m_iTtlNTBs;
    Bool               m_fNewTimeBase;
    Bool               m_fContinuousDecodeAdj;
    Bool               m_iContinuousDecodeCountdown; // Countdown to first packet w/ continuous adj
    I64                m_iNewTimeBase;//in 100nano second
    I64                m_iNewTimeBaseTemp;// The second (later one) NewTimeBase.
    I64                m_iCurrPresTime;//in samples

    own U8**           m_rgpiRecon; // Used to manage recon pointers in audecGetPCM

    // iCurrReconCoef is in pau.
    U16                m_iDivisorWidth;
    U32                m_iResQ;
    U32                m_iResQBits;
    U32                m_iRem;
#if defined ENABLE_ARITHCODER
    // V3 LLM (LLMB) Chao. Arithmetic coding.
    ArithDecoder       *m_pArithDecLLM;
    ArithCoderModel    *m_pACModelLLM;
#endif //ENABLE_ARITHCODER
    Void (* pprvDecLMSPredictor)(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);

    Bool               m_fLastSubFrame;
    I16                m_iCurrTile;
    CWMAInputBitStream m_ibstrm;
    I16                m_cMaxRun;
    I16                m_iMaxLevelInVlc;

#ifdef ENABLE_EQUALIZER
#define MAX_NO_EQBAND 10
    Float       m_rgfltEqBandWeight[MAX_NO_EQBAND];
    U16         m_rgwEqBandBoundary[MAX_NO_EQBAND + 1];
    I8          m_cEqBand;
    I8          m_rgbBandPower[MAX_NO_EQBAND];
    Bool        m_fComputeBandPower;
    Int         m_iEqFrameSize;
#endif // ENABLE_EQUALIZER

#if defined(SEEK_DECODE_TEST)
    tRandState *m_pSaveRandState;
#endif // SEEK_DECODE_TEST

    // INTERPOLATED_DOWNSAMPLE
    Bool    m_fUpsample2x;
    Bool    m_fLowPass;             // Specify independently of downsampling
    Bool    m_fResample;          // Eg, Downsample 32kHz output to 22kHz for some devices
    Int     m_iInterpolSrcBlkSize;  // Size of 1 indivisible source block
    Int     m_iInterpolDstBlkSize;  // Size of 1 indivisible destination block

    Int     m_iDstSamplingRate;
    Int     m_iInterpolCurPos;
    I32       *m_iPriorSample;
    PCMSAMPLE *m_iLastSample;

    // Channel & sample downsampling at playback time
    Bool       m_fChannelFoldDown;      // Eg, from 5.1 to 2 channels or 7.1 to 5.1
    Bool       m_fReQuantizeTo16;      // Eg. from 3 bytes to 2 bytes/sample
    Int        m_cDstChannel;          // Destination channels
    U32        m_nDstChannelMask;      // Destination channel mask
    U32        m_nDstBytePerSample;    // Destination resolution, bytes per sample
    Bool       m_bAuthorControlledChDnMixMtx; // Did user specify channel downmix matrix?
    Int        m_cDstChannelInChDnMixMtx;    // This will be equal to m_cDstChannel in all cases except for 
                                             // LtRt folddown where it will be equal to LTRT_SRC_CHANNELS
    ChDnMixType**    m_rgrgfltChDnMixMtx;    // user specified, or automatically generated?
    Float**          m_rgrgfltChDnMixMtxTmp; // Used in generation of default matrices
    PCMSAMPLE* m_rgpcmsTemp;           // Used in channel down mixing, of size cChannel: can be shared for other uses.
    CoefType* m_pctTemp; // Used in sample places as m_rgpcmsTemp, shares memory with m_rgpcmsTemp, so no real allocation here (i.e. DO NOT FREE THIS!!)
    CoefType** m_rgpctTemp; // Array of pointers to CoefType buffer
    CBT**      m_ppcbtTemp; //
    U16        m_nDstValidBitsPerSample;
    Float      m_fltChannelFoldDownGain;   // Gain factor used to boost folded down channels. Used in channel downmixing and drcControl.

    Bool m_bPlusV2Init;
    CWMAInputBitStream *m_pibsPlus;
    Int m_iFexByteCnt;
    Bool m_bIgnoreFreqexThroughRegistry;// To use in all audecGetPCM calls

    Bool m_bSkipPlus;

    Bool m_fLtRtDownmix;
    Bool m_fLtRtDownmixNonnormal;
    LtRtDownmix *m_pLtRtDownmix;
    Int m_cLtRtBufSize;

    // Post-processing channel transform at playback time
    PPXformStatus     m_ppxformsts;
    Bool              m_fPostProcXform;
    Bool              m_fGeneralPostProcXform; // as opposed to pre-defined
    ChPPXFormType*    m_rgfltPostProcXform;
    Int               m_iPPXformIndex;  // to iterate over all coefs
    Int*              m_rgiPostProcBuf; // temporary buffer.

    Bool              m_fPostProcXformPrev;    // Status in previous frame
    ChPPXFormType*    m_rgfltPostProcXformPrev;// Status in previous frame
    ChPPXFormType*    m_rgfltPostProcXformBlend;// Blend of previous and current transform
    
    // Dynamic range compression at playback time
    Bool    m_fDRC;                 // Perform DRC - either filewise or dynamic
    WMAPlayerInfo m_wmapi;

    WMARESULT (*m_pfnDecodeSubFrame) (struct CAudioObjectDecoder* paudec);
    WMARESULT (*m_pfnDecodeCoefficient) (struct CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo);   
    Void      (*m_pfnResetEntropyCoder)(struct CAudioObjectDecoder *paudec);

    DecRunLevelVecState m_decRunLevelVecState;

    audecState m_externalState; // which public function should be called next
    Bool m_fNeedHeader;
    U32 m_cSamplesReady;
    Bool m_fSPDIF;
    Bool m_fSPDIFStyleGetPCM;
#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder related.
    Bool m_fWriteMetaFile;
    const char * m_pMetaFileDir;
    Bool m_fDumpMetaData;
    Bool m_fParsingOnly;
    I32 m_fFrameBitsReady;
    I32 m_ulCurrSeekPoint;
#endif //WMA_COMPRESSION_TOOL

#ifdef TEST_VRHEADPHONE
    PCMFormat m_fmtI;
    PCMFormat m_fmtO;
    Void * m_pVRHPhone;
#endif //TEST_VRHEADPHONE

#ifdef _WMA_COUNT_CPU_CYCLES_IF_REGKEY_
    CCSStruct m_CCSStruct;
#endif
    // UES
#ifdef BUILD_UES
    enum UES_DEC_INIT_FLAG  m_iUESInitFlag;
    CUESObjectDecoder *m_pCUESdec;
#endif

#ifdef BUILD_WMAPROLBRV2
    Bool m_fDecodingBPlus;      // is decoder decoding bplus layer now? control ibstrm.
#endif //BUILD_WMAPROLBRV2

                                // Is the current frame broken? (bit stream corruption)
    Bool m_bBrokenFrame;        // This determines whether the call to GetPCM should be made
                                // Impacts only scenarios where GetPCM is called with a small buffer.

    WMARESULT (*m_pprvNewInputBuffer)(CAudioObjectDecoder *paudec, audecInputBufferInfo *pBuf);

} CAudioObjectDecoderXXX;

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

#ifdef ENABLE_EQUALIZER         
WMARESULT audecSetEqualizer (CAudioObjectDecoder* paudec, Int iBand, Int iGainIndB);
WMARESULT audecResetEqualizer (CAudioObjectDecoder* paudec);  
Void    audecStartComputeBandPower (CAudioObjectDecoder* paudec);
Void    audecStopComputeBandPower (CAudioObjectDecoder* paudec);
WMARESULT audecGetBandPower (CAudioObjectDecoder* paudec, I8* rgbBandPower);
#endif //ENABLE_EQUALIZER
#ifdef __cplusplus
}
#endif

INLINE
Int audecGetNoiseSubUsed(CAudioObjectDecoder *paudec)
{
    return paudec->pau->m_fNoiseSub;
}

//streaming decoding interface
WMARESULT prvDecodeInfo (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeData (CAudioObjectDecoder* paudec, U16* pcSampleReady,
                           I16* pcSampleSeekAdj);

WMARESULT prvDecodeFrameHeader (CAudioObjectDecoder* paudec);

Void prvResetRunLevelState(CAudioObjectDecoder *paudec);

WMARESULT prvDecodeSubFrame (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSubFrameHighRate (CAudioObjectDecoder* paudec);

WMARESULT prvDecodeSubFrameHeader (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSubFrameHeaderLpc (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSubFrameHeaderNoiseSub (CAudioObjectDecoder* paudec);
WMARESULT prvGetNextRunDEC (Void* pvoid, PerChannelInfo* ppcinfo);
WMARESULT prvGetNextRunDECVecTableIndex(Void*           pobjin, 
                                        PerChannelInfo* ppcinfo);
WMARESULT prvGetNextRunDECVecNonRL(Void*           pobjin, 
                                   PerChannelInfo* ppcinfo);
WMARESULT prvGetNextRunDECVecRL(Void*           pobjin, 
                                PerChannelInfo* ppcinfo);
WMARESULT prvGetNextRunDECVecNonRLV4(Void*           pobjin, 
                                     PerChannelInfo* ppcinfo);
WMARESULT prvGetNextRunDECVecRLV4(Void*           pobjin, 
                                  PerChannelInfo* ppcinfo);
Void prvResetVecCoder(CAudioObjectDecoder *paudec);
#define AUINV_RECON_CHANNEL
#define AUINV_RECON_CHANNEL_DEC
#include "msaudiotemplate.h"
#undef AUINV_RECON_CHANNEL_DEC
#undef AUINV_RECON_CHANNEL

WMARESULT prvNewInputBuffer(CAudioObjectDecoder* paudec, audecInputBufferInfo* pBuf);

WMARESULT prvUpdateSubFrameConfig (CAudioObjectDecoder* paudec, Int iSizeNext);

WMARESULT prvDecodeCoefficientMono  
                (CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo);
WMARESULT prvDecodeCoefficientStereo 
                (CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo);
WMARESULT prvDecodeRunLevel  (CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo,
                              Int iCoefFirst, 
                              Int iCoefLim);
WMARESULT prvDecodeMaskRunLevel  (CAudioObjectDecoder* paudec, 
                                  PerChannelInfo* ppcinfo,
                                  Int iBandLim);
Int prvNumDstSamplesFromXFormSamples(CAudioObjectDecoder *paudec,
                                     Int nTransformSamples);


#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
// ================================ V3 Lossless Start =========================== //
// ------------------------------- Pure Lossless Mode -------------------------- //
WMARESULT prvDecodeSubFramePureLosslessMode (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSubFrameHeaderPureLosslessMode (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSubFrameChannelResiduePureLosslessModeVerA (CAudioObject* pau, CAudioObjectDecoder *paudec,
                                                               PerChannelInfo* ppcinfo);
WMARESULT prvDecodeSubFrameChannelResiduePureLosslessModeVerB (CAudioObject* pau, CAudioObjectDecoder *paudec,
                                                               PerChannelInfo* ppcinfo);
WMARESULT prvDecodeSubFrameChannelRawPCMPureLosslessMode (CAudioObject* pau, CAudioObjectDecoder *paudec,
                                                          PerChannelInfo* ppcinfo);
WMARESULT prvSubFrameRestoreChannelDC(CAudioObject *pau);

// ----------------------------- V3 Unified MLLM or PLLM ------------------------- //
WMARESULT prvDecodeSubFrameChannelResidueMono_Unified_MLLM_Or_PLLM(CAudioObject* pau, CAudioObjectDecoder *paudec,
                                                                   PerChannelInfo* ppcinfo);
WMARESULT prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_Or_PLLM(CAudioObject* pau, CAudioObjectDecoder *paudec,
                                                                       PerChannelInfo* ppcinfo);
WMARESULT prvDecodeSubFrameReconWindowedFrameMono_Unified_PLLM(CAudioObjectDecoder * paudec,
                                                               PerChannelInfo * ppcinfoComm, 
                                                               CBT * rgiCoefRecon, 
                                                               CBT * rgiLPCResidue, 
                                                               I32 iLen);
WMARESULT prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_LPC(CAudioObject * pau,
                                                                   PerChannelInfo * ppcinfoComm, 
                                                                   CBT * rgiCoefRecon, 
                                                                   CBT * rgiLPCResidue, 
                                                                   I32 iLen);
WMARESULT prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_POLY(CAudioObject * pau,
                                                                    PerChannelInfo * ppcinfoComm, 
                                                                    CBT * rgiCoefRecon, 
                                                                    CBT * rgiLPCResidue, 
                                                                    I32 iLen);
WMARESULT prvFixMLLM4HalfTransform (CAudioObject * pau, PerChannelInfo* ppcinfo, CoefType * rgfltCoef);

Void prvLPCFilteringInv(CAudioObject *pau, CBT * rgiCoefRecon, I32 * rgiLPCPrevSamples, CBT * rgiLPCResidue, I32 * rgiLPCFilter, I32 iLen, I16 iOrder);

Void prvDecoderCDLMSPredictorHelper(CAudioObjectDecoder *paudec, PerChannelInfo* ppcinfoComm, PerChannelInfo* ppcinfo, CBT * rgiResidue, I32 iDataLen);

Void prvDecLMSPredictor_I16_C(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
Void prvDecLMSPredictor_I16_MMX(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
Void prvDecLMSPredictor_I32_C(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
#if defined(_WMA_TARGET_XBOX2_) && defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
extern Void prvDecLMSPredictor_I16_C_XENON(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
extern Void prvDecLMSPredictor_I32_C_XENON(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
#endif

#if defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_LOSSLESSDECPROLSL)
extern int mips_use_MIPSII_strict;
extern Void prvDecLMSPredictor_I16_MIPSII(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
extern Void prvDecLMSPredictor_I16_MIPS32(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
extern Void prvDecLMSPredictor_I32_MIPSII(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
extern Void prvDecLMSPredictor_I32_MIPS32(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen);
#endif


// ================================ V3 Lossless End =========================== //

// Common to WMAPRO & both kinds of WMA Lossless
Void prvInitDecodeTileHdr(CAudioObjectDecoder *paudec, ConfigFrame iFrame);
I32 prvDecodeTileHdr(CAudioObjectDecoder* paudec, ConfigFrame iFrame);
#endif // BUILD_WMAPRO || BUILD_WMALSL

//equalize
Void    prvAdaptEqToSubFrame(CAudioObjectDecoder* paudec);
WMARESULT prvEqualize (CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo);
Void    prvComputeBandPower (CAudioObjectDecoder* paudec);

INLINE Void WMA_set_PacketLoss (CAudioObjectDecoder* hWMA, Bool fPacketLoss)
{
    hWMA->m_fPacketLoss = fPacketLoss;
}

INLINE U8 WMA_get_nHdrBits(CAudioObjectDecoder* hWMA)
{
    const CAudioObject *pau = hWMA->pau;
    if (pau->m_iVersion <= 2)
    {
        if (pau->m_fAllowSuperFrame)
            return (U8) (pau->m_cBitPackedFrameSize + NBITS_FRM_CNT + NBITS_PACKET_CNT + 3);
        else 
            return 0;
    }
    else 
    {
        if (pau->m_fExtraBitsInPktHeader)
            return (U8) (pau->m_cBitPackedFrameSize + NBITS_PACKET_CNT + NBITS_PACKET_EMPTYNESS + NBITS_FORCE_PACKETLOSS + 11) ;
        else
            return (U8) (pau->m_cBitPackedFrameSize + NBITS_PACKET_CNT + NBITS_PACKET_EMPTYNESS + NBITS_FORCE_PACKETLOSS) ;
    }
}

void prvInterpolateInit(CAudioObjectDecoder *paudec, Int iSrcSampleRate,
                        Int iDstSampleRate);



#if defined (BUILD_WMAPRO)
// These functions are only needed for WMA Pro.
WMARESULT prvPrepareResampledMaskV3_Channel(CAudioObject* pau, PerChannelInfo* ppcinfo);

WMARESULT prvInitChDnMix(CAudioObjectDecoder* paudec, I32* rgiMixDownMatrix,
                         Int cSrcChannel, U32 nSrcChannelMask,
                         Int cDstChannel, U32 nDstChannelMask);

WMARESULT prvChannelDownMix (CAudioObjectDecoder *paudec, U8 *piSourceBuffer, Int nBlocks,
                             U8 *piDestBuffer);
WMARESULT prvChannelDownMixFloat (CAudioObjectDecoder *paudec, U8 *piSourceBuffer, Int nBlocks,
                                  U8 *piDestBuffer);
WMARESULT prvChannelDownMixLtRt (CAudioObjectDecoder *paudec, U8 *piSourceBuffer, U16 *pnBlocks,
                                 U8 *piDestBuffer);

// Perform post-processing channel transform
WMARESULT prvPostProcChannelXformV3 (CAudioObjectDecoder* paudec, 
                                     U8 *piDataBuffer, const U16 cSampleReady);

WMARESULT prvInitDecodeDRC(CAudioObjectDecoder *paudec,
                           Int nDRCSetting);
#endif // BUILD_WMAPRO

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
WMARESULT prvRequantizeTo16(CAudioObjectDecoder *paudec, U8 *piSrc, Int nBlocks);

#endif //BUILD_WMAPRO || BUILD_WMALSL

WMARESULT audecPostProcessPrePCM(Void *pDecHandle, U16 *pcSamplesReturned,
                                 U8 *pbDst, U32 cbDstLength);
WMARESULT audecPostProcessPostPCM(Void *pDecHandle, U16 *pcSamplesReturned,
                                  U8 *pbDst, U32 cbDstLength, I16 nDRCSetting);

#ifdef WMA_COMPRESSION_TOOL
// Professional Encoder related
WMARESULT prvWriteMetaFileSubFrmConfig (CAudioObjectDecoder* paudec, PerChannelInfo * ppcinfo, 
                                        ConfigFrame iFrame, LPCSTR pMeteFileName);

// Professional Encoder Related
WMARESULT prvRecordFrameStartInBitStrm (CAudioObjectDecoder * paudec, CWMAInputBitStream * pibstrm);
WMARESULT prvRecordFrameHdrBits (CAudioObjectDecoder * paudec, I32 cFrmHdrBits);
WMARESULT prvWriteMetaFileMask (CAudioObjectDecoder * paudec, I32 iPCMFrameNumber, I16 iCurrTile, LPCSTR pMetaFileName);
WMARESULT prvRecordFrameEndInBitStrm (CAudioObjectDecoder * paudec, CWMAInputBitStream * pibstrm);
WMARESULT prvWriteMetaFileGetCommonFrmHdr (CAudioObjectDecoder * paudec);
WMARESULT prvWriteMetaFileFrameBitsInfo(CAudioObjectDecoder * paudec, LPCSTR pMetaFileName);
WMARESULT prvWriteMetaFileFrameBitsData (CAudioObjectDecoder * paudec, LPCSTR pMetaFileName, I32 iPCMFrameNumber);
WMARESULT prvAddBitsToFrameBitsBuf (void *pDec, U8 * pbSrc, I32 cbSrc, I32 iStart, I32 iEnd);
WMARESULT prvWriteMetaFileTileInfo (CAudioObjectDecoder * paudec, I32 iPCMFrameNumber, I16 iCurrTile, LPCSTR pMetaFileName);
WMARESULT prvWriteMetaFileCHX (CAudioObjectDecoder * paudec, I32 iPCMFrameNumber, I16 iCurrTile, LPCSTR pMetaFileName);
WMARESULT prvWriteMetaFileMDCTCoeffs (CAudioObjectDecoder * paudec, I32 iPCMFrameNumber, I16 iCurrTile, LPCSTR pMetaFileName);

#endif //WMA_COMPRESSION_TOOL

// freqex related
WMARESULT freqexDecodeTile(CAudioObjectDecoder *paudec);
WMARESULT freqexDecInit(CAudioObjectDecoder *paudec);
Void freqexDecFree(CAudioObjectDecoder *paudec);
WMARESULT chexEndDecodeData(CAudioObjectDecoder *paudec, U16 *pcSampleReady);
WMARESULT chexDecodeReconFex(CAudioObjectDecoder *paudec);
Void freqexDecodeTileInit(CAudioObjectDecoder *paudec);
WMARESULT chexDecodeTile(CAudioObjectDecoder *paudec);
#ifdef BUILD_WMAPROLBRV2
WMARESULT   freqexDecodeCodingGlobalParam( CAudioObjectDecoder *paudec, 
                                           Bool fUpdateGrpA, Bool fUpdateGrpB, Bool fUpdateGrpC, Bool fUpdateGrpD );
WMARESULT   freqexDecodeReconGlobalParam( CAudioObjectDecoder *paudec, 
                                          Bool fUpdateGrpA, Bool fUpdateGrpB, Bool fUpdateGrpC, Bool fUpdateGrpD );
WMARESULT   freqexDecodeReconTileConfigV2( CAudioObjectDecoder *paudec );
#ifdef BUILD_WMAPROLBRV3
WMARESULT   freqexDecodeGlobalParamV3( CAudioObjectDecoder       *paudec,
                                       FexGlobalParamUpdateType  iUpdateType );
WMARESULT   freqexDecodeReconTileConfigV3( CAudioObjectDecoder *paudec );

WMARESULT   bpeakDecodeTile_Channel( CAudioObjectDecoder *paudec,
                                     PerChannelInfo *ppcinfo );
Void        bpeakClearPeakCoef( PerChannelInfo *ppcinfo, Int iMaxPeakCoef );
#endif
#endif
#if defined(BUILD_WMAPROLBRV2)
WMARESULT chexDecodeReconFexTile(CAudioObject *pau, ReconTileInfo *prti,
                                 Int iCh);
#endif

#if defined (WMA_OPT_VLC_DEC_ARM) && WMA_OPT_VLC_DEC_ARM
WMARESULT decodeVLC(CAudioObject* pau, Void* pcaller, PerChannelInfo* ppcinfo, I16 iNextBarkIndex, 
                    Int iShift, QuantFloat qfltQuantizer, CoefType ctCoefRecon, I16* piRecon);
#endif

// ==============================================================

#ifdef BUILD_WMAPROLBRV1

WMARESULT plusGetIndex( const CAudioObjectDecoder *paudec,
                          const U16 *pDecTable   , UInt numBits, U32 *puVal,
                          const Int iMinSym    , const Int iMaxSym,
                          const Int cMinSymBits, const Int cMaxSymBits,
                          const Int iExtraBits );
WMARESULT plusGetIndexH( const CAudioObjectDecoder *paudec,
                           U32 *uVal, HuffInfo *phdi);
#endif


#if !defined(WRITE_PLUS_TO_FILE)
#define PLUS_GETDATA(wr, fn) { \
  wr = fn; \
  if (WMA_FAILED(wr)) REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wr); \
}
WMARESULT plusGetMoreData(CAudioObjectDecoder *paudec);
#else
#define PLUS_GETDATA(wr, fn) { \
  while (1) { \
    wr = fn; \
    if (wr == WMA_E_ONHOLD) { TRACEWMA_EXIT(wr, plusGetMoreData(paudec)); } \
    else if (WMA_FAILED(wr)) { REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wr); } \
    else { break; } /* success */ \
  } \
}
#endif

#define PLUS_GETBITS(wr, numBits, puVal) { \
  PLUS_GETDATA(wr, ibstrmLookForBits(paudec->m_pibsPlus, numBits)); \
  TRACEWMA_EXIT(wr, ibstrmGetBits(paudec->m_pibsPlus, numBits, (U32 *)puVal)); \
}

#define PLUS_PEEKBITS(wr, numBits, puVal) { \
  PLUS_GETDATA(wr, ibstrmLookForBits(paudec->m_pibsPlus, numBits)); \
  TRACEWMA_EXIT(wr, ibstrmPeekBits(paudec->m_pibsPlus, numBits, puVal)); \
  *puVal >>= 32-numBits; \
}

#define PLUS_FLUSHBITS(wr, numBits) { \
  ASSERTWMA_EXIT(wr, ibstrmFlushBits(paudec->m_pibsPlus, numBits)); \
}

WMARESULT freqexGet1ofNVals(const CAudioObjectDecoder *paudec,
                            const Int iVals, U32 *puVal);
#ifdef BUILD_WMAPROLBRV3
WMARESULT plusDecodeBasePeak(CAudioObjectDecoder *paudec);
WMARESULT plusDecodeBasePeak_Channel(CAudioObjectDecoder *paudec, PerChannelInfo *ppcinfo);
#endif
#endif  //__MSAUDIODEC_H_
