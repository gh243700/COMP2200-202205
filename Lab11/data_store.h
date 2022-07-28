
#ifndef DATA_STORE_H
#define DATA_STORE_H
#include <stdbool.h>
#include "user.h"
#include <string.h>

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id);

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username);

bool update_email(user_t** users_or_null, size_t id, const char* email);

bool update_password(user_t** users_or_null, size_t id, const char* password);

inline void hide(char* c, size_t str_len, int mode) 
{
    size_t length = str_len;
    
    if (mode == 0) {
        length = 0;
        size_t i;
        char* ptr = c;
        for (i = 0; i < str_len; i++) {
            if (*ptr == '@') {
                break;
            }
            ptr++;
            length++;
        }
    }

    if (length == 1) {
        c[0] = '*';
    } else if (length == 2) {
        c[1] = '*';
    } else {
        memset(&c[1], '*', length - 2);
    }
}

#endif
