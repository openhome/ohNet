//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

{
    Int i;
    CoefType *pct0Begin = pctCoef,
             *pct0End = pctCoef + REFL_HALF - 1;
    for (i=0; i < REFL_SIZE/4; i++)
    {
        CoefType b2 = *pct2Begin,
                 b3 = *pct3Begin,
                 e3 = *pct3End,
                 b1 = *pct1Begin;
        *pct3Begin = *pct1End + *pct0Begin;
        *pct3End   = *pct1Begin + *pct0End;
        *pct1Begin = *pct1End - *pct0Begin;
        *pct1End   = b1       - *pct0End;
        *pct0Begin = *pct2End + b3;
        *pct0End   = b2 + e3;
        *pct2Begin = *pct2End - b3;
        *pct2End   = b2 - e3;
        pct0Begin++;
        pct0End--;
    }
}
