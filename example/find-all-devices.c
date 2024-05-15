#include <mimikyu/pcap.h>

int main(int argc, char ** argv) {
    if(mimikyu_pcap_init() == success) {
        mimikyu_pcap_debug_if_all();
    }
    return 0;
}