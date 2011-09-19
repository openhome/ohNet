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

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include <ifaddrs.h>

// Android (bionic) doesn't have getifaddrs(3)/freeifaddrs(3).
// We fake it here, so java_net_NetworkInterface.cpp can use that API
// with all the non-portable code being in this file.

inline bool sendNetlinkMessage(int fd, const void* data, size_t byteCount) {
    ssize_t sentByteCount = TEMP_FAILURE_RETRY(send(fd, data, byteCount, 0));
    return (sentByteCount == static_cast<ssize_t>(byteCount));
}

inline ssize_t recvNetlinkMessage(int fd, char* buf, size_t byteCount) {
    return TEMP_FAILURE_RETRY(recv(fd, buf, byteCount, 0));
}

// Source-compatible with the BSD function.
int getifaddrs(ifaddrs** result) {

    // Simplify cleanup for callers.
    *result = NULL;

    // Create a netlink socket.
    ScopedFd fd(socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE));
    if (fd.get() < 0) {
        return -1;
    }

    // Ask for the address information.
    addrReq_struct addrRequest;
    memset(&addrRequest, 0, sizeof(addrRequest));
    addrRequest.netlinkHeader.nlmsg_flags = NLM_F_REQUEST | NLM_F_MATCH;
    addrRequest.netlinkHeader.nlmsg_type = RTM_GETADDR;
    addrRequest.netlinkHeader.nlmsg_len = NLMSG_ALIGN(NLMSG_LENGTH(sizeof(addrRequest)));
    addrRequest.msg.ifa_family = AF_UNSPEC; // All families.
    addrRequest.msg.ifa_index = 0; // All interfaces.
    if (!sendNetlinkMessage(fd.get(), &addrRequest, addrRequest.netlinkHeader.nlmsg_len)) {
        return -1;
    }
    
    // Read the responses.
    LocalArray<0> buf(65536); // We don't necessarily have std::vector.
    ssize_t bytesRead;
    while ((bytesRead  = recvNetlinkMessage(fd.get(), &buf[0], buf.size())) > 0) {
        nlmsghdr* hdr = reinterpret_cast<nlmsghdr*>(&buf[0]);
        for (; NLMSG_OK(hdr, (unsigned int)bytesRead); hdr = NLMSG_NEXT(hdr, bytesRead)) {
            switch (hdr->nlmsg_type) {
            case NLMSG_DONE:
            {
                return 0;
            }
            case NLMSG_ERROR:
            {
                return -1;
            }
            case RTM_NEWADDR:
                {
                    ifaddrmsg* address = reinterpret_cast<ifaddrmsg*>(NLMSG_DATA(hdr));
                    rtattr* rta = IFA_RTA(address);
                    size_t ifaPayloadLength = IFA_PAYLOAD(hdr);
                    while (RTA_OK(rta, ifaPayloadLength)) {
                        if (rta->rta_type == IFA_LOCAL) {
                            unsigned char family = address->ifa_family;
                            if (family == AF_INET || family == AF_INET6) {
                                *result = new ifaddrs(*result);
                                if (!(*result)->setNameAndFlagsByIndex(address->ifa_index)) {
                                    return -1;
                                }
                                (*result)->setAddress(family, RTA_DATA(rta), RTA_PAYLOAD(rta));
                                (*result)->setNetmask(family, address->ifa_prefixlen);
                            }
                        }
                        rta = RTA_NEXT(rta, ifaPayloadLength);
                    }
                }
                break;
            }
        }
    }
    // We only get here if recv fails before we see a NLMSG_DONE.
    return -1;
}

// Source-compatible with the BSD function.
void freeifaddrs(struct ifaddrs* addresses) {
    delete addresses;
}

