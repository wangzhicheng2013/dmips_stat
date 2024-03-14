#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/times.h>
#include <iostream>
#include <thread>
#define QNX_OS
#ifdef QNX_OS
#include <sys/neutrino.h>
#endif
const static int Mic_secs_Per_Second = 1000000;
typedef enum {
    Ident_1, Ident_2, Ident_3, Ident_4, Ident_5
} Enumeration;
typedef int     One_Thirty;
typedef int     One_Fifty;
typedef char    Capital_Letter;
typedef int     Boolean;
typedef char    Str_30 [31];
typedef int     Arr_1_Dim [50];
typedef int     Arr_2_Dim [50] [50];

typedef struct record {
    struct record *Ptr_Comp;
    Enumeration    Discr;
    union {
        struct {
            Enumeration Enum_Comp;
            int         Int_Comp;
            char        Str_Comp [31];
        } var_1;
        struct {
            Enumeration E_Comp_2;
            char        Str_2_Comp [31];
        } var_2;
        struct {
            char        Ch_1_Comp;
            char        Ch_2_Comp;
        } var_3;
    } variant;
} Rec_Type, *Rec_Pointer;

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [50];
int             Arr_2_Glob [50] [50];

struct tms      time_info;
int             Too_Small_Time = 2 * HZ;

long            Begin_Time,
                End_Time,
                User_Time;
float           Microseconds,
                Dhrystones_Per_Second;

int DHRY_ITERS = 50000000;
int MHZ = 0;
int CPU_NO = 0;
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
bool Func_3(Enumeration Enum_Par_Val);
void Proc_3(Rec_Pointer *Ptr_Ref_Par);
void Proc_6(Enumeration  Enum_Val_Par, Enumeration *Enum_Ref_Par);
void Proc_7(One_Fifty Int_1_Par_Val, One_Fifty Int_2_Par_Val, One_Fifty* Int_Par_Ref);

