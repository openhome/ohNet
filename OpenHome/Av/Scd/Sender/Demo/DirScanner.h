#pragma once

#include <string>

namespace OpenHome {
namespace Scd {
namespace Sender {
    class IScdSupply;
namespace Demo {

class DirScanner
{
public:
    static void Run(std::string& aPath, IScdSupply& aSupply);
};

} // namespace Demo
} // namespace Sender
} // namespace Scd
} // namespace OpenHome
