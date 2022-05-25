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

{
char str[] = "Oh happy day! My lovely day!";
printf("%s\n" ,tokenize(str, " !")); /* &str[0]을 반환. 토큰은 "Oh" */
printf("%s\n" ,tokenize(NULL, " !"));
printf("%s\n" ,tokenize(NULL, " !"));
printf("%s\n" ,tokenize(NULL, " !"));
printf("%s\n" ,tokenize(NULL, " !"));
printf("%s\n" ,tokenize(NULL, " !"));
printf("%s\n" ,tokenize(NULL, " !"));
printf("%s\n" ,tokenize(NULL, " !"));
}
printf("\n");
{


char str[] = "Oh happy day! My lovely day!";
printf("%s\n" ,reverse_tokenize(str, " !")); /* &str[0]을 반환. 토큰은 "hO" */
printf("%s\n" ,reverse_tokenize(NULL, " !")); /* &str[3]을 반환. 토큰은 "yppah" */
printf("%s\n" ,reverse_tokenize(NULL, " !")); /* &str[9]을 반환. 토큰은 "yad" */
printf("%s\n" ,reverse_tokenize(NULL, " !")); /* &str[14]을 반환. 토큰은 "yM" */

tokenize(NULL, " !"); /* &str[17]을 반환. 토큰은 "lovely" */
reverse_tokenize(NULL, " !"); /* &str[24]을 반환. 토큰은 "yad" */




}


    
    printf("test fin\n");
    return 0;
}
