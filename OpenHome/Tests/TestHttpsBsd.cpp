#include <stdio.h>
#include <stdint.h>
#ifdef _WIN32
#include <ws2tcpip.h>
#include <Winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#define SOCKET int
#endif

#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/engine.h"

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

static long BioCallback(BIO *b, int oper, const char *argp, int argi, long /*argl*/, long retvalue)
{
    if (oper & BIO_CB_RETURN) {
        return retvalue;
    }
    switch (oper)
    {
    case BIO_CB_READ:
    {
        BIO_reset(b);
        SOCKET* socketH = (SOCKET*)BIO_get_callback_arg(b);
        char* data;
        long len = BIO_get_mem_data(b, &data);
        if (argi > len) {
            printf("Wanted %d bytes, bio only has space for %ld\n", argi, len);
            argi = len;
        }
        int remaining = argi;
        while (remaining > 0) {
            int bytes = recv(*socketH, data, remaining, 0);
            if (bytes <= 0) {
                break;
            }
            data += bytes;
            remaining -= bytes;
        }
        retvalue = argi - remaining;
        if (retvalue < argi) {
            printf("Wanted %d bytes, read %ld\n", argi, retvalue);
        }
    }
        break;
    case BIO_CB_WRITE:
    {
        SOCKET* socketH = (SOCKET*)BIO_get_callback_arg(b);
        int remaining = argi;
        const char* p = argp;
        while (remaining > 0) {
            int bytes = send(*socketH, p, remaining, 0);
            if (bytes <= 0) {
                break;
            }
            p += bytes;
            remaining -= bytes;
        }
        retvalue = argi - remaining;
        if (retvalue < argi) {
            printf("Wanted %d bytes, wrote %ld\n", argi, retvalue);
        }
    }
        break;
    default:
        break;
    }
    return retvalue;
}

int main(int argc, char* argv[])
{
    const char* hoststr = (argc>1? argv[1] : "www.ssllabs.com");
    const char* path = (argc>2? argv[2] : "/ssltest/viewMyClient.html");
    const int kPort = 443;
    /*if (argc != 2) {
        printf("usage: TestHttps [host] [path]\n");
        return -1;
    }*/

#ifdef _WIN32
    WSADATA wsaData;
    WORD ver = (2<<8)|2; // WinSock v2.2.  Standard on XP and later
    if (0 != WSAStartup(ver, &wsaData)) {
        return -2;
    }
#endif

    struct addrinfo *results = NULL;
    int ret = 0;
    ret = getaddrinfo(hoststr, "", NULL, &results);
    if (results == NULL) {
        ret = -3;
    }
    uint32_t host = ((struct sockaddr_in*)results[0].ai_addr)->sin_addr.s_addr;
    freeaddrinfo(results);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(kPort);
    addr.sin_addr.s_addr = host;
    SOCKET socketH = socket(AF_INET, SOCK_STREAM, 0);

    if (0 != connect(socketH, (struct sockaddr*)&addr, sizeof(addr))) {
        return -4;
    }

    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);
    SSL* ssl = SSL_new(ctx);
    SSL_set_info_callback(ssl, SslInfoCallback);
    static unsigned char memBuf[16 * 1024] = {0};
    BIO* rbio = BIO_new_mem_buf(memBuf, sizeof(memBuf));
    BIO_set_callback(rbio, BioCallback);
    BIO_set_callback_arg(rbio, (char*)&socketH);
    BIO* wbio = BIO_new(BIO_s_mem());
    BIO_set_callback(wbio, BioCallback);
    BIO_set_callback_arg(wbio, (char*)&socketH);

    SSL_set_bio(ssl, rbio, wbio); // ownership of bios passes to ssl
    SSL_set_connect_state(ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    ret = SSL_connect(ssl);
    if (ret != 1) {
        printf("SSL_connect failed - %d\n", SSL_get_error(ssl, 0));
        goto cleanup;
    }

    {
        char req[512];
        int bytes = sprintf(req, "GET %s HTTP/1.1\r\nHOST: %s\r\nConnection: close\r\n\r\n", path, hoststr);
        printf("req is: %s\n", req);
        int written = SSL_write(ssl, req, bytes);
        if (written != bytes) {
            printf("ERROR: wrote %d from %d bytes\n", written, bytes);
        }
    }
    {
        char resp[1024];
        int bytes;
        for (;;) {
            bytes = SSL_read(ssl, resp, sizeof(resp)-1);
            if (bytes <= 0 ) {
                break;
            }
            resp[bytes] = '\0';
            printf("%s", resp);
        }
    }

    SSL_shutdown(ssl);
cleanup:
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();
    ENGINE_cleanup();
    EVP_cleanup();

#ifdef _WIN32
    (void)closesocket(socketH);
#else
    (void)close(socketH);
#endif
    return 0;
}
