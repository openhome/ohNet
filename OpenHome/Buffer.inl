#ifndef HEADER_BUFFER_INL
#define HEADER_BUFFER_INL

//Bwx

inline OpenHome::Brx::Brx(TUint aBytes) : iBytes(aBytes)
{
}

inline OpenHome::Brx::Brx(const Brx& aBrx) : iBytes(aBrx.Bytes())
{
}

inline TUint OpenHome::Brx::Bytes() const
{
    return iBytes;
}

inline const TByte& OpenHome::Brx::operator[](TUint aByteIndex) const
{
    return At(aByteIndex);
}

inline TBool OpenHome::Brx::operator==(const Brx& aBrx) const
{
    return Equals(aBrx);
}

inline TBool OpenHome::Brx::operator!=(const Brx& aBrx) const
{
    return !Equals(aBrx);
}

//Brn

inline OpenHome::Brn::Brn() : Brx(0), iPtr(0)
{
}

inline OpenHome::Brn::Brn(const Brx& aBrx) : Brx(aBrx), iPtr(aBrx.Ptr())
{
}

inline OpenHome::Brn::Brn(const Brn& aBrn) : Brx(aBrn), iPtr(aBrn.Ptr())
{
}

inline OpenHome::Brn::Brn(const TByte* aPtr, TUint aBytes) : Brx(aBytes), iPtr(aPtr)
{
}

inline void OpenHome::Brn::Set(const Brx& aBrx)
{
    iPtr = aBrx.Ptr();
    iBytes = aBrx.Bytes();
}

inline void OpenHome::Brn::Set(const TByte* aPtr, TUint aBytes)
{
    iPtr = aPtr;
    iBytes = aBytes;
}

// Brv

inline OpenHome::Brv::Brv() : Brx(0) , iPtr(0)
{
}

inline OpenHome::Brv::Brv(TUint aBytes) : Brx(aBytes), iPtr(0)
{
}

// Brh

inline OpenHome::Brh::Brh()
{
}

inline void OpenHome::Brh::Set(const Brx& aBrx)
{
    Set(aBrx.Ptr(), aBrx.Bytes());
}

// Brhz

inline OpenHome::Brhz::Brhz()
{
}

inline void OpenHome::Brhz::Set(const Brx& aBrx)
{
    Set(aBrx.Ptr(), aBrx.Bytes());
}

inline const TChar* OpenHome::Brhz::CString() const
{
    return (const TChar*)iPtr;
}

//Bwx

inline void OpenHome::Bwx::Append(TChar aChar)
{
    Append(((TByte*)&aChar), 1);
}

inline void OpenHome::Bwx::Append(TByte aByte)
{
    Append((&aByte), 1);
}

inline void OpenHome::Bwx::FillZ()
{
    Fill(0);
}

inline TUint OpenHome::Bwx::MaxBytes() const
{
    return iMaxBytes;
}

inline TUint Bwx::BytesRemaining() const
{
    return MaxBytes() - Bytes();
}

inline TByte& OpenHome::Bwx::operator[](TUint aByteIndex)
{
    return At(aByteIndex);
}

//Bws

template <TUint S> inline OpenHome::Bws<S>::Bws() : Bwx(0, S)
{
}

template <TUint S> inline OpenHome::Bws<S>::Bws(const TChar* aStr)
    : Bwx(0,S)
{
    Replace(aStr);
}

template <TUint S> inline OpenHome::Bws<S>::Bws(const TByte* aPtr, TUint aBytes)
    : Bwx(0,S)
{
    Replace(aPtr, aBytes);
}

template <TUint S> inline OpenHome::Bws<S>::Bws(const Brx& aBuf) : Bwx(0,S)
{
    Replace(aBuf);
}

template <TUint S> inline OpenHome::Bws<S>::Bws(TUint aBytes) : Bwx(aBytes, S)
{
}

template <TUint S> inline OpenHome::Bws<S>::Bws(const Bws<S>& aBuf) : Bwx(0,S)
{
    Replace(aBuf);
}

template <TUint S> inline const TByte* OpenHome::Bws<S>::Ptr() const
{
    return iBuf;
}


#endif //HEADER_BUFFER_INL
