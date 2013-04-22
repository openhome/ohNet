//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains the logic common to WMA Pro & WMA Lossless decoders.
// Not needed for WMA Std decoding.
//*@@@---@@@@******************************************************************

#include "msaudiodec.h"
#include "huffdec.h"
#include "AutoProfile.h"  
#include "entropydec.h"

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)

//#define DEBUG_DECODE_TRACE
#undef DEBUG_DECODE_TRACE
#if defined (DEBUG_DECODE_TRACE)
extern unsigned int g_ulOutputSamples;
#define DEBUG_TRACE_QUANT(a, b, c)                                              \
                WMAPrintf("%d %d %d %u\n", a, b, c, g_ulOutputSamples);                                  \
                FFLUSH (stdout);
#pragma COMPILER_MESSAGE(__FILE__ "(43) : Warning - m_iQuantStepSize Debug Code Enabled.")
#else
#define DEBUG_TRACE_QUANT(a, b, c)
#endif

#if defined (_DEBUG)
#define COUNT_BITS(a,b) a += b
#else
#define COUNT_BITS(a,b)
#endif


WMARESULT prvDecodeTrailerBit (CAudioObjectDecoder* paudec)
{
    WMARESULT   wmaResult = WMA_OK;
    I32 iResult;
    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
    paudec->m_cFrmInPacket = (I16) iResult;

exit:    
    return wmaResult;
} // prvDecodeTrailerBit

void prvInitDecodeTileHdr(CAudioObjectDecoder *paudec, ConfigFrame iFrame)
{
    Int iCh;
    CAudioObject* pau = paudec->pau;
    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        PerChannelInfo*     ppcinfo       = pau->m_rgpcinfo + iCh;
        SubFrameConfigInfo* psubfrmconfig = &(ppcinfo->m_rgsubfrmconfig[iFrame]);

        psubfrmconfig->m_cSubFrame = 0;
        psubfrmconfig->m_rgiSubFrameStart[0] = 0;
    }
}

