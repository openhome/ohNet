//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

AVRT_DATA const RvrbType g_rgfRvrbGains[3] = {
    RVRB_FROM_FLOAT(0.7f),
    RVRB_FROM_FLOAT(0.6f),
    RVRB_FROM_FLOAT(0.5f)
};
AVRT_DATA const Float g_rgfRvrbDelay[3] = {0.4f, 1.2f, 3.6f};
AVRT_DATA const Int   g_rgiRvrbDelay[3] = {1, 2, 3};

// ====================================================================

#if ( 1 == CX_SMALL_REVERB )

WMARESULT cxReverbInitHistAndGain(CxReverbFilter *pcxrf)
{
    WMARESULT wmaResult = WMA_OK;
    Int iNumStages, iCh;
    __bound Int nTotal;
    CoefType *pEnd, *pBuf;
    const RvrbType *rgfGains = g_rgfRvrbGains;
    const Float *rgfDelay = g_rgfRvrbDelay;
    const Int *rgiDelay = g_rgiRvrbDelay;

#if (CX_DCT_ONLY==0)
    Int iBand, iStart, j;
    RvrbType *pGain;

    // allocate gain buffer
    nTotal = ( pcxrf->m_iNumBands[0] +
               pcxrf->m_iNumBands[1] +
               pcxrf->m_iNumBands[2] ) * 4;
    pcxrf->m_rgfGains = (RvrbType*)callocAligned(nTotal*sizeof(RvrbType), 16);
    CHECKWMA_ALLOC( wmaResult, pcxrf->m_rgfGains );

    // initialize gain buffer
    pGain = pcxrf->m_rgfGains;
    iBand  = 0;
    iStart = 0;
    for( iNumStages = CXREVERB_STAGES; iNumStages > 0; --iNumStages )
    {
        for( ; iBand < pcxrf->m_iNumBands[iNumStages-1]; ++iBand )
        {
            const Int iFreq = iStart + pcxrf->m_rgiNumFreq[iBand]/2;

            for( j=0; j < iNumStages; ++j )
            {
                const Float c    = (Float)(2.0f*PI*(rgfDelay[j]-rgiDelay[j])
                                           * iFreq) / pcxrf->m_iNumFreq;
                const Float cosC = (Float)cos( c );
                const Float sinC = (Float)sin( c );
                    
                *(pGain++) = RVRB_FROM_FLOAT(  cosC );
                *(pGain++) = RVRB_FROM_FLOAT( -sinC );
                *(pGain++) = (RvrbType)( -cosC*rgfGains[j] );
                *(pGain++) = (RvrbType)(  sinC*rgfGains[j] );
            }
            iStart += pcxrf->m_rgiNumFreq[iBand];
        }
    }
#endif

    // Allocate history position buffer
    pcxrf->m_iHistCurr = 
        (Int (*)[CXREVERB_STAGES])auCalloc(pcxrf->m_iNumChannel*
                                           sizeof(pcxrf->m_iHistCurr[0]));
    CHECKWMA_ALLOC( wmaResult, pcxrf->m_iHistCurr );

    // Allocate history pointer buffer
    pcxrf->m_rgpHistBuf = (CoefType*(*)[CXREVERB_STAGES][CXREVERB_HIST_LEN])
        auCalloc(sizeof(pcxrf->m_rgpHistBuf[0])*pcxrf->m_iNumChannel);
    CHECKWMA_ALLOC( wmaResult, pcxrf->m_rgpHistBuf );

    // Allocate actual history buffer
    nTotal = ( pcxrf->m_iNumFreqs[0] * 3
             + pcxrf->m_iNumFreqs[1] * 3
             + pcxrf->m_iNumFreqs[2] * 4 ) * pcxrf->m_iNumChannel;

#if (CX_DCT_ONLY==0)
    nTotal *= 2; // real/imag
#endif

    pcxrf->m_nTotalHistSize = nTotal;

    pBuf = (CoefType*)callocAligned( nTotal * sizeof(CoefType), 16 );
    CHECKWMA_ALLOC(wmaResult, pBuf );

    // Initialize history pointer buffer
    pEnd = pBuf + nTotal;
    for( iCh=0; iCh < pcxrf->m_iNumChannel; ++iCh )
    {
        for( iNumStages=CXREVERB_STAGES; iNumStages > 0; --iNumStages )
        {
            const Int iHistSize = (iNumStages+2)*(iNumStages+1)/2;
            const Int iNumFreqs = pcxrf->m_iNumFreqs[iNumStages-1]
                                - pcxrf->m_iNumFreqs[iNumStages  ];
            Int iHist;

            for( iHist=0; iHist < iHistSize; ++iHist )
            {
                pcxrf->m_rgpHistBuf[ iCh ][ 3-iNumStages ][ iHist ] = pBuf;
#if (CX_DCT_ONLY==0)
                pBuf += iNumFreqs * 2;
#else
                pBuf += iNumFreqs;
#endif
                assert( pBuf <= pEnd );
            }
        }
    }

exit:
    return wmaResult;
}

#else // CX_SMALL_REVERB

