#include "data_store.h"
#include <string.h>
#include "user.h"
#include "stdlib.h"
#include "stdio.h"

extern inline void hide_Info(char* c1, size_t strlen, int mode);

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    user_t** users_ptr = users_or_null;
    user_t* result = NULL;
    while (*users_ptr != NULL) {
        user_t* user = *users_ptr;
        if (user -> id == id) {
            result = user;
            break;
        }
        users_ptr++;
    }
    return result;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    user_t** users_ptr = users_or_null;
    user_t* result = NULL;

    while (*users_ptr != NULL) {
        user_t* user = *users_ptr;
        if (strncmp(user -> username, username, LENGTH) == 0) {
            result = user;
            break;
        }
        users_ptr++;
    }
    return result;
}

bool update_email(user_t** users_or_null, size_t id, const char* email)
{
    user_t* user_or_null = get_user_by_id_or_null(users_or_null, id);
    if (user_or_null == NULL) {
        return false;
    }

    size_t email_bak_length = strlen(user_or_null -> email);
    size_t email_new_length = strlen(email);
    char email_bak[LENGTH];
    char email_new[LENGTH];

    strncpy(email_bak, user_or_null -> email, email_bak_length);
    *(email_bak + email_bak_length) = '\0';
    
    strncpy(email_new, email, email_new_length);
    *(email_new + email_new_length) = '\0';
    
    strncpy(user_or_null -> email, email, email_new_length);
    *(user_or_null -> email + email_new_length) = '\0';
    
    #ifndef RELEASE
    hide_Info(email_bak, email_bak_length, 0);
    hide_Info(email_new, email_new_length, 0);
    #endif
    
    char msg[150];
    size_t msg_length;
    FILE* fp = fopen("log.txt", "a+");
    sprintf(msg, "TRACE: User %d updated email from \"%s\" to \"%s\"\r\n", user_or_null -> id, email_bak, email_new);
    msg_length = strlen(msg);
    fwrite(msg, sizeof(char), msg_length, fp);
    fclose(fp);
    return true;
}

bool update_password(user_t** users_or_null, size_t id, const char* password)
{
    user_t* user_or_null = get_user_by_id_or_null(users_or_null, id);
    if (user_or_null == NULL) {
        return false;
    }

    size_t password_bak_length = strlen(user_or_null -> password);
    size_t password_new_length = strlen(password);
    char password_bak[LENGTH];
    char password_new[LENGTH];

    strncpy(password_bak, user_or_null -> password, password_bak_length);
    *(password_bak + password_bak_length) = '\0';
    
    strncpy(password_new, password, password_new_length);
    *(password_new + password_new_length) = '\0';
    
    strncpy(user_or_null -> password, password, password_new_length);
    *(user_or_null -> password + password_new_length) = '\0';
    
    #ifndef RELEASE
    hide_Info(password_bak, password_bak_length, 1);
    hide_Info(password_new, password_new_length, 1);
    #endif
    
    char msg[150];
    size_t msg_length;
    FILE* fp = fopen("log.txt", "a+");
    sprintf(msg, "TRACE: User %d updated password from \"%s\" to \"%s\"\r\n", user_or_null -> id, password_bak, password_new);
    msg_length = strlen(msg);
    fwrite(msg, sizeof(char), msg_length, fp);
    fclose(fp);
    return true;
}
