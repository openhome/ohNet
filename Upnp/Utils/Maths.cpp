// This license applies to all the random related functions
//
// mtrand.h
// C++ include file for MT19937, with initialization improved 2002/1/26.
// Coded by Takuji Nishimura and Makoto Matsumoto.
// Ported to C++ by Jasper Bedaux 2003/1/1 (see http://www.bedaux.net/mtrand/).
// The generators returning floating point numbers are based on
// a version by Isaku Wada, 2002/01/09
//
// Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. The names of its contributors may not be used to endorse or promote
//    products derived from this software without specific prior written
//    permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Any feedback is very welcome.
// http://www.math.keio.ac.jp/matumoto/emt.html
// email: matumoto@math.keio.ac.jp
//
// Feedback about the C++ port should be sent to Jasper Bedaux,
// see http://www.bedaux.net/mtrand/ for e-mail address and info.


#include <Maths.h>
#include <Arch.h>
#include <stdlib.h>

using namespace Zapp;

static const TUint kMersennePoint = 397;
static const TUint kMaxRandomIndex = 624;

TBool gRandomSeedSet = false;
TUint gRandomIndex;
TUint gRandomState[kMaxRandomIndex];

TUint Twiddle(TUint u, TUint v)
{
    return (((u & 0x80000000UL) | (v & 0x7FFFFFFFUL)) >> 1) ^ ((v & 1UL) ? 0x9908B0DFUL : 0x0UL);
}

void Zapp::SetRandomSeed(const Brx& aSeed)
{
    ASSERT(aSeed.Bytes() >= 4);
    
    TUint seed = 0;
    TUint i = 0;    

    for (i = 0; i < aSeed.Bytes() - 3; i += 4) {
        seed ^= Arch::LittleEndian4(*((TUint32*)(aSeed.Ptr()+i)));
    }

    // xor the remaining bytes.
    while( i < aSeed.Bytes() ) {
        seed ^= *((TUint8*)(aSeed.Ptr()+i)) << (aSeed.Bytes()-i);
        i++;
    }
    
    SetRandomSeed(seed);
}

void Zapp::SetRandomSeed(TUint aSeed)
{
    srand(aSeed);
    gRandomState[0] = aSeed;
    
    for (TUint i = 1; i < kMaxRandomIndex; ++i) {
        gRandomState[i] = 1812433253UL * (gRandomState[i - 1] ^ (gRandomState[i - 1] >> 30)) + i;
    }
    
    gRandomIndex = kMaxRandomIndex; // force GenerateState() to be called for next random number
    
    gRandomSeedSet = true;
}

TUint Zapp::Random(TUint aMaxValue, TUint aMinValue)
{
    ASSERT(aMaxValue > aMinValue);

    if (!gRandomSeedSet) {
        SetRandomSeed(123456789);
    }
    
    if (gRandomIndex == kMaxRandomIndex) {
        for (TUint i = 0; i < (kMaxRandomIndex - kMersennePoint); ++i) {
            gRandomState[i] = gRandomState[i + kMersennePoint] ^ Twiddle(gRandomState[i], gRandomState[i + 1]);
        }
        
        for (TUint i = (kMaxRandomIndex - kMersennePoint); i < (kMaxRandomIndex - 1); ++i) {
            gRandomState[i] = gRandomState[i + kMersennePoint - kMaxRandomIndex] ^ Twiddle(gRandomState[i], gRandomState[i + 1]);
        }
        
        gRandomState[kMaxRandomIndex - 1] = gRandomState[kMersennePoint - 1] ^ Twiddle(gRandomState[kMaxRandomIndex - 1], gRandomState[0]);
        
        gRandomIndex = 0; // reset position
    }
  
    TUint random = gRandomState[gRandomIndex++];
    
    random ^= (random >> 11);
    random ^= (random << 7) & 0x9D2C5680UL;
    random ^= (random << 15) & 0xEFC60000UL;
    random ^= (random >> 18);

    TUint modulo = aMaxValue - aMinValue + 1;
    
    if (!modulo) {
        return (random);
    }
    
    return ((random % (aMaxValue - aMinValue + 1)) + aMinValue);
}

