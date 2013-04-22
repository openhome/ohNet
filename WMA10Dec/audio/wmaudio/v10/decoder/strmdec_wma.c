//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) 1996-1999  Microsoft Corporation

Module Name:

	strmdec_wma.c

Abstract:

	Decoder BitStream

Author:

	Craig Dowell (craigdo@microsoft.com) 10-December-1996
	Ming-Chieh Lee (mingcl@microsoft.com) 10-December-1996
	Bruce Lin (blin@microsoft.com) 10-December-1996

Revision History:
    Wei-ge Chen (wchen@microsoft.com) 20-July-1999
    Make it in C.


*************************************************************************/
#ifdef _XBOX
#include <xtl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "strmdec_wma.h"
#include "msaudiodec.h"

#define AUDIO_MAGIC_NUM 0x9d6ca34e

#if!defined(S_SUNOS5) && !WMA_OPT_STRMDEC_ARM && !defined(PLATFORM_SPECIFIC_IBSTRM) 
const UInt getMask[33] = {
    0x00000000,
    0x00000001,
    0x00000003,
    0x00000007,
    0x0000000f,
    0x0000001f,
    0x0000003f,
    0x0000007f,
    0x000000ff,
    0x000001ff,
    0x000003ff,
    0x000007ff,
    0x00000fff,
    0x00001fff,
    0x00003fff,
    0x00007fff,
    0x0000ffff,
    0x0001ffff,
    0x0003ffff,
    0x0007ffff,
    0x000fffff,
    0x001fffff,
    0x003fffff,
    0x007fffff,
    0x00ffffff,
    0x01ffffff,
    0x03ffffff,
    0x07ffffff,
    0x0fffffff,
    0x1fffffff,
    0x3fffffff,
    0x7fffffff,
    0xffffffff
};
#endif

#ifdef _WMA_DRM_DESCRAMBLE_
U8 __fastcall NoDescramble ( U8* pb, CWMAInputBitStream* pibs )
{
    return *pb;
}

// We are not sure what happened to v1

U8 __fastcall DescrambleV2 ( U8* pb, CWMAInputBitStream* pibs )
{
    return pibs->m_pfnDescrambleV2( *pb );
}

static void blkcpy(U8* pDst, U8* pSrc, size_t cb)
{
    while (cb)
    {
        *pDst = *pSrc ^ (U8)(DWORD_PTR)pDst;
        pSrc++;
        pDst++;
        cb--;
    }
}


U8 __fastcall DescrambleV3 ( U8* pb, CWMAInputBitStream* pibs )
{
    size_t idx = (size_t)pb % RC4_BLOCK_SIZE;
    if (0 == idx)
    {
        UInt cb = min(RC4_BLOCK_SIZE, pibs->m_cbBuflen);
        blkcpy( pibs->m_rc4buf, pb, cb );
        pibs->m_pfnrc4( pibs->m_prc4ctx, cb, pibs->m_rc4buf );
    }
    
    return pibs->m_rc4buf[idx] ^ (U8)(DWORD_PTR)(pibs->m_rc4buf+idx);
}
#endif

Void ibstrmInit (CWMAInputBitStream* pibstrm, CAudioObjectDecoder* pOwner)
{
    //added for streaming mode
    pibstrm->m_pfnGetMoreData = NULL;
    pibstrm->m_pUser  = 0;
    pibstrm->m_dwOwner = pOwner;    
    pibstrm->m_dwHeaderBuf   = 0;
    pibstrm->m_dwHeaderBufTemp   = 0;
    pibstrm->m_pBufferBegin  = NULL;
    pibstrm->m_cbBuflenBegin = 0;    // used in association of m_pBufferBegin
    pibstrm->m_fNoMoreInput = WMAB_FALSE;
	
    //end of streaming mode

    pibstrm->m_pBuffer = NULL;
    pibstrm->m_iPrevPacketNum = (1 << NBITS_PACKET_CNT) - 1; // Keep -1 spacing w/ curr pkt num
    pibstrm->m_fAllowPackets = pOwner->pau->m_fAllowSuperFrame;
    pibstrm->m_fSuppressPacketLoss = WMAB_TRUE; // Suppress first packet from loss detection

#ifdef _WMA_DRM_DESCRAMBLE_
    pibstrm->m_pfnDescramble = NoDescramble;
#endif
    ibstrmReset(pibstrm);

#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder
    pibstrm->m_cTtlBits = 0;
    pibstrm->m_iFrameStart = 0;
    pibstrm->m_iFrameEnd = 0;
#endif //WMA_COMPRESSION_TOOL
    pibstrm->m_cbInputBuffer = 0;
    pibstrm->m_pbInputBuffer = NULL;
}

Void ibstrmReset(CWMAInputBitStream *pibstrm)
{   
#ifdef _WMA_DRM_DESCRAMBLE_
    // Call ibstrmDetach() here because usually (always ?) audecDecodeInfo() calls
    // ibstrmReset() *before* we hit ON_HOLD in audecDecode() m_fNeedHeader branch,
    // so m_pfnDescramble and m_cbBuflen get reset before ON_HOLD happens, and the
    // ibstrmDetach() call from audecDecode() does nothing.  I thought about getting
    // rid of the ibstrmDetach() call in audecDecode() and just always relying on the
    // one here, but I am not 100% sure that ibstrmReset() is *always* called at the
    // end of a packet.  So we call ibstrmDetach() here, and again in audecDecode()
    // just for good measure.  Usually the one here is the one that counts, but if
    // ibstrmReset() for some reason does not happen, the one in audecDecode() should
    // take care of things.
    ibstrmDetach(pibstrm); 
    pibstrm->m_pfnDescramble = NoDescramble;
#endif
    
    pibstrm->m_dwDot = 0;
    pibstrm->m_dwBitsLeft = 0;
    pibstrm->m_dwDotT = 0;
    pibstrm->m_cBitDotT = 0;
    pibstrm->m_cbBuflen = 0;

    if (pibstrm->m_dwOwner->m_fSPDIF)
    {
        pibstrm->m_fDeferredGap = WMAB_FALSE; // cancel any currently scheduled gap
        pibstrm->m_fNoMoreInput = WMAB_FALSE; // not appropriate for non-SPDIF reset
    
        // reset these to prevent false positives in ibstrmMoreInputAfterGap()
        pibstrm->m_pBuffer = NULL;
        pibstrm->m_cbBuflen = 0;
        pibstrm->m_pBufferBegin  = NULL;
        pibstrm->m_cbBuflenBegin = 0;
        
        // This initialization is not strictly necessary.  In fact,
        // 0 is not even a good value for this variable.
        // The real initialization happens in ibstrmSetGap(),
        // when processing the frame header.
        pibstrm->m_cbLastProcessedGapLocationBackFromEndOfLastBuffer = 0;
    }
    pibstrm->m_uLastHeaderByte = 0; // may not be necessary - initializing just in case

#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder
    // we do not reset cTtlBits here since ibstrmReset does not mean the bit stream is corrupted.
    pibstrm->m_dumpFrmBitSts = NEED_FRAME_STA;   
    pibstrm->m_fNewPacketCurr = WMAB_FALSE;
    pibstrm->m_dwBitsLeftPrev = 0;
    pibstrm->m_f1stNewFrmInPkt = WMAB_FALSE;
#endif //WMA_COMPRESSION_TOOL
}

