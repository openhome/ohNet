#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Thread.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// OpenHome::Net::Parameter

OpenHome::Net::Parameter::Parameter(const TChar* aName, EType aType)
    : iName(aName)
    , iType(aType)
{
}

OpenHome::Net::Parameter::~Parameter()
{
}

const Brx& OpenHome::Net::Parameter::Name() const
{
    return iName;
}

OpenHome::Net::Parameter::EType OpenHome::Net::Parameter::Type() const
{
    return iType;
}

void OpenHome::Net::Parameter::ValidateBool(TBool /*aValue*/) const
{
    ASSERTS();
}

void OpenHome::Net::Parameter::ValidateInt(TInt /*aValue*/) const
{
    ASSERTS();
}

void OpenHome::Net::Parameter::ValidateUint(TUint /*aValue*/) const
{
    ASSERTS();
}

void OpenHome::Net::Parameter::ValidateString(const Brx& /*aValue*/) const
{
    ASSERTS();
}

void OpenHome::Net::Parameter::ValidateBinary(const Brx& /*aValue*/) const
{
    ASSERTS();
}


// ParameterBool

ParameterBool::ParameterBool(const TChar* aName)
    : Parameter(aName, OpenHome::Net::Parameter::eTypeBool)
{
}

ParameterBool::~ParameterBool()
{
}

void ParameterBool::ValidateBool(TBool /*aValue*/) const
{
}


// ParameterInt

ParameterInt::ParameterInt(const TChar* aName, TInt aMinValue, TInt aMaxValue, TInt aStep)
    : Parameter(aName, OpenHome::Net::Parameter::eTypeInt)
    , iMinValue(aMinValue)
    , iMaxValue(aMaxValue)
    , iStep(aStep)
{
    ASSERT(iMinValue <= iMaxValue);
    ASSERT((iMaxValue-iMinValue)%iStep == 0);
}

ParameterInt::~ParameterInt()
{
}

void ParameterInt::ValidateInt(TInt aValue) const
{
    if (aValue < iMinValue || aValue > iMaxValue || (((TUint)(aValue-iMinValue))%iStep != 0)) {
        THROW(ParameterValidationError);
    }
}

TInt ParameterInt::MinValue() const
{
    return iMinValue;
}

TInt ParameterInt::MaxValue() const
{
    return iMaxValue;
}

TInt ParameterInt::Step() const
{
    return iStep;
}


// ParameterUint

ParameterUint::ParameterUint(const TChar* aName, TUint aMinValue, TUint aMaxValue, TUint aStep)
    : Parameter(aName, OpenHome::Net::Parameter::eTypeUint)
    , iMinValue(aMinValue)
    , iMaxValue(aMaxValue)
    , iStep(aStep)
{
    ASSERT(iMinValue <= iMaxValue);
    ASSERT((iMaxValue-iMinValue)%iStep == 0);
}

ParameterUint::~ParameterUint()
{
}

void ParameterUint::ValidateUint(TUint aValue) const
{
    if (aValue < iMinValue || aValue > iMaxValue || ((aValue-iMinValue)%iStep != 0)) {
        THROW(ParameterValidationError);
    }
}

TUint ParameterUint::MinValue() const
{
    return iMinValue;
}

TUint ParameterUint::MaxValue() const
{
    return iMaxValue;
}

TUint ParameterUint::Step() const
{
    return iStep;
}


// ParameterString

ParameterString::ParameterString(const TChar* aName)
    : Parameter(aName, OpenHome::Net::Parameter::eTypeString)
{
}

ParameterString::ParameterString(const TChar* aName, TChar** aAllowedValues, TUint aCount)
    : Parameter(aName, OpenHome::Net::Parameter::eTypeString)
{
    for (TUint i=0; i<aCount; i++) {
        Brh* buf = new Brh(aAllowedValues[i]);
        Brn key(*buf);
        iMap.insert(std::pair<Brn,Brh*>(key, buf));
    }
}

ParameterString::~ParameterString()
{
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        delete it->second;
        it->second = NULL;
        it++;
    }
}

void ParameterString::ValidateString(const Brx& aValue) const
{
    if (iMap.size() == 0) {
        return;
    }
    Brn buf(aValue);
    Map::const_iterator it = iMap.find(buf);
    if (it == iMap.end()) {
        THROW(ParameterValidationError);
    }
}

const ParameterString::Map& ParameterString::AllowedValues() const
{
    return iMap;
}


// ParameterBinary

