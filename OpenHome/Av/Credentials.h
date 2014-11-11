#ifndef HEADER_CREDENTIALS_MANAGER
#define HEADER_CREDENTIALS_MANAGER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>

#include <vector>

EXCEPTION(CredentialsIdNotFound);
EXCEPTION(CredentialsLoginFailed);
EXCEPTION(CredentialsLogoutFailed);

namespace OpenHome {
    class Environment;
    class Timer;
namespace Net {
    class DvDevice;
}
namespace Configuration {
    class IStoreReadWrite;
    class IConfigInitialiser;
}
namespace Av {

class ICredentialConsumer
{
public:
    virtual ~ICredentialConsumer() {}
    virtual const Brx& Id() const = 0;
    virtual void CredentialsChanged(const Brx& aUsername, const Brx& aPassword) = 0; // password is decrypted
    virtual void Login(Bwx& aToken) = 0;
    virtual void Logout(const Brx& aToken) = 0;
};

class ICredentials
{
public:
    static const TUint kMaxUsernameBytes = 64;
    static const TUint kMaxPasswordBytes = 64;
    static const TUint kMaxPasswordEncryptedBytes = 256;
    static const TUint kMaxStatusBytes = 128;
    static const TUint kMaxTokenBytes = 128;
public:
    virtual void Set(const Brx& aId, const Brx& aUsername, const Brx& aPassword) = 0;
    virtual void Clear(const Brx& aId) = 0;
    virtual void Enable(const Brx& aId, TBool aEnable) = 0;
    virtual void Get(const Brx& aId, Bwx& aUsername, Bwx& aPassword, TBool& aEnabled, Bwx& aStatus) = 0;
    virtual void Login(const Brx& aId, Bwx& aToken) = 0;
    virtual void Logout(const Brx& aId, const Brx& aToken) = 0;
};

class ICredentialObserver
{
public:
    virtual void CredentialChanged() = 0;
};

class ProviderCredentials;
class Credential;

class Credentials : public ICredentials, private ICredentialObserver
{
    static const Brn kKeyRsaPrivate;
    static const Brn kKeyRsaPublic;
    static const TUint kModerationTimeMs = 500;
public:
    Credentials(Environment& aEnv, Net::DvDevice& aDevice, Configuration::IStoreReadWrite& aStore, const Brx& aEntropy, Configuration::IConfigInitialiser& aConfigInitialiser, TUint aKeyBits = 2048);
    ~Credentials();
    void Add(ICredentialConsumer* aConsumer);
    void SetStatus(const Brx& aId, const Brx& aState);
    void SetStatusLocked(const Brx& aId, const Brx& aState); // call from CredentialsChanged() only
    void GetPublicKey(Bwx& aKey); // test use only
private: // from ICredentials
    void Set(const Brx& aId, const Brx& aUsername, const Brx& aPassword); // password must be encrypted
    void Clear(const Brx& aId);
    void Enable(const Brx& aId, TBool aEnable);
    void Get(const Brx& aId, Bwx& aUsername, Bwx& aPassword, TBool& aEnabled, Bwx& aStatus);
    void Login(const Brx& aId, Bwx& aToken);
    void Logout(const Brx& aId, const Brx& aToken);
private: // from ICredentialObserver
    void CredentialChanged();
private:
    Credential* Find(const Brx& aId) const;
    void CreateKey(Configuration::IStoreReadWrite& aStore, const Brx& aEntropy, TUint aKeyBits);
    void ModerationTimerCallback();
private:
    Environment& iEnv;
    Configuration::IConfigInitialiser& iConfigInitialiser;
    ProviderCredentials* iProvider;
    void* iKey; /* Type is RSA but don't want to include openssl headers.
                   These define lower case macros which can conflict with functions in our code. */
    std::vector<Credential*> iCredentials;
    Timer* iModerationTimer;
    TBool iModerationTimerStarted;
    Bws<2048> iKeyBuf;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CREDENTIALS_MANAGER