/*
Void ibstrmAttach(CWMAInputBitStream *pibstrm, U32 dwDot, U32 dwBitsLeft, U8* pbSrc, I32 cbSrc)
{
    //added for streaming mode
    pibstrm->m_dwHeaderBuf   = 0;
    pibstrm->m_dwHeaderBufTemp   = 0;
    pibstrm->m_pBufferBegin  = NULL;
    pibstrm->m_cbBuflenBegin = 0;    // used in association of m_pBufferBegin	
    //end of streaming mode

    pibstrm->m_pBuffer = pbSrc;
    pibstrm->m_cbBuflen = cbSrc;
    pibstrm->m_dwDot = dwDot;
    pibstrm->m_dwBitsLeft = dwBitsLeft;
}
*/

#ifdef WMA_COMPRESSION_TOOL
WMARESULT ibstrmDumpBits(CWMAInputBitStream *pibs, U8 * pbSrc, I32 cbSrc, I32 iStart, I32 iEnd)
{
    WMARESULT wmaResult = WMA_OK;

#if 0 //9/20/2004
    FILE * fp = FOPEN("c:\\temp\\dumpbits.meta","a+");
    if (NULL != fp)
    {
        WMAFprintf(fp, "Dumped %5d bits \n", iEnd - iStart);
        FCLOSE(fp);
    }
#endif 
    assert(pbSrc != NULL);
    if (NULL != pbSrc)
    {
        ASSERTWMA_EXIT (wmaResult, prvAddBitsToFrameBitsBuf ((void *)pibs->m_dwOwner, pbSrc, cbSrc, iStart, iEnd));
    }
exit:
    return wmaResult;
}

WMARESULT ibstrmDumpFrmBitsAfterFrameEnd(CWMAInputBitStream *pibs, I32 iWinFrameNumber, Int iVersion)
{
    WMARESULT wmaResult = WMA_OK;
    I32 iPCMFrameNumber;
    I32 cBufLenBits = (pibs->m_cbInputBuffer << 3);
    U8 nHdrBits = WMA_get_nHdrBits(pibs->m_dwOwner);

    I64 iPosA = (pibs->m_cTtlBits - cBufLenBits - pibs->m_dwBitsLeftPrev);
    I64 iPosB = (pibs->m_cTtlBits - cBufLenBits);

    iPCMFrameNumber = prvGetPCMFrameNumber(iWinFrameNumber, WMAB_FALSE, iVersion);

    assert(pibs->m_dumpFrmBitSts == NEED_FRAME_STA);
    assert(pibs->m_iFrameEnd <= pibs->m_cTtlBits);

    if (pibs->m_iFrameStart >= iPosB)
    {   // frame starts from curr input segment.
        if (pibs->m_fNewPacketCurr == WMAB_TRUE)
        {   // frame can not start from a position inside the pkt hdr.
            assert(pibs->m_iFrameStart >= (iPosB + nHdrBits));
        }
        ibstrmDumpBits(pibs,
            pibs->m_pbInputBuffer, 
            pibs->m_cbInputBuffer, 
            (I32)(pibs->m_iFrameStart - iPosB), 
            (I32)(pibs->m_iFrameEnd - iPosB));
    }
    else if ((pibs->m_iFrameStart < iPosB) && (pibs->m_iFrameStart >= iPosA) )
    {   // frame starts from previous input's leftover.
        if (pibs->m_iFrameEnd < iPosB) 
        {
            ibstrmDumpBits(pibs,
                pibs->m_rgbInputTailPrev, 
                8, 
                (I32)(pibs->m_iFrameStart - (iPosB - 64)), 
                (I32)(pibs->m_iFrameEnd - (iPosB - 64)));                        
        }
        else 
        {
            ibstrmDumpBits(pibs,
                pibs->m_rgbInputTailPrev, 
                8, 
                (I32)(pibs->m_iFrameStart - (iPosB - 64)), 
                64);                        

            ibstrmDumpBits(pibs,
                pibs->m_pbInputBuffer, 
                pibs->m_cbInputBuffer, 
                (pibs->m_fNewPacketCurr == WMAB_TRUE) ? nHdrBits : 0,
                (I32)(pibs->m_iFrameEnd - iPosB));
        }
    }
    else if (pibs->m_iFrameStart < iPosA)
    {   // start more earlier.
        if (pibs->m_iFrameEnd < iPosB)
        {
            ibstrmDumpBits(pibs,
                pibs->m_rgbInputTailPrev, 
                8, 
                64 - pibs->m_dwBitsLeftPrev, 
                (I32)(pibs->m_iFrameEnd - (iPosB - 64)));                        
        }
        else
        {
            ibstrmDumpBits(pibs,
                pibs->m_rgbInputTailPrev, 
                8, 
                64 - pibs->m_dwBitsLeftPrev, 
                64);                        
            ibstrmDumpBits(pibs,
                pibs->m_pbInputBuffer, 
                pibs->m_cbInputBuffer, 
                (pibs->m_fNewPacketCurr == WMAB_TRUE) ? nHdrBits : 0,
                (I32)(pibs->m_iFrameEnd - iPosB));
            
        }
    }
    else
    {
        assert(WMAB_FALSE);
    }

    
    return wmaResult;
}

WMARESULT ibstrmDumpFrmBitsPreGetMoreData(CWMAInputBitStream *pibs, I32 iWinFrameNumber, Int iVersion)
{
    WMARESULT wmaResult = WMA_OK;
    I32 iPCMFrameNumber;
    I32 cBufLenBits = (pibs->m_cbInputBuffer << 3);
    U8 nHdrBits = WMA_get_nHdrBits(pibs->m_dwOwner);

    iPCMFrameNumber = prvGetPCMFrameNumber (iWinFrameNumber, WMAB_FALSE, iVersion);

    // If we are waiting for the frame end, we dump all bits of current input.
    // We do nothing if the statusis NEED_FRAME_STA.
    if (pibs->m_dumpFrmBitSts == NEED_FRAME_END)
    {
        I64 iPosA = (pibs->m_cTtlBits - cBufLenBits - pibs->m_dwBitsLeftPrev);
        I64 iPosB = (pibs->m_cTtlBits - cBufLenBits);
        I64 iPosC = (pibs->m_cTtlBits - pibs->m_dwBitsLeft);

        if (pibs->m_iFrameStart >= iPosB)
        {   // start in curr input segment.
            if (pibs->m_fNewPacketCurr == WMAB_TRUE)
            {   // frame can not start from a position inside the pkt hdr.
                assert(pibs->m_iFrameStart >= (iPosB + nHdrBits));
            }
            ibstrmDumpBits(pibs,
                pibs->m_pbInputBuffer, 
                pibs->m_cbInputBuffer, 
                (I32)(pibs->m_iFrameStart - iPosB), 
                (I32)(iPosC - iPosB));
        }
        else if ((pibs->m_iFrameStart < iPosB) && (pibs->m_iFrameStart >= iPosA))
        {   // start in previous input's leftover.
            ibstrmDumpBits(pibs,
                pibs->m_rgbInputTailPrev, 
                8, 
                (I32)(pibs->m_iFrameStart - (iPosB - 64)), 
                64);            
            ibstrmDumpBits(pibs,
                pibs->m_pbInputBuffer,
                pibs->m_cbInputBuffer, 
                (pibs->m_fNewPacketCurr == WMAB_TRUE) ? nHdrBits : 0,
                cBufLenBits - pibs->m_dwBitsLeft);

        }
        else if (pibs->m_iFrameStart < iPosA)
        {   // start more earlier.
            ibstrmDumpBits(pibs,
                pibs->m_rgbInputTailPrev, 
                8, 
                64 - pibs->m_dwBitsLeftPrev, 
                64);
            ibstrmDumpBits(pibs,
                pibs->m_pbInputBuffer,
                pibs->m_cbInputBuffer, 
                (pibs->m_fNewPacketCurr == WMAB_TRUE) ? nHdrBits : 0,
                cBufLenBits - pibs->m_dwBitsLeft);                
        }
        else
        {
            assert(WMAB_FALSE);
        }
    }

    // save the leftover bits of this input.
    if (pibs->m_cbInputBuffer >= 8)
    {
        memcpy(pibs->m_rgbInputTailPrev, pibs->m_pbInputBuffer + pibs->m_cbInputBuffer - 8, 8);
    }
    else
    {
        assert(WMAB_FALSE); // let me know if this happens. chao.
    }
    pibs->m_dwBitsLeftPrev = pibs->m_dwBitsLeft;

    return wmaResult;
}
#endif //WMA_COMPRESSION_TOOL

