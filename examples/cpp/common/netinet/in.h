#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_

#pragma pack(push, 1)

enum {
    IPPROTO_IP = 0,
    IPPROTO_ICMP = 1,
    IPPROTO_TCP = 6,
    IPPROTO_UDP = 17,
    IPPROTO_IPV6 = 41
};

struct in6_addr
{
    union
    {
        unsigned char	__u6_addr8[16];
        unsigned short __u6_addr16[8];
        unsigned int __u6_addr32[4];
    } __in6_u;
};

#pragma pack(pop)

#endif // #ifndef _NETINET_IN_H_
