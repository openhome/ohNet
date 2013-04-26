//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains entropy decoding functions needed exclusively by WMA Pro.
// They are not needed for WMA Standard or WMA Lossless.
//*@@@---@@@@******************************************************************


#include "msaudiodec.h"
#include "huffdec.h"
#include "AutoProfile.h"  
#include "entropydec.h"

#if defined (BUILD_WMAPRO)

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

// And also settle transform values if predefined
WMARESULT prvDecideXformType (CAudioObjectDecoder* paudec)
{      
    WMARESULT   wmaResult = WMA_OK;
    Int iCh, iCh0, iCh1;
    CAudioObject* pau = paudec->pau;
    Int     iResult = 0;
    Int     cChannelsInGrp = paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_cChannelsInGrp;
    CChannelGroupInfo *pcgi = NULL;

    assert(paudec->m_cChannelGroup <= pau->m_cChannel);
    assert(cChannelsInGrp <= pau->m_cChannel);

    pcgi = paudec->m_rgChannelGrpInfo + paudec->m_cChannelGroup;
    
    // The inverse transform is assumed to have been zeroed initially for this channel group
    pcgi->m_fIsPredefinedXform = WMAB_FALSE;
    pcgi->m_fIsSuperGroupXform = paudec->m_fDecodingSuperGroupXform;

    if (cChannelsInGrp == 1) {
        // pre-defined identity: hunt for the channel
        pcgi->m_fIsPredefinedXform = WMAB_TRUE;
        pcgi->m_predefinedXformType = MULTICH_IDENTITY;
        pcgi->m_rgfltMultiXInverse[0] = CH_FROM_FLOAT(1.0F);
    } else if (cChannelsInGrp == 2) {
        // All the bits needed are available
        iResult = 0;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
        if (iResult == 0) {
            // Joint standard (Hadamard)
            // Set joint standard xform: These get used only for non-stereo cases.
            // Values are quantized to 1.8bits
            pcgi->m_fIsPredefinedXform = WMAB_TRUE;
            pcgi->m_predefinedXformType = MULTICH_HADAMARD;
            pcgi->m_rgfltMultiXInverse[0] = CH_FROM_FLOAT( 0.70703125F);
            pcgi->m_rgfltMultiXInverse[1] = CH_FROM_FLOAT(-0.70703125F);
            pcgi->m_rgfltMultiXInverse[2] = CH_FROM_FLOAT( 0.70703125F);
            pcgi->m_rgfltMultiXInverse[3] = CH_FROM_FLOAT( 0.70703125F);
        } else {
            // Read one more bit
            iResult = 0;
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
            if (iResult == 0) {
                // 2 independently coded channels
                // Set joint standard xform
                pcgi->m_fIsPredefinedXform = WMAB_TRUE;
                pcgi->m_predefinedXformType = MULTICH_IDENTITY;
                pcgi->m_rgfltMultiXInverse[0] = CH_FROM_FLOAT(1.0F);
                pcgi->m_rgfltMultiXInverse[1] = CH_FROM_FLOAT(0.0F);
                pcgi->m_rgfltMultiXInverse[2] = CH_FROM_FLOAT(0.0F);
                pcgi->m_rgfltMultiXInverse[3] = CH_FROM_FLOAT(1.0F);
            } else {
                // Joint flexible coded.
            }
        }
    } else {
        // More than 2 channels in this channel group.
        iResult = 0;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
        if (iResult == 0) {
            // All independently coded channels
            pcgi->m_fIsPredefinedXform = WMAB_TRUE;
            pcgi->m_predefinedXformType = MULTICH_IDENTITY;
            for (iCh = 0; iCh < cChannelsInGrp; iCh++) {
                pcgi->m_rgfltMultiXInverse[iCh * cChannelsInGrp + iCh] = CH_FROM_FLOAT(1.0F);
            }
        } else {
            // Either DCT or free style

            iResult = 0;
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
            if (iResult == 0) {
                // DCT-Type 2
                assert(pcgi->m_cChannelsInGrp > 0 && pcgi->m_cChannelsInGrp <= MAX_CHANNEL);
                pcgi->m_fIsPredefinedXform = WMAB_TRUE;
                pcgi->m_predefinedXformType = MULTICH_DCT;
                // Fill the inverse transform for the channels in this group
                for (iCh0 = 0; iCh0 < cChannelsInGrp; iCh0++) {
                    for (iCh1 = 0; iCh1 < cChannelsInGrp; iCh1++) {
                        pcgi->m_rgfltMultiXInverse[iCh0 * cChannelsInGrp + iCh1] = 
                            pau->m_rgrgrgfltMultiXIDCT[cChannelsInGrp][iCh0][iCh1];
                    }
                }
                //assert(0);
            } else {
                // Free style
                pcgi->m_fIsPredefinedXform = WMAB_FALSE;
                pcgi->m_predefinedXformType = MULTICH_INVALID;
            }
        }
    }
exit:
    return wmaResult;
} // prvDecideXformType

WMARESULT prvDecodeTransformOnOffInfo (CAudioObjectDecoder* paudec)
{      
    WMARESULT   wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;
    Int     iResult = 0;
    Int     iBand;
    Int     cBits0 = min(24, pau->m_cValidBarkBand+1); // Maximum 24 bits to be read at a time.
    
    assert(paudec->m_cChannelGroup < pau->m_cChannel);
    assert((pau->m_cValidBarkBand+1) <= 2 * 24);

    if ((paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_cChannelsInGrp > 1) &&
        ((paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_fIsPredefinedXform == WMAB_TRUE &&
        paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_predefinedXformType != MULTICH_IDENTITY) ||
        (paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_fIsPredefinedXform == WMAB_FALSE))) {
        // Read the on-off information
        switch (paudec->m_chxformsts) {
        case CHXFORM_XFORMONOFF0:
#ifdef BUILD_UES
            if(!(paudec->pau->m_fUES == WMAB_TRUE && paudec->m_pCUESdec->m_cbAudioPayloadLeft==0))
#endif
            {
                TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, cBits0));
            }
            // Are all the barks on?
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
            paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_fAllBarksOn = iResult;
            if (iResult == WMAB_TRUE) {
                // All barks have transform on
                for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
                    paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_rgfXformOn[iBand] = WMAB_TRUE;
                paudec->m_chxformsts = CHXFORM_XFORMONOFF_DONE;
            } else {
                for (iBand = 0; iBand < cBits0 - 1; iBand++) {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
                    paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_rgfXformOn[iBand] = iResult;
                }
                if (cBits0 == (pau->m_cValidBarkBand+1)) {
                    // We are done with this channel group's on-of information.
                    paudec->m_chxformsts = CHXFORM_XFORMONOFF_DONE;
                } else {
                    // We have few more bark bands to settle
                    paudec->m_chxformsts = CHXFORM_XFORMONOFF1;
                }
            }
            break;
        case CHXFORM_XFORMONOFF1:
            assert(cBits0 < (pau->m_cValidBarkBand+1));
            // settle remaining bark bands beyond first 24 bits
            TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, ((pau->m_cValidBarkBand+1)-cBits0)));
            for (iBand = cBits0 - 1; iBand < pau->m_cValidBarkBand; iBand++) {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
                paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_rgfXformOn[iBand] = iResult;
            }
            paudec->m_chxformsts = CHXFORM_XFORMONOFF_DONE;
            break;
        default:
            assert(0);// Should not arrive here: internal state machine error
            paudec->m_chxformsts = CHXFORM_XFORMONOFF_DONE;
            break;
        }
    } else {
        // All barks have transform on
        for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_rgfXformOn[iBand] = WMAB_TRUE;
        paudec->m_chxformsts = CHXFORM_XFORMONOFF_DONE;
    }
    
exit:
    
    return wmaResult;
} // prvDecodeTransformOnOffInfo

