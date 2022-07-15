#include "hashmap.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define DEFAULT_ARRAY_LENGTH (20)

static size_t hash_function(const char* key);

int main(void)
{
    size_t i = 0;
    hashmap_t* hashmap = NULL;
    size_t hash;
    hashmap = init_hashmap_malloc(DEFAULT_ARRAY_LENGTH, hash_function);
    assert(add_key(hashmap, "key1", 10) == TRUE); /* TRUE */
    assert(add_key(hashmap, "key1", 13) == FALSE); /* FALSE */
    assert(add_key(hashmap, "key1", 10) == FALSE); /* FALSE */

    assert(get_value(hashmap, "key1") == 10); /* 21 */
    assert(update_value(hashmap, "key0", 12) == FALSE);
   
    assert(update_value(hashmap, "key1", 1) == TRUE);
    assert(get_value(hashmap, "key1") == 1);
    
    assert(remove_key(hashmap, "key2") == FALSE);
    assert(remove_key(hashmap, "key1") == TRUE);
    assert(get_value(hashmap, "key1") == -1);    

{
    size_t i = 0;
    hashmap_t* hashmap = NULL;

    hashmap = init_hashmap_malloc(DEFAULT_ARRAY_LENGTH, hash_function);

    for (i = 0; i < 100; i++) {
        char key[100];
        int value = (int)i;
        int c;
        int dummy = 512;

        sprintf(key, "key%zu", i);

        assert(add_key(hashmap, key, value) == TRUE);

        c = get_value(hashmap, key);
        assert(c == value);

        assert(add_key(hashmap, key, dummy) == FALSE);

        c = get_value(hashmap, key);
        assert(c == value);
    }

    for (i = 0; i < 100; i++) {
        char key[100];
        int value = (int)(i * i * i);
        int c;

        sprintf(key, "key%zu", i);

        assert(update_value(hashmap, key, value) == TRUE);
        c = get_value(hashmap, key);

        assert(c == value);
    }

    for (i = 0; i < 100; i++) {
        char key[100];
        int c;

        sprintf(key, "key%zu", i);

        assert(remove_key(hashmap, key) == TRUE);
        c = get_value(hashmap, key);

        assert(c == -1);

        assert(remove_key(hashmap, key) == FALSE);
    }

    for (i = 0; i < DEFAULT_ARRAY_LENGTH; i++) {
        assert((hashmap->plist)[i] == NULL);
    }

    destroy(hashmap);
}


    printf("FIN\n");
    return 0;
}

static size_t hash_function(const char* key)
{
    size_t code = 0;
    const char* c = key;

    while (*c != '\0') {
        code += *c++;
    }

    return code;
}
