//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifdef FEX_OVERLAYBAND

#define IS_VALID()        IS_VALID_FEXPT()
#define IS_VALID_MASK()   IS_VALID_FEXPT_MASK()
#define freqexKeepPeaksT freqexKeepPeaksOverlay
#define freqexScaleBandT freqexScaleBandOverlay
#define freqexGetMvBandScaleT freqexGetMvBandScaleOverlay
#define freqexGetMvBandScaleWithMaskT freqexGetMvBandScaleWithMaskOverlay

#if 0 // (defined (FEX_GET_MV_SCALE_C_OPT) && WMA_OPT_FEX_GET_MV_SCALE_ARM)
#    define freqexGetMvBandScaleLoopT freqexGetMvBandScaleLoopOverlay
#endif

#else // FEX_OVERLAYBAND

#define IS_VALID()        (1)
#define IS_VALID_MASK()   (NULL==pucMask || pucMask[i]==1)
#define freqexKeepPeaksT freqexKeepPeaksNoOverlay
#define freqexScaleBandT freqexScaleBandNoOverlay
#define freqexGetMvBandScaleT freqexGetMvBandScaleNoOverlay
#define freqexGetMvBandScaleWithMaskT freqexGetMvBandScaleWithMaskNoOverlay

#if 0 // (defined (FEX_GET_MV_SCALE_C_OPT) && WMA_OPT_FEX_GET_MV_SCALE_ARM)
#   define freqexGetMvBandScaleLoopT freqexGetMvBandScaleLoopNoOverlay
#endif

#endif

// returns # of valid mask
Int freqexKeepPeaksT(       Fex *pfx, 
                       const CoefType *pVec, 
                       const CoefType *pfRecon,
                             U8 *pMask, 
                       const Int iLen,
                       const Bool bRev,
                       const Int iRecLen,
                             Int *piCbStart,
                       const I32 cLeftShiftBits,
                             Int *piActLen
                      )
{
    Int i, iMaskLen, iActLen=0;
    Int k, step;
    CoefType maxVal;
    FexType fThresh;
    PerChannelInfoShr *pcis = pfx->m_pau->m_rgpcinfoShr + pfx->m_iChSrc;

    step = 1;
    if( bRev )
        step = -1;
    if( piCbStart == NULL )
        k = 0;
    else
        k = *piCbStart;

    maxVal = 0;
    for (i=0; i < iLen; i++,k+=step)
    {
        if (IS_VALID())
        {
            maxVal = max(ABS(pVec[k]), maxVal); // global max value
            iActLen++;
        }
        if( !bRev && k == (iRecLen - 1) )
            k = -1; // increment to 0 at the top of loop
        else if( bRev && k == -(iRecLen - 1) )
            k = 1;  // decrement to 0 at the top of loop
    }

    *piActLen = iActLen;

    step = 1;
    if( bRev )
        step = -1;
    if( piCbStart == NULL )
        k = 0;
    else
        k = *piCbStart;

    fThresh = freqexInvQuantNoiseFloorThresh(pcis->m_iFxNoiseFloorThresh);
    iMaskLen = 0;
    iActLen = 0;
    for (i=0; i < iLen; i++,k+=step)
    {
        if (IS_VALID())
        {
#if !defined(BUILD_INTEGER)
            if ( 0 == maxVal || COEF_ABS(pVec[k]) > maxVal * fThresh )
#else // !BUILD_INTEGER

            //assert( FEXT_BITS >= cLeftShiftBits );
            assert( U32_MAX > COEF_ABS( pVec[k] ) );
            assert( U32_MAX > maxVal );

            if ( 0 == maxVal || (((U64)COEF_ABS(pVec[k]))<<FEXT_BITS) > (U64)maxVal*fThresh )
#endif // BUILD_INTEGER
            {
                pMask[i] = 1;
                iMaskLen++;
            }
            else
            {
                pMask[i] = 0;
            }
            iActLen++;
        }
        else
        {
            pMask[i] = 0;
        }
        if( !bRev && k == (iRecLen - 1) )
            k = -1; // increment to 0 at the top of loop
        else if( bRev && k == -(iRecLen - 1) )
            k = 1;  // decrement to 0 at the top of loop
    }
    if( piCbStart )
        *piCbStart = k;

    assert(iActLen == *piActLen);

    assert( 0 < iMaskLen );

    return iMaskLen;
}