WMARESULT prvDecodeChannelMask (CAudioObjectDecoder* paudec)
{      
    WMARESULT   wmaResult = WMA_OK;
    Int iCh;
    CAudioObject* pau = paudec->pau;
    Int iResult       = 0;
    CChannelGroupInfo* pcgi = NULL;
    
    if (paudec->m_cChannelGroup >= pau->m_cChannel)
    {
        wmaResult = WMA_E_BROKEN_FRAME;
        REPORT_BITSTREAM_CORRUPTION();
        CHECKWMA_EXIT(wmaResult);
    }
    pcgi = paudec->m_rgChannelGrpInfo + paudec->m_cChannelGroup;
    
    assert(paudec->m_cChannelGroup < pau->m_cChannel);
    pcgi->m_cChannelsInGrp = 0;
    memset(pcgi->m_rgfChannelMask, 0, sizeof(Bool) * pau->m_cChannel);
    
    if (paudec->m_cChannelsLeft <= 2) {
        // Derive from current state
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];
            PerChannelInfoDEC* pcinfoDEC = paudec->m_rgpcinfoDEC + iChSrc;

            pcgi->m_rgfChannelMask[iChSrc] = (pcinfoDEC->m_fVisited == WMAB_TRUE) ? WMAB_FALSE : WMAB_TRUE;
            // Now all channels are visited
            pcinfoDEC->m_fVisited = WMAB_TRUE;
        }
        pcgi->m_cChannelsInGrp = paudec->m_cChannelsLeft;
    } else {
        // (paudec->m_cChannelsLeft > 2) 
        // Must read the bitstream and decode: enough bits are available
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];
            PerChannelInfoDEC* pcinfoDECSrc = paudec->m_rgpcinfoDEC + iChSrc;

            if (pcinfoDECSrc->m_fVisited == WMAB_FALSE) {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
                if (iResult == 1) {
                    pcgi->m_rgfChannelMask[iChSrc] = WMAB_TRUE;
                    pcinfoDECSrc->m_fVisited = WMAB_TRUE;
                    pcgi->m_cChannelsInGrp = pcgi->m_cChannelsInGrp + 1;
                }
            }
        }
    }
    if (pcgi->m_cChannelsInGrp < 1) {
        // Horrible channel group
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
exit:
    
    return wmaResult;
} // prvDecodeChannelMask

#if defined (_DEBUG)
#define DEBUG_PRINT_QUANTSTEPMODIFIERS(fPrint) \
{ \
    if (fPrint) {\
        Int iCh=0;\
        while (iCh < pau->m_cChInTile) \
        {\
          I16 iChSrc = pau->m_rgiChInTile [iCh];\
          PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;\
          WMAFprintf(stdout, "%d %d %d\n", pau->m_iFrameNumber,\
                  iChSrc,\
                  (Int)ppcinfo->m_ucQuantStepModifierIndex);\
          iCh++;\
        }\
    }\
}
#else
#define DEBUG_PRINT_QUANTSTEPMODIFIERS(fPrint) 
#endif // _DEBUG

WMARESULT prvDecodeQuantStepModifiers (CAudioObjectDecoder* paudec)
{      
    WMARESULT   wmaResult = WMA_OK;

    CAudioObject* pau = paudec->pau;
    Int iResult = 0;

    if (pau->m_iVersion <= 2) 
    {
        paudec->m_iChannel = 0;
        return wmaResult;
    }

    if (pau->m_cChInTile == 1)
    {
        // No need of balancing # for mono tile.
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + pau->m_rgiChInTile [0];
        
        paudec->m_iChannel = 0;
        // Set the scale index to 0.
        ppcinfo->m_ucQuantStepModifierIndex = 0;
        ppcinfo->m_qstQuantStepModifier = qstCalcQuantStep(0, 0);
        goto exit;
    } 

    if (paudec->m_iChannel == -1)
    {
        // Read size information.
        iResult = 0;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 3, (U32 *)&iResult));
        paudec->m_cBitQuantStepModifierIndex = iResult;
        paudec->m_iChannel = 0;
    }
    
    while (paudec->m_iChannel < pau->m_cChInTile) 
    {
        I16 iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;

        // Reserve bits for 0 indication as well as for the index, if it is not 0.
        TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, (paudec->m_cBitQuantStepModifierIndex+1)));

        // Is the scale index 0?
        iResult = 0;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
        if (iResult == 0) {
            ppcinfo->m_ucQuantStepModifierIndex = 0;
            ppcinfo->m_qstQuantStepModifier = qstCalcQuantStep(0, 0);
        } else {
            // index is not 0.
            if (paudec->m_cBitQuantStepModifierIndex == 0)
            {
                // no need to read the bits, but use an index of 1.
                ppcinfo->m_ucQuantStepModifierIndex = 1;
                ppcinfo->m_qstQuantStepModifier = qstCalcQuantStep(1, 0);
            } else {
                // Must read the bits to get index value.
                iResult = 0;
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, paudec->m_cBitQuantStepModifierIndex, (U32 *)&iResult));
                ppcinfo->m_ucQuantStepModifierIndex = (U8) iResult + 1;
                ppcinfo->m_qstQuantStepModifier  = qstCalcQuantStep((Int)ppcinfo->m_ucQuantStepModifierIndex, 0);
            }
        }
        // done with this channel
        paudec->m_iChannel++;
    }
    
exit:
    DEBUG_PRINT_QUANTSTEPMODIFIERS(WMAB_FALSE) ;
    return wmaResult;
} // prvDecodeQuantStepModifiers

WMARESULT prvEntropyDecodeChannelXform (CAudioObjectDecoder* paudec)
{      
    WMARESULT   wmaResult = WMA_OK;
    
    CAudioObject* pau = paudec->pau;
    Int iCh;
    Int iResult = 0;
    Int cChannelsInGrp;
    CChannelGroupInfo* pcgi = NULL;
    assert(pau->m_iVersion >= 3);
	
    if (pau->m_cChannel == 1 && pau->m_bMonoV3)
    {
        // nothing to decode
        pau->m_cChannelGroup = paudec->m_cChannelGroup = 1;
        pcgi = paudec->m_rgChannelGrpInfo;
                
        pcgi->m_cChannelsInGrp = 1;
        memset(pcgi->m_rgfChannelMask, 0, sizeof(Bool) * pau->m_cChannel);
        pcgi->m_rgfChannelMask[0] = WMAB_TRUE;
        pcgi->m_fIsSuperGroupXform = WMAB_FALSE;
        pcgi->m_fIsPredefinedXform = WMAB_TRUE;
        pcgi->m_predefinedXformType = MULTICH_INVALID;
        pcgi->m_fAllBarksOn = WMAB_TRUE;
        memset(pcgi->m_rgfXformOn, 0, sizeof(Bool) * NUM_BARK_BAND);
        memset(pcgi->m_rgfltMultiXInverse, 0, sizeof(ChXFormType) * pau->m_cChannel * pau->m_cChannel);
        pcgi->m_fIsPredefinedXform = WMAB_TRUE;
        pcgi->m_predefinedXformType = MULTICH_IDENTITY;
        pcgi->m_rgfltMultiXInverse[0] = CH_FROM_FLOAT(1.0F);
        paudec->m_chxformsts = CHXFORM_DONE;
        return WMA_OK;
    }

    while (paudec->m_chxformsts != CHXFORM_DONE) {
        switch (paudec->m_chxformsts) {
        case CHXFORM_BEGIN:
            paudec->m_fDecodingSuperGroupXform = WMAB_FALSE;
            paudec->m_cChannelsLeft = pau->m_cChInTile;
            paudec->m_cAngles = 0;
            paudec->m_iAngle  = 0;
            paudec->m_cSigns  = 0;
            paudec->m_iSign   = 0;
            
            // Clean slate
            paudec->m_cChannelGroup = 0;
            for (iCh = 0; iCh < pau->m_cChannel; iCh++) {
                paudec->m_rgpcinfoDEC[iCh].m_fVisited = WMAB_FALSE;
            }
            
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
                pcgi = paudec->m_rgChannelGrpInfo + iCh;
                
                pcgi->m_cChannelsInGrp = 0;
                memset(pcgi->m_rgfChannelMask, 0, sizeof(Bool) * pau->m_cChannel);
                pcgi->m_fIsSuperGroupXform = WMAB_FALSE;
                pcgi->m_fIsPredefinedXform = WMAB_FALSE;
                pcgi->m_predefinedXformType = MULTICH_INVALID;
                pcgi->m_fAllBarksOn = WMAB_FALSE;
                memset(pcgi->m_rgfXformOn, 0, sizeof(Bool) * NUM_BARK_BAND);
                memset(pcgi->m_rgfltMultiXInverse, 0, sizeof(ChXFormType) * pau->m_cChannel * pau->m_cChannel);
            }
            paudec->m_chxformsts = CHXFORM_LEVEL;
            break;

        case CHXFORM_LEVEL:
            // Read one bit to decide the level of first group to decode.
            iResult = 0;
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
            paudec->m_fDecodingSuperGroupXform = (iResult == 0) ? WMAB_FALSE : WMAB_TRUE;
            paudec->m_chxformsts = CHXFORM_CHGRP;
            break;
            
        case CHXFORM_CHGRP:
            if (paudec->m_cChannelsLeft == 0 && 
                paudec->m_fDecodingSuperGroupXform == WMAB_FALSE) 
            {
                paudec->m_chxformsts = CHXFORM_DONE;
                // Set common info
                pau->m_cChannelGroup = paudec->m_cChannelGroup;
                assert (wmaResult == WMA_OK);
                return wmaResult;
            } 
            if (paudec->m_cChannelsLeft == 0 && 
                paudec->m_fDecodingSuperGroupXform == WMAB_TRUE) 
            {
                // Should not have happened. Bad bitstream.
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            } 
            
            TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, (paudec->m_cChannelsLeft+3)));
            
            // decode channel mask for the group
            TRACEWMA_EXIT(wmaResult, prvDecodeChannelMask(paudec));
            
            // Decide if we need a flexible transform or predefined
            TRACEWMA_EXIT(wmaResult, prvDecideXformType(paudec));
            
            assert(paudec->m_cChannelGroup <= pau->m_cChannel);
            cChannelsInGrp    = paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_cChannelsInGrp;
            assert(cChannelsInGrp <= pau->m_cChannel);
            paudec->m_cAngles = (cChannelsInGrp * (cChannelsInGrp-1))/2;
            paudec->m_cSigns  = cChannelsInGrp;
            paudec->m_iAngle  = 0;
            paudec->m_iSign   = 0;
            paudec->m_chxformsts = CHXFORM_XFORM_ANGLES;
            break;
            
        case CHXFORM_XFORM_ANGLES:
            pcgi = paudec->m_rgChannelGrpInfo + paudec->m_cChannelGroup;
            if (!pcgi->m_fIsPredefinedXform) 
            {
                for (; paudec->m_iAngle < paudec->m_cAngles; paudec->m_iAngle++) 
                {
                    iResult = 0;
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, ROTATION_ANGLE_BITS, (U32 *)&iResult));
                    // Map iResult into quantized index 
                    pcgi->m_rgbRotationAngle[paudec->m_iAngle] = (I8)(iResult-MAX_ROTATION_ANGLE_INDEX);
                }
            }
            paudec->m_chxformsts = CHXFORM_XFORM_SIGNS;
            break;

        case CHXFORM_XFORM_SIGNS:
            pcgi = paudec->m_rgChannelGrpInfo + paudec->m_cChannelGroup;
            if (!pcgi->m_fIsPredefinedXform) 
            {
                for (; paudec->m_iSign < paudec->m_cSigns; paudec->m_iSign++) 
                {
                    iResult = 0;
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
                    pcgi->m_rgbRotationSign[paudec->m_iSign] = (I8)iResult;
                }
            }
            paudec->m_chxformsts = CHXFORM_XFORMONOFF0;
            break;
            
        case CHXFORM_XFORMONOFF0:
        case CHXFORM_XFORMONOFF1:
            assert(paudec->m_cChannelGroup < pau->m_cChannel);
            // prvDecodeTransformOnOffInfo distinguishes between CHXFORM_XFORMONOFF0 and CHXFORM_XFORMONOFF1.
            TRACEWMA_EXIT(wmaResult, prvDecodeTransformOnOffInfo(paudec));
            if (paudec->m_chxformsts == CHXFORM_XFORMONOFF_DONE) {
                paudec->m_cChannelsLeft -= paudec->m_rgChannelGrpInfo[paudec->m_cChannelGroup].m_cChannelsInGrp;
                paudec->m_cChannelGroup += 1;
                paudec->m_chxformsts = CHXFORM_CONTINUED;
            }
            break;

        case CHXFORM_CONTINUED:
            if (paudec->m_fDecodingSuperGroupXform) {
                // Read one more bit to decide if more super groups are to be read.
                iResult = 0;
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
                if (iResult == 0) {
                    // Done with super group xform.
                    paudec->m_fDecodingSuperGroupXform = WMAB_FALSE;
                    // Do some resets before reading normal group xforms.
                    paudec->m_cChannelsLeft = pau->m_cChInTile;
                    for (iCh = 0; iCh < pau->m_cChannel; iCh++) {
                        paudec->m_rgpcinfoDEC[iCh].m_fVisited = WMAB_FALSE;
                    }
                } 
                // else, continue with super group decoding
            } // else, there is a different stopping criteria for lower level hierarchy.
            paudec->m_chxformsts = CHXFORM_CHGRP;
            break;

        default:
            assert(0); // internal state machine error
            break;
        }
    }
    
