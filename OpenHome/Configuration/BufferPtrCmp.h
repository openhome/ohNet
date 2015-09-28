#pragma once

#include <OpenHome/Buffer.h>

namespace OpenHome {
namespace Configuration {

/**
 * Custom comparison function for Brx pointers.
 */
class BufferPtrCmp : public BufferCmp
{
public:
    TBool operator()(const Brx* aStr1, const Brx* aStr2) const;
};

} // namespace Configuration
} // namespace OpenHome

