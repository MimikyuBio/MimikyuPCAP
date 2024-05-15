/**
 * @file        mimikyu/pcap.h
 * @brief       패킷 캡쳐 라이브러리 PCAP 을 사용하여 ...
 * @details
 * 
 * @author      mimikyu <mimikyu@snorlax.bio>
 * @since       May 15, 2024
 */

#ifndef   __MIMIKYU_PCAP__PCAP__H__
#define   __MIMIKYU_PCAP__PCAP__H__

#include <mimikyu.h>

#include <pcap/pcap.h>

extern int mimikyu_pcap_init(void);
extern int mimikyu_pcap_if_exist(const char * name);

extern void mimikyu_pcap_debug_if_all(void);
extern void mimikyu_pcap_debug_if(pcap_if_t * device);

#endif // __MIMIKYU_PCAP__PCAP__H__