WMARESULT cxReverbInitHistAndGain(CxReverbFilter *pcxrf)
{
    WMARESULT wmaResult = WMA_OK;
    Int nTotal, iBand, iStart, iCh, i, j;
    CoefType *pBuf;

    UInt nFreqs0 = pcxrf->m_iNumFreqs[0];
    UInt nFreqs1 = pcxrf->m_iNumFreqs[1];
    UInt nFreqs2 = pcxrf->m_iNumFreqs[2];

    const RvrbType *rgfGains = g_rgfRvrbGains;
    const Float *rgfDelay = g_rgfRvrbDelay;
    const Int *rgiDelay = g_rgiRvrbDelay;

    // allocate/initialize gain buffer
    nTotal = ( pcxrf->m_iNumFreqs[0] +
               pcxrf->m_iNumFreqs[1] +
               pcxrf->m_iNumFreqs[2] ) * 4;

    pcxrf->m_rgGainInDReal[0] =
        (RvrbType*)callocAligned( nTotal*sizeof(RvrbType), 16 );
    CHECKWMA_ALLOC( wmaResult, pcxrf->m_rgGainInDReal[0] );

    pcxrf->m_rgGainInDReal[1] = pcxrf->m_rgGainInDReal[0] + nFreqs0;
    pcxrf->m_rgGainInDReal[2] = pcxrf->m_rgGainInDReal[1] + nFreqs1;
    pcxrf->m_rgGainInDImag[0] = pcxrf->m_rgGainInDReal[2] + nFreqs2;
    pcxrf->m_rgGainInDImag[1] = pcxrf->m_rgGainInDImag[0] + nFreqs0;
    pcxrf->m_rgGainInDImag[2] = pcxrf->m_rgGainInDImag[1] + nFreqs1;
    pcxrf->m_rgGainOutReal[0] = pcxrf->m_rgGainInDImag[2] + nFreqs2;
    pcxrf->m_rgGainOutReal[1] = pcxrf->m_rgGainOutReal[0] + nFreqs0;
    pcxrf->m_rgGainOutReal[2] = pcxrf->m_rgGainOutReal[1] + nFreqs1;
    pcxrf->m_rgGainOutImag[0] = pcxrf->m_rgGainOutReal[2] + nFreqs2;
    pcxrf->m_rgGainOutImag[1] = pcxrf->m_rgGainOutImag[0] + nFreqs0;
    pcxrf->m_rgGainOutImag[2] = pcxrf->m_rgGainOutImag[1] + nFreqs1;

    for( j = 0; j < CXREVERB_STAGES; ++j )
    {
        RvrbType *pGainInDReal = pcxrf->m_rgGainInDReal[j];
        RvrbType *pGainInDImag = pcxrf->m_rgGainInDImag[j];
        RvrbType *pGainOutReal = pcxrf->m_rgGainOutReal[j];
        RvrbType *pGainOutImag = pcxrf->m_rgGainOutImag[j];

        for( iStart = 0, iBand = 0; iBand < pcxrf->m_iNumBands[j]; ++iBand )
        {
            // shift of d is e^(-j*2*pi*k*d/N)

            const Int iFreq  = iStart + pcxrf->m_rgiNumFreq[iBand]/2;
#if (CX_DCT_ONLY==1)
            const Float c = 0.0f;
#else
            const Float c = (Float)(2.0f*PI*(rgfDelay[j]-rgiDelay[j])*iFreq)/pcxrf->m_iNumFreq;
#endif
            const Float cosC = (Float)cos( c );
            const Float sinC = (Float)sin( c );
            Int k;

            for( k = 0; k < pcxrf->m_rgiNumFreq[iBand]; ++k )
            {
                *pGainInDReal++ = RVRB_FROM_FLOAT(  cosC );
                *pGainInDImag++ = RVRB_FROM_FLOAT( -sinC );
                *pGainOutReal++ = (RvrbType)( -cosC*rgfGains[j] );
                *pGainOutImag++ = (RvrbType)(  sinC*rgfGains[j] );
            }
            iStart += pcxrf->m_rgiNumFreq[iBand];
        }
    }

    // history position
    pcxrf->m_iHistCurr = 
        (Int*)auCalloc(pcxrf->m_iNumChannel*sizeof(Int));
    CHECKWMA_ALLOC( wmaResult, pcxrf->m_iHistCurr );

    // history pointer buffer
    pcxrf->m_rgpHistBuf = (CoefType*(*)[CXREVERB_HIST_LEN]) 
        auCalloc(sizeof(pcxrf->m_rgpHistBuf[0])*pcxrf->m_iNumChannel);
    CHECKWMA_ALLOC( wmaResult, pcxrf->m_rgpHistBuf );

    // actual history buffer
    pBuf = (CoefType*)callocAligned(2*CXREVERB_HIST_LEN*pcxrf->m_iNumFreq*
             pcxrf->m_iNumChannel*sizeof(CoefType), 16);
    CHECKWMA_ALLOC(wmaResult, pBuf );

    // initialize history pointer buffer
    for( iCh=0; iCh < pcxrf->m_iNumChannel; ++iCh )
    {
        for( i=0; i < CXREVERB_HIST_LEN; ++i )
        {
            pcxrf->m_rgpHistBuf[iCh][i] = pBuf;
            pBuf += pcxrf->m_iNumFreq*2; 
        }
    }

exit:
    return wmaResult;
}

#endif // CX_SMALL_REVERB