#ifdef _WMA_DRM_DESCRAMBLE_
#   define DESCRAMBLE( x )   pibs->m_pfnDescramble ( &(x) , pibs )
#else
#   define ASSERT_PFNDESCRAMBLE
#   define DESCRAMBLE( x ) ( x )
#endif

#if !defined(UNDER_CE)
//#pragma code_seg(push, no_bbtopt, ".no_bbt")
#endif

FORCEINLINE WMARESULT _ibstrmAttach(CWMAInputBitStream *pibs, U8* pbSrc, I32 cbSrc, 
                       Bool fNewPacket, Bool fNoMoreInput, Bool fSPDIF, Int iVersion,
                       void* pfnDescramble)
{
    I32 iFirstBit = 0;
    WMARESULT   wmaResult = WMA_OK;

    assert (pibs->m_cbBuflen == 0);
    
    if ((cbSrc == 0) || (fNoMoreInput))
    { 
        pibs->m_fNoMoreInput = WMAB_TRUE;
    }

    if(cbSrc <= 0)
    {
        wmaResult = WMA_OK;
        goto exit;
    }

    pibs->m_pBuffer = pbSrc;
    pibs->m_cbBuflen = cbSrc;

#ifdef _WMA_DRM_DESCRAMBLE_
    if ( pfnDescramble )
    {
        DescrambleStruct* p = (DescrambleStruct*)pfnDescramble;
        if ( 3 == p->uVer )
        {
            pibs->m_prc4ctx = p->pctx;
            pibs->m_pfnrc4 = p->pfn;
            pibs->m_pfnDescramble = DescrambleV3;
            
            {
                U8* pb = pibs->m_pBuffer;
                size_t idx = (size_t)pb % RC4_BLOCK_SIZE;
                if (0 != idx)
                {
                    size_t cb = min(RC4_BLOCK_SIZE - idx, pibs->m_cbBuflen);
                    blkcpy(pibs->m_rc4buf + idx, pb, cb);
                    pibs->m_pfnrc4( pibs->m_prc4ctx, cb, pibs->m_rc4buf + idx );
                }
            }
        }
        else if ( 2 == p->uVer )
        {
            pibs->m_pfnDescrambleV2 = p->pfn;
            pibs->m_pfnDescramble = DescrambleV2;
        }
        else
        {
            assert( !"unknown descramble version" );
            goto nodescramble;
        }
    }
    else
    {
    nodescramble:
        pibs->m_pfnDescramble = NoDescramble;
    }
    assert( pibs->m_pfnDescramble );
#endif

#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder Related
#if 0
    if (pibs->m_cTtlBits + (cbSrc << 3) < pibs->m_cTtlBits)
        assert(WMAB_FALSE);
#endif
    pibs->m_cTtlBits += (((I64)cbSrc) << 3);
    pibs->m_fNewPacketCurr = fNewPacket;   
#endif //WMA_COMPRESSION_TOOL
    pibs->m_pbInputBuffer = pbSrc;
    pibs->m_cbInputBuffer = cbSrc;

#ifndef _XBOX
    if (0)
    {
        FILE *fp;
//        fp = FOPEN("C:\\temp\\log.data","ab+");
//        FWRITE(pibs->m_pBuffer,pibs->m_cbBuflen, 1, fp);
//        FCLOSE(fp);
        
        fp = FOPEN("C:\\temp\\log.txt","at+");
        WMAFprintf(fp,"%d\n",pibs->m_cbBuflen);
        FCLOSE(fp);
    }
#endif

#ifdef WMA2CMP
    {   // write out bits to a .cmp file
        extern FILE *pfWma2Cmp;       // file (and flag) to output .cmp file
        if (pfWma2Cmp != NULL)
        {
            size_t uWritten = FWRITE(pibs->m_pBuffer,pibs->m_cbBuflen,1,pfWma2Cmp);
            // Asserts are not a good way to report errors, but this is for internal test purposes only
            assert( uWritten == 1 );
        }
    }
#endif

    if (fNewPacket || fSPDIF)
    {
        pibs->m_pBufferBegin = pibs->m_pBuffer;
        pibs->m_cbBuflenBegin = pibs->m_cbBuflen;
    }

    if (fSPDIF)
    {
        if (0 != WMA_get_nHdrBits(pibs->m_dwOwner) % 8) // no gaps if pkt hdr is a multiple of 8 bits
        {   // Update the position of the last processed gap, since the position is
            // relative to the end of the most recent input buffer, and we have just
            // received a new input buffer.
            pibs->m_cbLastProcessedGapLocationBackFromEndOfLastBuffer += pibs->m_cbBuflen;
        }

        if (pibs->m_fDeferredGap)
        {   // A gap was detected during a previous buffer but the gap's location was
            // beyond the end of that buffer.  See if it falls within the current buffer.
            if ((U32)cbSrc > pibs->m_cbToDeferredGap) {
                assert(pibs->m_pBuffer == pibs->m_pBufferBegin); // just set above
                assert(pibs->m_cbBuflen == pibs->m_cbBuflenBegin); // just set above
                assert(pibs->m_cbBuflen > pibs->m_cbToDeferredGap);
    
                pibs->m_cbBuflen = pibs->m_cbToDeferredGap;
                pibs->m_fDeferredGap = WMAB_FALSE; // just took care of it
            }
            else
            { // reschedule the gap for a later buffer
                pibs->m_cbToDeferredGap -= cbSrc;
            }
        }
    }


    if (WMAB_FALSE == pibs->m_fAllowPackets)
    {
        // In non-superframe mode, provide a running packet count that wraps around (to avoid I32 vs. U32 issues)
        if (fNewPacket)
        {
            assert(((~(NONSUPER_WRAPAROUND - 1) << 1) & NONSUPER_WRAPAROUND) == 0); // assert Pwr of 2
            pibs->m_dwHeaderBuf = (pibs->m_dwHeaderBuf + 1) & (NONSUPER_WRAPAROUND - 1);
        }
    }
    else if (fNewPacket && !fSPDIF) //set up packet header in superframe mode
    {
        Int iPrevPacketNum, iNextPacketNum;
        unsigned char nHdrBits;
        unsigned char nHdrBytes;
        U32 uLastByte; // temporary 32-bit var to avoid having to cast 8=>32 before shifting
        const int cPacketNumBitsRS = (BITS_PER_DWORD - NBITS_PACKET_CNT);
        const int cPacketForcePacketLossRS = (BITS_PER_DWORD - NBITS_PACKET_CNT - NBITS_PACKET_EMPTYNESS - NBITS_FORCE_PACKETLOSS);
        nHdrBits = WMA_get_nHdrBits(pibs->m_dwOwner); // this only updates per file for v2; varialb for v3
        nHdrBytes = (nHdrBits + 7) / 8;

        assert (pibs->m_pBuffer != NULL); //always get a valid one
        pibs->m_dwHeaderBuf = pibs->m_dwHeaderBufTemp; //move a new one into the queue
        pibs->m_dwHeaderBufTemp = 0;
        
        // Don't load any more than necessary to keep [ the number of bytes that are used
        // both here and in ibstrmLoadBits() ] to 1.  Bytes that are used multiple times
        // require special care to avoid breaking stateful DRM descrambling - namely, we
        // must avoid calling DESCRAMBLE on them multiple times.
        uLastByte = DESCRAMBLE( pibs->m_pBuffer[0] );
        pibs->m_dwHeaderBufTemp |= ( uLastByte << 24 );
        if (nHdrBits > 8)
        {
            uLastByte = DESCRAMBLE( pibs->m_pBuffer[1] );
            pibs->m_dwHeaderBufTemp |= ( uLastByte << 16 );
            if (nHdrBits > 16)
            {
                uLastByte = DESCRAMBLE( pibs->m_pBuffer[2] );
                pibs->m_dwHeaderBufTemp |= ( uLastByte <<  8 );
                if (nHdrBits > 24)
                {
                    uLastByte = DESCRAMBLE( pibs->m_pBuffer[3] );
                    pibs->m_dwHeaderBufTemp |= ( uLastByte );
                }
            }
        }

        // Fill the unused bytes in pibs->m_dwHeaderBugTemp with all ones
        // Why are we doing this? Heres why - (WinOS bug #1698864)
        // It is possible for a packet to have a header that is all zeros.
        //
        // Code in prvDecodeInfo compares the value of m_dwHeaderBufTemp to ZERO to determine whether the decoder 
        // currently has a packet for decoding. Checking against a value of ZERO to determine whether we have a 
        // packet is a *wrong* assumption since a packet could have a header with all bits set to zero.
        //
        // In v9, this code here used to populate m_dwHeaderBufTemp with the first 4 bytes from the bitstream. 
        // This meant that even if the header bits were zero, the remaining trailing bits from the bitstream could 
        // be non-zero and hence the check above in prvDecodeInfo returns true (albeit for the wrong reasons i.e. 
        // not because the header was non zero, but because the bits following the header in the bit stream 
        // were non-zero).
        //
        // In v10, a change has been made to load just the required number of header bits from the bitstream. Now 
        // if the header bits are all zero, the check in prvdecodeInfo fails and the decoder incorrectly thinks that 
        // it does not have a packet to decode. By packing the rest of DWORD with ones we are making the value of 
        // m_dwHeaderBufTemp non-zero when all the header bits are zero, so that the check in prvDecodeInfo correctly 
        // identifies the presence of a new packet.
        //
        // We still have the following risks:
        // 1. We assume that a packet header is always <= 32 bits (relatively safe)
        // 2. If the number of header bits is greater than 24, 4 bytes from the buffer will be used to 
        //    populate m_dwHeaderBufTemp. In this case, if the header bits are zero *AND* the first few compressed 
        //    bits from the bitstream are zero, m_dwHeaderBufTemp will be zero and prvDecodeInfo will not detect the 
        //    presence of a packet for decoding. The correct way to solve this is to use a flag to indicate the 
        //    presence of a new packet.

        pibs->m_dwHeaderBufTemp |= (1 << ((4 - nHdrBytes) * BITS_PER_BYTE)) - 1;

        pibs->m_uLastHeaderByte = (U8)uLastByte; // save for later use by ibstrmResetPacket

#ifdef TEST_CORRUPT_BITSTREAM
        if (rand() * CORRUPT_PROBABILITY < RAND_MAX) {
            if (rand() > rand()) {
                pibs->m_dwHeaderBufTemp = pibs->m_dwHeaderBufTemp ^ ((rand() << 16) + rand());
            }
            else {
                pibs->m_dwHeaderBufTemp = pibs->m_dwHeaderBufTemp ^ (1 << (rand() % 32));
            }
        }
#endif //TEST_CORRUPT_BITSTREAM
        iFirstBit = nHdrBits % 8;
        pibs->m_pBuffer += nHdrBytes;
        pibs->m_cbBuflen -= nHdrBytes;
        assert (nHdrBits <= BITS_PER_DWORD);
//        assert (pibs->m_dwBitsLeft <= 24);  //so that we have enough to save the fractional byte that would otherwise be lost

        // Now we should check that we didn't lose a packet
        iNextPacketNum = (pibs->m_dwHeaderBufTemp >> cPacketNumBitsRS);
        iPrevPacketNum = pibs->m_iPrevPacketNum;
        pibs->m_iPrevPacketNum = iNextPacketNum;
        if (WMAB_FALSE == pibs->m_fSuppressPacketLoss)
        {
            Bool bForcedPacketLoss = WMAB_FALSE;
            if (iVersion > 2 &&
                (pibs->m_dwHeaderBufTemp >> cPacketForcePacketLossRS) & 0X1) {
                bForcedPacketLoss = WMAB_TRUE;
            }

            if ((WMAB_FALSE == (iNextPacketNum - iPrevPacketNum == 1 || 
//                iNextPacketNum - iPrevPacketNum == 0 ||
                iNextPacketNum - iPrevPacketNum + (1 << NBITS_PACKET_CNT) == 1))
                || bForcedPacketLoss)
            {
                // PACKET LOSS: Return error. Next call to DecodeInfo will cue to next frame
                assert(pibs->m_pBuffer == pibs->m_pBufferBegin + nHdrBytes);
                assert(pibs->m_cbBuflen == pibs->m_cbBuflenBegin - nHdrBytes);
                
                pibs->m_dwDot = pibs->m_dwHeaderBufTemp >> (8 * (4 - nHdrBytes));
                assert (nHdrBits <= 8 * nHdrBytes);
                pibs->m_dwBitsLeft = 8 * nHdrBytes - nHdrBits;

                WMA_set_PacketLoss (pibs->m_dwOwner, WMAB_TRUE);
                TRACEWMA_EXIT (wmaResult, WMA_S_LOSTPACKET);
                goto exit;
            }
            else
            {
                WMA_set_PacketLoss (pibs->m_dwOwner, WMAB_FALSE);
            }
        }
        else
            // Avoid checking for packet loss, eg, after a seek
            pibs->m_fSuppressPacketLoss = WMAB_FALSE;
        
        if (iFirstBit)
        {
            ibstrmLoadBits(pibs, iFirstBit, (U8)uLastByte);
        }
    }

exit:
    return wmaResult;
}                                       

