#include "tokenize.h"
#include <string.h>
#include <stdlib.h>

char** tokenize_malloc(const char* str, const char* delim) 
{
    const char* str_ptr = str;

    size_t line_count;

    const char* offset = str_ptr;

    char** pa_tokens;

    char* pa_token = NULL;

    size_t token_size = sizeof(char*);
    
    line_count = 0;
    pa_tokens = malloc(token_size);
    
    if (*delim == '\0' && *str != '\0') {

        size_t size = strlen(str) * sizeof(char) + sizeof(char);

        pa_token = malloc(size);

        memcpy(pa_token, str, size);

        goto malloc_tokens;
    }
    
    while (*offset != '\0') {

        const char* delim_ptr = delim;
        pa_token = NULL;
        while (*delim_ptr != '\0') { 

            if (*offset == *delim_ptr++ || *(offset + 1) == '\0') {
                int subtract_ptr = offset - str_ptr;
                
                if (str == str_ptr && *(offset + 1) == '\0') {
                    subtract_ptr++;
                }
              
                pa_token = malloc(sizeof(char) * subtract_ptr + sizeof(char));
                memcpy(pa_token, str_ptr, sizeof(char) * subtract_ptr + sizeof(char));    
                pa_token[subtract_ptr] = '\0';
                
                str_ptr = offset + 1;
                
                break;
            }
        }
        
        if (pa_token != NULL) {

            char** pa_temp;
            if (strcmp(pa_token, "") == 0) {

                goto free_pa_token;
            }
            
            while (*delim_ptr != '\0') {

                if (*pa_token == *delim_ptr) {
free_pa_token:
                    free(pa_token);
                    pa_token = NULL;
                    goto continue_loop;
                }
                delim_ptr++;
            }
malloc_tokens:
            line_count++;
            if (line_count >= token_size / sizeof(char*)) {

                token_size *= 2;
                pa_temp = realloc(pa_tokens, token_size);
                if (pa_temp != NULL) {
                    pa_tokens = pa_temp;
                }
            }
            pa_tokens[line_count - 1] = pa_token;
        }
continue_loop:
        offset++;
    }
    
    pa_tokens[line_count] = NULL;
    
    return pa_tokens;
}
