#include <OpenHome/Av/Scd/Sender/Demo/WavSender.h>
#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Av/Scd/Sender/ScdSupply.h>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Scd;
using namespace OpenHome::Scd::Sender;
using namespace OpenHome::Scd::Sender::Demo;


WavSender::WavSender(const std::string& aFilename, IScdSupply& aSupply)
    : iFile(aFilename, std::ifstream::binary)
    , iFilename(aFilename)
    , iSupply(aSupply)
{
}

void WavSender::Run()
{
    uint32_t remaining = 0;
    if (!TryParseHeader(remaining)) {
        return;
    }
    while (remaining > 0) {
        uint32_t bytes = std::min(remaining, sizeof iBuf);
        iFile.read(iBuf, bytes);
        bytes = static_cast<uint32_t>(iFile.gcount());
        iSupply.OutputAudio(reinterpret_cast<const TByte*>(iBuf), bytes);
        remaining -= bytes;
    }
}

bool WavSender::TryParseHeader(uint32_t& aAudioBytes)
{
    // Half-hearted WAV parsing.  Works with many but not all WAV files
    auto size = iFile.tellg();
    iFile.seekg(0, std::ios::end);
    size = iFile.tellg() - size;
    iFile.seekg(0, std::ios::beg);
    static const int32_t kHeaderBytes = 44;
    if (size < kHeaderBytes) { // too small, can't be a WAV
        return false;
    }
    unsigned char header[kHeaderBytes];
    iFile.read(reinterpret_cast<char*>(&header[0]), sizeof header);
    if (header[0] != 'R' || header[1] != 'I' || header[2] != 'F' || header[3] != 'F') {
        return false;
    }
    // ignore bytes [4..7]
    if (header[8] != 'W' || header[9] != 'A' || header[10] != 'V' || header[11] != 'E') {
        return false;
    }
    if (header[12] != 'f' || header[13] != 'm' || header[14] != 't' || header[15] != ' ') {
        return false;
    }
    const TUint subChunk1Size = header[16] | (header[17] << 8) | (header[18] << 16) | (header[19] << 24);
    if (subChunk1Size != 16) {
        return false;
    }
    const TUint audioFormat = header[20] | (header[21] << 8);
    if (audioFormat != 1) {
        return false;
    }
    const TUint numChannels = header[22] | (header[23] << 8);
    const TUint sampleRate = header[24] | (header[25] << 8) | (header[26] << 16) | (header[27] << 24);
    const TUint byteRate = header[28] | (header[29] << 8) | (header[30] << 16) | (header[31] << 24);
    // ignore bytes [32..33]
    const TUint bitDepth = header[34] | (header[35] << 8);
    if (header[36] != 'd' || header[37] != 'a' || header[38] != 't' || header[39] != 'a') {
        return false;
    }
    const uint32_t subChunk2Size = header[40] | (header[41] << 8) | (header[42] << 16) | (header[43] << 24);

    OpenHomeMetadata metadata;
    metadata.push_back(std::pair<std::string, std::string>("uri", iFilename));
    metadata.push_back(std::pair<std::string, std::string>("title", iFilename));
    iSupply.OutputMetadataOh(metadata);
    const TUint64 samplesTotal = static_cast<TUint64>(subChunk2Size) / (numChannels * bitDepth);
    iSupply.OutputFormat(bitDepth, sampleRate, numChannels, byteRate*8,
                         0LL, samplesTotal,
                         true /*seekable*/, true /*lossless*/,
                         false/*live*/, true/*broadcastAllowed*/,
                         "WAV");

    aAudioBytes = subChunk2Size;
    return true;
}