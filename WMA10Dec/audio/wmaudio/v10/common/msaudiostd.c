//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains functions needed for WMA Std. These are not needed by WMA Pro or Lossless.
//*@@@---@@@@******************************************************************
    /*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    MsAudio.cpp

Abstract:

    Implementation of public member functions for CAudioObject.

Author:

    Wei-ge Chen (wchen) 11-March-1998

Revision History:


*************************************************************************/

// Print out the target we're building for
#define COMMONMACROS_OUTPUT_TARGET

#if !defined (_WIN32_WCE) && !defined (HITACHI)
#include <time.h>
#endif  // _WIN32_WCE

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include "msaudio.h"
#include "AutoProfile.h"
#include "macros.h"
#include "float.h"
#include "wavfileexio.h"
#include "drccommon.h"

#if defined (BUILD_WMASTD)
//*****************************************************************************************
//
// prvWeightedQuantization
// calculate 10^( (MaskQ-MaxMaskQ)*2.5*0.5/20 ) * 10^( QuantStepSize/20 )
//         = (10^(1/16))^( MaskQ-MaxMaskQ )     * (10^(1/20)^QuantStepSize
//*****************************************************************************************
QuantFloat prvWeightedQuantization(CAudioObject *pau, PerChannelInfo *ppcinfo, Int iBark)
{
    Int iIndex = ppcinfo->m_iMaxMaskQ - ppcinfo->m_rgiMaskQ[iBark];
    QuantFloat qfltRMS;
    assert( 0 <= iIndex );

    if( iIndex >= MASK_MINUS_POWER_TABLE_SIZE )
         iIndex = MASK_MINUS_POWER_TABLE_SIZE-1;

#if defined(BUILD_INTEGER)
    {
        Int uiFraction, iFracBits;
        uiFraction = rgiMaskMinusPower10[ iIndex ];     // with MASK_POWER_FRAC_BITS==28 fractional bits
        iFracBits = MASK_POWER_FRAC_BITS+(iIndex>>2);
        //MONITOR_RANGE(gMR_WeightRatio,(Float)uiFraction/(Float)pow(2.0F,iFracBits));
#       if defined(_DEBUG) && !defined(CATCH_FLOATOPS)
        {
            Float realRMS = (Float)pow(10.0F,(Float)(ppcinfo->m_rgiMaskQ[iBark] - ppcinfo->m_iMaxMaskQ)/(1<<4));
            Float Calculated = (Float)uiFraction/(Float)pow(2.0F,iFracBits); 
            Float diff = (Float)fabs(realRMS-Calculated);
            Float rel = (Float)fabs(diff/realRMS);
            if (rel > .00002)
                DEBUG_BREAK();
        }
#       endif
        qfltRMS.iFraction = MULT_HI(pau->m_qstQuantStep.iFraction,uiFraction);  
        qfltRMS.iFracBits = pau->m_qstQuantStep.iFracBits + iFracBits - 31;
        Norm4FastFloat( &qfltRMS );
    }
#else

    qfltRMS = rgiMaskMinusPower10[ iIndex ] / (Float)(1<<(iIndex>>2));
    MONITOR_RANGE(gMR_WeightRatio,qfltRMS);
    qfltRMS *= FLOAT_FROM_QUANTSTEPTYPE( pau->m_qstQuantStep );  

#endif

    return qfltRMS;
}//prvWeightedQuantization
#endif // BUILD_WMASTD

