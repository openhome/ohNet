#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Private/Stream.h>

#include <vector>

namespace OpenHome {
namespace Media {

class AllocatorInfoLogger : public IInfoAggregator, private IWriter
{
public:
    AllocatorInfoLogger();
    void PrintStats();
private: // from IInfoAggregator
    void Register(IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    std::vector<IInfoProvider*> iInfoProviders;
};

} // namespace Media
} // namespace OpenHome

