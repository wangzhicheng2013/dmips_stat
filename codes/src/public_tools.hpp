#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sched.h>
#include <thread>
//#define QNX_OS
#define ANDROID_OS
#ifdef QNX_OS
#include <sys/neutrino.h>
#endif
static inline bool bind_cpu(int cpu_no) {
#ifdef QNX_OS
    if (cpu_no < 0 || cpu_no >= 8) {
        return false;
    }
    int run_mask = (0x00000001 << cpu_no);
    // set current threads to cpu
    return ThreadCtl(_NTO_TCTL_RUNMASK, (void *)(run_mask)) != -1;
#else
    cpu_set_t mask = { 0 };
    CPU_SET(cpu_no, &mask);
    // set current process to cpu
    return sched_setaffinity(0, sizeof(mask), &mask) >= 0;
#endif
}
static int get_cpu_mhz(int cpu_no) {
    char cmd[128] = { 0 };
    char buf[256] = { 0 };
    FILE *fp = nullptr;
#ifdef QNX_OS
    // 8295 qnx cpu as following
    /*
    Processor1: 1091556528 Octa Kryo-695 Gold 2092MHz FPU
    Processor2: 1091556528 Octa Kryo-695 Gold 2092MHz FPU
    Processor3: 1091556528 Octa Kryo-695 Gold 2092MHz FPU
    Processor4: 1091556528 Octa Kryo-695 Gold 2092MHz FPU
    Processor5: 1091556544 Octa Kryo-695 Gold Plus 2380MHz FPU
    Processor6: 1091556544 Octa Kryo-695 Gold Plus 2380MHz FPU
    Processor7: 1091556544 Octa Kryo-695 Gold Plus 2380MHz FPU
    Processor8: 1091556544 Octa Kryo-695 Gold Plus 2380MHz FPU
    */
    snprintf(cmd, sizeof(cmd), "pidin info | grep Processor%d | grep MHz", cpu_no + 1);
    fp = popen(cmd, "r");
    if (!fp) {
        return 0;
    }
    fgets(buf, sizeof(buf) - 1, fp);
    fclose(fp);
    const char* ptr = strstr(buf, "MHz");
    if (nullptr == ptr) {
        return 0;
    }
    while (*ptr != ' ') {
        if (ptr == buf) {
            return 0;
        }
        --ptr;
    }
    return atoi(ptr + 1);
#elif defined(ANDROID_OS)
    snprintf(cmd, sizeof(cmd), "cat /sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", cpu_no);
    fp = popen(cmd, "r");
    if (!fp) {
        return 0;
    }
    fgets(buf, sizeof(buf) - 1, fp);
    fclose(fp);
    return atoi(buf) / 1000;
#else
    snprintf(cmd, sizeof(cmd), "cat /proc/cpuinfo | grep \"cpu MHz\" | sed -e 's/.*:[^0-9]//' | head -n %d | tail -n 1", cpu_no + 1);
    fp = popen(cmd, "r");
    if (!fp) {
        return 0;
    }
    fgets(buf, sizeof(buf) - 1, fp);
    fclose(fp);
    return atoi(buf);   
#endif
    return 0;
}