WMARESULT ibstrmAttach(CWMAInputBitStream *pibs, U8* pbSrc, I32 cbSrc, 
                       Bool fNewPacket, Bool fNoMoreInput, Bool fSPDIF, Int iVersion)
{
    return _ibstrmAttach(pibs, pbSrc, cbSrc, fNewPacket, fNoMoreInput, fSPDIF, iVersion, NULL);
}

#ifdef _WMA_DRM_DESCRAMBLE_
void ibstrmDetach(CWMAInputBitStream *pibs)
{
    if ( DescrambleV3 == pibs->m_pfnDescramble )
    {
        // Descramble the rest of the buffer just to maintain synch with the
        // scrambler.  Only needed for formats for which multiple WMA packets
        // get encrypted together and passed to the DMO as a single buffer.
        // Empirically, this is only required for old non-superframe v1 files
        // like 56k2min.wma, but theoretically the caller could start batching
        // packets for any format at any time.  Hopefully the overhead is small
        // for the cases where dummy descrambling is unnecessary.
        // Note: according to Geoff, the current encryption method has the
        // property that the en/decryptor's state is not data-dependent - i.e.,
        // we could descramble a bunch of 0's instead of real data, as long
        // as we call descramble() the correct number of times.  So, if it ever
        // becomes desirable to defer this dummy descrambling until the input
        // data is gone, that is probably ok as long as the count of unused bytes
        // is kept.
        while (pibs->m_cbBuflen)
        {
            DESCRAMBLE(*(pibs->m_pBuffer)++);
            pibs->m_cbBuflen--;
        }
    }
}

