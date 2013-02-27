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
    static const TUint kAudioBytes = 6 * 1024;
//    static const TUint kEntityBufferBytes = 2 * 1024;
//    static const TUint kEntityLineBytes = 256;
    static const TUint kIcyMetadataBytes = 255 * 16;
    static const TUint kMaxUriBytes = 1024;
public:
	ProtocolHttp(Environment& aEnv);
private: // from Protocol	
    ProtocolStreamResult Stream(const Brx& aUri);
private: // from IStreamHandler
    TBool OkToPlay(TUint aTrackId, TUint aStreamId);
    TBool Seek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    void Stop();
private:
    ProtocolStreamResult DoStream();
    ProtocolStreamResult DoSeek(TUint64 aOffset);
    ProtocolStreamResult DoLiveStream();
    TUint WriteRequest(TUint64 aOffset);
    ProtocolStreamResult ProcessContent();
    void ExtractMetadata();
/*    void ProcessContentType();
    void ProcessPls(ReaderBuffer& aHeader);
    void ProcessM3u(ReaderBuffer& aHeader);
    void ProcessAsx(ReaderBuffer& aHeader);
    void ProcessXml(ReaderBuffer& aHeader);
    Brn EntityReadLine(ReaderBuffer& aHeader);
    Brn EntityReadTag(ReaderBuffer& aHeader);*/
private:
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    HttpHeaderContentType iHeaderContentType;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderLocation iHeaderLocation;
    HeaderIcyMetadata iHeaderIcyMetadata;
    Bws<kIcyMetadataBytes> iIcyMetadata;
    OpenHome::Uri iUri;
//    Bws<kEntityLineBytes> iLine;
//    Bws<kAudioBytes> iAudio;
//    Bws<kMaxUriBytes> iMmsUri;
//    Bws<kMaxUriBytes> iXmlUri;
//    OpenHome::Uri iAsxUri;
    TUint64 iTotalBytes;
    TUint iStreamId;
    TBool iSeekable;
    TBool iSeek;
    TBool iLive;
    TBool iStarted;
    TBool iStopped;
    TUint64 iSeekPos;
    TUint64 iOffset;
    ContentProcessor* iContentProcessor;
};

/*class UriEntry
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
};*/

};  // namespace Media
};  // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_HTTP