WMARESULT cxReverbInit(CAudioObject *pau, CxReverbFilter *pcxrf)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    Int i, iStart, iEnd, iFreq;
    Float fFreq;

    pcxrf->m_pau = pau;

    if (WMAB_TRUE == pcx->m_bDoReverbAsPostProcess)
        pcxrf->m_iNumChannel = pau->m_cChannel;
    else
        pcxrf->m_iNumChannel = 1;

    TRACEWMA_EXIT(wmaResult, chexInitTileConfig(pcx, NULL, WMAB_TRUE, 0));

    pcxrf->m_iNumFreq = prp->m_cFrameSampleHalfChex;
    pcxrf->m_iNumFreqRanges = pcx->m_cBands;

    pcxrf->m_rgiNumFreq = (Int*)auCalloc(pcxrf->m_iNumFreqRanges*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcxrf->m_rgiNumFreq);

    pcxrf->m_rgiFreqEnd =
        (Int*)auCalloc(pcxrf->m_iNumFreqRanges*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcxrf->m_rgiFreqEnd);

    pcxrf->m_iNumBands[0] = 0;  pcxrf->m_iNumFreqs[0] = 0;
    pcxrf->m_iNumBands[1] = 0;  pcxrf->m_iNumFreqs[1] = 0;
    pcxrf->m_iNumBands[2] = 0;  pcxrf->m_iNumFreqs[2] = 0;
    pcxrf->m_iNumBands[3] = 0;  pcxrf->m_iNumFreqs[3] = 0;

    for( iStart = 0, i = 0; i < pcxrf->m_iNumFreqRanges; ++i )
    {
        pcxrf->m_rgiNumFreq[i] = (Int)pcx->m_rgiBandSizes[i];
        iFreq = iStart + pcxrf->m_rgiNumFreq[i]/2;
        iEnd  = iStart + pcxrf->m_rgiNumFreq[i];
        pcxrf->m_rgiFreqEnd[i] = iEnd;

        fFreq = (Float)iFreq/pcxrf->m_iNumFreq*(pau->m_iSamplingRate/2.0f);

        pcxrf->m_iNumBands[0]++;
        pcxrf->m_iNumFreqs[0] += pcxrf->m_rgiNumFreq[i];

        if( 10000.0f > fFreq )
        {
            pcxrf->m_iNumBands[1]++;
            pcxrf->m_iNumFreqs[1] += pcxrf->m_rgiNumFreq[i];
        }
        if(  5000.0f > fFreq )
        {
            pcxrf->m_iNumBands[2]++;
            pcxrf->m_iNumFreqs[2] += pcxrf->m_rgiNumFreq[i];
        }

        iStart += pcxrf->m_rgiNumFreq[i];
    }

    assert( 0 == pcxrf->m_iNumFreqRanges % 4 );

    // in order to make sure that my SSE code in cxReverbFilter_SSE1() doesn't
    // puke because of un-aligned addresses, align all the rgGain*[] buffers on
    // 16-byte boundaries ( 4-float boundaries ).
    if( pcxrf->m_iNumFreqs[0]&3 )
        pcxrf->m_iNumFreqs[0] = (pcxrf->m_iNumFreqs[0]+4)&~3;
    if( pcxrf->m_iNumFreqs[1]&3 )
        pcxrf->m_iNumFreqs[1] = (pcxrf->m_iNumFreqs[1]+4)&~3;
    if( pcxrf->m_iNumFreqs[2]&3 )
        pcxrf->m_iNumFreqs[2] = (pcxrf->m_iNumFreqs[2]+4)&~3;

    TRACEWMA_EXIT(wmaResult, cxReverbInitHistAndGain(pcxrf));

exit:
    return wmaResult;
}

Void cxReverbFree(CxReverbFilter *pcxrf)
{
    if (NULL == pcxrf)
        return;

    DELETE_ARRAY(pcxrf->m_rgiNumFreq);
    DELETE_ARRAY(pcxrf->m_rgiFreqEnd);
    DELETE_ARRAY(pcxrf->m_iHistCurr);

#if ( 1 == CX_SMALL_REVERB )
    freeAligned(pcxrf->m_rgfGains);
    if( pcxrf->m_rgpHistBuf )
    {
        freeAligned(pcxrf->m_rgpHistBuf[0][0][0]);
        DELETE_ARRAY(pcxrf->m_rgpHistBuf);
    }
#else // so ( 0 == CX_SMALL_REVERB )
    freeAligned(pcxrf->m_rgGainInDReal[0]);
    if( pcxrf->m_rgpHistBuf )
    {
        freeAligned(pcxrf->m_rgpHistBuf[0][0]);
        DELETE_ARRAY(pcxrf->m_rgpHistBuf);
    }
#endif // CX_SMALL_REVERB

}

Void cxReverbAddInput(CxReverbFilter *pcxrf,
                      const CoefType *pDataReal, 
                      const CoefType *pDataImag,
                      Int iSize, Int iCh )
{
    CoefType *pBufRe, *pBufIm;
    Int i, k, l;
    Int iNumStages = 0;
    ChexType scale;

    const Int iStep = pcxrf->m_iNumFreq/iSize;

    assert(iCh < pcxrf->m_iNumChannel);
    assert(iSize <= pcxrf->m_iNumFreq);

    assert(iStep*iSize == pcxrf->m_iNumFreq);

    switch (iStep)
    {
        case 1:  scale = CX_ONE;        break;
        case 2:  scale = CX_SQRT2;      break;
        case 4:  scale = 2 * CX_ONE;    break;
        case 8:  scale = 2 * CX_SQRT2;  break;
        case 16: scale = 4 * CX_ONE;    break;
        default: assert(!"Invalid size");  scale = CX_ONE;
    }

    k = 0;
    l = 0;

#if ( 1 == CX_SMALL_REVERB )

    for( iNumStages = CXREVERB_STAGES; iNumStages > 0; --iNumStages )
    {
        const Int iNumFreqs = pcxrf->m_iNumFreqs[iNumStages-1]
                            - pcxrf->m_iNumFreqs[iNumStages  ];
        const Int offs = cxReverbOffsetHist( pcxrf, iCh, 0, iNumStages );
        pBufRe   = pcxrf->m_rgpHistBuf[ iCh ][ 3-iNumStages ][ offs ];
        pBufIm   = pBufRe + iNumFreqs;

        if( 1 == iStep )
        {
            memcpy( pBufRe, pDataReal, sizeof(CoefType)*iNumFreqs );
            pDataReal += iNumFreqs;

#if (CX_DCT_ONLY==0)
            memcpy( pBufIm, pDataImag, sizeof(CoefType)*iNumFreqs );
            pDataImag += iNumFreqs;
#endif
        }
        else for( i=0; i<iNumFreqs; ++i )
        {
            if (l == 0)
            { 
                pBufRe[i] = COEF_MUL_CXSC( pDataReal[k], scale );
#if (CX_DCT_ONLY==0)
                pBufIm[i] = COEF_MUL_CXSC( pDataImag[k], scale );
#endif
                k++;
            }
            else
            {
                if (k != iSize)
                {
                    const ChexType scaleA = (       l *scale) / iStep;
                    const ChexType scaleB = ((iStep-l)*scale) / iStep;

                    pBufRe[i] = COEF_MUL_CXSC( pDataReal[k  ], scaleA )
                              + COEF_MUL_CXSC( pDataReal[k-1], scaleB );
                    
#if (CX_DCT_ONLY==0)
                    pBufIm[i] = COEF_MUL_CXSC( pDataImag[k  ], scaleA )
                              + COEF_MUL_CXSC( pDataImag[k-1], scaleB );
#endif
                }
                else
                {
                    pBufRe[i] = COEF_MUL_CXSC( pDataReal[k-1], scale );
#if (CX_DCT_ONLY==0)
                    pBufIm[i] = COEF_MUL_CXSC( pDataImag[k-1], scale );
#endif
                }
            }
            if (++l == iStep)
                l = 0;
        }
    }

#else

    pBufRe = pcxrf->m_rgpHistBuf[ iCh ][ cxReverbOffsetHist( pcxrf, iCh, 0 ) ];
    pBufIm = pBufRe + pcxrf->m_iNumFreq;

    if( 1 == iStep )
    {
        memcpy( pBufRe, pDataReal, sizeof(CoefType)*iSize );
        memcpy( pBufIm, pDataImag, sizeof(CoefType)*iSize );
    }
    else for (i=0; i < pcxrf->m_iNumFreq; i++)
    {
        if (l == 0)
        { 
            pBufRe[i] = COEF_MUL_CXSC(pDataReal[k], scale);
            pBufIm[i] = COEF_MUL_CXSC(pDataImag[k], scale);
            k++;
        }
        else
        {
            if (k != iSize)
            {
                const ChexType scaleA = (       l *scale) / iStep;
                const ChexType scaleB = ((iStep-l)*scale) / iStep;

                pBufRe[i] = COEF_MUL_CXSC( pDataReal[k  ], scaleA )
                          + COEF_MUL_CXSC( pDataReal[k-1], scaleB );
                
                pBufIm[i] = COEF_MUL_CXSC( pDataImag[k  ], scaleA )
                          + COEF_MUL_CXSC( pDataImag[k-1], scaleB );
            }
            else
            {
                pBufRe[i] = COEF_MUL_CXSC(pDataReal[k-1], scale);
                pBufIm[i] = COEF_MUL_CXSC(pDataImag[k-1], scale);
            }
        }
        if (++l == iStep)
            l = 0;
    }

#endif

}

