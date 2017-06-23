#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

namespace OpenHome {
namespace Scd {
namespace Sender {
    class IScdSupply;
namespace Demo {

class WavSender
{
public:
    WavSender(const std::string& aFilename, IScdSupply& aSupply);
    void Run();
private:
    bool TryParseHeader(uint32_t& aAudioBytes);
private:
    std::ifstream iFile;
    std::string iFilename;
    IScdSupply& iSupply;
    char iBuf[4096];
};

} // namespace Demo
} // namespace Sender
} // namespace Scd
} // namespace OpenHome
