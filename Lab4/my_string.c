#include "my_string.h"
#include <assert.h>

static int length(const char* str);
static int contains(char c, const char* delims);

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
    static char* s_buffer;
    
    char* str_ptr = s_buffer;
    
    if (str_or_null != NULL) {
        s_buffer = str_or_null;
        str_ptr = s_buffer;
    } else if (s_buffer == NULL) {
        return NULL;
    }
    
    if (contains(*s_buffer, delims)) {
        s_buffer++;
        return tokenize(NULL, delims);
    }
    
    if (*s_buffer == '\0') {
        str_ptr = NULL;
    }
    
    while (*s_buffer != '\0') {
        if (contains(*s_buffer, delims)) {
            *s_buffer++ = '\0';
            break;
        }
        s_buffer++;
    }
    
    return str_ptr;
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

static int contains(char c, const char* delims) 
{
    while (*delims != '\0') {
        if (*delims == c) {
            return 1;
        }
        delims++;
    }
    return 0;
}
