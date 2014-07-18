#ifndef HEADER_OPTION_PARSER
#define HEADER_OPTION_PARSER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>

#include <vector>

EXCEPTION(OptionParserError)

namespace OpenHome {
namespace TestFramework {

class Option
{
public:
    Option(const TChar* aShortName, const TChar* aLongName, const TChar* aHelpDesc);
    virtual ~Option();
    TBool Match(Brn aName) const;
    virtual void Process(const std::vector<Brn>& aArgs) = 0;
    virtual void Reset() = 0;
    virtual TInt ExpectedArgCount() const = 0;
    const TChar* HelpText() const;
protected:
    TChar* iShortName;
    TChar* iLongName;
    TChar* iHelpText;
};

class OptionString : public Option
{
public:
    OptionString(const TChar* aShortName, const TChar* aLongName, const Brx& aDefault, const TChar* aHelpDesc);
    void Process(const std::vector<Brn>& aArgs);
    void Reset();
    TInt ExpectedArgCount() const;
    const Brx& Value() const;
    const TChar* CString() const;
    virtual ~OptionString() {}
private:
    Brhz iValue;
    Brhz iDefault;
};

class OptionInt : public Option
{
public:
    OptionInt(const TChar* aShortName, const TChar* aLongName, TInt aDefault, const TChar* aHelpDesc);
    void Process(const std::vector<Brn>& aArgs);
    void Reset();
    TInt ExpectedArgCount() const;
    TInt Value() const;
    virtual ~OptionInt() {}
private:
    TInt iValue;
    TInt iDefault;
};

class OptionUint : public Option
{
public:
    OptionUint(const TChar* aShortName, const TChar* aLongName, TUint aDefault, const TChar* aHelpDesc);
    void Process(const std::vector<Brn>& aArgs);
    void Reset();
    TInt ExpectedArgCount() const;
    TUint Value() const;
    virtual ~OptionUint() {}
private:
    TUint iValue;
    TUint iDefault;
};

class OptionBool : public Option
{
public:
    OptionBool(const TChar* aShortName, const TChar* aLongName, const TChar* aHelpDesc);
    void Process(const std::vector<Brn>& aArgs);
    void Reset();
    TInt ExpectedArgCount() const;
    TBool Value() const;
    virtual ~OptionBool() {}
private:
    TBool iValue;
};

class OptionParser
{
public:
    OptionParser();
    ~OptionParser();
    void AddOption(Option* aOption);
    TBool Parse(TInt aArgc, TChar* aArgv[]); // false => exception, exit
    TBool Parse(const std::vector<Brn>& aArgs, TBool aIgnoreUnrecognisedOptions = false); // false => exception, exit
    TBool HelpDisplayed();
    void DisplayHelp();
    void SetUsage(const TChar* aUsage);
    static std::vector<Brn> ConvertArgs(TInt aArgc, TChar* aArgv[]);
private:
    Option* Find(Brn aName);
private:
    typedef std::vector<Option*> VectorOption;
    VectorOption iOptions;
    OptionBool iHelpOption;
    TChar* iUsage;
};

} // namespace TestFramework
} // namespace OpenHome

#endif // HEADER_OPTION_PARSER
