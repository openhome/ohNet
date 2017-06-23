#include <OpenHome/Av/Scd/Sender/Demo/DirScanner.h>
#include <OpenHome/Av/Scd/Sender/Demo/WavSender.h>

#include <string>
#include <filesystem>

using namespace OpenHome;
using namespace OpenHome::Scd;
using namespace OpenHome::Scd::Sender;
using namespace OpenHome::Scd::Sender::Demo;

void DirScanner::Run(std::string& aPath, IScdSupply& aSupply)
{
    for (auto it = std::tr2::sys::directory_iterator(aPath); it != std::tr2::sys::directory_iterator(); ++it) {
        std::cout << it->path() << std::endl;
        WavSender sender(it->path(), aSupply);
        sender.Run();
    }
}
