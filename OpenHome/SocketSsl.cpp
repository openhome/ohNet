#include <OpenHome/SocketSsl.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Printer.h>

#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/engine.h"

#include <stdio.h> // FIXME - for printf - needs to be removed
#include <stdlib.h>

namespace OpenHome {

class SslContext
{
public:
    static SSL_CTX* Get(Environment& aEnv);
    static void RemoveRef(Environment& aEnv);
private:
    static TUint iRefCount;
    static SSL_CTX* iCtx;
};

class SocketSslImpl : public IWriter, public IReaderSource
{
    static const TUint kMinReadBytes = 8 * 1024;
public:
    SocketSslImpl(Environment& aEnv, TUint aReadBytes);
    ~SocketSslImpl();
    void Connect(const Endpoint& aEndpoint, TUint aTimeoutMs);
    void Close();
    void LogVerbose(TBool aVerbose);
public: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
public: // from IReaderSource
    void Read(Bwx& aBuffer);
    void ReadFlush();
    void ReadInterrupt();
private:
    static long BioCallback(BIO *b, int oper, const char *argp, int argi, long argl, long retvalue);
private:
    Environment& iEnv;
    SocketTcpClient iSocketTcp;
    SSL* iSsl;
    TBool iConnected;
    TBool iVerbose;
};

} // namespace OpenHome


using namespace OpenHome;


// SslContext

TUint SslContext::iRefCount = 0;
SSL_CTX* SslContext::iCtx = NULL;

SSL_CTX* SslContext::Get(Environment& aEnv)
{ // static
    AutoMutex a(aEnv.Mutex());
    if (iRefCount++ == 0) {
        SSL_library_init();
        SSL_load_error_strings();
        ERR_load_BIO_strings();
        OpenSSL_add_all_algorithms();
        iCtx = SSL_CTX_new(SSLv23_client_method());
        SSL_CTX_set_verify(iCtx, SSL_VERIFY_NONE, NULL);
    }
    return iCtx;
}

void SslContext::RemoveRef(Environment& aEnv)
{ // static
    AutoMutex a(aEnv.Mutex());
    if (--iRefCount == 0) {
        SSL_CTX_free(iCtx);
        iCtx = NULL;
        ERR_free_strings();
        ENGINE_cleanup();
        EVP_cleanup();
    }
}


// SocketSsl

SocketSsl::SocketSsl(Environment& aEnv, TUint aReadBytes)
{
    iImpl = new SocketSslImpl(aEnv, aReadBytes);
}

SocketSsl::~SocketSsl()
{
    delete iImpl;
}

void SocketSsl::Connect(const Endpoint& aEndpoint, TUint aTimeoutMs)
{
    iImpl->Connect(aEndpoint, aTimeoutMs);
}

void SocketSsl::Close()
{
    iImpl->Close();
}

void SocketSsl::LogVerbose(TBool aVerbose)
{
    iImpl->LogVerbose(aVerbose);
}

void SocketSsl::Write(TByte aValue)
{
    iImpl->Write(aValue);
}

void SocketSsl::Write(const Brx& aBuffer)
{
    iImpl->Write(aBuffer);
}

void SocketSsl::WriteFlush()
{
    iImpl->WriteFlush();
}

void SocketSsl::Read(Bwx& aBuffer)
{
    iImpl->Read(aBuffer);
}

void SocketSsl::ReadFlush()
{
    iImpl->ReadFlush();
}

void SocketSsl::ReadInterrupt()
{
    iImpl->ReadInterrupt();
}


// SocketSslImpl

#define SSL_WHERE_INFO(ssl, flag, logIfSet, msg) {                     \
    if(flag & logIfSet) {                                              \
      printf("%20.20s - %30.30s  - %5.10s\n",                          \
              msg, SSL_state_string_long(ssl), SSL_state_string(ssl)); \
    }                                                                  \
  } 

static void SslInfoCallback(const SSL* ssl, int flag, int ret)
{
    if(ret == 0) {
        printf("-- SslInfoCallback: error occured.\n");
    }
    SSL_WHERE_INFO(ssl, flag, SSL_CB_LOOP, "LOOP");
    SSL_WHERE_INFO(ssl, flag, SSL_CB_HANDSHAKE_START, "HANDSHAKE START");
    SSL_WHERE_INFO(ssl, flag, SSL_CB_HANDSHAKE_DONE, "HANDSHAKE DONE");
}

SocketSslImpl::SocketSslImpl(Environment& aEnv, TUint aReadBytes)
    : iEnv(aEnv)
    , iConnected(false)
    , iVerbose(false)
{
    iSocketTcp.Open(aEnv);
    iSsl = SSL_new(SslContext::Get(aEnv));
    SSL_set_info_callback(iSsl, SslInfoCallback);
    const TUint memBufSize = (kMinReadBytes<aReadBytes? aReadBytes : kMinReadBytes);
    void* buf = malloc((int)memBufSize);
    BIO* rbio = BIO_new_mem_buf(buf, memBufSize);
    BIO_set_callback(rbio, BioCallback);
    BIO_set_callback_arg(rbio, (char*)this);
    BIO* wbio = BIO_new(BIO_s_mem());
    BIO_set_callback(wbio, BioCallback);
    BIO_set_callback_arg(wbio, (char*)this);

    SSL_set_bio(iSsl, rbio, wbio); // ownership of bios passes to iSsl
    SSL_set_connect_state(iSsl);
    SSL_set_mode(iSsl, SSL_MODE_AUTO_RETRY);
}

