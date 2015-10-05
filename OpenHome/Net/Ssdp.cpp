#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/OsWrapper.h>

using namespace OpenHome;
using namespace OpenHome::Net;

static const Brn kAlive("ssdp:alive");
static const Brn kByeBye("ssdp:byebye");

//static const TUint kMinMaxAge = 1800;
static const TByte kMaxAgeSeparator('=');
static const Brn kMaxAge("max-age");

static const TByte kUuidSeparator(':');
static const Brn kUuid("uuid");

static const Brn kUpnpRoot("upnp:rootdevice");

static const Brn kMsearchDiscover("\"ssdp:discover\"");
static const Brn kMsearchAll("ssdp:all");
static const Brn kMsearchUpnpRoot("upnp:rootdevice");
static const Brn kMsearchUuid("uuid");
static const Brn kMsearchUrn("urn");
static const Brn kMsearchDevice("device");
static const Brn kMsearchService("service");

static const Brn kUsnSeparator("::");
static const Brn kVersionSeparator(":");
static const Brn kSsdpPortSeparator(":");
static const Brn kSsdpUrlSeparator("/");
static const Brn kSsdpHttp("http://");

static const TUint kMaxDomainBytes = 64;

static const TByte kSsdpMaxAgeSeparator('=');
static const Brn kSsdpMaxAge("max-age");

const Brn kSchemasUpnpOrg("schemas-upnp-org");
const Brn kUpnpOrg("upnp.org");

const TByte Ssdp::kUrnSeparator = ':';
const TUint Ssdp::kMulticastPort = 1900;
const Brn Ssdp::kUrn("urn:");
const Brn Ssdp::kMulticastAddress("239.255.255.250");
const Brn Ssdp::kMulticastAddressAndPort("239.255.255.250:1900");
const Brn Ssdp::kMethodNotify("NOTIFY");
const Brn Ssdp::kMethodMsearch("M-SEARCH");
const Brn Ssdp::kMethodUri("*");
const Brn Ssdp::kStatusOk("OK");
const Brn Ssdp::kHeaderHost("HOST");
const Brn Ssdp::kHeaderServer("SERVER");
const Brn Ssdp::kHeaderCacheControl("CACHE-CONTROL");
const Brn Ssdp::kHeaderLocation("LOCATION");
const Brn Ssdp::kHeaderNt("NT");
const Brn Ssdp::kHeaderSt("ST");
const Brn Ssdp::kHeaderUsn("USN");
const Brn Ssdp::kHeaderNts("NTS");
const Brn Ssdp::kHeaderExt("EXT");
const Brn Ssdp::kHeaderMan("MAN");
const Brn Ssdp::kHeaderMx("MX");
const Brn Ssdp::kHeaderBootId("BOOTID.UPNP.ORG");
const Brn Ssdp::kHeaderNextBootId("NEXTBOOTID.UPNP.ORG");
const Brn Ssdp::kHeaderConfigId("CONFIGID.UPNP.ORG");
const Brn Ssdp::kHeaderSearchPort("SEARCHPORT.UPNP.ORG");
const Brn Ssdp::kDeviceSeparator(":device:");
const Brn Ssdp::kServiceSeparator(":service:");

void Ssdp::UpnpDomainToCanonical(const Brx& aUpnpDomain, Bwx& aCanonicalDomain) // was CanonicalDomain
{
    if (aUpnpDomain == kSchemasUpnpOrg) {
        aCanonicalDomain.Replace(kUpnpOrg);
    }
    else {
        aCanonicalDomain.Replace(aUpnpDomain);
        for (TUint i = 0; i < aCanonicalDomain.Bytes(); i++) {
            if (aCanonicalDomain[i] == '-') {
                aCanonicalDomain[i] = '.';
            }
        }
    }
}