NOINLINE WMARESULT ibstrmAttachP(CWMAInputBitStream *pibs, U8* pbSrc, I32 cbSrc, 
                       Bool fNewPacket, Bool fNoMoreInput, Bool fSPDIF, Int iVersion,
                       void* pfnDescramble)
{
    DescrambleStruct tmp, *p = (DescrambleStruct*)pfnDescramble;
    tmp.uVer = p->uVer;
    tmp.pfn  = p->pfn;
    tmp.pctx = p->pctx;
    if ( 2 == p->uVer )
    {
        tmp.pfn = (void*)((unsigned __int64)(tmp.pfn) ^ AUDIO_MAGIC_NUM);
    }
    return _ibstrmAttach(pibs, pbSrc, cbSrc, fNewPacket, fNoMoreInput, fSPDIF, iVersion, &tmp);
}
#endif

#if !defined(UNDER_CE)
//#pragma code_seg(pop, no_bbtopt)
#endif

#if !WMA_OPT_STRMDEC_ARM
void ibstrmLoadBits(CWMAInputBitStream *pibs, I32 iFirstBit, U8 uByte)
{
    U8 temp;
    assert(iFirstBit < 8);

    if ( 0 == iFirstBit ) // ues
    {
        uByte = *(pibs->m_pBuffer);
    }

    if (pibs->m_cBitDotT == 0 && pibs->m_dwBitsLeft + (8 - iFirstBit) <= 32)
    {
        temp = uByte;

        //zeros out the top (not valid) bits
        temp = temp<<iFirstBit;
        temp = temp>>iFirstBit;
        pibs->m_dwDot = (pibs->m_dwDot<<(8 - iFirstBit))|temp;

        pibs->m_dwBitsLeft += (8 - iFirstBit);
        iFirstBit = 0;
    }
    else 
    {
        assert (pibs->m_cBitDotT + 8 - iFirstBit <= 32);
        temp = uByte;
        temp = temp<<iFirstBit;
        temp = temp>>iFirstBit;
        pibs->m_dwDotT = (pibs->m_dwDotT<<(8 - iFirstBit))|temp;
        pibs->m_cBitDotT += (8 - iFirstBit);
    }

}
#endif //WMA_OPT_STRMDEC_ARM


#ifdef _WMA_DRM_DESCRAMBLE_
#define pibstrm pibs
#endif


#define LOAD_BITS_FROM_DotT \
if (pibstrm->m_cBitDotT > 0) \
{ \
    I32 cBitMoved = min (32 - pibstrm->m_dwBitsLeft, pibstrm->m_cBitDotT); \
    pibstrm->m_dwDot <<= cBitMoved; \
    pibstrm->m_cBitDotT -= cBitMoved; \
    pibstrm->m_dwDot |= (pibstrm->m_dwDotT >> pibstrm->m_cBitDotT); \
    pibstrm->m_dwDotT &= ((I32) (1 << pibstrm->m_cBitDotT)) - 1; \
    pibstrm->m_dwBitsLeft += cBitMoved; \
}

#define LOAD_BITS_FROM_STREAM \
while (pibstrm->m_dwBitsLeft <= 24 && pibstrm->m_cbBuflen > 0) { \
    pibstrm->m_dwDot <<= 8; \
    pibstrm->m_dwDot |= DESCRAMBLE(*(pibstrm->m_pBuffer)++); \
    --(pibstrm->m_cbBuflen); \
    pibstrm->m_dwBitsLeft += 8; \
}

#define LOAD_BITS_INTO_DotT \
assert(pibstrm->m_dwBitsLeft > 24 || 0 == pibstrm->m_cbBuflen); \
pibstrm->m_dwDotT = 0; \
while (pibstrm->m_cbBuflen > 0) \
{ \
    pibstrm->m_dwDotT <<= 8; \
    pibstrm->m_dwDotT |= DESCRAMBLE(*(pibstrm->m_pBuffer)++); \
    --(pibstrm->m_cbBuflen); \
    pibstrm->m_cBitDotT += 8; \
} \
assert (pibstrm->m_cBitDotT <= 24); // we only take this branch if we have <56 bits left total

#if !WMA_OPT_STRMDEC_ARM 
#if !defined(PLATFORM_SPECIFIC_IBSTRM)
#if !defined(WMA_OPT_STRMDEC_XENON)
WMARESULT ibstrmPeekBits (CWMAInputBitStream *pibstrm, register UInt dwNumBits,
                          U32 *piRetBits)
{
    I16 cBitExtra;
    WMARESULT   wmaResult = WMA_OK;
    assert (dwNumBits <= 24); //only works for sure under this
    if (pibstrm->m_dwBitsLeft < dwNumBits)
    {
        //make sure there is enougth data in dwDot for peek
        LOAD_BITS_FROM_DotT;
        LOAD_BITS_FROM_STREAM;

        //if enough take the data and go home; else take what ever is left
        if (pibstrm->m_dwBitsLeft < dwNumBits)
        {
            TRACEWMA_EXIT(wmaResult, ibstrmGetMoreData(pibstrm, ModePeek, dwNumBits));
            if (pibstrm->m_dwBitsLeft < dwNumBits)
            {
                assert(pibstrm->m_fNoMoreInput);
                dwNumBits = pibstrm->m_dwBitsLeft;
            }
        }
    }

    cBitExtra = (I16) pibstrm->m_dwBitsLeft - (I16) dwNumBits;
    assert(NULL != piRetBits); // Avoid conditionals
    *piRetBits = (pibstrm->m_dwDot >> cBitExtra) << (32 - dwNumBits);
    //printf("%d: Peek(%d)=%08X\n", pibstrm->m_cFrmBitCnt, dwNumBits, *piRetBits);

exit:
    return wmaResult;
}

