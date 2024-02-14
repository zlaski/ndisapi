#ifndef _NETINET_IP_H_
#define _NETINET_IP_H_

#pragma pack(push, 1)

struct ip {
    unsigned char ip_hl:4;             
    unsigned char ip_v:4;                    
    unsigned char ip_tos;              
    short ip_len;               
    unsigned short ip_id;              
    short ip_off;               
    unsigned char ip_ttl;              
    unsigned char ip_p;                
    unsigned short ip_sum;             
    unsigned int ip_src;              
    unsigned int ip_dst;              
};

#pragma pack(pop)

#endif // #ifndef _NETINET_IP_H_
