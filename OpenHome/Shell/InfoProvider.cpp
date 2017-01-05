#include <OpenHome/Private/InfoProvider.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Shell.h>

#include <vector>
#include <map>

using namespace OpenHome;


static const TChar kShellCommandInfo[] = "info";

InfoAggregator::InfoAggregator(Shell& aShell)
    : iShell(aShell)
{
    iShell.AddCommandHandler(kShellCommandInfo, *this);
}

InfoAggregator::~InfoAggregator()
{
    iShell.RemoveCommandHandler(kShellCommandInfo);
}

void InfoAggregator::Register(IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries)
{
    iInfoProviders.push_back(&aProvider);
    for (TUint i=0; i<(TUint)aSupportedQueries.size(); i++) {
        Brn query(aSupportedQueries[i]);
        auto it = iQueries.find(query);
        if (it == iQueries.end()) {
            iQueries.insert(std::pair<Brn,Brn>(query, query));
        }
    }
}

void InfoAggregator::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() != 1) {
        aResponse.Write(Brn("Unexpected number of arguments for \'info\' command\n"));
        return;
    }
    Brn query(aArgs[0]);
    for (TUint i=0; i<(TUint)iInfoProviders.size(); i++) {
        iInfoProviders[i]->QueryInfo(query, aResponse);
    }
}

void InfoAggregator::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("info [query]\n"));
    aResponse.Write(Brn("  supported queries are:\n"));
    auto it = iQueries.begin();
    while (it != iQueries.end()) {
        aResponse.Write(Brn("    "));
        aResponse.Write(it->second);
        aResponse.Write(Brn("\n"));
        it++;
    }
}