exit:    
    return wmaResult;
} // prvEntropyDecodeChannelXform


#if defined (_DEBUG)
#define DEBUG_PRINT_POSTPROCXFORM(fPrint) \
{ \
    if (fPrint) {\
        Int iCh0, iCh1;\
        for (iCh0 = 0; iCh0 < pau->m_cChannel; iCh0++) {\
            for (iCh1 = 0; iCh1 < pau->m_cChannel; iCh1++) {\
                WMAFprintf(stdout, "%f ", paudec->m_rgfltPostProcXform[iCh0 * pau->m_cChannel + iCh1]);\
            }\
            WMAFprintf(stdout,"\n");\
        }\
    }\
}
#else
#define DEBUG_PRINT_POSTPROCXFORM(fPrint) 
#endif // _DEBUG

WMARESULT prvEntropyDecodePostProcXform (CAudioObjectDecoder* paudec)
{      
    WMARESULT   wmaResult = WMA_OK;
    
    CAudioObject* pau = paudec->pau;
    Int iResult = 0;
    Bool fPrint = WMAB_FALSE;
    Int cChannel = pau->m_cChannel;
    //assert(pau->m_iVersion >= 3);
    
    while (paudec->m_ppxformsts != PPXFORM_DONE) {
        switch (paudec->m_ppxformsts) {
        case CHXFORM_BEGIN:
            // Save old transform
            paudec->m_fPostProcXformPrev = paudec->m_fPostProcXform;
            if (paudec->m_rgfltPostProcXformPrev && paudec->m_rgfltPostProcXform)
            {
                memcpy(paudec->m_rgfltPostProcXformPrev,
                    paudec->m_rgfltPostProcXform, sizeof(ChXFormType) * cChannel * cChannel);
            }

            // Initialization of the transform for current frame
            paudec->m_fPostProcXform = WMAB_FALSE;
            paudec->m_fGeneralPostProcXform = WMAB_FALSE;
            if (paudec->m_rgfltPostProcXform)
                memset(paudec->m_rgfltPostProcXform, 
                0, sizeof(ChXFormType) * cChannel * cChannel);
            
            if (pau->m_iVersion <= 2 ||
                cChannel < 2 || 
                (pau->m_iVersion > 2 && pau->m_bPureLosslessMode == WMAB_TRUE))
                // No need to decode anything.
                paudec->m_ppxformsts = PPXFORM_DONE;
            else 
                paudec->m_ppxformsts = PPXFORM_ONOFF;
            break;
            
        case PPXFORM_ONOFF:
            // Read one bit to decide if the postpocessing channel transform is on or off.
            iResult = 0;
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
            paudec->m_fPostProcXform = (iResult == 0) ? WMAB_FALSE : WMAB_TRUE;
            if (paudec->m_fPostProcXform)
                paudec->m_ppxformsts = PPXFORM_GENERIC;
            else
                paudec->m_ppxformsts = PPXFORM_DONE;
            break;

        case PPXFORM_GENERIC:
            // Read one bit to decide if the postpocessing channel transform is generic, or pre-determined.
            iResult = 0;
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
            paudec->m_fGeneralPostProcXform = (iResult == 0) ? WMAB_FALSE : WMAB_TRUE;
            if (paudec->m_fGeneralPostProcXform)
            {
                paudec->m_iPPXformIndex = 0;
                paudec->m_ppxformsts = PPXFORM_COEF;
            }
            else
            {
                // Pre-defined transform.
                if (pau->m_cChannel == 6 && pau->m_nChannelMask == 63)
                {
                    //5.1 with phantom center.
                    if (paudec->m_rgfltPostProcXform)
                    {
                        ChPPXFormType* rgfltX = paudec->m_rgfltPostProcXform;

                        // Phantom center recon based on front left & front right
                        // assumes already zero'ed transform.
                        rgfltX[0] = rgfltX[7] = rgfltX[21] = rgfltX[28] = rgfltX[35] = CHPP_FROM_FLOAT(1.0F);
                        rgfltX[12] = rgfltX[13] = CHPP_FROM_FLOAT(0.5F);
                    }
                }
                else 
                {
                    // Unknown config: Identity for now.
                    paudec->m_fPostProcXform = WMAB_FALSE;
                }
                paudec->m_ppxformsts = PPXFORM_DONE;
            }
            break;

     
        case PPXFORM_COEF:
            while (paudec->m_iPPXformIndex < cChannel * cChannel)
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 4, (U32 *)&iResult));
                // Sign extend
                if (iResult & 0x08) iResult |= 0xFFFFFFF0;
                // iResult between -8 and 7
#ifdef BUILD_INTEGER
                paudec->m_rgfltPostProcXform[paudec->m_iPPXformIndex] = -iResult << (CHPP_FRAC_BITS - 3);
#else
                paudec->m_rgfltPostProcXform[paudec->m_iPPXformIndex] = (Float)iResult/-8.0F;
#endif
                paudec->m_iPPXformIndex++;
            }
            paudec->m_ppxformsts = PPXFORM_DONE;
            break;

        default:
            assert(0); // internal state machine error
            break;
        }
    }
    DEBUG_PRINT_POSTPROCXFORM(fPrint);

exit:    
    return wmaResult;
} // prvEntropyDecodePostProcXform


