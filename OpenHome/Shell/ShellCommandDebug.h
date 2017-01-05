#ifndef HEADER_SHELL_COMMAND_DEBUG
#define HEADER_SHELL_COMMAND_DEBUG

#include <OpenHome/Private/Shell.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

#include <vector>
#include <map>

namespace OpenHome {
class IWriter;

class ShellCommandDebug : private IShellCommandHandler
{
public:
    ShellCommandDebug(Shell& aShell);
    ~ShellCommandDebug();
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    void AddLevel(const TChar* aName, TUint64 aValue);
private:
    class Level
    {
    public:
        Level(const TChar* aName, TUint64 aValue);
        const TChar* Name() const;
        TUint64 Value() const;
    private:
        const TChar* iName;
        TUint64 iValue;
    };
private:
    Shell& iShell;
    typedef std::map<Brn, Level*, BufferCmp> LevelMap;
    LevelMap iLevels;
};

} // namespace OpenHome

#endif // HEADER_SHELL_COMMAND_DEBUG
