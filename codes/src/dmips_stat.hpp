#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>

#include "color_log.hpp"
#include "global_data_define.hpp"
class dmips_stat {
public:
    static dmips_stat& get_instance() {
        static dmips_stat instance;
        return instance;
    }
private:
    dmips_stat() = default;
    virtual ~dmips_stat() {
        uninit();
    }
private:
    int too_small_time_ = 2 * HZ;
    struct tms time_info_ = { 0 };
    long begin_time_ = 0, end_time_ = 0, user_time_ = 0;
    float microseconds_ = 0, dhrystones_per_second_ = 0;
    const float mic_secs_per_second_ = 1000000.0;
    int number_of_runs_ = 50000;

    int int_glob_ = 0;
    bool bool_glob_ = false;
    char ch_1_glob_ = 0, ch_2_glob_ = 0;
    int arr_1_glob_[50] = { 0 };
    int arr_2_glob_[50] [50] = {};

    Rec_Pointer ptr_glob_ = nullptr, next_ptr_glob_ = nullptr;

    One_Fifty int_1_loc_ = 0;
    One_Fifty int_2_loc_ = 0;
    One_Fifty int_3_loc_ = 0;
    char ch_index_ = 0;
    Enumeration enum_loc_ = Ident_1;
    Str_30 str_1_loc_ = { 0 };
    Str_30 str_2_loc_ = { 0 };
    int run_index_ = 0;

    bool done_ = false;
    int hz_ = HZ;
    int mhz_ = 1000;
private:
    /*************************************************/
    /* executed three times                                         */
    /* first call:      Ch_1_Par_Val == 'H', Ch_2_Par_Val == 'R'    */
    /* second call:     Ch_1_Par_Val == 'A', Ch_2_Par_Val == 'C'    */
    /* third call:      Ch_1_Par_Val == 'B', Ch_2_Par_Val == 'C'    */

