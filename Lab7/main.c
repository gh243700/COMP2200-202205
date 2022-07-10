#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(void)
{
    {
        const char* str = "I like cookies.  Do you like cookies? Cookies are good!";
        char** tokens = tokenize_malloc(str, " ?!.");
        char** tt = tokens;
        printf("sizeof void* %d\n", sizeof(void*));
        
        printf("start\n");
        while(*tt != NULL) {
            printf("%p\n", (void*)*tt);
            tt++;
        }
        printf("end of my printf");
        
        tt = tokens;
        
        assert(strcmp(*tt++, "I") == 0);
        assert(strcmp(*tt++, "like") == 0);
        assert(strcmp(*tt++, "cookies") == 0);
        assert(strcmp(*tt++, "Do") == 0);
        assert(strcmp(*tt++, "you") == 0);
        assert(strcmp(*tt++, "like") == 0);
        assert(strcmp(*tt++, "cookies") == 0);
        assert(strcmp(*tt++, "Cookies") == 0);
        assert(strcmp(*tt++, "are") == 0);
        assert(strcmp(*tt++, "good") == 0);
        assert(*tt == NULL);

        tt = tokens;
        while (*tt != NULL) {
            free(*tt++);
        }

        free(tokens);
        
        printf("aaaaa");
    }
    
    {
        
        const char* str = "I like cookies. Do you like cookies? Cookies are good!";
        char** tokens = tokenize_malloc(str, "");
        char** tt = tokens;
        
        printf("\n test 2\n%s", *tt);
        assert(strcmp(*tt++, "I like cookies. Do you like cookies? Cookies are good!") == 0);
        assert(*tt == NULL);

        tt = tokens;
        while (*tt != NULL) {
            free(*tt++);
        }

        free(tokens);
        
        printf("--------------------------------\ntest2 complete--------------------------------\n");
        
    }
    
    {
        const char* str = "I like cookies. Do you like cookies? Cookies are good!";
        char** tokens = tokenize_malloc(str, "");
        char** tt = tokens;
        assert(strcmp(*tt++, "I like cookies. Do you like cookies? Cookies are good!") == 0);
        assert(*tt == NULL);
 
        tt = tokens;
        while (*tt != NULL) {
            free(*tt++);
        }
        free(tokens);
 
        puts("empty delim test\n");
    }
    
    
    {
        const char* str = " I ";
        char** tokens = tokenize_malloc(str, " ?!.");
        char** tt = tokens;
 
        assert(strcmp(*tt++, "I") == 0);
        assert(*tt == NULL);
 
        tt = tokens;
        while (*tt != NULL) {
            free(*tt++);
        }
        free(tokens);
 
        puts("test1\n");
    }

     {
        const char* str = "I like cookies. Do you like cookies? Cookies are good!";
        char** tokens = tokenize_malloc(str, " ?!.");
        char** tt = tokens;
 
        assert(strcmp(*tt++, "I") == 0);
        assert(strcmp(*tt++, "like") == 0);
        assert(strcmp(*tt++, "cookies") == 0);
        assert(strcmp(*tt++, "Do") == 0);
        assert(strcmp(*tt++, "you") == 0);
        assert(strcmp(*tt++, "like") == 0);
        assert(strcmp(*tt++, "cookies") == 0);
        assert(strcmp(*tt++, "Cookies") == 0);
        assert(strcmp(*tt++, "are") == 0);
        assert(strcmp(*tt++, "good") == 0);
        assert(*tt == NULL);
 
        tt = tokens;
        while (*tt != NULL) {
            free(*tt++);
        }
        free(tokens);
 
        puts("test2\n");
    }
 
    {
        const char* str = "";
        char** tokens = tokenize_malloc(str, "");
        char** tt = tokens;
        
        printf("str('') = '%s'\n", *tt);
        assert(*tt == NULL);
 
        tt = tokens;
        while (*tt != NULL) {
            free(*tt++);
        }
        free(tokens);
 
        puts("test3\n");
    }
 
    {
        const char* str = "II";
        char** tokens = tokenize_malloc(str, " ");
        char** tt = tokens;
        assert(strcmp(*tt++, "II") == 0);
        assert(*tt == NULL);
 
        tt = tokens;
        while (*tt != NULL) {
            free(*tt++);
        }
        free(tokens);
 
        puts("test4\n");
    }
 
    {
        const char* str = "I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I  I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I I";
        char** tokens = tokenize_malloc(str, " ");
        char** tt = tokens;
        size_t i = 0;
        while (*tt != NULL) {
            i++;
            printf("i is :%d ac val is :%s\n", i, *tt);
            assert(*(*tt) == 'I');
            tt++;
        }
 
        assert(*tt == NULL);
 
        tt = tokens;
    
        while (*tt != NULL) {
            free(*tt++);
        }
        free(tokens);
 
        puts("test5\n");
    }
    
    printf("finish");


    return 0;
}