WMARESULT ibstrmLookForBits (CWMAInputBitStream *pibstrm, UInt dwNumBits)
{
    WMARESULT   wmaResult = WMA_OK;
    assert(dwNumBits <= 56); // we need to make sure that there is enough space to put the first byte of data from the new packet. by Hong
    if (dwNumBits > pibstrm->m_dwBitsLeft + pibstrm->m_cBitDotT + pibstrm->m_cbBuflen * 8) 
    {
        //load up everything so that we can return and ext. buf may be overwritten
        LOAD_BITS_FROM_STREAM;
        LOAD_BITS_INTO_DotT;
        TRACEWMA_EXIT(wmaResult, ibstrmGetMoreData(pibstrm, ModeLookFor, dwNumBits));
    }

exit:
    return wmaResult;
}
#endif //WMA_OPT_STRMDEC_XENON

WMARESULT ibstrmFlushBits (CWMAInputBitStream *pibstrm, register UInt dwNumBits) 
{

    WMARESULT wmaResult = WMA_OK;
     assert(dwNumBits <= 24); // this is to make sure there is enough buffer space when a new packet comes in. Hong

#if defined(_DEBUG) || defined(BITRATE_REPORT) || defined(DEBUG_BIT_DISTRIBUTION)
    g_cBitGet += dwNumBits;
#endif  // _DEBUG || BITRATE_REPORT || DEBUG_BIT_DISTRIBUTION

    assert (dwNumBits <= 24); //only works for sure under this
    //make sure there is enougth data in dwDot for peek
    if (pibstrm->m_dwBitsLeft < dwNumBits)
    {
        LOAD_BITS_FROM_DotT;
        LOAD_BITS_FROM_STREAM;

        if (pibstrm->m_dwBitsLeft < dwNumBits)
        {
            TRACEWMA_EXIT(wmaResult, ibstrmGetMoreData(pibstrm, ModeGetFlush, dwNumBits));
        }
    }

    //take the data and go home; or we have to pause
    pibstrm->m_dwBitsLeft -= dwNumBits; 

#ifdef WMA_COMPRESSION_TOOL
    pibstrm->m_cFrmBitCnt += dwNumBits;
#else
    pibstrm->m_cFrmBitCnt += dwNumBits;
#endif //WMA_COMPRESSION_TOOL

exit:
#ifdef WMA_ENTROPY_TEST
    if (!WMA_FAILED(wmaResult) && g_decCountBits)
        g_bitCnt += dwNumBits;
#endif
    return wmaResult;
}
#endif //PLATFORM_SPECIFIC_IBSTRM
#endif //WMA_OPT_STRMDEC_ARM


void ibstrmProcessGap(CWMAInputBitStream *pibs)
{
    CAudioObjectDecoder* paudec = pibs->m_dwOwner;
    U32 cHdrBitsMod8 = WMA_get_nHdrBits(paudec) % 8;
    U32 cbNextGap = paudec->pau->m_cBytePacketLength - WMA_get_nHdrBits(paudec) / 8;
    
    //WMAPrintf("gap %d bits of %02X %d+%d bits into frame %d\n", cHdrBitsMod8, *pibs->m_pBuffer, pibs->m_cFrmBitCnt, ibstrmBitsInDots(pibs), pibs->m_dwOwner->pau->m_iFrameNumber);

    assert(0 != cHdrBitsMod8); // ibstrmSetGap() checks this before scheduling a gap
    assert(!pibs->m_fDeferredGap); // We never set up the next gap before the current gap has been processed
    
    // extend pibs->m_cbBuflen to the next gap or the end of the input buffer, whichever is sooner
    assert(pibs->m_pBuffer >= pibs->m_pBufferBegin);
    pibs->m_cbBuflen = pibs->m_cbBuflenBegin - (U32)(pibs->m_pBuffer - pibs->m_pBufferBegin);
    assert(pibs->m_cbBuflen > 0);
    pibs->m_cbLastProcessedGapLocationBackFromEndOfLastBuffer = pibs->m_cbBuflen;
    if (pibs->m_cbBuflen > cbNextGap) // is the next gap in sight ?
    { // yes - schedule the gap for the current buffer
        pibs->m_cbBuflen = cbNextGap;
    }
    else
    { // no - schedule the gap for a future buffer
        pibs->m_fDeferredGap = WMAB_TRUE; // audecInput() pays attention to this
        pibs->m_cbToDeferredGap = cbNextGap - pibs->m_cbBuflen; // 0 is a valid case
    }

    ibstrmLoadBits(pibs, cHdrBitsMod8, *(pibs->m_pBuffer));
    pibs->m_pBuffer++;
    pibs->m_cbBuflen--;
}

#define NEED_MORE_DATA (cBitsNeeded > pibs->m_dwBitsLeft + ((mode == ModeLookFor) ? (pibs->m_cBitDotT + pibs->m_cbBuflen * 8) : 0))

WMARESULT ibstrmGetMoreData(CWMAInputBitStream *pibs, GetMoreDataMode mode, U32 cBitsNeeded)
{
    WMARESULT   wmaResult = WMA_OK;
    WMA_Bool fCalledDueToGap = WMAB_FALSE;
    
    assert(0 == pibs->m_cbBuflen);
    assert(NEED_MORE_DATA); // otherwise why was ibstrmGetMoreData() called ?

    if (pibs->m_dwOwner->m_fSPDIF)
    {
        assert(ModePktHdr != mode);
        assert(pibs->m_cbBuflenBegin <= 1048576 && pibs->m_cbBuflenBegin <= 1048576); // not a real restriction - assert just to catch suspicious values
        assert(pibs->m_pBuffer >= pibs->m_pBufferBegin);
        assert(pibs->m_pBuffer + pibs->m_cbBuflen <= pibs->m_pBufferBegin + pibs->m_cbBuflenBegin);
        
        if (ibstrmMoreInputAfterGap(pibs)) // more left
        { // not really done with the buffer - cbBuflen was set short because of a gap
            fCalledDueToGap = WMAB_TRUE;
            ibstrmProcessGap(pibs);
        
            if (NEED_MORE_DATA)
            {   // Make sure we have reached the end of the input buffer.  We could not have hit
                // yet another gap as long as gaps are >= 8 bytes apart, which they
                // should be because gaps occur only at packed boundaries and packets are >>8 bytes.
                assert(pibs->m_pBuffer == pibs->m_pBufferBegin + pibs->m_cbBuflenBegin);
            }
            else
            {
                goto exit;
            }
        }
    }
         
    assert(NEED_MORE_DATA);
    if (!pibs->m_fNoMoreInput)
    {
        audecInputBufferInfo buf;
        if (!pibs->m_pfnGetMoreData)
        {
            TRACEWMA_EXIT (wmaResult, WMA_E_ONHOLD);
        }

        memset(&buf, 0, sizeof(buf));
        TRACEWMA_EXIT(wmaResult, pibs->m_pfnGetMoreData(pibs->m_pUser, &buf));
        if (!buf.fNoMoreInput) {
            assert(buf.cbIn >= 8); // to guarantee 56 bits when we return (+ up to 7 bits for SPDIF gap)
        }

        TRACEWMA_EXIT(wmaResult, prvNewInputBuffer(pibs->m_dwOwner, &buf)); // calls ibstrmAttach()
        if (pibs->m_dwBitsLeft < 24) 
        {
            if (ibstrmMoreInputAfterGap(pibs)) {
                // must have hit a gap within the first few bytes of the new buffer
                assert(!fCalledDueToGap); // unexpected to hit another gap having just processed one above
                ibstrmProcessGap(pibs);
            }
        }
        
    }

    if (NEED_MORE_DATA)
    {
        if (pibs->m_fNoMoreInput)
        {
            if (mode == ModeLookFor)
            { // Sometimes LookForBits() is asked for more bits than the frame contains.
              // m_fAllBarksOn = TRUE in prvDecodeTransformOnOffInfo() is one such case.
                goto exit;
            }
            else if (mode == ModePeek)
            {
                assert(pibs->m_dwBitsLeft < 24);
                assert(0 == pibs->m_cBitDotT);
                assert(0 == pibs->m_cbBuflen);
                goto exit;
            }
            else
            {   // Trying to read past the end in GetBits or FlushBits
                // indicates a corrupt or truncated bitstream.
                // Known cases are truncated SPDIF frames & WMA files truncated to packet boundary.
                if (!((mode == ModePktHdr) || pibs->m_dwOwner->m_fSPDIF))
                {
                    REPORT_BITSTREAM_CORRUPTION();
                }
                TRACEWMA_EXIT (wmaResult, WMA_E_ONHOLD);
            }
        }
        else
        {
            assert(!pibs->m_pfnGetMoreData);
            TRACEWMA_EXIT (wmaResult, WMA_E_ONHOLD);
        }
    }

    assert(!NEED_MORE_DATA);

exit:
    return wmaResult;
}