void Ssdp::CanonicalDomainToUpnp(const Brx& aCanonicalDomain, Bwx& aUpnpDomain) // was UpnpDomain
{
    if (aCanonicalDomain == kUpnpOrg) {
        aUpnpDomain.Replace(kSchemasUpnpOrg);
    }
    else {
        aUpnpDomain.Replace(aCanonicalDomain);
        for (TUint i = 0; i < aUpnpDomain.Bytes(); i++) {
            if (aUpnpDomain[i] == '.') {
                aUpnpDomain[i] = '-';
            }
        }
    }
}

void Ssdp::WriteRoot(IWriter& aWriter)
{
    aWriter.Write(kUpnpRoot);
}

void Ssdp::WriteUuid(IWriter& aWriter, const Brx& aUuid)
{
    aWriter.Write(kUuid);
    aWriter.Write(kUuidSeparator);
    aWriter.Write(aUuid);
}

void Ssdp::WriteDeviceType(IWriter& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    aWriter.Write(kUrn);
    Bws<kMaxDomainBytes> domain;
    Ssdp::CanonicalDomainToUpnp(aDomain, domain);
    aWriter.Write(domain);
    aWriter.Write(kDeviceSeparator);
    aWriter.Write(aType);
    aWriter.Write(kVersionSeparator);
    Bws<Ascii::kMaxUintStringBytes> version;
    (void)Ascii::AppendDec(version, aVersion);
    aWriter.Write(version);
}

void Ssdp::WriteServiceType(IWriter& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    aWriter.Write(kUrn);
    Bws<kMaxDomainBytes> domain;
    Ssdp::CanonicalDomainToUpnp(aDomain, domain);
    aWriter.Write(domain);
    aWriter.Write(kServiceSeparator);
    aWriter.Write(aType);
    aWriter.Write(kVersionSeparator);
    Bws<Ascii::kMaxUintStringBytes> version;
    (void)Ascii::AppendDec(version, aVersion);
    aWriter.Write(version);
}

void Ssdp::WriteMethodNotify(IWriterHttpMethod& aWriter)
{
    aWriter.WriteMethod(Ssdp::kMethodNotify, Ssdp::kMethodUri, Http::eHttp11);
}

void Ssdp::WriteMethodMsearch(IWriterHttpMethod& aWriter)
{
    aWriter.WriteMethod(Ssdp::kMethodMsearch, Ssdp::kMethodUri, Http::eHttp11);
}

void Ssdp::WriteHost(IWriterHttpHeader& aWriter)
{
    aWriter.WriteHeader(Ssdp::kHeaderHost, Ssdp::kMulticastAddressAndPort);
}

void Ssdp::WriteMan(IWriterHttpHeader& aWriter)
{
    aWriter.WriteHeader(Ssdp::kHeaderMan, kMsearchDiscover);
}

void Ssdp::WriteMx(IWriterHttpHeader& aWriter, TUint aSeconds)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderMx);
    stream.WriteUint(aSeconds);
    stream.WriteFlush();
}

void Ssdp::WriteSearchTypeRoot(IWriterHttpHeader& aWriter)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderSt);
    WriteRoot(stream);
    stream.WriteFlush();
}

void Ssdp::WriteSearchTypeUuid(IWriterHttpHeader& aWriter, const Brx& aUuid)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderSt);
    WriteUuid(stream, aUuid);
    stream.WriteFlush();
}

void Ssdp::WriteSearchTypeDeviceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderSt);
    WriteDeviceType(stream, aDomain, aType, aVersion);
    stream.WriteFlush();
}

void Ssdp::WriteSearchTypeServiceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderSt);
    WriteServiceType(stream, aDomain, aType, aVersion);
    stream.WriteFlush();
}

void Ssdp::WriteSearchTypeAll(IWriterHttpHeader& aWriter)
{
    aWriter.WriteHeader(Ssdp::kHeaderSt, kMsearchAll);
}

