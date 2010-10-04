#ifndef HEADER_OPTION_PARSER
#define HEADER_OPTION_PARSER

#include <Standard.h>
#include <ZappTypes.h>
#include <Buffer.h>

#include <vector>

EXCEPTION(OptionParserError);

namespace Zapp
{
namespace TestFramework
{

typedef std::vector<TChar*> VectorPosArg;

class Option
{
public:
    Option(const TChar* aShortName, const TChar* aLongName, const TChar* aHelpDesc);
    ~Option();
    TBool Match(const TChar* aName) const;
    virtual void Process(TInt aArgc, TChar* aArgv[]) = 0;
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
    void Process(TInt aArgc, TChar* aArgv[]);
    void Reset();
    TInt ExpectedArgCount() const;
    const Brx& Value() const;
private:
    Brh iValue;
    Brh iDefault;
};

class OptionInt : public Option
{
public:
    OptionInt(const TChar* aShortName, const TChar* aLongName, TInt aDefault, const TChar* aHelpDesc);
    void Process(TInt aArgc, TChar* aArgv[]);
    void Reset();
    TInt ExpectedArgCount() const;
    TInt Value() const;
private:
    TInt iValue;
    TInt iDefault;
};

class OptionUint : public Option
{
public:
    OptionUint(const TChar* aShortName, const TChar* aLongName, TUint aDefault, const TChar* aHelpDesc);
    void Process(TInt aArgc, TChar* aArgv[]);
    void Reset();
    TInt ExpectedArgCount() const;
    TUint Value() const;
private:
    TUint iValue;
    TUint iDefault;
};

class OptionBool : public Option
{
public:
    OptionBool(const TChar* aShortName, const TChar* aLongName, const TChar* aHelpDesc);
    void Process(TInt aArgc, TChar* aArgv[]);
    void Reset();
    TInt ExpectedArgCount() const;
    TBool IsSet() const;
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
    TBool HelpDisplayed();
    void DisplayHelp();
    void SetUsage(const TChar* aUsage);
    VectorPosArg& PosArgs();
private:
    Option* Find(const TChar* aName);
private:
    typedef std::vector<Option*> VectorOption;
    VectorOption iOptions;
    VectorPosArg iPosArgs;
    OptionBool iHelpOption;
    TChar* iUsage;
};


}; // namespace TestFramework
}; // namespace Zapp

#endif // HEADER_OPTION_PARSER
