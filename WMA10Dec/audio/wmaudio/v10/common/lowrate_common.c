//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains stub functions useful when building WMA Pro or WMA Lossless decoders.
// Actual implementations are in lowrate_commonstd.c
//*@@@---@@@@******************************************************************

#ifdef ENABLE_ALL_ENCOPT

#include <math.h>
#include <limits.h>
#include "stdio.h"

#include "AutoProfile.h" 
#include "msaudio.h"

#include "lowrate_common.h"

#if !defined (BUILD_WMASTD)
WMARESULT prvInverseQuantizeMidRate (CAudioObject* pau, 
                                     PerChannelInfo* ppcinfo, 
                                     Int* rgiWeightFactor)
{
    return WMA_OK;
}
WMARESULT prvInitNoiseSubSecondaryFixed (CAudioObject* pau)
{
    return WMA_OK;
}
WMARESULT prvInitNoiseSubSecondaryAllocated(CAudioObject *pau)
{
    return WMA_OK;
}
#if defined (BUILD_INTEGER)
WMARESULT prvInverseQuantizeLowRate (CAudioObject* pau, 
                                     PerChannelInfo* ppcinfo, 
                                     Int* rgiWeightFactor)
{
    return WMA_OK;
}
#endif // BUILD_INTEGER
#endif // !BUILD_WMASTD
#endif //ENABLE_ALL_ENCOPT

const int g_silence_LNK4221_lowrate_common = 0;