#include "array.h"
#include <limits.h>

int get_index_of(const int numbers[], const size_t element_count, const int num) 
{
    int i;
    const int* ptr = numbers;
    
    for (i = 0; i < element_count; i++) {
        if (*ptr++ == num) {
            return i;
        }
    }
    
    return -1;
}


int get_last_index_of(const int numbers[], const size_t element_count, const int num) 
{
    
    int i; 
    const int* ptr = numbers + element_count - 1;
    
    for (i = 0; i < element_count; i++) {
        if (*ptr == num) {
            return element_count - i - 1;
        }
        ptr--;
    }

    return -1;
}

int get_max_index(const int numbers[], const size_t element_count) 
{
    int i; 
    const int* max_ptr; 
    const int* ptr = numbers;

    if (element_count == 0) {
        return -1;
    }

    max_ptr = numbers;

   for (i = 0; i < element_count; i++) {
        if (*ptr > *max_ptr) { 
            max_ptr = ptr; 
        }
        ptr++;
    }

    return max_ptr - numbers;
}

int get_min_index(const int numbers[], const size_t element_count) 
{
    int i; 
    const int* min_ptr; 
    const int* ptr = numbers;

    if (element_count == 0) {
        return -1;
    }

    min_ptr = numbers;  

   for (i = 0; i < element_count; i++) {
        if (*ptr < *min_ptr) { 
            min_ptr = ptr; 
        }
        ptr++;
    }
    return min_ptr - numbers;
}

int is_all_positive(const int numbers[], const size_t element_count) 
{
    int i;
    const int* ptr = numbers;

    if (element_count == 0) {
        return FALSE;
    }

    for (i = 0; i < element_count; i++) {
        if (*ptr++ < 0) { 
            return FALSE;
        }
    }        

    return TRUE;
}

int has_even(const int numbers[], const size_t element_count) 
{
    int i;   
    const int* ptr = numbers;
  
    for (i = 0; i < element_count; i++) {
        if (*ptr++ % 2 == 0) {
            return TRUE;
        }            
    }

    return FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos) 
{
    int i; 
    int* ptr = numbers;

    if (element_count == 0 || pos > element_count) {
        return FALSE;
    }
    
    ptr += element_count;
    for (i = pos; i < element_count; i++) {
        *ptr = *(ptr - 1);
        ptr--;
    }
    *ptr = num;

    return TRUE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index) 
{
    int i;
    int* ptr = numbers;

    if (element_count == 0 || element_count <= index) {
        return FALSE;
    }
    
    ptr += index;
    for (i = index; i < element_count - 1; i++) {
       *ptr = *(ptr + 1);
        ptr++;
    }
    *ptr = INT_MIN;

    return TRUE;
}



