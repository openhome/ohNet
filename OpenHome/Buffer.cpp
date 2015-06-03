#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Printer.h>

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

using namespace OpenHome;

const TUint kMinBwdMaxBytes = 4;

const Brn kBrnEmpty((TByte*)"EMPTY", 0);

#define OhNetStrlen(s) (TUint)strlen(s)

// Brx

const Brn& Brx::Empty()
{
    return kBrnEmpty;
}

TBool Brx::Equals(const Brx& aBrx) const
{
    if (Bytes() == aBrx.Bytes()) {
        const TByte* dest = Ptr();
        if (dest == NULL) {
            return (aBrx.Bytes() == 0);
        }
        const TByte* src = aBrx.Ptr();
        if (src == NULL) {
            return false;
        }
        return (memcmp(dest, src, Bytes()) == 0);
    }
    return false;
}

const TByte& Brx::At(TUint aByteIndex) const
{
    ASSERT(aByteIndex < Bytes());
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    return((TByte&)(ptr[aByteIndex]));
}

Brn Brx::Split(TUint aByteIndex) const
{
    ASSERT(aByteIndex <= Bytes());
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    return Brn(ptr + aByteIndex, Bytes() - aByteIndex);
}

Brn Brx::Split(TUint aByteIndex, TUint aBytes) const
{
    ASSERT(aByteIndex + aBytes <= Bytes());
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    return Brn(ptr + aByteIndex, aBytes);
}

TBool Brx::BeginsWith(const Brx& aBrx) const
{
    if(Bytes() >= aBrx.Bytes()) {
        const TByte* ptr1 = Ptr();
        ASSERT(ptr1 != NULL);
        const TByte* ptr2 = aBrx.Ptr();
        ASSERT(ptr2 != NULL);
        return(memcmp(ptr1, ptr2, aBrx.Bytes()) == 0);
    }
    return false;
}

// Brn

Brn::Brn(const TChar* aPtr) : Brx(OhNetStrlen(aPtr)), iPtr((TByte*)aPtr)
{
}

void Brn::Set(const TChar* aStr)
{
    iPtr = (const TByte*)aStr;
    iBytes = OhNetStrlen(aStr);
}

const TByte* Brn::Ptr() const
{
    return iPtr;
}

// Brv

Brv::~Brv()
{
    free((void*)iPtr);
}

const TByte* Brv::Ptr() const
{
    return iPtr;
}

// Brh

Brh::Brh(const Brx& aBrx)
{
    Set(aBrx);
}

Brh::Brh(const TChar* aPtr)
{
    Set(aPtr);
}

void Brh::Set(const TByte* aPtr, TUint aBytes)
{
    free((void*)iPtr);
    iPtr = (TByte*)malloc(aBytes);
    ASSERT(iPtr != NULL);
    memcpy((void*)iPtr, aPtr, aBytes);
    iBytes = aBytes;
}

void Brh::Set(const TChar* aPtr)
{
    Set((const TByte*)aPtr, OhNetStrlen(aPtr));
}

void Brh::TransferTo(Brh& aBrh)
{
    free((void*)aBrh.iPtr);
    aBrh.iPtr = iPtr;
    aBrh.iBytes = iBytes;
    iPtr = NULL;
    iBytes = 0;
}

TChar* Brh::Extract()
{
    TChar* buf = (TChar*)iPtr;
    iPtr = NULL;
    iBytes = 0;
    return buf;
}

// Brhz

Brhz::Brhz(const Brx& aBrx)
{
    Set(aBrx);
}

Brhz::Brhz(const TChar* aPtr)
{
    Set(aPtr);
}

void Brhz::Set(const TByte* aPtr, TUint aBytes)
{
    const TByte kZero = 0;
    free((void*)iPtr);
    iPtr = (TByte*)malloc(aBytes + 1);
    ASSERT(iPtr != NULL);
    memcpy((void*)iPtr, aPtr, aBytes);
    memcpy((void*)(iPtr + aBytes), &kZero, 1);
    iBytes = aBytes;
}