WMARESULT prvDecodeMaskHeaderV3_Channel (CAudioObjectDecoder* paudec, Int iCh)
{
    WMARESULT     wmaResult       = WMA_OK;
    U32           iResult         = 0;
    CAudioObject* pau             = paudec->pau;
    PerChannelInfo* ppcinfo       = pau->m_rgpcinfo + iCh;
    PerChannelInfoDEC* ppcinfoDEC = paudec->m_rgpcinfoDEC + iCh;

    TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, 3));

    assert(ppcinfoDEC->m_fMaskHeaderDone == WMAB_FALSE);
    
    // Is mask being sent or not
    if (ppcinfo->m_iCurrSubFrame > 0 || 
        pau->m_bUnifiedLLM == WMAB_TRUE) 
    {
        iResult = WMAB_FALSE;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0] = (U8) iResult; // to detect initial silence
    } 
    else 
    {
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0] = WMAB_TRUE;
    }

    // Read mask step sizes
    if ((ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0] == WMAB_TRUE) &&
         ppcinfo->m_fAnchorMaskAvailable == WMAB_FALSE) 
    {
        iResult = 0;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 2, &iResult));
        pau->m_rgpcinfo[iCh].m_iMaskQuantMultiplier = iResult + 1;
        assert (ppcinfo->m_iMaskQuantMultiplier > 0);
        assert (ppcinfo->m_iMaskQuantMultiplier <= 4);
    }

    // Set prediction values for Mask 
    if (ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0] == WMAB_TRUE &&
        ppcinfo->m_fAnchorMaskAvailable == WMAB_TRUE) 
    {
        // Do some set-up for runlength decoding of mask
        paudec->pau->m_iCurrReconMaskBand = 0; 
        paudec->m_maskrlsts = VLC;
        memcpy (paudec->pau->m_rgpcinfo[iCh].m_rgiMaskQ, paudec->pau->m_rgpcinfo[iCh].m_rgiMaskQResampled, 
            sizeof(Int) * paudec->pau->m_cValidBarkBand);
    }
    ppcinfoDEC->m_fMaskHeaderDone = WMAB_TRUE;

exit:  
    return wmaResult;
} // prvDecodeMaskHeaderV3_Channel

WMARESULT prvDecodeQuantStepV3 (CAudioObjectDecoder* paudec)
{      
    WMARESULT wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;        
    U32         iResult;
    Int iStepSize;

    if (paudec->m_iQuantStepSign == INT_MAX)
    {
        // First part, sent in 2's complement is not decoded yet
        paudec->m_fQuantStepEscaped = WMAB_FALSE;

        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm,
            6, &iResult));
        
        // Determine the sign
        iStepSize = iResult;
        paudec->m_iQuantStepSign = (iStepSize & 0x20) ? -1 : 1;
        // Extend the sign.
        if (paudec->m_iQuantStepSign == -1)
            iStepSize |= 0xFFFFFFC0;
        // Accumulate the result
        pau->m_iQuantStepSize += iStepSize;
        // Determine if escape coded
        if (iStepSize <= -32 || iStepSize >= 31)
            paudec->m_fQuantStepEscaped = WMAB_TRUE;
    }

    while(paudec->m_fQuantStepEscaped) 
    {
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm,
            NUM_BITS_QUANTIZER_V3, &iResult));

        iStepSize = iResult;
        assert(iStepSize <= MSA_MAX_QUANT_ESC_V3);
        if(iStepSize != MSA_MAX_QUANT_ESC_V3) 
        {
            // the last one...
            pau->m_iQuantStepSize += (iStepSize * paudec->m_iQuantStepSign);
            MONITOR_RANGE(gMR_iQuantStepSize,pau->m_iQuantStepSize);
            break;
        }
        // escape code, so on to the next level...
        pau->m_iQuantStepSize += (MSA_MAX_QUANT_ESC_V3 * paudec->m_iQuantStepSign);
        if (pau->m_iQuantStepSize < MIN_QUANT)
        {
            // set some what safer step size.
            pau->m_iQuantStepSize = 2 * MSA_MAX_QUANT_ESC_V3;
            REPORT_BITSTREAM_CORRUPTION();
            wmaResult = TraceResult(WMA_E_BROKEN_FRAME);
            goto exit;
        }
    }
    DEBUG_TRACE_QUANT(pau->m_iFrameNumber, pau->m_iCurrSubFrame, iStepSize);
    
exit:
    return wmaResult;
} // prvDecodeQuantStepV3

//#define RL_PRINT_SRC
#undef RL_PRINT_SRC
#if defined (RL_PRINT_SRC)
#define DBG_RUNLEVEL_DEC(a,b,c,e)     \
                    if(e) {\
                        WMAPrintf("%d %d %d\n", a, b, c);\
                        FFLUSH (stdout);\
                    }
#pragma COMPILER_MESSAGE(__FILE__ "(43) : Warning - RunLevel Debug Code Enabled.")

#else 
#define DBG_RUNLEVEL_DEC(a,b,c,e)
#endif //DBG_RUNLEVEL_DEC

//*****************************************************************************************
//
// prvGetNextRunDEC
//
//*****************************************************************************************
extern Int g_cBitPut;

//#define WMA_ENTCODE_DEBUG
#if defined(WMA_ENTCODE_DEBUG)
static Int wmaEntCodeCount = 0;
static Int wmaNumGets = 0;
static FILE *pDbgFile = NULL;
#define ADDGET { wmaNumGets++; }
#else
#define ADDGET
#endif

Void prvResetVecCoder(CAudioObjectDecoder *paudec)
{
  CAudioObject *pau = paudec->pau;
  DecRunLevelVecState *pState;
  if (pau->m_fUseVecCoder) {
    pState = &paudec->m_decRunLevelVecState;
    pState->getState = TABLE_INDEX;
    pau->aupfnGetNextRun = prvGetNextRunDECVecTableIndex;
  }
} // prvResetVecCoder

INLINE
WMARESULT prvDecodeEscapeLargeVal(Int *pSymbol, Int max,
                                  CWMAInputBitStream *pibstrm,
                                  CAudioObjectDecoder* paudec,
                                  DecRunLevelVecState *pState)
{
  WMARESULT wmaResult = WMA_OK;
  U32 iResult;

  while (1) {
    switch (pState->getLargeState) {
    case LargeValBitCnt:
      TRACEWMA_EXIT(wmaResult,
               ibstrmPeekBits(pibstrm, 3, &iResult));
      iResult >>= 32-3;
      if      ((iResult & 0x4)>>2 == 0) {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
        pState->getLargeState = LargeVal8;  // 0xx
      }
      else if ((iResult & 0x6)>>1 == 2) {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 2));
        pState->getLargeState = LargeVal16; // 10x
      }
      else if ((iResult      )    == 6) {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 3));
        pState->getLargeState = LargeVal24; // 110
      }
      else                              {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 3));
        pState->getLargeState = LargeVal32_1; //111
      }
      break;
    case LargeVal8:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 8, (U32 *)pSymbol));
      goto done;
    case LargeVal16:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 16, (U32 *)pSymbol));
      goto done;
    case LargeVal24:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 24, (U32 *)pSymbol));
      goto done;
    case LargeVal32_1:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 24, (U32 *)&pState->symbol));
      pState->getLargeState = LargeVal32_2;
      // fall through for next 7 bits (LSBs)
    case LargeVal32_2:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 7, (U32 *)pSymbol));
      *pSymbol |= (pState->symbol << 7);
      goto done;
    }
  }

done:
  *pSymbol += max;

  // successs so reset
  pState->getLargeState = LargeValBitCnt;

exit:

  return wmaResult;
} // prvDecodeEscapeLargeVal

WMARESULT prvEscapeDecodeRunV3(Int *pcRunOfZeros, Int cMaxRun,
                               CWMAInputBitStream *pibstrm)
{
  WMARESULT wmaResult = WMA_OK;
  Int iResult;

  // Look & peek don't alter bitstream state, so do as many times as it takes
  TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(pibstrm, 3 + cMaxRun));
  TRACEWMA_EXIT(wmaResult, ibstrmPeekBits(pibstrm, 3, (U32 *)&iResult));

  //run code:   0    = no run.
  //            10   = 2
  //            110  = cBitMaxRun
  if ((iResult & 0x80000000) == 0)
    {
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
      *pcRunOfZeros = 0;
    }
  else if ((iResult & 0x40000000) == 0)
    {
      //flush and get bits can be combined 
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 2));
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits (pibstrm, 2, (U32 *)&iResult));
      *pcRunOfZeros = iResult + 1;
    }
  else if ((iResult & 0x20000000) == 0)
    {
      //flush and get bits can be combined 
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 3));
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits (pibstrm, cMaxRun, (U32 *)&iResult));
      *pcRunOfZeros = iResult + 4;
    }
  else 
    {
      TRACEWMA_EXIT(wmaResult, WMA_E_BROKEN_FRAME);
    }

exit:
  return wmaResult;
} // prvEscapeDecodeRunV3

