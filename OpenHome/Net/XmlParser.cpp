#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Net;

Brn XmlParserBasic::Find(const TChar* aTag, const Brx& aDocument)
{
    Brn tag(aTag);
    Brn ignore;
    return XmlParserBasic::Find(tag, aDocument, ignore);
}

Brn XmlParserBasic::Find(const Brx& aTag, const Brx& aDocument)
{
    Brn ignore;
    return XmlParserBasic::Find(aTag, aDocument, ignore);
}

Brn XmlParserBasic::Find(const TChar* aTag, const Brx& aDocument, Brn& aRemaining)
{
    Brn tag(aTag);
    return XmlParserBasic::Find(tag, aDocument, aRemaining);
}

Brn XmlParserBasic::Find(const Brx& aTag, const Brx& aDocument, Brn& aRemaining)
{
    EParserState state = eSearchOpen;
    TInt ignoreClose = 0;
    Brn namesp;
    Brn name;
    Brn attributes;
    Brn ns;
    TUint index;
    Brn doc(Ascii::Trim(aDocument));
    Brn remaining(Ascii::Trim(aDocument));
    Brn retStart;
    ETagType tagType;
    for (;;) {
#ifdef PLATFORM_IOS
        try {
#endif
        NextTag(doc, name, attributes, ns, index, remaining, tagType);
#ifdef PLATFORM_IOS
        }
        catch (XmlError&) {
            throw;
        }
#endif
        if (Ascii::CaseInsensitiveEquals(name, aTag)) {
            if (state == eSearchOpen) {
                if (tagType == eTagClose) {
                    if (--ignoreClose < 0)
                        THROW(XmlError);
                }
                else if (tagType == eTagOpenClose) {
                    return Brn(Brx::Empty());
                }
                namesp.Set(ns);
                retStart.Set(remaining);
                state = eSearchClose;
            }
            else { // eSearchClose
                if (tagType == eTagOpen) {
                    ++ignoreClose;
                }
                else if (tagType == eTagClose) {
                    if (ignoreClose == 0) {
                        if (namesp != ns) {
                            THROW(XmlError);
                        }
                        aRemaining.Set(remaining);
                        const TUint retBytes = (TUint)(doc.Ptr() - retStart.Ptr()) + index;
                        Brn ret(retStart.Ptr(), retBytes);
                        return ret;
                    }
                    ignoreClose--;
                }
            }
        }
        if (remaining.Bytes() == 0) {
            THROW(XmlError);
        }
        doc.Set(remaining);
    }
}

void XmlParserBasic::NextTag(const Brx& aDocument, Brn& aName, Brn& aAttributes, Brn& aNamespace, TUint& aIndex, Brn& aRemaining, ETagType& aType)
{
    aName.Set(Brx::Empty());
    aAttributes.Set(Brx::Empty());
    aNamespace.Set(Brx::Empty());
    aRemaining.Set(Brx::Empty());
    Parser parser(aDocument);
    for (;;) {
        Brn item = parser.Next('>');
        TUint bytes = item.Bytes();
        if (bytes > 0 && item[0] != '<') {
            Parser valueParser(item);
            Brn value = valueParser.Next('<');
            bytes -= value.Bytes();
            item.Set(item.Split(value.Bytes(), bytes));
            item.Set(Ascii::Trim(item));
            bytes = item.Bytes();
        }
        if (bytes < 2 || item[0] != '<') {
            THROW(XmlError);
        }
        aIndex = (TUint)(item.Ptr() - aDocument.Ptr());
        if (item[1] == '?') {
            if (bytes < 3) { // catch special case of <?>
                THROW(XmlError);
            }
            if (item[bytes - 1] == '?') { // processing instruction
                continue;
            }
            THROW(XmlError);
        }
        if (item[1] == '!') {
            if (bytes < 7) { // "<!---->" empty comment tag
                THROW(XmlError);
            }
            continue;
        }

        aRemaining.Set(parser.Remaining());

        TUint start = 1; // skip opening '<'
        TUint len = bytes-1;
        if (item[1] == '/') {
            aType = eTagClose;
            start++;
            len--;
        }
        else if (item[bytes-1] == '/') {
            aType = eTagOpenClose;
            len--;
        }
        else {
            aType = eTagOpen;
        }

        parser.Set(item.Split(start, len));
        aName.Set(parser.NextWhiteSpace());
        aAttributes.Set(parser.Remaining());

        if (Ascii::Contains(aName, ':')) { // collect the namespace
            parser.Set(aName);
            aNamespace.Set(parser.Next(':'));
            if (!aNamespace.Bytes()) {
                THROW(XmlError);
            }
            aName.Set(parser.Remaining());
        }
        else {
            aNamespace.Set(Brx::Empty());
        }

        if (!aName.Bytes()) {
            THROW(XmlError);
        }

        return;
    }
}

Brn XmlParserBasic::FindAttribute(const TChar* aTag, const TChar* aAttribute, const Brx& aDocument)
{
    Brn tag(aTag);
    Brn attribute(aAttribute);
    return (XmlParserBasic::FindAttribute(tag, attribute, aDocument));
}

Brn XmlParserBasic::FindAttribute(const Brx& aTag, const Brx& aAttribute, const Brx& aDocument)
{
    Brn namesp;
    Brn name;
    Brn attributes;
    Brn ns;
    TUint index;
    Brn doc(Ascii::Trim(aDocument));
    Brn remaining(Ascii::Trim(aDocument));
    Brn retStart;
    ETagType tagType;
    for (;;) {
#ifdef PLATFORM_IOS
        try {
#endif
        NextTag(doc, name, attributes, ns, index, remaining, tagType);
#ifdef PLATFORM_IOS
        }
        catch (XmlError&) {
            throw;
        }
#endif
        if (Ascii::CaseInsensitiveEquals(name, aTag)) {
            if (tagType != eTagClose) {
                Parser parser(attributes);
                while (!parser.Finished()) {
                    Brn att = parser.Next('=');
                    Brn ws = parser.Next('\"');
                    Brn value = parser.Next('\"');
                    if (att == aAttribute) {
                        return (value);
                    }
                }
            }
        }
        if (remaining.Bytes() == 0) {
            THROW(XmlError);
        }
        doc.Set(remaining);
    }
}


