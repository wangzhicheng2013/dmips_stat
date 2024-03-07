#include <getopt.h>
#include "global_conf_info.hpp"
#include "dmips_stat.hpp"
#include "public_tools.hpp"
struct option long_options[] = {
    { "periods", required_argument, 0, 'p' },
    { "cpu", required_argument, 0, 'c' },
    { "loops", required_argument, 0, 'l' },
    { "mhz", required_argument, 0, 'm' },
    { "help", no_argument, 0, 'h' },
    { 0, 0, 0, 0 }
}; 
void parse_cmd_line(int argc, char** argv) {
    int opt = 0, index = 0;
    while ((opt = getopt_long_only(argc, argv, "p:c:l:m:h:", long_options, &index)) != -1) {
        switch (index)
        {
        case 0:
            if (optarg) {
                GLOBAL_CONF_INFO.periods_per_second = atoi(optarg);
            }
            break;
        case 1:
            if (optarg) {
                GLOBAL_CONF_INFO.cpu_id = atoi(optarg);
            }
            break;
        case 2:
            if (optarg) {
                GLOBAL_CONF_INFO.loops = atoi(optarg);
            }
            break;
        case 3:
            if (optarg) {
                GLOBAL_CONF_INFO.mhz = atoi(optarg);
            }
            break;
        case 4:
            printf("usage:./dmips_stat -periods_per_second=100 -cpu_id=0 -loops=50000 -mhz=1000\n");
            exit(0);
            break;
        default:
            break;
        }
    }
}
void stat_thread() {
    if (true == bind_cpu(GLOBAL_CONF_INFO.cpu_id)) {
        LOG_I("bind cpu:%d success!", GLOBAL_CONF_INFO.cpu_id);
    }
    DMIPS_STAT.do_stat();
}
int main(int argc, char** argv) {
    parse_cmd_line(argc, argv);
    DMIPS_STAT.set_hz(GLOBAL_CONF_INFO.periods_per_second);
    DMIPS_STAT.set_number_of_runs(GLOBAL_CONF_INFO.loops);
    if (0 == GLOBAL_CONF_INFO.mhz) {
        GLOBAL_CONF_INFO.mhz = get_cpu_mhz(GLOBAL_CONF_INFO.cpu_id);
        LOG_I("current cpu main frequency:%d", GLOBAL_CONF_INFO.mhz);
        DMIPS_STAT.set_mhz(GLOBAL_CONF_INFO.mhz);
    }
    if (false == DMIPS_STAT.init()) {
        return -1;
    }
    std::thread st(stat_thread);
    if (st.joinable()) {
        st.join();
    }

    return 0;
}