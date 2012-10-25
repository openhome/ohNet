#ifndef HEADER_ALLOCATOR_INFO_LOGGER
#define HEADER_ALLOCATOR_INFO_LOGGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Private/Stream.h>

#include <vector>

namespace OpenHome {
namespace Media {

class AllocatorInfoLogger : public Av::IInfoAggregator, private IWriter
{
public:
    AllocatorInfoLogger();
    void PrintStats();
private: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    std::vector<Av::IInfoProvider*> iInfoProviders;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_ALLOCATOR_INFO_LOGGER
