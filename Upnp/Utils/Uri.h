#ifndef HEADER_LINN_ASCII_URI
#define HEADER_LINN_ASCII_URI

#include <Standard.h>
#include <ZappTypes.h>
#include <Buffer.h>

EXCEPTION(UriError);

namespace Zapp
{

class Uri
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

    static void Unescape(Bwx& aDst, const Brx& aSrc);
    
public:
    static const TUint kMaxDirLevels = 50;
    static const TUint kMaxUriBytes = 1024;

private:
    void Parse(const Brx& aUri);
    void ValidateScheme();
    void ValidateHost();
    void ValidatePath();
    TUint EscapedBytes(const Brx& aBuffer);
    void Escape(Bwx& aDst, const Brx& aSrc);
    static TBool IsEscaped(const Brx& aBuffer, TUint aIndex);

    Bws<kMaxUriBytes> iAbsoluteUri;
    Bws<kMaxUriBytes> iBase;
    Bws<kMaxUriBytes> iRelative;
    Brn iScheme;
    Brn iHost;
    TInt iPort;
    Brn iAuthority;
    Brn iPath;
    Brn iQuery;
    Brn iPathAndQuery;
    Brn iFragment;
};

};  // namespace Zapp

#endif  // HEADER_LINN_ASCII_URI
