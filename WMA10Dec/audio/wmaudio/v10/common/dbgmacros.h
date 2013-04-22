//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 2006

Module Name:

    DbgMacros.h

Abstract:

    Debug macros.

Author:

    Hui Gao (huigao)       Sep 06, 2006

Revision History:


*************************************************************************/

#ifndef __DBG_MACROS_H
#define __DBG_MACROS_H

// macros to refresh data after each transform stage to test 
// the integer precision in chex

#if defined(WMA_DECPK_BUILD) && !defined(DBG_CX_STAGES)
#if defined(BUILD_WMAPROLBRV2)  || defined(BUILD_WMAPROLBRV3) \
        || (BUILDCFG_STDPROLBR) || (BUILDCFG_STDPROSTEREOLBR)
//#define DBG_CX_STAGES
#endif
#endif

#if defined(DBG_CX_STAGES)

#include "msaudio.h"
#include "wavfileexio.h"

#define DBG_PCM_MAXDIFF 0
#define DBG_FWDMLT_MAXDIFF 0
#define DBG_RFX_MAXDIFF 0
#define DBG_CX_MAXDIFF 0

#define BUFSIZE 4096

extern TCHAR g_fileNameRef[];
extern TCHAR g_fileNameCan[];
extern Bool g_bEnableStageWiseConf;
extern Bool g_bReferenceDec;

#define ENABLE_PCM          1
#define ENABLE_FWDMLT       1
#define ENABLE_RFX          1
#define ENABLE_CX           0

#define DBG_CX_REFRESH_DECL(SCOPE,TYPE,OP)                      \
    SCOPE TYPE *g_file_PCM_##OP    = NULL;                      \
    SCOPE TYPE *g_file_FWDMLT_##OP = NULL;                      \
    SCOPE TYPE *g_file_RFX_##OP    = NULL;                      \
    SCOPE TYPE *g_file_CX_##OP     = NULL;

#define DBG_CX_HISTBUF_DECL(SCOPE)                              \
    SCOPE CoefType *g_hist_PCM    = NULL;                       \
    SCOPE CoefType *g_hist_FWDMLT = NULL;                       \
    SCOPE CoefType *g_hist_RFX    = NULL;                       \
    SCOPE CoefType *g_hist_CX     = NULL;                       \
    SCOPE CoefType *g_bufRefr     = NULL;                       \
    SCOPE CoefType *g_bufRefr2    = NULL;

#define COEF_SIZE_PCM    (prti->m_iSizeCurr*2)
#define COEF_SIZE_FWDMLT (prti->m_iSizeCurr)
#define COEF_SIZE_RFX    (prti->m_iSizeCurr)
#define COEF_SIZE_CX     (prti->m_iSizeCurr)

#define ISPCM_PCM    (1)
#define ISPCM_FWDMLT (0)
#define ISPCM_RFX    (0)
#define ISPCM_CX     (0)