    inline Enumeration func_1(Capital_Letter Ch_1_Par_Val, Capital_Letter Ch_2_Par_Val) {
        if (Ch_1_Par_Val != Ch_2_Par_Val) {
            /* then, executed */
            return Ident_1;
        }
        else  /* not executed */ {
            ch_1_glob_ = Ch_1_Par_Val;
            return Ident_2;
        }
    }
    /*************************************************/
    /* executed once */
    /* Str_1_Par_Ref == "DHRYSTONE PROGRAM, 1'ST STRING" */
    /* Str_2_Par_Ref == "DHRYSTONE PROGRAM, 2'ND STRING" */
    bool func_2(Str_30 Str_1_Par_Ref, Str_30 Str_2_Par_Ref) {
        One_Thirty Int_Loc = 2;
        Capital_Letter Ch_Loc = 0;
        /* loop body executed once */
        while (Int_Loc <= 2) {
            /* then, executed */
            if (func_1(Str_1_Par_Ref[Int_Loc], Str_2_Par_Ref[Int_Loc + 1]) == Ident_1) {
                Ch_Loc = 'A';
                Int_Loc += 1;
            } /* if, while */
        }
        if (Ch_Loc >= 'W' && Ch_Loc < 'Z') {
            /* then, not executed */
            Int_Loc = 7;
        }
        if ('R' == Ch_Loc) {    /* then, not executed */
            return true;
        }
        else /* executed */ {
            if (strcmp (Str_1_Par_Ref, Str_2_Par_Ref) > 0) /* then, not executed */ {
                Int_Loc += 7;
                int_glob_ = Int_Loc;
                return true;
            }
            else { /* executed */
                return false;
            } /* if Ch_Loc */
        } 
    }
    inline bool func_3(Enumeration Enum_Par_Val) {
        return Ident_3 == Enum_Par_Val;
    }
    void proc_1(Rec_Pointer Ptr_Val_Par) {
        Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;  
        /* == Ptr_Glob_Next */
        /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
        /* corresponds to "rename" in Ada, "with" in Pascal           */
        *Ptr_Val_Par->Ptr_Comp = *ptr_glob_;
        Ptr_Val_Par->variant.var_1.Int_Comp = 5;
        Next_Record->variant.var_1.Int_Comp = Ptr_Val_Par->variant.var_1.Int_Comp;
        Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
        proc_3(&Next_Record->Ptr_Comp);
        /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp 
                        == Ptr_Glob->Ptr_Comp */
        if (Ident_1 == Next_Record->Discr) /* then, executed */ {
            Next_Record->variant.var_1.Int_Comp = 6;
            proc_6(Ptr_Val_Par->variant.var_1.Enum_Comp, &Next_Record->variant.var_1.Enum_Comp);
            Next_Record->Ptr_Comp = ptr_glob_->Ptr_Comp;
            proc_7(Next_Record->variant.var_1.Int_Comp, 10, &Next_Record->variant.var_1.Int_Comp);
        }
        else /* not executed */ {
            *Ptr_Val_Par = *Ptr_Val_Par->Ptr_Comp;
        }
    }
    /******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */
    void proc_2(One_Fifty *Int_Par_Ref) {
        One_Fifty Int_Loc = *Int_Par_Ref + 10;
        Enumeration Enum_Loc = Ident_1;
        do /* executed once */ {
            if ('A' == ch_1_glob_) /* then, executed */ {
                Int_Loc -= 1;
                *Int_Par_Ref = Int_Loc - int_glob_;
                Enum_Loc = Ident_1;
            } /* if */
        } while (Enum_Loc != Ident_1); /* true */
    }
    inline void proc_3(Rec_Pointer *Ptr_Ref_Par) {
        if (ptr_glob_ != nullptr) {    /* then, executed */
            *Ptr_Ref_Par = ptr_glob_->Ptr_Comp;
        }
        proc_7(10, int_glob_, &ptr_glob_->variant.var_1.Int_Comp);
    }
    inline void proc_4(void) {
        bool Bool_Loc = ('A' == ch_1_glob_);
        bool_glob_ = Bool_Loc | bool_glob_;
        ch_2_glob_ = 'B';
    }
    inline void proc_5(void) {
        ch_1_glob_ = 'A';
        bool_glob_ = false;
    }
    void proc_6(Enumeration  Enum_Val_Par, Enumeration *Enum_Ref_Par) {
        *Enum_Ref_Par = Enum_Val_Par;
        if (!func_3(Enum_Val_Par)) {
            *Enum_Ref_Par = Ident_4;
        }
        switch (Enum_Val_Par) {
        case Ident_1:
            *Enum_Ref_Par = Ident_1;
            break;
        case Ident_2:
            if (int_glob_ > 100) {
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
    /**********************************************/
    /* executed three times                                      */ 
    /* first call:      Int_1_Par_Val == 2, Int_2_Par_Val == 3,  */
    /*                  Int_Par_Ref becomes 7                    */
    /* second call:     Int_1_Par_Val == 10, Int_2_Par_Val == 5, */
    /*                  Int_Par_Ref becomes 17                   */
    /* third call:      Int_1_Par_Val == 6, Int_2_Par_Val == 10, */
    /*                  Int_Par_Ref becomes 18                   */
    inline void proc_7(One_Fifty Int_1_Par_Val,
                One_Fifty Int_2_Par_Val,
                One_Fifty *Int_Par_Ref) {
        One_Fifty Int_Loc = Int_1_Par_Val + 2;
        *Int_Par_Ref = Int_2_Par_Val + Int_Loc;
    }
    /*********************************************************************/
    /* executed once      */
    /* Int_Par_Val_1 == 3 */
    /* Int_Par_Val_2 == 7 */
    void proc_8(Arr_1_Dim Arr_1_Par_Ref,
                Arr_2_Dim Arr_2_Par_Ref,
                int Int_1_Par_Val,
                int Int_2_Par_Val) {
        One_Fifty Int_Index = 0;
        One_Fifty Int_Loc = Int_1_Par_Val + 5;
        Arr_1_Par_Ref [Int_Loc] = Int_2_Par_Val;
        Arr_1_Par_Ref [Int_Loc + 1] = Arr_1_Par_Ref [Int_Loc];
        Arr_1_Par_Ref [Int_Loc + 30] = Int_Loc;
        for (Int_Index = Int_Loc; Int_Index <= Int_Loc+1; ++Int_Index) {
            Arr_2_Par_Ref [Int_Loc] [Int_Index] = Int_Loc;
        }
        Arr_2_Par_Ref [Int_Loc] [Int_Loc-1] += 1;
        Arr_2_Par_Ref [Int_Loc+20] [Int_Loc] = Arr_1_Par_Ref [Int_Loc];
        int_glob_ = 5;
    }
    void show_stat_result() {
        LOG_I("Final values of the variables used in the benchmark:");
        LOG_I("Int_Glob:%d should be 5", int_glob_);
        LOG_I("Bool_Glob:%d should be:1", bool_glob_);
        LOG_I("Ch_1_Glob:%c should be:A", ch_1_glob_);
        LOG_I("Ch_2_Glob:%c should be:B", ch_2_glob_);
        LOG_I("Arr_1_Glob[8]:%d should be:7", arr_1_glob_[8]);
        LOG_I("Arr_2_Glob[8][7]:%d should be:%d", arr_2_glob_[8][7], number_of_runs_ + 10);
        LOG_I("Ptr_Glob->");
        LOG_I("Ptr_Comp:%p should be:(implementation-dependent)", ptr_glob_->Ptr_Comp);
        LOG_I("Discr:%d should be:0", ptr_glob_->Discr);
        LOG_I("Enum_Comp:%d should be:2", ptr_glob_->variant.var_1.Enum_Comp);
        LOG_I("Int_Comp:%d should be:17", ptr_glob_->variant.var_1.Int_Comp);
        LOG_I("Str_Comp:%s should be:DHRYSTONE PROGRAM, SOME STRING", ptr_glob_->variant.var_1.Str_Comp);
        LOG_I("Next_Ptr_Glob->");
        LOG_I("Ptr_Comp:%p should be:   (implementation-dependent), same as above", next_ptr_glob_->Ptr_Comp);
        LOG_I("Discr:%d should be:0", next_ptr_glob_->Discr);
        LOG_I("Enum_Comp:%d should be:1", next_ptr_glob_->variant.var_1.Enum_Comp);
        LOG_I("Int_Comp:%d should be:18", next_ptr_glob_->variant.var_1.Int_Comp);
        LOG_I("Str_Comp:%s should be:DHRYSTONE PROGRAM, SOME STRING", next_ptr_glob_->variant.var_1.Str_Comp);
        LOG_I("Int_1_Loc:%d should be:5", int_1_loc_);
        LOG_I("Int_2_Loc:%d should be:13", int_2_loc_);
        LOG_I("Int_3_Loc:%d should be:7", int_3_loc_);
        LOG_I("Enum_Loc:%d should be:1", enum_loc_);
        LOG_I("Str_1_Loc:%s should be:DHRYSTONE PROGRAM, 1'ST STRING", str_1_loc_);
        LOG_I("Str_2_Loc:%s should be:DHRYSTONE PROGRAM, 2'ND STRING", str_2_loc_);

        microseconds_ = (float) user_time_ * mic_secs_per_second_ / ((float) hz_ * ((float) number_of_runs_));
        dhrystones_per_second_ = ((float) hz_ * (float) number_of_runs_) / (float) user_time_;
        LOG_I("Microseconds for one run through Dhrystone:");
        LOG_I("%f", microseconds_);
        LOG_I("Dhrystones per Second:");
        LOG_I("%f", dhrystones_per_second_);
        float dmips = dhrystones_per_second_ / 1757;
        LOG_I("DMIPS:%f", dmips);
        LOG_I("DMIPS/Mhz:%f", dmips / mhz_);
    }
public:
    inline const char* version() const {
        return "C++, Version 2.2";
    }
    bool init() {
        next_ptr_glob_ = (Rec_Pointer) malloc (sizeof (Rec_Type));
        if (nullptr == next_ptr_glob_) {
            LOG_E("malloc failed!");
            return false;
        }
        ptr_glob_ = (Rec_Pointer) malloc (sizeof (Rec_Type));
        if (nullptr == ptr_glob_) {
            LOG_E("malloc failed!");
            return false;
        }
        ptr_glob_->Ptr_Comp = next_ptr_glob_;
        ptr_glob_->Discr = Ident_1;
        ptr_glob_->variant.var_1.Enum_Comp = Ident_3;
        ptr_glob_->variant.var_1.Int_Comp = 40;
        strncpy (ptr_glob_->variant.var_1.Str_Comp, "DHRYSTONE PROGRAM, SOME STRING", sizeof(ptr_glob_->variant.var_1.Str_Comp) - 1);
        strncpy (str_1_loc_, "DHRYSTONE PROGRAM, 1'ST STRING", sizeof(str_1_loc_) - 1);
        arr_2_glob_ [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */
        LOG_I("Dhrystone Benchmark, Version:%s", version());
        LOG_I("Using hz:%d", hz_);
        if (hz_ <= 0) {
            LOG_E("hz:%d invalid!", hz_);
            return false;
        }
        if (mhz_ <= 0) {
            LOG_E("mhz:%d invalid!", mhz_);
            return false;
        }
        done_ = false;
        return true;
    }
    void uninit() {
        if (next_ptr_glob_ != nullptr) {
            free(next_ptr_glob_);
            next_ptr_glob_ = nullptr;
        }
        if (ptr_glob_ != nullptr) {
            free(ptr_glob_);
            ptr_glob_ = nullptr;
        }
        LOG_I("uninit dmips stat success!");
    }
    inline void start_timer() {
        times(&time_info_);
        begin_time_ = (long)time_info_.tms_utime;
    }
    inline void stop_timer() {
        times(&time_info_);
        end_time_ = (long)time_info_.tms_utime;
    }
    inline void set_number_of_runs(int n) {
        number_of_runs_ = n;
    }
    inline void set_hz(int val) {
        hz_ = val;
    }
    inline void set_mhz(int val) {
        mhz_ = val;
    }
    void do_stat() {
        while (!done_) {
            arr_2_glob_ [8][7] = 10;
            LOG_I("Trying %d runs through Dhrystone:", number_of_runs_);
            start_timer();
            for (run_index_ = 1; run_index_ <= number_of_runs_; ++run_index_) {
                proc_5();
                proc_4();
                /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
                int_1_loc_ = 2;
                int_2_loc_ = 3;
                strcpy(str_2_loc_, "DHRYSTONE PROGRAM, 2'ND STRING");
                enum_loc_ = Ident_2;
                bool_glob_ = ! func_2 (str_1_loc_, str_2_loc_);
                /* Bool_Glob == 1 */
                while (int_1_loc_ < int_2_loc_)  /* loop body executed once */ {
                    int_3_loc_ = 5 * int_1_loc_ - int_2_loc_;
                    /* Int_3_Loc == 7 */
                    proc_7(int_1_loc_, int_2_loc_, &int_3_loc_);
                    /* Int_3_Loc == 7 */
                    int_1_loc_ += 1;
                } /* while */
                /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
                proc_8(arr_1_glob_, arr_2_glob_, int_1_loc_, int_3_loc_);
                /* Int_Glob == 5 */
                proc_1(ptr_glob_);
                /* loop body executed twice */
                for (ch_index_ = 'A'; ch_index_ <= ch_2_glob_; ++ch_index_) {
                    if (enum_loc_ == func_1 (ch_index_, 'C')) /* then, not executed */ {
                        proc_6(Ident_1, &enum_loc_);
                        strcpy(str_2_loc_, "DHRYSTONE PROGRAM, 3'RD STRING");
                        int_2_loc_ = run_index_;
                        int_glob_ = run_index_;
                    }
                }
                /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
                int_2_loc_ = int_2_loc_ * int_1_loc_;
                int_1_loc_ = int_2_loc_ / int_3_loc_;
                int_2_loc_ = 7 * (int_2_loc_ - int_3_loc_) - int_1_loc_;
                /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
                proc_2(&int_1_loc_);
                /* Int_1_Loc == 5 */
            } /* loop "for Run_Index" */
            stop_timer();
            user_time_ = end_time_ - begin_time_;
            if (user_time_ < too_small_time_) {
                number_of_runs_ *= 10;
                LOG_W("Measured time too small to obtain meaningful results, now to enlarge number of runs:%d", number_of_runs_);
            }
            else {
                done_ = true;
            }
        }
        show_stat_result();
    }
};
#define DMIPS_STAT dmips_stat::get_instance()