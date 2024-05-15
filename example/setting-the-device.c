#include <mimikyu.h>
#include <mimikyu/pcap.h>

int main(int argc, char ** argv) {

    if(mimikyu_pcap_init() == success) {
        if(mimikyu_pcap_if_exist("eth0")) {
            printf("eth0 is exist\n");
        } else {
            printf("eth0 is not exist\n");
        }
    }

    return 0;
}