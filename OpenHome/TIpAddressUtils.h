#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {

class TIpAddressUtils
{
public:
    static const TUint16 kLinkLocalIPv6Prefix = 0xFE80;
    static const TUint kMaxAddressBytes = 40; // Potentially 32 Hex characters + 7 colon de-limiters + terminator for IPv6 addr
    typedef Bws<kMaxAddressBytes> AddressBuf;
public:
    static TBool Equals(const TIpAddress& aAddr1, const TIpAddress& aAddr2);
    static TBool LessThan(const TIpAddress& aAddr1, const TIpAddress& aAddr2);          // Returns true if aAddr1.iFamily == IPv4 and aAddr2.iFamily == IPv6
    static TIpAddress ApplyMask(const TIpAddress& aAddr, const TIpAddress& aMask);
    static TBool IsZero(const TIpAddress& aAddr);
    static TBool IsLoopback(const TIpAddress& aAddr);
    static TBool IsLinkLocalIPv6Address(const TIpAddress& aAddr);
    static TBool IsIPv6MappedIPv4Address(const TIpAddress& aAddr);
    static TIpAddress IPv4FromIPv6MappedIPv4Address(const TIpAddress& aAddr);
    static TIpAddress MapIPv4ToIPv6Address(const TIpAddress& aAddr);
    static TIpAddress AddressV6AllAdapters();
    static void ToString(const TIpAddress& aAddr, Bwx& aAddressBuffer);
private:
    static void AddressToStringV4(Bwx& aAddressBuffer, const TIpAddress& aAddress);
    static void AddressToStringV6(Bwx& aAddressBuffer, const TIpAddress& aAddress);
};

} // namespace OpenHome