void Ssdp::WriteServer(Environment& aEnv, IWriterHttpHeader& aWriter)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderServer);
    TUint major, minor;
    Brn osName = Os::GetPlatformNameAndVersion(aEnv.OsCtx(), major, minor);
    stream.Write(osName);
    stream.Write('/');
    stream.WriteUint(major);
    stream.Write('.');
    stream.WriteUint(minor);
    stream.Write(Brn(" UPnP/1.1 ohNet/"));
    aEnv.GetVersion(major, minor);
    stream.WriteUint(major);
    stream.Write('.');
    stream.WriteUint(minor);
    stream.WriteFlush();
}

void Ssdp::WriteMaxAge(Environment& aEnv, IWriterHttpHeader& aWriter)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderCacheControl);
    stream.Write(kSsdpMaxAge);
    stream.Write(kSsdpMaxAgeSeparator);
    stream.WriteUint(aEnv.InitParams()->DvMaxUpdateTimeSecs());
    stream.WriteFlush();
}

void Ssdp::WriteLocation(IWriterHttpHeader& aWriter, const Brx& aUrl)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderLocation);
    stream.Write(aUrl);
    stream.WriteFlush();
}

void Ssdp::WriteSubTypeAlive(IWriterHttpHeader& aWriter)
{
    aWriter.WriteHeader(Ssdp::kHeaderNts, kAlive);
}

void Ssdp::WriteSubTypeByeBye(IWriterHttpHeader& aWriter)
{
    aWriter.WriteHeader(Ssdp::kHeaderNts, kByeBye);
}

void Ssdp::WriteStatus(IWriterHttpStatus& aWriter)
{
    aWriter.WriteStatus(HttpStatus::kOk, Http::eHttp11);
}

void Ssdp::WriteExt(IWriterHttpHeader& aWriter)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderExt);
    stream.WriteFlush();
}

void Ssdp::WriteNotificationTypeRoot(IWriterHttpHeader& aWriter)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderNt);
    WriteRoot(stream);
    stream.WriteFlush();
}

void Ssdp::WriteNotificationTypeUuid(IWriterHttpHeader& aWriter, const Brx& aUuid)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderNt);
    WriteUuid(stream, aUuid);
    stream.WriteFlush();
}

void Ssdp::WriteNotificationTypeDeviceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderNt);
    WriteDeviceType(stream, aDomain, aType, aVersion);
    stream.WriteFlush();
}

void Ssdp::WriteNotificationTypeServiceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderNt);
    WriteServiceType(stream, aDomain, aType, aVersion);
    stream.WriteFlush();
}

void Ssdp::WriteUsnRoot(IWriterHttpHeader& aWriter, const Brx& aUuid)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderUsn);
    WriteUuid(stream, aUuid);
    stream.Write(kUsnSeparator);
    WriteRoot(stream);
    stream.WriteFlush();
}

void Ssdp::WriteUsnUuid(IWriterHttpHeader& aWriter, const Brx& aUuid)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderUsn);
    WriteUuid(stream, aUuid);
    stream.WriteFlush();
}

void Ssdp::WriteUsnDeviceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderUsn);
    WriteUuid(stream, aUuid);
    stream.Write(kUsnSeparator);
    WriteDeviceType(stream, aDomain, aType, aVersion);
    stream.WriteFlush();
}

void Ssdp::WriteUsnServiceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderUsn);
    WriteUuid(stream, aUuid);
    stream.Write(kUsnSeparator);
    WriteServiceType(stream, aDomain, aType, aVersion);
    stream.WriteFlush();
}

void Ssdp::WriteConfigId(IWriterHttpHeader& aWriter, TUint aConfigId)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderConfigId);
    stream.WriteUint(aConfigId);
    stream.WriteFlush();
}

void Ssdp::WriteSearchPort(IWriterHttpHeader& aWriter, TUint aPort)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderSearchPort);
    stream.WriteUint(aPort);
    stream.WriteFlush();
}

TBool Ssdp::ParseUrnDevice(const Brx& aUrn, Brn& aDomainName, Brn& aDeviceType, TUint& aVer)
{
    return ParseUrn(aUrn, kMsearchDevice, aDomainName, aDeviceType, aVer);
}

