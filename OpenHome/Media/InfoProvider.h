#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Private/Shell.h>

#include <vector>

namespace OpenHome {
namespace Media {

class IInfoProvider
{
public:
    virtual void QueryInfo(const Brx& aQuery, IWriter& aWriter) = 0;
};

class IInfoAggregator
{
public:
    virtual void Register(IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries) = 0;
};

class InfoAggregator : public IInfoAggregator, private Net::IShellCommandHandler
{
public:
    InfoAggregator(Net::Shell& aShell);
    ~InfoAggregator();
private: // from IInfoAggregator
    void Register(IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // Net::IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    Net::Shell& iShell;
    std::vector<IInfoProvider*> iInfoProviders;
    typedef std::map<Brn, Brn, BufferCmp> QueryMap;
    QueryMap iQueries;
};

} // namespace Media
} // namespace OpenHome

