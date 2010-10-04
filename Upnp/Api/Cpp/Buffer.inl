#ifndef HEADER_BUFFER_INL
#define HEADER_BUFFER_INL

//Bwx

inline Brx::Brx(TUint aBytes) : iBytes(aBytes)
{
}

inline Brx::Brx(const Brx& aBrx) : iBytes(aBrx.Bytes())
{
}

inline TUint Brx::Bytes() const
{
    return iBytes;
}

inline const TByte& Brx::operator[](TUint aByteIndex) const
{
    return At(aByteIndex);
}

inline TBool Brx::operator==(const Brx& aBrx) const
{
    return Equals(aBrx);
}

inline TBool Brx::operator!=(const Brx& aBrx) const
{
    return !Equals(aBrx);
}

//Brn

inline Brn::Brn() : Brx(0), iPtr(0)
{
}

inline Brn::Brn(const Brx& aBrx) : Brx(aBrx), iPtr(aBrx.Ptr())
{
}

inline Brn::Brn(const Brn& aBrn) : Brx(aBrn), iPtr(aBrn.Ptr())
{
}

inline Brn::Brn(const TByte* aPtr, TUint aBytes) : Brx(aBytes), iPtr(aPtr)
{
}

inline void Brn::Set(const Brx& aBrx)
{
    iPtr = aBrx.Ptr();
    iBytes = aBrx.Bytes();
}

inline void Brn::Set(const TByte* aPtr, TUint aBytes)
{
    iPtr = aPtr;
    iBytes = aBytes;
}

// Brv

inline Brv::Brv() : Brx(0) , iPtr(0)
{
}

inline Brv::Brv(TUint aBytes) : Brx(aBytes), iPtr(0)
{
}

// Brh

inline Brh::Brh()
{
}

inline void Brh::Set(const Brx& aBrx)
{
    Set(aBrx.Ptr(), aBrx.Bytes());
}

// Brhz

inline Brhz::Brhz()
{
}

inline void Brhz::Set(const Brx& aBrx)
{
    Set(aBrx.Ptr(), aBrx.Bytes());
}

inline const TChar* Brhz::CString() const
{
    return (const TChar*)iPtr;
}

//Bwx

inline void Bwx::Append(TChar aChar)
{
    Append(((TByte*)&aChar), 1);
}

inline void Bwx::Append(TByte aByte)
{
    Append((&aByte), 1);
}

inline void Bwx::FillZ()
{
    Fill(0);
}

inline TUint Bwx::MaxBytes() const
{
    return iMaxBytes;
}

inline TByte& Bwx::operator[](TUint aByteIndex) 
{
    return At(aByteIndex);
}

//Bws

template <TUint S> inline Bws<S>::Bws() : Bwx(0, S)
{
}

template <TUint S> inline Bws<S>::Bws(const TChar* aStr)
    : Bwx(0,S)
{
    Replace(aStr); 
}

template <TUint S> inline Bws<S>::Bws(const TByte* aPtr, TUint aBytes)
    : Bwx(0,S)
{
    Replace(aPtr, aBytes); 
}

template <TUint S> inline Bws<S>::Bws(const Brx& aBuf) : Bwx(0,S)
{
    Replace(aBuf);
}

template <TUint S> inline Bws<S>::Bws(TUint aBytes) : Bwx(aBytes, S)
{
}

template <TUint S> inline Bws<S>::Bws(const Bws<S>& aBuf) : Bwx(0,S)
{
    Replace(aBuf);
}

template <TUint S> inline const TByte* Bws<S>::Ptr() const
{
    return iBuf;
}


#endif //HEADER_BUFFER_INL
