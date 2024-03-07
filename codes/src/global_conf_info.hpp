#pragma once
struct conf_info {
    int periods_per_second = 100;
    int cpu_id = 1;
    int loops = 50000;
    int mhz = 0;
};
conf_info GLOBAL_CONF_INFO;