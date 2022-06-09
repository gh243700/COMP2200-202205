#include "translate.h"
#include <stdio.h>
#include <limits.h>

#define LENGTH (512)

static int refine_set(int* length, char* refined_set, const char* const set, int can_be_scope, error_code_t* code);
static char get_escape(const char c);

int translate(int argc, const char** argv)
{   
    int i;
    int j;

    char* ptr0;
    int has_char;

    char c;
    error_code_t error_code;

    char refined_set1[LENGTH];
    char refined_set2[LENGTH];     
    
    int length1 = 0;
    int length2 = 0;

    int is_case_sensitive = FALSE;

    const char* set1;
    const char* set2;

    if (argc == 4) {
        if (**(argv + 1) != '-') {
            goto label1;
        } 
        if (*(*(argv + 1) + 1) != 'i') {
            return ERROR_CODE_INVALID_FLAG;
        }
    
        is_case_sensitive = TRUE;
    
        set1 = *(argv + 2);
        set2 = *(argv + 3);
        
    } else if (argc > 4 || argc < 3) {
label1:
        return ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
    } else {
        set1 = *(argv + 1);
        set2 = *(argv + 2);
    }

    if (!refine_set(&length1, refined_set1, set1, FALSE, &error_code) || !refine_set(&length2, refined_set2, set2, FALSE, &error_code)) {
        return error_code;
    }
    
    if (length1 > length2) {
        for (i = length2; i < length1; i++) {
            refined_set2[i] = refined_set2[length2 - 1];
        } 
    }

    refined_set2[length1] = '\0';
    length2 = length1;

    ptr0 = refined_set1;
    for (i = 0; i < length1; i++) {
        char* ptr1 = refined_set1 + i + 1;
        for (j = i + 1; j < length1; j++) {
            if (*ptr0 == CHAR_MIN) {
                break;
            }
            if (*ptr0 == *ptr1) {
                *ptr0 = CHAR_MIN;
                refined_set2[ptr0 - refined_set1] = CHAR_MIN;
                break;
            }
            ptr1++;
        }
        ptr0++; 
    }

    c = fgetc(stdin);
    while (c != EOF) {
        has_char = FALSE;
        ptr0 = refined_set1;
        while (*ptr0 != '\0') {
            if ((is_case_sensitive) ? (0x20 | c) == (0x20 | *ptr0) : c == *ptr0) {
                printf("%c", refined_set2[ptr0 - refined_set1]); 
                has_char = TRUE;
                break;
            }     
            ptr0++;   
        }
        
        if (!has_char) {
            printf("%c", c);
        }

        c = fgetc(stdin);
    }

    return 0;
}


static int refine_set(int* length, char* refined_set, const char* const set, int can_be_scope, error_code_t* code)
{
    char next_char;
 
    if (*set == '\0') {
        return TRUE;
    }

    next_char = *(set + 1);

    if (*length >= 512 - 1) {
        *code = ERROR_CODE_ARGUMENT_TOO_LONG;
        return FALSE;
    }

    if (*set == '\\') {
        next_char = get_escape(next_char);
        if (next_char == ERROR_CODE_INVALID_FORMAT) {
            *code = ERROR_CODE_INVALID_FORMAT;
            return FALSE;
        }
        *refined_set++ = next_char;
        *refined_set = '\0';

        *length += 1;
        return refine_set(length, refined_set, set + 2, TRUE, code);
    }
    
    if (*set == '-' && can_be_scope && next_char != '\0') {
        int i;
        char c1 = *(refined_set - 1);
        int has_escape = FALSE;

        if (next_char == '\\') {
            next_char = get_escape(*(set + 2));
            has_escape = TRUE;
            if (next_char == ERROR_CODE_INVALID_FORMAT) {
                *code = ERROR_CODE_INVALID_FORMAT;
                return FALSE;
            }
        }    

        if (c1 > next_char) {
            *code = ERROR_CODE_INVALID_RANGE;
            return FALSE;
        }
        
        for (i = c1 + 1; i <= next_char; i++) {
            *refined_set++ = i;
            *refined_set = '\0';
            *length += 1;
        }

        return refine_set(length, refined_set, set + 2 + has_escape, FALSE, code); 
    }    
    *refined_set++ = *set;
    *refined_set = '\0';
    *length += 1;
    
    return refine_set(length, refined_set, set + 1, TRUE, code);
}

static char get_escape(const char c) 
{
    char escape;
    switch (c) {
    case '\\':
        escape = '\\';
        break;
    case 'a':
        escape = '\a';
        break;
    case 'b':
        escape = '\b';
        break;
    case 'f':
        escape = '\f';
        break;
    case 'n':
        escape = '\n';
        break;
    case 'r':
        escape = '\r';
        break;
    case 't':
        escape = '\t';
        break;
    case 'v':
        escape = '\v';
        break;
    case '\'':
        escape = '\'';
        break;
    case '\"':
        escape = '\"';
    break;
    default :
        escape = ERROR_CODE_INVALID_FORMAT;
        break;
    }
    return escape;
}


