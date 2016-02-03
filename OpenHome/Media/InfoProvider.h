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
    virtual ~IInfoProvider() {}
};

class IInfoAggregator
{
public:
    virtual void Register(IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries) = 0;
    virtual ~IInfoAggregator() {}
};

class InfoAggregator : public IInfoAggregator, private Net::IShellCommandHandler
{
public:
    InfoAggregator(Net::Shell& aShell);
    ~InfoAggregator();
private: // from IInfoAggregator
    void Register(IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries) override;
private: // from Net::IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse) override;
    void DisplayHelp(IWriter& aResponse) override;
private:
    Net::Shell& iShell;
    std::vector<IInfoProvider*> iInfoProviders;
    typedef std::map<Brn, Brn, BufferCmp> QueryMap;
    QueryMap iQueries;
};

} // namespace Media
} // namespace OpenHome

