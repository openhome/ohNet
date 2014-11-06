#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/SocketSsl.h>
#include <OpenHome/Private/Http.h>

#include <stdlib.h>
#include "openssl/bio.h"
#include "openssl/pem.h"
#include "openssl/rand.h"
#include <algorithm>

namespace OpenHome {

class Environment;

class SuiteSsl : public TestFramework::Suite
{
public:
    SuiteSsl(Environment& aEnv);
    ~SuiteSsl();
private: // from TestFramework::Suite
    void Test();
private:
    void Head(const TChar* aHost, const TChar* aPath);
private:
    static const TUint kWriteBufBytes = 2 * 1024;
    static const TUint kReadBufBytes = 4 * 1024;
    SocketSsl* iSocket;
    Srs<kReadBufBytes>* iReadBuffer;
    ReaderHttpResponse* iReaderResponse;
    Sws<kWriteBufBytes>* iWriteBuffer;
    WriterHttpRequest* iWriterRequest;
};

class SuiteRsa : public TestFramework::Suite
{
public:
    SuiteRsa();
private: // from TestFramework::Suite
    void Test();
};

} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;

// SuiteSsl

SuiteSsl::SuiteSsl(Environment& aEnv)
    : Suite("HTTPS tests")
{
    iSocket = new SocketSsl(aEnv, kReadBufBytes);
    iReadBuffer = new Srs<kReadBufBytes>(*iSocket);
    iReaderResponse = new ReaderHttpResponse(aEnv, *iReadBuffer);
    iWriteBuffer = new Sws<kWriteBufBytes>(*iSocket);
    iWriterRequest = new WriterHttpRequest(*iWriteBuffer);
}

SuiteSsl::~SuiteSsl()
{
    delete iWriterRequest;
    delete iWriteBuffer;
    delete iReaderResponse;
    delete iReadBuffer;
    delete iSocket;
}

void SuiteSsl::Test()
{
    Head("www.ssllabs.com", "/ssltest/viewMyClient.html");
    Head("github.com", "/openhome/ohNetGenerated");
}

void SuiteSsl::Head(const TChar* aHost, const TChar* aPath)
{
    const Brn host(aHost);
    const Brn path(aPath);
    static const TUint kTimeoutMs = 5 * 1000;
    static const TUint kPort = 443;
    Endpoint ep(kPort, host);
    iSocket->Connect(ep, kTimeoutMs);
    iWriterRequest->WriteMethod(Http::kMethodHead, path, Http::eHttp11);
    Http::WriteHeaderHostAndPort(*iWriterRequest, host, kPort);
    Http::WriteHeaderConnectionClose(*iWriterRequest);
    iWriterRequest->WriteFlush();

    iReaderResponse->Read(kTimeoutMs);
    const HttpStatus& status = iReaderResponse->Status();
    TEST(status == HttpStatus::kOk);
    if (status != HttpStatus::kOk) {
        Print("Error from host ");
        Print(aHost);
        Print(" - %u\n", status.Code());
    }
    iSocket->Close();
}


// SuiteRsa

SuiteRsa::SuiteRsa()
    : Suite("RSA tests")
{
}

static void printPemKey(BIO* bio)
{
    int keylen = BIO_pending(bio);
    char* pem_key = (char*)calloc(keylen+1, 1);
    BIO_read(bio, pem_key, keylen);
    Print("\n");
    int remaining = keylen;
    char* ptr = pem_key;
    do {
        int bytes = (remaining<128? remaining : 128);
        Brn buf((const TByte*)ptr, (TUint)bytes);
        Print(buf);
        remaining -= bytes;
        ptr += bytes;
    } while (remaining > 0);
    Print("\n");
    free(pem_key);
}

void SuiteRsa::Test()
{
    // create public/private key pair
    static const char buf[] = "moderate sized string, created to give the illusion of entropy";
    RAND_seed(buf, sizeof(buf));
	BIGNUM *bn = BN_new();
	TEST(BN_set_word(bn, RSA_F4));
    RSA* rsa = RSA_new();
	TEST(RSA_generate_key_ex(rsa, 2048, bn, NULL) != 0);
    BN_free(bn);

    // check they could be written to file
    BIO* bio = BIO_new(BIO_s_mem());
    TEST(1 == PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL));
    printPemKey(bio);
    TEST(1 == PEM_write_bio_RSAPublicKey(bio, rsa));
    printPemKey(bio);
    BIO_free(bio);

    // encrypt then decrypt text
    Brn src("ShortText");
    Bws<256> encrypted;
    int encryptedLen = RSA_public_encrypt(src.Bytes(), src.Ptr(), const_cast<TByte*>(encrypted.Ptr()), rsa, RSA_PKCS1_OAEP_PADDING);
    TEST(encryptedLen == 256);
    encrypted.SetBytes(encryptedLen);
    Bws<16> decrypted;
    const int decryptedLen = RSA_private_decrypt(encrypted.Bytes(), encrypted.Ptr(), const_cast<TByte*>(decrypted.Ptr()), rsa, RSA_PKCS1_OAEP_PADDING);
    TEST((TUint)decryptedLen == src.Bytes());
    decrypted.SetBytes(decryptedLen);
    TEST(src == decrypted);

    RSA_free(rsa);
}



void TestSsl(OpenHome::Environment& aEnv)
{
    Runner runner("SSL tests\n");
    runner.Add(new SuiteSsl(aEnv));
    runner.Add(new SuiteRsa());
    runner.Run();
}