// minimize storage by doing IIR filters as follows
// suppose for 2 stage with delays 1 & 2, we have the following
// y0[n] = g0* x[n] +  x[n-1] - g0*y0[n-1]
// y1[n] = g1*y0[n] + y0[n-2] - g1*y1[n-2]
// then for history we create following buffer (cicular)
//      x[n-1] y0[n-1] y0[n-2] y1[n-1] y1[n-2]
// new input comes in we get
// x[n]   x[n-1]  y0[n-1] y0[n-2] y1[n-1] y1[n-2]
// after first stage filtering we get (overwrite x[n-1])
// x[n]   y0[n]   y0[n-1] y0[n-2] y1[n-1] y1[n-2]
// after second state we get (overwrite y0[n-2])
// x[n]   y0[n]   y0[n-1] y1[n]   y1[n-1] y1[n-2]
// take output and let y1[n-2] be next place for new input
// x[n-1] y0[n-1] y0[n-2] y1[n-1] y1[n-2] <next input>

//   x[ n ]   x[n-1]   y[n-1]   y[n-2]   z[n-1]   z[n-2]   z[n-3]   w[n-1]   w[n-2]   w[n-3]   x[n+1]
//   x[ n ]   y[ n ]   y[n-1]   y[n-2]   z[n-1]   z[n-2]   z[n-3]   w[n-1]   w[n-2]   w[n-3]   x[n+1]
//   x[ n ]   y[ n ]   y[n-1]   z[ n ]   z[n-1]   z[n-2]   z[n-3]   w[n-1]   w[n-2]   w[n-3]   x[n+1]
//   x[ n ]   y[ n ]   y[n-1]   z[ n ]   z[n-1]   z[n-2]   w[ n ]   w[n-1]   w[n-2]   w[n-3]   x[n+1]

//   x[n-1]   y[n-1]   y[n-2]   z[n-1]   z[n-2]   z[n-3]   w[n-1]   w[n-2]   w[n-3]   x[n+1]   x[ n ]

#if ( 1 == CX_SMALL_REVERB )

#if (CX_DCT_ONLY==0)

#define FILTER_RE(  xr0,   g0,                      \
                    xr1, gxr1, xi1, gxi1,           \
                    yr1, gyr1, yi1, gyi1 )          \
    (CoefType)( COEF_MUL_RVRB( xr0, g0   ) +        \
                COEF_MUL_RVRB( xr1, gxr1 ) -        \
                COEF_MUL_RVRB( xi1, gxi1 ) +        \
                COEF_MUL_RVRB( yr1, gyr1 ) -        \
                COEF_MUL_RVRB( yi1, gyi1 ) )

#define FILTER_IM(  xi0,   g0,                      \
                    xr1, gxr1, xi1, gxi1,           \
                    yr1, gyr1, yi1, gyi1 )          \
    (CoefType)( COEF_MUL_RVRB( xi0, g0   ) +        \
                COEF_MUL_RVRB( xr1, gxi1 ) +        \
                COEF_MUL_RVRB( xi1, gxr1 ) +        \
                COEF_MUL_RVRB( yi1, gyr1 ) +        \
                COEF_MUL_RVRB( yr1, gyi1 ) )

#endif // CX_DCT_ONLY