void Proc_1(Rec_Pointer Ptr_Val_Par) {
    Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;
    *Ptr_Val_Par->Ptr_Comp = *Ptr_Glob; 
    Ptr_Val_Par->variant.var_1.Int_Comp = 5;
    Next_Record->variant.var_1.Int_Comp = Ptr_Val_Par->variant.var_1.Int_Comp;
    Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
    Proc_3 (&Next_Record->Ptr_Comp);
    if (Next_Record->Discr == Ident_1) {
        Next_Record->variant.var_1.Int_Comp = 6;
        Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp, &Next_Record->variant.var_1.Enum_Comp);
        Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
        Proc_7 (Next_Record->variant.var_1.Int_Comp, 10, &Next_Record->variant.var_1.Int_Comp);
    }
    else {
         *Ptr_Val_Par = *Ptr_Val_Par->Ptr_Comp;
    }
}
void Proc_2(One_Fifty* Int_Par_Ref) {
    One_Fifty Int_Loc = *Int_Par_Ref + 10;
    Enumeration Enum_Loc;
    do {
        if (Ch_1_Glob == 'A') {
            Int_Loc -= 1;
            *Int_Par_Ref = Int_Loc - Int_Glob;
            Enum_Loc = Ident_1;
        }
    }  while (Enum_Loc != Ident_1);
}
void Proc_3(Rec_Pointer* Ptr_Ref_Par) {
    if (Ptr_Glob != nullptr) {
        *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
    }
    Proc_7(10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
}
void Proc_4() {
    bool Bool_Loc = (Ch_1_Glob == 'A');
    Bool_Glob = Bool_Loc | Bool_Glob;
    Ch_2_Glob = 'B';
}
void Proc_5() {
    Ch_1_Glob = 'A';
    Bool_Glob = false;
}
void Proc_6(Enumeration Enum_Val_Par, Enumeration* Enum_Ref_Par) {
    *Enum_Ref_Par = Enum_Val_Par;
    if (!Func_3(Enum_Val_Par)) {
        *Enum_Ref_Par = Ident_4;
    }
    switch (Enum_Val_Par) {
    case Ident_1:
        *Enum_Ref_Par = Ident_1;
        break;
    case Ident_2:
        if (Int_Glob > 100) {
            *Enum_Ref_Par = Ident_1;
        }
        else {
            *Enum_Ref_Par = Ident_4;
        }
        break;
    case Ident_3:
        *Enum_Ref_Par = Ident_2;
        break;
    case Ident_4:
        break;
    case Ident_5:
        *Enum_Ref_Par = Ident_3;
        break;
    }
}
void Proc_7(One_Fifty Int_1_Par_Val, One_Fifty Int_2_Par_Val, One_Fifty* Int_Par_Ref) {
    One_Fifty Int_Loc = Int_1_Par_Val + 2;
    *Int_Par_Ref = Int_2_Par_Val + Int_Loc;
}
void Proc_8(Arr_1_Dim Arr_1_Par_Ref,
            Arr_2_Dim Arr_2_Par_Ref,
            int Int_1_Par_Val,
            int Int_2_Par_Val) {
    One_Fifty Int_Index;
    One_Fifty Int_Loc;
    Int_Loc = Int_1_Par_Val + 5;
    Arr_1_Par_Ref[Int_Loc] = Int_2_Par_Val;
    Arr_1_Par_Ref[Int_Loc + 1] = Arr_1_Par_Ref[Int_Loc];
    Arr_1_Par_Ref[Int_Loc + 30] = Int_Loc;
    for (Int_Index = Int_Loc;Int_Index <= Int_Loc + 1;++Int_Index) {
        Arr_2_Par_Ref[Int_Loc][Int_Index] = Int_Loc;
    }
    Arr_2_Par_Ref[Int_Loc][Int_Loc-1] += 1;
    Arr_2_Par_Ref[Int_Loc+20][Int_Loc] = Arr_1_Par_Ref[Int_Loc];
    Int_Glob = 5;
}
Enumeration Func_1(Capital_Letter Ch_1_Par_Val, Capital_Letter Ch_2_Par_Val) {
    if (Ch_1_Par_Val != Ch_2_Par_Val) {
        return Ident_1;
    }
    else {
        Ch_1_Glob = Ch_1_Par_Val;
        return Ident_2;
    }
}
bool Func_2 (Str_30 Str_1_Par_Ref, Str_30 Str_2_Par_Ref) {
    One_Thirty Int_Loc = 2;
    Capital_Letter Ch_Loc = 0;
    while (Int_Loc <= 2) {
        if (Func_1(Str_1_Par_Ref[Int_Loc], Str_2_Par_Ref[Int_Loc + 1]) == Ident_1) {
            Ch_Loc = 'A';
            Int_Loc += 1;
        }
    }
    if (Ch_Loc >= 'W' && Ch_Loc < 'Z') {
        Int_Loc = 7;
    }
    if (Ch_Loc == 'R') {
        return true;
    }
    else {
        if (strcmp(Str_1_Par_Ref, Str_2_Par_Ref) > 0) {
            Int_Loc += 7;
            Int_Glob = Int_Loc;
            return true;
        }
        else {
            return false;
        }
    } 
}
bool Func_3(Enumeration Enum_Par_Val) {
    return Ident_3 == Enum_Par_Val;
}
void dhrystone(int cpu_no) {
    if (true == bind_cpu(cpu_no)) {
        printf("bind cpu:%d success!\n", cpu_no);
    }
    One_Fifty       Int_1_Loc;
    One_Fifty       Int_2_Loc;
    One_Fifty       Int_3_Loc;
    char            Ch_Index;
    Enumeration     Enum_Loc;
    Str_30          Str_1_Loc;
    Str_30          Str_2_Loc;
    int             Run_Index;
    int             Number_Of_Runs;

    Next_Ptr_Glob = (Rec_Pointer)malloc(sizeof (Rec_Type));
    if (nullptr == Next_Ptr_Glob) {
        perror("malloc failed!\n");
        exit(0);
    }
    Ptr_Glob = (Rec_Pointer)malloc(sizeof (Rec_Type));
    if (nullptr == Ptr_Glob) {
        perror("malloc failed!\n");
        exit(0);       
    }
    Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
    Ptr_Glob->Discr                       = Ident_1;
    Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
    Ptr_Glob->variant.var_1.Int_Comp      = 40;
    strcpy (Ptr_Glob->variant.var_1.Str_Comp, "DHRYSTONE PROGRAM, SOME STRING");
    strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");
    Arr_2_Glob [8][7] = 10;
    printf ("\n");
    printf ("Dhrystone Benchmark, Version 2.2 (Language: C++)\n");
    printf ("\n");
    printf ("Program compiled without 'register' attribute\n");
    printf ("\n");
    Number_Of_Runs = DHRY_ITERS;
    printf ("Execution starts, %d runs through Dhrystone\n", Number_Of_Runs);
    times(&time_info);
    Begin_Time = (long)time_info.tms_utime;
    for (Run_Index = 1;Run_Index <= Number_Of_Runs;++Run_Index) {
        Proc_5();
        Proc_4();
        Int_1_Loc = 2;
        Int_2_Loc = 3;
        strcpy(Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
        Enum_Loc = Ident_2;
        Bool_Glob = !Func_2(Str_1_Loc, Str_2_Loc);
        while (Int_1_Loc < Int_2_Loc) {
            Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
            Proc_7(Int_1_Loc, Int_2_Loc, &Int_3_Loc);
            Int_1_Loc += 1;
        }
        Proc_8(Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
        Proc_1 (Ptr_Glob);
        for (Ch_Index = 'A';Ch_Index <= Ch_2_Glob;++Ch_Index) {
            if (Enum_Loc == Func_1 (Ch_Index, 'C')) {
                Proc_6(Ident_1, &Enum_Loc);
                strcpy(Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
                Int_2_Loc = Run_Index;
                Int_Glob = Run_Index;
            }
        }
        Int_2_Loc = Int_2_Loc * Int_1_Loc;
        Int_1_Loc = Int_2_Loc / Int_3_Loc;
        Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
        Proc_2(&Int_1_Loc);
    }
    times (&time_info);
    End_Time = (long) time_info.tms_utime;
    printf ("Execution ends\n");
    printf ("\n");
    printf ("Final values of the variables used in the benchmark:\n");
    printf ("\n");
    printf ("Int_Glob:            %d\n", Int_Glob);
    printf ("        should be:   %d\n", 5);
    printf ("Bool_Glob:           %d\n", Bool_Glob);
    printf ("        should be:   %d\n", 1);
    printf ("Ch_1_Glob:           %c\n", Ch_1_Glob);
    printf ("        should be:   %c\n", 'A');
    printf ("Ch_2_Glob:           %c\n", Ch_2_Glob);
    printf ("        should be:   %c\n", 'B');
    printf ("Arr_1_Glob[8]:       %d\n", Arr_1_Glob[8]);
    printf ("        should be:   %d\n", 7);
    printf ("Arr_2_Glob[8][7]:    %d\n", Arr_2_Glob[8][7]);
    printf ("        should be:   Number_Of_Runs + 10\n");
    printf ("Ptr_Glob->\n");
    printf ("  Ptr_Comp:          %p\n", Ptr_Glob->Ptr_Comp);
    printf ("        should be:   (implementation-dependent)\n");
    printf ("  Discr:             %d\n", Ptr_Glob->Discr);
    printf ("        should be:   %d\n", 0);
    printf ("  Enum_Comp:         %d\n", Ptr_Glob->variant.var_1.Enum_Comp);
    printf ("        should be:   %d\n", 2);
    printf ("  Int_Comp:          %d\n", Ptr_Glob->variant.var_1.Int_Comp);
    printf ("        should be:   %d\n", 17);
    printf ("  Str_Comp:          %s\n", Ptr_Glob->variant.var_1.Str_Comp);
    printf ("        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
    printf ("Next_Ptr_Glob->\n");
    printf ("  Ptr_Comp:          %p\n",  Next_Ptr_Glob->Ptr_Comp);
    printf ("        should be:   (implementation-dependent), same as above\n");
    printf ("  Discr:             %d\n", Next_Ptr_Glob->Discr);
    printf ("        should be:   %d\n", 0);
    printf ("  Enum_Comp:         %d\n", Next_Ptr_Glob->variant.var_1.Enum_Comp);
    printf ("        should be:   %d\n", 1);
    printf ("  Int_Comp:          %d\n", Next_Ptr_Glob->variant.var_1.Int_Comp);
    printf ("        should be:   %d\n", 18);
    printf ("  Str_Comp:          %s\n", Next_Ptr_Glob->variant.var_1.Str_Comp);
    printf ("        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
    printf ("Int_1_Loc:           %d\n", Int_1_Loc);
    printf ("        should be:   %d\n", 5);
    printf ("Int_2_Loc:           %d\n", Int_2_Loc);
    printf ("        should be:   %d\n", 13);
    printf ("Int_3_Loc:           %d\n", Int_3_Loc);
    printf ("        should be:   %d\n", 7);
    printf ("Enum_Loc:            %d\n", Enum_Loc);
    printf ("        should be:   %d\n", 1);
    printf ("Str_1_Loc:           %s\n", Str_1_Loc);
    printf ("        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n");
    printf ("Str_2_Loc:           %s\n", Str_2_Loc);
    printf ("        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n");
    printf ("\n");

    User_Time = End_Time - Begin_Time;
    if (User_Time < Too_Small_Time) {
        printf ("Measured time too small to obtain meaningful results\n");
        printf ("Please increase number of runs\n");
        printf ("\n");
    }
    else {
        Microseconds = (float)User_Time * Mic_secs_Per_Second / ((float) HZ * ((float) Number_Of_Runs));
        Dhrystones_Per_Second = ((float)HZ * (float) Number_Of_Runs) / (float) User_Time;
        printf ("Microseconds for one run through Dhrystone: ");
        printf ("%d \n", (int)Microseconds);
        printf ("Dhrystones per Second:                      ");
        printf ("%f\n", Dhrystones_Per_Second);
        printf ("DMIPS:%f \n", Dhrystones_Per_Second / 1575);
        printf ("KDMIPS:%f \n", Dhrystones_Per_Second / 1575 / 1000);
        printf ("DMIPS/Mhz:%f\n", Dhrystones_Per_Second / 1575 / MHZ);
        printf ("\n");
    }
    free(Next_Ptr_Glob);
    free(Ptr_Glob);
}
struct option long_options[] = {
    { "cpu", required_argument, 0, 'c' },
    { "loops", required_argument, 0, 'l' },
    { "mhz", required_argument, 0, 'm' },
    { "help", no_argument, 0, 'h' },
    { 0, 0, 0, 0 }
}; 
void parse_cmd_line(int argc, char** argv) {
    int opt = 0, index = 0;
    while ((opt = getopt_long_only(argc, argv, "c:l:m:h:", long_options, &index)) != -1) {
        switch (index)
        {
        case 0:
            if (optarg) {
                CPU_NO = atoi(optarg);
            }
            break;
        case 1:
            if (optarg) {
                DHRY_ITERS = atoi(optarg);
            }
            break;
        case 2:
            if (optarg) {
                MHZ = atoi(optarg);
            }
            break;
        case 3:
            printf("usage:./dmips_stat -cpu_id=0 -loops=50000 -mhz=1000\n");
            exit(0);
            break;
        default:
            break;
        }
    }
}
int main(int argc, char** argv) {
    parse_cmd_line(argc, argv);
    if (0 == MHZ) {
        MHZ = get_cpu_mhz(CPU_NO);
        printf("current cpu main frequency:%d", MHZ);
    }
    std::thread dhrystone_thread(dhrystone, CPU_NO);
    if (dhrystone_thread.joinable()) {
        dhrystone_thread.join();
    }

    return 0;
}