#define DBG_CX_OPEN_FILE(X,OP,NAME,TYPE)                        \
    if (g_bEnableStageWiseConf)                                 \
    {                                                           \
        g_file_##X##_##OP = _tfopen(NAME, TEXT(TYPE));          \
        assert(g_file_##X##_##OP != NULL);                      \
    }

#define DBG_CX_OPEN_FILE_PCM(X,OP,NAME,TYPE)                    \
    if (g_bEnableStageWiseConf)                                 \
    {                                                           \
        g_file_##X##_##OP = NULL;                               \
        g_file_##X##_##OP = wfioNew();                          \
        assert(g_file_##X##_##OP != NULL);                      \
                                                                \
        if (wfioOpen(g_file_##X##_##OP, NAME, &g_wfx,           \
                 sizeof(g_wfx.Format) + g_wfx.Format.cbSize,    \
                 TYPE)!=0)                                      \
        {                                                       \
            fprintf(stderr, "Can't create file %s \n", NAME);   \
            goto exit;                                          \
        }                                                       \
    }

#define DBG_CX_CLOSE_FILE(X,OP)                                 \
    if (g_bEnableStageWiseConf)                                 \
    {                                                           \
        if (g_file_##X##_##OP != NULL)                          \
            fclose(g_file_##X##_##OP);                          \
    }

#define DBG_CX_CLOSE_FILE_PCM(X,OP)                             \
    if (g_bEnableStageWiseConf)                                 \
    {                                                           \
        if (g_file_##X##_##OP != NULL)                          \
            wfioDelete(g_file_##X##_##OP);                      \
    }


#define DBG_CX_CLOSE_FILES(OP)                                  \
    if (g_bEnableStageWiseConf)                                 \
    {                                                           \
        DBG_CX_CLOSE_FILE(PCM,OP)                               \
        DBG_CX_CLOSE_FILE(FWDMLT,OP)                            \
        DBG_CX_CLOSE_FILE(RFX,OP)                               \
        DBG_CX_CLOSE_FILE(CX,OP)                                \
    }

#define DBG_CX_CLOSE_FILES_PCM(OP)                              \
    if (g_bEnableStageWiseConf)                                 \
    {                                                           \
        DBG_CX_CLOSE_FILE_PCM(PCM,OP)                           \
        DBG_CX_CLOSE_FILE_PCM(FWDMLT,OP)                        \
        DBG_CX_CLOSE_FILE_PCM(RFX,OP)                           \
        DBG_CX_CLOSE_FILE_PCM(CX,OP)                            \
    }

#define DBG_CX_DECL                                             \
    TCHAR g_fileNameRef[1024] = TEXT("C:\\reconRef.wav");       \
    TCHAR g_fileNameCan[1024] = TEXT("C:\\reconCan.wav");       \
    Float g_fMaxAbsDiff = 0;                                    \
    Float g_fMaxAbsDiffThreshold = 0;                           \
    Int g_iMaxAbsDiffIndex = -1;                                \
    Bool g_bEnableStageWiseConf = WMAB_FALSE;                   \
    Bool g_bReferenceDec = WMAB_TRUE;                           \
    WAVEFORMATEXTENSIBLE g_wfx;                                 \
    DBG_CX_HISTBUF_DECL(;)                                      \
    DBG_CX_REFRESH_DECL( ,WavFileIO,PCM)                        \
    DBG_CX_REFRESH_DECL( ,FILE,WRITE)                           \
    DBG_CX_REFRESH_DECL( ,FILE,READ)

#define DBG_CX_OPEN                                    \
    if (g_bReferenceDec)                               \
    {                                                  \
        TRACEWMA_EXIT(wmaResult, DbgRefrOpenRef(pau)); \
    }                                                  \
    else                                               \
    {                                                  \
        TRACEWMA_EXIT(wmaResult, DbgRefrOpenCan(pau)); \
    }

#define DBG_CX_CLOSE          \
    if (g_bReferenceDec)      \
        DbgRefrCloseRef(pau); \
    else                      \
        DbgRefrCloseCan(pau);

#define DBG_CX_REFRESH(X)                   \
    {                                       \
        g_fMaxAbsDiffThreshold =            \
                    DBG_##X##_MAXDIFF;      \
        if (g_bReferenceDec)                \
            DbgRefrRef(pau, ppcinfo, prti,  \
                    bUseDSTRecon,           \
                    iSamples, iCh,          \
                    COEF_SIZE_##X,          \
                    ENABLE_##X,             \
                    ISPCM_##X,              \
                    g_file_##X##_WRITE,     \
                    g_file_##X##_PCM,       \
                    g_hist_##X##);          \
        else                                \
            DbgRefrCan(pau, ppcinfo, prti,  \
                    bUseDSTRecon,           \
                    iSamples, iCh,          \
                    COEF_SIZE_##X,          \
                    ENABLE_##X,             \
                    ISPCM_##X,              \
                    g_file_##X##_READ,      \
                    g_file_##X##_WRITE,     \
                    g_file_##X##_PCM,       \
                    g_hist_##X##);          \
    }

#define PARSE_REFR_ARGS \
{ \
            g_bEnableStageWiseConf = WMAB_TRUE; \
            iArgc++; \
            if (iArgc >= argc) \
            { \
                iError = 1; \
                break; \
            } \
            if (!_tcscmp(argv[iArgc], TEXT("ref"))) \
            { \
                g_bReferenceDec = WMAB_TRUE; \
            } \
            else if (!_tcscmp(argv[iArgc], TEXT("can"))) \
            { \
                g_bReferenceDec = WMAB_FALSE; \
                iArgc++; \
                if (iArgc >= argc) \
                { \
                    iError = 1; \
                    break; \
                } \
                assert(_tcslen(argv[iArgc]) < 1000); \
                _tcscpy(g_fileNameRef, argv[iArgc]); \
            } \
            else \
            { \
                iError = 1; \
                break; \
            } \
}

#define COPY_REFR_FILENAME(szOutputName) \
if (g_bEnableStageWiseConf) \
{ \
    assert(_tcslen(szOutputName) < 1000); \
    if (g_bReferenceDec) \
        _tcscpy(g_fileNameRef, szOutputName); \
    else \
        _tcscpy(g_fileNameCan, szOutputName); \
}

#else   // DBG_CX_STAGES

#define DBG_CX_DECL
#define DBG_CX_OPEN
#define DBG_CX_CLOSE
#define DBG_CX_REFRESH(X)

#endif //DBG_CX_STAGES

#endif //__DBG_MACROS_H
