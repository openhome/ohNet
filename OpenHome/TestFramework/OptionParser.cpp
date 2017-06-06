#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/TestFramework.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;


// Option

Option::Option(const TChar* aShortName, const TChar* aLongName, const TChar* aHelpDesc)
{
    iShortName = new TChar[strlen(aShortName) + 1];
    (void)strcpy(iShortName, aShortName);
    iLongName = new TChar[strlen(aLongName) + 1];
    (void)strcpy(iLongName, aLongName);
    iHelpText = new TChar[strlen(aShortName) + strlen(aLongName) + strlen(aHelpDesc) + 5];
    (void)strcpy(iHelpText, aShortName);
    (void)strcat(iHelpText, ", ");
    (void)strcat(iHelpText, aLongName);
    (void)strcat(iHelpText, ", ");
    (void)strcat(iHelpText, aHelpDesc);
}

Option::~Option()
{
    delete[] iShortName;
    delete[] iLongName;
    delete[] iHelpText;
}

TBool Option::Match(Brn aName) const
{
    Brn shortName(iShortName);
    Brn longName(iLongName);
    return (aName == shortName || aName == longName);
}

const TChar* Option::HelpText() const
{
    return iHelpText;
}


// OptionString

OptionString::OptionString(const TChar* aShortName, const TChar* aLongName, const Brx& aDefault, const TChar* aHelpDesc)
: Option(aShortName, aLongName, aHelpDesc), iDefault(aDefault)
{
}

void OptionString::Process(const std::vector<Brn>& aArgs)
{
    iValue.Set(aArgs[0].Ptr(), aArgs[0].Bytes());
}

void OptionString::Reset()
{
    iValue.Set(iDefault);
}

TInt OptionString::ExpectedArgCount() const
{
    return 1;
}

const Brx& OptionString::Value() const
{
    return iValue;
}

const TChar* OptionString::CString() const
{
    return iValue.CString();
}


// OptionInt

OptionInt::OptionInt(const TChar* aShortName, const TChar* aLongName, TInt aDefault, const TChar* aHelpDesc)
: Option(aShortName, aLongName, aHelpDesc), iDefault(aDefault)
{
}

void OptionInt::Process(const std::vector<Brn>& aArgs)
{
    Bws<Ascii::kMaxIntStringBytes> buf(aArgs[0].Ptr(), aArgs[0].Bytes());
    iValue = Ascii::Int(buf);
}

void OptionInt::Reset()
{
    iValue = iDefault;
}

TInt OptionInt::ExpectedArgCount() const
{
    return 1;
}

TInt OptionInt::Value() const
{
    return iValue;
}


// OptionUint

OptionUint::OptionUint(const TChar* aShortName, const TChar* aLongName, TUint aDefault, const TChar* aHelpDesc)
: Option(aShortName, aLongName, aHelpDesc), iDefault(aDefault)
{
}

void OptionUint::Process(const std::vector<Brn>& aArgs)
{
    Bws<Ascii::kMaxUintStringBytes> buf(aArgs[0]);
    iValue = Ascii::Uint(buf);
}

void OptionUint::Reset()
{
    iValue = iDefault;
}

TInt OptionUint::ExpectedArgCount() const
{
    return 1;
}

TUint OptionUint::Value() const
{
    return iValue;
}


// OptionBool

OptionBool::OptionBool(const TChar* aShortName, const TChar* aLongName, const TChar* aHelpDesc)
: Option(aShortName, aLongName, aHelpDesc), iValue(false)
{
}

void OptionBool::Process(const std::vector<Brn>& /*aArgs*/)
{
    iValue = true;
}

void OptionBool::Reset()
{
    iValue = false;
}

TInt OptionBool::ExpectedArgCount() const
{
    return 0;
}

TBool OptionBool::Value() const
{
    return iValue;
}


// OptionParser

OptionParser::OptionParser()
    : iHelpOption("-h", "--help", "show this help message and exit")
    , iUsage(NULL)

{
    AddOption(&iHelpOption);
}

OptionParser::~OptionParser()
{
    delete iUsage;
}

void OptionParser::AddOption(Option* aOption)
{
    iOptions.push_back(aOption);
}

TBool OptionParser::Parse(TInt aArgc, TChar* aArgv[])
{
    std::vector<Brn> args = ConvertArgs(aArgc, aArgv);
    return Parse(args);
}

TBool OptionParser::Parse(const std::vector<Brn>& aArgs, TBool aIgnoreUnrecognisedOptions)
{
    TUint count = (TUint)iOptions.size();
    for (TUint i = 0; i<count; i++) {
        iOptions[i]->Reset();
    }

    try {
        TInt i = 0;
        while (i < (TInt)aArgs.size()) {
            Option* opt = Find(aArgs[i]);
            if (opt == NULL) {
                // this is not an option - positional argument
                if (aArgs[i][0] == '-') {
                    if (!aIgnoreUnrecognisedOptions) {
                        // this is an unspecified option
                        Print("Unrecognised option ");
                        Print(aArgs[i]);
                        Print("\n");
                        THROW(OptionParserError);
                    }
                }
                i++;
            }
            else {
                TInt numOptArgs = opt->ExpectedArgCount();
                if (numOptArgs+i+1 > (TInt)aArgs.size()) {
                    Print("Option ");
                    Print(aArgs[i]);
                    Print(" has insufficient arguments\n");
                    THROW(OptionParserError);
                }
                // check that we won't be passing a high level "-" option to the option processor
                // this'd imply an incorrect argument list
                for (TInt j=0; j<numOptArgs; j++) {
                    if (Find(aArgs[i+1+j]) != NULL) {
                        Print("Option ");
                        Print(aArgs[i]);
                        Print(" has incorrect arguments\n");
                        THROW(OptionParserError);
                    }
                }
                std::vector<Brn> optArgs;
                for (TInt k=0; k<numOptArgs; k++) {
                    optArgs.push_back(aArgs[i+1+k]);
                }
                opt->Process(optArgs);
                i += 1 + numOptArgs;
            }
        }
    }
    catch (...) {
        std::vector<Brn> empty;
        iHelpOption.Process(empty);
        DisplayHelp();
        return false;
    }

    // Check if help option has been set
    if (iHelpOption.Value()) {
        DisplayHelp();
        return (false);
    }

    return true;
}


TBool OptionParser::HelpDisplayed()
{
    return iHelpOption.Value();
}

void OptionParser::DisplayHelp()
{
    if (iUsage == NULL) {
        Print("Usage is: \n");
    }
    else {
        Print("%s\n", iUsage);
    }
    TUint count = (TUint)iOptions.size();
    for (TUint i = 0; i < count; i++) {
        const TChar* optHelp = iOptions[i]->HelpText();
        Print("  %s\n", optHelp);
    }
}

void OptionParser::SetUsage(const TChar* aUsage)
{
    delete iUsage;
    iUsage = NULL;
    iUsage = new TChar[strlen(aUsage)];
    (void)strcpy(iUsage, aUsage);
}

std::vector<Brn> OptionParser::ConvertArgs(TInt aArgc, TChar* aArgv[])
{ // static
    std::vector<Brn> args;
    for (TInt i=0; i<aArgc; i++) {
        args.push_back(Brn(aArgv[i]));
    }
    return args;
}

Option* OptionParser::Find(Brn aName)
{
    TUint count = (TUint)iOptions.size();
    for (TUint i = 0; i < count; i++) {
        if (iOptions[i]->Match(aName)) {
            return iOptions[i];
        }
    }
    return NULL;
}
