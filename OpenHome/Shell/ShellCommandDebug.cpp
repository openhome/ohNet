#include <OpenHome/Private/ShellCommandDebug.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Debug.h>
#include <stdexcept>      // std::out_of_range

using namespace OpenHome;

// ShellCommandDebug

static const TChar kShellCommandDebug[] = "debug";

ShellCommandDebug::ShellCommandDebug(Shell& aShell)
    : iShell(aShell)
{
    iShell.AddCommandHandler(kShellCommandDebug, *this);
    AddLevel("Thread", Debug::kThread);
    //AddLevel("Network", Debug::kNetwork); // Shell is only contactable over network. Attempting to log network interactions will result in endless chain of logging until device crashes.
    AddLevel("Timer", Debug::kTimer);
    AddLevel("SsdpMulticast", Debug::kSsdpMulticast);
    AddLevel("SsdpUnicast", Debug::kSsdpUnicast);
    AddLevel("Http", Debug::kHttp);
    AddLevel("Device", Debug::kDevice);
    AddLevel("XmlFetch", Debug::kXmlFetch);
    AddLevel("Service", Debug::kService);
    AddLevel("Event", Debug::kEvent);
    AddLevel("SsdpNotifier", Debug::kDvSsdpNotifier);
    AddLevel("DvInvocation", Debug::kDvInvocation);
    AddLevel("DvEvent", Debug::kDvEvent);
    AddLevel("DvWebSocket", Debug::kDvWebSocket);
    AddLevel("Bonjour", Debug::kBonjour);
    AddLevel("DvDevice", Debug::kDvDevice);
    AddLevel("Application0", Debug::kApplication0);
    AddLevel("Application1", Debug::kApplication1);
    AddLevel("Application2", Debug::kApplication2);
    AddLevel("Application3", Debug::kApplication3);
    AddLevel("Application4", Debug::kApplication4);
    AddLevel("Application5", Debug::kApplication5);
    AddLevel("Application6", Debug::kApplication6);
    AddLevel("Application7", Debug::kApplication7);
    AddLevel("Application8", Debug::kApplication8);
    AddLevel("Application9", Debug::kApplication9);
    AddLevel("Application10", Debug::kApplication10);
    AddLevel("Application11", Debug::kApplication11);
    AddLevel("Application12", Debug::kApplication12);
    AddLevel("Application13", Debug::kApplication13);
    AddLevel("Application14", Debug::kApplication14);
    AddLevel("Application15", Debug::kApplication15);
    AddLevel("Application16", Debug::kApplication16);
    AddLevel("Application17", Debug::kApplication17);
    AddLevel("Application18", Debug::kApplication18);
    AddLevel("Application19", Debug::kApplication19);
    AddLevel("Application20", Debug::kApplication20);
    AddLevel("Application21", Debug::kApplication21);
    AddLevel("Application22", Debug::kApplication22);
    AddLevel("Application23", Debug::kApplication23);
    AddLevel("Application24", Debug::kApplication24);
    AddLevel("Application25", Debug::kApplication25);
    AddLevel("Application26", Debug::kApplication26);
    AddLevel("Application27", Debug::kApplication27);
    AddLevel("Application28", Debug::kApplication28);
    AddLevel("Application29", Debug::kApplication29);
    AddLevel("Application30", Debug::kApplication30);
    AddLevel("Application31", Debug::kApplication31);
    AddLevel("Application32", Debug::kApplication32);
    AddLevel("Application33", Debug::kApplication33);
    AddLevel("Application34", Debug::kApplication34);
    AddLevel("Application35", Debug::kApplication35);
    AddLevel("Application36", Debug::kApplication36);
    AddLevel("Application37", Debug::kApplication37);
    AddLevel("Application38", Debug::kApplication38);
    AddLevel("Application39", Debug::kApplication39);
    AddLevel("Application40", Debug::kApplication40);
    AddLevel("Application41", Debug::kApplication41);
    AddLevel("Application42", Debug::kApplication42);
    AddLevel("Application43", Debug::kApplication43);
    AddLevel("Application44", Debug::kApplication44);

    AddLevel("AdapterChange", Debug::kAdapterChange);
    AddLevel("CpDeviceDv", Debug::kCpDeviceDv);

    AddLevel("All", Debug::kAll & (~Debug::kNetwork));

    AddSeverity("Critical", Debug::kSeverityCritical);
    AddSeverity("Error", Debug::kSeverityError);
    AddSeverity("Warning", Debug::kSeverityWarning);
    AddSeverity("Info", Debug::kSeverityInfo);
    AddSeverity("Debug", Debug::kSeverityDebug);
    AddSeverity("Trace", Debug::kSeverityTrace);
}

