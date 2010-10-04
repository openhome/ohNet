#ifndef HEADER_BUFFER
#define HEADER_BUFFER

#include <ZappTypes.h>
#include <Exception.h>
#include <Standard.h>

EXCEPTION(BufferFull);
EXCEPTION(BufferOverflow);

namespace Zapp {

class Brn;

class Brx
{
public:
    inline TUint Bytes() const;
    inline const TByte& operator[](TUint aByteIndex) const;
    inline TBool operator==(const Brx& aBrx) const;
    inline TBool operator!=(const Brx& aBrx) const;
    DllExport TBool Equals(const Brx& aBrx) const;
    const TByte& At(TUint aByteIndex) const;
    virtual const TByte* Ptr() const=0;
    Brn Split(TUint aByteIndex) const;
    Brn Split(TUint aByteIndex, TUint aBytes) const;
    TBool BeginsWith(const Brx& aBrx) const;
    static const Brn& Empty();
    virtual ~Brx() {};
protected:
    explicit inline Brx(TUint aBytes);
    explicit inline Brx(const Brx& aBrx);
    TUint iBytes;
private:
    TInt16 Int16At(TUint aBytes) const;
    TUint16 Uint16At(TUint aBytes) const;
    TUint32 Uint32At(TUint aBytes) const;

    Brx& operator=(const Brx& aBrx);
};

class Brn : public Brx
{
public:
    inline explicit Brn();
    inline explicit Brn(const Brx& aBrx);
    inline Brn(const Brn& aBrn);
    inline explicit Brn(const TByte* aPtr, TUint aBytes);
    DllExport explicit Brn(const TChar* aPtr);
    inline void Set(const Brx& aBrx);
    inline void Set(const TByte* aPtr, TUint aBytes);
    void Set(const TChar* aPtr);
    virtual const TByte* Ptr() const;
protected:
    const TByte* iPtr;
private:
    Brn& operator=(const Brn& aBrn);
};

class Brv : public Brx, public INonCopyable
{
public:
    DllExport ~Brv();
    DllExport virtual const TByte* Ptr() const;
protected:
    inline Brv();
    inline Brv(TUint aBytes);
protected:
    const TByte* iPtr;
};

class Brhz;

class Brh : public Brv
{
	friend class Bwh;
	friend class Brhz;
public:
    inline explicit Brh();
    DllExport explicit Brh(const Brx& aBrx);
    DllExport explicit Brh(const TChar* aPtr);
    inline void Set(const Brx& aBrx);
    DllExport void Set(const TByte* aPtr, TUint aBytes);
    DllExport void Set(const TChar* aPtr);
    DllExport void TransferTo(Brh& aBrh);
    DllExport TChar* Extract();
};

class Brhz : public Brv
{
	friend class Bwh;
public:
    inline explicit Brhz();
    explicit Brhz(const Brx& aBrx);
    DllExport explicit Brhz(const TChar* aPtr);
    inline void Set(const Brx& aBrx);
    DllExport void Set(const TByte* aPtr, TUint aBytes);
    DllExport void Set(const TChar* aPtr);
    inline const TChar* CString() const;
    void Shrink(TUint aBytes);
    void TransferTo(Brh& aBrh);
    void TransferTo(Brhz& aBrhz);
    DllExport TChar* Transfer();
};

class Bwx : public Brx
{
public:
    void Replace(const Brx& aBuf);
    void ReplaceThrow(const Brx& aBuf);
    void Replace(const TByte* aPtr, TUint aBytes);
    void Replace(const TChar* aStr);
    inline void Append(TChar aChar);
    inline void Append(TByte aByte);
    void Append(const Brx& aB);
    void Append(const TChar* aStr);
    void Append(const TByte* aPtr, TUint aBytes);
    void AppendUint8(TUint8 aNum);
    void AppendInt8(TInt8 aNum);
    void AppendUint16(TUint16 aNum);
    void AppendInt16(TInt16 aNum);
    void AppendUint32(TUint32 aNum);
    void AppendInt32(TInt32 aNum);
    void AppendUint64(TUint64 aNum);
    void AppendInt64(TInt64 aNum);
    void AppendPrintf(const TChar* aFormatString, ...);
    const TChar* PtrZ() const;
    void Fill(TByte aFillByte);
    inline void FillZ();
    inline TUint MaxBytes() const;
    void SetBytes(TUint aBytes);
    inline TByte& operator[](TUint aByteIndex);
    TByte& At(TUint aByteIndex);
    TUint32& Uint32At(TUint aByteIndex);
protected:
    explicit Bwx(TUint aBytes, TUint aMaxBytes);
    TUint iMaxBytes;
};

class Bwn : public Bwx
{
public:
    explicit Bwn();
    explicit Bwn(const Bwx& aBwx);
    Bwn(const Bwn& aBwn);
    explicit Bwn(const TByte* aPtr, TUint aMaxBytes);
    explicit Bwn(const TByte* aPtr, TUint aBytes, TUint aMaxBytes);
    explicit Bwn(const TChar* aPtr, TUint aMaxBytes);
    explicit Bwn(const TChar* aPtr, TUint aBytes, TUint aMaxBytes);
    void Set(const Bwx& aBwx);
    void Set(const TByte* aPtr, TUint aMaxBytes);
    void Set(const TByte* aPtr, TUint aBytes, TUint aMaxBytes);
    virtual const TByte* Ptr() const;
protected:
    const TByte* iPtr;
private:
    Bwn& operator=(const Bwn&);
};

template <TUint S> class Bws : public Bwx
{
public:
    inline Bws();
    inline Bws(TUint aBytes);
    explicit inline Bws(const TChar* aStr);
    explicit inline Bws(const TByte* aPtr, TUint aBytes);
    explicit inline Bws(const Brx& aBuf);
    explicit inline Bws(const Bws<S>&);
    inline const TByte* Ptr() const;
protected:
    TByte iBuf[S];
private:
    Bws<S>& operator=(const Bws<S>&);
};

class Bwh : public Bwx
{
public:
    Bwh();
    Bwh(TUint aMaxBytes);
    Bwh(TUint aBytes, TUint aMaxBytes);
    explicit Bwh(const TChar* aStr);
    explicit Bwh(const TByte* aPtr, TUint aBytes);
    explicit Bwh(const Brx& aBrx);
    explicit Bwh(const Bwh& aBuf);
    virtual ~Bwh();
    void Grow(TUint aMaxBytes);
    void TransferTo(Brh& aBrh);
    void TransferTo(Brhz& aBrh);
    void TransferTo(Bwh& aBwh);
    virtual const TByte* Ptr() const;
protected:
    const TByte* iPtr;
private:
    Bwh& operator=(const Bwh&);
};

/**
 * Custom comparison function for stl map keyed on Brn
 */
class BufferCmp
{
public:
    TBool operator()(const Brx& aStr1, const Brx& aStr2) const;
};

#include <Buffer.inl>

} //namespace Zapp

#endif