WMARESULT freqexScaleBandT( PerChannelInfo *ppcinfo, Fex *pfx, 
                           const FastFloat *pfScaleFac,
                           const FastFloat fMvScale, CoefType *pfRecon,
                           const CoefType *pVec, const U8 *pucMask,
                           CoefType *pfReconDST, const CoefType *pVecDST,
                           const Int iLen, const QuantStepType fGlobalQ,
                           const FexType fExp, const Int iCwSign,
                           const Bool bRev, const Int iRecLen,
                           Int *piCbStart,
                           Int *plshift, const Bool bNoise,
                           FastFloat *pfBandScale )
{
    WMARESULT wmaResult = WMA_OK;
    FastFloat fBandScale;
    Int i, k, step;
#if 0 //def FEX_SCALE_BAND_C_OPT 
    Int	iPrev = 0;
    Bool    *bFlags = malloc(iLen * sizeof(Bool));
#endif
    PerChannelInfoShr *pcis = pfx->m_pau->m_rgpcinfoShr + pfx->m_iChSrc;

    if ( FEXT_FROM_FLOAT(1.0f) != fExp && 
         FEXT_FROM_FLOAT(2.0f) != fExp && 
         FEXT_FROM_FLOAT(0.5f) != fExp )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    pfx->m_iCoeffScaleFacBand = 0;

    // get new scale factor
    if (pfx->m_iScaleBand >= pfx->m_cScaleBands)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    if (WMAB_FALSE==pfx->m_bUseObtainedBandScale)
    {
        //assert( 0 <= FLOAT_FROM_FASTFLOAT( pfScaleFac[pfx->m_iScaleBand] ) );
        fBandScale = freqexGetBandScale(pfScaleFac[pfx->m_iScaleBand],
                                             fMvScale, fGlobalQ);
    }
    else
    {
        fBandScale = pfx->m_fObtainedBandScale;
    }

#if 0//def FEX_SCALE_BAND_C_OPT  
	if (WMAB_TRUE == pfx->m_rgbUseImplicitStartPos[pfx->m_iChCode] &&
        WMAB_FALSE == pfx->m_bMvRangeFull && WMAB_FALSE == pfx->m_bOverlay) 
	{
        for (i=0; i < iLen; i++)
        {
            if ((pucMask==NULL || pucMask[i]) && pfRecon[i] != 0 )
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
        }
    }

#ifdef FEX_OVERLAYBAND
    for (i=0; i < iLen; i++)
    {
        bFlags[i] = IS_VALID_MASK();
    }
#else
#if !WMA_OPT_FEX_SCL_BAND_OPT_ARM
    if (NULL==pucMask)
        for (i=0; i < iLen; i++)
            bFlags[i] = TRUE;
    else    
        for (i=0; i < iLen; i++)
            bFlags[i] = pucMask[i];
#else
    freqexScaleBandUpdateFlags(pucMask, bFlags, iLen);
#endif
#endif

#endif	// FEX_SCALE_BAND_C_OPT

    step = 1;
    if( bRev )
        step = -1;
    if( piCbStart == NULL )
        k = 0;
    else
        k = *piCbStart;

//    DBG_FREQEX_SCALE_BAND();

    for (i=0; i < iLen; i++,k+=step)
    {
        ++pfx->m_iCoeffScaleFacBand;

#ifndef ALLOW_EXTERNAL_FILE_FOR_RECON
        if ((pucMask==NULL || pucMask[i]) &&
            pfRecon[i] != 0 &&
            WMAB_TRUE == pcis->m_bFxUseImplicitStartPos &&
            WMAB_FALSE == pfx->m_bMvRangeFull &&
            WMAB_FALSE == pfx->m_bOverlay &&
            WMAB_FALSE == pfx->m_pau->m_bCx)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
#endif
        if (IS_VALID_MASK())
        {
            assert( 1 == abs( iCwSign ) );

#ifndef ALLOW_EXTERNAL_FILE_FOR_RECON
            if( pfRecon[i] != 0 && 
                WMAB_FALSE == pfx->m_bMvRangeFull && 
                WMAB_FALSE == pfx->m_pau->m_bCx )
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
#endif

#if !defined( BUILD_INTEGER )

            {
                CoefType val = pVec[k] * iCwSign;

                // apply exponentiation here.

                if( 1.0f != fExp )
                {
                    const I32 iSign = ( 0 <= val ) ? 1 : -1;
                    val = COEF_ABS( val );

                    if( 0.5f == fExp )
                    {
                        val = (Float)sqrt( val );
                    }
                    else if( 2.0f == fExp )
                    {
                        val = val * val;
                    }
                    val = ( 0 <= iSign ) ? val : -val;
                }

                pfRecon[i] = val * fBandScale;
            }

#else  // BUILD_INTEGER

            if( 0 == pVec[k] )
            {
                pfRecon[i] = 0;
            }
            else
            {
                FastFloat fval;
                fval.iFraction = (I32)pVec[k] * iCwSign;
                fval.iFracBits = ( bNoise ) ? FEXT_BITS : *plshift;
                Norm4FastFloat( &fval );

                assert( I32_MAX > COEF_ABS( pVec[k] ) );

                // apply exponentiation here.

                if( FEXT_FROM_FLOAT( 1.0f ) != fExp )
                {
                    I32 iSign = 1;
                    
                    if( 0 > fval.iFraction )
                    {
                        iSign = -1;
                        fval.iFraction = -fval.iFraction;
                    }

                    if( FEXT_FROM_FLOAT( 0.5f ) == fExp )
                    {
                        fval = FASTFLOAT_SQRT( fval );
                    }
                    else if( FEXT_FROM_FLOAT( 2.0f ) == fExp )
                    {
                        fval = FASTFLOAT_MULT( fval, fval );
                    }

                    if( 0 > iSign )
                        fval.iFraction = -fval.iFraction;
                }

                fval.iFracBits -= *plshift;
                fval = FASTFLOAT_MULT( fval, fBandScale );

                if( fval.iFracBits > 31 )
                {
                    pfRecon[i] = 0;
                }
                else if( 0 <= fval.iFracBits )
                {
                    pfRecon[i] = (CoefType)( fval.iFraction >> fval.iFracBits );
                }
                else
                {
                    // if 0 > fval.iFracBits, there is risk 
                    // of overflow. this should never happen
                    // in recon-domain FEX, but may occur in
                    // coding-domain FEX if dynamic scaling
                    // is used. To avoid the overflow, coefs
                    // must be scaled down.

                    Int j;
                    const Int rshift = -fval.iFracBits;

                    assert( !pfx->m_bReconDomain );

                    // adjust the stored 'shift-bits' values
                    // that describe the coefficient arrays.

                    ppcinfo->m_cLeftShiftBitsTotal -= rshift;
                    *plshift -= rshift;

                    TraceInfo1( " *** TRACE *** prvFreqexScaleBand() rescaled coefs. ( >>= %i )\n", rshift );

                    // right-shift the coefficient buffers.
                    for( j = 0; j < pfx->m_cSubFrameSampleHalf; ++j )
                        ppcinfo->m_rgCoefRecon[j] >>= rshift;

                    // save the current coefficient.
                    pfRecon[i] = fval.iFraction;
                }

            }
#endif	// BUILD_INTEGER

        }
        if( !bRev && k == (iRecLen - 1) )
            k = -1; // increment to 0 at the top of loop
        else if( bRev && k == -(iRecLen - 1) )
            k = 1;  // decrement to 0 at the top of loop
    }
    if( piCbStart )
        *piCbStart = k;

exit:

    if (pfBandScale && WMAB_FALSE==pfx->m_bUseObtainedBandScale)
    {
        if( pfx->m_bAdjustScaleForDelayedExp && FEXT_FROM_FLOAT(1.0f) != fExp )
        {
            if( FEXT_FROM_FLOAT(0.5f) == fExp )
            {
                fBandScale = FASTFLOAT_MULT( fBandScale, fBandScale );
            }
            else if( FEXT_FROM_FLOAT(2.0f) == fExp )
            {
                fBandScale = FASTFLOAT_SQRT( fBandScale );
            }
            else 
                assert(!"Not a valid exponent");
        }
        
        //DBG_SCALE( fBandScale );

        *pfBandScale = fBandScale;
    }

    if ( pfx->m_iCoeffScaleFacBand !=
            pfx->m_piScaleBandSizes[pfx->m_iScaleBand] )
    {
        // Not using REPORT_BITSTREAM_CORRUPTION_AND_EXIT here 
        // since we are already in the 'exit' block
        REPORT_BITSTREAM_CORRUPTION();
        wmaResult = TraceResult(WMA_E_BROKEN_FRAME);
    }

    ++pfx->m_iScaleBand;

#if 0//def FEX_SCALE_BAND_C_OPT 
    free(bFlags);
#endif
    return wmaResult;
}

