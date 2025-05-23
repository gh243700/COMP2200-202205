#include "macros.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
int main(void)
{
    {
        int num1 = 10;
        int num2 = 3;

        assert(MAX(++num1, num2) == 12);
        printf("TEST\n");
        
        
    }
    
    {
        int num1;
        int num2;
        int result;
        
        num1 = 0;
        num2 = 1;
        
        result = MAX(num1, num2);
        assert(result == num2);
        
        num1 = 1;
        num2 = 0;
     
        result = MAX(num1, num2);
        assert(result == num1);
        
        num1 = 0;
        num2 = 0;
     
        result = MAX(num1, num2);
        assert(result == num1 && result == num2);
        printf("-------------MAX TEST FIN------------------\n");
    }
    
    {
        int num1;
        int num2;
        int result;
        
        num1 = 0;
        num2 = 1;
        
        result = MIN(num1, num2);
        assert(result == num1);
        
        num1 = 1;
        num2 = 0;
     
        result = MIN(num1, num2);
        assert(result == num2);
        
        num1 = 0;
        num2 = 0;
     
        result = MIN(num1, num2);
        assert(result == num1 && result == num2);
        printf("-------------MIN TEST FIN------------------\n");
    }
    
    {
        int num_int;
        float num_float;
        printf("CHAR_BIT %d\n", CHAR_BIT);
        num_int = 1;
        printf("result 1 %d\n", ABS(num_int));
        assert(ABS(num_int) == 1);
        
        num_int = -2;
        
        printf("result 2 %d\n", ABS(num_int));
        assert(ABS(num_int) == 2);

    
    
        
        num_int = 0;
        assert(ABS(num_int) == 0);
    
    
        
        num_int = -8;
        assert(ABS(num_int) == 8);
        
        
        num_int = -27;
        assert(ABS(num_int) == 27);
        
        num_float = 1.2f;
        assert(ABS(num_float) == 1.2f);
        
        num_float = -1.2f;
        assert(ABS(num_float) == 1.2f);
        
        
        printf("-------------ABS TEST FIN------------------\n");
    }    
    
    
    
    {
        int curr;
        char buffer[256];
        char temp[256];
        
        
        
        RANGE(curr, 20, 40) {
            printf("%d ", curr);
        }
        
        printf("%s\n", buffer);
        
        printf("-------------RANGE TEST FIN------------------\n");
    }
    
    {
        int curr;
        RANGE_DESC(curr, 25, 20) {
            printf("%d ", curr);
        }
        /* 출력 결과 */
        /*
        25 24 23 22 21 20
        */
        
        printf("-------------RANGE_DESC TEST FIN------------------\n");
    }
    {
        int arr[10];
        SET(arr, 0, 10, 0); /* arr: [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ] */
        SET(arr, 1, 1, 10); /* arr: [ 0, 10, 0, 0, 0, 0, 0, 0, 0, 0 ] */
        SET(arr, 3, 4, 25); /* arr: [ 0, 10, 0, 25, 25, 25, 25, 0, 0, 0 ] */
        
        assert(arr[0] == 0);
        assert(arr[1] == 10);
        assert(arr[2] == 0);
        assert(arr[3] == 25);
        assert(arr[4] == 25);
        assert(arr[5] == 25);
        assert(arr[6] == 25);
        assert(arr[7] == 0);
        assert(arr[8] == 0);
        assert(arr[9] == 0);
        
        
        printf("-------------SET TEST FIN------------------\n");
    }
    
    {
        {
            int temp_value = 318;
            int temp_index = 1;
            int temp_count = 0;
            int arr_int[20];
            unsigned int arr_unsigned_int[20];
            char arr_char[20];
            short arr_short[20];
            unsigned short arr_unsigned_short[20];
            float arr_float[20];
            double arr_double[20];
            int value_int = 319;
            unsigned int value_unsigned_int = -1;
            char value_char = 'c';
            short value_short = 319;
            unsigned short value_unsigned_short = -1;
            float value_float = 3.14f;
            double value_double = 3.14f;
            if (1 != 0) SET(arr_int, 0, 1, 318);
            assert(arr_int[0] == 318);
            if (1 != 0) SET(arr_int, 0, ++temp_count, 216); /* count에 표현식이 들어갈때 */
            assert(arr_int[0] == 216);
            if (1 != 0) SET(arr_int, --temp_index, 1, 318); /* index에 표현식이 들어갈때 */
            assert(arr_int[0] == 318);
            if (1 != 0) SET(arr_int, 0, 1, ++temp_value); /* value에 표현식이 들어갈때 1 */
            assert(arr_int[0] == 319);
            if (1 != 0) SET(arr_int, 0, 1, --temp_value); /* value에 표현식이 들어갈때 2 */
            assert(arr_int[0] == 318);
            if (1 != 0) SET(arr_int, 0, 1, --temp_value + 3); /* value에 표현식이 들어갈때 3 */
            assert(arr_int[0] == 320);
            printf("%d, %d, %d \n", temp_index, temp_count, temp_value);
            if (1 != 0) SET(arr_int, ++temp_index - 1, ++temp_count - 1, ++temp_value - 1); /* index, count, value 에 표현식이 들어갈때 */
            printf("%d \n", arr_int[0]);
            assert(arr_int[0] == 317);
            if (1 != 0) SET(arr_int, 0, 0, 123123123); /* count의 매개변수가 0알때 */
            assert(arr_int[0] == 317);
            if (1 != 0) SET(arr_char, 0, 1, value_char); /* char을 대입할때 */
            assert(arr_char[0] == 'c');
            if (1 != 0) SET(arr_short, 0, 1, value_short); /* short을 대입할때 */
            assert(arr_short[0] == 319);
            if (1 != 0) SET(arr_unsigned_short, 0, 1, value_unsigned_short); /* unsigned short을 대입할때 */
            assert(arr_unsigned_short[0] == 65535);
            if (1 != 0) SET(arr_int, 0, 1, value_int); /* int를 대입할때 */
            assert(arr_int[0] == 319);
            if (1 != 0) SET(arr_unsigned_int, 0, 1, value_unsigned_int); /* unsigned int를 대입할때 */
            assert(arr_unsigned_int[0] == 4294967295);
            if (1 != 0) SET(arr_float, 0, 1, value_float); /* float을 대입할때 */
            assert(arr_float[0] == 3.14f);
            if (1 != 0) SET(arr_double, 0, 1, value_double); /* double 대입할때 */
            assert(arr_double[0] == 3.14f);
            if (1 == 0) SET(arr_int, 0, 1, 1234); /* if-else 문 {}없고 SET 실행 */
            else SET(arr_int, 0, 1, 1235);
            assert(arr_int[0] == 1235);
            if (1 == 0) { /* if-else 문 {}있고 SET 실행 */
                SET(arr_int, 0, 20, 0);
            } else {
                SET(arr_int, 0, 1, 10000004);
            }
            assert(arr_int[0] == 10000004);
        }
        
        printf("finnnnn\n");
    }
    return 0;
}
