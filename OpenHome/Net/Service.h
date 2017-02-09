/**
 * Service classes which are common to Control Point and Device stacks
 *
 * This module is independent of the protocol being used.
 */

#ifndef HEADER_SERVICE
#define HEADER_SERVICE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Ascii.h>

#include <cstdint>
#include <vector>
#include <map>

EXCEPTION(ParameterValidationError)
EXCEPTION(PropertyError)

namespace OpenHome {

class Environment;
    
namespace Net {


/**
 * Parameter.  Each action has 0..n of these
 */
class Parameter
{
    friend class Property;
public:
    enum EType
    {
        eTypeBool
       ,eTypeInt
       ,eTypeUint
       ,eTypeString
       ,eTypeBinary
       ,eTypeRelated
    };
public:
    virtual ~Parameter();
    const Brx& Name() const;
    EType Type() const;
    virtual void ValidateBool(TBool aValue) const;
    virtual void ValidateInt(TInt aValue) const;
    virtual void ValidateUint(TUint aValue) const;
    virtual void ValidateString(const Brx& aValue) const;
    virtual void ValidateBinary(const Brx& aValue) const;
protected:
    Parameter(const TChar* aName, EType aType);
private:
    Brhz iName;
    EType iType;
};

/**
 * Bool parameter.  No validation is performed on TBool values; other types are not allowed
 */
class ParameterBool : public Parameter
{
public:
    DllExport ParameterBool(const TChar* aName);
    DllExport ~ParameterBool();
    void ValidateBool(TBool aValue) const;
};

/**
 * Int parameter.  Checked to ensure a value is inside the range [aMinValue..aMaxValue]
 * and is an exact multiple of aStep from aMinValue and aMaxValue
 */
class ParameterInt : public Parameter
{
public:
    enum {
        kValueMin = INT32_MIN
       ,kValueMax = INT32_MAX
       ,kStep     = 1
    };
public:
    DllExport ParameterInt(const TChar* aName, TInt aMinValue=kValueMin, TInt aMaxValue=kValueMax, TInt aStep=kStep);
    DllExport ~ParameterInt();
    void ValidateInt(TInt aValue) const;
    TInt MinValue() const;
    TInt MaxValue() const;
    TInt Step() const;
private:
    TInt iMinValue;
    TInt iMaxValue;
    TInt iStep;
};

/**
 * Uint parameter.  Checked to ensure a value is inside the range [aMinValue..aMaxValue]
 * and is an exact multiple of aStep from aMinValue and aMaxValue
 */
class ParameterUint : public Parameter
{
public:
    enum {
        kValueMin = 0
       ,kValueMax = UINT32_MAX
       ,kStep     = 1
    };
public:
    DllExport ParameterUint(const TChar* aName, TUint aMinValue=kValueMin, TUint aMaxValue=kValueMax, TUint aStep=kStep);
    DllExport ~ParameterUint();
    void ValidateUint(TUint aValue) const;
    TUint MinValue() const;
    TUint MaxValue() const;
    TUint Step() const;
private:
    TUint iMinValue;
    TUint iMaxValue;
    TUint iStep;
};

/**
 * String parameter.  Checked to ensure a value is one of a list of allowed strings.
 * Any string is treated as valid if the 'allowed' list is empty
 */
class ParameterString : public Parameter
{
public:
    DllExport ParameterString(const TChar* aName);
    DllExport ParameterString(const TChar* aName, TChar** aAllowedValues, TUint aCount);
    DllExport ~ParameterString();
    void ValidateString(const Brx& aValue) const;
    typedef std::map<Brn,Brh*,BufferCmp> Map;
    const Map& AllowedValues() const;
private:
    Map iMap;
};

/**
 * Binary parameter.  No validation is performed on binary values; other types are not allowed
 */
class ParameterBinary : public Parameter
{
public:
    DllExport ParameterBinary(const TChar* aName);
    DllExport ~ParameterBinary();
    void ValidateBinary(const Brx& aValue) const;
};

class Property;
class ParameterRelated : public Parameter
{
public:
    DllExport ParameterRelated(const TChar* aName, const OpenHome::Net::Property& aRelated);
    DllExport ~ParameterRelated();
    const OpenHome::Net::Property& Related() const;
private:
    const OpenHome::Net::Property& iRelated;
};

/**
 * Used by a device to convert output arguments from the form used by the protocol
 */
class IOutputProcessor
{
public:
    virtual void ProcessString(const Brx& aBuffer, Brhz& aVal) = 0;
    virtual void ProcessInt(const Brx& aBuffer, TInt& aVal) = 0;
    virtual void ProcessUint(const Brx& aBuffer, TUint& aVal) = 0;
    virtual void ProcessBool(const Brx& aBuffer, TBool& aVal) = 0;
    virtual void ProcessBinary(const Brx& aBuffer, Brh& aVal) = 0;
};

/**
 * Used by device stack to output property name/value
 */
class IPropertyWriter
{
public:
    virtual void PropertyWriteString(const Brx& aName, const Brx& aValue) = 0;
    virtual void PropertyWriteInt(const Brx& aName, TInt aValue) = 0;
    virtual void PropertyWriteUint(const Brx& aName, TUint aValue) = 0;
    virtual void PropertyWriteBool(const Brx& aName, TBool aValue) = 0;
    virtual void PropertyWriteBinary(const Brx& aName, const Brx& aValue) = 0;
    virtual void PropertyWriteEnd() = 0;
    virtual ~IPropertyWriter() {}
};

/**
 * (Service) Property
 *
 * One Property will be created per Property (state variable) for the Service
 */
class Property
{
public:
    virtual ~Property();
    const OpenHome::Net::Parameter& Parameter() const;
    TUint SequenceNumber() const;
    void ResetSequenceNumber();
    TBool ReportChanged();
    virtual void Process(IOutputProcessor& aProcessor, const Brx& aBuffer) = 0;
    virtual void Write(IPropertyWriter& aWriter) = 0;
protected:
    Property(OpenHome::Net::Parameter* aParameter, Functor& aFunctor);
    Property(OpenHome::Net::Parameter* aParameter);
    void operator=(const Property &);
private:
    void Construct(OpenHome::Net::Parameter* aParameter);
protected:
    mutable Mutex iLock;
    OpenHome::Net::Parameter* iParameter;
    Functor iFunctor;
    TBool iChanged;
    TUint iSequenceNumber;
};

/**
 * String property.  Output buffers will be nul terminated.
 */
class PropertyString : public Property
{
public:
    DllExport PropertyString(const TChar* aName, Functor& aFunctor);
    DllExport PropertyString(OpenHome::Net::Parameter* aParameter);
    DllExport ~PropertyString();
    DllExport const Brx& Value() const; // !!!! threadsafe?
    void Process(IOutputProcessor& aProcessor, const Brx& aBuffer);
    TBool SetValue(const Brx& aValue);
    void Write(IPropertyWriter& aWriter);
private:
    Brhz iValue;
};

/**
 * Integer property
 */
class PropertyInt : public Property
{
public:
    DllExport PropertyInt(const TChar* aName, Functor& aFunctor);
    DllExport PropertyInt(OpenHome::Net::Parameter* aParameter);
    DllExport ~PropertyInt();
    DllExport TInt Value() const;
    void Process(IOutputProcessor& aProcessor, const Brx& aBuffer);
    TBool SetValue(TInt aValue);
    void Write(IPropertyWriter& aWriter);
private:
    TInt iValue;
};

/**
 * Unsigned integer property
 */
class PropertyUint : public Property
{
public:
    DllExport PropertyUint(const TChar* aName, Functor& aFunctor);
    DllExport PropertyUint(OpenHome::Net::Parameter* aParameter);
    DllExport ~PropertyUint();
    DllExport TUint Value() const;
    void Process(IOutputProcessor& aProcessor, const Brx& aBuffer);
    TBool SetValue(TUint aValue);
    void Write(IPropertyWriter& aWriter);
private:
    TUint iValue;
};

/**
 * Boolean property
 */
class PropertyBool : public Property
{
public:
    DllExport PropertyBool(const TChar* aName, Functor& aFunctor);
    DllExport PropertyBool(OpenHome::Net::Parameter* aParameter);
    DllExport ~PropertyBool();
    DllExport TBool Value() const;
    void Process(IOutputProcessor& aProcessor, const Brx& aBuffer);
    TBool SetValue(TBool aValue);
    void Write(IPropertyWriter& aWriter);
private:
    TBool iValue;
};

/**
 * Binary argument.  Similar to ArgumentString but output will not be nul terminated
 */
class PropertyBinary : public Property
{
public:
    DllExport PropertyBinary(const TChar* aName, Functor& aFunctor);
    DllExport PropertyBinary(OpenHome::Net::Parameter* aParameter);
    DllExport ~PropertyBinary();
    DllExport const Brx& Value() const;
    void Process(IOutputProcessor& aProcessor, const Brx& aBuffer);
    TBool SetValue(const Brx& aValue);
    void Write(IPropertyWriter& aWriter);
private:
    Brh iValue;
};

/**
 * Action.
 *
 * Each service has 0..n of these.  Each action has 0..n input parameters and
 * 0..m output parameters.  Each parameter must be either input or output.
 */
class Action
{
public:
    DllExport Action(const TChar* aName);
    DllExport ~Action();