FastFloat freqexGetMvBandScaleT( Fex      *pfx,
                          const CoefType *pVec, 
                          const CoefType *pfRecon,
                          const Int     iLen,
                          const FexType   fExp,
                          const Bool      bRev,
                          const Int     iRecLen,
                                Int    *piCbStart,
                                Int       lshift )
{
#ifndef BUILD_INTEGER

    Float fScale  = 0;
    Int iLenAct = 0;
    Int i, j, step;

    step = 1;
    if( bRev )
        step = -1;
    if( piCbStart == NULL )
        j = 0;
    else
        j = *piCbStart;

    for( i=0; i < iLen; j+=step,++i )
    {
        if (IS_VALID())
        {
                 if( 0.5f == fExp )
            {
                fScale += (Float)COEF_ABS( pVec[j] );
            }
            else if( 1.0f == fExp )
            {
                fScale += pVec[j] * pVec[j];
            }
            else if( 2.0f == fExp )
            {
                const Float fTemp = pVec[j] * pVec[j];
                fScale += fTemp * fTemp;
            }
            else
            {
                fScale += (Float)pow( COEF_ABS( pVec[j] ), 2 * fExp );
            }
            iLenAct++;
        }
        if( !bRev && j == (iRecLen - 1) )
            j = -1; // increment to 0 at the top of loop
        else if( bRev && j == -(iRecLen - 1) )
            j = 1;  // decrement to 0 at the top of loop
    }
    if( piCbStart )
        *piCbStart = j;

    if (iLenAct != 0)
        return (Float)sqrt( fScale / iLenAct );    
    else 
        return 0;

#else // !BUILD_INTEGER

    FastFloat ffltScale = {0};
    I64   fScale  = 0;
    CoefType maxCoef = 0;
    I32 rshift = 0;
    Int iLenAct = 0;
    Int i,j;
        
    const Int step = bRev ? -1 : 1;

    if( piCbStart == NULL )
        j = 0;
    else
        j = *piCbStart;

    for( i=0; i < iLen; j+=step,++i )
    {
        maxCoef |= COEF_ABS( pVec[j] );
        if( !bRev && j == (iRecLen - 1) )
            j = -1; // increment to 0 at the top of loop
        else if( bRev && j == -(iRecLen - 1) )
            j = 1;  // decrement to 0 at the top of loop
    }

    // perform this check prior to LOG2().
    // can't simply return without properly updating piCbStart. 
    // hence set rshift to 0 for the special case

//    if( 0 == maxCoef || 0 == iLen )
//        return FFLT_ZERO;

    assert( U32_MAX >= maxCoef );

    if( 0 == maxCoef || 0 == iLen )
    {
        rshift = 0;
    }
    else
    {
        rshift  = LOG2( (U32)maxCoef ) + 1;
        rshift *= fExp >> (FEXT_BITS-1);
        rshift += LOG2( (U32)iLen ) - 62;
	    rshift  = (rshift + 3) & ~3;
        if( rshift < 0 ) rshift = 0;
    }

    if( piCbStart == NULL )
        j = 0;
    else
        j = *piCbStart;

    for( i=0; i < iLen; j+=step,++i )
    {
        if (IS_VALID())
        {
            assert( U32_MAX > ABS( pVec[j] ) );

            if( FEXT_FROM_FLOAT( 0.5f ) == fExp )
            {
                fScale += COEF_ABS( pVec[j] ) >> rshift;
            }
            else if( FEXT_FROM_FLOAT( 1.0f ) == fExp )
            {  
                fScale += ( (I64)(pVec[j] >> (rshift/2)) * (I64)(pVec[j] >> (rshift/2)) ) ;
            }
            else if( FEXT_FROM_FLOAT( 2.0f ) == fExp )
            {
                I64 tmp = ( (I64)(pVec[j] >> (rshift/4)) * (I64)(pVec[j] >> (rshift/4)) );
                fScale += tmp * tmp;
            }
            else
            {
                assert( !"only exponents of 0.5, 1, and 2 are supported." );
            }
            assert( 0 <= fScale );
            iLenAct++;
        }
        if( !bRev && j == (iRecLen - 1) )
            j = -1; // increment to 0 at the top of loop
        else if( bRev && j == -(iRecLen - 1) )
            j = 1;  // decrement to 0 at the top of loop
    }
    if( piCbStart )
        *piCbStart = j;

    if (iLenAct != 0 && fScale != 0)
    {
        lshift *= fExp >> (FEXT_BITS-1);
        lshift -= rshift;
        if( 0x3fffffff > fScale ){ fScale <<= 32; lshift += 32; }

        fScale /= iLenAct;

        while( fScale > (U64)0x7fffffff )
        {
            fScale >>= 2;
            lshift  -= 2;
        }

        ffltScale.iFraction = (I32)fScale;
        ffltScale.iFracBits = lshift;
        Norm4FastFloatU( &ffltScale );
        ffltScale = FASTFLOAT_SQRT( ffltScale );
    }

    return ffltScale;

#endif  // BUILD_INTEGER
}