ParameterBinary::ParameterBinary(const TChar* aName)
    : Parameter(aName, OpenHome::Net::Parameter::eTypeBinary)
{
}

ParameterBinary::~ParameterBinary()
{
}

void ParameterBinary::ValidateBinary(const Brx& /*aValue*/) const
{
}


// ParameterRelated

ParameterRelated::ParameterRelated(const TChar* aName, const Property& aRelated)
    : Parameter(aName, OpenHome::Net::Parameter::eTypeRelated)
    , iRelated(aRelated)
{
    ASSERT(&iRelated != NULL);
}

ParameterRelated::~ParameterRelated()
{
}

const Property& ParameterRelated::Related() const
{
    return iRelated;
}


// Property

const OpenHome::Net::Parameter& Property::Parameter() const
{
    return *iParameter;
}

TUint Property::SequenceNumber() const
{
    return iSequenceNumber;
}

void Property::ResetSequenceNumber()
{
    iSequenceNumber = 0;
}

TBool Property::ReportChanged()
{
    if (iChanged) {
        iFunctor();
        iChanged = false;
        return true;
    }
    return false;
}

Property::Property(OpenHome::Net::Parameter* aParameter, Functor& aFunctor)
    : iLock("PROP")
    , iParameter(aParameter)
    , iFunctor(aFunctor)
    , iChanged(false)
    , iSequenceNumber(0)
{
    ASSERT(iParameter != NULL);
    ASSERT(iParameter->Type() != OpenHome::Net::Parameter::eTypeRelated);
}

Property::Property(OpenHome::Net::Parameter* aParameter)
    : iLock("PROP")
    , iParameter(aParameter)
    , iChanged(false)
    , iSequenceNumber(0)
{
    ASSERT(iParameter != NULL);
    ASSERT(iParameter->Type() != OpenHome::Net::Parameter::eTypeRelated);
}

void Property::Construct(OpenHome::Net::Parameter* aParameter)
{
    iParameter = aParameter;
    iChanged = true;
    iSequenceNumber = 0;
    ASSERT(iParameter != NULL);
    ASSERT(iParameter->Type() != OpenHome::Net::Parameter::eTypeRelated);
}

Property::~Property()
{
    delete iParameter;
}


// PropertyString

PropertyString::PropertyString(const TChar* aName, Functor& aFunctor)
    : Property(new ParameterString(aName), aFunctor)
{
}

PropertyString::PropertyString(OpenHome::Net::Parameter* aParameter)
    : Property(aParameter)
{
}

PropertyString::~PropertyString()
{
}

const Brx& PropertyString::Value() const
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0) {
        THROW(PropertyError);
    }
    return iValue;
}

void PropertyString::Process(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    AutoMutex _(iLock);
    Brhz old;
    iValue.TransferTo(old);
    aProcessor.ProcessString(aBuffer, iValue);
    if (iSequenceNumber == 0 || old != iValue) {
        iChanged = true;
        iSequenceNumber++;
    }
}

TBool PropertyString::SetValue(const Brx& aValue)
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0 || aValue != iValue) {
        iValue.Set(aValue);
        iSequenceNumber++;
        return true;
    }
    return false;
}

void PropertyString::Write(IPropertyWriter& aWriter)
{
    AutoMutex _(iLock);
    aWriter.PropertyWriteString(iParameter->Name(), iValue);
}


// PropertyInt

PropertyInt::PropertyInt(const TChar* aName, Functor& aFunctor)
    : Property(new ParameterInt(aName), aFunctor)
{
}

PropertyInt::PropertyInt(OpenHome::Net::Parameter* aParameter)
    : Property(aParameter)
{
}

PropertyInt::~PropertyInt()
{
}

TInt PropertyInt::Value() const
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0) {
        THROW(PropertyError);
    }
    return iValue;
}

void PropertyInt::Process(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    AutoMutex _(iLock);
    TInt old = iValue;
    aProcessor.ProcessInt(aBuffer, iValue);
    if (iSequenceNumber == 0 || old != iValue) {
        iChanged = true;
        iSequenceNumber++;
    }
}

TBool PropertyInt::SetValue(TInt aValue)
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0 || aValue != iValue) {
        iValue = aValue;
        iSequenceNumber++;
        return true;
    }
    return false;
}

void PropertyInt::Write(IPropertyWriter& aWriter)
{
    AutoMutex _(iLock);
    aWriter.PropertyWriteInt(iParameter->Name(), iValue);
}