Void cxReverbFilter( CxReverbFilter *pcxrf, Int iCh )
{
    const RvrbType *pGain = pcxrf->m_rgfGains;

    Int iNumStages;
    Int iNumFreqs = 0;
    Int iBand     = 0;

    const RvrbType *rgfGains = g_rgfRvrbGains;

#if defined(TABLE_REVERB_FILTER) && CX_DCT_ONLY
    CoefType *pPointerTab[18];
    CoefType **ppPointer = pPointerTab, **ppPointer0 = pPointerTab;
    Int offsC, offsD1, offsD2;

    // iStage: 1,2,3
    // iCurr:  0,1,3
    // 0,1,2  1,3,5  3,6,9
    iNumStages = 3;
    offsC  = cxReverbOffsetHist( pcxrf, iCh, 0, iNumStages );
    offsD1 = cxReverbOffsetHist( pcxrf, iCh, 1, iNumStages );
    offsD2 = cxReverbOffsetHist( pcxrf, iCh, 2, iNumStages );
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsC];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD1];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD2];
    offsC  = cxReverbOffsetHist( pcxrf, iCh, 1, iNumStages );
    offsD1 = cxReverbOffsetHist( pcxrf, iCh, 3, iNumStages );
    offsD2 = cxReverbOffsetHist( pcxrf, iCh, 5, iNumStages );
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsC];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD1];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD2];
    offsC  = cxReverbOffsetHist( pcxrf, iCh, 3, iNumStages );
    offsD1 = cxReverbOffsetHist( pcxrf, iCh, 6, iNumStages );
    offsD2 = cxReverbOffsetHist( pcxrf, iCh, 9, iNumStages );
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsC];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD1];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD2];

    iNumStages--;
    offsC  = cxReverbOffsetHist( pcxrf, iCh, 0, iNumStages );
    offsD1 = cxReverbOffsetHist( pcxrf, iCh, 1, iNumStages );
    offsD2 = cxReverbOffsetHist( pcxrf, iCh, 2, iNumStages );
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsC];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD1];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD2];
    offsC  = cxReverbOffsetHist( pcxrf, iCh, 1, iNumStages );
    offsD1 = cxReverbOffsetHist( pcxrf, iCh, 3, iNumStages );
    offsD2 = cxReverbOffsetHist( pcxrf, iCh, 5, iNumStages );
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsC];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD1];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD2];

    iNumStages--;
    offsC  = cxReverbOffsetHist( pcxrf, iCh, 0, iNumStages );
    offsD1 = cxReverbOffsetHist( pcxrf, iCh, 1, iNumStages );
    offsD2 = cxReverbOffsetHist( pcxrf, iCh, 2, iNumStages );
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsC];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD1];
    *ppPointer++ = pcxrf->m_rgpHistBuf[iCh][3-iNumStages][offsD2];

#endif  // TABLE_REVERB_FILTER

    assert(iCh < pcxrf->m_iNumChannel);

#if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM

    for( iNumStages = 3; iNumStages > 0; --iNumStages )
    {
        const Int iNumBands = pcxrf->m_iNumBands[iNumStages-1];
        const Int iNumFreqs = pcxrf->m_iNumFreqs[iNumStages-1]
                            - pcxrf->m_iNumFreqs[iNumStages  ];

        Int iFreqSkip = 0;
        CoefType **pHistBuf = pcxrf->m_rgpHistBuf[ iCh ][ 3-iNumStages ];

        for( ; iBand < iNumBands; ++iBand )
        {
            const Int iNumBandFreqs = pcxrf->m_rgiNumFreq[ iBand ];

            Int iStage, iCurr;

#if defined(TABLE_REVERB_FILTER) && CX_DCT_ONLY
            ppPointer = ppPointer0;
#endif            
            for( iStage = 0, iCurr = 0; iStage++ < iNumStages; )
            {

                // for each band,
                // get the # of frequencies
                // get the gain array pointer

                const RvrbType fGain = rgfGains[iStage-1];
#if defined(TABLE_REVERB_FILTER) && CX_DCT_ONLY
                const CoefType *pInCurRe  = *ppPointer++ + iFreqSkip;
                      CoefType *pOutCurRe = *ppPointer++ + iFreqSkip;
                const CoefType *pOutDelRe = *ppPointer++ + iFreqSkip;
#else 
                const Int offsC  = cxReverbOffsetHist( pcxrf, iCh, iCurr         , iNumStages );
                const Int offsD1 = cxReverbOffsetHist( pcxrf, iCh, iCurr+iStage  , iNumStages );
                const Int offsD2 = cxReverbOffsetHist( pcxrf, iCh, iCurr+iStage*2, iNumStages );

                const CoefType *pInCurRe  = pHistBuf[ offsC  ] + iFreqSkip;
                      CoefType *pOutCurRe = pHistBuf[ offsD1 ] + iFreqSkip;
                const CoefType *pOutDelRe = pHistBuf[ offsD2 ] + iFreqSkip;
#endif

#if (CX_DCT_ONLY==0)
                const CoefType *pInDelRe  = pHistBuf[ offsD1 ] + iFreqSkip;
                const CoefType *pInCurIm  = pInCurRe  + iNumFreqs;
                      CoefType *pOutCurIm = pOutCurRe + iNumFreqs;
                const CoefType *pInDelIm  = pInDelRe  + iNumFreqs;
                const CoefType *pOutDelIm = pOutDelRe + iNumFreqs;
#endif
                Int i;

                for( i=0; i<iNumBandFreqs; ++i )
                {
#if (CX_DCT_ONLY==0)
                    const CoefType tmpRe = FILTER_RE(
                        pInCurRe [i], fGain   ,
                        pOutCurRe[i], pGain[0], pInDelIm [i], pGain[1],
                        pOutDelRe[i], pGain[2], pOutDelIm[i], pGain[3] );

                    const CoefType tmpIm = FILTER_IM( 
                        pInCurIm [i], fGain   ,
                        pOutCurRe[i], pGain[0], pInDelIm [i], pGain[1],
                        pOutDelRe[i], pGain[2], pOutDelIm[i], pGain[3] );

                    pOutCurRe[i] = tmpRe;
                    pOutCurIm[i] = tmpIm;
#else
                    pOutCurRe[i] += COEF_MUL_RVRB( pInCurRe[i]-pOutDelRe[i], fGain );
#endif
                }   // for( i=0; i<iNumBandFreqs; ++i )

                iCurr += iStage;
#if (CX_DCT_ONLY==0)
                pGain += 4;
#endif
            }       // for( iStage = 0, iCurr = 0; iStage++ < iNumStages; )

            iFreqSkip += iNumBandFreqs;
        }       // for( ; iBand < iNumBands; ++iBand )
#if defined(TABLE_REVERB_FILTER) && CX_DCT_ONLY
        ppPointer0 = ppPointer;
#endif            
    }       // for( iNumStages = 3; iNumStages > 0; --iNumStages )

