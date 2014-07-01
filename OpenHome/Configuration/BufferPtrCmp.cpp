#include <OpenHome/Configuration/BufferPtrCmp.h>

using namespace OpenHome;
using namespace OpenHome::Configuration;


// BufferPtrCmp

TBool BufferPtrCmp::operator()(const Brx* aStr1, const Brx* aStr2) const
{
    return BufferCmp()(*aStr1, *aStr2);
}