TBool Ssdp::ParseUrnService(const Brx& aUrn, Brn& aDomainName, Brn& aDeviceType, TUint& aVer)
{
    return ParseUrn(aUrn, kMsearchService, aDomainName, aDeviceType, aVer);
}

TBool Ssdp::ParseUrn(const Brx& aUrn, const Brx& aType, Brn& aDomainName, Brn& aDeviceType, TUint& aVer)
{
    Parser parser(aUrn);
    aDomainName.Set(parser.NextNoTrim(kUrnSeparator));
    if (!aType.Equals(parser.NextNoTrim(kUrnSeparator))) {
        return false;
    }
    aDeviceType.Set(parser.NextNoTrim(kUrnSeparator));
    Brn ver = parser.Remaining();
    try {
        aVer = Ascii::Uint(ver);
    }
    catch(AsciiError&) {
        return false;
    }
    return true;
}

// SsdpHeaderCacheControl

TUint SsdpHeaderCacheControl::MaxAge() const
{
    return (Received()? iMaxAge : 0);
}

TBool SsdpHeaderCacheControl::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderCacheControl);
}

void SsdpHeaderCacheControl::Process(const Brx& aValue)
{
    iMaxAge = 0;
    Parser parser(aValue);
    Brn maxAge = Ascii::Trim(parser.Next(kMaxAgeSeparator));
    if (maxAge == kMaxAge) {
        try {
            iMaxAge = Ascii::Uint(parser.Remaining());
            SetReceived();
        }
        catch (AsciiError&) {
            THROW (HttpError);
        }

        /*
        Can't really apply this test because there is one important transgressor
        who uses a Max Age of 180 seconds : MediaTomb
        If they fix this problem, then we should reinstate this following check

        if (iMaxAge < kMinMaxAge) {
            THROW (HttpError);
        }
        */
    }
}

// SsdpHeaderServer

TBool SsdpHeaderServer::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderServer);
}

void SsdpHeaderServer::Process(const Brx& /*aValue*/)
{
    SetReceived();
}

// SsdpHeaderSt

ESsdpTarget SsdpHeaderSt::Target() const
{
    return iTarget;
}

const Brx& SsdpHeaderSt::Uuid() const
{
    return iUuid;
}

const Brx& SsdpHeaderSt::Domain() const
{
    return iDomain;
}

const Brx& SsdpHeaderSt::Type() const
{
    return iType;
}

TUint SsdpHeaderSt::Version() const
{
    return iVersion;
}

TBool SsdpHeaderSt::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderSt);
}

void SsdpHeaderSt::Process(const Brx& aValue)
{
    SetReceived();

    if (aValue == kMsearchAll) {
        iTarget = eSsdpAll;
        return;
    }
    if (aValue == kMsearchUpnpRoot) {
        iTarget = eSsdpRoot;
        return;
    }

    Parser parser(aValue);
    Brn type = parser.Next(':');

    if (type == kMsearchUuid) {
        Brn uuid = parser.Remaining();
        if (uuid.Bytes() > kMaxUuidBytes) {
            THROW(HttpError);
        }
        iUuid.Replace(uuid);
        iTarget = eSsdpUuid;
        return;
    }

    if (type == kMsearchUrn) {
        Brn domain = parser.Next(':');
        Brn kind = parser.Next(':');
        Brn urntype = parser.Next(':');
        if (domain.Bytes() > kMaxDomainBytes) {
            THROW(HttpError);
        }

        Ssdp::UpnpDomainToCanonical(domain, iDomain);

        try {
            iVersion = Ascii::Uint(parser.Remaining());
        }
        catch (AsciiError&) {
            THROW(HttpError);
        }

        if (urntype.Bytes() > kMaxTypeBytes) {
            THROW(HttpError);
        }

        iType.Replace(urntype);

        if (kind == kMsearchDevice) {
            iTarget = eSsdpDeviceType;
            return;
        }
        if (kind == kMsearchService) {
            iTarget = eSsdpServiceType;
            return;
        }
    }
    THROW(HttpError);
}

