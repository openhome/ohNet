//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __CATCH_FLOATOPS_H_
#define __CATCH_FLOATOPS_H_

#if !defined(CATCH_FLOATOPS)

    FORCEINLINE void initFP(){};
    FORCEINLINE void catchFP(){};

#else  // !CATCH_FLOATOPS

    #include <memory.h>

    typedef unsigned __int16 word;

    extern word g_initFP;
    extern word g_rgwFP0[ 56 ];      // reference state
    extern word g_rgwFP1[ 56 ];      // candidate state

    // ==================================================
    // initFP() - initialize floating-point state.
    //
    //      initialize memory, clear all 8 fp
    //      registers, initialize the fp envt.
    //      and then save the state to g_rgFP0
    //
    // ==================================================

    __forceinline void initFP()
    {
        memset( g_rgwFP0, 0xff, sizeof(g_rgwFP0) );   // set all bits to on
        memset( g_rgwFP1, 0xff, sizeof(g_rgwFP1) );   // in both buffers

        _asm
        {
            fldz                // clear all 8 fp registers
            fldz
            fldz
            fldz
            fldz
            fldz
            fldz
            fldz

            finit               // initialize reference state
            fsave g_rgwFP0      // save reference state
        }

        g_initFP = 1;
    }

    // ==================================================
    // catchFP() - examine current floating-point state.
    //
    //      if the reference state has been initialized
    //      and the current state matches the reference,
    //      return. If they do not match, then break.
    //      
    //      if initFP() has not been called yet or
    //      if the states did not match, call initFP().
    //
    // ==================================================

    __forceinline void catchFP()
    {
        if( g_initFP )
        {
            _asm fsave g_rgwFP1

            if( 0 == memcmp( g_rgwFP0, g_rgwFP1, 
                    sizeof(g_rgwFP0) ) ) return;

            _asm int 3
        }

        initFP();
    }

#endif // CATCH_FLOATOPS

#endif // __CATCH_FLOATOPS_H_
