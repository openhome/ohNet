#include "AllocatorInfoLogger.h"
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// AllocatorInfoLogger

AllocatorInfoLogger::AllocatorInfoLogger()
{
}

void AllocatorInfoLogger::PrintStats()
{
    for (size_t i=0; i<iInfoProviders.size(); i++) {
        iInfoProviders[i]->QueryInfo(AllocatorBase::kQueryMemory, *this);
    }
}

void AllocatorInfoLogger::Register(Av::IInfoProvider& aProvider, std::vector<Brn>& /*aSupportedQueries*/)
{
    iInfoProviders.push_back(&aProvider);
}

void AllocatorInfoLogger::Write(TByte aValue)
{
    Log::Print("%c", aValue);
}

void AllocatorInfoLogger::Write(const Brx& aBuffer)
{
    Log::Print(aBuffer);
}

void AllocatorInfoLogger::WriteFlush()
{
}
