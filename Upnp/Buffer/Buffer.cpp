#include <Buffer.h>
#include <Standard.h>
#include <Arch.h>
#include <Printer.h>

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

using namespace Zapp;

const TUint kMinBwdMaxBytes = 4;

const Brn kBrnEmpty((TByte*)"EMPTY", 0);

#define ZappStrlen(s) (TUint)strlen(s)

// Brx

const Brn& Brx::Empty()
{
    return kBrnEmpty;
}

TBool Brx::Equals(const Brx& aBrx) const
{
    if(Bytes() == aBrx.Bytes()) {
        return(memcmp(Ptr(), aBrx.Ptr(), Bytes()) == 0);
    }
    return false;
}

const TByte& Brx::At(TUint aByteIndex) const
{
    ASSERT(aByteIndex < Bytes());
    return((TByte&)(Ptr()[aByteIndex]));
}

Brn Brx::Split(TUint aByteIndex) const
{
    ASSERT(aByteIndex <= Bytes());
    return Brn(Ptr() + aByteIndex, Bytes() - aByteIndex);
}

Brn Brx::Split(TUint aByteIndex, TUint aBytes) const
{
    ASSERT(aByteIndex + aBytes <= Bytes());
    return Brn(Ptr() + aByteIndex, aBytes);
}

TBool Brx::BeginsWith(const Brx& aBrx) const
{
    if(Bytes() >= aBrx.Bytes()) {
        return(memcmp(Ptr(), aBrx.Ptr(), aBrx.Bytes()) == 0);
    }
    return false;
}

// Brn

Brn::Brn(const TChar* aPtr) : Brx(ZappStrlen(aPtr)), iPtr((TByte*)aPtr)
{
}

void Brn::Set(const TChar* aStr)
{
    iPtr = (const TByte*)aStr;
    iBytes = ZappStrlen(aStr);
}

const TByte* Brn::Ptr() const
{
    ASSERT(iPtr);
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
    memcpy((void*)iPtr, aPtr, aBytes);
    iBytes = aBytes;
}

void Brh::Set(const TChar* aPtr)
{
    Set((const TByte*)aPtr, ZappStrlen(aPtr));
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
    memcpy((void*)iPtr, aPtr, aBytes);
    memcpy((void*)(iPtr + aBytes), &kZero, 1);
    iBytes = aBytes;
}

void Brhz::Set(const TChar* aPtr)
{
    Set((const TByte*)aPtr, ZappStrlen(aPtr));
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
        (void)memmove(const_cast<TByte*>(Ptr()), aBuf.Ptr(), aBuf.Bytes());
        iBytes = aBuf.Bytes();
    }
}

void Bwx::Replace(const TByte* aPtr, TUint aBytes)
{
    ASSERT(aBytes <= MaxBytes());
    memcpy(const_cast<TByte*>(Ptr()), aPtr, aBytes);
    iBytes = aBytes;
}

void Bwx::Replace(const TChar* aStr)
{
    TUint bytes = ZappStrlen(aStr);
    ASSERT(bytes <= MaxBytes());
    memcpy(const_cast<TByte*>(Ptr()), aStr, bytes);
    iBytes = bytes;
}

void Bwx::Append(const TChar* aStr)
{
    Append((TByte*)aStr, ZappStrlen(aStr));
}

void Bwx::Append(const Brx& aB)
{
    Append(aB.Ptr(), aB.Bytes());
}

void Bwx::Append(const TByte* aPtr, TUint aBytes)
{
    ASSERT(Bytes() + aBytes <= MaxBytes());
    memcpy(const_cast<TByte*>(Ptr()+Bytes()), aPtr, aBytes);
    iBytes = Bytes() + aBytes;
}

void Bwx::AppendUint8(TUint8 aNum)
{
    Append(&aNum, 1);
}

void Bwx::AppendInt8(TInt8 aNum)
{
    Append((TByte*)&aNum, 1);
}

void Bwx::AppendUint16(TUint16 aNum)
{
    ASSERT(Bytes() + sizeof(TUint16) <= MaxBytes());
    TUint16 num = Arch::BigEndian2(aNum);
    memcpy(const_cast<TByte*>(Ptr()+Bytes()), &num, sizeof(TUint16));
    iBytes = Bytes() + sizeof(TUint16);
}

void Bwx::AppendInt16(TInt16 aNum)
{
    ASSERT(Bytes() + sizeof(TInt16) <= MaxBytes());
    TInt16 num = Arch::BigEndian2(aNum);
    memcpy(const_cast<TByte*>(Ptr()+Bytes()), &num, sizeof(TInt16));
    iBytes = Bytes() + sizeof(TInt16);
}

