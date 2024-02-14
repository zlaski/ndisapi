#ifndef _NETINET_IP6_H_
#define _NETINET_IP6_H_

#include "in.h"

#pragma pack(push, 1)

struct ip6_hdr
{
    union
    {
        struct ip6_hdrctl
        {
            unsigned int ip6_un1_flow;   /* 4 bits version, 8 bits TC,
                        20 bits flow-ID */
            unsigned short ip6_un1_plen;   /* payload length */
            unsigned char  ip6_un1_nxt;    /* next header */
            unsigned char  ip6_un1_hlim;   /* hop limit */
        } ip6_un1;
        unsigned char ip6_un2_vfc;       /* 4 bits version, top 4 bits tclass */
    } ip6_ctlun;
    struct in6_addr ip6_src;      /* source address */
    struct in6_addr ip6_dst;      /* destination address */
};

#pragma pack(pop)

#endif // #ifndef _NETINET_IP6_H_