// SsdpHeaderNt

ESsdpTarget SsdpHeaderNt::Target() const
{
    return iTarget;
}

const Brx& SsdpHeaderNt::Uuid() const
{
    return iUuid;
}

const Brx& SsdpHeaderNt::Domain() const
{
    return iDomain;
}

const Brx& SsdpHeaderNt::Type() const
{
    return iType;
}

TUint SsdpHeaderNt::Version() const
{
    return iVersion;
}

TBool SsdpHeaderNt::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderNt);
}

void SsdpHeaderNt::Process(const Brx& aValue)
{
    SetReceived();

    if (aValue == kMsearchAll) {
        iTarget = eSsdpAll;
        return;
    }
    if (aValue == kMsearchUpnpRoot) {
        iTarget = eSsdpRoot;
        return;
    }

    Parser parser(aValue);
    Brn type = parser.Next(':');

    if (type == kMsearchUuid) {
        Brn uuid = parser.Remaining();
        if (uuid.Bytes() > kMaxUuidBytes) {
            THROW(HttpError);
        }
        iUuid.Replace(uuid);
        iTarget = eSsdpUuid;
        return;
    }

    if (type == kMsearchUrn) {
        Brn domain = parser.Next(':');
        Brn kind = parser.Next(':');
        Brn urntype = parser.Next(':');
        if (domain.Bytes() > kMaxDomainBytes) {
            THROW(HttpError);
        }
        Ssdp::UpnpDomainToCanonical(domain, iDomain);
        try {
            iVersion = Ascii::Uint(parser.Remaining());
        }
        catch (AsciiError&) {
            THROW(HttpError);
        }
        if (urntype.Bytes() > kMaxTypeBytes) {
            THROW(HttpError);
        }
        iType.Replace(urntype);
        if (kind == kMsearchDevice) {
            iTarget = eSsdpDeviceType;
            return;
        }
        if (kind == kMsearchService) {
            iTarget = eSsdpServiceType;
            return;
        }
    }
    THROW(HttpError);
}

// SsdpHeaderUsn

ESsdpTarget SsdpHeaderUsn::Target() const
{
    return iTarget;
}

const Brx& SsdpHeaderUsn::Uuid() const
{
    return iUuid;
}

const Brx& SsdpHeaderUsn::Domain() const
{
    return iDomain;
}

const Brx& SsdpHeaderUsn::Type() const
{
    return iType;
}

TUint SsdpHeaderUsn::Version() const
{
    return iVersion;
}

TBool SsdpHeaderUsn::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderUsn);
}

void SsdpHeaderUsn::Process(const Brx& aValue)
{
    SetReceived();

    Parser parser(aValue);
    Brn prefix = parser.Next(':');
    if (prefix != kUuid) {
        THROW(HttpError);
    }

    Brn uuid = parser.Next(':');
    if (uuid.Bytes() > kMaxUuidBytes) {
        THROW(HttpError);
    }

    iUuid.Replace(uuid);
    if (parser.Next(kUuidSeparator).Bytes() != 0) { // double colon separator
        THROW(HttpError);
    }

    Brn value = parser.Remaining();
    if (value.Bytes() == 0) {
        iTarget = eSsdpUuid;
        return;
    }
    if (value == kUpnpRoot) {
        iTarget = eSsdpRoot;
        return;
    }

    Brn type = parser.Next(':');

    if (type == kMsearchUrn) {
        Brn domain = parser.Next(':');
        Brn kind = parser.Next(':');
        Brn urntype = parser.Next(':');
        if (domain.Bytes() > kMaxDomainBytes) {
            THROW(HttpError);
        }
        Ssdp::UpnpDomainToCanonical(domain, iDomain);
        if (urntype.Bytes() > kMaxTypeBytes) {
            THROW(HttpError);
        }
        iType.Replace(urntype);
        try {
            iVersion = Ascii::Uint(parser.Remaining());
        }
        catch (AsciiError&) {
            THROW(HttpError);
        }
        if (kind == kMsearchDevice) {
            iTarget = eSsdpDeviceType;
            return;
        }
        if (kind == kMsearchService) {
            iTarget = eSsdpServiceType;
            return;
        }
    }
    THROW(HttpError);
}

