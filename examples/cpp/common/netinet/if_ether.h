#ifndef _NETINET_IF_ETHER_H_
#define _NETINET_IF_ETHER_H_

#pragma pack(push, 1)

struct ether_header {
    unsigned char ether_dhost[6];     
    unsigned char ether_shost[6];     
    unsigned short ether_type;         
};

#pragma pack(pop)

#define ETH_HLEN	14

#define ETHER_TYPE_IPv4 0x0800
#define ETHER_TYPE_IPv6 0x86DD

#endif // #ifndef _NETINET_IF_ETHER_H_
