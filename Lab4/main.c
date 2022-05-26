#include "my_string.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

int main(void)
{

    {
       char a[3]; 
       char* ptr = a;
       a[0] = 'a';
       a[1] = 'b';
       a[2] = '\n';
        

       *ptr ^= *(ptr + 1);
       *(ptr + 1) ^= *ptr;
       *ptr ^= *(ptr + 1);

    }

    {
         char str[12 + 1] = "Oh happy day";
         char* expected = "yad yppah hO";
         reverse(str);
         assert(strcmp(str, expected) == 0);


    }

    {
        char str[] = "Oh happy day";
        int index = index_of(str, "happy"); /* index: 3 */
        assert(index == 3);

    }

{
char str[] = "Oh happy day";
char* ex = "hO yppah yad";
reverse_by_words(str); /* str이 "hO yppah yad"가 됨 */
assert(strcmp(str, ex) == 0);

}
printf("----------------------------------------\n");
{
char str[] = "OhhappydayMylovely day!";
char* p = tokenize(str, " !"); 
char* b;
printf("%s\n", p);
b = tokenize(p, " !");
printf("%s\n", b);

}
printf("----------------------------------------\n");
{


char str[] = "Oh happy day! My lovely day!";
char* ptr;
tokenize(str, " !"); /* &str[0]을 반환. 토큰은 "Oh" */
tokenize(NULL, " !"); /*  "happy" */
tokenize(NULL, " !"); /* "day" */
tokenize(NULL, " !"); /*  토큰은 "My" */
tokenize(NULL, " !"); /*  토큰은 "lovely" */
tokenize(NULL, " !"); /* 토큰은 "day" */
ptr = tokenize(NULL, " !"); /*  토큰은 "NULL" */
printf("%s\n", tokenize(str, " !")); /*NULL*/
}
printf("\n");
{
char str[] = "........,,,,,, ";
char delim[] = ",. ";
printf("sss%s\n", tokenize(str, delim));
printf("ssss%s\n", tokenize(NULL, delim));
}
   {
        const char* one_delim = " ";
        const char* mult_delim = " ,!";
        char str_strtok[] = "I am a boy, and you are a girl!";
        char str_tokenize[] = "I am a boy, and you are a girl!";

        char str_strtok2[] = "!,I    am  a boy,  and    you   are a   girl!";
        char str_tokenize2[] = "!,I    am  a boy,  and    you   are a   girl!";
        char* token_strtok = strtok(str_strtok, one_delim);
        char* token_tokenize = tokenize(str_tokenize, one_delim);

        while (token_strtok != NULL && token_tokenize != NULL) {
            assert(strcmp(token_strtok, token_tokenize) == 0);
            token_strtok = strtok(NULL, one_delim);
            token_tokenize = tokenize(NULL, one_delim);
        }

        token_strtok = strtok(str_strtok2, mult_delim);
        token_tokenize = tokenize(str_tokenize2, mult_delim);

        while (token_strtok != NULL && token_tokenize != NULL) {
            assert(strcmp(token_strtok, token_tokenize) == 0);
            token_strtok = strtok(NULL, mult_delim);
            token_tokenize = tokenize(NULL, mult_delim);
        }
    }


{
char empty0[1] = {'\0'};
char* empty1 = "";

assert(strncmp(empty0, empty1, 1) == 0); 



}


{

char str[] = "asdf,.. jfdsf";
char delim[] = ",. ";
printf("%s\n" , tokenize(str, delim));
printf("%s\n" , tokenize(NULL, delim));
printf("%s\n" , tokenize(NULL, delim));
}

    {
        const char* one_delim = " ";
        const char* mult_delim = " ,!";
        char str_strtok[] = "I am a boy, and you are a girl!";
        char str_tokenize[] = "I am a boy, and you are a girl!";

        char str_strtok2[] = "!,I    am  a boy,  and    you   are a   girl!";
        char str_tokenize2[] = "!,I    am  a boy,  and    you   are a   girl!";
        char* token_strtok = strtok(str_strtok, one_delim);
        char* token_tokenize = tokenize(str_tokenize, one_delim);

        while (token_strtok != NULL && token_tokenize != NULL) {
            assert(strcmp(token_strtok, token_tokenize) == 0);
            token_strtok = strtok(NULL, one_delim);
            token_tokenize = tokenize(NULL, one_delim);
        }

        token_strtok = strtok(str_strtok2, mult_delim);
        token_tokenize = tokenize(str_tokenize2, mult_delim);

        while (token_strtok != NULL && token_tokenize != NULL) {
            assert(strcmp(token_strtok, token_tokenize) == 0);
            token_strtok = strtok(NULL, mult_delim);
            token_tokenize = tokenize(NULL, mult_delim);
        }
    }
    
    printf("test fin\n");
    return 0;
}
