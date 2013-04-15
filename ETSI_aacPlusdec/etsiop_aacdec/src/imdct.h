/*
   IMDCT transform
*/

#ifndef IMDCT_H
#define IMDCT_H


#include "typedef.h"

void CLongBlock_InverseTransform(Word32 data[],
                                 Word16 *imdctScale);

void CShortBlock_InverseTransform(Word32 data[],
                                  Word16 *imdctScale);


#endif /* #ifndef IMDCT_H */