#else   // if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM
    cxReverbFilterLoopSmall(pcxrf, ppPointer0, rgfGains);
#endif  // if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM

    pcxrf->m_iHistCurr[iCh][0] = cxReverbOffsetHist( pcxrf, iCh, -1, 3 );
    pcxrf->m_iHistCurr[iCh][1] = cxReverbOffsetHist( pcxrf, iCh, -1, 2 );
    pcxrf->m_iHistCurr[iCh][2] = cxReverbOffsetHist( pcxrf, iCh, -1, 1 );
}

#else // so ( 0 == CX_SMALL_REVERB )

Void cxReverbFilter( CxReverbFilter *pcxrf, Int iCh )
{
    Int j;
#if 1 //!WMA_OPT_CHEXPRO_ARM
    Int k;
#endif
    Int iCurr = 0;

    const RvrbType *rgfGains = g_rgfRvrbGains;
    const Int *rgiDelay = g_rgiRvrbDelay;

    assert(iCh < pcxrf->m_iNumChannel);

    for( j=0; j < 3; ++j )
    {
        const RvrbType gainIn = rgfGains[j];
        const Int      iDelay = rgiDelay[j];
        const Int   iNumFreq  = pcxrf->m_iNumFreq;
        const Int   iNumFreqs = pcxrf->m_iNumFreqs[j];

        const Int   offsC  = cxReverbOffsetHist( pcxrf, iCh, iCurr          );
        const Int   offsD1 = cxReverbOffsetHist( pcxrf, iCh, iCurr+iDelay   );
        const Int   offsD2 = cxReverbOffsetHist( pcxrf, iCh, iCurr+iDelay*2 );

        const RvrbType *pGainInDRe = pcxrf->m_rgGainInDReal[j];
        const RvrbType *pGainInDIm = pcxrf->m_rgGainInDImag[j];
        const RvrbType *pGainOutRe = pcxrf->m_rgGainOutReal[j];
        const RvrbType *pGainOutIm = pcxrf->m_rgGainOutImag[j];

        const CoefType *pInCurRe  = pcxrf->m_rgpHistBuf[ iCh ][ offsC  ];
              CoefType *pOutCurRe = pcxrf->m_rgpHistBuf[ iCh ][ offsD1 ];
        const CoefType *pInDelRe  = pcxrf->m_rgpHistBuf[ iCh ][ offsD1 ];
        const CoefType *pOutDelRe = pcxrf->m_rgpHistBuf[ iCh ][ offsD2 ];

        const CoefType *pInCurIm  = pInCurRe  + iNumFreq;
              CoefType *pOutCurIm = pOutCurRe + iNumFreq;
        const CoefType *pInDelIm  = pInDelRe  + iNumFreq;
        const CoefType *pOutDelIm = pOutDelRe + iNumFreq;

#if 1 //!WMA_OPT_CHEXPRO_ARM
        for( k = 0; k < iNumFreqs; ++k )
        {
            const RvrbType gainInDReal  = pGainInDRe[ k ];
            const RvrbType gainInDImag  = pGainInDIm[ k ];
            const RvrbType gainOutReal  = pGainOutRe[ k ];
            const RvrbType gainOutImag  = pGainOutIm[ k ];

            const CoefType inRealCurr   = pInCurRe  [ k ];
            const CoefType inRealDelay  = pInDelRe  [ k ];
            const CoefType outRealDelay = pOutDelRe [ k ];

            const CoefType inImagCurr   = pInCurIm  [ k ];
            const CoefType inImagDelay  = pInDelIm  [ k ];
            const CoefType outImagDelay = pOutDelIm [ k ];

            const CoefType outRealCurr = (CoefType)(
                COEF_MUL_RVRB( inRealCurr  , gainIn      ) +
                COEF_MUL_RVRB( inRealDelay , gainInDReal ) -
                COEF_MUL_RVRB( inImagDelay , gainInDImag ) +
                COEF_MUL_RVRB( outRealDelay, gainOutReal ) -
                COEF_MUL_RVRB( outImagDelay, gainOutImag ));

            const CoefType outImagCurr = (CoefType)(
                COEF_MUL_RVRB( inImagCurr  , gainIn      ) +
                COEF_MUL_RVRB( inRealDelay , gainInDImag ) +
                COEF_MUL_RVRB( inImagDelay , gainInDReal ) +
                COEF_MUL_RVRB( outImagDelay, gainOutReal ) +
                COEF_MUL_RVRB( outRealDelay, gainOutImag ));

            pOutCurRe[ k ] = outRealCurr;
            pOutCurIm[ k ] = outImagCurr;
        }
#else   // WMA_OPT_CHEXPRO_ARM
//      Prototype:
//  void cxReverbFilterLoop(const Int iNumFreqs,
//          const Int iNumFreq,
//          const RvrbType gainIn,
//          const RvrbType *pGainInDRe,
//          const RvrbType *pGainInDIm,
//          const RvrbType *pGainOutRe,
//          const RvrbType *pGainOutIm,
//          const CoefType *pInCurRe,
//                CoefType *pOutCurRe,
//          const CoefType *pInDelRe,
//          const CoefType *pOutDelRe);

        cxReverbFilterLoop(iNumFreqs, iNumFreq,
            gainIn, pGainInDRe, pGainInDIm, pGainOutRe, pGainOutIm,
            pInCurRe, pOutCurRe, pInDelRe, pOutDelRe);
#endif  // WMA_OPT_CHEXPRO_ARM

        if( iNumFreq - iNumFreqs )
        {
            // each IIR pass only hits 'iNumFreqs' freqency coefficients, but there
            // are 'iNumFreq' total coefficients.  The ones that are not filtered in
            // this pass need to be copied ( equivalent to gainIn = 1 ). If there
            // are any of these extra coefficients, copy them to the new destination.

            memcpy( pOutCurRe + iNumFreqs, pInCurRe + iNumFreqs, 
                sizeof(CoefType)*(pcxrf->m_iNumFreq - iNumFreqs));
            memcpy( pOutCurIm + iNumFreqs, pInCurIm + iNumFreqs, 
                sizeof(CoefType)*(pcxrf->m_iNumFreq - iNumFreqs));
        }  

        iCurr += iDelay;
    }

    pcxrf->m_iHistCurr[iCh] = cxReverbOffsetHist( pcxrf, iCh, -1 );
}

