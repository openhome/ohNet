/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * Changes:
 *
 *	2011-08-17 Gregg Hamilton for OpenHome (http://openhome.org/wiki/OhNet:What)
 *			Split file into header and source for compilation against C code.
 */

#ifndef IFADDRS_ANDROID_H_included
#define IFADDRS_ANDROID_H_included

#ifdef __cplusplus
#include <cstring>
#include <new>
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include <net/if.h>
#include <netinet/in.h>

#ifdef __cplusplus
#include "LocalArray.h"
#include "ScopedFd.h"
#endif

// Android (bionic) doesn't have getifaddrs(3)/freeifaddrs(3).
// We fake it here, so java_net_NetworkInterface.cpp can use that API
// with all the non-portable code being in this file.

// Source-compatible subset of the BSD struct.
struct ifaddrs {
    // Pointer to next struct in list, or NULL at end.
    struct ifaddrs* ifa_next;

    // Interface name.
    char* ifa_name;

    // Interface flags.
    unsigned int ifa_flags;

    // Interface address.
    struct sockaddr* ifa_addr;

    // Interface netmask;
    struct sockaddr* ifa_netmask;

#ifdef __cplusplus
    ifaddrs(ifaddrs* next)
    : ifa_next(next), ifa_name(NULL), ifa_flags(0), ifa_addr(NULL), ifa_netmask(NULL)
    {
    }

    ~ifaddrs() {
        delete ifa_next;
        delete[] ifa_name;
        delete ifa_addr;
        delete ifa_netmask;
    }

    // Sadly, we can't keep the interface index for portability with BSD.
    // We'll have to keep the name instead, and re-query the index when
    // we need it later.
    bool setNameAndFlagsByIndex(int interfaceIndex) {
        // Get the name.
        //interfaceIndex = 0;
        char buf[IFNAMSIZ];
        char* name = if_indextoname(interfaceIndex, buf);
        if (name == NULL) {
            return false;
        }
        ifa_name = new char[strlen(name) + 1];
        strcpy(ifa_name, name);

        // Get the flags.
        ScopedFd fd(socket(AF_INET, SOCK_DGRAM, 0));
        if (fd.get() == -1) {
            return false;
        }
        ifreq ifr;
        memset(&ifr, 0, sizeof(ifr));
        strcpy(ifr.ifr_name, name);
        int rc = ioctl(fd.get(), SIOCGIFFLAGS, &ifr);
        if (rc == -1) {
            return false;
        }
        ifa_flags = ifr.ifr_flags;
        return true;
    }

    // Netlink gives us the address family in the header, and the
    // sockaddr_in or sockaddr_in6 bytes as the payload. We need to
    // stitch the two bits together into the sockaddr that's part of
    // our portable interface.
    void setAddress(unsigned char family, void* data, size_t byteCount) {
        sockaddr_storage* ss = new sockaddr_storage;
        ss->ss_family = family;
        if (family == AF_INET) {
            void* dst = &reinterpret_cast<sockaddr_in*>(ss)->sin_addr;
            memcpy(dst, data, byteCount);
        } else if (family == AF_INET6) {
            void* dst = &reinterpret_cast<sockaddr_in6*>(ss)->sin6_addr;
            memcpy(dst, data, byteCount);
        }
        ifa_addr = reinterpret_cast<sockaddr*>(ss);
    }

    // Netlink gives us the prefix length of the IP address, so we
    // use this to construct the netmask.
    void setNetmask(unsigned char family, unsigned char prefixlen) {
        if (family == AF_INET) {
            __uint32_t netmask = 0xffffffff;
            netmask = netmask << (32 - prefixlen);
            sockaddr_in* netmask_addr = new sockaddr_in;
            netmask_addr->sin_family = family;
            netmask_addr->sin_port = 0;
            netmask_addr->sin_addr.s_addr = htonl(netmask);
            ifa_netmask = reinterpret_cast<sockaddr*>(netmask_addr);
        }
    }

    #endif
};

// FIXME: use iovec instead.
struct addrReq_struct {
    struct nlmsghdr netlinkHeader;
    struct ifaddrmsg msg;
};

#ifdef __cplusplus
inline bool sendNetlinkMessage(int fd, const void* data, size_t byteCount);
inline ssize_t recvNetlinkMessage(int fd, char* buf, size_t byteCount);
#endif

#ifdef __cplusplus
extern "C" {
#endif
// Source-compatible with the BSD function.
int getifaddrs(struct ifaddrs** result);

// Source-compatible with the BSD function.
void freeifaddrs(struct ifaddrs* addresses);
#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // IFADDRS_ANDROID_H_included