FastFloat freqexGetMvBandScaleWithMaskT( Fex *pfx,
                                    const CoefType *pVec, 
                                    const CoefType *pfRecon,
                                    const U8 *pucMask, 
                                    const Int iLen,
                                    const Bool bRev,
                                    const Int  iRecLen,
                                          Int  *piCbStart,
                                          Int lshift )
{

#ifndef BUILD_INTEGER

    Float fScale  = 0;
    Int iLenAct = 0;

    Int i, k, step;

    step = 1;
    if( bRev )
        step = -1;
    if( piCbStart == NULL )
        k = 0;
    else
        k = *piCbStart;

    for( i=0; i < iLen; ++i,k+=step )
    {
        if (IS_VALID_MASK())
        {
            fScale += pVec[k] * pVec[k];
            iLenAct++;
        }
        if( !bRev && k == (iRecLen - 1) )
            k = -1; // increment to 0 at the top of loop
        else if( bRev && k == -(iRecLen - 1) )
            k = 1;  // decrement to 0 at the top of loop
    }
    if( piCbStart )
        *piCbStart = k;
  
    if (iLenAct != 0)
        return (Float)sqrt( fScale / iLenAct );
    else
        return 0;

#else // !BUILD_INTEGER

    I32 rshift    = 0;
    I64 fScale    = 0;
    Int iLenAct = 0;

    FastFloat ffltScale = FFLT_ZERO;

    Int i, k, step;

    CoefType maxCoef = 0;

    step = 1;
    if( bRev )
        step = -1;
    if( piCbStart == NULL )
        k = 0;
    else
        k = *piCbStart;

    for( i=0; i < iLen; ++i,k+=step )
    {
        if( maxCoef < COEF_ABS( pVec[k] ) )
            maxCoef = COEF_ABS( pVec[k] );
        if( !bRev && k == (iRecLen - 1) )
            k = -1; // increment to 0 at the top of loop
        else if( bRev && k == -(iRecLen - 1) )
            k = 1;  // decrement to 0 at the top of loop
    }

    // perform this check prior to LOG2().

    if( 0 == maxCoef || 0 == iLen ) return FFLT_ZERO;

    assert( U32_MAX > maxCoef );
    rshift  = LOG2( (U32)maxCoef ) + 1;

    rshift *= 2;
    rshift += LOG2( (U32)iLen );
    rshift -= 62;
    rshift += ( rshift % 2 );
    if( rshift < 0 ) rshift = 0;

    step = 1;
    if( bRev )
        step = -1;
    if( piCbStart == NULL )
        k = 0;
    else
        k = *piCbStart;

    for( i=0; i < iLen; ++i,k+=step )
    {
        if (IS_VALID_MASK())
        {
            assert( U32_MAX > ABS( pVec[k] ) );

            fScale += ( (I64)pVec[k] * pVec[k] ) >> rshift;
            assert( 0 <= fScale );
            iLenAct++;
        }
        if( !bRev && k == (iRecLen - 1) )
            k = -1; // increment to 0 at the top of loop
        else if( bRev && k == -(iRecLen - 1) )
            k = 1;  // decrement to 0 at the top of loop
    }
    if( piCbStart )
        *piCbStart = k;

    if (iLenAct != 0 && fScale != 0)
    {
        lshift *= 2;
        lshift -= rshift;
        if( 0x3fffffff > fScale ){ fScale <<= 32; lshift += 32; }

        fScale /= iLenAct;

        while( fScale > (U64)0x7fffffff )
        {
            fScale >>= 2;
            lshift  -= 2;
        }

        ffltScale.iFraction = (I32)fScale;
        ffltScale.iFracBits = lshift;
        Norm4FastFloatU( &ffltScale );
        ffltScale = FASTFLOAT_SQRT( ffltScale );
    }

    return ffltScale;

#endif // BUILD_INTEGER

}

#undef IS_VALID
#undef IS_VALID_MASK
#undef freqexKeepPeaksT
#undef freqexScaleBandT
#undef freqexGetMvBandScaleT
#undef freqexGetMvBandScaleWithMaskT

#if 0 //(defined (FEX_GET_MV_SCALE_C_OPT) && WMA_OPT_FEX_GET_MV_SCALE_ARM)
#undef freqexGetMvBandScaleLoopT
#endif