void Brhz::Set(const TChar* aPtr)
{
    Set((const TByte*)aPtr, OhNetStrlen(aPtr));
}

void Brhz::Shrink(TUint aBytes)
{
    const TByte kZero = 0;
    ASSERT(aBytes <= iBytes);
    memcpy((void*)(iPtr + aBytes), &kZero, 1);
    iBytes = aBytes;
}

void Brhz::TransferTo(Brh& aBrh)
{
    free((void*)aBrh.iPtr);
    aBrh.iPtr = iPtr;
    aBrh.iBytes = iBytes;
    iPtr = NULL;
    iBytes = 0;
}

void Brhz::TransferTo(Brhz& aBrhz)
{
    free((void*)aBrhz.iPtr);
    aBrhz.iPtr = iPtr;
    aBrhz.iBytes = iBytes;
    iPtr = NULL;
    iBytes = 0;
}

TChar* Brhz::Transfer()
{
    TChar* ptr = (TChar*)iPtr;
    iPtr = NULL;
    iBytes = 0;
    return ptr;
}

// Bwx

Bwx::Bwx(TUint aBytes, TUint aMaxBytes) : Brx(aBytes), iMaxBytes(aMaxBytes)
{
    //Ensure we didn't just construct an invalid Buffer
    ASSERT(Bytes() <= MaxBytes());
}

void Bwx::Replace(const Brx& aBuf)
{
    try {
        ReplaceThrow(aBuf);
    }
    catch (BufferOverflow&) {
        ASSERTS();
    }
}

void Bwx::ReplaceThrow(const Brx& aBuf)
{
    if (aBuf.Bytes() > MaxBytes()) {
        THROW(BufferOverflow);
    }
    else
    {
        const TByte* dest = Ptr();
        ASSERT(dest != NULL);
        const TByte* src = aBuf.Ptr();
        ASSERT(src != NULL);
        (void)memmove(const_cast<TByte*>(dest), src, aBuf.Bytes());
        iBytes = aBuf.Bytes();
    }
}

void Bwx::Replace(const TByte* aPtr, TUint aBytes)
{
    ASSERT(aBytes <= MaxBytes());
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    memcpy(const_cast<TByte*>(ptr), aPtr, aBytes);
    iBytes = aBytes;
}

void Bwx::Replace(const TChar* aStr)
{
    TUint bytes = OhNetStrlen(aStr);
    ASSERT(bytes <= MaxBytes());
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    memcpy(const_cast<TByte*>(ptr), aStr, bytes);
    iBytes = bytes;
}

TBool OpenHome::Bwx::TryAppend(TChar aChar)
{
    if ((iMaxBytes-Bytes())<1)
    {
        return(false);
    }
    Append(aChar);
    return(true);
}

TBool OpenHome::Bwx::TryAppend(TByte aByte)
{
    if ((iMaxBytes-Bytes())<1)
    {
        return(false);
    }
    Append(aByte);
    return(true);
}


TBool Bwx::TryAppend(const TChar* aStr)
{
    if ((iMaxBytes-Bytes())<OhNetStrlen(aStr))
    {
        return(false);
    }
    Append(aStr);
    return(true);
}

void Bwx::Append(const TChar* aStr)
{
    Append((TByte*)aStr, OhNetStrlen(aStr));
}

TBool Bwx::TryAppend(const Brx& aB)
{
    if ((iMaxBytes-Bytes())<aB.Bytes())
    {
        return(false);
    }
    Append(aB);
    return(true);
}
void Bwx::Append(const Brx& aB)
{
    const TByte* ptr = aB.Ptr();
    ASSERT(ptr != NULL);
    Append(ptr, aB.Bytes());
}

TBool Bwx::TryAppend(const TByte* aPtr, TUint aBytes)
{
    if ((iMaxBytes-Bytes())<aBytes)
    {
        return(false);
    }
    Append(aPtr, aBytes);
    return(true);
}