#if defined(BUILD_INT_FLOAT) && !defined(WMA_DISABLE_SSE1)
#include <xmmintrin.h>
Void cxReverbFilter_SSE1( CxReverbFilter *pcxrf, Int iCh )
{
    Int j, k;
    Int iCurr = 0;

    const RvrbType *rgfGains = g_rgfRvrbGains;
    const Int *rgiDelay = g_rgiRvrbDelay;

    assert(iCh < pcxrf->m_iNumChannel);

    for( j=0; j < 3; ++j )
    {
        const Int iDelay    = rgiDelay[j];
        const Int iNumFreq  = pcxrf->m_iNumFreq;
        const Int iNumFreqs = pcxrf->m_iNumFreqs[j];

        const Int offsC  = cxReverbOffsetHist( pcxrf, iCh, iCurr          );
        const Int offsD1 = cxReverbOffsetHist( pcxrf, iCh, iCurr+iDelay   );
        const Int offsD2 = cxReverbOffsetHist( pcxrf, iCh, iCurr+iDelay*2 );

        const Float * const pGainInDRe = pcxrf->m_rgGainInDReal[j];
        const Float * const pGainInDIm = pcxrf->m_rgGainInDImag[j];
        const Float * const pGainOutRe = pcxrf->m_rgGainOutReal[j];
        const Float * const pGainOutIm = pcxrf->m_rgGainOutImag[j];

        const Float * const pInCurRe  = pcxrf->m_rgpHistBuf[ iCh ][ offsC  ];
              Float * const pOutCurRe = pcxrf->m_rgpHistBuf[ iCh ][ offsD1 ];
        const Float * const pInDelRe  = pcxrf->m_rgpHistBuf[ iCh ][ offsD1 ];
        const Float * const pOutDelRe = pcxrf->m_rgpHistBuf[ iCh ][ offsD2 ];

        const Float * const pInCurIm  = pInCurRe  + iNumFreq;
              Float * const pOutCurIm = pOutCurRe + iNumFreq;
        const Float * const pInDelIm  = pInDelRe  + iNumFreq;
        const Float * const pOutDelIm = pOutDelRe + iNumFreq;

        const __m128 gainIn = _mm_set1_ps( rgfGains[j] );

        assert( 0 == ((size_t)pGainInDRe) % 16 );
        assert( 0 == ((size_t)pInCurRe  ) % 16 );

        // iNumFreqs _might_ not be a multiple of 4, but
        // all of these buffers are allocated in multiples
        // of 4, so the below operation will work in SSE1.

        for( k = 0; k < iNumFreqs; k += 4 )
        {
            __m128 inRe, inIm, gainRe, gainIm, outRe, outIm;

            outRe  = _mm_load_ps( pInCurRe + k );
            outIm  = _mm_load_ps( pInCurIm + k );

            outRe  = _mm_mul_ps(  outRe, gainIn );
            outIm  = _mm_mul_ps(  outIm, gainIn );

            inRe   = _mm_load_ps( pInDelRe + k );
            inIm   = _mm_load_ps( pInDelIm + k );

            gainRe = _mm_load_ps( pGainInDRe + k );
            gainIm = _mm_load_ps( pGainInDIm + k );

            outRe  = _mm_add_ps( outRe, _mm_mul_ps(  inRe, gainRe ) );
            outRe  = _mm_sub_ps( outRe, _mm_mul_ps(  inIm, gainIm ) );
            outIm  = _mm_add_ps( outIm, _mm_mul_ps(  inRe, gainIm ) );
            outIm  = _mm_add_ps( outIm, _mm_mul_ps(  inIm, gainRe ) );

            inRe   = _mm_load_ps( pOutDelRe + k );
            inIm   = _mm_load_ps( pOutDelIm + k );

            gainRe = _mm_load_ps( pGainOutRe + k );
            gainIm = _mm_load_ps( pGainOutIm + k );

            outRe  = _mm_add_ps( outRe, _mm_mul_ps(  inRe, gainRe ) );
            outRe  = _mm_sub_ps( outRe, _mm_mul_ps(  inIm, gainIm ) );
            outIm  = _mm_add_ps( outIm, _mm_mul_ps(  inRe, gainIm ) );
            outIm  = _mm_add_ps( outIm, _mm_mul_ps(  inIm, gainRe ) );

            _mm_store_ps( pOutCurRe + k, outRe );
            _mm_store_ps( pOutCurIm + k, outIm );
        }

        if( iNumFreq - iNumFreqs )
        {
            // each IIR pass only hits 'iNumFreqs' freqency coefficients, but there
            // are 'iNumFreq' total coefficients.  The ones that are not filtered in
            // this pass need to be copied ( equivalent to gainIn = 1 ). If there
            // are any of these extra coefficients, copy them to the new destination.

            memcpy( pOutCurRe + iNumFreqs, pInCurRe + iNumFreqs, sizeof(Float)*(pcxrf->m_iNumFreq - iNumFreqs));
            memcpy( pOutCurIm + iNumFreqs, pInCurIm + iNumFreqs, sizeof(Float)*(pcxrf->m_iNumFreq - iNumFreqs));
        }

        iCurr += iDelay;
    }
    
    pcxrf->m_iHistCurr[iCh] = cxReverbOffsetHist( pcxrf, iCh, -1 );
}


#endif

#endif // ! CX_SMALL_REVERB

#if 0