#ifdef BUILD_WMAPROLBRV2
    #define GET_NEXT_RUN_INIT \
    WMARESULT wmaResult = WMA_OK; \
    CAudioObjectDecoder* paudec  = (CAudioObjectDecoder*) pobjin; \
    CAudioObject*        pau = paudec->pau; \
    CWMAInputBitStream*  pibstrm = (paudec->m_fDecodingBPlus ? paudec->m_pibsPlus : &(paudec->m_ibstrm)); \
    DecRunLevelVecState *pState = &paudec->m_decRunLevelVecState; \
    Int iResult                       
#else
    #define GET_NEXT_RUN_INIT \
    WMARESULT wmaResult = WMA_OK; \
    CAudioObjectDecoder* paudec  = (CAudioObjectDecoder*) pobjin; \
    CAudioObject*        pau = paudec->pau; \
    CWMAInputBitStream*  pibstrm = &(paudec->m_ibstrm); \
    DecRunLevelVecState *pState = &paudec->m_decRunLevelVecState; \
    Int iResult                       
#endif //BUILD_WMAPROLBRV2

WMARESULT prvGetNextRunDECVecTableIndex(Void*           pobjin, 
                                        PerChannelInfo* ppcinfo)
{
  GET_NEXT_RUN_INIT;
  Int i;

#ifdef USE_V4ENTCODING
  pau->m_bUseV4EntropyCoding = (pau->m_iEncodeOpt & ENCOPT3_V4ENTCODING) ? WMAB_TRUE : WMAB_FALSE;
#endif

  if (WMAB_FALSE == pau->m_bUseV4EntropyCoding)
  {
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits (pibstrm, 1, (U32 *)&iResult));

      if (RLCTBL_SS == iResult) {
          ppcinfo->m_rgiHuffDecTbl = g_wmaHuffDecTbls_3_SS;
          ppcinfo->m_rgiRunEntry = g_wmaRunLevelToRun_SS;
          ppcinfo->m_rgiLevelEntry = g_wmaRunLevelToLevel_SS;
          paudec->m_iMaxLevelInVlc = WMA_MAX_RL_LEVEL_SS;
#ifdef WMA_ENTROPY_TEST
          SET_CUR_MODE(0, "Set SS\n");
#endif
      } else {
          ppcinfo->m_rgiHuffDecTbl = g_wmaHuffDecTbls_3_SM;
          ppcinfo->m_rgiRunEntry = g_wmaRunLevelToRun_SM;
          ppcinfo->m_rgiLevelEntry = g_wmaRunLevelToLevel_SM;
          paudec->m_iMaxLevelInVlc = WMA_MAX_RL_LEVEL_SM;
#ifdef WMA_ENTROPY_TEST
          SET_CUR_MODE(1, "Set SM\n");
#endif
      }
  }

  pState->trip = 0;
  pState->getState = GET_VEC4;
  pState->curRun = 0;
  pState->cVecsInNonRLMode = 0;
  pState->iBark = 0;
  pState->iCoeff = 0;
  pState->iVecType = 0;
  for (i=0; i < 4; i++)
  {
      pState->iLastSwitchPt[i] = 0;
      pState->nTbls[i] = 0;
  }

#ifdef USE_V4ENTCODING
  if (pau->m_bUseV4EntropyCoding)
  {
      pState->getState = FREQADAPTIDX_4D;
      pau->aupfnGetNextRun = prvGetNextRunDECVecNonRLV4;
  }
  else
#endif
      pau->aupfnGetNextRun = prvGetNextRunDECVecNonRL;
  TRACEWMA_EXIT(wmaResult,
                pau->aupfnGetNextRun(pobjin, ppcinfo));

exit:
  return wmaResult;
} // prvGetNextRunDECVecTableIndex

#ifdef WMA_ENTCODE_DEBUG
#define CHECK_VALS { \
  if (wmaEntCodeCount == 0) { \
    pDbgFile = FOPEN("coeff", "rb"); \
  } \
  if (!WMA_FAILED(wmaResult) && pDbgFile!=NULL) { \
    int run, level, sign; \
    FREAD(&run, 1, sizeof(Int), pDbgFile); \
    FREAD(&level, 1, sizeof(Int), pDbgFile); \
    FREAD(&sign, 1, sizeof(Int), pDbgFile);  \
    if (sign) sign = 0; \
    else sign = -1; \
    if (pau->m_cRunOfZeros != run || \
        pau->m_iLevel != level || \
        (pau->m_iSign!=sign && level!=0 && 1)) { \
      WMAPrintf("Don't match\n"); \
      assert(0); \
    } \
    wmaEntCodeCount++; \
  } \
}
#else
#define CHECK_VALS
#endif

#ifdef USE_V4ENTCODING

WMARESULT prvGetFreqAdaptTblIdx(Void *pobjin,
                                PerChannelInfo *ppcinfo,
                                Int i)
{
    GET_NEXT_RUN_INIT;
    Int idx, last, iTblBits, iNTblBits;

    iTblBits = g_iWmaEntCodeTblBitsV4[i];
    if (pState->iBark >= pau->m_cValidBarkBand)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    if (pState->iBark-pState->iLastSwitchPt[i] >= pState->nTbls[i])
    {
        iNTblBits = CEILLOG2(pau->m_cValidBarkBand-pState->iBark-1);
        TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(pibstrm, 
                                                   1+iNTblBits+iTblBits));
        pState->iLastSwitchPt[i] = pState->iBark;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 1,
                                               (U32 *)&iResult));
        last = iResult;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, iTblBits,
                                               (U32 *)&iResult));
        idx = iResult;
        pState->iTblIdx[i] = iResult;
        if (last == 1)
        {
            pState->nTbls[i] = pau->m_cValidBarkBand - pState->iBark;
        }
        else
        {
            if (iNTblBits != 0)
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm,
                                                       iNTblBits,
                                                       (U32 *)&iResult));
            }
            else
            {
                iResult = 0;
            }
            pState->nTbls[i] = iResult + 1;
            if (pState->nTbls[i] > pau->m_cValidBarkBand-pState->iBark)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
        }
        switch (i)
        {
        case 0:
            pState->huffDecTbl4d = g_wmaHuffDecTbls4d[idx];
            if (g_wmaIsSmallTbl4d[idx])
            {
                pState->iEscVal4d = g_wmaSmallTblMax4d-1;
                pState->uSymToVec4 = g_wmaSmallSymBaseToVec4;
            }
            else
            {
                pState->iEscVal4d = g_wmaVec4NSyms;
                pState->uSymToVec4 = g_wmaSymToVec4;
            }
            break;
        case 1:
            pState->huffDecTbl2d = g_wmaHuffDecTbls2d[idx];
            if (g_wmaIsSmallTbl2d[idx])
            {
                pState->iEscVal2d = g_wmaSmallTblMax2d-1;
                pState->uSymToVec2 = g_wmaSmallSymBaseToVec2;
            }
            else
            {
                pState->iEscVal2d = g_wmaVec2NSyms;
                pState->uSymToVec2 = g_wmaSymToVec2;
            }
            break;
        case 2:
            pState->huffDecTbl1d = g_wmaHuffDecTbls1d[idx];
            if (g_wmaIsSmallTbl1d[idx])
                pState->iEscVal1d = g_wmaSmallTblMax1d-1;
            else
                pState->iEscVal1d = g_wmaVec1NSyms;
            break;
        case 3:
            pState->huffDecTblRL = g_wmaHuffDecTblsRL[idx];
            pState->smallHuffDecTblRL = g_wmaSmallHuffDecTblRL[idx];
            ppcinfo->m_rgiRunEntry = g_wmaRunLevelToRun[idx];
            ppcinfo->m_rgiLevelEntry = g_wmaRunLevelToLevel[idx];
            pState->iEscValRL = g_wmaSmallTblMaxRL[idx];
            pState->smallSymLeafRunLevelToRun =
                g_wmaSmallSymLeafRunLevelToRun[idx];
            pState->smallSymLeafRunLevelToLevel =
                g_wmaSmallSymLeafRunLevelToLevel[idx];
            break;
        }
    }

exit:
    return wmaResult;
}

WMARESULT prvGetFreqAdaptTblIndices(Void *pobjin,
                                    PerChannelInfo *ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObjectDecoder* paudec  = (CAudioObjectDecoder*) pobjin;
    DecRunLevelVecState *pState = &paudec->m_decRunLevelVecState;
    Int i;

    for (i=pState->iVecType; i < 4; i++)
    {
        TRACEWMA_EXIT(wmaResult, prvGetFreqAdaptTblIdx(pobjin, ppcinfo, i));
    }

exit:
    pState->iVecType = i;
    return wmaResult;
}

#define INCR_BARK \
  if (pState->iCoeff == ppcinfo->m_cSubbandActual) \
  { \
      while (pState->iCoeff > pau->m_rgiBarkIndex[pState->iBark+1]) \
          pState->iBark++; \
  } \
  else \
  { \
      while (pState->iCoeff >= pau->m_rgiBarkIndex[pState->iBark+1]) \
          pState->iBark++; \
  }