    /**
     * Add an input parameter, passing ownership of aParameter
     */
    DllExport void AddInputParameter(Parameter* aParameter);

    /**
     * Add an output parameter, passing ownership of aParameter
     */
    DllExport void AddOutputParameter(Parameter* aParameter);

    DllExport const Brx& Name() const;

    typedef std::vector<Parameter*> VectorParameters;
    /**
     * Return a vector of the input parameters for this action
     */
    DllExport const VectorParameters& InputParameters() const;
    /**
     * Return a vector of the output parameters for this action
     */
    DllExport const VectorParameters& OutputParameters() const;
private:
    Brhz iName;
    VectorParameters iInputParameters;
    VectorParameters iOutputParameters;
};

/**
 * Name for a service
 */
class ServiceType
{
public:
    ServiceType(Environment& aStack, const TChar* aDomain, const TChar* aName, TUint aVersion);
    ServiceType(const ServiceType& aServiceType);
    ~ServiceType();
    const Brx& Domain() const;
    const Brx& Name() const;
    TUint Version() const;
    const Brx& VersionBuf() const; // nul terminated
    const Brx& FullName() const;
    const Brx& FullNameUpnp() const; // serviceType tag from device xml
    const Brx& PathUpnp() const; // paths within device xml
    const Brx& ServiceId() const; // serviceId tag from device xml
private:
    void operator=(const ServiceType &);
    static const Brn kUrn;
    static const Brn kService;
    static const Brn kServiceId;
private:
    Environment& iEnv;
    Brh iDomain;
    Brh iName;
    TUint iVersion;
    mutable Bws<Ascii::kMaxUintStringBytes+1> iVersionBuf;
    mutable Bwh iFullName;
    mutable Bwh iServiceType;
    mutable Bwh iPathUpnp;
    mutable Bwh iServiceId;
};

/**
 * Service.  Specific to a single device.
 *
 * A service does not claim a reference to a device.  It is assumed that the owner
 * of the service will also own a device reference and will ensure that the service
 * is destroyed before the device reference is released.
 */
class Service
{
public:
    /**
     * Return a reference to the service's name
     */
    const OpenHome::Net::ServiceType& ServiceType() const;
protected:
    Service(Environment& aStack, const TChar* aDomain, const TChar* aName, TUint aVersion);
    virtual ~Service() {}
protected:
    OpenHome::Net::ServiceType iServiceType;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SERVICE
