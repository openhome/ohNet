#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Shell.h>

#include <vector>

namespace OpenHome {

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

class InfoAggregator : public IInfoAggregator, private IShellCommandHandler
{
public:
    InfoAggregator(Shell& aShell);
    ~InfoAggregator();
private: // from IInfoAggregator
    void Register(IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    Shell& iShell;
    std::vector<IInfoProvider*> iInfoProviders;
    typedef std::map<Brn, Brn, BufferCmp> QueryMap;
    QueryMap iQueries;
};

} // namespace OpenHome