WMARESULT prvGetNextRunDECVecNonRLV4(Void*           pobjin, 
                                     PerChannelInfo* ppcinfo)
{
  GET_NEXT_RUN_INIT;
  Int bitCnt;
  Int cSubband = ppcinfo->m_cSubbandActual;
  Int threshold = cSubband / 256;

#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) startEntropyTest();
#endif

#ifdef WMA_ENTCODE_DEBUG
  if (wmaEntCodeCount >= 8749062) {
    WMAPrintf("");
  }
#endif

  while (1) {
    switch (pState->getState) {
    case FREQADAPTIDX_4D:
      TRACEWMA_EXIT(wmaResult, prvGetFreqAdaptTblIdx(pobjin, ppcinfo, 0));
      pState->getState = GET_VEC4;
      break;
    case FREQADAPTIDX_2D:
      TRACEWMA_EXIT(wmaResult, prvGetFreqAdaptTblIdx(pobjin, ppcinfo, 1));
      pState->getState = GET_VEC2;
      break;
    case FREQADAPTIDX_1D:
      TRACEWMA_EXIT(wmaResult, prvGetFreqAdaptTblIdx(pobjin, ppcinfo, 2));
      pState->getState = GET_VEC1;
      break;
    case GET_VEC4:
      pState->vecIdx = 0;
      if (pau->m_fExpVecsInNonRLMode &&
          pState->cVecsInNonRLMode==ppcinfo->m_iVecsInNonRLMode) {
        pState->getState = DECODE_RL;
        break;
      }
      if (pau->m_iCurrReconCoef + pState->curRun + 1 >= cSubband) { // end of block
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pau->m_iLevel = 0;
        pau->m_iSign = 0;
        goto done;
      }
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->huffDecTbl4d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      pState->cVecsInNonRLMode++;
      if (iResult == pState->iEscVal4d)
      {
          pState->getState = FREQADAPTIDX_2D;
      }
      else if (iResult < pState->iEscVal4d)
      {
          pState->vec[0] = (pState->uSymToVec4[iResult] >> 12) & 0xf;
          pState->vec[1] = (pState->uSymToVec4[iResult] >>  8) & 0xf;
          pState->vec[2] = (pState->uSymToVec4[iResult] >>  4) & 0xf;
          pState->vec[3] = (pState->uSymToVec4[iResult]      ) & 0xf;
          pState->getState = GET_SIGN4;
      }
      else
      {
          pState->getState = GET_VEC4SMALL;
      }
      break;
    case GET_VEC4SMALL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(g_wmaSmallHuffDecTbl4d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      pState->vec[0] = (g_wmaSmallSymLeafToVec4[iResult] >> 12) & 0xf;
      pState->vec[1] = (g_wmaSmallSymLeafToVec4[iResult] >>  8) & 0xf;
      pState->vec[2] = (g_wmaSmallSymLeafToVec4[iResult] >>  4) & 0xf;
      pState->vec[3] = (g_wmaSmallSymLeafToVec4[iResult]      ) & 0xf;
      pState->getState = GET_SIGN4;
      break;
    case GET_VEC2:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->huffDecTbl2d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == pState->iEscVal2d)
      {
          pState->getState = FREQADAPTIDX_1D;
      }
      else if (iResult < pState->iEscVal2d)
      {
          pState->vec[pState->vecIdx]   = (pState->uSymToVec2[iResult] >> 4) & 0xf;
          pState->vec[pState->vecIdx+1] = (pState->uSymToVec2[iResult]     ) & 0xf;
          pState->vecIdx += 2;
          if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      }
      else
      {
          pState->getState = GET_VEC2SMALL;
      }
      break;
    case GET_VEC2SMALL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(g_wmaSmallHuffDecTbl2d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      pState->vec[pState->vecIdx]   = (g_wmaSmallSymLeafToVec2[iResult] >> 4) & 0xf;
      pState->vec[pState->vecIdx+1] = (g_wmaSmallSymLeafToVec2[iResult]     ) & 0xf;
      pState->vecIdx += 2;
      if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      else pState->getState = GET_VEC2; // only allow bark increments on 4d, no need to go to FREQADAPTIDX_2D again
      break;
    case GET_VEC1:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->huffDecTbl1d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == pState->iEscVal1d)
      {
          pState->getState = GET_ESC_VEC1;
      }
      else if (iResult < pState->iEscVal1d)
      {
          pState->vec[pState->vecIdx] = iResult;
          pState->vecIdx++;
          if (pState->vecIdx == 2) pState->getState = GET_VEC2;
          else if (pState->vecIdx == 4) pState->getState= GET_SIGN4;
      }
      else
      {
          pState->getState = GET_VEC1SMALL;
      }
      break;
    case GET_VEC1SMALL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(g_wmaSmallHuffDecTbl1d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      pState->vec[pState->vecIdx] = iResult + g_wmaSmallTblMax1d - 1;
      pState->vecIdx++;
      if (pState->vecIdx == 2) pState->getState = GET_VEC2;
      else if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      else pState->getState = GET_VEC1;
      break;
    case GET_ESC_VEC1:
      TRACEWMA_EXIT(wmaResult,
                    prvDecodeEscapeLargeVal(&iResult, g_wmaVec1NSyms,
                                            pibstrm,
                                            paudec, pState));
      pState->vec[pState->vecIdx] = iResult;
      pState->vecIdx++;
      if (pState->vecIdx == 2) pState->getState = GET_VEC2;
      else if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      else pState->getState = GET_VEC1;
      break;
    case GET_SIGN4:
      TRACEWMA_EXIT(wmaResult, ibstrmPeekBits(pibstrm, 4, (U32 *)&iResult));
      {
        U32 mask = 0x80000000;
        int cnt = 0;
        if (pState->vec[0] != 0)
          { pState->sgn[0] = (iResult & mask) >> (31-  0); mask >>= 1; cnt++; }
        if (pState->vec[1] != 0)
          { pState->sgn[1] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        if (pState->vec[2] != 0)
          { pState->sgn[2] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        if (pState->vec[3] != 0)
          { pState->sgn[3] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, cnt));
      }
      pState->getState = DECODE_NONRL;
      pState->vecIdx = 0;
      pState->iCoeff += 4;
      pState->iVecType = 0;
      INCR_BARK;
      break;
    case DECODE_NONRL:
      if (pState->vec[pState->vecIdx] == 0) {
        pState->vecIdx++;
        pState->curRun++;
        if (pau->m_fExpVecsInNonRLMode == WMAB_FALSE)
          if (pState->curRun > threshold) pState->trip = 1; // after finish
        if (pau->m_iCurrReconCoef + pState->curRun + 1 >= cSubband) { // end of block
          pau->m_cRunOfZeros = (I16)pState->curRun;
          pau->m_iLevel = 0;
          pau->m_iSign = 0;
          goto done;
        }
        if (pState->vecIdx == 4) {
          if (pState->trip) pState->getState = DECODE_RL;
          else pState->getState = FREQADAPTIDX_4D;
        }
      } else {
        if (pau->m_fExpVecsInNonRLMode == WMAB_FALSE)
          if (pState->curRun > threshold) pState->trip = 1; // after finish
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pState->curRun = 0;
        pau->m_iLevel = pState->vec[pState->vecIdx];
        pau->m_iSign = pState->sgn[pState->vecIdx] - 1;
        pState->vecIdx++;
        if (pState->vecIdx == 4) {
          if (pState->trip) pState->getState = DECODE_RL;
          else pState->getState = FREQADAPTIDX_4D;
        }
        goto done;
      }
      break;
    case DECODE_RL:
      pau->aupfnGetNextRun = prvGetNextRunDECVecRLV4;
      pState->getState = FREQADAPTIDX_RL;
      TRACEWMA_EXIT(wmaResult,
                    prvGetNextRunDECVecRLV4(pobjin, ppcinfo));
      goto exit;
    }
  }

done:
#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) 
    putEntropyTestV3(pau->m_cRunOfZeros, pau->m_iLevel, pau->m_iSign);
#endif

  CHECK_VALS;

exit:
  return wmaResult;
} // prvGetNextRunDECVecNonRLV4

WMARESULT prvGetNextRunDECVecRLV4(Void*           pobjin, 
                                  PerChannelInfo* ppcinfo)
{
  GET_NEXT_RUN_INIT;
  U32 uSign;
  Int bitCnt, run;

#ifdef WMA_ENTCODE_DEBUG
  if (wmaEntCodeCount >= 8749062) {
    WMAPrintf("");
  }
#endif

#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) startEntropyTest();
#endif

  while (1) {
    switch (pState->getState) {
    case FREQADAPTIDX_RL:
      TRACEWMA_EXIT(wmaResult, prvGetFreqAdaptTblIdx(pobjin, ppcinfo, 3));
      pState->getState = DECODE_RL;      
      break;
    case DECODE_RL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->huffDecTblRL,
                             pibstrm,
                             (U32*)&bitCnt, (U32*)&iResult, (U32*)&uSign));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == 0) { // escape
        pState->getState = DECODE_ESC_RLLEVEL;
        pau->m_iSign = 0;
        break;
      }
      else if (iResult == 1) { // end of block
        pau->m_iLevel = 0;
        pau->m_cRunOfZeros = (I16) (ppcinfo->m_cSubbandActual - pau->m_iCurrReconCoef - 1);
        pState->iCoeff = ppcinfo->m_cSubbandActual;
        pau->m_iSign = 0;
        goto done;
      }
      else if (iResult < pState->iEscValRL) { // actual block
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
        run = ppcinfo->m_rgiRunEntry[iResult - 2] & 0x7FFFFFFF;
        pState->curRun += run;
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pState->curRun = 0;
        assert (pau->m_cRunOfZeros >= 0);
        pau->m_iLevel = ppcinfo->m_rgiLevelEntry[iResult - 2];
        pau->m_iSign = (I32)(uSign >> 31) - 1;
        pState->iCoeff += run + 1;
        goto done;
      } else {
        pState->getState = DECODE_RLSMALL;
        break;
      }
    case DECODE_RLSMALL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->smallHuffDecTblRL, pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, (U32*)&uSign));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
      run = pState->smallSymLeafRunLevelToRun[iResult] & 0x7FFFFFFF;
      pState->curRun += run;
      pau->m_cRunOfZeros = (I16)pState->curRun;
      pState->curRun = 0;
      assert (pau->m_cRunOfZeros >= 0);
      pau->m_iLevel = pState->smallSymLeafRunLevelToLevel[iResult];
      pau->m_iSign = (I32)(uSign >> 31) - 1;
      pState->iCoeff += run + 1;
      pState->getState = DECODE_RL;
      goto done;
    case DECODE_ESC_RLLEVEL:
      TRACEWMA_EXIT(wmaResult,
                    prvDecodeEscapeLargeVal(&iResult, 0,
                                            pibstrm,
                                            paudec, pState));
      pau->m_iLevel = iResult;
      pState->iCoeff++;
      pState->getState = DECODE_ESC_RLRUN;
    case DECODE_ESC_RLRUN:
      TRACEWMA_EXIT(wmaResult,
                    prvEscapeDecodeRunV3(&iResult, paudec->m_cMaxRun,
                                         pibstrm));
      pState->iCoeff += iResult;
      pState->curRun += iResult;
      pau->m_cRunOfZeros = (I16)pState->curRun;
      pState->curRun = 0;
      pState->getState = DECODE_ESC_RLSIGN;
    case DECODE_ESC_RLSIGN:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 1, (U32 *)&iResult));
      pau->m_iSign = iResult - 1;
      pState->getState = DECODE_RL;
      goto done;
    }
  }

