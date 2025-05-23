#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "array.h"

int main(void)
{
{
    int ary[7] = { 1, 4, 5, 6, 6, INT_MIN, INT_MIN };
    assert(get_index_of(ary, 5, 6) == 3); /* 3 */
    assert(get_index_of(ary, 5, 2) == -1); /* -1 */


}
{
    int ary[7] = { 1, 4, 6, 6, 5, INT_MIN, INT_MIN };
    assert(get_last_index_of(ary, 5, 6) == 3); /* 3 */
    printf("%d sss\n", get_last_index_of(ary, 5, 2));
    assert(get_last_index_of(ary, 5, 2) == -1); /* -1 */
}
{
    int ary1[7] = { 1, 4, 6, 6, 5, INT_MIN, INT_MIN };
    int ary2[0];
    assert(get_max_index(ary1, 5) == 2); /* 2 */
    assert(get_max_index(ary2, 0) == -1); /* -1 */
    
    
}
{
    int ary1[7] = { 1, 4, -6, -6, 5, INT_MIN, INT_MIN };
    int ary2[0];
    assert(get_min_index(ary1, 5) == 2); /* 2 */
    assert(get_min_index(ary2, 0) == -1); /* -1 */

}

{
    int ary[8] = { 1, 4, -6, -6, 5, INT_MIN, INT_MIN, INT_MIN };

    assert(insert(ary, 5, 10, 3) == 1); /* 1을 반환, ary: [ 1, 4, -6, 10, -6, 5, INT_MIN, INT_MIN ] */

    assert(ary[0] == 1);
    assert(ary[1] == 4);
    assert(ary[2] == -6);
    assert(ary[3] == 10);
    assert(ary[4] == -6);
    assert(ary[5] == 5);    
  
    assert(insert(ary, 6, 10, 7) == 0); /* 0을 반환 */
    assert(insert(ary, 6, 11, 6) == 1); /* 1을 반환.  ary: [ 1, 4, -6, 10, -6, 5, 11, INT_MIN ] */

    assert(ary[0] == 1);
    assert(ary[1] == 4);
    assert(ary[2] == -6);
    assert(ary[3] == 10);
    assert(ary[4] == -6);
    assert(ary[5] == 5);    
    assert(ary[6] == 11); 
    assert(ary[7] == INT_MIN); 
}


{
    int ary[7] = { 1, 4, -6, -6, 5, INT_MIN, INT_MIN };

    assert(remove_at(ary, 5, 1) == 1); /* 1을 반환. result1: [ 1, -6, -6, 5, INT_MIN, INT_MIN, INT_MIN ] */
    assert(ary[0] == 1);
    assert(ary[1] == -6);
    assert(ary[2] == -6);
    assert(ary[3] == 5);
    assert(ary[4] == INT_MIN);
    assert(remove_at(ary, 4, 4) == 0); /* 0을 반환 */
}


    printf("test finsssss\n");
    return 0;

}