// PropertyUint

PropertyUint::PropertyUint(const TChar* aName, Functor& aFunctor)
    : Property(new ParameterUint(aName), aFunctor)
{
}

PropertyUint::PropertyUint(OpenHome::Net::Parameter* aParameter)
    : Property(aParameter)
{
}

PropertyUint::~PropertyUint()
{
}

TUint PropertyUint::Value() const
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0) {
        THROW(PropertyError);
    }
    return iValue;
}

void PropertyUint::Process(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    AutoMutex _(iLock);
    TUint old = iValue;
    aProcessor.ProcessUint(aBuffer, iValue);
    if (iSequenceNumber == 0 || old != iValue) {
        iChanged = true;
        iSequenceNumber++;
    }
}

TBool PropertyUint::SetValue(TUint aValue)
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0 || aValue != iValue) {
        iValue = aValue;
        iSequenceNumber++;
        return true;
    }
    return false;
}

void PropertyUint::Write(IPropertyWriter& aWriter)
{
    AutoMutex _(iLock);
    aWriter.PropertyWriteUint(iParameter->Name(), iValue);
}


// PropertyBool

PropertyBool::PropertyBool(const TChar* aName, Functor& aFunctor)
    : Property(new ParameterBool(aName), aFunctor)
{
}

PropertyBool::PropertyBool(OpenHome::Net::Parameter* aParameter)
    : Property(aParameter)
{
}

PropertyBool::~PropertyBool()
{
}

TBool PropertyBool::Value() const
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0) {
        THROW(PropertyError);
    }
    return iValue;
}

void PropertyBool::Process(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    AutoMutex _(iLock);
    TBool old = iValue;
    aProcessor.ProcessBool(aBuffer, iValue);
    if (iSequenceNumber == 0 || old != iValue) {
        iChanged = true;
        iSequenceNumber++;
    }
}

TBool PropertyBool::SetValue(TBool aValue)
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0 || aValue != iValue) {
        iValue = aValue;
        iSequenceNumber++;
        return true;
    }
    return false;
}

void PropertyBool::Write(IPropertyWriter& aWriter)
{
    AutoMutex _(iLock);
    aWriter.PropertyWriteBool(iParameter->Name(), iValue);
}


// PropertyBinary

PropertyBinary::PropertyBinary(const TChar* aName, Functor& aFunctor)
    : Property(new ParameterBinary(aName), aFunctor)
{
}

PropertyBinary::PropertyBinary(OpenHome::Net::Parameter* aParameter)
    : Property(aParameter)
{
}

PropertyBinary::~PropertyBinary()
{
}

const Brx& PropertyBinary::Value() const
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0) {
        THROW(PropertyError);
    }
    return iValue;
}

void PropertyBinary::Process(IOutputProcessor& aProcessor, const Brx& aBuffer)
{
    AutoMutex _(iLock);
    Bwh old(iValue.Ptr(), iValue.Bytes());
    aProcessor.ProcessBinary(aBuffer, iValue);
    if (iSequenceNumber == 0 || old != iValue) {
        iChanged = true;
        iSequenceNumber++;
    }
}

TBool PropertyBinary::SetValue(const Brx& aValue)
{
    AutoMutex _(iLock);
    if (iSequenceNumber == 0 || aValue != iValue) {
        iValue.Set(aValue);
        iSequenceNumber++;
        return true;
    }
    return false;
}

void PropertyBinary::Write(IPropertyWriter& aWriter)
{
    AutoMutex _(iLock);
    aWriter.PropertyWriteBinary(iParameter->Name(), iValue);
}


// OpenHome::Net::Action

OpenHome::Net::Action::Action(const TChar* aName)
    : iName(aName)
{
}

OpenHome::Net::Action::~Action()
{
    TUint i;
    for (i=0; i<iInputParameters.size(); i++) {
        delete iInputParameters[i];
    }
    for (i=0; i<iOutputParameters.size(); i++) {
        delete iOutputParameters[i];
    }
}

void OpenHome::Net::Action::AddInputParameter(Parameter* aParameter)
{
    iInputParameters.push_back(aParameter);
}

void OpenHome::Net::Action::AddOutputParameter(Parameter* aParameter)
{
    iOutputParameters.push_back(aParameter);
}

const Brx& OpenHome::Net::Action::Name() const
{
    return iName;
}
const Action::VectorParameters& Action::InputParameters() const
{
    return iInputParameters;
}

const Action::VectorParameters& Action::OutputParameters() const
{
    return iOutputParameters;
}