done:
  INCR_BARK;
#if 0
  if (pState->iCoeff == ppcinfo->m_cSubbandActual)
      assert(pState->iBark == pau->m_cValidBarkBand);
#endif
  pState->iVecType = 0;
  pState->getState = FREQADAPTIDX_RL;

#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest)
    putEntropyTestV3(pau->m_cRunOfZeros, pau->m_iLevel, pau->m_iSign);
#endif

exit:
  CHECK_VALS;

  return wmaResult;
} // prvGetNextRunDECVecRLV4

#endif // USE_V4ENTCODING

#if !defined(WMA_OPT_STRMDECPRO_XENON)
WMARESULT prvGetNextRunDECVecNonRL(Void*           pobjin, 
                                   PerChannelInfo* ppcinfo)
{
  GET_NEXT_RUN_INIT;
  Int bitCnt;
  Int cSubband = ppcinfo->m_cSubbandActual;
  Int threshold = cSubband / 256;

  
#ifdef WMA_ENTCODE_DEBUG
  if (wmaEntCodeCount >= 523863) {
    WMAPrintf("");
  }
#endif

#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) startEntropyTest();
#endif

  while (1) {
    switch (pState->getState) {
    case GET_VEC4:
      pState->vecIdx = 0;
      if (pau->m_fExpVecsInNonRLMode &&
          pState->cVecsInNonRLMode==ppcinfo->m_iVecsInNonRLMode) {
        pState->getState = DECODE_RL;
        pau->aupfnGetNextRun = prvGetNextRunDECVecRL;
        TRACEWMA_EXIT(wmaResult,
                      prvGetNextRunDECVecRL(pobjin, ppcinfo));
        goto exit;
      }
      if (pau->m_iCurrReconCoef + pState->curRun + 1 >= cSubband) { // end of block
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pau->m_iLevel = 0;
        pau->m_iSign = 0;
        goto done;
      }
      TRACEWMA_EXIT(wmaResult, huffDecGet(g_wmaHuffDecTbls_0_0,
                                          pibstrm,
                                          (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == (Int)g_wmaVec4NSyms) pState->getState = GET_VEC2;
      else {
        pState->vec[0] = (g_wmaSymToVec4[iResult] >> 12) & 0xf;
        pState->vec[1] = (g_wmaSymToVec4[iResult] >>  8) & 0xf;
        pState->vec[2] = (g_wmaSymToVec4[iResult] >>  4) & 0xf;
        pState->vec[3] = (g_wmaSymToVec4[iResult]      ) & 0xf;
        pState->getState = GET_SIGN4;
      }
      pState->cVecsInNonRLMode++;
      break;
    case GET_VEC2:
      TRACEWMA_EXIT(wmaResult, huffDecGet(g_wmaHuffDecTbls_1_0,
                                          pibstrm,
                                          (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == (Int)g_wmaVec2NSyms) pState->getState = GET_VEC1;
      else {
        pState->vec[pState->vecIdx]   = (g_wmaSymToVec2[iResult] >> 4) & 0xf;
        pState->vec[pState->vecIdx+1] = (g_wmaSymToVec2[iResult]     ) & 0xf;
        pState->vecIdx += 2;
        if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      }
      break;
    case GET_VEC1:
      TRACEWMA_EXIT(wmaResult, huffDecGet(g_wmaHuffDecTbls_2_0,
                                          pibstrm,
                                          (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == (Int)g_wmaVec1NSyms) pState->getState = GET_ESC_VEC1;
      else {
        pState->vec[pState->vecIdx] = iResult;
        pState->vecIdx++;
        if (pState->vecIdx == 2) pState->getState = GET_VEC2;
        else if (pState->vecIdx == 4) pState->getState= GET_SIGN4;
      }
      break;
    case GET_ESC_VEC1:
      TRACEWMA_EXIT(wmaResult,
                    prvDecodeEscapeLargeVal(&iResult, g_wmaVec1NSyms,
                                            pibstrm,
                                            paudec, pState));
      pState->vec[pState->vecIdx] = iResult;
      pState->vecIdx++;
      if (pState->vecIdx == 2) pState->getState = GET_VEC2;
      else if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      else pState->getState = GET_VEC1;
      break;
    case GET_SIGN4:
      TRACEWMA_EXIT(wmaResult, ibstrmPeekBits(pibstrm, 4, (U32 *)&iResult));
      {
        U32 mask = 0x80000000;
        int cnt = 0;
        if (pState->vec[0] != 0)
          { pState->sgn[0] = (iResult & mask) >> (31-  0); mask >>= 1; cnt++; }
        if (pState->vec[1] != 0)
          { pState->sgn[1] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        if (pState->vec[2] != 0)
          { pState->sgn[2] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        if (pState->vec[3] != 0)
          { pState->sgn[3] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, cnt));
      }
      pState->getState = DECODE_NONRL;
      pState->vecIdx = 0;
      break;
    case DECODE_NONRL:
      if (pState->vec[pState->vecIdx] == 0) {
        pState->vecIdx++;
        pState->curRun++;
        if (pau->m_fExpVecsInNonRLMode == WMAB_FALSE)
          if (pState->curRun > threshold) pState->trip = 1; // after finish
        if (pau->m_iCurrReconCoef + pState->curRun + 1 >= cSubband) { // end of block
          pau->m_cRunOfZeros = (I16)pState->curRun;
          pau->m_iLevel = 0;
          pau->m_iSign = 0;
          goto done;
        }
        if (pState->vecIdx == 4) {
          if (pState->trip) pState->getState = DECODE_RL;
          else pState->getState = GET_VEC4;
        }
      } else {
        if (pau->m_fExpVecsInNonRLMode == WMAB_FALSE)
          if (pState->curRun > threshold) pState->trip = 1; // after finish
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pState->curRun = 0;
        pau->m_iLevel = pState->vec[pState->vecIdx];
        pau->m_iSign = pState->sgn[pState->vecIdx] - 1;
        pState->vecIdx++;
        if (pState->vecIdx == 4) {
          if (pState->trip) pState->getState = DECODE_RL;
          else pState->getState = GET_VEC4;
        }
        goto done;
      }
      break;
    case DECODE_RL:
      pau->aupfnGetNextRun = prvGetNextRunDECVecRL;
      TRACEWMA_EXIT(wmaResult,
                    prvGetNextRunDECVecRL(pobjin, ppcinfo));
      goto exit;
    }
  }

done:
#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) 
    putEntropyTestV3(pau->m_cRunOfZeros, pau->m_iLevel, pau->m_iSign);
#endif

  CHECK_VALS;

exit:
  return wmaResult;
} // prvGetNextRunDECVecNonRL
#endif // !defined(WMA_OPT_STRMDECPRO_XENON)

WMARESULT prvGetNextRunDECVecRL(Void*           pobjin, 
                                PerChannelInfo* ppcinfo)
{
  GET_NEXT_RUN_INIT;
  U32 uSign;
  Int bitCnt;

#ifdef WMA_ENTCODE_DEBUG
  if (wmaEntCodeCount >= 523863) {
    WMAPrintf("");
  }
#endif

#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) startEntropyTest();
#endif

  while (1) {
    switch (pState->getState) {
    case DECODE_RL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(ppcinfo->m_rgiHuffDecTbl, pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, (U32*)&uSign));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == 0) {
        pState->getState = DECODE_ESC_RLLEVEL;
        pau->m_iSign = 0;
        break;
      }
      else if (iResult == 1) {
        pau->m_iLevel = 0;
        pau->m_cRunOfZeros = (I16) (ppcinfo->m_cSubbandActual - pau->m_iCurrReconCoef - 1);
        pau->m_iSign = 0;
        goto exit;
      }
      else {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
        pState->curRun += ppcinfo->m_rgiRunEntry[iResult - 2] & 0x7FFFFFFF;
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pState->curRun = 0;
        assert (pau->m_cRunOfZeros >= 0);
        pau->m_iLevel = ppcinfo->m_rgiLevelEntry[iResult - 2];
        pau->m_iSign = (I32)(uSign >> 31) - 1;
        goto exit;
      }
    case DECODE_ESC_RLLEVEL:
      TRACEWMA_EXIT(wmaResult,
                    prvDecodeEscapeLargeVal(&iResult, 0,
                                            pibstrm,
                                            paudec, pState));
      pau->m_iLevel = iResult;
      pState->getState = DECODE_ESC_RLRUN;
    case DECODE_ESC_RLRUN:
      TRACEWMA_EXIT(wmaResult,
                    prvEscapeDecodeRunV3(&iResult, paudec->m_cMaxRun,
                                         pibstrm));
      pState->curRun += iResult;
      pau->m_cRunOfZeros = (I16)pState->curRun;
      pState->curRun = 0;
      pState->getState = DECODE_ESC_RLSIGN;
    case DECODE_ESC_RLSIGN:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 1, (U32 *)&iResult));
      pau->m_iSign = iResult - 1;
      pState->getState = DECODE_RL;
      goto exit;
    }
  }

exit:
#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest && !WMA_FAILED(wmaResult)) 
    putEntropyTestV3(pau->m_cRunOfZeros, pau->m_iLevel, pau->m_iSign);
#endif

  CHECK_VALS;

  return wmaResult;
} // prvGetNextRunDECVecRL


WMARESULT prvGetNextMaskRunDEC(Void* pobjin, 
                               PerChannelInfo* ppcinfo)
{
    U32 uSign  = 0;     //1 for positive 0 for nonpositive
    I32 iSign  = 0;
    U32 iEntry = 0;     //index to the Vlc table entry
    U32 iResult;
    U16 cBitsTotal;
    WMARESULT     wmaResult = WMA_OK;
    CAudioObjectDecoder* paudec  = (CAudioObjectDecoder*) pobjin;
    CAudioObject*        pau = paudec->pau;
    CWMAInputBitStream*  pibstrm = &(paudec->m_ibstrm);
    DEBUG_ONLY( Bool fPrint = (pau->m_iFrameNumber  == 19 && pau->m_rgpcinfo->m_iCurrSubFrame == 1); );

    switch (paudec->m_maskrlsts)  {
        case VLC:
            TRACEWMA_EXIT(wmaResult, huffDecGet (g_rgunHuffDecTblMaskRLCV3, &paudec->m_ibstrm,
                &iResult, &iEntry, &uSign));
            TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(&paudec->m_ibstrm, iResult));   //flush bits used by huffDecGet
            if (iEntry == 0)
                goto escape;
            if (iEntry == 1)
            {
                /*
                // [1], end of mask for this channel of the subFrame 
                */
                pau->m_iMaskLevel = 0;
                pau->m_cRunOfMaskZeros = (I16) (pau->m_cValidBarkBand - pau->m_iCurrReconMaskBand - 1);
            }
            else 
            {
                assert (iEntry >= 2);
                TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(&paudec->m_ibstrm, 1));   //flush the sign bit also
                pau->m_cRunOfMaskZeros = g_rgunRunMaskV3 [iEntry - 2] & 0x7FFFFFFF;
                assert (pau->m_cRunOfMaskZeros >= 0);
                pau->m_iMaskLevel = g_rgunLevelMaskV3 [iEntry - 2];
                pau->m_iMaskSign = (I32) (uSign >> 31) - 1;
            }
            break;

        case ESCAPE:
escape:
            paudec->m_maskrlsts = ESCAPE;
            cBitsTotal = 14; // 8 + 5 + 1
            assert (cBitsTotal <= 27);

            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBitsTotal, &iResult));

            cBitsTotal = 6;
            pau->m_iMaskLevel = (I16) (iResult >> cBitsTotal);
            pau->m_iMaskSign = (I32) (iResult & 0x00000001) - 1;

            pau->m_cRunOfMaskZeros = (I16) (iResult & (0xFFFFFFFF >> (32 - cBitsTotal))) >> 1;
            pau->m_cRunOfMaskZeros &= 0x7FFFFFFF;
            paudec->m_maskrlsts = VLC;
    }