// SsdpHeaderHost

TBool SsdpHeaderHost::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderHost);
}

void SsdpHeaderHost::Process(const Brx& aValue)
{
    if (!Ascii::CaseInsensitiveEquals(aValue, Ssdp::kMulticastAddressAndPort)) {
        if (!Ascii::CaseInsensitiveEquals(aValue, Ssdp::kMulticastAddress)) {
            THROW (HttpError);
        }
    }
    SetReceived();
}

// HeaderMan

TBool SsdpHeaderMan::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderMan);
}

void SsdpHeaderMan::Process(const Brx& aValue)
{
    if (aValue != kMsearchDiscover) {
        THROW (HttpError);
    }
    SetReceived();
}

// SsdpHeaderMx

TUint SsdpHeaderMx::Mx() const
{
    return (Received()? iMx : 0);
}

TBool SsdpHeaderMx::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderMx);
}

void SsdpHeaderMx::Process(const Brx& aValue)
{
    iMx = 0;
    try {
        iMx = Ascii::Uint(aValue);
        SetReceived();
    }
    catch (AsciiError&) {
        THROW (HttpError);
    }
}

// SsdpHeaderNts

TBool SsdpHeaderNts::Alive() const
{
    return iAlive;
}

TBool SsdpHeaderNts::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderNts);
}

void SsdpHeaderNts::Process(const Brx& aValue)
{
    if (aValue == kAlive) {
        SetReceived();
        iAlive = true;
        return;
    }
    if (aValue == kByeBye) {
        SetReceived();
        iAlive = false;
        return;
    }

    THROW(HttpError);
}

// SsdpHeaderExt

TBool SsdpHeaderExt::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Ssdp::kHeaderExt);
}

void SsdpHeaderExt::Process(const Brx& aValue)
{
    if (aValue != Brx::Empty()) {
        THROW (HttpError);
    }
    SetReceived();
}

// SsdpWriterMsearchRequest

SsdpWriterMsearchRequest::SsdpWriterMsearchRequest(IWriter& aWriter)
: iWriter(aWriter)
{
}

void SsdpWriterMsearchRequest::MsearchRoot(TUint aSeconds)
{
    Msearch(aSeconds);
    Ssdp::WriteSearchTypeRoot(iWriter);
    iWriter.WriteFlush();
}

void SsdpWriterMsearchRequest::MsearchUuid(const Brx& aUuid, TUint aSeconds)
{
    Msearch(aSeconds);
    Ssdp::WriteSearchTypeUuid(iWriter, aUuid);
    iWriter.WriteFlush();
}

void SsdpWriterMsearchRequest::MsearchDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, TUint aSeconds)
{
    Msearch(aSeconds);
    Ssdp::WriteSearchTypeDeviceType(iWriter, aDomain, aType, aVersion);
    iWriter.WriteFlush();
}

void SsdpWriterMsearchRequest::MsearchServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, TUint aSeconds)
{
    Msearch(aSeconds);
    Ssdp::WriteSearchTypeServiceType(iWriter, aDomain, aType, aVersion);
    iWriter.WriteFlush();
}

void SsdpWriterMsearchRequest::MsearchAll(TUint aSeconds)
{
    Msearch(aSeconds);
    Ssdp::WriteSearchTypeAll(iWriter);
    iWriter.WriteFlush();
}

void SsdpWriterMsearchRequest::Msearch(TUint aSeconds)
{
    ASSERT(aSeconds >= kMinMsearchSeconds);
    ASSERT(aSeconds <= kMaxMsearchSeconds);

    Ssdp::WriteMethodMsearch(iWriter);
    Ssdp::WriteHost(iWriter);
    Ssdp::WriteMan(iWriter);
    Ssdp::WriteMx(iWriter, aSeconds);
}