//sigular case#1: all tiles agligned; skip ch mask
//sigular case#2: 1 tile left, size is mininum; implied, skip ch. mask & size
//sigular case#3: 1 ch possible; skip ch. mask
I32 prvDecodeTileHdr(CAudioObjectDecoder* paudec, ConfigFrame iFrame)
{
    CAudioObject*       pau           = paudec->pau;
    PerChannelInfo*     ppcinfo       = NULL;
    SubFrameConfigInfo* psubfrmconfig = NULL;
    WMARESULT           wmaResult     = WMA_OK;

    Int iSubFrm;
    I16 iCh;
    I16 iStartMin     = 0; 
    I32 cBitSize = 0, cBitSize0 = 0, cBitSize1 = 0;
    I32 cSampleLeft   = pau->m_cFrameSampleHalf * pau->m_cChannel;

    if (pau->m_iMaxSubFrameDiv == 1)
    {
        // Trivial case: no bitstream decoding is necessary.
        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
        {
            ppcinfo        = pau->m_rgpcinfo + iCh;        
            psubfrmconfig= &ppcinfo->m_rgsubfrmconfig [iFrame];
            psubfrmconfig->m_rgiSubFrameSize[0]  = (I16) pau->m_cFrameSampleHalf;
            psubfrmconfig->m_rgiSubFrameStart[0] = 0;
            psubfrmconfig->m_cSubFrame           = 1;
        }
        return wmaResult;
    }

    assert (pau->m_iMaxSubFrameDiv > 1);        //avoid log(0) below
    if (pau->m_bPureLosslessMode == WMAB_FALSE) 
    {
        if (pau->m_iMaxSubFrameDiv == 4)
        {
            cBitSize0 = 1; //0, 
            cBitSize1 = 1; //1 + 0, 1
        }
        else if (pau->m_iMaxSubFrameDiv == 16)
        {
            cBitSize0 = 1; //0, 
            cBitSize1 = 2; //1 + 00, 01, 10, 11
        }
        else //2: just 0, 1; 8; 00, 01, 10, 11; 64 and above: will be holes
        {
            I16 cWin = (I16) LOG2(pau->m_iMaxSubFrameDiv) + 1;
            cBitSize1 = LOG2 (cWin - 1) + 1;
            cBitSize0 = 0;
        }       
        cBitSize = cBitSize0 + cBitSize1;
    }
    else // pau->m_bPureLosslessMode == WMAB_TRUE
    {
        cBitSize = LOG2 (pau->m_iMaxSubFrameDiv - 1) + 1;
    }

    //init subfrm start and counter
    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        ppcinfo        = pau->m_rgpcinfo + iCh;        
        psubfrmconfig  = &(ppcinfo->m_rgsubfrmconfig [iFrame]);

        for (iSubFrm=0; iSubFrm < psubfrmconfig->m_cSubFrame; iSubFrm++)
        {
            cSampleLeft -= psubfrmconfig->m_rgiSubFrameSize[iSubFrm];
        }
    }

    while (cSampleLeft > 0) 
    {
        Bool fSkipChMsk = WMAB_FALSE;
        Bool fSkipSize  = WMAB_FALSE;
        I16  iSizeTile = (I16) (pau->m_cFrameSampleHalf / pau->m_iMaxSubFrameDiv);
        U32 iResult = 0, iResultS = 0;
        I32 cBitChMsk = 0;
        U64 iChMsk = 0;
        I32 cSampleLeftSav = cSampleLeft;
        TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, pau->m_cChannel + cBitSize + 1));

        //only get at the beginning of the tile hdr
        //singular case #1
        if (cSampleLeft  == pau->m_cFrameSampleHalf * pau->m_cChannel)
        {
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            if (iResult != 0)
                paudec->m_fTileAligned = WMAB_TRUE;
            else 
                paudec->m_fTileAligned = WMAB_FALSE;
        }

        //search for tile starting position
        ppcinfo = pau->m_rgpcinfo;
        iStartMin = (I16) pau->m_cFrameSampleHalf;
        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
        {            
            I16* piStart;
            psubfrmconfig = &(ppcinfo->m_rgsubfrmconfig [iFrame]);
//            piStart       = psubfrmconfig->m_rgiSubFrameStart + psubfrmconfig->m_cSubFrame;
            piStart       = psubfrmconfig->m_rgiSubFrameStart;
            
            if (iStartMin > *piStart)
            {
                iStartMin = (I16) *piStart;
            }
            ppcinfo++;
        }

        if (paudec->m_fTileAligned == WMAB_FALSE) //only when not aligned
        {
            //search for possible ch in tile
            iResult = 0;
            ppcinfo   = pau->m_rgpcinfo;
            for (iCh = 0; iCh < pau->m_cChannel; iCh++)
            {
                I16* rgiStart;
                I16* piSubFrmCurr;

                psubfrmconfig= &ppcinfo->m_rgsubfrmconfig [iFrame];
                rgiStart     = psubfrmconfig->m_rgiSubFrameStart;
                piSubFrmCurr = &psubfrmconfig->m_cSubFrame;
        
                //possibly a ch in tile
//                if (iStartMin == rgiStart [*piSubFrmCurr])
                if (iStartMin == *rgiStart)
                {
                    cBitChMsk++;
                    iResult = 1; //if cBitChMsk is 1, iResult stays at 1.
                }
                ppcinfo++;
            }
            assert (cBitChMsk <= 32);
            if (cBitChMsk <= 1)  //singular case #3
            {
                fSkipChMsk = WMAB_TRUE;
            }
        }
        else 
        {
            fSkipChMsk = WMAB_TRUE;
            cBitChMsk = pau->m_cChannel;    //sigular case #1
        }
        if (cSampleLeft / cBitChMsk == iSizeTile)
        {
            //#sigular case #2
            fSkipChMsk = WMAB_TRUE;
            fSkipSize  = WMAB_TRUE;
        }

        iChMsk = 0xFFFFFFFFFFFFFFFFULL;
        if (!fSkipChMsk)        //singular case #3
        {
            I32 cBitLeft = cBitChMsk;
            I32 cBitGet = min (24, cBitChMsk);
            iChMsk = 0;
            while (cBitLeft != 0)
            {
                U32 iResultT;
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBitGet, &iResultT));
                iChMsk |= iResultT;
                cBitLeft -= cBitGet;
                cBitGet = min (24, cBitLeft);
                iChMsk = iChMsk << cBitGet;
            }
        }
       
        if (!fSkipSize)
        {
            //get tile size        
            if (cBitSize0 == 0)
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBitSize, &iResultS));
            }
            else 
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBitSize0, &iResultS));
                if (iResultS >= (U16) cBitSize0)
                {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBitSize1, &iResultS));
                    iResultS += cBitSize0;
                }
            }
            if (pau->m_bPureLosslessMode == WMAB_FALSE) 
                iSizeTile = (I16)(pau->m_cFrameSampleHalf / (1 << iResultS));
            else 
                iSizeTile = (I16)((iResultS + 1) * (pau->m_cFrameSampleHalf / pau->m_iMaxSubFrameDiv));
        }

        if (iSizeTile < pau->m_cMinSubFrameSampleHalf || iSizeTile > pau->m_cFrameSampleHalf)
        {
            //impossible case; bit error
            wmaResult = WMA_E_BROKEN_FRAME;
            REPORT_BITSTREAM_CORRUPTION();
            CHECKWMA_EXIT(wmaResult);
        }
