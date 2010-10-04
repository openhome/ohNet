#include <OptionParser.h>
#include <Ascii.h>
#include <Exception.h>
#include <TestFramework.h>

#include <string.h>

using namespace Zapp;
using namespace TestFramework;


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
    delete iShortName;
    delete iLongName;
    delete iHelpText;
}

TBool Option::Match(const TChar* aName) const
{
    return (strcmp(aName, iShortName)==0 || strcmp(aName, iLongName)==0);
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

void OptionString::Process(TInt /*aArgc*/, TChar* aArgv[])
{
    iValue.Set(aArgv[0]);
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


// OptionInt

OptionInt::OptionInt(const TChar* aShortName, const TChar* aLongName, TInt aDefault, const TChar* aHelpDesc)
: Option(aShortName, aLongName, aHelpDesc), iDefault(aDefault)
{
}

void OptionInt::Process(TInt /*aArgc*/, TChar* aArgv[])
{
    Bws<Ascii::kMaxIntStringBytes> buf(aArgv[0]);
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

void OptionUint::Process(TInt /*aArgc*/, TChar* aArgv[])
{
    Bws<Ascii::kMaxUintStringBytes> buf(aArgv[0]);
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

void OptionBool::Process(TInt /*aArgc*/, TChar* /*aArgv*/[])
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

TBool OptionBool::IsSet() const
{
    return iValue;
}


// OptionParser

OptionParser::OptionParser()
    : iHelpOption("-h", "--help", "show this help message and exit")
    , iUsage(false)

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
    iPosArgs.clear();
    TUint count = iOptions.size();
    for (TUint i = 0; i<count; i++) {
        iOptions[i]->Reset();
    }

    try {
        TInt i = 0;
        while (i < aArgc) {
            Option* opt = Find(aArgv[i]);
            if (opt == NULL) {
                // this is not an option - positional argument
                if (aArgv[i][0] == '-') {
                    // this is an unspecified option
                    Print("Unrecognised option %s\n", (const char*)aArgv[i]);
                    THROW(OptionParserError);
                }
                iPosArgs.push_back(aArgv[i]);
                i++;
            }
            else {
                TInt numOptArgs = opt->ExpectedArgCount();
                if (numOptArgs+i+1 > aArgc) {
                    Print("Option %s has insufficient arguments\n", (const char*)aArgv[i]);
                    THROW(OptionParserError);
                }
                // check that we won't be passing a high level "-" option to the option processor
                // this'd imply an incorrect argument list
                for (TInt j=0; j<numOptArgs; j++) {
                    if (Find(aArgv[i+1+j]) != NULL) {
                        Print("Option %s has incorrect arguments\n", (const char*)aArgv[i]);
                        THROW(OptionParserError);
                    }
                }
                opt->Process(numOptArgs, &aArgv[i+1]);
                i += 1 + numOptArgs;
            }
        }
    }
    catch (...) {
        iHelpOption.Process(0, NULL);
        DisplayHelp();
        return false;
    }

    // Check if help option has been set
    if (iHelpOption.IsSet()) {
        DisplayHelp();
    }

    return true;
}

TBool OptionParser::HelpDisplayed()
{
    return iHelpOption.IsSet();
}

void OptionParser::DisplayHelp()
{
    if (iUsage == NULL) {
        Print("Usage is: \n");
    }
    else {
        Print("%s\n", iUsage);
    }
    TUint count = iOptions.size();
    for (TUint i = 0; i < count; i++) {
        const TChar* optHelp = iOptions[i]->HelpText();
        Print("  %s\n", optHelp);
    }
}

void OptionParser::SetUsage(const TChar* aUsage)
{
    delete iUsage;
    iUsage = NULL;
    iUsage = new TChar[strlen(iUsage)];
    (void)strcpy(iUsage, aUsage);
}

VectorPosArg& OptionParser::PosArgs()
{
    return iPosArgs;
}

Option* OptionParser::Find(const TChar* aName)
{
    TUint count = iOptions.size();
    for (TUint i = 0; i < count; i++) {
        if (iOptions[i]->Match(aName)) {
            return iOptions[i];
        }
    }
    return NULL;
}
