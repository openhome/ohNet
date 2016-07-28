#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

EXCEPTION(CredentialsIdNotFound);
EXCEPTION(CredentialsLoginFailed);

namespace OpenHome {
    class Environment;
    class Timer;
    class ThreadFunctor;
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
    virtual void UpdateStatus() = 0;
    virtual void Login(Bwx& aToken) = 0;
    virtual void ReLogin(const Brx& aCurrentToken, Bwx& aNewToken) = 0;
};

class ICredentials
{
public:
    static const TUint kMaxUsernameBytes = 64;
    static const TUint kMaxPasswordBytes = 64;
    static const TUint kMaxPasswordEncryptedBytes = 512;
    static const TUint kMaxStatusBytes = 512;
    static const TUint kMaxDataBytes = 128;
    static const TUint kMaxTokenBytes = 128;
public:
    virtual void Set(const Brx& aId, const Brx& aUsername) = 0;
    virtual void Set(const Brx& aId, const Brx& aUsername, const Brx& aPassword) = 0;
    virtual void Clear(const Brx& aId) = 0;
    virtual void Enable(const Brx& aId, TBool aEnable) = 0;
    virtual void Get(const Brx& aId, Bwx& aUsername, Bwx& aPassword, TBool& aEnabled, Bwx& aStatus, Bwx& aData) = 0;
    virtual void Login(const Brx& aId, Bwx& aToken) = 0;
    virtual void ReLogin(const Brx& aId, const Brx& aCurrentToken, Bwx& aNewToken) = 0;
};

class ICredentialsState
{
public:
    virtual void SetState(const Brx& aId, const Brx& aStatus, const Brx& aData) = 0;
};

class ICredentialObserver
{
public:
    virtual void CredentialChanged() = 0;
};

class ProviderCredentials;
class Credential;

class Credentials : public ICredentials, public ICredentialsState, private ICredentialObserver
{
    static const Brn kKeyRsaPrivate;
    static const Brn kKeyRsaPublic;
    static const TUint kModerationTimeMs = 500;
    static const TUint kNumFifoElements = 10;
public:
    Credentials(Environment& aEnv, Net::DvDevice& aDevice, Configuration::IStoreReadWrite& aStore, const Brx& aEntropy, Configuration::IConfigInitialiser& aConfigInitialiser, TUint aKeyBits = 2048);
    virtual ~Credentials();
    void Add(ICredentialConsumer* aConsumer);
    void Start();
    void GetPublicKey(Bwx& aKey); // test use only
private: // from ICredentials
    void Set(const Brx& aId, const Brx& aUsername) override;
    void Set(const Brx& aId, const Brx& aUsername, const Brx& aPassword) override; // password must be encrypted
    void Clear(const Brx& aId) override;
    void Enable(const Brx& aId, TBool aEnable) override;
    void Get(const Brx& aId, Bwx& aUsername, Bwx& aPassword, TBool& aEnabled, Bwx& aStatus, Bwx& aData) override;
    void Login(const Brx& aId, Bwx& aToken) override;
    void ReLogin(const Brx& aId, const Brx& aCurrentToken, Bwx& aNewToken) override;
public: // from ICredentialsState
    void SetState(const Brx& aId, const Brx& aStatus, const Brx& aData) override;
private: // from ICredentialObserver
    void CredentialChanged() override;
private:
    Credential* Find(const Brx& aId) const;
    void CreateKey(Configuration::IStoreReadWrite& aStore, const Brx& aEntropy, TUint aKeyBits);
    void CurrentAdapterChanged();
    void ModerationTimerCallback();
    void CredentialsThread();
private:
    class KeyParams
    {
    public:
        KeyParams(Configuration::IStoreReadWrite& aStore, const Brx& aEntropy, TUint aKeyBits);
        Configuration::IStoreReadWrite& Store() const;
        const Brx& Entropy() const;
        TUint KeyBits() const;
    private:
        Configuration::IStoreReadWrite& iStore;
        Bwh iEntropy;
        TUint iKeyBits;
    };
private:
    Mutex iLock;
    Environment& iEnv;
    Configuration::IConfigInitialiser& iConfigInitialiser;
    ProviderCredentials* iProvider;
    void* iKey; /* Type is RSA but don't want to include openssl headers.
                   These define lower case macros which can conflict with functions in our code. */
    std::vector<Credential*> iCredentials;
    Timer* iModerationTimer;
    TBool iModerationTimerStarted;
    Bws<2048> iKeyBuf;
    KeyParams iKeyParams;
    ThreadFunctor* iThread;
    Fifo<Credential*> iFifo;
    TUint iAdapterChangeListenerId;
    TBool iStarted;
};

} // namespace Av
} // namespace OpenHome

