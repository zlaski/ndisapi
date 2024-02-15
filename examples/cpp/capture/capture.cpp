// capture.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#define ip_size sizeof(struct iphdr)
#define tcp_size  sizeof(struct tcphdr)
#define packet buffer.m_IBuffer

#define TCP_PORT_SMB3 0x01BD
#define TCP_PORT_SMB3_NET 0xBD01

#define TCP_PORT_4445 0x115D
#define TCP_PORT_4445_NET 0x5D11

#define LOCAL_SUBNET 0xC0A8
#define LOCAL_SUBNET_NET 0xA8C0

int main()
{
	try
	{
		std::string file_name;
		pcap::pcap_file_storage file_stream;

		auto ndis_api = std::make_unique<ndisapi::fastio_packet_filter>(
			[&file_stream](HANDLE, INTERMEDIATE_BUFFER& buffer)
			{
                file_stream << buffer;

                struct ether_header* ethernet = (struct ether_header*)packet;
                if (ethernet->h_proto == ETH_P_IP_NET) {
                    struct iphdr* ip = (struct iphdr*)(packet + ETHER_HEADER_LENGTH);
                    if (ip->ip_p == IPPROTO_TCP && ip->ip_dst.S_un.S_un_w.s_w1 != LOCAL_SUBNET_NET) {
                        struct tcphdr* tcp = (struct tcphdr*)(packet + ETHER_HEADER_LENGTH + ip_size);
                        if (tcp->th_sport == TCP_PORT_4445_NET) {
                            tcp->th_sport = TCP_PORT_SMB3_NET;
                        }
                    }
                }

                return ndisapi::fastio_packet_filter::packet_action::pass;
			},
			[&file_stream](HANDLE, INTERMEDIATE_BUFFER& buffer)
			{
                struct ether_header* ethernet = (struct ether_header*)packet;
                if (ethernet->h_proto == ETH_P_IP_NET) {
                    struct iphdr* ip = (struct iphdr*)(packet + ETHER_HEADER_LENGTH);
                    if (ip->ip_p == IPPROTO_TCP && ip->ip_dst.S_un.S_un_w.s_w1 != LOCAL_SUBNET_NET) {
                        struct tcphdr* tcp = (struct tcphdr*)(packet + ETHER_HEADER_LENGTH + ip_size);
                        if (tcp->th_dport == TCP_PORT_SMB3_NET) {
                            tcp->th_dport = TCP_PORT_4445_NET;
                        }
                    }
                }

                file_stream << buffer;

                return ndisapi::fastio_packet_filter::packet_action::pass;
			}, 
            true);

		if (ndis_api->IsDriverLoaded())
		{
			std::cout << "WinpkFilter is loaded" << std::endl << std::endl;
		}
		else
		{
			std::cout << "WinpkFilter is not loaded" << std::endl << std::endl;
			return 1;
		}

        std::cout << "Available network interfaces:" << std::endl << std::endl;
        size_t index = 0;
        for (auto& e : ndis_api->get_interface_names_list())
        {
            std::cout << ++index << ")\t" << e << std::endl;
        }

#if 1
        index = 7;
        std::cout << "Listening on: " << ndis_api->get_interface_names_list()[index - 1] << std::endl;
#else
		std::cout << std::endl << "Select interface to filter:";
		std::cin >> index;
#endif

		if (index > ndis_api->get_interface_names_list().size())
		{
			std::cout << "Wrong parameter was selected. Out of range." << std::endl;
			return 0;
		}

#if 1
        file_name = "d:\\temp\\capture.pcap";
#else
		std::cout << std::endl << "Enter filename to save the capture:";
		std::cin >> file_name;
#endif

		file_stream.open(file_name);

		if (!file_stream)
		{
			std::cout << "Failed to open " << file_name << "\n";
			return 0;
		}

		ndis_api->start_filter(index - 1);

		std::cout << "Press any key to stop filtering" << std::endl;

		std::ignore = _getch();

		std::cout << "Exiting..." << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception occurred: " << ex.what() << std::endl;
	}

	return 0;
}
