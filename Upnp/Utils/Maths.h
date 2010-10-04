#ifndef HEADER_MATHS
#define HEADER_MATHS

#include <ZappTypes.h>
#include <Standard.h>
#include <Buffer.h>

namespace Zapp
{

void SetRandomSeed(TUint aSeed);
void SetRandomSeed(const Brx& aSeed);

TUint Random(TUint aMaxValue, TUint aMinValue = 0);

} // namespace Zapp

#endif // HEADER_MATHS

