/**
 * @file            mimikyu/pcap.c
 * @brief           
 * @details
 * 
 * @author          mimikyu <mimikyu@snorlax.bio>
 * @since           May 15, 2024
 */

#include <mimikyu.h>

#include <string.h>

#include "pcap.h"

extern int mimikyu_pcap_init(void) {
    char errbuf[PCAP_ERRBUF_SIZE];

    mimikyu_string_init(errbuf);

    if(pcap_init(PCAP_CHAR_ENC_LOCAL, errbuf) == 0) {
        printf("verbose: succeed to pcap_init(...)\n");

        return success;
    }

    printf("error: fail to pcap_init(...) caused by %s\n", errbuf);

    return fail;
}

extern int mimikyu_pcap_if_exist(const char * name) {
    pcap_if_t * devices = nil;
    char errbuf[PCAP_ERRBUF_SIZE];

    mimikyu_string_init(errbuf);

    if(pcap_findalldevs(&devices, errbuf) == 0) {
        for(pcap_if_t * device = devices; device != nil; device = device->next) {
            /**
             * TODO: IMPLEMENT DEBUG
             */

            mimikyu_pcap_debug_if(device);
            if(strcmp(devices->name, name) == 0) {
                pcap_freealldevs(devices);
                return true;
            }
        }

        pcap_freealldevs(devices);
        return false;
    }

    printf("error: fail to pcap_findalldevs(...) caused by %s\n", errbuf);

    return false;
}

extern void mimikyu_pcap_debug_if_all(void) {
    pcap_if_t * devices = nil;
    char errbuf[PCAP_ERRBUF_SIZE];

    mimikyu_string_init(errbuf);
    
    if(pcap_findalldevs(&devices, errbuf) == 0) {
        for(pcap_if_t * device = devices; device != nil; device = device->next) {
            mimikyu_pcap_debug_if(device);
        }
        pcap_freealldevs(devices);
        return;
    }

    printf("error: fail to pcap_findalldevs(...) caused by %s\n", errbuf);
}

extern void mimikyu_pcap_debug_if(pcap_if_t * device) {
    printf("device: name: %s\n", device->name);
    printf("device: description: %s\n", device->description ? device->description : "");
    printf("device: flag: loopback: %s\n", device->flags & PCAP_IF_LOOPBACK ? "o" : "x");
    printf("device: flag: up: %s\n", device->flags & PCAP_IF_UP ? "o" : "x");
    printf("device: flag: wireless: %s\n", device->flags & PCAP_IF_WIRELESS ? "o" : "x");
    printf("device: flag: run: %s\n", device->flags & PCAP_IF_RUNNING ? "o" : "x");
    uint32_t status = (device->flags & PCAP_IF_CONNECTION_STATUS);
    if(status == PCAP_IF_CONNECTION_STATUS_CONNECTED) {
        printf("device: flag: status: connected\n");
    } else if(status == PCAP_IF_CONNECTION_STATUS_DISCONNECTED) {
        printf("device: flag: status: disconnected\n");
    } else if(status == PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE) {
        printf("device: flag: status: not applicable\n");
    } else {
        printf("device: flag: status: unknown\n");
    }
}