void ibstrmFlushOldBits(CWMAInputBitStream *pibs)
{
    int cOldBits = (signed)pibs->m_dwBitsLeft - 8 * (signed)( pibs->m_cbBuflenBegin - pibs->m_cbBuflen );
    assert(cOldBits >= 0);
    if (cOldBits > 0)
    {
        ibstrmFlushBits(pibs, cOldBits);
    }
}

Void ibstrmResetPacket(CWMAInputBitStream *pibs)
{
    U8 nHdrBits = WMA_get_nHdrBits(pibs->m_dwOwner); // this only updates per file for V2
    I32 iFirstBit;
    U8 temp;

    assert (pibs->m_pBuffer != 0);

    pibs->m_dwDotT = 0;
    pibs->m_cBitDotT = 0;

    //skip the packet header
    iFirstBit = nHdrBits % 8;
    pibs->m_pBuffer = pibs->m_pBufferBegin;
    pibs->m_pBuffer += nHdrBits / 8;
    pibs->m_cbBuflen = pibs->m_cbBuflenBegin - nHdrBits / 8;

    if (iFirstBit)
    {   // Now that we must use m_uLastHeaderByte instead of reading from tne input
        // buffer directly (reading directly would mean duplicate descramble calls
        // and cause the encryption/decryption to go out of synch), this generic
        // code can no longer do the right thing automatically for the iFirstBit==0
        // case because, e.g., if the header is exactly 3 bytes, this code wants to
        // (probably needlessly) load the 4th byte, but m_uLastHeaderByte is set by
        // ibstrmAttach to be the 3rd byte.
        // (setting m_uLastHeaderByte to the 4th byte in ibstrmAttach in that case
        // would be a terrible option because it would require things like
        // ibstrmGetBits to have a special case to avoid descrambling the 4th
        // byte twice).
        // Hence we have to handle iFirstBit==0 as a special case.
        temp = pibs->m_uLastHeaderByte;
        pibs->m_pBuffer++;
        pibs->m_cbBuflen--;
    
        //zeros out the top (not valid) bits
        temp = temp<<iFirstBit;
        temp = temp>>iFirstBit;
        pibs->m_dwDot = temp;
        pibs->m_dwBitsLeft = (8 - iFirstBit);
    }
    else
    {
        pibs->m_dwDot = 0;
        pibs->m_dwBitsLeft = 0;
    }
}

Bool ibstrmMoreInputAfterGap(const CWMAInputBitStream* pibstrm)
{
    if (pibstrm->m_dwOwner->m_fSPDIF)
    {
        if (pibstrm->m_pBuffer + pibstrm->m_cbBuflen < pibstrm->m_pBufferBegin + pibstrm->m_cbBuflenBegin)
        {
            return WMAB_TRUE;
        }
        else
        {
            return WMAB_FALSE;
        }
    }
    else
    {
        return WMAB_FALSE;
    }
}

Bool ibstrmNoMoreInput(const CWMAInputBitStream* pibstrm)
{
    if (pibstrm->m_fNoMoreInput)
    {
        if (ibstrmMoreInputAfterGap(pibstrm))
        {
            return WMAB_FALSE;
        }
        else
        {
            return WMAB_TRUE;
        }
    }
    else
    {
        return WMAB_FALSE;
    }
}

Int ibstrmBitsInDots(const CWMAInputBitStream* pibstrm)
{
    Int cBitsInDots = pibstrm->m_dwBitsLeft + pibstrm->m_cBitDotT;
    U32 cHdrBitsMod8 = WMA_get_nHdrBits(pibstrm->m_dwOwner) % 8;
    if (0 != cHdrBitsMod8) // no gaps if pkt hdr is a multiple of 8 bits
    { 
        U32 cbThatThing = pibstrm->m_cbLastProcessedGapLocationBackFromEndOfLastBuffer;
        if (pibstrm->m_pBuffer > pibstrm->m_pBufferBegin + pibstrm->m_cbBuflenBegin - cbThatThing)
        {
            WMA_U32 cbBytesEatenSinceGap = (WMA_U32) (pibstrm->m_pBuffer - (pibstrm->m_pBufferBegin + pibstrm->m_cbBuflenBegin - cbThatThing));
            if (cBitsInDots + cHdrBitsMod8 >= 8 * cbBytesEatenSinceGap)
            {   // We have not read any of the bits from after the gap yet, so add the gap
                // size to cBitsInDots because m_pBuffer was incremented when the gap was
                // eaten, but the gap bits never went into cBitsInDots.
                //
                // This happens when a frame ends on a byte boundary and the frame size in
                // the frame header is actual.  We don't know that the frame size is actual
                // when we process the frame header, so we set up a gap just in case the 
                // frame size points to a gap.  Without the special logic here, audecDecode()
                // would then get cbBytesInLastBuffer wrong by 1 byte because bits past the
                // gap have already been loaded into m_dwDot/m_dwDotT, and m_pBuffer was
                // incremented when we processed the gap on the assumption that we would
                // need to read some bits after the gap.
                assert(cBitsInDots + cHdrBitsMod8 == 8 * cbBytesEatenSinceGap);
                return cBitsInDots + cHdrBitsMod8;
            }
      
        }
        else
        {
            assert(0);
        }
    }
    return cBitsInDots;
}


