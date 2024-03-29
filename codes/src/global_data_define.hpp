#pragma once
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