void Bwx::AppendUint32(TUint32 aNum)
{
    ASSERT(Bytes() + sizeof(TUint32) <= MaxBytes());
    TUint32 num = Arch::BigEndian4(aNum);
    memcpy(const_cast<TByte*>(Ptr()+Bytes()), &num, sizeof(TUint32));
    iBytes = Bytes() + sizeof(TUint32);
}

void Bwx::AppendInt32(TInt32 aNum)
{
    ASSERT(Bytes() + sizeof(TInt32) <= MaxBytes());
    TInt32 num = Arch::BigEndian4(aNum);
    memcpy(const_cast<TByte*>(Ptr()+Bytes()), &num, sizeof(TInt32));
    iBytes = Bytes() + sizeof(TInt32);
}

void Bwx::AppendUint64(TUint64 aNum)
{
    ASSERT(Bytes() + sizeof(TUint64) <= MaxBytes());
    TUint64 num = Arch::BigEndian8(aNum);
    memcpy(const_cast<TByte*>(Ptr()+Bytes()), &num, sizeof(TUint64));
    iBytes = Bytes() + sizeof(TUint64);
}

void Bwx::AppendInt64(TInt64 aNum)
{
    ASSERT(Bytes() + sizeof(TInt64) <= MaxBytes());
    TInt64 num = Arch::BigEndian8(aNum);
    memcpy(const_cast<TByte*>(Ptr()+Bytes()), &num, sizeof(TInt64));
    iBytes = Bytes() + sizeof(TInt64);
}

void Bwx::AppendPrintf(const TChar* aFormatString, ...)
{
    va_list args;
    va_start( args, aFormatString );

    TUint n = vsnprintf(
        (TChar*) (Ptr() + Bytes()),
        MaxBytes() - Bytes(),
        aFormatString,
        args );

    if((Bytes() + n) >= MaxBytes()) {
        SetBytes(MaxBytes());
        THROW(BufferFull);
    }
    else {
        SetBytes( Bytes() + n );
    }

    va_end( args );
}

const TChar* Bwx::PtrZ() const
{
    ASSERT(Bytes() + 1 <= MaxBytes());
    //Nul terminate without updating number of bytes in buffer
    TByte* ptr = (TByte*)Ptr();
    *(ptr + Bytes()) = '\0';
    return (const TChar*)ptr;
}

void Bwx::Fill(TByte aByte)
{
    memset(const_cast<TByte*>(Ptr()), aByte, Bytes());
}

void Bwx::SetBytes(TUint aBytes)
{
    ASSERT(aBytes <= MaxBytes());
    iBytes = aBytes;
}

TByte& Bwx::At(TUint aByteIndex)
{
    ASSERT(aByteIndex < Bytes());
    return(const_cast<TByte&>(Ptr()[aByteIndex]));
}

TUint32& Bwx::Uint32At(TUint aByteIndex)
{
    ASSERT((aByteIndex + sizeof(TUint32)) <= Bytes());
    return((TUint32&)(Ptr()[aByteIndex]));
}

// Bwn

Bwn::Bwn() : Bwx(0,0), iPtr(0)
{
}

Bwn::Bwn(const Bwx& aBwx) : Bwx(aBwx.Bytes(), aBwx.MaxBytes()), iPtr(aBwx.Ptr())
{
}

Bwn::Bwn(const Bwn& aBwn) : Bwx(aBwn.Bytes(), aBwn.MaxBytes()), iPtr(aBwn.Ptr())
{
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
}

Bwh::Bwh(TUint aBytes, TUint aMaxBytes) : Bwx(aBytes, aMaxBytes)
{
    iPtr = (TByte*)malloc(aMaxBytes);
}

Bwh::~Bwh()
{
    free((void*)iPtr);
}

const TByte* Bwh::Ptr() const
{
    ASSERT(iPtr);
    return iPtr;
}

Bwh::Bwh(const TChar* aStr) : Bwx(0, ZappStrlen(aStr))
{
    iPtr = (TByte*)malloc(ZappStrlen(aStr));
    Replace(aStr);
}

Bwh::Bwh(const TByte* aPtr, TUint aBytes) : Bwx(aBytes, aBytes)
{
    iPtr = (TByte*)malloc(aBytes);
    Replace(aPtr, aBytes);
}

Bwh::Bwh(const Brx& aBrx) : Bwx(aBrx.Bytes(), aBrx.Bytes())
{
    iPtr = (TByte*)malloc(aBrx.Bytes());
    Replace(aBrx);
}

Bwh::Bwh(const Bwh& aBuf) : Bwx(aBuf.Bytes(), aBuf.Bytes())
{
    iPtr = (TByte*)malloc(aBuf.Bytes());
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
            Replace(oldPtr, Bytes());
            free((void*)oldPtr);
            iMaxBytes = aMaxBytes;
        }
    }
    else {
        iPtr = (TByte*)malloc(aMaxBytes);
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
    aBrhz.iPtr = iPtr;
    aBrhz.iBytes = iBytes;
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

