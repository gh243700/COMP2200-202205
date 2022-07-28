#ifndef USER_H
#define USER_H

#include <stddef.h>

#define LENGTH (50)

typedef struct user {
    size_t id;
    char username[LENGTH];
    char email[LENGTH];
    char password[LENGTH];
} user_t;

#endif

