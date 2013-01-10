#ifndef HEADER_PIPELINE_PROTOCOL_HTTP
#define HEADER_PIPELINE_PROTOCOL_HTTP

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Protocol/Protocol.h>

#include <vector>

namespace OpenHome {
namespace Media {

class HeaderIcyMetadata : public HttpHeader
{
public:
    static void Write(WriterHttpHeader& aWriter);
    TUint Bytes() const;
private: // from HttpHeader
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    TUint iBytes;
};

class ProtocolHttp : public ProtocolNetwork
{
    static const TUint kAudioBytes = 4 * 1024;
    static const TUint kEntityBufferBytes = 2 * 1024;
    static const TUint kEntityLineBytes = 256;
    static const TUint kIcyMetadataBytes = 255 * 16;
    static const TUint kMaxUriBytes = 1024;
public:
	ProtocolHttp(Environment& aEnv, ProtocolManager& aManager);
public: // from Protocol	
    void Stream();
    TBool Restream(TUint64 aOffset);
private:
    void ProcessContentType();
    void ProcessPls(ReaderBuffer& aHeader);
    void ProcessM3u(ReaderBuffer& aHeader);
    void ProcessAsx(ReaderBuffer& aHeader);
    void ProcessXml(ReaderBuffer& aHeader);
    void ProcessAudio();
    void ExtractMetadata();
    Brn EntityReadLine(ReaderBuffer& aHeader);
    Brn EntityReadTag(ReaderBuffer& aHeader);
private:
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    HttpHeaderContentType iHeaderContentType;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderLocation iHeaderLocation;
    HeaderIcyMetadata iHeaderIcyMetadata;
    TUint64 iTotalBytes;
    TBool iSeekable;
    TBool iSnaffling;
    Bws<kIcyMetadataBytes> iIcyMetadata;
    Bws<kEntityLineBytes> iLine;
    Bws<kAudioBytes> iAudio;
    Bws<kMaxUriBytes> iMmsUri;
    Bws<kMaxUriBytes> iXmlUri;
    OpenHome::Uri iAsxUri;
};

class UriEntry
{
public:
	UriEntry(Brn aUri, TUint aEntry);
	Brn Uri() const { return Brn(iUri); }
	TUint Entry() const { return iEntry; }
private:
    static const TUint kMaxUriBytes = 1024;
	Bws<kMaxUriBytes> iUri;
	TUint iEntry;
};

class UriList
{
public:
	UriList();
	~UriList();
	void NextEntry();
	void AddUri(Brn aUri);
	void FindFirst();
	TBool FindNext(Brn& aUri);
private:
	std::vector<UriEntry*> iUriList;
    TUint iMaxUris;
    TUint iMaxUrisEntry;
    TUint iEntry;
    TUint iUriCount;
    TUint iUriIndex;
};

};  // namespace Media
};  // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_HTTP
