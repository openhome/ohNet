#include <OpenHome/Private/sha.h>
#include <cstdlib>

extern "C" {
#include "../thirdparty/sha/sha1.h"
#include "../thirdparty/sha/sha256.h"
}

using namespace OpenHome;

// SHA1

void SHA1::Compute(const Brx& aData, Bwx& aHash)
{
    SHA1_CTX* ctx = (SHA1_CTX*)malloc(sizeof(*ctx));
    sha1_init(ctx);
    sha1_update(ctx, aData.Ptr(), aData.Bytes());
    TByte digest[SHA1_BLOCK_SIZE];
    sha1_final(ctx, digest);
    free(ctx);

    aHash.Replace(digest, SHA1_BLOCK_SIZE);
}


// SHA256

void SHA256::Compute(const Brx& aData, Bwx& aHash)
{
    SHA256_CTX* ctx = (SHA256_CTX*)malloc(sizeof(*ctx));
    sha256_init(ctx);
    sha256_update(ctx, aData.Ptr(), aData.Bytes());
    TByte digest[SHA256_BLOCK_SIZE];
    sha256_final(ctx, digest);
    free(ctx);

    aHash.Replace(digest, SHA256_BLOCK_SIZE);
}