// OpenHome::Net::ServiceType

const Brn OpenHome::Net::ServiceType::kUrn("urn:");
const Brn OpenHome::Net::ServiceType::kService(":service:");
const Brn OpenHome::Net::ServiceType::kServiceId(":serviceId:");

OpenHome::Net::ServiceType::ServiceType(Environment& aEnv, const TChar* aDomain, const TChar* aName, TUint aVersion)
    : iEnv(aEnv)
    , iDomain(aDomain)
    , iName(aName)
    , iVersion(aVersion)
{
}

OpenHome::Net::ServiceType::ServiceType(const ServiceType& aServiceType)
    : iEnv(aServiceType.iEnv)
    , iVersion(aServiceType.iVersion)
    , iFullName(aServiceType.FullName())
{
    iDomain.Set(aServiceType.iDomain);
    iName.Set(aServiceType.iName);
}

OpenHome::Net::ServiceType::~ServiceType()
{
}

const Brx& OpenHome::Net::ServiceType::Domain() const
{
    return iDomain;
}

const Brx& OpenHome::Net::ServiceType::Name() const
{
    return iName;
}

TUint OpenHome::Net::ServiceType::Version() const
{
    return iVersion;
}

const Brx& OpenHome::Net::ServiceType::FullName() const
{
    iEnv.Mutex().Wait();
    if (iFullName.Bytes() == 0) {
        const TInt len = kUrn.Bytes() + iDomain.Bytes() + kService.Bytes() +
                             iName.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1;
        iFullName.Grow(len);
        iFullName.Append(kUrn);
        iFullName.Append(iDomain);
        iFullName.Append(kService);
        iFullName.Append(iName);
        iFullName.Append(':');
        Ascii::AppendDec(iFullName, iVersion);
        iFullName.PtrZ();
    }
    iEnv.Mutex().Signal();
    return iFullName;
}

const Brx& OpenHome::Net::ServiceType::FullNameUpnp() const
{
    iEnv.Mutex().Wait();
    if (iServiceType.Bytes() == 0) {
        Bwh upnpDomain(iDomain.Bytes() + 10);
        Ssdp::CanonicalDomainToUpnp(iDomain, upnpDomain);
        const TInt len = kUrn.Bytes() + upnpDomain.Bytes() + kService.Bytes() +
                            iName.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1;
        iServiceType.Grow(len);
        iServiceType.Append(kUrn);
        iServiceType.Append(upnpDomain);
        iServiceType.Append(kService);
        iServiceType.Append(iName);
        iServiceType.Append(':');
        Ascii::AppendDec(iServiceType, iVersion);
        iServiceType.PtrZ();
    }
    iEnv.Mutex().Signal();
    return iServiceType;
}

const Brx& OpenHome::Net::ServiceType::PathUpnp() const
{
    iEnv.Mutex().Wait();
    if (iPathUpnp.Bytes() == 0) {
        const TInt len = iDomain.Bytes() + 1 + iName.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1;
        iPathUpnp.Grow(len);
        iPathUpnp.Append(iDomain);
        iPathUpnp.Append('-');
        iPathUpnp.Append(iName);
        iPathUpnp.Append('-');
        Ascii::AppendDec(iPathUpnp, iVersion);
        iPathUpnp.PtrZ();
    }
    iEnv.Mutex().Signal();
    return iPathUpnp;
}

const Brx& OpenHome::Net::ServiceType::ServiceId() const
{
    iEnv.Mutex().Wait();
    if (iServiceId.Bytes() == 0) {
        Bwh domain(iDomain);
        for (TUint i=0; i<domain.Bytes(); i++) {
            if (domain[i] == '.') {
                domain[i] = '-';
            }
        }
        const TInt len = kUrn.Bytes() + domain.Bytes() + kServiceId.Bytes() + iName.Bytes() + 1;
        iServiceId.Grow(len);
        iServiceId.Append(kUrn);
        iServiceId.Append(domain);
        iServiceId.Append(kServiceId);
        iServiceId.Append(iName);
        iServiceId.PtrZ();
    }
    iEnv.Mutex().Signal();
    return iServiceId;
}


// Service

Service::Service(Environment& aEnv, const TChar* aDomain, const TChar* aName, TUint aVersion)
    : iServiceType(aEnv, aDomain, aName, aVersion)
{
}

const OpenHome::Net::ServiceType& Service::ServiceType() const
{
    return iServiceType;
}