#if 0
if (pau->m_iFrameNumber < 10)
{
WMAFprintf(stderr, "%d %d    \n", pau->m_iFrameNumber, iSizeTile);
FFLUSH(stderr);
}
#endif
        ppcinfo   = pau->m_rgpcinfo;
        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
        {
            I16* rgiSize;
            I16* rgiStart;
            I16* piSubFrmCurr;

            psubfrmconfig= &ppcinfo->m_rgsubfrmconfig [iFrame];
            rgiSize      = psubfrmconfig->m_rgiSubFrameSize;
            rgiStart     = psubfrmconfig->m_rgiSubFrameStart;
            piSubFrmCurr = &psubfrmconfig->m_cSubFrame;
            
            //extra safe to BO of m_rgiSubFrameSize & m_rgiSubFrameStart
            if (*piSubFrmCurr > MAX_SUBFRAMES)
            {
                REPORT_BITSTREAM_CORRUPTION();
                wmaResult = WMA_E_BROKEN_FRAME;
                CHECKWMA_EXIT(wmaResult);
            }
            //possibly a ch in tile
//            if (iStartMin == rgiStart [*piSubFrmCurr])
            if (iStartMin == *rgiStart)
            {
                cBitChMsk--;
                if ((iChMsk & ((U64)0x01 << cBitChMsk)) != 0)
                {    
                    if (*piSubFrmCurr >= MAX_SUBFRAMES) {
                        // Buffer overrun situation: should have been caught earlier, but for safety.
                        REPORT_BITSTREAM_CORRUPTION();
                        wmaResult = WMA_E_BROKEN_FRAME;
                        CHECKWMA_EXIT(wmaResult);
                    }
                    rgiSize [*piSubFrmCurr] = iSizeTile;
                    (*piSubFrmCurr)++;

//                    rgiStart [*piSubFrmCurr] = iSizeTile + rgiStart [(*piSubFrmCurr) - 1];                                                    
                    *rgiStart += iSizeTile;
                    cSampleLeft -= iSizeTile;

                    //tile shouldn't overlapp & each channel should span exactly m_cFrameSampleHalf.
                    if (cSampleLeft < 0 || *rgiStart > pau->m_cFrameSampleHalf)
                    {
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    }
                }
            }
            ppcinfo++;
        }
        assert (cBitChMsk == 0);

        if (cSampleLeft >= cSampleLeftSav) //this tile must have non-0 samples
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
    }
    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        ppcinfo       = pau->m_rgpcinfo + iCh;
        psubfrmconfig = &(ppcinfo->m_rgsubfrmconfig[iFrame]);

        psubfrmconfig->m_rgiSubFrameStart[0] = 0;
    }
exit:  
    return wmaResult;
} // prvDecodeTileHdr


#ifdef WMA_COMPRESSION_TOOL
//
//  Generate meta file of subframing configuration.
//

WMARESULT prvWriteMetaFileSubFrmConfig (CAudioObjectDecoder* paudec, PerChannelInfo * rgpcinfo, ConfigFrame iFrame, LPCSTR pMetaFileName)
{
    WMARESULT wmaResult = WMA_OK;
#ifndef WMA_COMPTOOL_NODUMPING

    CAudioObject * pau = paudec->pau;
    PerChannelInfo * ppcinfo;
    I16 iCh;
    FILE * fp;
    I32 iPCMFrameNumber;
    I16 iSubFrm;                    
    I16 cSubFrm;
    I16 *piSubFrmSize;
    char fileName[_MAX_PATH];
        
    if (paudec->m_fWriteMetaFile != WMAB_TRUE)
        return wmaResult;

    // In v2, the whole config is ready only after we decode the last subframe.
    if (pau->m_iVersion == 2)
    {
        if (paudec->m_fLastSubFrame != WMAB_TRUE)
        {
            return wmaResult;
        }
    }

    assert (iFrame == CONFIG_CURRFRM);


    // Map windowed frame number (m_iFrameNumber) to PCM frame number.
    iPCMFrameNumber = prvGetPCMFrameNumber(pau->m_iFrameNumber, WMAB_FALSE, pau->m_iVersion);

    sprintf(fileName, "%sSubFrmCfg.dat",pMetaFileName);

    // We don't send the subfrmconfig of the -1 PCMFrame. Only effective in v2.
    if (iPCMFrameNumber < 0)
        return wmaResult;

    fp = FOPEN(fileName,"at");
    if (fp == NULL)
    {
        return wmaResult;
    }

    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        ppcinfo = rgpcinfo + iCh;
        cSubFrm = ppcinfo->m_rgsubfrmconfig[iFrame].m_cSubFrame;
        piSubFrmSize = ppcinfo->m_rgsubfrmconfig[iFrame].m_rgiSubFrameSize;
        WMAFprintf(fp, "iPCMFrm = %10d iCh = %3d cSubFrm = %3d   ", (Int)iPCMFrameNumber, (Int)iCh, (Int)cSubFrm);
        for (iSubFrm = 0; iSubFrm < cSubFrm; iSubFrm++)
        {
            WMAFprintf(fp, "%4d   ",(Int)piSubFrmSize[iSubFrm]);
        }
        WMAFprintf(fp,"\n");
    }

    FCLOSE(fp);
#endif WMA_COMPTOOL_NODUMPING
    return wmaResult;
}
#endif //WMA_COMPRESSION_TOOL

#endif // BUILD_WMAPRO || BUILD_WMALSL