void Bwx::Append(const TByte* aPtr, TUint aBytes)
{
    ASSERT(Bytes() + aBytes <= MaxBytes());
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    memcpy(const_cast<TByte*>(ptr+Bytes()), aPtr, aBytes);
    iBytes = Bytes() + aBytes;
}

void Bwx::AppendPrintf(const TChar* aFormatString, ...)
{
    va_list args;
    va_start( args, aFormatString );
    AppendPrintf(aFormatString, args);
    va_end(args);
}

void Bwx::AppendPrintf(const TChar* aFormatString, va_list aArgs)
{
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    TUint n = vsnprintf(
        (TChar*) (ptr + Bytes()),
        MaxBytes() - Bytes(),
        aFormatString,
        aArgs );

    if((Bytes() + n) > MaxBytes()) {
        SetBytes(MaxBytes());
        THROW(BufferFull);
    }
    else {
        SetBytes(Bytes() + n);
    }
}

const TChar* Bwx::PtrZ() const
{
    ASSERT(Bytes() + 1 <= MaxBytes());
    //Nul terminate without updating number of bytes in buffer
    TByte* ptr = (TByte*)Ptr();
    ASSERT(ptr != NULL);
    *(ptr + Bytes()) = '\0';
    return (const TChar*)ptr;
}

void Bwx::Fill(TByte aByte)
{
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    memset(const_cast<TByte*>(ptr), aByte, Bytes());
}

void Bwx::SetBytes(TUint aBytes)
{
    ASSERT(aBytes <= MaxBytes());
    iBytes = aBytes;
}

TByte& Bwx::At(TUint aByteIndex)
{
    ASSERT(aByteIndex < Bytes());
    const TByte* ptr = Ptr();
    ASSERT(ptr != NULL);
    return(const_cast<TByte&>(ptr[aByteIndex]));
}

// Bwn

Bwn::Bwn() : Bwx(0,0), iPtr(0)
{
}

Bwn::Bwn(const Bwx& aBwx) : Bwx(aBwx.Bytes(), aBwx.MaxBytes()), iPtr(aBwx.Ptr())
{
    ASSERT(iPtr != NULL);
}

Bwn::Bwn(const Bwn& aBwn) : Bwx(aBwn.Bytes(), aBwn.MaxBytes()), iPtr(aBwn.Ptr())
{
    ASSERT(iPtr != NULL);
}

Bwn::Bwn(const TByte* aPtr, TUint aMaxBytes) : Bwx(0, aMaxBytes), iPtr(aPtr)
{
}

Bwn::Bwn(const TByte* aPtr, TUint aBytes, TUint aMaxBytes) : Bwx(aBytes, aMaxBytes), iPtr(aPtr)
{
}

Bwn::Bwn(const TChar* aPtr, TUint aMaxBytes) : Bwx(0, aMaxBytes), iPtr((TByte*)aPtr)
{
}

Bwn::Bwn(const TChar* aPtr, TUint aBytes, TUint aMaxBytes) : Bwx(aBytes, aMaxBytes), iPtr((TByte*)aPtr)
{
}

void Bwn::Set(const Bwx& aBwx)
{
    iPtr = aBwx.Ptr();
    ASSERT(iPtr != NULL);
    iBytes = aBwx.Bytes();
    iMaxBytes = aBwx.MaxBytes();
}

void Bwn::Set(const TByte* aPtr, TUint aMaxBytes)
{
    iPtr = aPtr;
    iBytes = 0;
    iMaxBytes = aMaxBytes;
}

void Bwn::Set(const TByte* aPtr, TUint aBytes, TUint aMaxBytes)
{
    ASSERT(aBytes <= aMaxBytes);
    iPtr = aPtr;
    iBytes = aBytes;
    iMaxBytes = aMaxBytes;
}

const TByte* Bwn::Ptr() const
{
    return iPtr;
}

// Bwh

Bwh::Bwh() : Bwx(0,0), iPtr(0)
{
}

