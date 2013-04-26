//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "macros.h"
#include "downmix.h"

// use 2 bits to specify one of following:
//
// 10 = left channel
// 01 = right channel
// 11 = center channel
//
// therefore for all speaker positions, we have following
// 01 11 10 01 11 10 11 01 10 11 01 10 01 10 11 11 01 10
// 0111 1001 1110 1101 1011 0110 0110 1111 0110
// 0x79edb66f6

#define NUM_SPEAKER_POS (18)
#define CHANNEL_LOC_MASK ((U64)0x79edb66f6ULL)
#define CHANNEL_LOC(i) ((CHANNEL_LOC_MASK >> (i<<1)) & 0x3)
#define IS_LEFT_CHANNEL(i) (0x2 == CHANNEL_LOC(i))
#define IS_RIGHT_CHANNEL(i) (0x1 == CHANNEL_LOC(i))
#define IS_CENTER_CHANNEL(i) (0x3 == CHANNEL_LOC(i))
#define PPDMCSWAP(T, a, b) { \
  T ppdmc_temp; \
  ppdmc_temp = a; \
  a = b; \
  b = ppdmc_temp; \
}
#define EQUAL_THRESH (5)

static Int WMADownmixMatrixConv(I32 *rgiDownMix, I32 *rgiCoeff,
                    const Int cNumInCh  , const Int cNumOutCh,
                    const U32 dwInChMask, const U32 dwOutChMask,
                    const Bool fInverse , const Bool fWrite,
                    Bool *pfCoeffValid)
{
    Int i, j, nInCh, nOutCh, cLastValidInCh;
    Int numCoeff = 0, numRowCoeff;
    U32 dwInMask, dwOutMask;
    I32 *pM;
    I32 iCoeff;
    I32 lastLeftCoeff[NUM_SPEAKER_POS];

    if (fInverse)
    {
        for (i=0; i < cNumInCh*cNumOutCh; i++)
            rgiDownMix[i] = I32_MIN;
    }

    *pfCoeffValid = WMAB_TRUE;

    dwOutMask = 0x1;
    nOutCh = 0;
    for (i=0; i < NUM_SPEAKER_POS; i++)
    {
        if (nOutCh == cNumOutCh) break;
        if (dwOutChMask & dwOutMask)
        {
            dwInMask = 0x1;
            nInCh = 0;
            cLastValidInCh = 0;
            for (j=0; j < NUM_SPEAKER_POS; j++)
            {
                if (nInCh == cNumInCh) break;
                if (dwInChMask & dwInMask)
                {
                    if ((IS_LEFT_CHANNEL(i) && !IS_RIGHT_CHANNEL(j)) ||
                        (IS_RIGHT_CHANNEL(i) && !IS_LEFT_CHANNEL(j)) ||
                        IS_CENTER_CHANNEL(i))
                        cLastValidInCh = nInCh;
                    nInCh++;
                }
                dwInMask <<= 1;
            }
            //printf("Last valid channel = %d\n", cLastValidInCh);

            dwInMask = 0x1;
            nInCh = 0;
            pM = &rgiDownMix[nOutCh];
            numRowCoeff = 0;
            for (j=0; j < NUM_SPEAKER_POS; j++)
            {
                if (nInCh > cLastValidInCh) break;
                if (dwInChMask & dwInMask)
                {
                    if (!fInverse)
                    {
                        if ((IS_LEFT_CHANNEL(i) && !IS_RIGHT_CHANNEL(j)) ||
                            IS_CENTER_CHANNEL(i))
                        {
                            if (fWrite)
                                rgiCoeff[numCoeff] = *pM;
                        }
                    }
                    else
                    {
                        if ((IS_LEFT_CHANNEL(i) && !IS_RIGHT_CHANNEL(j)) ||
                            IS_CENTER_CHANNEL(i))
                            *pM = rgiCoeff[numCoeff];
                        else if (IS_RIGHT_CHANNEL(i) && !IS_LEFT_CHANNEL(j))
                            *pM = lastLeftCoeff[numRowCoeff];
                    }
                    if (IS_LEFT_CHANNEL(i) && !IS_RIGHT_CHANNEL(j))
                        lastLeftCoeff[numRowCoeff] = *pM;
                    if (!fInverse)
                    {
                        if ((IS_LEFT_CHANNEL(i) && !IS_RIGHT_CHANNEL(j)) ||
                            IS_CENTER_CHANNEL(i))
                            iCoeff = *pM;
                        else if (IS_RIGHT_CHANNEL(i) && !IS_LEFT_CHANNEL(j))
                            iCoeff = lastLeftCoeff[numRowCoeff];
                        else
                            iCoeff = I32_MIN;
                        if (abs(iCoeff - *pM)>EQUAL_THRESH)
                            *pfCoeffValid = WMAB_FALSE;
                    }
                    if ((IS_LEFT_CHANNEL(i) && !IS_RIGHT_CHANNEL(j)) ||
                        IS_CENTER_CHANNEL(i))
                    {
                        numCoeff++;
                        numRowCoeff++;
                    }
                    else if (IS_RIGHT_CHANNEL(i) && !IS_LEFT_CHANNEL(j))
                    {
                        numRowCoeff++;
                    }
                    nInCh++;
                    pM += cNumOutCh;
                }
                dwInMask <<= 1;
            }
            nOutCh++;
        }
        dwOutMask <<= 1;
    }

    return numCoeff;
}