Void cxReverbDumpHistBuf(CxReverbFilter *pcxrf, Int iCh, Int iType, FILE *fp)
{
    CAudioObject *pau = pcxrf->m_pau;
    ChexType *pBuf;
    Int i, j, k, f, iIndex;
    char cType;

    FILE_DUMP_INIT(cxrhist);
    switch (iType)
    {
    case 0: cType = 'B'; break; // before input
    case 1: cType = 'F'; break; // after filter
    }

    f = 0;
    for (i=0; i < pcxrf->m_iNumFreqRanges; i++)
    {
        for (k=0; k < pcxrf->m_rgiNumFreq[i]; k++, f++)
        {
            if (f != 1)
                continue;

            fprintf(fp, "%c ", cType);
            for (j=0; j < pcxrf->m_rgiNumHistBuf[i]; j++)
            {
                iIndex = pcxrf->m_rgrgiHistStart[iCh][i] + j + 1;
                iIndex = cxReverbOffsetHist(pcxrf, i, iIndex);
                pBuf =
                    pcxrf->m_ppHistBuf[iCh][i]+iIndex*pcxrf->m_rgiNumFreq[i]*2;
                fprintf(fp, "%10.3f%+10.3fj ", FLOAT_FROM_CHEX(pBuf[2*k]),
                        FLOAT_FROM_CHEX(pBuf[2*k+1]));
            }
            fprintf(fp, "\n");
        }
    }
    if (1==iType)
        fprintf(fp, "\n");

    fflush(fp);
}

Void cxReverbDumpOutput(CxReverbFilter *pcxrf, CoefType *pData, Int iSize,
                        FILE *fp)
{
    CAudioObject *pau = pcxrf->m_pau;
    Int i;

    FILE_DUMP_INIT(cxrout);

    for (i=0; i < iSize; i++)
    {
        fprintf(fp, "%10.3f%+10.3fj\n", pData[i], pData[i+iSize]);
    }
    fprintf(fp, "\n");
}

#endif 

Void cxReverbGetOutput(CxReverbFilter *pcxrf,
                       CoefType *pDataReal,
                       CoefType *pDataImag,
                       Int iSize, Int iCh,
                       ChexFilterOutput eFilterTap)
{
    const CoefType *pBufRe;
    const CoefType *pBufIm;
    const Int iStep = pcxrf->m_iNumFreq/iSize;

    Int i, k, l, iIndex = 0;
    ChexType scale;
    CoefType totalReal, totalImag;
    Int iNumStages = 0;

    assert(iCh < pcxrf->m_iNumChannel);
    assert(iSize <= pcxrf->m_iNumFreq);
    assert((Int)eFilterTap >= 0);

    assert(iStep*iSize == pcxrf->m_iNumFreq);

    switch (iStep)
    {
        case 1:  scale = CX_ONE;        break;
        case 2:  scale = CX_SQRT2;      break;
        case 4:  scale = 2 * CX_ONE;    break;
        case 8:  scale = 2 * CX_SQRT2;  break;
        case 16: scale = 4 * CX_ONE;    break;
        default: assert(!"Invalid size");  scale = CX_ONE;
    }

    k = 0;
    l = 0;
    totalReal = 0;
    totalImag = 0;

#if ( 1 == CX_SMALL_REVERB )

    for( iNumStages = CXREVERB_STAGES; iNumStages > 0; --iNumStages )
    {
        const Int iIndexLUT[3][4] = 
        {
            {1,2,4,7},
            {1,2,4,4},
            {1,2,2,2},
        };

        const Int iNumFreqs = pcxrf->m_iNumFreqs[iNumStages-1]
                            - pcxrf->m_iNumFreqs[iNumStages  ];
        const Int iHist = iIndexLUT[3-iNumStages][eFilterTap];
        const Int offs = cxReverbOffsetHist( pcxrf, iCh, iHist, iNumStages );
        pBufRe   = pcxrf->m_rgpHistBuf[ iCh ][ 3-iNumStages ][ offs ];
        pBufIm   = pBufRe + iNumFreqs;

        if( 1 == iStep )
        {
            memcpy( pDataReal, pBufRe, sizeof(CoefType)*iNumFreqs );
            pDataReal += iNumFreqs;

#if (CX_DCT_ONLY==0)
            memcpy( pDataImag, pBufIm, sizeof(CoefType)*iNumFreqs );
            pDataImag += iNumFreqs;
#endif
        }
        else for (i=0; i < iNumFreqs; ++i )
        {
            totalReal += pBufRe[i];
#if (CX_DCT_ONLY==0)
            totalImag += pBufIm[i];
#endif
            l++;
            if (l == iStep)
            {
                pDataReal[k] = COEF_MUL_CXSC(totalReal, scale);
                totalReal = 0;
#if (CX_DCT_ONLY==0)
                pDataImag[k] = COEF_MUL_CXSC(totalImag, scale);
                totalImag = 0;
#endif
                l = 0;
                k++;
            }
        }
    }

#else

    switch (eFilterTap)
    {
    case 0: iIndex = 1;  break;
    case 1: iIndex = 2;  break;
    case 2: iIndex = 4;  break;
    case 3: iIndex = 7;  break;
    default: assert(!"Invalid filter tap");
    }

    pBufRe = pcxrf->m_rgpHistBuf[ iCh ][ cxReverbOffsetHist( pcxrf, iCh, iIndex ) ];
    pBufIm = pBufRe + pcxrf->m_iNumFreq;

    if( 1 == iStep )
    {
        memcpy( pDataReal, pBufRe, sizeof(CoefType)*iSize );
        memcpy( pDataImag, pBufIm, sizeof(CoefType)*iSize );
    }
    else for (i=0; i < pcxrf->m_iNumFreq; ++i )
    {
        totalReal += pBufRe[i];
        totalImag += pBufIm[i];
        l++;
        if (l == iStep)
        {
            pDataReal[k] = COEF_MUL_CXSC(totalReal, scale);
            pDataImag[k] = COEF_MUL_CXSC(totalImag, scale);
            l = 0;
            totalReal = 0;
            totalImag = 0;
            k++;
        }
    }

#endif
}