SocketSslImpl::~SocketSslImpl()
{
    Close();
    SSL_free(iSsl);
    SslContext::RemoveRef(iEnv);
}

void SocketSslImpl::Connect(const Endpoint& aEndpoint, TUint aTimeoutMs)
{
    iSocketTcp.Connect(aEndpoint, aTimeoutMs);
    if (1 != SSL_connect(iSsl)) {
        iSocketTcp.Close();
        THROW(NetworkError);
    }
    iConnected = true;
}

void SocketSslImpl::Close()
{
    if (iConnected) {
        (void)SSL_shutdown(iSsl);
        iSocketTcp.Close();
        iConnected = false;
    }
}

void SocketSslImpl::LogVerbose(TBool aVerbose)
{
    iVerbose = aVerbose;
}

void SocketSslImpl::Write(TByte aValue)
{
    Brn buf(&aValue, 1);
    Write(buf);
}

void SocketSslImpl::Write(const Brx& aBuffer)
{
    const int bytes = (int)aBuffer.Bytes();
    if (iVerbose) {
        Log::Print("SocketSsl writing\n");
        Log::Print(aBuffer);
        Log::Print("\n");
    }
    if (bytes != SSL_write(iSsl, aBuffer.Ptr(), bytes)) {
        THROW(WriterError);
    }
}

void SocketSslImpl::WriteFlush()
{
    iSocketTcp.WriteFlush();
}

void SocketSslImpl::Read(Bwx& aBuffer)
{
    int bytes = SSL_read(iSsl, ((void*)(aBuffer.Ptr() + aBuffer.Bytes())), aBuffer.MaxBytes() - aBuffer.Bytes());
    if (bytes <= 0) {
        printf("SSL_read returned %d\n", bytes);
        int err = SSL_get_error(iSsl, bytes);
        printf("SSL_get_error()=%d\n", err);
        if (err == SSL_ERROR_SSL) {
            printf("ERR_get_error()=%ld\n", ERR_get_error());
        }
        const char* file = NULL;
        int line = 0;
        printf("ERR_get_error_line() returned %ld\n", ERR_get_error_line(&file, &line));
        printf("file=%s, line=%d\n", file, line);
        THROW(ReaderError);
    }
    aBuffer.SetBytes(aBuffer.Bytes() + bytes);
    if (iVerbose) {
        Log::Print("SocketSsl reading\n");
        Log::Print(aBuffer);
        Log::Print("\n");
    }
}

void SocketSslImpl::ReadFlush()
{
    iSocketTcp.ReadFlush();
}

void SocketSslImpl::ReadInterrupt()
{
    iSocketTcp.ReadInterrupt();
}

long SocketSslImpl::BioCallback(BIO *b, int oper, const char *argp, int argi, long /*argl*/, long retvalue)
{ // static
    //printf("BioCallback: oper=%x\n", oper);
    switch (oper)
    {
    case BIO_CB_READ:
    {
        (void)BIO_reset(b);
        SocketSslImpl* self = reinterpret_cast<SocketSslImpl*>(BIO_get_callback_arg(b));
        char* data;
        long len = BIO_get_mem_data(b, &data);
        if (argi > len) {
            printf("SSL: Wanted %d bytes, bio only has space for %d\n", argi, (int)len);
            argi = len;
        }
        int remaining = argi;
        try {
            while (remaining > 0) {
                Bwn buf(data, remaining);
                self->iSocketTcp.Read(buf);
                if (buf.Bytes() == 0) {
                    break;
                }
                data += buf.Bytes();
                remaining -= buf.Bytes();
            }
        }
        catch (ReaderError&) {
        }
        retvalue = argi - remaining;
        if (retvalue < argi) {
            printf("SSL: Wanted %d bytes, read %d\n", argi, (int)retvalue);
        }
    }
        break;
    case BIO_CB_WRITE:
    {
        SocketSslImpl* self = reinterpret_cast<SocketSslImpl*>(BIO_get_callback_arg(b));
        Brn buf(reinterpret_cast<const TByte*>(argp), (TUint)argi);
        try {
            self->iSocketTcp.Write(buf);
            retvalue = buf.Bytes();
        }
        catch (WriterError&) {
            retvalue = -1;
        }
        if (retvalue < argi) {
            printf("SSL: Wanted %d bytes, wrote %d\n", argi, (int)retvalue);
        }
    }
        break;
    default:
        break;
    }
    return retvalue;
}
