//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************


AVRT_DATA const U16 g_chexHuffScaleDec[24] = {
    0x8801, 0x0003, 0x8400, 0x8400, 0x8c02, 0x8c02, 0x9003, 0x0001, 
    0x9404, 0x9404, 0x9805, 0x0001, 0xa007, 0x0003, 0x9c06, 0x9c06, 
    0xa808, 0x0003, 0xa409, 0xa409, 0xac0a, 0xac0a, 0xb00b, 0xb00c
};

AVRT_DATA const Int g_chexHuffScaleMinSym = 0;
AVRT_DATA const Int g_chexHuffScaleMinBits = 0;

AVRT_DATA const Int g_chexHuffScaleMaxSym = 11;
AVRT_DATA const Int g_chexHuffScaleMaxBits = 4;

AVRT_DATA const U16 g_chexHuffScalePredDec[28] = {
    0x8400, 0x8400, 0x0002, 0x8801, 0x0004, 0x9003, 0x8c02, 0x8c02, 
    0x0004, 0x9805, 0x9404, 0x9404, 0x0004, 0xa007, 0x9c06, 0x9c06, 
    0xa408, 0xa408, 0xa809, 0x0001, 0xac0a, 0xac0a, 0xb00b, 0x0001, 
    0xb40c, 0xb40c, 0xb40d, 0xb40d
};

AVRT_DATA const Int g_chexHuffScalePredMinSym = 0;
AVRT_DATA const Int g_chexHuffScalePredMinBits = 0;

AVRT_DATA const Int g_chexHuffScalePredMaxSym = 12;
AVRT_DATA const Int g_chexHuffScalePredMaxBits = 6;