ShellCommandDebug::~ShellCommandDebug()
{
    iShell.RemoveCommandHandler(kShellCommandDebug);
    LevelMap::iterator it = iLevels.begin();
    while (it != iLevels.end()) {
        delete it->second;
        it++;
    }
}

void ShellCommandDebug::SetAlias(const TChar* aName, TUint64 aValue)
{
    Level* level = new Level(aName, aValue);
    Brn name(aName);
    LevelMap::iterator it = iAlias.find(name);
    if (it != iAlias.end()) {
        delete it->second;
        iAlias.erase(it);
    }
    iAlias.insert(std::pair<Brn, Level*>(name, level));
}

void ShellCommandDebug::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() != 2) {
        aResponse.Write(Brn("Unexpected number of arguments for \'debug\' command\n"));
        return;
    }
    TBool set;
    if (aArgs[0] == Brn("set")) {
        set = true;
    }
    else if (aArgs[0] == Brn("clear")) {
        set = false;
    }
    else if (aArgs[0] == Brn("severity")) {
        try {
            Debug::SetSeverity(iSevs.at(aArgs[1]));
        }
        catch (const std::out_of_range&)
        {
            aResponse.Write(Brn("Unexpected severity name for command \'debug\': "));
            aResponse.Write(aArgs[1]);
            aResponse.Write(Brn("\n"));
        }
        return;
    }
    else {
        aResponse.Write(Brn("Unexpected command for \'debug\': "));
        aResponse.Write(aArgs[0]);
        aResponse.Write(Brn("\n"));
        return;
    }
    Brn level = aArgs[1];
    TUint64 val = 0;
    LevelMap::iterator it = iLevels.find(level);
    if (it != iLevels.end()) {
        val = it->second->Value();
    }
    else {
        LevelMap::iterator it2 = iAlias.find(level);
        if (it2 != iAlias.end()) {
            val = it2->second->Value();
        }
    }
    if (val != 0) {
        if (set) {
            Debug::AddLevel(val);
        }
        else {
            Debug::RemoveLevel(val);
        }
    }
    else {
        aResponse.Write(Brn("Unexpected level name for command \'debug\': "));
        aResponse.Write(level);
        aResponse.Write(Brn("\n"));
    }
}

void ShellCommandDebug::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("debug [set|clear] [level]\n"));
    aResponse.Write(Brn("  set or clear a debug level from:\n"));
    LevelMap::iterator it = iLevels.begin();
    while (it != iLevels.end()) {
        Level* level = it->second;
        aResponse.Write(Brn("    "));
        aResponse.Write(Brn(level->Name()));
        aResponse.Write(Brn("\n"));
        it++;
    }
    aResponse.Write(Brn("  Note that any number of levels may be set via repeated calls to debug set.\n"));
}

void ShellCommandDebug::AddLevel(const TChar* aName, TUint64 aValue)
{
    Level* level = new Level(aName, aValue);
    Brn name(aName);
    iLevels.insert(std::pair<Brn, Level*>(name, level));
}

void ShellCommandDebug::AddSeverity(const TChar* aName, TUint aValue)
{
    Brn name(aName);
    iSevs.insert(std::pair<Brn, TUint>(name, aValue));
}

// ShellCommandDebug::Level

ShellCommandDebug::Level::Level(const TChar* aName, TUint64 aValue)
    : iName(aName)
    , iValue(aValue)
{
}

const TChar* ShellCommandDebug::Level::Name() const
{
    return iName;
}

TUint64 ShellCommandDebug::Level::Value() const
{
    return iValue;
}
