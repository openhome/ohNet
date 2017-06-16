#include "WavSender.h"
#include <OpenHome/Defines.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Media/Tests/Cdecl.h>
#include <OpenHome/Av/Scd/Sender/Demo/DirScanner.h>
#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Av/Scd/Sender/ScdSupply.h>
#include <OpenHome/Av/Scd/Sender/ScdServer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>

#include <stdlib.h>
#include <filesystem>

using namespace OpenHome;
using namespace OpenHome::Scd;
using namespace OpenHome::Scd::Sender;
using namespace OpenHome::Scd::Sender::Demo;

class DummySupply : public IScdSupply
{
public:
    void OutputMetadataDidl(const std::string& /*aUri*/, const std::string& /*aMetadata*/) override {}
    void OutputMetadataOh(const OpenHomeMetadata& /*aMetadata*/) override {}
    void OutputFormat(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels,
                      TUint /*aBitRate*/, TUint64 /*aSampleStart*/, TUint64 /*aSamplesTotal*/,
                      TBool /*aSeekable*/, TBool /*aLossless*/, TBool /*aLive*/,
                      TBool /*aBroadcastAllowed*/, const std::string& /*aCodecName*/)
    {
        printf("  Format: bitDepth=%u, sampleRate=%u, numChannels=%u\n", aBitDepth, aSampleRate, aNumChannels);
    }
    void OutputAudio(const TByte* /*aData*/, TUint /*aBytes*/) {}
    void OutputMetatextDidl(const std::string& /*aMetatext*/) {}
    void OutputMetatextOh(const OpenHomeMetadata& /*aMetatext*/) {}
    void OutputHalt() {}
};


int CDECL main(int aArgc, char* aArgv[])
{
#ifdef _WIN32
    char* noErrDlgs = getenv("NO_ERROR_DIALOGS");
    if (noErrDlgs != nullptr && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
#endif // _WIN32

    // Parse options.
    TestFramework::OptionParser parser;
    TestFramework::OptionString optionDir("-d", "--dir", Brn("c:\\TestAudio\\CodecStress"), "Directory to search for WAV files");
    parser.AddOption(&optionDir);
    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    auto initParams = Net::InitialisationParams::Create();
    auto lib = new Net::Library(initParams);
    auto subnetList = lib->CreateSubnetList();
    auto subnet = (*subnetList)[0]->Subnet();
    Net::Library::DestroySubnetList(subnetList);
    /*auto cpStack = */lib->StartCp(subnet);

    Debug::AddLevel(Debug::kScd);

    // app goes here
    ScdMsgFactory factory(1,   // Ready
                          0,   // MetadataDidl
                          5,   // MetadataOh,
                          5,   // Format,
                          100, // Audio,
                          0,   // MetatextDidl,
                          5,   // MetatextOh,
                          1,   // Halt,
                          1,   // Disconnect,
                          0,   // Seek,
                          0    // Skip
                         );
    ScdSupply supply(factory);
    ScdServer server(lib->Env(), supply, factory);
    Endpoint::EndpointBuf buf;
    server.Endpoint().AppendEndpoint(buf);
    Log::Print("SCD Sender running on %s\n", buf.Ptr());
    std::string path(optionDir.CString());
    //DummySupply supply;
    DirScanner::Run(path, supply);

    delete lib;

    return 0;
}
