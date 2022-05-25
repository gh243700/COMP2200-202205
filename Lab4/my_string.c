#include "my_string.h"
#include <assert.h>

static int length(const char* str);

void reverse(char* str)
{
    int i; 
    char* ptr = str;
    int len = length(str);

    for (i = 0; i < len / 2; i++) {
        *ptr ^= *(str + len - i - 1);
        *(str + len - i - 1) ^= *ptr;
        *ptr ^= *(str + len - i - 1);
         ptr++;
    }
}

int index_of(const char* str, const char* word)
{
    const char* str_ptr = str;
    if (*word == '\0') {
        return 0;
    }
    while (*str_ptr != '\0') {
        const char* word_ptr = word;
        const char* str_ptr_temp = str_ptr;
        while (*str_ptr_temp == *word_ptr) {
            str_ptr_temp++;
            word_ptr++;
	    if (*word_ptr == '\0') {
                return str_ptr - str;
            }
        }
        str_ptr++;
    }
    return -1;
}

void reverse_by_words(char* str)
{
    char* str_ptr0 = str;
    char* str_ptr1 = str;
    while (*str_ptr1 != '\0') {
        if (*(str_ptr1 + 1) == '\0') {
            reverse(str_ptr0);
        } else if (*str_ptr1 == ' ') {
            *str_ptr1 = '\0';
            reverse(str_ptr0);
            *str_ptr1 = ' ';
            str_ptr0 = str_ptr1 + 1;
        }                
        str_ptr1++;
    }
}

char* tokenize(char* str_or_null, const char* delims)
{
    static char* msg; 
    char* ptr;

    if (str_or_null != NULL) {
        msg = str_or_null;
    }
    ptr = msg;
 
    if (*msg == '\0') {
        return NULL;
    }    

    while (*msg != '\0') {
        const char* delims_ptr = delims; 
        while (*delims_ptr != '\0') {
            if (*msg == *delims_ptr) {
                if (ptr == msg) {
                    ptr++;
                } else {
                    *msg = '\0';
                    msg++;
                    goto label1;
                }
            }
            delims_ptr++;
        } 
        msg++;
    }
label1:
    return (*ptr == '\0') ? NULL : ptr;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* ptr = tokenize(str_or_null, delims);
    if (ptr != NULL) {
        reverse(ptr);
    }
    return ptr;
}

static int length(const char * str) {
    const char* ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}
