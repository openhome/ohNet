#ifndef HEADER_MATHS
#define HEADER_MATHS

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {

void SetRandomSeed(TUint aSeed);
void SetRandomSeed(const Brx& aSeed);

TUint Random(TUint aMaxValue, TUint aMinValue = 0);

} // namespace OpenHome

#endif // HEADER_MATHS

