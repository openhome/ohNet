#ifndef HEADER_URI
#define HEADER_URI

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>

EXCEPTION(UriError)

namespace OpenHome {

class IWriter;

class Uri : private INonCopyable
{
public:
    explicit Uri();
    explicit Uri(const Brx& aAbsoluteUri);
    explicit Uri(const Brx& aBaseUri, const Brx& aRelativeUri);
    void Replace(const Brx& aAbsoluteUri);
    void Replace(const Brx& aBaseUri, const Brx& aRelativeUri);
    void Clear();

    const Brx& AbsoluteUri() const { return iAbsoluteUri; }
    const Brx& Scheme() const { return iScheme; }
    const Brx& Host() const { return iHost; }
    TInt Port() const { return iPort; }
    const Brx& Authority() const { return iAuthority; }
    const Brx& Path() const { return iPath; }
    const Brx& Query() const { return iQuery; }
    const Brx& PathAndQuery() const { return iPathAndQuery; }
    const Brx& Fragment() const { return iFragment; }

    static TBool IsUnreserved(TChar aValue);
    static TBool IsExcluded(TChar aValue);

    static void Escape(Bwx& aDst, const Brx& aSrc);
    static void Escape(IWriter& aWriter, const Brx& aSrc);
    static void Unescape(Bwx& aDst, const Brx& aSrc); // supports in-place unescaping

public:
    static const TUint kMaxDirLevels = 50;
    static const TUint kMaxUriBytes = 1024;
    static const TInt kPortNotSpecified = -1;

private:
    void Parse(const Brx& aUri);
    void ValidateScheme();
    void ValidateHost();
    void ValidatePath();
    TUint EscapedBytes(const Brx& aBuffer);
    static TBool IsEscaped(const Brx& aBuffer, TUint aIndex);

    Bws<kMaxUriBytes> iAbsoluteUri;
    Bws<kMaxUriBytes> iBase;     // only used in Replace() but too large for the stack
    Bws<kMaxUriBytes> iRelative; // only used in Replace() but too large for the stack
    Brn iScheme;
    Brn iHost;
    TInt iPort;
    Brn iAuthority;
    Brn iPath;
    Brn iQuery;
    Brn iPathAndQuery;
    Brn iFragment;
};

} // namespace OpenHome

#endif  // HEADER_URI