Brn XmlParserBasic::Element(const TChar* aTag, const Brx& aDocument)
{
    Brn tag(aTag);
    Brn ignore;
    return XmlParserBasic::Element(tag, aDocument, ignore);
}

Brn XmlParserBasic::Element(const TChar* aTag, const Brx& aDocument, Brn& aRemaining)
{
    Brn tag(aTag);
    return XmlParserBasic::Element(tag, aDocument, aRemaining);
}


Brn XmlParserBasic::Element(const Brx& aTag, const Brx& aDocument)
{
    Brn ignore;
    return XmlParserBasic::Element(aTag, aDocument, ignore);
}


Brn XmlParserBasic::Element(const Brx& aTag, const Brx& aDocument, Brn& aRemaining)
{
    EParserState state = eSearchOpen;
    TInt ignoreClose = 0;
    Brn namesp;
    Brn name;
    Brn attributes;
    Brn ns;
    TUint index;
    TUint startIndex = 0;
    Brn docTrimmed(Ascii::Trim(aDocument));
    Brn doc(docTrimmed);
    Brn remaining(docTrimmed);
    Brn retStart;
    ETagType tagType;
    for (;;) {
#ifdef PLATFORM_IOS
        try {
#endif
        NextTag(doc, name, attributes, ns, index, remaining, tagType);
#ifdef PLATFORM_IOS
        }
        catch (XmlError&) {
            throw;
        }
#endif
        if (Ascii::CaseInsensitiveEquals(name, aTag)) {
            if (state == eSearchOpen) {
                if (tagType == eTagClose) {
                    if (--ignoreClose < 0)
                        THROW(XmlError);
                }
                else if (tagType == eTagOpenClose) {
                    return Brn(Brx::Empty());
                }
                namesp.Set(ns);
                retStart.Set(remaining);
                state = eSearchClose;
            }
            else { // eSearchClose
                if (tagType == eTagOpen) {
                    ++ignoreClose;
                }
                else if (tagType == eTagClose) {
                    if (ignoreClose == 0) {
                        if (namesp != ns) {
                            THROW(XmlError);
                        }
                        aRemaining.Set(remaining);

                        const TUint retBytes = (TUint)(aRemaining.Ptr() - docTrimmed.Ptr()) - startIndex;
                        Brn ret(docTrimmed.Split(startIndex, retBytes));
                        return ret;
                    }
                    ignoreClose--;
                }
            }
        }
        if (remaining.Bytes() == 0) {
            THROW(XmlError);
        }
        if (state != eSearchClose)
        {
            startIndex += (TUint)(remaining.Ptr()-doc.Ptr());
        }
        doc.Set(remaining);
    }
}

Brn XmlParserBasic::Next(const Brx& aDocument, Brn& aTag)
{
    Brn ignore;
    return XmlParserBasic::Next(aDocument, aTag, ignore);
}

Brn XmlParserBasic::Next(const Brx& aDocument, Brn& aTag, Brn& aRemaining)
{
    EParserState state = eSearchOpen;
    TInt ignoreClose = 0;
    Brn namesp;
    Brn name;
    Brn tag;
    Brn attributes;
    Brn ns;
    TUint index;
    TUint startIndex = 0;
    TUint endIndex = 0;
    Brn docTrimmed(Ascii::Trim(aDocument));
    Brn doc(docTrimmed);
    Brn remaining(docTrimmed);
    Brn retStart;
    ETagType tagType;

    for (;;) {
        doc.Set(docTrimmed.Ptr() + endIndex, docTrimmed.Bytes() - endIndex);
        startIndex = endIndex;
        while (state == eSearchOpen) {
#ifdef PLATFORM_IOS
            try {
#endif
                NextTag(doc, name, attributes, ns, index, remaining, tagType);
#ifdef PLATFORM_IOS
            }
            catch (XmlError&) {
                throw;
            }
#endif
            if (tagType == eTagOpen) {
                tag.Set(name);
                namesp.Set(ns);
                retStart.Set(remaining);
                state = eSearchClose;
            }
            else {
                startIndex += (TUint)(remaining.Ptr() - doc.Ptr());
            }
            endIndex += (TUint)(remaining.Ptr() - doc.Ptr());
            doc.Set(remaining);
        }
        while (state == eSearchClose) {
            try {
                NextTag(doc, name, attributes, ns, index, remaining, tagType);
                if (Ascii::CaseInsensitiveEquals(name, tag)) {
                    if (tagType == eTagOpen) {
                        ++ignoreClose;
                    }
                    else if (tagType == eTagClose) {
                        if (ignoreClose == 0) {
                            if (namesp != ns) {
                                THROW(XmlError);
                            }
                            aTag.Set(name);
                            aRemaining.Set(remaining);
                            const TUint retBytes = (TUint)(aRemaining.Ptr() - docTrimmed.Ptr()) - startIndex;
                            Brn ret(docTrimmed.Split(startIndex, retBytes));
                            return ret;
                        }
                        ignoreClose--;
                    }
                }
                if (remaining.Bytes() == 0) {
                    THROW(XmlError);
                }
                doc.Set(remaining);
            }
            catch (XmlError&) {
                state = eSearchOpen;
                continue;
            }
        }
    }
}


