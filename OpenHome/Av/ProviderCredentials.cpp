#include <OpenHome/Av/ProviderCredentials.h>
#include <Generated/DvAvOpenhomeOrgCredentials1.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Av/Credentials.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

static const TUint kIdNotFoundCode = 800;
static const Brn kIdNotFoundMsg("Id not found");
static const TUint kLoginFailedCode = 801;
static const Brn kLoginFailedMsg("Login failed");
static const TUint kUsernamePasswordTooLongCode = 802;
static const Brn kUsernamePasswordTooLongMsg("Username or password too long");

ProviderCredentials::ProviderCredentials(DvDevice& aDevice, ICredentials& aCredentials)
    : DvProviderAvOpenhomeOrgCredentials1(aDevice)
    , iCredentialsManager(aCredentials)
{
    EnablePropertyIds();
    EnablePropertyPublicKey();
    EnablePropertySequenceNumber();

    EnableActionSet();
    EnableActionClear();
    EnableActionSetEnabled();
    EnableActionGet();
    EnableActionLogin();
    EnableActionReLogin();
    EnableActionGetIds();
    EnableActionGetPublicKey();
    EnableActionGetSequenceNumber();

    (void)SetPropertyIds(Brx::Empty());
    (void)SetPropertyPublicKey(Brx::Empty());
    (void)SetPropertySequenceNumber(0);
}

void ProviderCredentials::AddId(const Brx& aId)
{
    if (iIds.Bytes() > 0) {
        iIds.Append(' ');
    }
    iIds.Append(aId);
    SetPropertyIds(iIds);
}

void ProviderCredentials::SetPublicKey(const Brx& aKey)
{
    iPublicKey.Replace(aKey);
    SetPropertyPublicKey(iPublicKey);
}

void ProviderCredentials::NotifyCredentialsChanged()
{
    TUint seq;
    GetPropertySequenceNumber(seq);
    seq++;
    SetPropertySequenceNumber(seq);
}

void ProviderCredentials::Set(IDvInvocation& aInvocation, const Brx& aId, const Brx& aUsername, const Brx& aPassword)
{
    try {
        iCredentialsManager.Set(aId, aUsername, aPassword);
    }
    catch (CredentialsIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    catch (CredentialsTooLong&) {
        aInvocation.Error(kUsernamePasswordTooLongCode, kUsernamePasswordTooLongMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderCredentials::Clear(IDvInvocation& aInvocation, const Brx& aId)
{
    try {
        iCredentialsManager.Clear(aId);
    }
    catch (CredentialsIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderCredentials::SetEnabled(IDvInvocation& aInvocation, const Brx& aId, TBool aEnabled)
{
    try {
        iCredentialsManager.Enable(aId, aEnabled);
    }
    catch (CredentialsIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderCredentials::Get(IDvInvocation& aInvocation, const Brx& aId, IDvInvocationResponseString& aUsername, IDvInvocationResponseBinary& aPassword, IDvInvocationResponseBool& aEnabled, IDvInvocationResponseString& aStatus, IDvInvocationResponseString& aData)
{
    try {
        auto& state = iCredentialsManager.State(aId);
        AutoCredentialState _(state);
        aInvocation.StartResponse();
        state.Username(aUsername);
        aUsername.WriteFlush();
        state.Password(aPassword);
        aPassword.WriteFlush();
        aEnabled.Write(state.Enabled());
        state.Status(aStatus);
        aStatus.WriteFlush();
        state.Data(aData);
        aData.WriteFlush();
        aInvocation.EndResponse();
    }
    catch (CredentialsIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
}

void ProviderCredentials::Login(IDvInvocation& aInvocation, const Brx& aId, IDvInvocationResponseString& aToken)
{
    Bws<ICredentials::kMaxTokenBytes> token;
    try {
        iCredentialsManager.Login(aId, token);
    }
    catch (CredentialsIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    catch (CredentialsLoginFailed&) {
        aInvocation.Error(kLoginFailedCode, kLoginFailedMsg);
    }
    aInvocation.StartResponse();
    aToken.Write(token);
    aToken.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderCredentials::ReLogin(IDvInvocation& aInvocation, const Brx& aId, const Brx& aCurrentToken, IDvInvocationResponseString& aNewToken)
{
    Bws<ICredentials::kMaxTokenBytes> token;
    try {
        iCredentialsManager.ReLogin(aId, aCurrentToken, token);
    }
    catch (CredentialsIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    catch (CredentialsLoginFailed&) {
        aInvocation.Error(kLoginFailedCode, kLoginFailedMsg);
    }
    aInvocation.StartResponse();
    aNewToken.Write(token);
    aNewToken.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderCredentials::GetIds(IDvInvocation& aInvocation, IDvInvocationResponseString& aIds)
{
    aInvocation.StartResponse();
    aIds.Write(iIds);
    aIds.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderCredentials::GetPublicKey(IDvInvocation& aInvocation, IDvInvocationResponseString& aPublicKey)
{
    aInvocation.StartResponse();
    aPublicKey.Write(iPublicKey);
    aPublicKey.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderCredentials::GetSequenceNumber(IDvInvocation& aInvocation, IDvInvocationResponseUint& aSequenceNumber)
{
    TUint seq;
    GetPropertySequenceNumber(seq);
    aInvocation.StartResponse();
    aSequenceNumber.Write(seq);
    aInvocation.EndResponse();
}