Bwh::Bwh(TUint aMaxBytes) : Bwx(0, aMaxBytes)
{
    iPtr = (TByte*)malloc(aMaxBytes);
    ASSERT(iPtr != NULL);
}

Bwh::Bwh(TUint aBytes, TUint aMaxBytes) : Bwx(aBytes, aMaxBytes)
{
    iPtr = (TByte*)malloc(aMaxBytes);
    ASSERT(iPtr != NULL);
}

Bwh::~Bwh()
{
    free((void*)iPtr);
}

const TByte* Bwh::Ptr() const
{
    return iPtr;
}

Bwh::Bwh(const TChar* aStr) : Bwx(0, OhNetStrlen(aStr))
{
    iPtr = (TByte*)malloc(iMaxBytes);
    ASSERT(iPtr != NULL);
    Replace(aStr);
}

Bwh::Bwh(const TByte* aPtr, TUint aBytes) : Bwx(aBytes, aBytes)
{
    iPtr = (TByte*)malloc(aBytes);
    ASSERT(iPtr != NULL);
    Replace(aPtr, aBytes);
}

Bwh::Bwh(const Brx& aBrx) : Bwx(aBrx.Bytes(), aBrx.Bytes())
{
    iPtr = (TByte*)malloc(aBrx.Bytes());
    ASSERT(iPtr != NULL);
    Replace(aBrx);
}

Bwh::Bwh(const Bwh& aBuf) : Bwx(aBuf.Bytes(), aBuf.Bytes())
{
    iPtr = (TByte*)malloc(aBuf.Bytes());
    ASSERT(iPtr != NULL);
    Replace(aBuf);
}

void Bwh::Grow(TUint aMaxBytes)
{
    if(aMaxBytes < kMinBwdMaxBytes) {
        aMaxBytes = kMinBwdMaxBytes;
    }
    if(iPtr) {
        if(aMaxBytes > iMaxBytes) {
            const TByte* oldPtr = iPtr;
            iPtr = (TByte*)malloc(aMaxBytes);
            ASSERT(iPtr != NULL);
            Replace(oldPtr, Bytes());
            free((void*)oldPtr);
            iMaxBytes = aMaxBytes;
        }
    }
    else {
        iPtr = (TByte*)malloc(aMaxBytes);
        ASSERT(iPtr != NULL);
        iMaxBytes = aMaxBytes;
    }
}

void Bwh::TransferTo(Brh& aBrh)
{
    free((void*)aBrh.iPtr);
    aBrh.iPtr = iPtr;
    aBrh.iBytes = iBytes;
    iPtr = NULL;
    iBytes = 0;
}

void Bwh::TransferTo(Brhz& aBrhz)
{
    free((void*)aBrhz.iPtr);
    aBrhz.iPtr = (TByte*)malloc(iBytes+1);
    ASSERT(aBrhz.iPtr != NULL);
    (void)memcpy((void*)aBrhz.iPtr, iPtr, iBytes);
    const_cast<TByte*>(aBrhz.iPtr)[iBytes] = '\0';
    aBrhz.iBytes = iBytes;
    free((void*)iPtr);
    iPtr = NULL;
    iBytes = 0;
}

void Bwh::TransferTo(Bwh& aBwh)
{
    free((void*)aBwh.iPtr);
    aBwh.iPtr = iPtr;
    aBwh.iBytes = iBytes;
    iPtr = NULL;
    iBytes = 0;
}

// BufferCmp

TBool BufferCmp::operator()(const Brx& aStr1, const Brx& aStr2) const
{
    const TInt bytes1 = aStr1.Bytes();
    const TInt bytes2 = aStr2.Bytes();
    const TInt bytes = (bytes1<bytes2? bytes1 : bytes2);
    const TByte* ptr1 = aStr1.Ptr();
    const TByte* ptr2 = aStr2.Ptr();
    for (TInt i=0; i<bytes; i++) {
        if (*ptr1 != *ptr2) {
            return (*ptr1 < *ptr2);
        }
        ptr1++;
        ptr2++;
    }
    return (bytes1 < bytes2);
}

