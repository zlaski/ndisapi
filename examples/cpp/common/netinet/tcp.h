#ifndef _NETINET_TCP_H_
#define _NETINET_TCP_H_

#pragma pack(push, 1)

struct tcphdr {
    unsigned short th_sport;       
    unsigned short th_dport;       
    unsigned int  th_seq;         
    unsigned int  th_ack;         
    unsigned char  th_x2:4;     
    unsigned char  th_off:4;       
    unsigned char  th_flags;       
    unsigned short th_win;         
    unsigned short th_sum;         
    unsigned short th_urp;         
};

#pragma pack(pop)

#endif // #ifndef _NETINET_TCP_H_