void ibstrmSetGap(CWMAInputBitStream *pibs, U32 cBitsToGap)
{
    U32 cBitsLeft = ibstrmBitsLeft(pibs) + 8 * ibstrmBufLen(pibs);
    assert(pibs->m_dwOwner->m_fSPDIF);
    assert(!pibs->m_fDeferredGap); // this is called during FHDR_SIZE, we should not have a gap yet

    if (0 == WMA_get_nHdrBits(pibs->m_dwOwner) % 8) // no gap - pkt hdr is a multiple of 8 bits
    {
        return;
    }
    
    // Set this so that ibstrmBitsInDots() realizes that we have not yet processed a gap.
    pibs->m_cbLastProcessedGapLocationBackFromEndOfLastBuffer = pibs->m_cbBuflenBegin;

    // pibstrm->m_cBitDotT is only set on ONHOLD, and we shouldn't be
    // on hold this early because we are just starting to process a frame
    assert(0 == pibs->m_cBitDotT);
    // still, in case somebody decides to torture ibstrmGetBits()...
    cBitsLeft += pibs->m_cBitDotT;

    // Gaps only occur on byte boundaries because they come from packet headers.
    // If a gap appears to not be, it means the frame size is real - there is no gap.
    if (cBitsLeft % 8 != cBitsToGap % 8)
    { 
        return;
    }

    if (cBitsLeft > cBitsToGap)
    { // set up for the gap to be taken care of during the current input buffer 
        U32 cbBytes = (cBitsLeft - cBitsToGap) / 8;
        if (cbBytes <= (U32)pibs->m_cbBuflen)
        {
            pibs->m_cbBuflen -= cbBytes;
        }
        else
        { // we've already sucked a few bytes at/beyond the gap into m_dwDot.  Discard them
            cbBytes -= pibs->m_cbBuflen;
            assert(cbBytes <= 2); // not necessarily a problem but unexpected
            assert(pibs->m_dwBitsLeft >= 8 * cbBytes); // this would be a problem
            assert(0 == pibs->m_cBitDotT); // we have only decoded the length from the frm hdr 
            pibs->m_pBuffer -= cbBytes;
            pibs->m_cbBuflen = 0;
            pibs->m_dwBitsLeft -= 8 * cbBytes;
            pibs->m_dwDot >>= 8 * cbBytes;
            assert(pibs->m_pBuffer >= pibs->m_pBufferBegin);
    
        }
    }
    else
    { // set up for the gap to be taken care of during a later input buffer
        pibs->m_fDeferredGap = WMAB_TRUE; // audecInput() pays attention to this
        pibs->m_cbToDeferredGap = (cBitsToGap - cBitsLeft) / 8;
    }
}

#if !WMA_OPT_STRMDEC_ARM
#if !defined(PLATFORM_SPECIFIC_IBSTRM)
WMARESULT ibstrmGetBits (CWMAInputBitStream* pibstrm, register UInt dwNumBits,
                         U32 *piResult)
{
    WMARESULT   wmaResult = WMA_OK;

    if (dwNumBits > 24)
    {
        return WMA_E_INVALIDARG;
    }

#if defined(_DEBUG) || defined(BITRATE_REPORT) || defined(DEBUG_BIT_DISTRIBUTION)
    g_cBitGet += dwNumBits;
#endif  // _DEBUG || BITRATE_REPORT || DEBUG_BIT_DISTRIBUTION

    if (pibstrm->m_dwBitsLeft < dwNumBits)
    {
        LOAD_BITS_FROM_DotT;
        LOAD_BITS_FROM_STREAM;

        if(pibstrm->m_dwBitsLeft < dwNumBits){
            TRACEWMA_EXIT(wmaResult, ibstrmGetMoreData(pibstrm, ModeGetFlush, dwNumBits));   
        }
    }
        //
        // Do the most common case first.  If this doesn't play, we have one branch
        // to get to the next most common case (usually 1/32 of the time in the case
        // of the codec doing a huffman decode).  Note that we use a mask array to
        // avoid a special case branch when the bitcount is 32 (even though this is
        // relatively unlikely) since a left shift operation where the shift count
        // is equal to or greater than the number of bits in the destination is
        // undefined.
        //
        pibstrm->m_dwBitsLeft -= dwNumBits;
        *piResult = (pibstrm->m_dwDot >> pibstrm->m_dwBitsLeft) & getMask[dwNumBits];
        //printf("%d: Get(%d)=%08X\n", pibstrm->m_cFrmBitCnt, dwNumBits, *piResult);        
#ifdef WMA_COMPRESSION_TOOL
        pibstrm->m_cFrmBitCnt += dwNumBits;
#else
        pibstrm->m_cFrmBitCnt += dwNumBits;
#endif //WMA_COMPRESSION_TOOL
exit:
#if 0
    {
        static int count = 0;
        static int totalGet = 0;
        if (wmaResult == WMA_OK && dwNumBits != 0)
        {
            totalGet += dwNumBits;
            //WMAPrintf("%d Get bits totalbits=%d bits=%d data=%d\n", count, totalGet, dwNumBits, *piResult);
            count++;
        }
    }
#endif
#ifdef TEST_CORRUPT_BITSTREAM
    {
        CAudioObjectDecoder* paudec = (CAudioObjectDecoder*) pibstrm->m_dwOwner;
//        if (paudec->m_hdrdecsts != HDR_DONE) //only mutate hdr bits
        {
            I32 iRV = rand();
            if ((iRV * CORRUPT_PROBABILITY) < RAND_MAX) {
                // *piResult = ((rand() << 16) + rand()) & (0xFFFFFFFF >> (32 - dwNumBits));
                if (dwNumBits > 0) {
                    if (rand() > rand()) { // singluar error
                        *piResult = (*piResult) ^ (1 << (rand() % dwNumBits));
                    }
                    else { // burst error
                        *piResult = ((rand() << 16) + rand()) & (0xFFFFFFFF >> (32 - dwNumBits));
                    }
                }
            }
        }   
    }
#endif //TEST_CORRUPT_BITSTREAM

#ifdef WMA_ENTROPY_TEST
    if (!WMA_FAILED(wmaResult) && g_decCountBits)
        g_bitCnt += dwNumBits;
#endif
    return wmaResult;
}

//WMA Lossless related
#if defined (BUILD_WMALSL)
WMARESULT ibstrmCountSerial1Bits (CWMAInputBitStream* pibstrm, U32 *pCount)
{
    WMARESULT   wmaResult = WMA_OK;
    U32 dwCurrent;
    U32 dwCount;

    if (pibstrm->m_dwBitsLeft <= 0)
    {
reload:
        pibstrm->m_dwBitsLeft = 0;

        LOAD_BITS_FROM_DotT;
        LOAD_BITS_FROM_STREAM;
        
        if(pibstrm->m_dwBitsLeft < 1){
            TRACEWMA_EXIT(wmaResult, ibstrmGetMoreData(pibstrm, ModeGetFlush, 1));   
        }
    }

    dwCurrent = pibstrm->m_dwDot << (32-pibstrm->m_dwBitsLeft);
    dwCount = 0;

    while (dwCurrent & 0x80000000)
    {
        dwCount ++;
        dwCurrent <<= 1;
    }

    *pCount += dwCount;
    pibstrm->m_dwBitsLeft -= (dwCount+1);

    if ((I32)pibstrm->m_dwBitsLeft < 0)
        goto reload;

exit:
    return wmaResult;
}
#endif //(BUILD_WMALSL)
#endif	//PLATFORM_SPECIFIC_IBSTRM
#endif //WMA_OPT_STRMDEC_ARM
// end of strmdec_wma.c
