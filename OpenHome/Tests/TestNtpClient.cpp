#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Types.h>
#include <OpenHome/NtpClient.h>


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Environment* env = Net::UpnpLibrary::Initialise(aInitParams);

    NtpClient* ntpClient = new NtpClient(*env);
    ntpClient->TestAllServers();
    delete ntpClient;

    Net::UpnpLibrary::Close();
}