#undef NUM_SPEAKER_POS
#undef CHANNEL_LOC_MASK
#undef CHANNEL_LOC
#undef IS_LEFT_CHANNEL
#undef IS_RIGHT_CHANNEL
#undef IS_CENTER_CHANNEL
#undef PPDMCSWAP

WMARESULT WMADownmixMatrixToCoeff( const I32 *rgiDownMix,
                          I32 *rgiCoeff , Int *piNumCoeff,
                    const Int cNumInCh  , const Int cNumOutCh,
                    const U32 dwInChMask, const U32 dwOutChMask )
{
    Bool fWrite = WMAB_TRUE;
    Bool fCoeffValid = WMAB_TRUE;
    Int numCoeff, i;

    const Int numMtxCoef = cNumInCh * cNumOutCh;

    // these should be positive values
    if( cNumInCh  < 0 ||
        cNumOutCh < 0 )
        return WMA_E_INVALIDARG;

    // check for integer overflow
    if( numMtxCoef < cNumInCh ||
        numMtxCoef < cNumOutCh )
        return WMA_E_FAIL;

    if (NULL == rgiCoeff)
        fWrite = WMAB_FALSE;

    if (rgiDownMix==NULL) return WMA_E_INVALIDARG;
    if (rgiCoeff==NULL && piNumCoeff==NULL) return WMA_E_INVALIDARG;

    numCoeff = WMADownmixMatrixConv( (I32*)rgiDownMix, rgiCoeff,
                   cNumInCh, cNumOutCh, dwInChMask, dwOutChMask,
                    WMAB_FALSE, fWrite, &fCoeffValid);

    if (numCoeff >= numMtxCoef )
        fCoeffValid = WMAB_FALSE;

    if (fCoeffValid)
    {
        if (piNumCoeff!=NULL)
            *piNumCoeff = numCoeff;
    }
    else
    {
        // full matrix
        if (piNumCoeff!=NULL)
            *piNumCoeff = numMtxCoef;
        if (rgiCoeff != NULL)
            for (i=0; i < numMtxCoef; i++)
                rgiCoeff[i] = rgiDownMix[i];
    }

    return WMA_OK;
}

WMARESULT WMADownmixCoeffToMatrix(I32 *rgiDownMix,
              const I32 *rgiCoeff , const Int iNumCoeff,
              const Int cNumInCh  , const Int cNumOutCh,
              const U32 dwInChMask, const U32 dwOutChMask)
{
    Int numCoeff, i;
    Bool fCoeffValid;

    if (rgiDownMix==NULL || rgiCoeff==NULL || iNumCoeff==0)
        return WMA_E_INVALIDARG;

    assert(iNumCoeff <= cNumInCh*cNumOutCh);
    if (iNumCoeff==cNumInCh*cNumOutCh)
    {
        for (i=0; i < cNumInCh*cNumOutCh; i++)
            rgiDownMix[i] = rgiCoeff[i];
    }
    else
    {
        numCoeff = WMADownmixMatrixConv(rgiDownMix, (I32*)rgiCoeff,
                      cNumInCh, cNumOutCh, dwInChMask, dwOutChMask,
                      WMAB_TRUE, WMAB_TRUE, &fCoeffValid);

        assert(numCoeff == iNumCoeff);
    }

    return WMA_OK;
}

