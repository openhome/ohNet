#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class Logger
{
public:
    Logger();
    void SubnetChanged();
    void SubnetAdded(NetworkAdapter& aAdapter);
    void SubnetRemoved(NetworkAdapter& aAdapter);
    void AdapterChanged(NetworkAdapter& aAdapter);
private:
    TUint iUpdates;
};

Logger::Logger()
    : iUpdates(0)
{
}

void Logger::SubnetChanged()
{
    Log::Print("Logger::SubnetChanged - updates=%u\n", ++iUpdates);
}

void Logger::SubnetAdded(NetworkAdapter& /*aAdapter*/)
{
    Log::Print("Logger::SubnetAdded - updates=%u\n", ++iUpdates);
}

void Logger::SubnetRemoved(NetworkAdapter& /*aAdapter*/)
{
    Log::Print("Logger::SubnetRemoved - updates=%u\n", ++iUpdates);
}

void Logger::AdapterChanged(NetworkAdapter& /*aAdapter*/)
{
    Log::Print("Logger::AdapterChanged - updates=%u\n", ++iUpdates);
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Logger* logger = new Logger();
    aInitParams->SetSubnetListChangedListener(MakeFunctor(*logger, &Logger::SubnetChanged));
    aInitParams->SetSubnetAddedListener(MakeFunctorNetworkAdapter(*logger, &Logger::SubnetAdded));
    aInitParams->SetSubnetRemovedListener(MakeFunctorNetworkAdapter(*logger, &Logger::SubnetRemoved));
    aInitParams->SetNetworkAdapterChangedListener(MakeFunctorNetworkAdapter(*logger, &Logger::AdapterChanged));
    Library* lib = new Net::Library(aInitParams);
    Thread::Sleep(5 * 60 * 1000); // 5 mins
    Log::Print("Closing...\n");

    delete lib;
    delete logger;
}
