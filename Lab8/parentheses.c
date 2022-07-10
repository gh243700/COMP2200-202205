#include "parentheses.h"
#include <stdio.h>

int compare_pos(const void* a, const void* b);
size_t get_matching_parentheses(parenthesis_t* out_parentheses, size_t max_size, const char* str);
void malloc_push(char** pa_stack, char start, size_t* stack_item_count, size_t index);

void malloc_push(char** pa_stack, char start, size_t* stack_item_count, size_t index)
{
    char* ptr = *pa_stack;
    if (index == *stack_item_count) {
        char* temp = realloc(ptr, *stack_item_count * sizeof(char) * 2);
        if (temp != NULL) {
            *pa_stack = temp;
            *stack_item_count *= 2;     
        } else {
            return;
        }
    }
    ptr[index] = start;
}

size_t get_matching_parentheses(parenthesis_t* out_parentheses, size_t max_size, const char* str)
{
    size_t stack_item_count;
    char* pa_stack;
    size_t* pa_stack_index;
    const char* str_ptr = str;
    size_t stack_index = 0;
    size_t result = 0;
    size_t i;
    size_t circle = 0;
    stack_item_count = 8;
    pa_stack = malloc(stack_item_count * sizeof(char));
    pa_stack_index = malloc(stack_item_count * sizeof(size_t));
    
    while (*str_ptr != '\0') {
        char* temp_stack;
        size_t* temp_stack_pos;
        size_t temp_index;
        
        temp_stack = malloc(stack_item_count * sizeof(char));
        temp_stack_pos = malloc(stack_item_count * sizeof(size_t));
      
        if (*str_ptr == '{' || *str_ptr == '(' || *str_ptr == '[' || *str_ptr == '<') {
            malloc_push(&pa_stack, *str_ptr, &stack_item_count, stack_index);
            malloc_push_position(&pa_stack_index, str_ptr - str, &stack_item_count, stack_index);
            stack_index++;
        } else if (*str_ptr == '}' || *str_ptr == ')' || *str_ptr == ']' || *str_ptr == '>') {
            char t;
            int pos;
            int is_front = 0;
            size_t count = stack_index;
            
            temp_index = 0;
            printf("log1\n");
            for (i = 0; i < count; i++) {
                t = pop(pa_stack, stack_index);
                pos = pop_position(pa_stack_index, stack_index);
                stack_index--;
                switch (*str_ptr) {
                case '}':
                    if (t == '{') {
                        is_front = 1;
                    }
                    break;
                case ')':
                    if (t == '(') {
                        is_front = 1;
                    }
                    break;
                case ']':
                    if (t == '[') {
                        is_front = 1;
                    }
                    break;
                case '>':
                    if (t == '<') {
                        is_front = 1;
                    }
                    break;                
                default:
                    assert(0);
                    break;
                }
                
                if (!is_front) {
                    malloc_push(&temp_stack, t, &stack_item_count, temp_index);
                    malloc_push_position(&temp_stack_pos, pos, &stack_item_count, temp_index);
                    temp_index++;
                } else {
                    parenthesis_t ps;
                    ps.opening_index = pos;
                    ps.closing_index = str_ptr - str;
                    
                    printf("open at : %d\n", pos);
                    printf("close at : %d\n", str_ptr - str);
                    if (result == max_size) {
                        out_parentheses[(result + circle) % max_size] = ps;
                        circle++;
                    } else {
                        out_parentheses[result] = ps;
                        result++;
                    }
                    
                    break;
                }
                
            }
            printf("log2\n");
            count = temp_index;
            for (i = 0; i < count; i++) {
                char t1 = pop(temp_stack, temp_index);
                size_t t2 = pop_position(temp_stack_pos, temp_index);
                temp_index--;
                malloc_push(&pa_stack, t1, &stack_item_count, stack_index);
                malloc_push_position(&pa_stack_index, t2, &stack_item_count, stack_index);
                stack_index++;
            }

            printf("log3\n");
        }
        str_ptr++;

        free(temp_stack);
        temp_stack = NULL;
        free(temp_stack_pos);
        temp_stack_pos = NULL;
    }
    printf("log4\n");
    
    free(pa_stack);
    pa_stack = NULL;
    free(pa_stack_index);
    pa_stack_index = NULL;
    
    qsort(out_parentheses, result, sizeof(parenthesis_t), compare_pos);
    
    return result;
}



void malloc_push_position(size_t** pa_stack_index, size_t start, size_t* stack_item_count, size_t index)
{
    size_t* ptr = *pa_stack_index;
    if (index == *stack_item_count) {
        size_t* temp = realloc(ptr, *stack_item_count * sizeof(size_t) * 2);
        if (temp != NULL) {
            *pa_stack_index = temp;
        } else {
            return;
        }
    }
    ptr[index] = start;
}

int compare_pos(const void* a, const void* b)
{
    const parenthesis_t* w0 = (parenthesis_t*)a;
    const parenthesis_t* w1 = (parenthesis_t*)b;
    
    return w0->opening_index - w1->opening_index;
}

size_t pop_position(size_t* pa_stack_index, size_t index) 
{
    size_t* ptr = pa_stack_index;
    
    assert(index > 0);
    return ptr[--index];
}

char pop(char* pa_stack, size_t index) 
{
    char* ptr = pa_stack;
    
    assert(index > 0);
    return ptr[--index];
}
