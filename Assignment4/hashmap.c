#include "hashmap.h"
#include "node.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#if !defined(NULL)
#define NULL ((void*) 0);
#endif

#if !defined(TRUE)
#define TRUE (1)
#endif

#if !defined(FALSE)
#define FALSE (0)
#endif

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{
    hashmap_t* pa_hashmap = malloc(sizeof(hashmap_t));
    hashmap_t* hashmap_ptr = pa_hashmap;
     
    assert(sizeof(hashmap_t) == 12);
    
    hashmap_ptr -> hash_func = p_hash_func;
    hashmap_ptr -> plist = malloc(sizeof(node_t*) * length);
    memset((char*)(hashmap_ptr -> plist), 0, sizeof(node_t*) * length);
    hashmap_ptr -> length = length;

    return pa_hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    size_t (*p_hash_func)(const char* key) = hashmap -> hash_func;
    size_t hash_length = hashmap -> length;
    size_t index = p_hash_func(key) % hash_length;
    size_t key_len = strlen(key);
    node_t** plist = hashmap -> plist;
    node_t* pa_node = *(plist + index);
    int has_key = FALSE;
    
    if (pa_node == NULL) {
        pa_node = malloc(sizeof(node_t));  
        *(plist + index) = pa_node;

        pa_node -> key = malloc(sizeof(char) * key_len + 1);
        memcpy(pa_node -> key, key, key_len + 1);
        pa_node -> value = value;
        pa_node -> key_len = key_len;
        pa_node -> next = NULL;
        
        return TRUE;
    }

    while (pa_node != NULL) {
        if (strlen(pa_node -> key) == key_len && strcmp(pa_node -> key, key) == 0) {
            has_key = TRUE;
            break;    
        } else if (pa_node -> next == NULL) {
            break;
        }
        pa_node = pa_node -> next;
    }         

    if (has_key == TRUE) {
        return FALSE;
    }

    pa_node -> next = malloc(sizeof(node_t));      
    pa_node = pa_node -> next;
    pa_node -> key = malloc(sizeof(char) * key_len + 1);
    memcpy(pa_node -> key, key, key_len + 1);
    pa_node -> value = value;
    pa_node -> key_len = key_len;
    pa_node -> next = NULL;

    return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    size_t hash_index = hashmap -> hash_func(key) % hashmap -> length;
    node_t* pa_node = *((hashmap -> plist) + hash_index);
    
    while (pa_node != NULL) {
        if (strlen(key) == pa_node -> key_len && strcmp(key, pa_node -> key) == 0) {
            return pa_node -> value;
        }
        pa_node = pa_node -> next;
    }
    

    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, const int value)
{
    size_t hash_index = hashmap -> hash_func(key) % hashmap -> length;
    node_t* pa_node = *((hashmap -> plist) + hash_index);

    while (pa_node != NULL) {
        if (strlen(key) == pa_node -> key_len && strcmp(key, pa_node -> key) == 0) {
            pa_node -> value = value;
            return TRUE;
        }
        pa_node = pa_node -> next;
    }

    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    size_t hash_index = hashmap -> hash_func(key) % hashmap -> length;
    node_t* pa_node = NULL;
    node_t* pa_node_next = *(hashmap -> plist + hash_index);

    while (pa_node_next != NULL) {
        if (strlen(key) == pa_node_next -> key_len && strcmp(key, pa_node_next -> key) == 0) {
            if (pa_node == NULL) {
                *(hashmap -> plist + hash_index) = pa_node_next -> next;
            } else {
                pa_node -> next = pa_node_next -> next;
            }
            free(pa_node_next -> key);
            free(pa_node_next);
            return TRUE;
        }
        pa_node = pa_node_next;
        pa_node_next = pa_node_next -> next;
    }
    
    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    node_t** plist = hashmap -> plist;
    node_t* pa_node = NULL;
    size_t i;
    
    for (i = 0; i < hashmap -> length; i++) {
         pa_node = *(plist + i);
         while (pa_node != NULL) {
              node_t* next = pa_node -> next;
              free(pa_node -> key);
              free(pa_node);
              pa_node = next;
          }
    }

    free(plist);
    free(hashmap);
}





