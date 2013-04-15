#include <stdio.h>

#include "intrinsics.h"



int main()
{
    Word32 result = fixmul(Word32(2), Word32(4));
    
    printf("%l\n", result);
    
    return 0;
}