#ifdef WMA_ENTROPY_TEST
    if (g_maskTest) {
        //assert(pau->m_cRunOfMaskZeros != 0 || pau->m_iMaskLevel != 0);
        putEntropyTest(iEntry,
                       pau->m_cRunOfMaskZeros, pau->m_iMaskLevel,
                       pau->m_iMaskSign);
    }
#endif

exit:
    DBG_RUNLEVEL_DEC(g_cBitGet-21,pau->m_cRunOfMaskZeros,pau->m_iMaskLevel,fPrint);
    return wmaResult;
} // prvGetNextMaskRunDEC

//*****************************************************************************************
//
// prvDecodeMaskRunLevel
//
//*****************************************************************************************

WMARESULT prvDecodeMaskRunLevel  (CAudioObjectDecoder* paudec, 
                                  PerChannelInfo* ppcinfo,
                                  Int iBandLim)
{
    Int* rgiMaskQ             = ppcinfo->m_rgiMaskQ;
    const U16* rgiRunEntry    = g_rgunRunMaskV3;    
    const U16* rgiLevelEntry  = g_rgunLevelMaskV3;    
    CAudioObject* pau = paudec->pau;
    I16* piMaskBand = &pau->m_iCurrReconMaskBand;   
#ifdef DEBUG_DECODE_TRACE
    DEBUG_ONLY( Bool fPrint = (g_ulOutputSamples==0x4e00); )
#else
    DEBUG_ONLY( Bool fPrint = (pau->m_iFrameNumber  <= 10 && pau->m_rgpcinfo->m_iCurrSubFrame == 0); )
#endif
    WMARESULT   wmaResult = WMA_OK;

#ifdef WMA_ENTROPY_TEST
    if (g_maskTest && *piMaskBand == 0) initEntropyTest();
#endif

    // This function is too frequently called to be profiled
    //FUNCTION_PROFILE(fp);
    //FUNCTION_PROFILE_START(&fp,DECODE_RUN_LEVEL_PROFILE);
    while (*piMaskBand < iBandLim) 
    {
        TRACEWMA_EXIT(wmaResult, prvGetNextMaskRunDEC(paudec,ppcinfo));
        pau->m_iMaskLevel = (I16) ((pau->m_iMaskLevel ^ pau->m_iMaskSign) - pau->m_iMaskSign);
        DBG_RUNLEVEL_DEC(g_cBitGet-21,pau->m_cRunOfMaskZeros,pau->m_iMaskLevel,fPrint);
        if ( (*piMaskBand+ pau->m_cRunOfMaskZeros) >= iBandLim)  
        {
            break;
        }
        *piMaskBand += (I16) pau->m_cRunOfMaskZeros;

        // Add to the prediction already available
        rgiMaskQ [*piMaskBand] += pau->m_iMaskLevel; 
        (*piMaskBand)++;
        paudec->m_maskrlsts = VLC;
    }

exit:
#ifdef WMA_ENTROPY_TEST
    if (g_maskTest &&
        !WMA_FAILED(wmaResult)) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif
    //FUNCTION_PROFILE_STOP(&fp);
    return wmaResult;
} // prvDecodeMaskRunLevel

#endif // BUILD_WMAPRO
